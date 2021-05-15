// EvOutsideGetData.h: interface for the CEvOutsideGetData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVOUTSIDEGETDATA_H__001CAB3E_FABB_425A_8A0A_A63C55E325BC__INCLUDED_)
#define AFX_EVOUTSIDEGETDATA_H__001CAB3E_FABB_425A_8A0A_A63C55E325BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Event.h"
#include <process.h>
#include "CritCheck.h"

class CEvOutsideGetData : public CEventImpl  
{
public:
	CEvOutsideGetData();
	virtual ~CEvOutsideGetData();

	// CEvent interface - that has to be implemented
//	virtual bool isActive(){ return true; }
//	virtual bool willTriggerOverTime( const variable& vValue, const variable& vValueStep, const string& sTrig = g_Time);
	virtual eEventSignal trigger( vector< variable >* pvecVars, vector< variable >* pvecVarsLast = NULL  );
	virtual bool willTrigger( vector< variable >* pvecVars ){ return m_bHasUpdate; }
//	virtual bool isReady() const{	return m_eState==cevInitiated;}
//	virtual bool isCorrect() const{	return m_eState!=cevError;}
//	virtual bool isInError()const{	return m_eState==cevError;}
	virtual bool isOfType(eEventType eet) const { return eet==ceetNoValueChange;}
	virtual eEventType giveEventType() const { return ceetNoValueChange; }
//	virtual CToken* canChange();
	virtual bool setupEvent(list<CEquation*>* pvecpEquations);
	virtual void reset();
//	virtual void setStrongType(const vector<varStrongType>& vecst);
//	virtual bool hasAPreciseTimeTrigger(const long );
//	virtual variable getTimeTillTrigger(const variable& vCurrentTime);
	virtual void simulationEnd(vector< variable >& rvecVars);
	// end CEvent interface

//	static bool check(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport );

//  CEvOutsideGetData only code
	void getValues(vector< variable >& rvSnapValues);

protected:
	vector< variable > m_vecLastValues;
//	vector<varStrongType> m_vecStrongTypes;	
//	vector< pair< long, variable > > m_vecChanges;
	bool m_bHasUpdate;
	CRITICAL_SECTION m_csDataUpdate;

};

#endif // !defined(AFX_EVOUTSIDEGETDATA_H__001CAB3E_FABB_425A_8A0A_A63C55E325BC__INCLUDED_)
