// EvItValueStep.h: interface for the CEvItValueStep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVITVALUESTEP_H__56E4B0CB_C691_4484_86CB_A551E373BAFD__INCLUDED_)
#define AFX_EVITVALUESTEP_H__56E4B0CB_C691_4484_86CB_A551E373BAFD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Event.h"

#define STEP_SIZE_EVITVALUESTEP 1.0

class CEvItValueStep : public CEventImpl  
{
public:
	CEvItValueStep(CToken* pctIterative );
	virtual ~CEvItValueStep();

	virtual bool findRHSvalue( SetPtCTokenStringSearch& setToksDef ); // note not defined in Event !

// begin CEvent interface
	virtual bool willTriggerOverTime( const variable& vValue, const variable& vValueStep, const string& sTrig = g_Time);
//	virtual bool willTriggerAtTime( const variable& vValue, const string& sTrig = g_Time){ return willTriggerOverTime((vValue-DEFAULT_SMALL_NUMBER/2.0),DEFAULT_SMALL_NUMBER,sTrig);}
	virtual eEventSignal trigger( vector< variable >* pvecVars, vector< variable >* pvecVarsLast );
	virtual bool willTrigger( vector< variable >* /*pvecVars*/ );
	virtual CToken* canChange(){ return m_pctChange; }
	virtual bool setupEvent(list<CEquation*>* /*pvecpEquations*/);

//   STANDARD IMPLEMENTATIONS below
//	virtual void endOfSimulation( vector< variable >* /*pvecVars*/, vector< variable >* /*pvecVarsLast*/ ){ return; }
	virtual bool isActive(){ return true; } // ie can this change values - or is it passive - eg a reporter ( all passive events carried out last
//	virtual bool isInError() const{	return m_eState==cevError;}
//	virtual const string getLastErrorMessage() const{ return m_sError;}
//	virtual bool isReady() const{ return m_eState==cevInitiated;}
//	virtual bool isCorrect() const{	return m_eState!=cevError;}
	virtual bool isOfType(eEventType eet) const{ return eet==ceetValueChangeAfterStart;}
	virtual bool prepareForSimulation( vector< variable >* /*pvecVars*/, ostream& /*oserr*/ );
	virtual eEventType giveEventType() const{ return ceetValueChangeAfterStart; }
//	virtual bool affectsStartTime(){return false;}
//	virtual variable giveStartTime(){return (variable)NOT_DEFINED;}
	virtual void reset(){m_bStart=true;};
	virtual void setStrongType(const vector<varStrongType>& vecst);
//	virtual void setFlag(const bool bFlag){}; // only for certain events
	virtual bool hasAPreciseTimeTrigger(const long iTime);
	virtual variable getTimeTillTrigger(const variable& vCurrentTime);
	virtual bool hasAPeriodUpperLimit(){return true;};
	virtual variable getPeriodUpperLimit(){return static_cast<variable>(STEP_SIZE_EVITVALUESTEP);}
//	virtual void simulationEnd(vector< variable >& rvecVars){}; // so can tell things over
//	virtual void finalRelease(){}; // tidy up any COM dependent stuff as COM service is closing before object destroyed
	virtual bool fixedAtStart() const{return false;} // this event does not define values at start of simulation
// end CEvent interface
protected:

	variable getLastTriggerPoint( const variable& vTime);
	variable& getNextTriggerPoint( const variable& vTime);

	variable m_vStart;
	variable m_tStep;
	variable m_tNext;
	variable m_tNextPrecise;
	long m_iFrom;
	long m_iSet;
	CToken* m_pctIterative;
	CToken* m_pctChange; // can also be NULL if no equivalent in problem
	bool m_bStart;
	varStrongType m_stChange;
	long m_iIndTime;
	variable m_tMonitor;

};

#endif // !defined(AFX_EVITVALUESTEP_H__56E4B0CB_C691_4484_86CB_A551E373BAFD__INCLUDED_)
