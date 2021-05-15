// EventFactory.cpp: implementation of the CEventFactory class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EventFactory.h"
#include "global.h"
#include "EvValue.h"
#include "EvStop.h"
#include "EvStart.h"
#include "EvRecorder.h"
#include "EvRegressionTest.h"
#include "EvOutsideStop.h"
#include "EvOutsideGetData.h"
#include "EvPace.h"
#include "EvSync.h"
#include "EvDump.h"
#include "EvRealTime.h"
#include "EvOutsideSetData.h"
#include "EvDDEserver.h"
#include "EvProgFeedback.h"
#include "EvIteration.h"
#include "EvDumpEquations.h"
#include "EvOnce.h"
#include "Symlix\ErrorFactory.h"
#include <algorithm>
#ifndef NDEBUG
#include <assert.h>
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
static const long C_EvValue=1;
static const long C_TrigEvent=2;
static const long C_LogEvent=3;
static const long C_RecorderEventSystem=4; // event called from code


///////////////////////////////////////////////////////////
// Function name	: CEventFactory::CEventFactory
// Description	    : protected constructor
// Return type		: 
///////////////////////////////////////////////////////////
CEventFactory::CEventFactory():bFinalReleaseCalled(false),m_pEvCallback(NULL)
{
	m_vecCEvent.reserve(20);
	m_mapTypes[g_EvEvent]=C_EvValue;
	m_mapTypes[g_TrigEvent]=C_TrigEvent;
	m_mapTypes[g_LogEvent]=C_LogEvent;
	m_mapTypes[g_RecorderEvent]=C_RecorderEventSystem;

	for(long i=0;i<g_iEvents;i++)
		m_mapTypes[g_sEvents[i]]=g_cEvents[i];

}


///////////////////////////////////////////////////////////
// Function name	: CEventFactory::~CEventFactory
// Description	    : protected destructor
// Return type		: 
///////////////////////////////////////////////////////////
CEventFactory::~CEventFactory()
{
	vector< CEvent* >::reverse_iterator it;

	if (!bFinalReleaseCalled)
			{
			SYMERRORLITE("Code execution error - missing final release for events",errInternal);
			}

	// 
	for( it=m_vecCEvent.rbegin();it!=m_vecCEvent.rend();it++)
			delete *it;

	m_mapTypes.clear();
}

CEventFactory* CEventFactory::m_instance = 0;


///////////////////////////////////////////////////////////
// Function name	: CEventFactory::reset
// Description	    : Static function to reset this factory
// Return type		: void 
///////////////////////////////////////////////////////////
void CEventFactory::reset()
{
	if (m_instance)
		{
		m_instance->finalRelease();
		}

	cleanupInstance();
}

///////////////////////////////////////////////////////////
// Function name	: CEventFactory::finalRelease
// Description	    : This must be used to signal to objects that
//                    their end is coming - before services such as COM stop.
// Return type		: void 
///////////////////////////////////////////////////////////
void CEventFactory::finalRelease()
{
	vector< CEvent* >::iterator it;

	// 
	for( it=m_vecCEvent.begin();it!=m_vecCEvent.end();it++)
			(*it)->finalRelease();

	bFinalReleaseCalled=true; // so don't trigger error on destructor
}

///////////////////////////////////////////////////////////
// Function name	: CEventFactory::cleanupInstance
// Description	    : delete singleton instance
// Return type		: void 
///////////////////////////////////////////////////////////
void CEventFactory::cleanupInstance()
{ 
   delete m_instance;
   m_instance = 0;
}
         



///////////////////////////////////////////////////////////
// Function name	: CEventFactory::makeInstance
// Description	    : create singleton and add function to delete object to atexit()
// Return type		: CEventFactory* 
///////////////////////////////////////////////////////////
CEventFactory* CEventFactory::makeInstance()
{
    atexit(&cleanupInstance);
    return (newtrack CEventFactory);
}


CEvent* CEventFactory::createEvent(const char* sType, const CEquation& ceAction, const CEquation& ceCondition)
{
	CEvent* ev = NULL;
	MapStringIndexEV::iterator itMap;

	itMap = m_mapTypes.find(sType);

	if (itMap==m_mapTypes.end())
				return NULL;

	switch(itMap->second)
	{
	case C_EvValue:
	ev = newtrack CEvValue(ceAction,ceCondition);

	break;
	case C_TrigEvent:
	// TBI
	break;
	case C_RecorderEventSystem:
	// Cannot be intialised with this function call - do nothing

	break;
	default:
	ASSERT2(false); // bring attention to this - should not have passed find
	
	break;
	}

	if (ev)
		m_vecCEvent.push_back(ev); // so life cycle managed by factory

	return ev;
}



