// EvDump.h: interface for the CEvDump class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVDUMP_H__484E0C24_6185_4BAF_B252_5051C6AFEB8C__INCLUDED_)
#define AFX_EVDUMP_H__484E0C24_6185_4BAF_B252_5051C6AFEB8C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Event.h"
#include <fstream>

class CEvDump : public CEventImpl, public CNavTokens
{
protected:
//	CEvDump(); // default constructor - should never be used directly
public:
//	CEvDump(const char* sFile,long iIndexTrig, variable vStep, vector<long>& vecRepIndexes );
	CEvDump( long iLeft, long iRight, vector< CToken* >& vecLine,ostream& oserr);
	virtual ~CEvDump();
// from CEventImpl
//	virtual bool willTriggerOverTime( const variable& vValue, const variable& vValueStep, const string& sTrig = g_Time);
	virtual eEventSignal trigger( vector< variable >* pvecVars, vector< variable >*   );
//	virtual bool willTrigger( vector< variable >* pvecVars );
	virtual bool isActive(){ return false; }
//	virtual bool isInError() const{	return m_eState==cevError;}
//	virtual bool isReady() const;
//	virtual bool isCorrect() const{	return m_eState!=cevError;}
	virtual void reset();
	virtual bool isOfType(eEventType eet) const{ return eet==ceetNoValueChange;}
	virtual eEventType giveEventType() const{ return ceetNoValueChange;}
	virtual CToken* canChange(){ return NULL;}
	virtual bool setupEvent(list<CEquation*>* pvecpEquations); // no action required
	virtual void simulationEnd(vector< variable >& rvecVars);

// end from CEventImpl
	static bool check(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport=cerr );
	static bool checkValidFileName( const char* sName){ return true; /*TBI*/ }

protected:


	void setupDump();
	void closeDump();
	bool m_bRecording;

//	virtual eEventSignal trigCalc( vector< variable >* pvecVars, vector< variable >* pvecVarsLast );
	void setCacheToDefault();

	bool m_bMonitorStarted; // needed to prevent possible recording problems as variables head to extremes
	string m_sFile;
	std::ofstream m_ofs;
//	long m_iIndexTrig;
//	CToken* m_pctTrig; // needed under some contruction types
//	variable m_vStep;
//	variable m_vMonitor;
	vector<long> m_vecRepInd;
	vector< CToken* > m_vecRepTok; 

	vector< variable >* m_pvecResults;
	vector< vector< variable > > m_vecvecDump;
	vector< vector< variable > >::iterator m_itvecvecDump;
	long m_ivecSizes;

	long m_iSteps;

//	NEED TO THINK ABOUT SOLVERS STEPPING FORWARD ALLOWING ACCESS To PREVIOUS VALUES
//
};

#endif // !defined(AFX_EVDUMP_H__484E0C24_6185_4BAF_B252_5051C6AFEB8C__INCLUDED_)
