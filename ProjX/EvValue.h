// EvValue.h: interface for the CEvValue class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVVALUE_H__F24685A0_670D_4DA9_9022_B9339D6D8227__INCLUDED_)
#define AFX_EVVALUE_H__F24685A0_670D_4DA9_9022_B9339D6D8227__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Event.h"
#include <fstream>
#include "Equation.h"

using namespace std;

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

class CEvValue : public CEventImpl, public CNavTokens   
{
public:
	CEvValue();
	CEvValue(const CEquation& ceAction, const CEquation& ceCondition);
	CEvValue(const CEvValue& CE);
	virtual ~CEvValue();

	// CEvent interface - that has to be implemented
	virtual bool isActive(){ return true; }
	virtual bool willTriggerOverTime( const variable& vValue, const variable& vValueStep, const string& sTrig = g_Time);
	virtual eEventSignal trigger( vector< variable >* pvecVars, vector< variable >* pvecVarsLast = NULL  );
	virtual bool willTrigger( vector< variable >* pvecVars );
//	virtual bool isReady() const{	return m_eState==cevInitiated;}
//	virtual bool isCorrect() const{	return m_eState!=cevError;}
//	virtual bool isInError()const{	return m_eState==cevError;}
	virtual bool isOfType(eEventType eet) const { return eet==ceetValueChange;}
	virtual eEventType giveEventType() const { return ceetValueChange; }
	virtual CToken* canChange();
	virtual bool setupEvent(list<CEquation*>* pvecpEquations);
	virtual void reset();
	virtual void setStrongType(const vector<varStrongType>& vecst);
	virtual bool hasAPreciseTimeTrigger(const long );
	virtual variable getTimeTillTrigger(const variable& vCurrentTime);
	virtual bool fixedAtStart() const { return m_bFixedAtStart; }
	// end CEvent interface

	static bool check(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport );
	virtual CEvValue& operator = (const CEvValue& CE){ copy(CE); return *this; }
	virtual bool operator() (const CEvValue& ce1, const CEvValue&ce2) const { return ce1.greaterThan(ce2); }
	virtual bool operator> (const CEvValue& cE) const{return greaterThan(cE);};

	// need to add metods for getting and checking states
	friend ostream& operator << (ostream& os,  const CEvValue& cE){ cE.sendtostream(os); return os; }
protected:
	virtual bool triggerAction( const variable& vTime, const variable& vTimeStep );
	virtual void sendtostream(ostream& os) const;
	virtual void copy(const CEvValue& CE);
	virtual bool greaterThan(const CEvValue& CE) const;

	CEquation m_eqAction;
	CEquation m_eqCondition;
//	eEventState m_eState;
	time_secs m_vActionValue;
	bool m_bFixedAtStart;

};

#endif // !defined(AFX_EVVALUE_H__F24685A0_670D_4DA9_9022_B9339D6D8227__INCLUDED_)
