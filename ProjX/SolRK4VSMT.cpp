// SolRK4VSMT.cpp: implementation of the CSolRK4VSMT class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SolRK4VSMT.h"
#include "Symlix/ErrorFactory.h"


//////////////////////////////////////////////////////////////////////
// Code for alternative solving thread
//////////////////////////////////////////////////////////////////////

#ifdef NDEBUG
#define CONTRACE //
#include <tchar.h>
#else
#define CONTRACE ATLTRACE
#endif


CSolveData::CSolveData(CSolMT& solMT,CSolver* pSolver,vectorValues* pvecValues,vectorConstrainedValues* pvecConST):
m_solMT(solMT),m_pSolver(pSolver),m_pvecValues(pvecValues),m_pvecConST(pvecConST),m_bError(true)
{
 if (m_pSolver&&m_pvecValues&&m_pvecConST)
		m_bError=false;
}

CSolveData::CSolveData(const CSolveData& csd ):
m_solMT(csd.m_solMT),m_pSolver(csd.m_pSolver),m_pvecValues(csd.m_pvecValues),m_pvecConST(csd.m_pvecConST),m_bError(csd.m_bError)
{
 
}

//#include "atlbase.h"

void SolRK4MTRunThread( void* pParams )
{ 

	bool bRun = true;
	CSolveData* psd = static_cast<CSolveData*>(pParams);
	if (!psd) // in case of balls up
			{
			// crashing out - but still need to send signal
			_endthread();
			}

	CSolveData sd(*psd); // now scope is linked here

	// signal ready to go
	SetEvent( sd.getSolMT().getRefHandleStartEvent() );


	try
	{

		do
		{
			while( WaitForSingleObject( sd.getSolMT().getRefHandleRunEvent(), INFINITE));
				{
					if (sd.getSolMT().endOfThreadRequested())
						{
						 CONTRACE(_T("Thread:- endOfThreadRequested.\n"));
						 SetEvent( sd.getSolMT().getRefHandleEndEvent() );
						 _endthread();
						}
				
					// lets calculate
					{
					CCritCheck cc(sd.getSolMT().getRefCritSecRunningState());
					CCritCheck cc2(sd.getSolMT().getRefCritSecDebugState());
					CONTRACE(_T("Thread:- About to step with this %d solver.\n"),sd.getpSolver());
					sd.getpSolver()->step(sd.getpvecValues(),sd.getpvecConsValues());
					}
					// signal have finished
					CONTRACE(_T("Thread:- SetEvent( sd.getSolMT().getRefHandleEndEvent() ).\n"));
					SetEvent( sd.getSolMT().getRefHandleEndEvent() );
				}
		CONTRACE(_T("Thread:- WaitForSingleObject.\n"));

		}
		while(bRun);

	}
	catch(...)
	{
		CONTRACE(_T("Thread:- Catch unhandled exception.\n"));
		cerr <<"<<Internal Error*>> In mutlitreaded solver."<<endl;
		SYMERRORLITE("Unhandled error in mulithread solver",errInternal);
		ASSERT2(false);
	}
	CONTRACE(_T("Thread:- _endthread line 84.\n"));		
	_endthread();

};



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSolRK4VSMT::CSolRK4VSMT():CSolRK4VS(),CSolMT(),m_SolRK4Long(),m_vecDecoy(),m_bThread(false)
{
	launchThread();
	
}

CSolRK4VSMT::CSolRK4VSMT(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport ):
CSolRK4VS(iLeft,iRight,vExpLine,osErrReport),m_SolRK4Long(),m_vecDecoy(),m_bThread(false)
{
	launchThread();

}


CSolRK4VSMT::~CSolRK4VSMT()
{
	killThread();

}

void CSolRK4VSMT::launchThread()
{
// so this can be called only once and only I thread exists
	if (m_bThread)
		return;
	m_bThread=true;

#ifndef NDEBUG
	m_iCountVecSize = NOT_DEFINED;
#endif	

	CSolveData csd(*this,&m_SolRK4Long,&m_vecLargerJump,&m_vecDecoy);

	unsigned long ithrd = _beginthread(SolRK4MTRunThread,0,&csd);
	if (ithrd==-1) // then thread has failed
		{
		 // go with back up single thread plan
		 m_bMT = false;
		}
		else
		{
		 WaitForSingleObject( this->getRefHandleStartEvent(), INFINITE );
		 ResetEvent(this->getRefHandleStartEvent()); // may not be necessary
		 m_bMT = true;
		}

}



