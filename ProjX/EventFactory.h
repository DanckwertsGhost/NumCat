// EventFactory.h: interface for the CEventFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVENTFACTORY_H__75516DE4_2BBC_47DB_A18C_031481B6B142__INCLUDED_)
#define AFX_EVENTFACTORY_H__75516DE4_2BBC_47DB_A18C_031481B6B142__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include <map>
#include <string>
#include "Event.h"
#include "equation.h"
#include "SymlixStore.h"
#include "Symlix\Symlix.h"



//declare rather than include
//class CEvent;
const char g_EvEvent[]="EvValue";
const char g_TrigEvent[]="TrigEvent";
const char g_LogEvent[]="LogEvent";
const char g_RecorderEvent[]="RecorderEvent";

struct SStringCompareEVFact
{
  bool operator()(const char* s1, const char* s2) const
  {
    return strcmp(s1, s2) < 0;
  }
};

#define MapStringIndexEV map<const char*,long,SStringCompareEVFact>

class CEventFactory: public CNavTokens  
{
public:
	CEvent* createUserEvent(const eUserEvents eueNewEvent, long iVarIndex, variable vValue, bool bTime );

    static CEventFactory* instance() { 
                 if (!m_instance) m_instance = makeInstance();
                 return m_instance;
             }
	CEvent* createEvent( long iLeft, long iRight, vector< CToken* >& vecLine, IARDataStore* pIARDataStore, ostream& oserr, ListLineTokenPts& rvecEqVecs  );
//	CEvent* createEvent( long iLeft, long iRight, vector< CToken* >& vecLine );
	CEvent* createEvent(const char* sType, const CEquation& ceAction, const CEquation& ceCondition);
//	CEvent* createEvent(const char* sType, const char* sFile,long iIndexTrig, variable vStep, vector<long>& vecRepIndexes);
	CEvent* createSystemEvent(const eSysEvents eNewSysEvent);
	CEvent* createCallbackEvent(INumCatHostCallBack* pINumCatHostCallBack, vector<long>& vecInds );
	bool checkUserRequestedEvent(vector<CToken*>& vLine, IARDataStore* pIARDataStore, ostream& oserr );
	bool checkSVEvent(const char* sType, vector<CToken*>&  rVecLine, ostream& oserr  );
	void finalRelease();
	bool deleteTheseEvents( vector<CEvent*>& rvecDelEvents );
	void manageEvent( CEvent* pev );
	
	static void reset();

protected:

    static CEventFactory* makeInstance();
	CEventFactory();
	virtual ~CEventFactory();
	vector<CEvent*> m_vecCEvent;

private: 
    static void cleanupInstance();
    static CEventFactory* m_instance;
	MapStringIndexEV m_mapTypes;
	bool bFinalReleaseCalled;
	CEvent* m_pEvCallback;

};


#endif // !defined(AFX_EVENTFACTORY_H__75516DE4_2BBC_47DB_A18C_031481B6B142__INCLUDED_)
