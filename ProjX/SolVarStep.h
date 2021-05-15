// SolVarStep.h: interface for the CSolVarStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOLVARSTEP_H__732669B8_2F77_4C77_9771_6309DA9F5423__INCLUDED_)
#define AFX_SOLVARSTEP_H__732669B8_2F77_4C77_9771_6309DA9F5423__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Solver.h"
#include "Token.h"
#include "Equation.h"

class CSolVarStep : public CSolver, CNavTokens  
{
public:
	CSolVarStep(const char* sType);
	CSolVarStep(const char* sType, long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport );
	virtual ~CSolVarStep();

// start CSolver interface
// end CSolver interface
	static bool check(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport=cerr ){ return false; /*TBI*/ }

protected:
	xt_value m_tstep;
	vectorValues m_2step;
	vectorValues m_1step;
	vectorValues m_startpos;
	long m_iSize;
	bool m_bOverRideNext;
	xt_value m_xtOverRide;

};

#endif // !defined(AFX_SOLVARSTEP_H__732669B8_2F77_4C77_9771_6309DA9F5423__INCLUDED_)
