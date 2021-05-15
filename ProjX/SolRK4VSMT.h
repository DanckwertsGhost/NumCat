// SolRK4VSMT.h: interface for the CSolRK4VSMT class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOLRK4VSMT_H__E4ADBDB2_5785_458A_8D1C_D8AA2DED1BF0__INCLUDED_)
#define AFX_SOLRK4VSMT_H__E4ADBDB2_5785_458A_8D1C_D8AA2DED1BF0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SolRK4VS.h"
#include <process.h>
#include "CritCheck.h"

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

using namespace std;


class CSolMT // in case this behaviour is needed elsewhere
{
public:
	CSolMT(){		m_hEventStart = CreateEvent(NULL,TRUE,FALSE,NULL);
					m_hEventRun = CreateEvent(NULL,FALSE,FALSE,NULL);
					m_hEventEnd = CreateEvent(NULL,TRUE,FALSE,NULL);
					InitializeCriticalSection(&m_csRunningState);
					InitializeCriticalSection(&m_csDebugState);
					m_bEndThread=false;}
	~CSolMT(){/*CCritCheck cc(m_csRunningState);*/ } // not sure - maybe deadlock

// Multithread stuff

	inline CRITICAL_SECTION& getRefCritSecRunningState(){ return m_csRunningState; }
	inline CRITICAL_SECTION& getRefCritSecDebugState(){ return m_csDebugState; }
	inline HANDLE& getRefHandleStartEvent(){ return m_hEventStart;}
	inline HANDLE& getRefHandleEndEvent(){ return m_hEventEnd;}
	inline HANDLE& getRefHandleRunEvent(){ return m_hEventRun;}
	inline bool endOfThreadRequested() const{ return m_bEndThread; }
	inline void requestEndOfThread(){ m_bEndThread = true; }

protected:
	HANDLE m_hEventStart;
	HANDLE m_hEventRun;
	HANDLE m_hEventEnd;
//	HANDLE m_hEventEndSimThread;
	CRITICAL_SECTION m_csRunningState;
	CRITICAL_SECTION m_csDebugState;
//	CRITICAL_SECTION m_csSimulationRunning;
	bool m_bEndThread;
};

class CSolRK4VSMT : public CSolRK4VS, public CSolMT  
{
public:
	CSolRK4VSMT();
	CSolRK4VSMT(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport );
	virtual ~CSolRK4VSMT();

// start CSolver interface
	virtual bool setup(CIModelSim* pims);
	virtual xt_value step(vectorValues* pvecValues,vectorConstrainedValues* pvecConST );
// end CSolver interface
	static bool check(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport=cerr );

protected:
	void launchThread();
	void killThread();
	vectorConstrainedValues m_vecDecoy;
	bool m_bMT;
	bool m_bThread;
#ifndef NDEBUG
	long m_iCountVecSize;
#endif
	CSolRK4 m_SolRK4Long;


};

class CSolveData
{
public:
	CSolveData(CSolMT& solMT, CSolver* pSolver,vectorValues* pvecValues,vectorConstrainedValues* pvecConST);
	CSolveData(const CSolveData& csd );
	~CSolveData(){};
		
	inline CSolver* getpSolver() const{ return m_pSolver; }
	inline vectorValues* getpvecValues() const{ return m_pvecValues; }
	inline vectorConstrainedValues* getpvecConsValues() const{ return m_pvecConST; }
	inline bool hasError() const{ return m_bError; }
	inline CSolMT& getSolMT(){ return m_solMT; }

protected:
	CSolver* m_pSolver;
	vectorValues* m_pvecValues;
	vectorConstrainedValues* m_pvecConST;
	CSolMT& m_solMT;
	bool m_bError;
};

#endif // !defined(AFX_SOLRK4VSMT_H__E4ADBDB2_5785_458A_8D1C_D8AA2DED1BF0__INCLUDED_)
