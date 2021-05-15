// EvIteration.h: interface for the CEvIteration class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVITERATION_H__3318A14C_FAD9_454E_8FB6_9F60D85C0CA8__INCLUDED_)
#define AFX_EVITERATION_H__3318A14C_FAD9_454E_8FB6_9F60D85C0CA8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Event.h"
#include "Equation.h"

//#define DEBUGEVI

#ifdef DEBUGEVI
#include <ostream>
#endif

#define CEI_MAX_STEP 1.0

class CEvIteration : public CEventImpl, public CNavTokens  
{

public:
	CEvIteration( long iLeft, long iRight, vector< CToken* >& vecLine, ostream& oserr);
	virtual ~CEvIteration();

// CEventImpl
	virtual bool willTriggerOverTime( const variable& /*vValue*/, const variable& /*vValueStep*/, const string& /*sTrig*/ = g_Time);
	virtual bool willTriggerAtTime( const variable& vValue, const string& sTrig = g_Time);
	virtual eEventSignal trigger( vector< variable >* pvecVars, vector< variable >* pvecVarsLast );
	virtual bool willTrigger( vector< variable >* pvecVars );
	virtual CToken* canChange(){ return m_pLHS; }
	virtual bool setupEvent(list<CEquation*>* pvecpEquations);
//   STANDARD IMPLEMENTATIONS below
//	virtual void endOfSimulation( vector< variable >* /*pvecVars*/, vector< variable >* /*pvecVarsLast*/ ){ return; }
	virtual bool isActive(){ return true; }
//	virtual bool isInError() const{	return m_eState==cevError;}
//	virtual const string getLastErrorMessage() const{ return m_sError;}
//	virtual bool isReady() const{ return m_eState==cevInitiated;}
//	virtual bool isCorrect() const{	return m_eState!=cevError;}
//	virtual bool isOfType(eEventType eet) const{ return eet==ceetValueChange;}
	virtual bool prepareForSimulation( vector< variable >* /*pvecVars*/, ostream& /*oserr*/ );
//	virtual eEventType giveEventType() const{ return ceetValueChange; }
//	virtual bool affectsStartTime(){return false;}
//	virtual variable giveStartTime(){return (variable)NOT_DEFINED;}
	virtual void reset();
	virtual void setStrongType(const vector<varStrongType>& vecst);
	virtual void setFlag(const bool bFlag){}; // only for certain events
	virtual bool hasAPreciseTimeTrigger(const long);
	virtual variable getTimeTillTrigger(const variable& vCurrentTime){ 	return (getNextTriggerPoint( vCurrentTime) - vCurrentTime);}
//	virtual bool hasAPeriodUpperLimit(){return true;};
//	virtual variable getPeriodUpperLimit(){return CEI_MAX_STEP;};
	virtual void simulationEnd(vector< variable >& rvecVars){}; // so can tell things over
//	virtual void finalRelease(){}; // tidy up any COM dependent stuff as COM service is closing before object destroyed
//	virtual bool fixedAtStart() const{return true;} // default value - if event trigger needs to be evaluated in light of all other simulation values should return false
// end CEvent interface	
	

// end CEventImpl

	static bool check( long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport=cerr );
protected:
	CEvIteration();

	CToken* m_pLHS; // left hand side token than is changed by this iteration
	bool m_bEqualFormat;

	variable getLastTriggerPoint( const variable& vTime);
	variable& getNextTriggerPoint( const variable& vTime);

	variable m_tstep;
	variable m_tSync; // point at which the sync should start
	variable m_tNext; // maybe use this for next point
	long m_iIndTime;
	long m_iIndexLHS;
	varStrongType m_vStrongType;

	class CEI_Counter
	{
		public:
		CEI_Counter(){}
		virtual ~CEI_Counter(){}
		virtual bool first() =0;
		virtual variable value() =0;
		virtual bool next() =0;
		virtual void reset(){ first(); }
	};

	class CEI_FromTo: public CEI_Counter
	{
	public:
		CEI_FromTo( variable vFrom, variable vTo, variable vStep ):m_vFrom(vFrom),m_vCurrent(vFrom),m_vTo(vTo),m_vStep(vStep){m_bNegSlope =(m_vTo<m_vFrom);}
		virtual ~CEI_FromTo(){}
		virtual bool first(){ m_vCurrent=m_vFrom; return test(); }
		virtual bool next(){ m_vCurrent+=m_vStep; return test(); }
		virtual variable value(){ return m_vCurrent; }
	private:
		bool test(){ if (m_bNegSlope)
								 return m_vCurrent>=m_vTo;
								else
								 return m_vCurrent<=m_vTo;}
		variable m_vFrom;
		variable m_vTo;
		variable m_vStep;
		variable m_vCurrent;
		bool m_bNegSlope;
	};

	class CEI_Sequence: public CEI_Counter
	{
	public:
		CEI_Sequence( vector< variable >& rvec ):m_iCount(0){ m_vecVals = rvec; m_iSize = m_vecVals.size(); }
		virtual ~CEI_Sequence(){}
		virtual bool first(){ m_iCount=0; return m_iCount<m_iSize; }
		virtual bool next(){ return (++m_iCount)<m_iSize; }
		virtual variable value(){ if (m_iCount<m_iSize) 
										return m_vecVals[m_iCount];
										else
										return NOT_DEFINED; }
	private:
		vector< variable > m_vecVals;
		long m_iSize;
		long m_iCount;

	};


	CEI_Counter* m_pCounter;
#ifdef DEBUGEVI
	static bool m_bOpenAlready;
	ofstream* m_pos;
#endif

};

#endif // !defined(AFX_EVITERATION_H__3318A14C_FAD9_454E_8FB6_9F60D85C0CA8__INCLUDED_)
