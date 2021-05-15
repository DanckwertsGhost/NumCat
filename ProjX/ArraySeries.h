// ArraySeries.h: interface for the CArraySeries class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARRAYSERIES_H__FA447418_3CF9_4BD4_A5B5_A646BA22E5C5__INCLUDED_)
#define AFX_ARRAYSERIES_H__FA447418_3CF9_4BD4_A5B5_A646BA22E5C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Array.h"
#include "SymlixStore.h"
#include "equation.h"


// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)


class CArraySeries : public CArraySetValue_Impl, public CNavTokens    
{
public:
	CArraySeries(long iLeft,long iRight,vector<CToken*>& vExpLine, ostream& osErrReport=cerr);
	virtual ~CArraySeries();

//	virtual bool assignsValues() const{ return true; } // can give values - change to true in time


	static bool check(long iLeft,long iRight,vector<CToken*>& vExpLine, ostream& osErrReport);
	#ifndef NDEBUG
	static bool unitTests();
	#endif

//	virtual CToken* getToken();
//	virtual bool addTokenPtVec(const vector< CToken* >& rvecpt);

protected:
	virtual void out( ostream& os ) const;

//	vector<CToken*> m_vecToks;
};

#endif // !defined(AFX_ARRAYSERIES_H__FA447418_3CF9_4BD4_A5B5_A646BA22E5C5__INCLUDED_)