///////////////////////////////////////////////////////////
// Function name	: CEventFactory::createEvent
// Description	    : 
// Return type		: CEvent* 
// Argument         : const char* sType
// Argument         : const char* sFile
// Argument         : long iIndexTrig
// Argument         : variable vStep
// Argument         : vector<long>& vecRepIndexes
///////////////////////////////////////////////////////////
/*CEvent* CEventFactory::createEvent(const char* sType, const char* sFile,long iIndexTrig, variable vStep, vector<long>& vecRepIndexes)
{
	CEvent* ev = NULL;
	MapStringIndexEV::iterator itMap;
	itMap = m_mapTypes.find(sType);

	if (itMap==m_mapTypes.end())
				return NULL;

	switch(itMap->second)
	{
	case C_EvValue:
	case C_TrigEvent:
	// as the wrong create method called
	break;
	case C_RecorderEventSystem:
	ev = newtrack CEvRecorder(sFile,iIndexTrig,vStep,vecRepIndexes);

	break;
	default:
	ASSERT2(false); // bring attention to this - should not have passed find
	
	break;
	}

	if (ev)
		m_vecCEvent.push_back(ev); // so life cycle managed by factory

	return ev;


}*/

///////////////////////////////////////////////////////////
// Function name	: CEventFactory::createEvent
// Description	    : This method will create events which are specified by valid
//                    event keywords as the first Token in a line.
// Return type		: CEvent*
// Argument         :  long iLeft
// Argument         : long iRight
// Argument         : vector< CToken* >& vecLine
// Argument         : IARDataStore* pIARDataStore
// Argument         : ostream& oserr
// Argument         : ListLineTokenPts& rvecEqVecs
///////////////////////////////////////////////////////////
CEvent* CEventFactory::createEvent( long iLeft, long iRight, vector< CToken* >& vecLine, IARDataStore* pIARDataStore, ostream& oserr,ListLineTokenPts& rvecEqVecs )
{
	long iRightNoComments;
	vector<CToken*>::const_iterator citRight;
	vector<CToken*>::const_iterator citLeft;
	CEvent* ev = NULL;
	MapStringIndexEV::const_iterator citMap;

	ASSERT2(iLeft<iRight);
	ASSERT2(iRight<=vecLine.size());

	if ((iLeft>=iRight)||(iRight>vecLine.size()))
			{
			if (vecLine.size()>0)
				{
				oserr << "<Error*> creating event for line "<<vecLine[0]->getLine()<<endl;
				SYMERRORTOK("Error creating event for line",errInternal,vecLine[0]);
				}
				else
				{
				oserr << "<Error*> Unable to create event - no tokens on line\n";
				SYMERRORLITE("Error creating event from a line with no content",errInternal);
				}
			return NULL; // so this action is handled
			}
	citLeft  = &vecLine[0];
	citRight = getRightWithoutComments(iLeft,iRight,vecLine);
	iRightNoComments = getPosRightWithoutComments(iLeft,iRight,vecLine);

	if (!(*citLeft)->IsOfType(ctEventKeyWord))
			{
			oserr << "<Error*> "<<(*citLeft)->getString().c_str()<<" does not define an event on line "<<(*citLeft)->getLine()<<endl;
			SYMERRORTOK("Unable to create an event for the following",errSyntax,(*citLeft));
			return NULL;
			}

	citMap = m_mapTypes.find((*citLeft)->getString().c_str());
	if (citMap==m_mapTypes.end())
			{
			oserr << "<Error*> "<<(*citLeft)->getString().c_str()<<" does not define an event on line "<<(*citLeft)->getLine()<<endl;
			SYMERRORTOK("Keyword does not define an event",errSyntax,(*citLeft));
			return NULL;
			}

	if (citMap->second==C_NotAnEvent)
			{
			oserr << "<Error*> "<<(*citLeft)->getString().c_str()<<" does not define an event on line "<<(*citLeft)->getLine()<<endl;
			SYMERRORTOK("Keyword does not define an event",errSyntax,(*citLeft));
			return NULL;
			}

	switch(citMap->second)
	{
	case C_StartEvent:
		ev = newtrack CEvStart(vecLine[iLeft+1],vecLine[iLeft+3]->getNumber());
		break;
	case C_StopEvent:
		ev = newtrack CEvStop(iLeft+1,iRightNoComments,vecLine,oserr);
		break;
	case C_RecordEvent:
		ev = newtrack CEvRecorder(iLeft+1,iRightNoComments,vecLine,pIARDataStore,oserr);
		break;
	 // the next cases should never be found via this call
	case C_EvValue:
	case C_TrigEvent:
		oserr << "<Internal Error*> Please report this error code "<<ERROR_EVENT_TRIGEVENT1 <<" to info@astonread.com with the input file and programme version,\n this line "<<(*citLeft)->getLine() <<" will need to be deleted for now - Sorry !\n";
		SYMERRORTOK("Syntax has created internal error - rephrase or report to vendor",errInternal,(*citLeft));
		ev = NULL;
		break;
	case C_RegressionTest:
		ev = newtrack CEvRegressionTest(iLeft+1,iRightNoComments,vecLine,oserr);
		break;
	case C_Pace:
		ev = newtrack CEvPace(iLeft+1,iRightNoComments,vecLine,oserr);
		break;
	case C_Sync:
		ev = newtrack CEvSync(iLeft+1,iRightNoComments,vecLine,oserr);
		break;
	case C_Dump:
		if (vecLine.size()<2) // should have been trigger in check phase, but put here to be complete
			{
			SYMERRORTOK("Dump event incomplete.",errSyntax,vecLine[0]);
			return false;
			}
		if (vecLine[1]->getString().compare(g_Equations)==0)
				ev = newtrack CEvDumpEquations(iLeft+1,iRightNoComments,vecLine,oserr,rvecEqVecs);
				else
				ev = newtrack CEvDump(iLeft+1,iRightNoComments,vecLine,oserr);
		break;
	case C_RealTime:
		ev = newtrack CEvRealTime(iLeft+1,iRightNoComments,vecLine,oserr);
		break;
	case C_DDEserver:
		ev = newtrack CEvDDEServer(iLeft+1,iRightNoComments,vecLine,oserr);
		break;
	case C_SequenceEvent:
		vecLine[iLeft]->setType( ctSolverKeyWord ); // so that when its processed as a solver it will be recognised
	case C_Iteration:  
		ev = newtrack CEvIteration(iLeft+1,iRightNoComments,vecLine,oserr);
		break;
	case C_OnceEvent:
		vecLine[iLeft]->setType( ctSolverKeyWord ); // so that when its processed as a solver it will be recognised
		ev = newtrack CEvOnce();
		break;
	default:
		oserr << "<Internal Error*> Please report this error code "<<ERROR_EVENT_DEFAULT1 <<" to info@astonread.com with the input file and programme version,\n this line "<<(*citLeft)->getLine() <<" will need to be deleted for now - Sorry !\n";
		SYMERRORTOK("There appears to be an internal error processing this line, please report to vendor",errInternal,(*citLeft));
		ev = NULL;
		break;
	}

	if ((ev)&&(ev->isInError()))
		{
		oserr << "<Error*> With creating an event '"<<(*citLeft)->getString().c_str()<< "' on line "<<(*citLeft)->getLine()<<". "<<ev->getLastErrorMessage().c_str()<<endl;
		SYMERRORTOK2("Creating this event created an error with the event: ",ev->getLastErrorMessage().c_str(),errWarning,(*citLeft));
		delete ev; // as it should be allowed to go forward
		ev = NULL;
		}

	if (ev)
		m_vecCEvent.push_back(ev); // so life cycle managed by factory


	return ev;
}



