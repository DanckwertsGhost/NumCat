// SolOneStep.h: interface for the CSolOneStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOLONESTEP_H__57CF16E8_B6B9_4E0C_AB81_577BD72C114D__INCLUDED_)
#define AFX_SOLONESTEP_H__57CF16E8_B6B9_4E0C_AB81_577BD72C114D__INCLUDED_

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

// Class to step time forward 1 unit at a time
// used to support iterative modelling

class CSolOneStep : public CSolver  
{
public:
	CSolOneStep();
	virtual ~CSolOneStep();

// start CSolver interface
	virtual bool setup(CIModelSim* pims);
	virtual xt_value step(vectorValues* pvecValues,vectorConstrainedValues* pvecConST );
	virtual xt_value nextIndVarStep() const {return m_tstep;} // return predicted next time jump - in case over ride needed
	virtual void overrideNextIndVarStep(xt_value xtNextOnly){} // does nothing - can't override
// end CSolver interface
//	static bool check(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport=cerr );
protected:
	long m_iSize;


};

#endif // !defined(AFX_SOLONESTEP_H__57CF16E8_B6B9_4E0C_AB81_577BD72C114D__INCLUDED_)
