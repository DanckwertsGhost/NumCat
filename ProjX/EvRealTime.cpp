// EvRealTime.cpp: implementation of the CEvRealTime class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <process.h>
#include "EvRealTime.h"
#include <windows.h>
#include "Symlix/ErrorFactory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#ifndef NDEBUG
#define DEBUG_EVREALTIME
#endif


CEvRealTime::CEvRealTime(long iLeft, long iRight, vector<CToken*>& vecCT, ostream& oserr /*= cerr*/):CEventImpl()
{
	m_ptimebLast= &m_timebOne;
	m_ptimebNow= &m_timebTwo;
	m_ptimebTemp= NULL;

	if (check(iLeft,iRight,vecCT,oserr))
		{

		if (iLeft==iRight)
			m_vTimeScale = 1;
			else
			m_vTimeScale = 1.f/vecCT[iLeft]->getNumber();
		m_eState = cevInitiated;

		}
		else
		{
		m_sError = "<Internal Error#> Unable to intialise ";
		m_sError.append(g_RealTime);
		m_sError.append(" event.");
		m_eState = cevError;
		
		}

}

CEvRealTime::~CEvRealTime()
{

}


///////////////////////////////////////////////////////////
// Function name	: CEvRealTime::trigger
// Description	    : 
// Return type		: eEventSignal 
// Argument         :  vector< variable >* pvecVars
// Argument         : vector< variable >* /*pvecVarsLast*/
///////////////////////////////////////////////////////////
eEventSignal CEvRealTime::trigger( vector< variable >* pvecVars, vector< variable >* /*pvecVarsLast*/ )
{
	ASSERT2(m_eState==cevInitiated);
	ASSERT2(m_iIndTime!=NOT_DEFINED);

	if (m_bHasNotStarted)
		{
			_ftime(m_ptimebLast);
			ASSERT2(m_iIndTime!=NOT_DEFINED);
			ASSERT2(cevInitiated<pvecVars->size());
			m_vSimTimeLast=(*pvecVars)[m_iIndTime];
			m_bHasNotStarted=false;
			#ifdef DEBUG_EVREALTIME
			_ftime(&m_timebStart);
			#endif
		}
		else
		{
			_ftime(m_ptimebNow);

			m_millitm = m_ptimebNow->millitm - m_ptimebLast->millitm;
			m_timetDSecs = m_ptimebNow->time - m_ptimebLast->time;
		

//			m_vTimeStep = m_timetDSecs + m_millitm/1000.f;
//			m_vTimeStep -= (*pvecVars)[m_iIndTime] - m_vSimTimeLast;


			m_vTimeStep = m_vTimeScale*((*pvecVars)[m_iIndTime] - m_vSimTimeLast);
			m_vTimeStep -= m_timetDSecs + (m_millitm/1000.f);

			if (m_vTimeStep>0)
//					 WaitForSingleObject(NULL,DWORD(m_vTimeStep*1000));
					 Sleep(DWORD(m_vTimeStep*1000));

			#ifdef DEBUG_EVREALTIME
			cout <<"m_vTimeStep="<< m_vTimeStep <<" m_vTimeScale="<< m_vTimeScale <<" Gap="<< (m_timetDSecs + m_millitm/1000.f) <<" ";
			long iMills = m_ptimebNow->millitm - m_timebStart.millitm;
			if (iMills<0)
					cout <<  m_ptimebNow->time - m_timebStart.time -1 << "." <<1000+ m_ptimebNow->millitm - m_timebStart.millitm <<"\t"<<(*pvecVars)[m_iIndTime]<<endl;
					else
					cout <<  m_ptimebNow->time - m_timebStart.time << "." << m_ptimebNow->millitm - m_timebStart.millitm <<"\t"<<(*pvecVars)[m_iIndTime]<<endl;
			#endif
			// do the pointer shuffle
			m_vSimTimeLast = (*pvecVars)[m_iIndTime];
			//m_ptimebTemp=m_ptimebLast;
			//m_ptimebLast=m_ptimebNow;
			//m_ptimebNow=m_ptimebTemp;

			// because this will be used to estimate the time taken by the solver
			_ftime(m_ptimebLast);


		}

    return ceesNoTrig;
}



///////////////////////////////////////////////////////////
// Function name	: CEvRealTime::reset
// Description	    : 
// Return type		: void 
///////////////////////////////////////////////////////////
void CEvRealTime::reset()
{
	m_bHasNotStarted = true;

}


///////////////////////////////////////////////////////////
// Function name	: CEvRealTime::hasAPreciseTimeTrigger
// Description	    : 
// Return type		: bool 
// Argument         : const long iTime
///////////////////////////////////////////////////////////
bool CEvRealTime::hasAPreciseTimeTrigger(const long iTime)
{
	ASSERT2(iTime>=0);

	m_iIndTime = iTime;
	if (m_eState==cevUninitiated)
		m_eState=cevInitiated;
	return false;
}


///////////////////////////////////////////////////////////
// Function name	: CEvRealTime::check
// Description	    : 
// Return type		: bool 
// Argument         : long iLeft
// Argument         : long iRight
// Argument         : vector<CToken*>& vExpLine
// Argument         : ostream& osErrReport
///////////////////////////////////////////////////////////
bool CEvRealTime::check(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport )
{
	bool bResult = true;

	ASSERT2(iLeft<=iRight);
	if (iLeft>iRight)
			return false;

	if (vExpLine.size()<iRight)
			{
			if (vExpLine.size()>0)
				{
				osErrReport <<"<Error*> format error with realtime Event on line "<<vExpLine[0]->getLine()<<" ."<<endl;
				SYMERRORTOK("Format error with realtime event",errSyntax,vExpLine[0]);
				}
				else
				{
				osErrReport <<"<Error*> format error with realtime Event on line."<<endl;
				SYMERRORLITE("Format error with realtime event",errSyntax);
				}
			return false;
			}

	if ((iRight-iLeft)<0) // this would indicate a bad intenral error
			{
			ASSERT2((iRight-iLeft)>=0);
			osErrReport << "<Internal Error*> Reading realtime event has caused an internal error";
			if (vExpLine.size()>0)
				osErrReport <<" on line "<< vExpLine[0]->getLine();
			osErrReport <<".\n";
			SYMERRORTOK("Error whilst reading realtime event",errInternal,vExpLine[0]);
			return false;
			}

	if ((iRight-iLeft)==0) // g_RealTime by itself is acceptable
			return true;

	// the left most term MUST now be a number
	if ((!vExpLine[iLeft]->IsOfType(ctNumber))||(vExpLine[iLeft]->getNumber()<=0))
			{
			osErrReport << "<Error*> Pace statment must e followed by a positive number '";
			osErrReport << vExpLine[iLeft]->getString().c_str() <<"' in line "<<vExpLine[iLeft]->getLine()<<".\n";
			SYMERRORTOK("Pace statement must be followed by a positive number",errSyntax,vExpLine[iLeft]);
			bResult = false;
			}
	
	return bResult;
}