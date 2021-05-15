// SolRK3.cpp: implementation of the CSolRK3 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SolRK3.h"
#include "Symlix/ErrorFactory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSolRK3::CSolRK3():CSolRK4()
{

}

CSolRK3::CSolRK3(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport ):CSolRK4(iLeft,iRight,vExpLine,osErrReport)
{

}

CSolRK3::~CSolRK3()
{

}

///////////////////////////////////////////////////////////
// Function name	: CSolRK3::setup
// Description	    : prepare solver
// Return type		: bool 
// Argument         : CIModelSim* pims
///////////////////////////////////////////////////////////
bool CSolRK3::setup(CIModelSim* pims)
{
	bool bResult =CSolRK4::setup(pims);
/*
	see CSolRK4::setup

*/

	return bResult;
}

///////////////////////////////////////////////////////////
// Function name	: CSolRK3::step
// Description	    : Make a step forward - assumes intialised
//                    Debug code has asserts to catch this - but not release
//                    See Numerical Methods for Engineers 2nd Ed p 604
//                    This method known as Butcher method
// Return type		: xt_value 
// Argument         : vectorValues* pvecValues
// Argument         : vectorConstrainedValues* pvecConST
///////////////////////////////////////////////////////////
xt_value CSolRK3::step(vectorValues* pvecValues, vectorConstrainedValues* pvecConST )
{
	long iT;
	xt_value xtTemp;
//	xt_value xtSeventh = 1.0L/7.0L; - moved to contructor

#ifndef NDEBUG // clearly don't want to do this in release solve mode
	assert(m_iSize!=NOT_DEFINED);
	assert(m_pIModelSim);
	assert(m_pIModelSim->isReady());
#endif

	if (m_bOverRideNext) // in case need to predict to a precise point - has more meaning for variable steps
		{
		xtTemp = m_tstep;
		m_tstep = m_xtOverRide;
		}

	// back up start position for variables
	copy(&(*pvecValues)[m_iVarStart],&(*pvecValues)[m_iVarEnd],m_startpos.begin());
	
	// find k1 values
	m_pIModelSim->updateValue(pvecValues);
	copy(&(*pvecValues)[m_iDerivStart],&(*pvecValues)[m_iDerivEnd],m_k1.begin());

	// find k2 values
	for(iT=0;iT<m_iSize;iT++)
		(*pvecValues)[m_iVarStart+iT] += 0.5L*m_tstep*m_k1[iT];
	(*pvecValues)[m_iIndVar] += 0.5L*m_tstep;
	m_pIModelSim->updateValue(pvecValues);
	copy(&(*pvecValues)[m_iDerivStart],&(*pvecValues)[m_iDerivEnd],m_k2.begin());

	// find k3 values
	for(iT=0;iT<m_iSize;iT++)
		(*pvecValues)[m_iVarStart+iT] = m_startpos[iT] - m_tstep*m_k1[iT] + 2.0L*m_tstep*m_k2[iT];
	// No time step forward for this k value
	m_pIModelSim->updateValue(pvecValues);
	copy(&(*pvecValues)[m_iDerivStart],&(*pvecValues)[m_iDerivEnd],m_k3.begin());

/*	// find k4 values
	for(iT=0;iT<m_iSize;iT++)
		(*pvecValues)[m_iVarStart+iT] = m_startpos[iT] - 0.5L*m_tstep*m_k2[iT] + m_tstep*m_k3[iT];
	(*pvecValues)[m_iIndVar] += 0.25L*m_tstep; // to bring it up to tstep forward
	m_pIModelSim->updateValue(pvecValues);
	copy(&(*pvecValues)[m_iDerivStart],&(*pvecValues)[m_iDerivEnd],m_k4.begin());

	// find k5 values
	for(iT=0;iT<m_iSize;iT++)
		(*pvecValues)[m_iVarStart+iT] = m_startpos[iT] + 0.1875L*m_tstep*m_k1[iT] + 0.5625L*m_tstep*m_k4[iT];
	(*pvecValues)[m_iIndVar] += 0.25L*m_tstep; // to bring it up to tstep forward
	m_pIModelSim->updateValue(pvecValues);
	copy(&(*pvecValues)[m_iDerivStart],&(*pvecValues)[m_iDerivEnd],m_k5.begin());

	// find k6 values
	for(iT=0;iT<m_iSize;iT++)
		(*pvecValues)[m_iVarStart+iT] = m_startpos[iT] 
		- 3.0L*m_xtSeventh*m_tstep*m_k1[iT]
		+ 2.0L*m_xtSeventh*m_tstep*m_k2[iT]
		+ 12.0L*m_xtSeventh*m_tstep*m_k3[iT]
		- 12.0L*m_xtSeventh*m_tstep*m_k4[iT]
		+ 8.0L*m_xtSeventh*m_tstep*m_k5[iT]; // this can be improved by taking m_tstep outside also may consider
											// m_xtSeventh as a define - to prevent need for reference to memory
		

	(*pvecValues)[m_iIndVar] += 0.25*m_tstep; // to bring it up to tstep forward
	m_pIModelSim->updateValue(pvecValues);
	copy(&(*pvecValues)[m_iDerivStart],&(*pvecValues)[m_iDerivEnd],m_k6.begin());
*/

    // Now assign those values

	for(iT=0;iT<m_iSize;iT++)
		(*pvecValues)[m_iVarStart+iT] = (*pvecConST)[m_iVarStart+iT] = 
		m_startpos[iT]+((1.0L/6.0L)*(m_k1[iT]+4.0L*m_k2[iT]+m_k3[iT]))*m_tstep;

	if (m_bOverRideNext)
		{
		m_tstep = xtTemp;
		m_bOverRideNext = false;
		}

	return (*pvecValues)[m_iIndVar];
}

