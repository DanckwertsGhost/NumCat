// SolRK3.h: interface for the CSolRK3 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOLRK3_H__DAAB277B_1858_462A_8EBF_C3B3D6291EFE__INCLUDED_)
#define AFX_SOLRK3_H__DAAB277B_1858_462A_8EBF_C3B3D6291EFE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SolRK4.h"

class CSolRK3 : public CSolRK4  
{
public:
	CSolRK3();
	CSolRK3(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport );
	virtual ~CSolRK3();

// start CSolver interface
	virtual bool setup(CIModelSim* pims);
	virtual xt_value step(vectorValues* pvecValues, vectorConstrainedValues* pvecConST);
// end CSolver interface
	static bool check(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport=cerr );
};

#endif // !defined(AFX_SOLRK3_H__DAAB277B_1858_462A_8EBF_C3B3D6291EFE__INCLUDED_)
