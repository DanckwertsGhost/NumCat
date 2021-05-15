// SolRK3VS.h: interface for the CSolRK3VS class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOLRK3VS_H__021F8FE6_7D0E_4E70_A68A_25196D43FFF0__INCLUDED_)
#define AFX_SOLRK3VS_H__021F8FE6_7D0E_4E70_A68A_25196D43FFF0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SolRK4VS.h"
#include "SolRK3.h"

class CSolRK3VS : public CSolVS<CSolRK3VS,CSolRK3>
{
public:
	CSolRK3VS():CSolVS<CSolRK3VS,CSolRK3>(){}
	CSolRK3VS(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport ):CSolVS<CSolRK3VS,CSolRK3>(iLeft,iRight,vExpLine,osErrReport){}
	virtual ~CSolRK3VS(){}
	static bool check(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport=cerr );

};

#endif // !defined(AFX_SOLRK3VS_H__021F8FE6_7D0E_4E70_A68A_25196D43FFF0__INCLUDED_)