///////////////////////////////////////////////////////////
// Function name	: CSolRK3::check
// Description	    : Assumes check run on line one token beyond solver keyword
// Return type		: bool 
// Argument         : long iLeft
// Argument         : long iRight
// Argument         : vector<CToken*>& vExpLine
// Argument         : ostream& osErrReport
///////////////////////////////////////////////////////////
bool CSolRK3::check(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport )
{

	long iEnd = CNavTokens::getPosRightWithoutComments(iLeft,iRight,vExpLine);
	
	if (iLeft!=iEnd-1) // then format for solver statement is wrong
		{
		if ((iEnd-iLeft)>3)
				{
				osErrReport << "<Error*> RK5 solver defintion has an error - try reducing the number of statements.\n";
				SYMERRORTOK("RK5 solver defintion has an error - try reducing the number of statements",errSyntax,vExpLine[iLeft]);
				return false;
				}
		if ((iEnd-iLeft)<3)
				{
				osErrReport << "<Error*> RK5 solver defintion has an error - the expression is missing term(s).\n";
				SYMERRORTOK("RK5 solver defintion has an error - the expression is missing term(s)",errSyntax,vExpLine[0]);
				return false;
				}

		if ((!vExpLine[iLeft+1]->IsOfType(ctSolverKeyWord))&&(vExpLine[iLeft+1]->getString().compare(g_Step)!=0))
				{
				osErrReport << "<Error*> RK5 solver defintion needs a '"<<g_Step <<"' statement.\n";
				SYMERRORTOK2("RK5 solver defintion: missing ",g_Step,errSyntax,vExpLine[iLeft+1]);
				return false;
				}

		if ((!vExpLine[iLeft+2]->IsOfType(ctNumber))&&(vExpLine[iLeft+2]->getNumber()<=0))
				{
				osErrReport << "<Error*> RK5 solver step needs to be greater than zero .\n";
				SYMERRORTOK("RK5 solver step needs to be greater than zero",errSyntax,vExpLine[iLeft+2]);
				return false;
				}

		}

/* Don't believe this is necessary as has already been identified in class factory
	if (vExpLine[iLeft]->getString().compare(g_RK5)==0)
		return true;

	return false;*/
	return true;
}