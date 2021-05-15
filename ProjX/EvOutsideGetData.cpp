// EvOutsideGetData.cpp: implementation of the CEvOutsideGetData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EvOutsideGetData.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEvOutsideGetData::CEvOutsideGetData():CEventImpl(),m_bHasUpdate(false)
{
	InitializeCriticalSection(&m_csDataUpdate);
	m_eState = cevUninitiated;
}

CEvOutsideGetData::~CEvOutsideGetData()
{
	CCritCheck cc(m_csDataUpdate); // probably not needed
}



///////////////////////////////////////////////////////////
// Function name	: CEvOutsideGetData::setupEvent
// Description	    : For this event just checks isReady()
// Return type		: bool 
// Argument         : list<CEquation*>* pvecpEquations
///////////////////////////////////////////////////////////
bool CEvOutsideGetData::setupEvent(list<CEquation*>* pvecpEquations)
{
	return (m_eState!=cevError);
}


///////////////////////////////////////////////////////////
// Function name	: CEvOutsideGetData::reset
// Description	    : 
// Return type		: void 
///////////////////////////////////////////////////////////
void CEvOutsideGetData::reset()
{
	CCritCheck cc(m_csDataUpdate);
	m_bHasUpdate=false;
	m_vecLastValues.clear();

}


///////////////////////////////////////////////////////////
// Function name	: CEvOutsideGetData::trigger
// Description	    : 
// Return type		: eEventSignal 
// Argument         :  vector< variable >* pvecVars
// Argument         : vector< variable >* pvecVarsLast /*= NULL*/
///////////////////////////////////////////////////////////
eEventSignal CEvOutsideGetData::trigger( vector< variable >* pvecVars, vector< variable >* pvecVarsLast /*= NULL*/  )
{
	CCritCheck cc(m_csDataUpdate);
	if (!willTrigger(pvecVars))
			return 	ceesNoTrig;


	if (pvecVars->size()!=m_vecLastValues.size()) // should only ever happen once
			m_vecLastValues.resize(pvecVars->size());
	
	m_vecLastValues = (*pvecVars);

	m_bHasUpdate=false;
	
	return ceesTrig;
}


///////////////////////////////////////////////////////////
// Function name	: CEvOutsideGetData::simulationEnd
// Description	    : 
// Return type		: void 
// Argument         : vector< variable >& rvecVars
///////////////////////////////////////////////////////////
void CEvOutsideGetData::simulationEnd(vector< variable >& rvecVars)
{

	CCritCheck cc(m_csDataUpdate);
	
	m_vecLastValues = rvecVars;


}


///////////////////////////////////////////////////////////
// Function name	: CEvOutsideGetData::getValues
// Description	    : 
// Return type		: void 
// Argument         : vector< variable >& rvSnapValues
///////////////////////////////////////////////////////////
void CEvOutsideGetData::getValues(vector< variable >& rvSnapValues)
{
	CCritCheck cc(m_csDataUpdate);
	
	rvSnapValues = m_vecLastValues;
}

