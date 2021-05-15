// Tokeniser.h: interface for the CTokeniser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TOKENISER_H__48BB508A_494E_46CB_B37D_3D1DF3496C1F__INCLUDED_)
#define AFX_TOKENISER_H__48BB508A_494E_46CB_B37D_3D1DF3496C1F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef NDEBUG
//#define DEBUGSUBSMACRO
#endif

#include <vector>
#include <set>
#include <list>
#include <string>
#include <numeric>
#include "Token.h"
#include <fstream>
//#include "StringHolder.h"

#pragma warning(disable:4786)

using namespace std;

struct ltstr
{
  bool operator()(const char s1, const char s2) const
  {
    return s1<s2;
  }
};

/*
struct ltStringstr
{
	bool operator()(const string s1, const string s2) const
	{
		if (s1.length()==s2.length())
			return accumulate(s1.begin(),s1.end(),0)>accumulate(s2.begin(),s2.end(),0);
			else
			return s1.length()>s2.length();
	}

};*/

struct ltstrSTR
{
  bool operator()(const char* s1, const char* s2) const
  {
    return strcmp(s1, s2) < 0;
  }
};



//#define setofwords set< const char*, ltstrSTR >
//#define setofwords set< CStringHolder, CStringHolder >

class CTokeniser : public CStringHelper 
{

protected:
	class CMaybeNumber
	{
	public:
	CMaybeNumber(){clear();}
	~CMaybeNumber(){}
	inline void clear(){ m_bStartNeg=false; m_bLastE=false; m_bHasDecimal=false; m_bNumeric=m_bLastNumeric=true; m_bFirst=true;}
	void AddChar( char c );
	inline bool Numeric() const { return m_bLastNumeric; }

	private:
	bool m_bStartNeg;
	bool m_bLastE;
	bool m_bHasDecimal;
	bool m_bNumeric;
	bool m_bFirst;
	bool m_bLastNumeric;

	};

public:
	CTokeniser(setofwords& setFileNames, const mapUserDefinedKeys& cmapUDK );
    CTokeniser(const char** psDelim, int iCountDelim, setofwords& setFileNames, const mapUserDefinedKeys& cmapUDK );
    CTokeniser(const char* sDelimFile, setofwords& setFileNames, const mapUserDefinedKeys& cmapUDK );
	~CTokeniser();

	long tokeniseLine(long lLine, const char* sLine, list<CToken>& vct, const char* sFileName, bool bForPaint = false ); // return number of tokens added
	virtual bool isReady(){ return m_bState; } // is this object OK to continue ?
	bool getNoFilePointer(setofwords::const_iterator& cit);
	bool spinUpMacroTokens( mapUserDefinedKeys& mapUDK, const list<CToken>& vct );
	static void assignVariables( vector<CToken*>& rvecLpts );

	friend ostream& operator << (ostream& os, const CTokeniser& cT ){ return cT.DumpDelim(os);}
protected:
	virtual void InitKeysandSets(const mapUserDefinedKeys& cmapUDK);
	virtual void InitDelimVec();
	virtual void InitFuncKeys();
	virtual void InitSolverKeys();
	virtual void InitEventKeys();
	virtual void InitEquationKeys();
	virtual void InitArrayKeys();
	virtual void InitTypeModifierKeys();
	virtual void InitMacroKeys();
	virtual void InitUserDefinedKeys(const mapUserDefinedKeys& cmapUDK);
	void Init(const char** psDelim, int iCountDelim, const mapUserDefinedKeys& cmapUDK );
	void Init(const char* sDelimFile, const mapUserDefinedKeys& cmapUDK );
	ostream& DumpDelim(ostream& os) const;
	vector<CStringHolder>::iterator FindLargest(const string& sExp, vector<CStringHolder>::iterator& pit) const;
	vector<CStringHolder>::iterator FindLargest(long lLast,long& lCount, long& lGap, const string& sExp, vector<CStringHolder>::iterator& it) const;
	bool IsANumber(const string str );
	eTokenType AssignTokenAsNumberorNot(const string& str);
	void TrimForChar(string& sToken, const char c);
	bool HasSpacesOnly(const string& sCheck ) const;
//	void setStringLowerCase( string &rsStr ) const;

	long m_iLineNo; // to keep tags on line position
	long m_iOffset; // to keep tage on x offset in file
//	set<char,ltstr> m_SetDelim;
//	setofwords m_SetDelimWords;
	vector<CStringHolder> m_vecDelimWords;

	setofwords m_SetMathWords;
	setofwords m_SetEventWords;
	setofwords m_SetSolverWords;
	setofwords m_SetEquationWords;
	setofwords m_SetTypeModifierWords;
	setofwords m_SetMacroWords;
	setofwords m_SetUserDefinedWords;
	setofwords m_SetFuncWords;
	setofwords m_SetArrayWords;
	setofwords& m_rsetFileNames;
	pair< setofwords::iterator, bool > m_pairTokenNoFile;
	bool m_bState; // need to know if OK to continue
	CMaybeNumber m_mnChecker;


};

class CHoldTokeniser
{
protected:
		CTokeniser*	m_pTokeniser;
		setofwords m_setRecognisedFileNames; // not populated - but needed 
		mapUserDefinedKeys m_mapUDK; // not populated - but needed
		list<CToken> m_lToks;

public:
		CHoldTokeniser();
		virtual ~CHoldTokeniser();
		virtual CTokeniser* getTokeniser(){ return m_pTokeniser; }
		virtual list<CToken>& getTokenisedList(long iLine, const char* sLine, const char* sStreamName );
	    virtual void assignVariables( vector<CToken*>& rvecLpts ) const;

};



class CTestHoldTokeniser : public CHoldTokeniser
{
public:
		CTestHoldTokeniser():CHoldTokeniser(){}
		virtual ~CTestHoldTokeniser(){}
		vector<CToken*>& getRefVectorOfTokenPointers(long iLine, const char* sLine, const char* sStreamName );
protected:
		vector<CToken*> m_vecCToks;
};

#endif // !defined(AFX_TOKENISER_H__48BB508A_494E_46CB_B37D_3D1DF3496C1F__INCLUDED_)
