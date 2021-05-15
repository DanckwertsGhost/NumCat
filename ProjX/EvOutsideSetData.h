// EvOutsideSetData.h: interface for the CEvOutsideSetData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVOUTSIDESETDATA_H__37B1B73B_4759_4461_889A_28D7ACE424AC__INCLUDED_)
#define AFX_EVOUTSIDESETDATA_H__37B1B73B_4759_4461_889A_28D7ACE424AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Event.h"
#include <process.h>
#include "CritCheck.h"

class CEvOutsideSetData : public CEventImpl  
{
public:
	CEvOutsideSetData();
	virtual ~CEvOutsideSetData();

	// CEvent interface - that has to be implemented
//	virtual bool isActive(){ return true; }
//	virtual bool willTriggerOverTime( const variable& vValue, const variable& vValueStep, const string& sTrig = g_Time);
	virtual eEventSignal trigger( vector< variable >* pvecVars, vector< variable >* pvecVarsLast = NULL  );
	virtual bool willTrigger( vector< variable >* pvecVars ){ return m_bHasUpdate; }
//	virtual bool isReady() const{	return m_eState==cevInitiated;}
//	virtual bool isCorrect() const{	return m_eState!=cevError;}
//	virtual bool isInError()const{	return m_eState==cevError;}
	virtual bool isOfType(eEventType eet) const { return eet==ceetValueChange;}
	virtual eEventType giveEventType() const { return ceetValueChange; }
//	virtual CToken* canChange();
	virtual bool setupEvent(list<CEquation*>* pvecpEquations);
	virtual void reset();
	virtual void setStrongType(const vector<varStrongType>& vecst);
//	virtual bool hasAPreciseTimeTrigger(const long );
//	virtual variable getTimeTillTrigger(const variable& vCurrentTime);
	// end CEvent interface

//	static bool check(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport );

//  CEvOutsideSetData only code
	void changeValue(long iIndex, variable vValue );

protected:
	vector<varStrongType> m_vecStrongTypes;	
	vector< pair< long, variable > > m_vecChanges;
	bool m_bHasUpdate;
	CRITICAL_SECTION m_csDataUpdate;


};

#endif // !defined(AFX_EVOUTSIDESETDATA_H__37B1B73B_4759_4461_889A_28D7ACE424AC__INCLUDED_)
