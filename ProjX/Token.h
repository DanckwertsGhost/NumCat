// Token.h: interface for the CToken class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TOKEN_H__56241753_F502_4703_9ECF_9886501EB46C__INCLUDED_)
#define AFX_TOKEN_H__56241753_F502_4703_9ECF_9886501EB46C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include "StringPlus.h"
#include "StringHolder.h"
#include "global.h"
#include "VarRoot.h"

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

using namespace std;

#define setofwords set< CStringHolder, CStringHolder >
#define mapUserDefinedKeys map< CStringHolder, list< CToken > >
//#define setofwords set< string >

class CLocation
{
public:
	CLocation();
	CLocation( const CLocation& cl):m_plParent(NULL){ copy(cl); }
	CLocation(long iLine, long iX, setofwords::iterator& itsw, CLocation* plParent=NULL);
	virtual ~CLocation();

	inline long getiX() const{ return m_iX; }
	inline long getiLine() const{ return m_iLine; }
	inline long getiXOrig() const{ return m_iXOrig; }
	void setRefFile(setofwords::const_iterator& cit){ m_citFile=cit; m_bHasIt=true; }
	const CLocation* getParent() const { return m_plParent; }
	void setParent(const CLocation* pcl);
	void setLocation(const long& iLine, const long& iX, long iXOrig = NOT_DEFINED){ m_iX=iX; m_iLine=iLine; m_iXOrig=iXOrig; }
	setofwords::const_iterator getRefFile() const { return m_citFile; }
	bool hasALoop(CLocation* lTest){ return false; } // TBI - stop loops of files
	bool hasFileRef() const{ return m_bHasIt; }
	CLocation& operator = (const CLocation& cl ){ copy(cl); return *this; }
	bool operator > (const CLocation& cl ) const;
	bool operator < (const CLocation& cl ) const {return cl>*this;}
	bool operator == (const CLocation& cl ) const;

	friend ostream& operator << (ostream& os, const CLocation& cl); // for debuging
	
private:

	void copy(const CLocation& cl);

	long m_iX;
	long m_iXOrig; // for subsituted values so correct order maintaned
	long m_iLine;
//	long m_iFileIndexCode;
	CLocation* m_plParent;
	setofwords::const_iterator m_citFile;
	bool m_bHasIt;

};


// have removed ctOperator - though perhaps this should be reinstituted to repair 
enum eTokenType{ctDefinedNotAssigned,ctComment, ctDerivative, ctVariable,
                ctDelim, ctNotDefined, ctUserDefined, ctNumber, ctName,
				ctDepVariable, ctIndVariable, ctSubsVariable,
				ctEventKeyWord, ctSolverKeyWord, ctEquationKeyWord,
				ctMacroKeyWord, ctArrayKeyWord, ctTypeModifier };


enum eTokArrayType{atNormal,atArray,atPartOfArray};

class CStringHelper
{
public:
	CStringHelper(){};
	virtual ~CStringHelper(){};
protected:
	inline bool setStringLowerCase(std::string& rsStr)
	{
		m_shb = false;

		for(m_shiC=0;m_shiC<rsStr.length();m_shiC++)
			{
			ATLTRACE("[%s] count=%d ascii %d ",rsStr.c_str(),m_shiC,rsStr[m_shiC]);
			if ((rsStr[m_shiC] < 90)&&(rsStr[m_shiC]>64))
					{
					m_shb = true;
					rsStr[m_shiC]+=32;
					}
			ATLTRACE(" after [%s]\n",rsStr.c_str());
			}	
		return m_shb;
	}
private:

	long m_shiC;
	bool m_shb;

};

class CArray; //declare for use latter and to avoid a loop of defintions

class CToken: public CStringHelper
{
public:
	virtual CToken* getPointer();
	virtual bool AssignParent( CToken* pCTParent );
	virtual void ClearParent(){m_ptCTtoSame=NULL;}
	CToken();
//	CToken(const long& iL, const long& iX, const char* sToken, eTokenType eType = ctNotDefined);
	CToken(const long& iL, const long& iX, const string& sToken, setofwords::const_iterator& cit, eTokenType eType = ctNotDefined, bool bPartArrayFlag = false );
	CToken(const string& sToken, eTokenType eType, setofwords::const_iterator& cit );
	CToken(const CToken& cT);
	virtual ~CToken();

