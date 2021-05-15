// SolVarStep.cpp: implementation of the CSolVarStep class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SolVarStep.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSolVarStep::CSolVarStep(const char* sType):CSolver(),m_iSize(NOT_DEFINED),m_tstep(DEFAULT_TIME_STEP),m_xtOverRide(DEFAULT_TIME_STEP),m_bOverRideNext(false) // by default
{
	m_bState=true; // as defining with default values
}

CSolVarStep::CSolVarStep(const char* sType, long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport/*=cerr*/ ):CSolver(),m_iSize(NOT_DEFINED),m_tstep(DEFAULT_TIME_STEP),m_xtOverRide(DEFAULT_TIME_STEP),m_bOverRideNext(false) // by default
{
	m_bState = check(iLeft,iRight,vExpLine,osErrReport);

	if (this->isFormedOK()) // then check for time step info
		{
		long iEnd = getPosRightWithoutComments(iLeft,iRight,vExpLine);
		if ((iEnd-iLeft)==3) // then information to override default time step exists
				m_tstep = vExpLine[iLeft+2]->getNumber();
		ASSERT2(m_tstep!=NOT_FOUND); // check should have prevented this
		}


}

CSolVarStep::~CSolVarStep()
{

}
