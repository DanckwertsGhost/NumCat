// EvRealTime.h: interface for the CEvRealTime class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVREALTIME_H__298D652D_EAAD_4B60_B84E_963F59C1A248__INCLUDED_)
#define AFX_EVREALTIME_H__298D652D_EAAD_4B60_B84E_963F59C1A248__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Event.h"
#include <time.h>
#include <sys/timeb.h>

class CEvRealTime : public CEventImpl  
{
public:
	CEvRealTime(long iLeft, long iRight, vector<CToken*>& vecCT, ostream& oserr = cerr);
	virtual ~CEvRealTime();

// start from CEventImpl
//	virtual CToken* canChange(){ return m_pctLHS; }
//	virtual bool willTriggerOverTime( const variable& /*vValue*/, const variable& /*vValueStep*/, const string& /*sTrig*/ = g_Time){ return false; } // as is never looked at beyond start
	virtual eEventSignal trigger( vector< variable >* pvecVars, vector< variable >* /*pvecVarsLast*/ );
	virtual bool willTrigger( vector< variable >* /*pvecVars*/ ){ return false; }
	virtual bool isOfType(eEventType eet) const{ return eet==ceetNoValueChange;}
	virtual bool setupEvent(list<CEquation*>* /*pvecpEquations*/){ return true; }
	virtual bool isActive(){ return false; }
//	virtual bool prepareForSimulation( vector< variable >* /*pvecVars*/, ostream& /*oserr*/  );
//	virtual void setStrongType(const vector<varStrongType>& vecst){}
//	virtual bool affectsStartTime(){ return false; }
//	virtual variable giveStartTime();
	virtual void reset();
//	virtual bool hasAPeriodUpperLimit(){return true;};
//	virtual variable getPeriodUpperLimit(){return m_maxTime;};
	virtual bool hasAPreciseTimeTrigger(const long iTime);

// end from CEventImpl

	static bool check(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport );

protected:
	bool m_bHasNotStarted;
	_timeb m_timebOne; // use _ftime function to get
	_timeb m_timebTwo;
	_timeb m_timebStart;
	_timeb* m_ptimebLast;
	_timeb* m_ptimebNow;
	_timeb* m_ptimebTemp;

	long m_millitm; // rather than unsigned short as may have to hold negatives
	time_t m_timetDSecs;
	variable m_vSimTimeLast;
	long m_iIndTime;
	variable m_vTimeStep;
	variable m_vTimeScale;

};

#endif // !defined(AFX_EVREALTIME_H__298D652D_EAAD_4B60_B84E_963F59C1A248__INCLUDED_)
