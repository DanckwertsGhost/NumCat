// Event.h: interface for the CEvent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVENT_H__573C082C_6861_4378_AD99_F129B5BC6F4B__INCLUDED_)
#define AFX_EVENT_H__573C082C_6861_4378_AD99_F129B5BC6F4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000




/***********************************
	Abstract class for Events.

***********************************/
#include "global.h"
#include "Token.h"
#include <vector>
#include <list>
#include <string>
#include "Equation.h"

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

using namespace std;

//define system events
enum eSysEvents{ eseOutsideStop, eseOutsideGet, eseOutsideSet };
enum eUserEvents{ eueStart, eueStop };

/* Development note
	Need to consider what interfaces should be here, perhaps a pre for STL
	abstract class is needed also to give a common interface for objects
	that may be help in STL containers.
*/
//class CEquation; // early declaration

enum eEventState{cevUninitiated,cevError,cevInitiated,cevFired};
enum eEventType{ceetValueChange,ceetNoValueChange,ceetValueChangeOnce,ceetValueChangeStart,ceetValueChangeAfterStart};
// code for responses from events - to allow an Event to stop a simulation and signal
// any other forms of control required.
enum eEventSignal{ceesTrig,ceesNoTrig, ceesEndSimulation, ceesStartSimulation};

class CEvent  
{
public:
	virtual ~CEvent(){};

	virtual bool willTriggerOverTime( const variable& /*vValue*/, const variable& /*vValueStep*/, const string& /*sTrig*/ = g_Time)=0;
	virtual bool willTriggerAtTime( const variable& /*vValue*/, const string& /*sTrig*/ = g_Time)=0;
	virtual eEventSignal trigger( vector< variable >* /*pvecVars*/, vector< variable >* /*pvecVarsLast*/ )=0;
	virtual bool willTrigger( vector< variable >* /*pvecVars*/ )=0;
	virtual void endOfSimulation( vector< variable >* /*pvecVars*/, vector< variable >* /*pvecVarsLast*/ )=0;
	virtual bool isActive()=0; // will this event change values ?
	virtual bool isInError() const=0;
	virtual const string getLastErrorMessage() const=0;
	virtual bool isReady() const=0;
	virtual bool isCorrect() const=0;
	virtual bool isOfType(eEventType ) const=0;
	virtual bool prepareForSimulation( vector< variable >* /*pvecVars*/, ostream& /*oserr*/ ) =0;
	virtual eEventType giveEventType() const=0;
	virtual CToken* canChange()=0;
	virtual bool setupEvent(list<CEquation*>* pvecpEquations)=0;
	virtual bool affectsStartTime()=0;
	virtual variable giveStartTime()=0;
	virtual void reset()=0;
	virtual void setStrongType(const vector<varStrongType>& /*vecst*/)=0;
	virtual void setFlag(const bool bFlag)=0;
	virtual bool hasAPreciseTimeTrigger(const long)=0;
	virtual variable getTimeTillTrigger(const variable& /*vCurrentTime*/)=0;
	virtual bool hasAPeriodUpperLimit()=0;
	virtual variable getPeriodUpperLimit()=0;
	virtual void simulationEnd(vector< variable >& rvecVars)=0;
	virtual void finalRelease()=0; // tidy up any COM dependent stuff as COM service is closing before object destroyed
	virtual bool fixedAtStart() const=0;

};


// A vanilla CEvent implementation to allow for common solutions
class CEventImpl : public CEvent
{
public:
	CEventImpl():m_eState(cevError),m_sError(""){}
	virtual ~CEventImpl(){}
// begin CEvent interface
	virtual bool willTriggerOverTime( const variable& /*vValue*/, const variable& /*vValueStep*/, const string& /*sTrig*/ = g_Time){ return false;}
	virtual bool willTriggerAtTime( const variable& vValue, const string& sTrig = g_Time){ return willTriggerOverTime((vValue-DEFAULT_SMALL_NUMBER/2.0),DEFAULT_SMALL_NUMBER,sTrig);}
	virtual eEventSignal trigger( vector< variable >* /*pvecVars*/, vector< variable >* /*pvecVarsLast*/ ){ return ceesNoTrig;}
	virtual bool willTrigger( vector< variable >* /*pvecVars*/ ){ return false; };
	virtual CToken* canChange(){ return NULL; }
	virtual bool setupEvent(list<CEquation*>* pvecpEquations){ return false; }
//   STANDARD IMPLEMENTATIONS below
	virtual void endOfSimulation( vector< variable >* /*pvecVars*/, vector< variable >* /*pvecVarsLast*/ ){ return; }
	virtual bool isActive(){ return true; } // ie can this change values - or is it passive - eg a reporter ( all passive events carried out last
	virtual bool isInError() const{	return m_eState==cevError;}
	virtual const string getLastErrorMessage() const{ return m_sError;}
	virtual bool isReady() const{ return m_eState==cevInitiated;}
	virtual bool isCorrect() const{	return m_eState!=cevError;}
	virtual bool isOfType(eEventType eet) const{ return eet==ceetValueChange;}
	virtual bool prepareForSimulation( vector< variable >* /*pvecVars*/, ostream& /*oserr*/ );
	virtual eEventType giveEventType() const{ return ceetValueChange; }
	virtual bool affectsStartTime(){return false;}
	virtual variable giveStartTime(){return (variable)NOT_DEFINED;}
	virtual void reset(){};
	virtual void setStrongType(const vector<varStrongType>& /*vecst*/){};
	virtual void setFlag(const bool bFlag){}; // only for certain events
	virtual bool hasAPreciseTimeTrigger(const long){ return false;} // default
	virtual variable getTimeTillTrigger(const variable& /*vCurrentTime*/){ return static_cast<variable>(-1); }
	virtual bool hasAPeriodUpperLimit(){return false;};
	virtual variable getPeriodUpperLimit(){return NOT_DEFINED;};
	virtual void simulationEnd(vector< variable >& rvecVars){}; // so can tell things over
	virtual void finalRelease(){}; // tidy up any COM dependent stuff as COM service is closing before object destroyed
	virtual bool fixedAtStart() const{return true;} // default value - if event trigger needs to be evaluated in light of all other simulation values should return false
// end CEvent interface
protected:
	eEventState m_eState;
	string m_sError;


};

#endif // !defined(AFX_EVENT_H__573C082C_6861_4378_AD99_F129B5BC6F4B__INCLUDED_)
