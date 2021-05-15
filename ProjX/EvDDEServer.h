// EvDDEServer.h: interface for the CEvDDEServer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVDDESERVER_H__3E4254C1_1F77_4503_8D39_754011A39F5F__INCLUDED_)
#define AFX_EVDDESERVER_H__3E4254C1_1F77_4503_8D39_754011A39F5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Event.h"
#include <fstream>
#include <time.h>
#include <sys/timeb.h>
#include "critcheck.h"
#include <map>

class CDDEServerData; // declare

struct SStringCompareEVDDE
{
  bool operator()(const string& s1, const string& s2) const
  {
    return s1.compare(s2) < 0;
  }
};

#define MapStringDDE map<string,long,SStringCompareEVDDE>

class CEvDDEServer : public CEventImpl, public CNavTokens  
{
public:
	CEvDDEServer( long iLeft, long iRight, vector< CToken* >& vecLine,ostream& oserr);
	virtual ~CEvDDEServer();
// from CEventImpl
//	virtual bool willTriggerOverTime( const variable& vValue, const variable& vValueStep, const string& sTrig = g_Time);
	virtual eEventSignal trigger( vector< variable >* pvecVars, vector< variable >* pvecVarsLast  );
//	virtual bool willTrigger( vector< variable >* pvecVars );
	virtual bool isActive(){ return false; }
//	virtual bool isInError() const{	return m_eState==cevError;}
//	virtual bool isReady() const;
//	virtual bool isCorrect() const{	return m_eState!=cevError;}
	virtual bool isOfType(eEventType eet) const{ return eet==ceetNoValueChange;}
	virtual eEventType giveEventType() const{ return ceetNoValueChange;}
//	virtual CToken* canChange(){ return NULL;}
	virtual bool setupEvent(list<CEquation*>* pvecpEquations); // no action required
	virtual void reset();

//	virtual bool hasAPeriodUpperLimit(){return true;};
//	virtual variable getPeriodUpperLimit(){return m_vStep;};
	virtual void simulationEnd();
// end from CEventImpl
	static bool check(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport=cerr );
	string& getServerName(){ return m_sServer; }
	unsigned short getTimeStep(){ return m_vDDETimeStep*1000;}
	bool findVariable( const char* sVar);
	long getSizeResults() const;
	variable getValue( const char* sVar) const;
	bool updateWithResults( vector<variable>& vecResults) const;
	bool copyIndexMap(MapStringDDE& newMap) const;

protected:

	bool launchDDEServer();
	void closeDDEServer();

	string m_sServer;
	vector<long> m_vecRepInd;
	vector< CToken* > m_vecRepTok; 
	vector< variable > m_vecResults; // where results are copied to
	long m_ivecSizes;
	variable m_vDDETimeStep;
	CDDEServerData* m_pDDEServerData;
	bool m_bNotRunning;
	MapStringDDE m_mapWatches;

};

#include <windows.h>

/*
Note:

HANDLE CreateEvent(
  LPSECURITY_ATTRIBUTES lpEventAttributes,
                      // pointer to security attributes
  BOOL bManualReset,  // flag for manual-reset event
  BOOL bInitialState, // flag for initial state
  LPCTSTR lpName      // pointer to event-object name
);
*/

class CDDEServerData
{
public:
		CDDEServerData(CEvDDEServer* pEvDDES ):m_pEvDDEServer(pEvDDES),m_hwndDDEWinProc(NULL),m_bState(true),m_hwndTimerDDEWinProc(NULL)
		{
			InitializeCriticalSection(&m_CritSectData);
			m_hEventStart = CreateEvent(NULL,TRUE,FALSE,NULL);
			m_hEventRun = CreateEvent(NULL,FALSE,FALSE,NULL);
			m_hEventClose = CreateEvent(NULL,FALSE,FALSE,NULL);
			if (!pEvDDES)
				m_bState=false;
				else
				{
				m_sAppName = pEvDDES->getServerName();
				szAppName = newtrack char[m_sAppName.length()+2];
				strcpy(szAppName,m_sAppName.c_str());
				}
		}
		~CDDEServerData()
		{
			delete []szAppName;
		}
		inline isOK(){ return m_bState; }
		inline CEvDDEServer* getEvDDEServer(){ return m_pEvDDEServer; }
//		inline HWND gethwndDDEWinProc(){ return m_hwndDDEWinProc; }
		inline bool SendEndOfSimulation()
			{
			if (m_hwndTimerDDEWinProc)
				{
				ATLTRACE("SendEndOfSimulation WM_CLOSE%d\n",m_hwndTimerDDEWinProc);
				SendMessage(m_hwndTimerDDEWinProc,WM_CLOSE,0,0L);
				return true;
				}
			return false;
			}
		inline void setTimerDDEHandle(HWND hwnd){ m_hwndTimerDDEWinProc = hwnd; }
		inline bool sendEndDDEServerAndWait(DWORD dwWait ) // send end and wait for it
		{
		 bool bResult;
		 if (!m_hwndTimerDDEWinProc)
			return false;
		 SendEndOfSimulation();
		 DWORD dw = WaitForSingleObject(m_hEventClose,dwWait);
		 switch(dw)
		 {
		  case WAIT_TIMEOUT:
		  case WAIT_ABANDONED:
		  case WAIT_FAILED:
			bResult = false;
			break;
		  default:
			bResult = true;
			break;
		  // nothing
		 }
		 return bResult;

		}
		inline void signalCloseTimerWindow()
		{
		#ifndef NDEBUG
		 if(!SetEvent(m_hEventClose))
			ATLTRACE("signalCloseTimerWindow failed\n");
			else
			ATLTRACE("signalCloseTimerWindow\n");
		#else
			SetEvent(m_hEventClose);
		#endif
		}		 
		inline CRITICAL_SECTION& getCriticalSection(){ return m_CritSectData; }
		inline HANDLE getStartEvent(){ return m_hEventStart; }
		inline HANDLE getRunEvent(){ return m_hEventRun; }
		inline HANDLE getCloseEvent(){ return m_hEventClose; }
		inline char* getAppName(){ return szAppName; }

private:

		HANDLE m_hEventStart;
		HANDLE m_hEventRun;
		HANDLE m_hEventClose;
		CRITICAL_SECTION m_CritSectData;
		char* szAppName;



		CEvDDEServer* m_pEvDDEServer;
		HWND m_hwndDDEWinProc;
		HWND m_hwndTimerDDEWinProc;
		bool m_bState;
		string m_sAppName;
		string m_sDataServiceName;
		string m_sRunTimeServiceName;
};
#endif // !defined(AFX_EVDDESERVER_H__3E4254C1_1F77_4503_8D39_754011A39F5F__INCLUDED_)
