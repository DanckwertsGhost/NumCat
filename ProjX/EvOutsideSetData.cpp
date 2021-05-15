// EvOutsideSetData.cpp: implementation of the CEvOutsideSetData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EvOutsideSetData.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEvOutsideSetData::CEvOutsideSetData():CEventImpl(),m_bHasUpdate(false)
{
	InitializeCriticalSection(&m_csDataUpdate);
	m_eState = cevUninitiated;
}

CEvOutsideSetData::~CEvOutsideSetData()
{
	CCritCheck cc(m_csDataUpdate); // probably not needed
}



///////////////////////////////////////////////////////////
// Function name	: CEvOutsideSetData::setStrongType
// Description	    : Make a local copy of strong types
//                    - why local copy ? As gets around
//                    thread access issues as well as 
//                    life cycle issue.
// Return type		: void 
// Argument         : const vector<varStrongType>& vecst
///////////////////////////////////////////////////////////
void CEvOutsideSetData::setStrongType(const vector<varStrongType>& vecst)
{

	m_vecStrongTypes = vecst; // make a copy
	if (m_eState!=cevError)
		m_eState = cevInitiated;
}


///////////////////////////////////////////////////////////
// Function name	: CEvOutsideSetData::setupEvent
// Description	    : For this event just checks isReady()
// Return type		: bool 
// Argument         : list<CEquation*>* pvecpEquations
///////////////////////////////////////////////////////////
bool CEvOutsideSetData::setupEvent(list<CEquation*>* pvecpEquations)
{
	return (m_eState!=cevError);
}


///////////////////////////////////////////////////////////
// Function name	: CEvOutsideSetData::reset
// Description	    : 
// Return type		: void 
///////////////////////////////////////////////////////////
void CEvOutsideSetData::reset()
{
	CCritCheck cc(m_csDataUpdate);
	m_bHasUpdate=false;
	m_vecChanges.clear();

}


///////////////////////////////////////////////////////////
// Function name	: CEvOutsideSetData::trigger
// Description	    : 
// Return type		: eEventSignal 
// Argument         :  vector< variable >* pvecVars
// Argument         : vector< variable >* pvecVarsLast /*= NULL*/
///////////////////////////////////////////////////////////
eEventSignal CEvOutsideSetData::trigger( vector< variable >* pvecVars, vector< variable >* pvecVarsLast /*= NULL*/  )
{
	CCritCheck cc(m_csDataUpdate);
	if (!willTrigger(pvecVars))
			return 	ceesNoTrig;

	ASSERT2(m_vecChanges.size()>0); // as willTrigger should return false if not.

	vector< pair< long, variable > >::iterator it;

	for(it=m_vecChanges.begin();it!=m_vecChanges.end();it++)
		{
		//make it easier to catch fundemental problems
		ASSERT2((*it).first<pvecVars->size());
		ASSERT2((*it).first<m_vecStrongTypes.size());

		(*pvecVars)[(*it).first] = m_vecStrongTypes[(*it).first] = (*it).second;

		}
	// get ready for next inputs
	m_vecChanges.clear();
	m_bHasUpdate=false;
	
	return ceesTrig;
}



///////////////////////////////////////////////////////////
// Function name	: CEvOutsideSetData::changeValue
// Description	    : change a vlaue from outside
//                    designed to be called from another
//                    thread than the solver.
//                    (Protected by critical section)
// Return type		: void 
// Argument         : long iIndex
// Argument         : variable vValue
///////////////////////////////////////////////////////////
void CEvOutsideSetData::changeValue(long iIndex, variable vValue )
{
	pair<long,variable> prV;

	CCritCheck cc(m_csDataUpdate);

	prV.first = iIndex;
	prV.second = vValue;
	m_vecChanges.push_back(prV);
	m_bHasUpdate=true;
}

