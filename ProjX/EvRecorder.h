// EvRecorder.h: interface for the CEvRecorder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVRECORDER_H__60043B54_56F0_4A5B_ABBC_00B2074CE77E__INCLUDED_)
#define AFX_EVRECORDER_H__60043B54_56F0_4A5B_ABBC_00B2074CE77E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Event.h"
//#include <fstream>
#include "SymlixStore.h"

#define SIZE_BUFFER_CONV 14
#define SIZE_CHAR_BUFFER SIZE_BUFFER_CONV + 10 // was 3 - need more to cover _gcvt behaviour
class CEvRecorder : public CEventImpl, public CNavTokens
{
protected:
	CEvRecorder(); // default constructor - should never be used directly
public:
//	CEvRecorder(const char* sFile,long iIndexTrig, variable vStep, vector<long>& vecRepIndexes );
	CEvRecorder( long iLeft, long iRight, vector< CToken* >& vecLine, IARDataStore* pIARDataStore, ostream& oserr);
	virtual ~CEvRecorder();
// from CEventImpl
//	virtual bool willTriggerOverTime( const variable& vValue, const variable& vValueStep, const string& sTrig = g_Time);
	virtual eEventSignal trigger( vector< variable >* pvecVars, vector< variable >* pvecVarsLast  );
	virtual bool willTrigger( vector< variable >* pvecVars );
	virtual bool isActive(){ return false; }
//	virtual bool isInError() const{	return m_eState==cevError;}
//	virtual bool isReady() const;
//	virtual bool isCorrect() const{	return m_eState!=cevError;}
	virtual bool isOfType(eEventType eet) const{ return eet==ceetNoValueChange;}
	virtual eEventType giveEventType() const{ return ceetNoValueChange;}
	virtual CToken* canChange(){ return NULL;}
	virtual bool setupEvent(list<CEquation*>* pvecpEquations); // no action required

	virtual bool hasAPeriodUpperLimit(){return true;};
	virtual variable getPeriodUpperLimit(){return m_vStep;};
	virtual void finalRelease();
	// end from CEventImpl
	static bool check(long iLeft, long iRight, vector<CToken*>& vExpLine, IARDataStore *pIARDataStore, ostream& osErrReport=cerr );
	static bool checkValidFileName( const char* sName){ return true; /*TBI*/ }

protected:

	virtual eEventSignal trigCalc( vector< variable >* pvecVars, vector< variable >* pvecVarsLast );

	bool m_bMonitorStarted; // needed to prevent possible recording problems as variables head to extremes
	string m_sFile;
//	std::ofstream m_ofs;
	long m_iIndexTrig;
	CToken* m_pctTrig; // needed under some contruction types
	variable m_vStep;
	variable m_vTrigStep;
	variable m_vMonitor;
	vector<long> m_vecRepInd;
	vector< CToken* > m_vecRepTok; 
	vector< variable > m_vecResults;
	long m_ivecSizes;
private:
	IARWriteStream* m_pIARWriteStream;
	char m_sTemp[SIZE_CHAR_BUFFER];
//	char m_TEMPBUFFER[20]; //  get rid of this latter on
	bool m_bReport;
//	NEED TO THINK ABOUT SOLVERS STEPPING FORWARD ALLOWING ACCESS To PREVIOUS VALUES
//
};

#endif // !defined(AFX_EVRECORDER_H__60043B54_56F0_4A5B_ABBC_00B2074CE77E__INCLUDED_)
