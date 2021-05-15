// ArrayLookup.h: interface for the CArrayLookup class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARRAYLOOKUP_H__A1DFD401_51D4_474D_A7BD_59C55B00F84C__INCLUDED_)
#define AFX_ARRAYLOOKUP_H__A1DFD401_51D4_474D_A7BD_59C55B00F84C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Array.h"
#include "csvHolder.h"
#include "SymlixStore.h"
#include "equation.h"


class CArrayLookup : public CArraySetValue_Impl, public CNavTokens  
{
public:
	CArrayLookup(long iLeft,long iRight,vector<CToken*>& vExpLine, IARDataStore* pIStore,ostream& osErrReport=cerr);
	virtual ~CArrayLookup();

//	virtual bool assignsValues() const{ return true; } // can give values - change to true in time


	static bool check(long iLeft,long iRight,vector<CToken*>& vExpLine, IARDataStore* pIStore, ostream& osErrReport);
	#ifndef NDEBUG
	static bool unitTests(IARDataStore* pIStore);
	#endif

//	virtual CToken* getToken();
//	virtual bool addTokenPtVec(const vector< CToken* >& rvecpt);

protected:
	virtual void out( ostream& os ) const;

//	vector<CToken*> m_vecToks;

};

#endif // !defined(AFX_ARRAYLOOKUP_H__A1DFD401_51D4_474D_A7BD_59C55B00F84C__INCLUDED_)
