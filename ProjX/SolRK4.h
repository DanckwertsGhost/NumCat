// SolRK4.h: interface for the CSolRK4 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOLRK4_H__3EA5EFF3_0034_4C56_AC6A_14DDA6F00F78__INCLUDED_)
#define AFX_SOLRK4_H__3EA5EFF3_0034_4C56_AC6A_14DDA6F00F78__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Solver.h"
#include "Token.h"
#include "Equation.h"
#include <fstream>
#include <vector>

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

using namespace std;
class CSolRK4 : public CSolver, public CNavTokens  
{
public:
	CSolRK4();
	CSolRK4(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport );
	virtual ~CSolRK4();
// start CSolver interface
	virtual bool setup(CIModelSim* pims);
	virtual xt_value step(vectorValues* pvecValues,vectorConstrainedValues* pvecConST );
	virtual xt_value nextIndVarStep() const; // return predicted next time jump - in case over ride needed
	virtual void overrideNextIndVarStep(xt_value xtNextOnly);
// end CSolver interface
	static bool check(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport=cerr );

protected:
	vectorValues m_k1;
	vectorValues m_k2;
	vectorValues m_k3;
	vectorValues m_k4;
	vectorValues m_startpos;
	long m_iSize;
	bool m_bOverRideNext;
	xt_value m_xtOverRide;


};

#endif // !defined(AFX_SOLRK4_H__3EA5EFF3_0034_4C56_AC6A_14DDA6F00F78__INCLUDED_)