///////////////////////////////////////////////////////////
// Function name	: CEventFactory::createSystemEvent
// Description	    : To creat system events
// Return type		: CEvent* 
// Argument         : const eSysEvents eNewSysEvent
///////////////////////////////////////////////////////////
CEvent* CEventFactory::createSystemEvent(const eSysEvents eNewSysEvent)
{
	CEvent* pev = NULL;

	switch(eNewSysEvent)
	{
	case eseOutsideStop:
		pev = newtrack CEvOutsideStop();
		break;
	case eseOutsideGet:
		ATLTRACE("eseOutsideSet not yet implemented %s %d\n",__FILE__,__LINE__);
//		pev = newtrack CEvOutsideGetData(); Commented out as not used right now
//		break;
	case eseOutsideSet: // NYI
		ATLTRACE("eseOutsideSet not yet implemented %s %d\n",__FILE__,__LINE__);
	default:
		break;
	}

	if (pev)
		m_vecCEvent.push_back(pev); // so life cycle managed by factory


	return pev;
}


///////////////////////////////////////////////////////////
// Function name	: CEventFactory::createCallbackEvent
// Description	    : Currently only allows one such event
// Return type		: CEvent* 
// Argument         : INumCatHostCallBack* pINumCatHostCallBack
// Argument         : vector<long>& vecInds
///////////////////////////////////////////////////////////
CEvent* CEventFactory::createCallbackEvent(INumCatHostCallBack* pINumCatHostCallBack, vector<long>& vecInds )
{
	if ((!pINumCatHostCallBack)||(vecInds.size()==0))
			return NULL;

	if (!m_pEvCallback) // only creating one call back event
		{
		m_pEvCallback = newtrack CEvProgFeedback(vecInds,pINumCatHostCallBack);
		if (m_pEvCallback)
				m_vecCEvent.push_back(m_pEvCallback);
		}
		else
		{
		SYMERRORLITE("Creating multiple callbacks not yet supported",errSystem);
		return NULL;
		}

	return m_pEvCallback;
	
	
}


