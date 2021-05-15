// EvItValueStep.cpp: implementation of the CEvItValueStep class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EvItValueStep.h"

#include "Symlix/ErrorFactory.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEvItValueStep::CEvItValueStep(CToken* pctIterative):CEventImpl(),m_pctIterative(pctIterative),m_pctChange(NULL),m_iSet(NOT_DEFINED),m_iFrom(NOT_DEFINED),m_vStart(NOT_DEFINED),m_tStep(STEP_SIZE_EVITVALUESTEP),m_tNext(NOT_DEFINED),m_iIndTime(NOT_DEFINED),m_tMonitor(NOT_DEFINED),m_tNextPrecise(NOT_DEFINED)
{
	if (!m_pctIterative)
			{
			m_sError = "Unable to set up iterative event to support iterative equation.";
			m_eState = cevError;

			}
			else
			m_eState = cevUninitiated;
}

CEvItValueStep::~CEvItValueStep()
{

}


///////////////////////////////////////////////////////////
// Function name	: CEvItValueStep::willTrigger
// Description	    : 
// Return type		: bool 
// Argument         : vector< variable >* pvecVars
///////////////////////////////////////////////////////////
bool CEvItValueStep::willTrigger( vector< variable >* pvecVars )
{
#ifndef NDEBUG
	variable iV = (*pvecVars)[m_iIndTime];

#endif

	return ((*pvecVars)[m_iIndTime]>=m_tNext);
}


///////////////////////////////////////////////////////////
// Function name	: CEvItValueStep::trigger
// Description	    : 
// Return type		: eEventSignal 
// Argument         :  vector< variable >* pvecVars
// Argument         : vector< variable >* pvecVarsLast
///////////////////////////////////////////////////////////
eEventSignal CEvItValueStep::trigger( vector< variable >* pvecVars, vector< variable >* pvecVarsLast )
{

 ASSERT2((m_iSet!=NOT_DEFINED)&&(m_iFrom!=NOT_DEFINED)&&(m_iIndTime!=NOT_DEFINED));

 if (willTrigger(pvecVars))
		{ 
//		 ATLTRACE("Before t %f, x' %f, x %f\t",(*pvecVars)[m_iIndTime],(*pvecVars)[m_iFrom],(*pvecVars)[m_iSet]);
		 (*pvecVars)[m_iSet] = m_stChange = (*pvecVars)[m_iFrom];
		 m_tMonitor = (*pvecVars)[m_iIndTime];
		 m_tNext += m_tStep;
		 m_tNextPrecise += m_tStep;
//		 ATLTRACE("After t %f, x' %f, x %f\n",(*pvecVars)[m_iIndTime],(*pvecVars)[m_iFrom],(*pvecVars)[m_iSet]);
		 return ceesTrig;
		}

 return ceesNoTrig; // since only change in values noted in next calculation round - this shoudl be called last in the events (after record eevents etc )
}

bool CEvItValueStep::willTriggerOverTime( const variable& vValue, const variable& vValueStep, const string& sTrig  )
{
 
 if (sTrig.compare(g_Time)!=0)
				return false; // then this doesn't apply.

 return (vValue+vValueStep)>=m_tNext; // no need for fabs as this is always time going forwards

}

bool CEvItValueStep::setupEvent(list<CEquation*>* /*pvecpEquations*/)
{
	
	if (m_eState==cevError)
			return false;

	ASSERT2(m_pctIterative);

	if (!m_pctIterative)
			{
			m_eState = cevError;
			m_sError = "Internal variable in event not defined";
			SYMERRORLITE(m_sError.c_str(),errInternal);
			return false;
			}

	m_iFrom = m_pctIterative->getIndex();

	if (!m_pctChange)
			return true; // just nothing to change

	m_iSet = m_pctChange->getIndex();

	return true;
}