///////////////////////////////////////////////////////////
// Function name	: CSolRK4VSMT::killThread
// Description	    : try to get rid of the thread
// Return type		: void 
///////////////////////////////////////////////////////////
void CSolRK4VSMT::killThread()
{

	this->requestEndOfThread();
	SetEvent(this->getRefHandleRunEvent()); // need to turn the handle here
	DWORD dw = WaitForSingleObject( this->getRefHandleEndEvent(), 4000 );
	if (dw==WAIT_TIMEOUT)
		{
		#ifndef NDEBUG
		cerr<<"<<Internal Error*>> Thread did not time out in ~CSolRK4VSMT()"<<endl;
		//ASSERT2(false);
		SYMERRORLITE("Thread did not time out in multithread solver",errSystem);
		#else
		SYMERRORLITE("Thread did not time out in multithread solver",errWarning);
		#endif
		}

}



///////////////////////////////////////////////////////////
// Function name	: CSolRK4VSMT::check
// Description	    : 
// Return type		: bool 
// Argument         : long iLeft
// Argument         : long iRight
// Argument         : vector<CToken*>& vExpLine
// Argument         : ostream& osErrReport/*=cerr*/
///////////////////////////////////////////////////////////
bool CSolRK4VSMT::check(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport/*=cerr*/ )
{

	return CSolRK4VS::check(iLeft,iRight,vExpLine,osErrReport);
}




///////////////////////////////////////////////////////////
// Function name	: CSolRK4VSMT::setup
// Description	    : 
// Return type		: bool 
// Argument         : CIModelSim* pims
///////////////////////////////////////////////////////////
bool CSolRK4VSMT::setup(CIModelSim* pims)
{

	if (!CSolRK4VS::setup(pims))
		return false;
	
	if (!m_SolRK4Long.setup(pims)) // need to check this solver
			return false;

	return true;
}

