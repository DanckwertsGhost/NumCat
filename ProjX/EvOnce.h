// EvOnce.h: interface for the CEvOnce class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVONCE_H__D9108A95_EF62_4833_8E10_FC65D0FA4724__INCLUDED_)
#define AFX_EVONCE_H__D9108A95_EF62_4833_8E10_FC65D0FA4724__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Event.h"

class CEvOnce : public CEventImpl  
{
public:
	CEvOnce();
	virtual ~CEvOnce();

// CEventImpl
	virtual bool willTriggerOverTime( const variable& /*vValue*/, const variable& /*vValueStep*/, const string& /*sTrig*/ = g_Time){ return false; }
	virtual bool willTriggerAtTime( const variable& vValue, const string& sTrig = g_Time){ return false; }
	virtual eEventSignal trigger( vector< variable >* pvecVars, vector< variable >* pvecVarsLast ){ return ceesEndSimulation; }
	virtual bool willTrigger( vector< variable >* pvecVars ){ return true; }
//	virtual CToken* canChange(){ return m_pLHS; }
	virtual bool setupEvent(list<CEquation*>* pvecpEquations){ return true; }
//   STANDARD IMPLEMENTATIONS below
//	virtual void endOfSimulation( vector< variable >* /*pvecVars*/, vector< variable >* /*pvecVarsLast*/ ){ return; }
	virtual bool isActive(){ return true; }
	virtual bool isInError() const{	return false;} // as its very simple
//	virtual const string getLastErrorMessage() const{ return m_sError;}
//	virtual bool isReady() const{ return m_eState==cevInitiated;}
//	virtual bool isCorrect() const{	return m_eState!=cevError;}
//	virtual bool isOfType(eEventType eet) const{ return eet==ceetValueChange;}
//	virtual bool prepareForSimulation( vector< variable >* /*pvecVars*/, ostream& /*oserr*/ );
//	virtual eEventType giveEventType() const{ return ceetValueChange; }
//	virtual bool affectsStartTime(){return false;}
//	virtual variable giveStartTime(){return (variable)NOT_DEFINED;}
//	virtual void reset();
//	virtual void setStrongType(const vector<varStrongType>& vecst);
//	virtual void setFlag(const bool bFlag){}; // only for certain events
//	virtual bool hasAPreciseTimeTrigger(const long);
//	virtual variable getTimeTillTrigger(const variable& vCurrentTime){ 	return (getNextTriggerPoint( vCurrentTime) - vCurrentTime);}
//	virtual bool hasAPeriodUpperLimit(){return true;};
//	virtual variable getPeriodUpperLimit(){return CEI_MAX_STEP;};
//	virtual void simulationEnd(vector< variable >& rvecVars){}; // so can tell things over
//	virtual void finalRelease(){}; // tidy up any COM dependent stuff as COM service is closing before object destroyed
//	virtual bool fixedAtStart() const{return true;} // default value - if event trigger needs to be evaluated in light of all other simulation values should return false
// end CEvent interface	
	

// end CEventImpl

//	static bool check( long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport=cerr );

};

#endif // !defined(AFX_EVONCE_H__D9108A95_EF62_4833_8E10_FC65D0FA4724__INCLUDED_)
