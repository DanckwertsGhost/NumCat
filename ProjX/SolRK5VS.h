// SolRK5VS.h: interface for the CSolRK5VS class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOLRK5VS_H__E304C437_F62D_471E_A414_A2F668D56F9D__INCLUDED_)
#define AFX_SOLRK5VS_H__E304C437_F62D_471E_A414_A2F668D56F9D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SolRK4VS.h"
#include "SolRK5.h"

class CSolRK5VS : public CSolVS<CSolRK5VS,CSolRK5>
{
public:
	CSolRK5VS():CSolVS<CSolRK5VS,CSolRK5>(){}
	CSolRK5VS(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport ):CSolVS<CSolRK5VS,CSolRK5>(iLeft,iRight,vExpLine,osErrReport){}
	virtual ~CSolRK5VS(){}
	static bool check(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport=cerr );

};

#endif // !defined(AFX_SOLRK5VS_H__E304C437_F62D_471E_A414_A2F668D56F9D__INCLUDED_)