///////////////////////////////////////////////////////////
// Function name	: CSolRK4VSMT::step
// Description	    : 
// Return type		: xt_value 
// Argument         : vectorValues* pvecValues
// Argument         : vectorConstrainedValues* pvecConST
///////////////////////////////////////////////////////////
xt_value CSolRK4VSMT::step(vectorValues* pvecValues,vectorConstrainedValues* pvecConST )
{

	bool bDidNotDropStep=true;

	if (!m_bMT)
		return CSolRK4VS::step(pvecValues,pvecConST);

#ifndef NDEBUG // ensure contraints array always same size
	if (m_iCountVecSize!=NOT_DEFINED)
		ASSERT2(m_iCountVecSize==pvecConST->size());
		else
		m_iCountVecSize=pvecConST->size();
#endif	

	if (m_vecDecoy.size()==0) // assumed pvecConSTR will always be constant
			{
			m_vecDecoy.resize(pvecConST->size());
			copy(pvecConST->begin(),pvecConST->end(),m_vecDecoy.begin());
			}


	xt_value xtvJ1,xtvJ2,xtTemp,xtError;
	long iV;


#ifndef NDEBUG // clearly don't want to do this in release solve mode
	assert(m_iSize!=NOT_DEFINED);
	assert(m_pIModelSim);
	assert(m_pIModelSim->isReady());
#endif

	if (m_bOverRideNext) // in case need to predict to a precise point - has more meaning for variable steps
		{
		xtTemp = m_tstep;
		m_tstep = m_xtOverRide;
		}

	CONTRACE(_T("Main:- step.\n"));
	long iTempCount=0;

	do
	{
		CONTRACE(_T("Main:- loop step %d.\n"),iTempCount++);

		// set the other thread of first
		ASSERT2(pvecValues->size()==m_vecLargerJump.size());
		{
		CCritCheck cc(this->getRefCritSecRunningState());
		copy(pvecValues->begin(),pvecValues->end(),m_vecLargerJump.begin());
		}
		//calc larger jump - to go into another thread latter
		{
		 m_SolRK4Long.setIndVarStep(m_tstep);
		 // old code m_SolRK4.step(&m_vecLargerJump,pvecConST);
		 // request thread pump
		 SetEvent( this->getRefHandleRunEvent());
		}


		xtvJ1 = m_tstep/static_cast<xt_value>(2);
		xtvJ2 = m_tstep - xtvJ1; // to catch any numerical rouding stuff

		ASSERT2((xtvJ1+xtvJ2)==m_tstep);

		ASSERT2(pvecValues->size()==m_vecSmallerJump.size());
		copy(pvecValues->begin(),pvecValues->end(),m_vecSmallerJump.begin());

		// calc smaller steps
		#ifndef NDEBUG
		#ifndef CRASHHARD
		try
		#endif
		#endif
		{
		 //CCritCheck cc(this->getRefCritSecDebugState());
		 CONTRACE("Main:- About to call smaller steps RK4 is %d\n",&m_Sol);
		 CONTRACE("Main:- check size vecsmaller %d, constaints %d\n",m_vecSmallerJump.size(),pvecConST->size());
		 CONTRACE("Main:- setIndVarStep(%g)\n",xtvJ1);
		 m_Sol.setIndVarStep(xtvJ1);
		 CONTRACE("Main:- step(%d,%d)\n",&m_vecSmallerJump,pvecConST);
		 m_Sol.step(&m_vecSmallerJump,pvecConST);
		 CONTRACE("Main:- setIndVarStep(%g)\n",xtvJ2);
		 m_Sol.setIndVarStep(xtvJ2);
		 CONTRACE("Main:- step(%d,%d)\n",&m_vecSmallerJump,pvecConST);
		 m_Sol.step(&m_vecSmallerJump,pvecConST);
		 CONTRACE("Main:- Finished calling smaller steps\n");
		}
		#ifndef NDEBUG
		#ifndef CRASHHARD
		catch(...)
		{
		CONTRACE(_T("Main:- Unhandled exception caught.\n"));
		ASSERT2(false);
		}
		#endif
		#endif


		// make sure event has completed
		CONTRACE(_T("Main:- About to wait for thread EndEvent.\n"));
		DWORD dw = WaitForSingleObject(this->getRefHandleEndEvent(),4000);
		CONTRACE(_T("Main:- Signal recieved from thread End.\n"),dw);
		if (dw!=WAIT_OBJECT_0) // bugger
				{
				// ok MT not working well - drop out to single thread
				m_bMT=false;
				return CSolRK4VS::step(pvecValues,pvecConST);
				}
		ResetEvent(this->getRefHandleEndEvent());


		m_vError = 0;
		#ifndef NDEBUG
		xtError = 0;// not needed - but make debuging easier
		#endif
		// find largest error
		for(long iC=m_iVarStart;iC<(m_iSize+m_iVarStart);iC++)
			{
			iV = iC-m_iVarStart;
			m_vecErrors[iV] = (m_vecSmallerJump[iC] - m_vecLargerJump[iC]);
			m_vecSmallerJump[iC] += m_vecErrors[iV]/static_cast<xt_value>(15); // adding correction

			// Find largest relative error - ignoring cases where the value is close to zero
			if (fabs(m_vecSmallerJump[iC])>DEFAULT_SMALL_NUMBER)
					{
					xtError = fabs(m_vecErrors[iV]/m_vecSmallerJump[iC]);
					if (xtError>m_vError)
							m_vError = xtError;
					}

			}

		// calculate new time step indicated

		// calculate new time step indicated
		if ((m_vError>DEFAULT_SMALL_NUMBER)||(m_vError>m_vTolerance))
						{
						bDidNotDropStep=false;
						m_tstep *= m_vTolerance/m_vError;
						}
						else
						if (m_tstep!=m_tmax)
							{
							m_tstep *=static_cast<xt_value>(2.0);
							if (m_tstep>m_tmax)
								m_tstep=m_tmax;
							}
/*
#ifdef EXPERIMENT_STEPADJUST


		if ((m_vError>DEFAULT_SMALL_NUMBER)||(m_vError>m_vTolerance))
					{
					bDidNotDropStep=false;
					m_tstep *= m_vTolerance/m_vError;
					m_iPogoLast = m_iPogoLast*0.9F + m_iPogo*0.1F;
					m_iPogo = 0;
					}
					else
					{
					if (m_tstep!=m_tmax)
						{
						if (m_iPogo<10000)
								m_iPogo++;
						if ((m_iPogo<30)&&(m_iPogoLast<30))
							{
							if (m_vError<m_vTolerance10)
								m_tstep *=1.05F;
								else
								if (m_vError<m_vTolerance90)
									m_tstep *= 1.01F;
									else
									m_tstep *= 1.001F;
							}
							else
							if (m_iPogoLast<80)
									{
									if (m_vError<m_vTolerance10)
										m_tstep *=1.10F;
										else
										if (m_vError<m_vTolerance90)
											m_tstep *= 1.05F;
											else
											m_tstep *= 1.001F;
									}
									else
									{
									if (m_vError<m_vTolerance10)
										m_tstep *=1.5F;
										else
										if (m_vError<m_vTolerance90)
											m_tstep *= 1.01F;
											else
											m_tstep *= 1.001F;
									}

						if (m_tstep>m_tmax)
							m_tstep=m_tmax;
						}
					}
#endif*/
		CONTRACE(_T("Main:- loop check error %g.\n"),m_vError);

	}
	while (m_vError>m_vTolerance); 


#ifdef EXTRADEBUG
	cout << "m_vError = "<<m_vError<<", m_vTolerance = "<<m_vTolerance<<", m_tstep = "<<m_tstep<<endl;
	
#endif

	// update new values
	copy(m_vecSmallerJump.begin(),m_vecSmallerJump.end(),pvecValues->begin());


	if (m_bOverRideNext)
		{
		if (bDidNotDropStep)
				m_tstep = xtTemp;
		m_bOverRideNext = false;
		}

	CONTRACE(_T("Main:- end of step %d.\n"),iTempCount);

	return (*pvecValues)[m_iIndVar];
}