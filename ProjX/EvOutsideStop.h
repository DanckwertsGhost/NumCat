// EvOutsideStop.h: interface for the CEvOutsideStop class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVOUTSIDESTOP_H__B7AC7937_E89F_4466_9B41_07EE460F5921__INCLUDED_)
#define AFX_EVOUTSIDESTOP_H__B7AC7937_E89F_4466_9B41_07EE460F5921__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Event.h"

class CEvOutsideStop : public CEventImpl  
{
public:
	CEvOutsideStop();
	virtual ~CEvOutsideStop();
	virtual bool isOfType(eEventType eet) const{ return eet==ceesStartSimulation;}
	virtual bool setupEvent(list<CEquation*>* pvecpEquations){ m_eState=cevInitiated; return true;} 


	virtual bool willTriggerOverTime( const variable& vValue, const variable& vValueStep, const string& sTrig = g_Time){ return false;}
	virtual eEventSignal trigger( vector< variable >* pvecVars, vector< variable >* pvecVarsLast );
	virtual bool willTrigger( vector< variable >* pvecVars ){ return m_bKillNext; }
	virtual bool isActive(){ return false; }
/*	virtual bool isActive()=0; 
	virtual bool isInError() const=0;
	virtual bool isReady() const=0;
	virtual bool isCorrect() const=0;
	virtual bool isOfType(eEventType ) const=0;
	virtual bool prepareForSimulation( vector< variable >* pvecVars, ostream& oserr ) =0;
	virtual eEventType giveEventType() const=0;
	virtual CToken* canChange()=0;
	virtual bool setupEvent(list<CEquation>* pvecEquations)=0;
*/
	virtual void setFlag(const bool bFlag){m_bKillNext=bFlag;}
//	static bool check(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport );

protected:
	bool m_bKillNext; // will be changed by external function to stop simulation
};

#endif // !defined(AFX_EVOUTSIDESTOP_H__B7AC7937_E89F_4466_9B41_07EE460F5921__INCLUDED_)
