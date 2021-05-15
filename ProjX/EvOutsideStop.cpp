// EvOutsideStop.cpp: implementation of the CEvOutsideStop class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EvOutsideStop.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEvOutsideStop::CEvOutsideStop():m_bKillNext(false)
{
	m_eState = cevUninitiated;
}

CEvOutsideStop::~CEvOutsideStop()
{

}

eEventSignal CEvOutsideStop::trigger( vector< variable >* pvecVars, vector< variable >* pvecVarsLast )
{
	if (willTrigger(pvecVars))
		return ceesEndSimulation;

	return ceesNoTrig;
}

