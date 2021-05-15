// Array.h: interface for the Array class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARRAY_H__CB02EB0E_3B75_44D7_AE7C_8BB4E915D9B6__INCLUDED_)
#define AFX_ARRAY_H__CB02EB0E_3B75_44D7_AE7C_8BB4E915D9B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Token.h"
#include <ostream>

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

#define ARRAY_LINE_COUNT 4

enum eArrayState{carUninitated,carError,carIntiated};


class CArray 
{
public:
	virtual variable getValue() const;
	CArray();
	virtual ~CArray();

	virtual bool first();
	virtual bool next();
	virtual long getIndex() const;
//	virtual long currentIndex(){ return NOT_DEFINED; }
	virtual long size(){ return NOT_DEFINED; }

	virtual bool IsInError() const{ return (m_eState==carError); }
	virtual bool IsReady() const{ return (m_eState==carIntiated); }
	virtual bool Ready() const;
	virtual string getArrayName() const { return (m_pToken != NULL ? m_pToken->getString() : m_sNoString ); }

	virtual const vector<long>& getIndicies() const { return m_vecIndicies; }
	virtual bool CatArray(CArray* pa){ return false; } // Some array classes may support this

	virtual bool assignsValues() const{ return false; } // can give values
	virtual string getString() const;
	virtual CToken* getToken() { return NULL; }
	virtual bool addTokenPtVec(const vector< CToken* >& rvecpt){ return false; } // not implemented at this level

	friend ostream& operator << (ostream& os,  const CArray* pA);
	friend ostream& operator << (ostream& os,  const CArray& rA){ os << &rA; return os; }


protected:
	virtual void copy( const CArray& rca );
	virtual bool setIndiciesFromString( const string& str ); // helper function
	virtual bool setIndiciesFromData( long iStart=0 ); // helper function
	static long checkArrayName( const CToken& ct );
	virtual void out( ostream& os ) const { os << " CArray type undefined\n"; }
	virtual bool cleanUpTokenNameAndSetAsArray();

	CToken* m_pToken;
	eArrayState m_eState;
	string m_sError;
	vector< long > m_vecIndicies;
	long m_iInd;
	vector< variable > m_vecValues;
	bool bIndiciesSet;
	static const string m_sNoString;


};

class CArraySetValue_Impl : public CArray
{
public:

	CArraySetValue_Impl():CArray(){}
	virtual ~CArraySetValue_Impl(){}

	virtual bool assignsValues() const{ return true; } // can give values - change to true in time

	virtual CToken* getToken()
	{
		ASSERT2(m_iInd>=0);
		if (m_iInd>=m_vecToks.size())
			return NULL;

		return m_vecToks[m_iInd];
	}

	virtual bool addTokenPtVec(const vector< CToken* >& rvecpt);


protected:
	virtual bool setupIndexesFromLHSToken();

	vector<CToken*> m_vecToks;

};

#endif // !defined(AFX_ARRAY_H__CB02EB0E_3B75_44D7_AE7C_8BB4E915D9B6__INCLUDED_)
