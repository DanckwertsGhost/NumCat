// SimRun.cpp: implementation of the CSimRun class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SimRun.h"
#include "Symlix/ErrorFactory.h"
#include <limits>


#ifndef NDEBUG
#include "assert.h"
#include <fstream>
#include <algorithm>

#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSimRun::CSimRun(CIModelSim* im, CSolver* sol):m_pIModel(im),m_pSolver(sol)
{
#ifndef NDEBUG
	assert(m_pIModel);
	assert(m_pSolver);
#endif

	if (!m_pIModel)
			throw newtrack CExceptionSimulation("CSimRun:: No model passed to simulator");
	if (!m_pSolver)
			throw newtrack CExceptionSimulation("CSimRun:: No solver passed to simulator");
}

CSimRun::~CSimRun()
{

}


///////////////////////////////////////////////////////////
// Function name	: CSimRun::runSimulation
// Description	    : see above
// Return type		: bool 
// Argument         : variable tCutOff/*=100*/
///////////////////////////////////////////////////////////
bool CSimRun::runSimulation(CIDataServicesCallBack& iCallServBack, variable tCutOff/*=100*/) // need to give a default
{
	bool bContinue = true;
	bool bCheckEvents = true;
	vector< variable > vecV1;
	vector< variable > vecV2;
	variable vTempTimeStep = -1;
	bool bRepeat = false;
	variable vMaxStep=-1;
//	variable vLocalCutOff=100;
	vector< varStrongType >* pvecStrongTypes;
	long iInd=0; // as a safe default
#ifndef NDEBUG
	ostream_iterator<variable> out(cout," "); // see p53 STL book
#endif
	vector< variable >::const_iterator cit;
	static variable vNegInf = numeric_limits<variable>::infinity()*(-1);


	ASSERT2(numeric_limits<variable>::has_infinity);
	ASSERT2(numeric_limits<variable>::has_signaling_NaN);
	ASSERT2(numeric_limits<variable>::has_quiet_NaN);


	#ifndef CRASHHARD
	try
	#endif
	{

		ASSERT2(m_pIModel->isReady());

		if (!m_pIModel->isReady())
				return false;

		vecV1.resize(m_pIModel->getModelSize(),0);
		vecV2.resize(m_pIModel->getModelSize(),0);

		iInd = m_pIModel->getIndIndex();

		m_pSolver->setup(m_pIModel);
		// prepare value
		m_pIModel->prepareSimulation(&vecV1);

		m_pIModel->updateValue(&vecV1); // moved 16 before checkEvents so events can start reports if necessary based on start values

		bContinue = !m_pIModel->checkEvents(&vecV1,&vecV1); // as really refering to a copy of self anyway

		iCallServBack.startDataServices();

		pvecStrongTypes = m_pIModel->getpVecStrongTypes();
//		m_pIModel->updateValue(&vecV1); old position
					
		vector< variable >* pvecV1 = &vecV1;
		if (m_pIModel->getMaxSolverStep(vMaxStep))
				m_pSolver->setMaxStep(vMaxStep);
		#ifndef NDEBUG
				else
				ASSERT2(vMaxStep==NOT_DEFINED);
		#endif

	#ifdef EXTRADEBUG
		variable timeNow=static_cast<variable>(NOT_DEFINED);
	#else
		#ifndef NDEBUG
		variable timeNow=static_cast<variable>(NOT_DEFINED);
		#endif
	#endif

#ifndef NDEBUG 
		while((bContinue)&&(vecV1[iInd]<tCutOff))
#else
		while(bContinue)
#endif
		{
			copy(vecV1.begin(),vecV1.end(),vecV2.begin());

	//		Check timing goes here m_pIModel->checkTiming perhaps - think about it
			vTempTimeStep = m_pSolver->nextIndVarStep();
			if (m_pIModel->ensureEventsSync(pvecV1,vTempTimeStep))
					m_pSolver->overrideNextIndVarStep(vTempTimeStep);

	//		#ifndef NDEBUG
	//		cout << "vecV1[5] Before = "<<vecV1[5];
	//		cout<<"Before ::";copy(vecV1.begin(),vecV1.end(),out);cout << endl;
	//		#endif
	#ifdef EXTRADEBUG
			timeNow = m_pSolver->step(pvecV1/*&vecV1*/,pvecStrongTypes);
			cout << timeNow << endl;
	#else
			try
			{
#ifndef NDEBUG
			timeNow = m_pSolver->step(pvecV1/*&vecV1*/,pvecStrongTypes);
			


#else
			m_pSolver->step(pvecV1/*&vecV1*/,pvecStrongTypes);
#endif

			for (cit=vecV1.begin();cit!=vecV1.end();cit++)
				{
/*				variable v = (*cit);
				ATLTRACE("%f *cit\n",(*cit));
				cout << "v="<< v << endl;
				cout << "numeric_limits<variable>::quiet_NaN()="<< numeric_limits<variable>::quiet_NaN() << endl;
				if (v==numeric_limits<variable>::signaling_NaN())
						ATLTRACE("v==numeric_limits<variable>::signaling_NaN()\n");
				if (v==numeric_limits<variable>::quiet_NaN())
						ATLTRACE("v==numeric_limits<variable>::quiet_NaN()\n");
				if (v==numeric_limits<variable>::infinity())
						ATLTRACE("v==numeric_limits<variable>::infinity()\n");
				if (v==vNegInf)
						ATLTRACE("v==vNegInf\n");*/
				if(((*cit)==numeric_limits<variable>::signaling_NaN())||
//				   ((*cit)==numeric_limits<variable>::quiet_NaN())||
				   ((*cit)==numeric_limits<variable>::infinity())||
				   ((*cit)==vNegInf))
						{
						if (!bRepeat)
							throw newtrack CExceptionCVarRoot("Out of bounds numerical value created");
							else
							{
							SYMERRORLITE("Out of bounds numerical value created",errSystem);
							throw newtrack CExceptionCVarRoot("One result has numerical overflow");
							}
						}
				} // end 	for (cit=vecV1.begin();cit!=vecV1.end();cit++)


			bRepeat = false;
			}
			catch(CExceptionCVarRoot* pcecvr)
				{
				if (!m_pSolver->isVariableStep()) // then there's nothing to be done
						throw pcecvr;

				if (bRepeat) // then we're caught in a loop - time to fail
						{
						SYMERRORLITE2("Solver :","Attempt to reduce step length did not prevent error",errWarning);
						throw pcecvr;
						}
				bRepeat=true;
				// try reducing step size
				vTempTimeStep/=static_cast<variable>(10);
				if (m_pSolver->lessThanMinStep(vTempTimeStep)) // then have to give up
						{
						SYMERRORLITE2("Solver :","Attempt to reduce step length below minium accepted value",errWarning);
						throw pcecvr;
						}
				// then lets try again
				m_pSolver->setIndVarStep(vTempTimeStep);
				copy(vecV2.begin(),vecV2.end(),vecV1.begin()); // go backwards one step
				bCheckEvents=false; // as we are redoing this step
				delete pcecvr;
				}
	#endif
	//		#ifndef NDEBUG
	//		cout << " After = "<<vecV1[5]<<endl;cout.flush();
	//		cout<<"After ::";copy(vecV1.begin(),vecV1.end(),out);cout << endl;
	//		#endif
			if (bCheckEvents)
				bContinue = !m_pIModel->checkEvents(&vecV1,&vecV2);
				else
				bCheckEvents = true;
		}

	}
	#ifndef CRASHHARD
	catch(CExceptionCVarRoot* pcecvr)
	{
			char sTime[25];
			string sMessage;
			gcvt(vecV1[iInd],8,sTime);
			cerr << (*pcecvr) << endl;
			sMessage = pcecvr->getMessage();
			sMessage.append(" @ t = ");
			sMessage.append(sTime);
			SYMERRORLITE2(pcecvr->getHeading(),sMessage.c_str(),errSystem);
			delete pcecvr;
		// Add call back for ended data services here
			iCallServBack.endDataServices();
			m_pIModel->signalEndSimulation(vecV1);
			return false;
	}
	catch(...)
	{
			cerr << "<<Internal Error*>> Unhandled exception - contact vendor" << endl;
		// Add call back for ended data services here
			SYMERRORLITE("Unhandled exception - contact vendor",errInternal);
			iCallServBack.endDataServices();
			m_pIModel->signalEndSimulation(vecV1);
			return false;
	}
	#endif
		// Add call back for ended data services here
	iCallServBack.endDataServices();
	m_pIModel->signalEndSimulation(vecV1);

	return true; // as some events may stop a simulation 
}