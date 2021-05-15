// SolRK4.cpp: implementation of the CSolRK4 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Solver.h"
#include "IModelSim.h"
#include "global.h"
#ifndef NDEBUG
#include "assert.h"
#endif


///////////////////////////////////////////////////////////
// Function name	: CSolver::setIndVarStep
// Description	    : set time step
// Return type		: void 
// Argument         : xt_value ivStep
///////////////////////////////////////////////////////////
void CSolver::setIndVarStep(xt_value ivStep)
{
	(ivStep<m_tmax? m_tstep=ivStep: m_tstep=m_tmax);
}


///////////////////////////////////////////////////////////
// Function name	: CSolver::setMaxStep
// Description	    : 
// Return type		: void 
// Argument         : xt_value xt_max
///////////////////////////////////////////////////////////
void CSolver::setMaxStep(xt_value xt_max)
{
	m_tmax = xt_max;
	if (m_tstep>xt_max)
			m_tstep = xt_max;
}