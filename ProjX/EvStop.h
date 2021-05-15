// EvStop.h: interface for the CEvStop class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVSTOP_H__CFF816DE_2DA9_4C6D_8B3E_05BF9666A58E__INCLUDED_)
#define AFX_EVSTOP_H__CFF816DE_2DA9_4C6D_8B3E_05BF9666A58E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Event.h"

class CEvStop : public CEventImpl  
{
public:
	CEvStop(long iLeft, long iRight, vector<CToken*>& vecCT, ostream& oserr = cerr);
	virtual ~CEvStop();
	virtual bool isOfType(eEventType eet) const{ return eet==ceesStartSimulation;}
	virtual bool setupEvent(list<CEquation*>* pvecpEquations); 


	virtual bool willTriggerOverTime( const variable& vValue, const variable& vValueStep, const string& sTrig = g_Time){ return false;}
	virtual eEventSignal trigger( vector< variable >* pvecVars, vector< variable >* pvecVarsLast );
	virtual bool willTrigger( vector< variable >* pvecVars );
	virtual bool isActive(){ return false; }
/*	virtual bool isActive()=0; // will this event change values ?
	virtual bool isInError() const=0;
	virtual bool isReady() const=0;
	virtual bool isCorrect() const=0;
	virtual bool isOfType(eEventType ) const=0;
	virtual bool prepareForSimulation( vector< variable >* pvecVars, ostream& oserr ) =0;
	virtual eEventType giveEventType() const=0;
	virtual CToken* canChange()=0;
	virtual bool setupEvent(list<CEquation>* pvecEquations)=0;
*/
	static bool check(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport );

protected:
	CVarRoot* m_cvr;
	vector<CToken*>& m_refvecCT;
	long m_iLeft;
	long m_iRight;
	ostream& m_oserr;
};

/*

THIS IS NOT YET IMPLEMENTED AND THE CODE IS LEFT AS A STARTING POINT

//This class is designed to hold dynamic changes from outside applications, after the model has been compiled.
class CEvStopUserGEq : public CEvStop
{
public:
	CEvStopUser(long iVarIndex, variable vValue):CEvStop(), m_bIsTime(bIsTime)
	{
		m_iIndex = iVarIndex;
		m_vSetValue = vValue;
		m_eState = cevInitiated;
	}
	virtual ~CEvStopUser(){
	ATLTRACE("~CEvStopUser()\n");
	};

	virtual CToken* canChange(){ return NULL; }
	virtual bool setupEvent(list<CEquation*>* pvecpEquations);
//	virtual bool affectsStartTime();

protected:


};

*/


#endif // !defined(AFX_EVSTOP_H__CFF816DE_2DA9_4C6D_8B3E_05BF9666A58E__INCLUDED_)
