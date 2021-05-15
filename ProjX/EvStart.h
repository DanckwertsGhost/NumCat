// EvStart.h: interface for the CEvStart class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVSTART_H__8593D359_D550_4908_8818_19F50C5EA276__INCLUDED_)
#define AFX_EVSTART_H__8593D359_D550_4908_8818_19F50C5EA276__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Event.h"


class CEvStart : public CEventImpl 
{
public:
	CEvStart(CToken* pctLHS, variable vSetValue);
	virtual ~CEvStart();
	virtual CToken* canChange(){ return m_pctLHS; }
	virtual bool willTriggerOverTime( const variable& /*vValue*/, const variable& /*vValueStep*/, const string& /*sTrig*/ = g_Time){ return ((!m_bFired)&&(m_eState!=cevError)); }
	virtual eEventSignal trigger( vector< variable >* pvecVars, vector< variable >* /*pvecVarsLast*/ );
	virtual bool willTrigger( vector< variable >* /*pvecVars*/ ){ return ((!m_bFired)&&(m_eState!=cevError)); }
	virtual bool isOfType(eEventType eet) const{ return eet==ceetValueChangeStart;}
	virtual bool setupEvent(list<CEquation*>* pvecpEquations);
	virtual bool prepareForSimulation( vector< variable >* pvecVars, ostream& oserr  );
	virtual void setStrongType(const vector<varStrongType>& vecst);
	virtual bool isActive(){ return true; }

	static bool check(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport );
	virtual bool affectsStartTime();
	virtual variable giveStartTime();
	virtual void reset(){m_bFired=false;};

protected:
	CEvStart():CEventImpl(),m_pctLHS(NULL),m_iIndex(NOT_DEFINED),m_vSetValue(NOT_DEFINED),m_bFired(false){}
	bool m_bFired; // this event fires once only
	varStrongType m_vSetValue;
	long m_iIndex;
	CToken* m_pctLHS;

};

//This class is designed to hold dynamic changes from outside applications, after the model has been compiled.
class CEvStartUser : public CEvStart
{
public:
	CEvStartUser(long iVarIndex, variable vValue, bool bIsTime ):CEvStart(), m_bIsTime(bIsTime)
	{
		m_iIndex = iVarIndex;
		m_vSetValue = vValue;
		m_eState = cevInitiated;
	}
	virtual ~CEvStartUser(){
	ATLTRACE("~CEvStartUser()\n");
	};

	virtual CToken* canChange(){ return NULL; }
	virtual bool setupEvent(list<CEquation*>* pvecpEquations);
	virtual bool affectsStartTime();
	virtual bool isActive(){ return true; }
#ifndef NDEBUG
	virtual eEventSignal trigger( vector< variable >* pvecVars, vector< variable >* /*pvecVarsLast*/ );
#endif
protected:

	bool m_bIsTime;

};

#endif // !defined(AFX_EVSTART_H__8593D359_D550_4908_8818_19F50C5EA276__INCLUDED_)