	#ifndef NDEBUG
	virtual bool IsOfType(const eTokenType eTest) const;/*{ return eTest==m_eToken;}*/
	#else
	virtual bool IsOfType(const eTokenType eTest) const{ return eTest==m_eToken;}
	#endif
	virtual bool IsOfTypeVariable() const;
	virtual bool IsIterative() const { return m_sToken.isIterative(); }
	virtual eTokenType getType() const{ return m_eToken; }
	virtual void setType(eTokenType eType, bool bLC = false );
/*	virtual void setType(eTokenType eType) // for debug only
		{
		 if ((m_eToken==ctMacroKeyWord)&&(eType==ctComment))
				cout << (*this)<<"Type conversion\n";
		 m_eToken=eType;
	    }*/
	virtual bool setIndex(const long iIndex);
	virtual const CStringPlus& getString() const{ return m_sToken; }
	string  getStringWithoutDeriv() const;
	virtual CStringPlus& getStringRef() { return m_sToken; }
	virtual long getLine() const { return m_Location.getiLine(); }
	virtual long getX() const { return m_Location.getiX(); }
	virtual long getIndex() const { return m_iIndex; } // maybe should return ref for speed - check latter
	virtual const CLocation& getLocation() const{ return m_Location;}
	virtual void Copy(const CToken& cT);
	virtual CToken& operator = (const CToken& cT);
	virtual bool operator == (const CToken& cT) const;
	virtual bool operator > (const CToken& cT) const;
	virtual bool operator < (const CToken& cT) const;
	virtual void Trim(){ ReplaceAllChar('\t',' '); TrimForChar(' ');}
	virtual bool operator() (const CToken& ct1, const CToken&ct2) const{ return ct2.greaterThan(ct1); }
	virtual const CToken& getRootToken() const;
	virtual CToken* getRootTokenPt();
	virtual void setString(const string sToken){ m_sToken = sToken; }
	virtual bool setDervivativeVariable(CToken& ct);
	virtual bool setIterativeVariable(CToken& ct);
	virtual void setRootLocation( const CLocation& cl );
	virtual void setRelativeLocation( const CLocation& clatpoint, const CLocation& clLinePos, const long iOffset );
	virtual bool getUnderlyingVariable(CToken** ppct);
	virtual variable getNumber(); // for type number tokens
	virtual variable getValue(vector<variable>* pvecV);
	virtual bool sameLine(const CToken& ct ) const;
	virtual eTokArrayType getArrayType() const { return m_etatArrayState; }
	virtual void setAsPartArray(){ m_etatArrayState = atPartOfArray;}
	virtual void setAsArray(){ m_etatArrayState = atArray;}
	virtual void setArrayType(eTokArrayType etatArrayState){ m_etatArrayState = etatArrayState; }
	virtual bool linkToArray(CArray* pA){ m_pArray = pA; return (m_pArray!=NULL); }
	virtual CArray* getArray() const{ return m_pArray; }
	virtual void setReserveType( long iSetReserveType ){ m_iReserveType = iSetReserveType; }
	virtual long getReserveType() const { return m_iReserveType; }
	virtual bool isReserved() const { return (m_iReserveType!=NOT_DEFINED); }

	static string getVariableFromDerivative(const string& sDerv);


//	friend ostream& operator << (ostream& os,  const CToken* cT);
	friend ostream& operator << (ostream& os,  const CToken& cT);
//	ostream& operator << (ostream& os);

protected:
	virtual bool adoptChildren( const vector< CToken* >& rChildren );
	eTokArrayType m_etatArrayState;
	CArray* m_pArray;
	virtual bool greaterThan(const CToken& cT) const;
	virtual void TrimForChar(const char c);
	virtual void ReplaceAllChar(const char c, const char cNew);

	eTokenType m_eToken;
	CStringPlus m_sToken;
	CLocation m_Location;
//	long m_iLine, m_iX; // position in input file
	CToken* m_ptCTtoSame;
	CToken* m_ptCTtoDerivValue; // pointer to a derivatives equivalent variable
								/* Note: This value is only intitated once equations
								         have been fully parsed are a mathematical model
										 is being set up */
	CToken* m_ptCTtoIterativeValue;
	long m_iIndex; // index in variables list - allows same equations to be applied to different instances.
	CVarRoot* m_pcvr;
	vector< CToken* >* m_pvecChildren; // a pointer since not every Token will need this
	long m_iReserveType;

public:
	virtual void addChild( CToken* pT );
	virtual bool setToDepVariable();
	virtual bool setToIndVariable();
	virtual bool setToSubsVariable();
	virtual void setToParentType();
	virtual bool HasAParent() const {
						ASSERT2(this!=m_ptCTtoSame); // real trouble - sort this out 
						return (m_ptCTtoSame!=NULL);
									};
	virtual bool setpVarRoot(CVarRoot* pcvr);
	virtual CVarRoot* getpVarRoot() const;
//	virtual bool setConstrainedType( const varStrongType& vst );


};

class CTokenStrCompare
{
	public:
	CTokenStrCompare(){};
	~CTokenStrCompare(){};
    bool operator()( CToken* pct1, CToken* pct2) const { return pct2->getString().compare(pct1->getString())<0; }

};

#define SetPtCToken set<CToken*>
#define SetPtCTokenStringSearch set<CToken* , CTokenStrCompare >

#endif // !defined(AFX_TOKEN_H__56241753_F502_4703_9ECF_9886501EB46C__INCLUDED_)