bool CEventFactory::checkSVEvent(const char* sType, vector<CToken*>& rVecLine, ostream& oserr  )
{
	bool bResult = false;
	MapStringIndexEV::iterator itMap;

	if (rVecLine.size()<1)
			{
			SYMERRORLITE("Malformed event passed from parser",errInternal);
			ASSERT2(false); // shouldn't happen
			return false;
			}


	itMap = m_mapTypes.find(sType);

	if (itMap==m_mapTypes.end())
				{
				SYMERRORTOK("Unable to identify this line, check syntax",errSyntax,rVecLine[0]);
				return false;
				}

	switch(itMap->second)
	{
	case C_EvValue:

		bResult = CEvValue::check(0,rVecLine.size(),rVecLine,oserr);

	break;
	default:
	SYMERRORLITE("Malformed event passed from parser",errInternal);
	SYMERRORTOK("Unable to identify this line, check syntax",errSyntax,rVecLine[0]);
	ASSERT2(false); // bring attention to this - should not have passed find
	
	break;
	}

	return bResult;
}


///////////////////////////////////////////////////////////
// Function name	: CEventFactory::checkUserRequestedEvent
// Description	    : Checks that user event requests are well formated
// Return type		: bool 
// Argument         : vector<CToken*>& vLine
// Argument         : IARDataStore* pIARDataStore
// Argument         : ostream& oserr
///////////////////////////////////////////////////////////
bool CEventFactory::checkUserRequestedEvent(vector<CToken*>& vLine, IARDataStore* pIARDataStore, ostream& oserr )
{

	bool bResult = false; // be default
	MapStringIndexEV::iterator itMap;

	if (vLine.size()==0)
				{
				oserr << "<Error*> Malformed event passed from parser. Internal error.\n"<<endl;
				SYMERRORLITE("Malformed event passed from parser",errInternal);
				ASSERT2(false); // should not happen
				return false;
				}

/*	if (vLine.size()<2) // not needed - should be caught latter
				{
				oserr << "<Error*> Malformed event on line "<<vLine[0]->getLine()<<endl;
				SYM - to be done if code reused.
				return false;
				}*/

	if (!vLine[0]->IsOfType(ctEventKeyWord))
				{
				oserr << "<Error*> first token of an event must be an event keyword.\n";
				SYMERRORTOK("First word of an event must be an event keyword",errSyntax,vLine[0]);
				return false;
				}

	itMap = m_mapTypes.find(vLine[0]->getStringRef().c_str());

	if (itMap==m_mapTypes.end())
				{
				oserr << "<Error*> Keyword not recognised '"<< vLine[0]->getStringRef().c_str()<<"' on line "<<vLine[0]->getLine() <<".\n";
				SYMERRORTOK("Keyword not recognised",errSyntax,vLine[0]);
				return false;
				}

	switch(itMap->second)
	{
	case C_EvValue:
	case C_TrigEvent:
	case C_RecorderEventSystem:
		oserr << "<Warning*> Checking requested for events that can only be initated from code - ignoring line: "<<vLine[0]->getLine()<<endl;
		SYMERRORTOK("You are requesting an event reserved for intiation only from code",errSyntax,vLine[0]);
		ASSERT2(false); // don't believe this should be happening 	
		break;
	case C_StartEvent:
		bResult=CEvStart::check(1,vLine.size(),vLine,oserr);
		break;
	case C_StopEvent:
		bResult=CEvStop::check(1,vLine.size(),vLine,oserr);
		break;
	case C_RecordEvent:
		bResult=CEvRecorder::check(1,vLine.size(),vLine,pIARDataStore,oserr);
		break;
	case C_Pace:
		bResult=CEvPace::check(1,vLine.size(),vLine,oserr);
		break;
	case C_NotAnEvent:
		oserr <<"<Error*> the first word used is not ment to be at the beginning of an event statement : {";
		oserr <<vLine[0]->getStringRef().c_str()<< "} on line "<<vLine[0]->getLine()<<endl;
		SYMERRORTOK("The first word used is not ment to be used at the beginning of an event",errSyntax,vLine[0]);
		break;
	case C_RegressionTest:
		bResult=CEvRegressionTest::check(1,vLine.size(),vLine,oserr);
		break;
	case C_Sync:
		bResult=CEvSync::check(1,vLine.size(),vLine,oserr);
		break;
	case C_Dump:
		if (vLine.size()<2)
			{
			SYMERRORTOK("Dump event incomplete.",errSyntax,vLine[0]);
			return false;
			}
		if (vLine[1]->getString().compare(g_Equations)==0)
				bResult=CEvDumpEquations::check(1,vLine.size(),vLine,oserr);
				else
				bResult=CEvDump::check(1,vLine.size(),vLine,oserr);
		break;
	case C_RealTime:
		bResult=CEvRealTime::check(1,vLine.size(),vLine,oserr);
		break;
	case C_DDEserver:
		bResult=CEvDDEServer::check(1,vLine.size(),vLine,oserr);
		break;
	case C_Iteration:
	case C_SequenceEvent:
		bResult=CEvIteration::check(1,vLine.size(),vLine,oserr);
		break;
	case C_OnceEvent:
		bResult = true;
		break;
	default:
		SYMERRORTOK("Failed to process event",errInternal,vLine[0]);
		ASSERT2(false); // bring attention to this - should not have passed find
		
		break;

	}


	return bResult;
}


