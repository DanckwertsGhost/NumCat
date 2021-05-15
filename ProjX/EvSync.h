// EvSync.h: interface for the CEvSync class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVSYNC_H__82A634B5_BE22_483D_AFC3_A87604EC3DFC__INCLUDED_)
#define AFX_EVSYNC_H__82A634B5_BE22_483D_AFC3_A87604EC3DFC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Event.h"

class CEvSync : public CEventImpl  
{
public:
	CEvSync(long iLeft, long iRight, vector<CToken*>& vecCT, ostream& oserr = cerr);
	virtual ~CEvSync();
// start from CEventImpl
//	virtual CToken* canChange(){ return m_pctLHS; }
	virtual bool willTriggerOverTime( const variable& vValue, const variable& vValueStep, const string& sTrig = g_Time);
	virtual eEventSignal trigger( vector< variable >* pvecVars, vector< variable >* /*pvecVarsLast*/ );
	virtual bool willTrigger( vector< variable >* pvecVars );
	virtual bool isOfType(eEventType eet) const{ return eet==ceetNoValueChange;}
	virtual bool setupEvent(list<CEquation*>* /*pvecpEquations*/){ return true; }
//	virtual bool prepareForSimulation( vector< variable >* /*pvecVars*/, ostream& /*oserr*/  );
//	virtual void setStrongType(const vector<varStrongType>& vecst){}
	virtual bool isActive(){ return false; }

	static bool check(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport );
//	virtual bool affectsStartTime(){ return false; }
//	virtual variable giveStartTime();
	virtual void reset();
//	virtual bool hasAPeriodUpperLimit(){return true;};
//	virtual variable getPeriodUpperLimit(){return m_maxTime;};
	virtual bool hasAPreciseTimeTrigger(const long iTime);
	virtual variable getTimeTillTrigger(const variable& vCurrentTime);
// end from CEventImpl

protected:

	variable getLastTriggerPoint( const variable& vTime);
	variable& getNextTriggerPoint( const variable& vTime);

	variable m_tstep;
	variable m_tSync; // point at which the sync should start
	variable m_tNext; // maybe use this for next point
	long m_iIndTime;
};

#endif // !defined(AFX_EVSYNC_H__82A634B5_BE22_483D_AFC3_A87604EC3DFC__INCLUDED_)
