// EvPace.h: interface for the CEvPace class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVPACE_H__10BA4C1F_106F_4F88_AFB7_C0236930E7C3__INCLUDED_)
#define AFX_EVPACE_H__10BA4C1F_106F_4F88_AFB7_C0236930E7C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Event.h"

class CEvPace : public CEventImpl  
{
public:
	CEvPace(long iLeft, long iRight, vector<CToken*>& vecCT, ostream& oserr = cerr);
	virtual ~CEvPace();
// start from CEventImpl
//	virtual CToken* canChange(){ return m_pctLHS; }
	virtual bool willTriggerOverTime( const variable& /*vValue*/, const variable& /*vValueStep*/, const string& /*sTrig*/ = g_Time){ return false; } // as is never looked at beyond start
	virtual eEventSignal trigger( vector< variable >* pvecVars, vector< variable >* /*pvecVarsLast*/ ){ return ceesNoTrig;}
	virtual bool willTrigger( vector< variable >* /*pvecVars*/ ){ return false; }
	virtual bool isOfType(eEventType eet) const{ return eet==ceetNoValueChange;}
	virtual bool setupEvent(list<CEquation*>* /*pvecpEquations*/){ return true; }
	virtual bool prepareForSimulation( vector< variable >* /*pvecVars*/, ostream& /*oserr*/  );
	virtual bool isActive(){ return false; }
//	virtual void setStrongType(const vector<varStrongType>& vecst){}

	static bool check(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport );
//	virtual bool affectsStartTime(){ return false; }
//	virtual variable giveStartTime();
//	virtual void reset(){};
	virtual bool hasAPeriodUpperLimit(){return true;};
	virtual variable getPeriodUpperLimit(){return m_maxTime;};
// end from CEventImpl

protected:
	variable m_maxTime;
};

#endif // !defined(AFX_EVPACE_H__10BA4C1F_106F_4F88_AFB7_C0236930E7C3__INCLUDED_)
