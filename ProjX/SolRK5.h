// SolRK5.h: interface for the CSolRK5 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOLRK5_H__CB0D4D09_0DF7_4340_ADD6_D512060A921C__INCLUDED_)
#define AFX_SOLRK5_H__CB0D4D09_0DF7_4340_ADD6_D512060A921C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SolRK4.h"

class CSolRK5 : public CSolRK4  
{
public:
	CSolRK5();
	CSolRK5(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport );
	virtual ~CSolRK5();
// start CSolver interface
	virtual bool setup(CIModelSim* pims);
	virtual xt_value step(vectorValues* pvecValues, vectorConstrainedValues* pvecConST);
// end CSolver interface
	static bool check(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport=cerr );

protected:

// ====== from CSolRK4 =========
//	xt_value m_tstep;
//	vectorValues m_k1;
//	vectorValues m_k2;
//	vectorValues m_k3;
//	vectorValues m_k4;
//	vectorValues m_startpos;
//	long m_iSize;
//	bool m_bOverRideNext;
//	xt_value m_xtOverRide;
// end ======== from CSolRK4 =========
	vectorValues m_k5;
	vectorValues m_k6;
	xt_value m_xtSeventh;
};

#endif // !defined(AFX_SOLRK5_H__CB0D4D09_0DF7_4340_ADD6_D512060A921C__INCLUDED_)