///////////////////////////////////////////////////////////
// Function name	: CEvItValueStep::findRHSvalue
// Description	    : This is a CEvItValueStep and its derivatives function
//                    it sets up a reference to the variable to be changed.
// Return type		: bool  - false if there is no variable to change
// Argument         : SetPtCTokenStringSearch& setToksDef
///////////////////////////////////////////////////////////
bool CEvItValueStep::findRHSvalue( SetPtCTokenStringSearch& setToksDef ) // note not defined in Event !
{
	SetPtCTokenStringSearch::const_iterator cit;
	CToken tokTest;
	tokTest.setString(m_pctIterative->getString().getLessIterative());

	ASSERT2(m_pctIterative->getString().isIterative()); // should never have got this far

	cit = setToksDef.find(&tokTest);

	if ((m_eState!= cevError )&&(m_iIndTime!=NOT_DEFINED)&&(m_iFrom!=NOT_DEFINED)) // don't want to set an error state as OK by mistake
			m_eState = cevInitiated;

	if (cit==setToksDef.end())
		return false;

	m_pctChange = *cit; // set the pointer

	return true;
}

void CEvItValueStep::setStrongType(const vector<varStrongType>& vecst)
{

	ASSERT2(m_eState==cevInitiated);
	if (m_eState!=cevInitiated)
			return;
	
	if ((m_iSet>=0)&&(m_iSet<=vecst.size()))
		m_stChange = vecst[m_iSet];

}

///////////////////////////////////////////////////////////
// Function name	: CEvItValueStep::getTimeTillTrigger
// Description	    : 
// Return type		: variable 
// Argument         : const variable& vCurrentTime
///////////////////////////////////////////////////////////
variable CEvItValueStep::getTimeTillTrigger(const variable& vCurrentTime)
{
#ifdef EXTRADEBUG

	variable tgap = getNextTriggerPoint( vCurrentTime) - vCurrentTime;

#endif


	return (getNextTriggerPoint( vCurrentTime) - vCurrentTime);

}



///////////////////////////////////////////////////////////
// Function name	: CEvItValueStep::getLastTriggerPoint
// Description	    : 
// Return type		: variable 
// Argument         : const variable& vTime
///////////////////////////////////////////////////////////
variable CEvItValueStep::getLastTriggerPoint( const variable& vTime)
{
	return (getNextTriggerPoint(vTime) - m_tStep);

}


///////////////////////////////////////////////////////////
// Function name	: CEvItValueStep::getNextTriggerPoint
// Description	    : 
// Return type		: variable& 
// Argument         : const variable& vTime
///////////////////////////////////////////////////////////
variable& CEvItValueStep::getNextTriggerPoint( const variable& vTime)
{

//	while(m_tNext<=vTime)
//		m_tNext += m_tstep;
	return m_tNextPrecise;

}


///////////////////////////////////////////////////////////
// Function name	: CEvItValueStep::prepareForSimulation
// Description	    : 
// Return type		: bool 
// Argument         :  vector< variable >* pvecVars
// Argument         : ostream& oserr
///////////////////////////////////////////////////////////
bool CEvItValueStep::prepareForSimulation( vector< variable >* pvecVars, ostream& oserr )
{
 m_bStart=true;

 ASSERT2(m_iIndTime!=NOT_DEFINED);
 
 m_tNextPrecise = (*pvecVars)[m_iIndTime] + m_tStep; 
 m_tNext = m_tNextPrecise - DEFAULT_SMALL_NUMBER; // not m_tMontor doesn't have this
 
 if ((m_eState!=cevError)&&(m_iFrom!=NOT_DEFINED))
		m_eState = cevInitiated;
 
 return true; 
}


///////////////////////////////////////////////////////////
// Function name	: CEvItValueStep::hasAPreciseTimeTrigger
// Description	    : 
// Return type		: bool 
// Argument         : const long iTime
///////////////////////////////////////////////////////////
bool CEvItValueStep::hasAPreciseTimeTrigger(const long iTime)
{
	ASSERT2(iTime>=0);

	m_iIndTime = iTime;

	return true;
}

//SOME OF THE WRONG VARIABLE NAME ARE ABOVE... WILL ALSO NEED TO TRACE THROUGH THE BEHVIOUR OF THIS EVENT CAREFULLY.