///////////////////////////////////////////////////////////
// Function name	: CEventFactory::createUserEvent
// Description	    : For the creation of events generated by the user outside of the input file.
// Return type		: CEvent* 
// Argument         : const eUserEvents eueNewEvent
// Argument         : long iVarIndex
// Argument         : variable vValue
// Argument         : bool bTime
///////////////////////////////////////////////////////////
CEvent* CEventFactory::createUserEvent(const eUserEvents eueNewEvent, long iVarIndex, variable vValue, bool bTime)
{

	CEvent* pev = NULL;

	switch(eueNewEvent)
	{
	case eueStart:
		pev = newtrack CEvStartUser(iVarIndex,vValue,bTime);
		break;
	default:
		break;
	}

	if (pev)
		m_vecCEvent.push_back(pev); // so life cycle managed by factory


	return pev;

}


///////////////////////////////////////////////////////////
// Function name	: CEventFactory::deleteTheseEvents
// Description	    : The vector of pointer of objects to be deleted
// Return type		: bool 
// Argument         : const vector<CEvent*> rvecDelEvents
///////////////////////////////////////////////////////////
bool CEventFactory::deleteTheseEvents( vector<CEvent*>& rvecDelEvents )
{
#ifndef NDEBUG
	long iBefore = m_vecCEvent.size();
#endif
	vector<CEvent*>::iterator itv;
	vector<CEvent*>::iterator it;

	for (itv=rvecDelEvents.begin();itv!=rvecDelEvents.end();itv++)
		{
		it = std::find(m_vecCEvent.begin(),m_vecCEvent.end(),*itv);
		if (it!=m_vecCEvent.end())
			{
			CEvent* pEv = (*it);
			if (pEv==m_pEvCallback) 
				m_pEvCallback=NULL;
			pEv->finalRelease();
			delete pEv;
			m_vecCEvent.erase(it);
			}
		(*itv) = NULL;
		}

#ifndef NDEBUG
	ATLTRACE("Number of events before %d and after %d\n",iBefore,m_vecCEvent.size());
	ATLASSERT((iBefore-rvecDelEvents.size())==m_vecCEvent.size());
#endif

	return true;
}


void CEventFactory::manageEvent(CEvent *pev)
{
	if (pev)
		m_vecCEvent.push_back(pev); // so life cycle managed by factory
}
