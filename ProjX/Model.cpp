// Model.cpp: implementation of the CModel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Model.h"
#ifndef NDEBUG
#include "assert.h"
#endif
#include <algorithm>
#include "CritCheck.h"
#include "EventFactory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CModel::CModel():m_eState(eMSUnintialised),
m_iEndInd(m_iBeginDeriv),m_iEndDeriv(m_iBeginDep),m_iEndDep(m_iBeginSubs),m_iEndSubs(m_iEndIndex),m_iTimeInd(NOT_DEFINED)
{
	InitializeCriticalSection(&m_csUpdateValues); // needed to prevent access violations latter

}


CModel::~CModel()
{

}



///////////////////////////////////////////////////////////
// Function name	: CModel::intialiseTokens
// Description	    : Set up indexs for variables and record divisions between them.
//                    Returns false if not in state to under take this task.
// Return type		: bool 
// Argument         : vector<CToken* >& vecIndVar
// Argument         : vector<CToken* >& vecDeriv
// Argument         : vector<CToken*>& vecDepVar
// Argument         : vector<CToken*>& vecSubsVar
// Argument			: CStrongTypeFactory* pstf // passed even though singleton for clarity
///////////////////////////////////////////////////////////
bool CModel::intialiseTokens(vector<CToken* >& vecIndVar,vector<CToken* >& vecDeriv, vector<CToken*>& vecDepVar,vector<CToken*>& vecSubsVar, CStrongTypeFactory* pstf )
{

	long iIndex = 0;
	vector< CToken* >::iterator itv;


	if (m_eState!=eMSUnintialised)
				return false;

	// first the Independant variables - time
	m_iBeginInd = iIndex; // just to make the logic more readable
	for(itv=vecIndVar.begin();itv!=vecIndVar.end();itv++)
			{
			(*itv)->getRootTokenPt()->setIndex(iIndex++);
			// if it a g_Time type then we need to record the index. There must be one time type
			if ((*itv)->getRootTokenPt()->getStringRef().compare(g_Time)==0)
					m_iTimeInd = (*itv)->getRootTokenPt()->getIndex();
			}

	#ifdef EXTRADEBUG
	cout << "gTime = " << m_iTimeInd <<endl;
	#endif

	ASSERT2(m_iTimeInd!=NOT_DEFINED);
	if (m_iTimeInd==NOT_DEFINED)
		return false;

	m_iBeginDeriv = iIndex;
	for(itv=vecDeriv.begin();itv!=vecDeriv.end();itv++)
			(*itv)->getRootTokenPt()->setIndex(iIndex++);

	m_iBeginDep = iIndex;
	for(itv=vecDepVar.begin();itv!=vecDepVar.end();itv++)
			(*itv)->getRootTokenPt()->setIndex(iIndex++);

	m_iBeginSubs = iIndex;
	for(itv=vecSubsVar.begin();itv!=vecSubsVar.end();itv++)
			(*itv)->getRootTokenPt()->setIndex(iIndex++);
	m_iEndIndex = iIndex;


	#ifndef NDEBUG // to help in debuging
	assert(m_iBeginInd<=m_iBeginDeriv);
	assert(m_iBeginDeriv<=m_iBeginDep);
	assert(m_iBeginDep<=m_iBeginSubs);
	assert(m_iBeginSubs<=m_iEndIndex); // as there could be no subs
	assert(m_iBeginInd<m_iEndIndex);
	#endif

	// now set any specific type information
	m_vecStrongTypes.clear();
	ASSERT2(m_vecStrongTypes.size()==0);

	m_vecStrongTypes.resize(m_iEndIndex,0);
	ASSERT2(m_vecStrongTypes.size()==m_iEndIndex);

	iIndex=0;
	for(itv=vecIndVar.begin();itv!=vecIndVar.end();itv++)
			pstf->assignTypeFor((*itv)->getString(),m_vecStrongTypes[iIndex++]);

	for(itv=vecDeriv.begin();itv!=vecDeriv.end();itv++)
			pstf->assignTypeFor((*itv)->getString(),m_vecStrongTypes[iIndex++]);

	for(itv=vecDepVar.begin();itv!=vecDepVar.end();itv++)
			pstf->assignTypeFor((*itv)->getString(),m_vecStrongTypes[iIndex++]);

	for(itv=vecSubsVar.begin();itv!=vecSubsVar.end();itv++)
			pstf->assignTypeFor((*itv)->getString(),m_vecStrongTypes[iIndex++]);

	ASSERT2(iIndex==m_vecStrongTypes.size());

	m_eState = eMSInitIndexes;

	return true;

}



///////////////////////////////////////////////////////////
// Function name	: CModel::intialiseEquations
// Description	    : 
// Return type		: bool 
// Argument         : list<CEquation>* pvecEquations
///////////////////////////////////////////////////////////
bool CModel::intialiseEquations(list<CEquation*>* pvecpEquations)
{
	bool bResult=true;
	list<CEquation*>::iterator itpEq;
	
	ASSERT2(m_eState==eMSInitIndexes); // must be true
	ASSERT2(pvecpEquations);

	if (m_eState!=eMSInitIndexes)
			return false;
	
#ifdef EQSTOPOPTION
	prepareEquations(pvecpEquations);
#endif // #ifdef EQSTOPOPTION

	#ifndef NDEBUG
	cerr << "Equations:\n";
	for(itpEq=pvecpEquations->begin();itpEq!=pvecpEquations->end();itpEq++)
		cerr << (**itpEq) <<endl;
	cerr << endl; cerr.flush();
	#endif

	for(itpEq=pvecpEquations->begin();(bResult)&&(itpEq!=pvecpEquations->end());itpEq++)
		bResult = (*itpEq)->setupExpression(pvecpEquations,CVarClassFactory::instance(),cerr);

	if (bResult)
			{
			m_eState = eMSInitEquations;
			for(itpEq=pvecpEquations->begin();itpEq!=pvecpEquations->end();itpEq++)
					this->push_back(*itpEq);
			}

	#ifndef NDEBUG
	cerr << "end  CModel::intialiseEquations\n";
	#endif

	return bResult;

}


///////////////////////////////////////////////////////////
// Function name	: CModel::intialiseEvents
// Description	    : Initialise EvEvents only - will need to be adjusted for other types
// Return type		: bool 
// Argument         : vector<CEvValue>* pvecEvValues
///////////////////////////////////////////////////////////
bool CModel::intialiseEvents(vector<CEvent*>* pvecpEvents,list<CEquation*>* pvecpEquations)
{

	bool bResult = true;
	vector<CEvent*>::iterator itpEv;

	ASSERT2(m_eState!=eMSUnintialised);
	if (m_eState==eMSUnintialised)
			return false;

	// make a stronger check
	ASSERT2(m_eState==eMSInitEquations);

	m_vpEvents.clear();
	m_vpPreciseEvents.clear();
	m_vpActiveEvents.clear();
	m_vpPassiveEvents.clear();
	m_vpLastEvents.clear();
	m_vpEvents.resize(pvecpEvents->size());
	copy(pvecpEvents->begin(),pvecpEvents->end(),m_vpEvents.begin());
	ASSERT2(pvecpEvents->size()==m_vpEvents.size());

	ASSERT2(m_iTimeInd!=NOT_DEFINED); // otherwise can't get some events to work
	if (m_iTimeInd==NOT_DEFINED) // have to cover this for release code also
						return false;

	for (itpEv=pvecpEvents->begin();((bResult)&&(itpEv!=pvecpEvents->end()));itpEv++)
		{
		bResult = (*itpEv)->setupEvent(pvecpEquations);
		if ((*itpEv)->hasAPreciseTimeTrigger(m_iTimeInd))
				m_vpPreciseEvents.push_back((*itpEv)); // make a copy of it
		if ((*itpEv)->isActive())
/*				if ((*itpEv)->isOfType(ceetValueChangeAfterStart))
						m_vpLastEvents.push_back((*itpEv));
						else*/
						m_vpActiveEvents.push_back((*itpEv));
				else
				m_vpPassiveEvents.push_back((*itpEv));
		}
	ASSERT2(m_vpEvents.size()==m_vpActiveEvents.size()+m_vpPassiveEvents.size()+m_vpLastEvents.size());


	if (bResult)
			m_eState = eMSInitAll;


 return bResult;
}


///////////////////////////////////////////////////////////
// Function name	: CModel::addUserRequestedEvents
// Description	    : 
// Return type		: bool 
// Argument         : vector<CEvent*>*  pvecpEvents
///////////////////////////////////////////////////////////
bool CModel::addUserRequestedEvents( vector<CEvent*>&  vecpEvents )
{

	vector<CEvent*>::iterator it;

#ifndef NDEBUG
	long iCount = m_vpEvents.size() + vecpEvents.size();


	for ( it=m_vpEvents.begin();it!=m_vpEvents.end();it++)
		{
		ATLTRACE("Before Event loc %d %d\n",it,(*it));
		}
	ATLTRACE("Size of array before = %d\n",m_vpEvents.size());

#endif


	ASSERT2(m_eState==eMSInitAll);
	if (m_eState!=eMSInitAll)
			return false;


#ifndef NDEBUG

	for ( it=m_vpEvents.begin();it!=m_vpEvents.end();it++)
		{
		ATLTRACE("Event loc %d %d\n",it,(*it));
		}
	ATLTRACE("Size of array after resize = %d\n",m_vpEvents.size());

	for ( it=vecpEvents.begin();it!=vecpEvents.end();it++)
		{
		ATLTRACE("USER Event loc %d %d\n",it,(*it));
		}

#endif

	for(it=vecpEvents.begin();it!=vecpEvents.end();it++)
			{
			m_vpEvents.push_back(*it);
			m_vpTempEvents.push_back(*it); // so they can be removed easily
			}


#ifndef NDEBUG

	for ( it=m_vpEvents.begin();it!=m_vpEvents.end();it++)
		{
		ATLTRACE("Event loc %d %d\n",it,(*it));
		}
	ATLTRACE("Size of array after copy = %d\n",m_vpEvents.size());
	
	ASSERT2(iCount==m_vpEvents.size());

#endif

	return true;

}

///////////////////////////////////////////////////////////
// Function name	: CModel::TestModel
// Description	    : Tempory test routine - heavily coppled with a certain test file
//                    should not normally be used.
// Return type		: bool 
// Argument         : vector<CToken* >* pvecTokens
// Argument         : vector<CEquation>* pvecEquations
// Argument         : vector<CEvValue>* pvecEvValues
///////////////////////////////////////////////////////////
bool CModel::TestModel(list<CEquation*>* pvecpEquations, vector<CEvent*>* pvecpEvents)
{
	bool bResult = true;

	vector< variable > vecV(m_iEndIndex);
	vector< variable >::iterator itvV;
	vector<CEvent*>::iterator itvpEv;
	list<CEquation*>::iterator itvpEq;


	ostream_iterator<variable> out(cout," "); // see p53 STL book



	for (itvV=vecV.begin();itvV!=vecV.end();itvV++)
		(*itvV) = 0;	

	copy(vecV.begin(),vecV.end(),out); cout << endl;

	// prepare events
	for (itvpEv=pvecpEvents->begin();itvpEv!=pvecpEvents->end();itvpEv++)
		{
		 (*itvpEv)->reset();
		 (*itvpEv)->prepareForSimulation(&vecV,cerr);

		}


	// check events
	for (itvpEv=pvecpEvents->begin();itvpEv!=pvecpEvents->end();itvpEv++)
			(*itvpEv)->trigger(&vecV,NULL);

	copy(vecV.begin(),vecV.end(),out); cout << endl;

	CVarRoot::stepGlobalCache();

	for (itvpEq=pvecpEquations->begin();itvpEq!=pvecpEquations->end();itvpEq++)
	{
			cout << **itvpEq<<endl;cout.flush();
			(*itvpEq)->updateValue(&vecV);
	}

	CVarRoot::switchCacheOff();

	copy(vecV.begin(),vecV.end(),out); cout << endl;

	// lets try a RK4 time step

	vector<variable> vecK1;
	vector<variable> vecK2;
	vector<variable> vecK3;
	vector<variable> vecK4;

cout <<	m_iBeginInd << " m_iBeginInd\n";
cout <<	m_iBeginDeriv << " m_iBeginDeriv\n";
cout <<	m_iBeginDep << " m_iBeginDep\n";
cout <<	m_iBeginSubs << " m_iBeginSubs\n";
cout << m_iEndIndex << " m_iEndIndex\n";

	variable& t = vecV[m_iBeginInd];
#ifdef EQSTOPOPTION
	CEquation::setStartTimeData(t); // in case its needed
#endif // #ifdef EQSTOPOPTION
	variable tstep = 0.01;
	long lLen = m_iEndDeriv-m_iBeginDeriv;
	long iT;
	cout << t << " t\t"<< tstep<<" tstep\n";;
	
	vecK1.resize(m_iEndDeriv-m_iBeginDeriv);
	vecK2.resize(m_iEndDeriv-m_iBeginDeriv);
	vecK3.resize(m_iEndDeriv-m_iBeginDeriv);
	vecK4.resize(m_iEndDeriv-m_iBeginDeriv);

	copy(&vecV[m_iBeginDeriv],&vecV[m_iEndDeriv],vecK1.begin());
	//vecK1.erase(&vecK1[m_iEndDeriv-m_iBeginDeriv],vecK1.end());

    cout << vecK1.size() << endl << "k1 ";
	copy(vecK1.begin(),vecK1.end(),out); cout << endl;

	cout << "update from k1 ";
	for(iT=0;iT<lLen;iT++)
		vecV[m_iBeginDep+iT] += 0.5*tstep*vecK1[iT];
	t += 0.5*tstep;
	copy(vecV.begin(),vecV.end(),out); cout << endl;

	CVarRoot::stepGlobalCache();
	
	for (itvpEq=pvecpEquations->begin();itvpEq!=pvecpEquations->end();itvpEq++)
	{
	//		cout << *itvEq<<endl;cout.flush();
			(*itvpEq)->updateValue(&vecV);
	}
	copy(&vecV[m_iBeginDeriv],&vecV[m_iEndDeriv],vecK2.begin());
    cout << vecK2.size() << endl << "k2 ";
	copy(vecK2.begin(),vecK2.end(),out); cout << endl;


	cout << "update from k2 ";
	for(iT=0;iT<lLen;iT++)
		vecV[m_iBeginDep+iT] += 0.5*tstep*vecK2[iT];
	t += 0.5*tstep;
	copy(vecV.begin(),vecV.end(),out); cout << endl;

	CVarRoot::stepGlobalCache();

	for (itvpEq=pvecpEquations->begin();itvpEq!=pvecpEquations->end();itvpEq++)
	{
	//		cout << *itvEq<<endl;cout.flush();
			(*itvpEq)->updateValue(&vecV);
	}
	copy(&vecV[m_iBeginDeriv],&vecV[m_iEndDeriv],vecK3.begin());
    cout << vecK3.size() << endl << "k3 ";
	copy(vecK3.begin(),vecK3.end(),out); cout << endl;

	cout << "update from k3 ";
	for(iT=0;iT<lLen;iT++)
		vecV[m_iBeginDep+iT] += 0.5*tstep*vecK3[iT];
	t += 0.5*tstep;
	copy(vecV.begin(),vecV.end(),out); cout << endl;

	CVarRoot::stepGlobalCache();

	for (itvpEq=pvecpEquations->begin();itvpEq!=pvecpEquations->end();itvpEq++)
	{
	//		cout << *itvEq<<endl;cout.flush();
			(*itvpEq)->updateValue(&vecV);
	}

	CVarRoot::switchCacheOff();


	copy(&vecV[m_iBeginDeriv],&vecV[m_iEndDeriv],vecK4.begin());
    cout << vecK4.size() << endl << "k4 ";
	copy(vecK4.begin(),vecK4.end(),out); cout << endl;
    cout << "end of CModel Test"<<endl;cout.flush();

	// clean up
#ifdef EQSTOPOPTION
	prepareEquations(pvecpEquations);
#endif //#ifdef EQSTOPOPTION

	return bResult;
}

bool CModel::getModelIndexs(long& iIndVar, long& iDeriveStart, long& iDerivEnd,long& iVarStart, long& iVarEnd)
{
	iIndVar = getIndIndex();
	iDeriveStart = m_iBeginDeriv;
	iDerivEnd = m_iEndDeriv;
	iVarStart = m_iBeginDep;
	iVarEnd = m_iEndDep;

	if (m_eState==eMSUnintialised)
			return false;

	return true;
}

void CModel::push_back(CIEquaSim* es)
{
	if (es)
		m_vecES.push_back(es);

}

bool CModel::isReady()
{

	return ((m_vecES.size()>0)&&(m_eState==eMSInitAll));
}

bool CModel::updateValue(vectorValues* vecValues  )
{
	bool bResult = true;

	CCritCheck cc(m_csUpdateValues); // needed to make sure this is done one at a time
	
	CVarRoot::stepGlobalCache(); // to avoid unnecessary recalculations

	for(m_itvecES=m_vecES.begin();m_itvecES!=m_vecES.end();m_itvecES++)
			bResult &= ((*m_itvecES)->updateValue(vecValues)!=CANNOT_EVALUATE);

	CVarRoot::switchCacheOff(); // in case something else is going on latter

	return bResult;
}	

long CModel::getModelSize() const
{
	return m_iEndIndex;
}	


///////////////////////////////////////////////////////////
// Function name	: CModel::prepareSimulation
// Description	    : 
// Return type		: bool 
// Argument         : vectorValues* pvecValues
///////////////////////////////////////////////////////////
bool CModel::prepareSimulation(vectorValues* pvecValues)
{
 vector< CEvent* >::iterator itpEv;

 ASSERT2(pvecValues);
 if (!pvecValues)
	return false;

 ASSERT2(m_iTimeInd!=NOT_DEFINED);
 if (m_iTimeInd==NOT_DEFINED)
	return false;

 ASSERT2(pvecValues->size()>m_iTimeInd);
 if (pvecValues->size()<=m_iTimeInd)
	return false;

#ifdef EQSTOPOPTION
 CEquation::setStartTimeData((*pvecValues)[m_iTimeInd]);
#endif // #ifdef EQSTOPOPTION

 for(itpEv=m_vpEvents.begin();itpEv!=m_vpEvents.end();itpEv++)
		(*itpEv)->reset();

 for(itpEv=m_vpEvents.begin();itpEv!=m_vpEvents.end();itpEv++)
		{
		(*itpEv)->prepareForSimulation(pvecValues,cerr);
		(*itpEv)->setStrongType(m_vecStrongTypes);
		}

 for(m_itvecES=m_vecES.begin();m_itvecES!=m_vecES.end();m_itvecES++)
		(*m_itvecES)->setStrongType(m_vecStrongTypes);

 return true;

}


///////////////////////////////////////////////////////////
// Function name	: CModel::checkEvents
// Description	    : 
// Return type		: bool 
// Argument         : vectorValues* pvecValues
// Argument         : vectorValues* pvecValuesLast
///////////////////////////////////////////////////////////
bool CModel::checkEvents(vectorValues* pvecValues,vectorValues* pvecValuesLast )
{
 vector< CEvent* >::iterator itpEv;
 bool bStop = false;
 bool bRecalc = false;

/*
 for(itpEv=m_vpEvents.begin();itpEv!=m_vpEvents.end();itpEv++)
	if ((*itpEv)->trigger(pvecValues,pvecValuesLast)==ceesEndSimulation)
		bStop=true;
*/

 for(itpEv=m_vpActiveEvents.begin();itpEv!=m_vpActiveEvents.end();itpEv++)
	switch( (*itpEv)->trigger(pvecValues,pvecValuesLast) )
		{
		case ceesEndSimulation:
			bStop = true;
			bRecalc = true;
			break;
		case ceesTrig:
			bRecalc = true;
			break;
		default:
			break;
		}

 if (bRecalc)
	this->updateValue(pvecValues);

 for(itpEv=m_vpPassiveEvents.begin();itpEv!=m_vpPassiveEvents.end();itpEv++)
	if ((*itpEv)->trigger(pvecValues,pvecValuesLast)==ceesEndSimulation)
		bStop=true;
 
 for(itpEv=m_vpLastEvents.begin();itpEv!=m_vpLastEvents.end();itpEv++)
	if ((*itpEv)->trigger(pvecValues,pvecValuesLast)==ceesEndSimulation)
		bStop=true;

 return bStop;

}


///////////////////////////////////////////////////////////
// Function name	: CModel::signalEndSimulation
// Description	    : 
// Return type		: void 
// Argument         : vectorValues& rVecVals
///////////////////////////////////////////////////////////
void CModel::signalEndSimulation(vectorValues& rVecVals)
{
 vector< CEvent* >::iterator itpEv;

 for(itpEv=m_vpEvents.begin();itpEv!=m_vpEvents.end();itpEv++)
	(*itpEv)->simulationEnd(rVecVals);

 // chop the tempry events
 CEventFactory* pev = CEventFactory::instance();
 pev->deleteTheseEvents(m_vpTempEvents);
 m_vpTempEvents.clear();

}



///////////////////////////////////////////////////////////
// Function name	: CModel::ensureEventsSync
// Description	    : check if time step will need to be adjusted for
//                    the next step to ensure events trigger when
//                    they need to.// Return type		: bool 
// Argument         : vectorValues* pvecValues
// Argument         : variable& vTimeStep
///////////////////////////////////////////////////////////
bool CModel::ensureEventsSync(vectorValues* pvecValues, variable& vTimeStep )
{

// run through precision timed events to see if they will be triggered
// in the next step. If so adjust the time step to hit that point exactly.
 vector< CEvent* >::iterator itpEv;
 variable vTempTimeStep;
 bool bAdjust = false;
 for(itpEv=m_vpPreciseEvents.begin();itpEv!=m_vpPreciseEvents.end();itpEv++)
	if ((*itpEv)->willTriggerOverTime((*pvecValues)[getIndIndex()],vTimeStep))
		{
		bAdjust = true;
		// need to finish this then call an over ride with the solver.
		vTempTimeStep = (*itpEv)->getTimeTillTrigger((*pvecValues)[getIndIndex()]);
		ASSERT2(vTempTimeStep>0);
		// there is a minimum time step - otherwise things may get stuck, regardless of errors
		if (vTempTimeStep<MIN_TIME_STEP) // not this is key as some number can have very small but significant differences
			vTempTimeStep = MIN_TIME_STEP;
		if (vTempTimeStep<vTimeStep) // there may be other items that need shorter steps
				vTimeStep = vTempTimeStep;
		}

 

 return bAdjust;  // just for now;
}




///////////////////////////////////////////////////////////
// Function name	: CModel::getMaxSolverStep
// Description	    : Check all events for any max step limits
//                    and set xtMax if found otherwise return false
//                    and set xtMax to NOT_DEFINED
// Return type		: bool 
// Argument         : xt_value& xtMax
///////////////////////////////////////////////////////////
bool CModel::getMaxSolverStep(xt_value& xtMax)
{
 vector< CEvent* >::iterator itpEv;
 bool bResult=false;
 xtMax = NOT_DEFINED;

 for(itpEv=m_vpEvents.begin();itpEv!=m_vpEvents.end();itpEv++)
		if ((*itpEv)->hasAPeriodUpperLimit())
			{
			if (!bResult)
				{
				bResult=true;
				xtMax=(*itpEv)->getPeriodUpperLimit();
				}
				else
				if (xtMax>(*itpEv)->getPeriodUpperLimit())
					xtMax=(*itpEv)->getPeriodUpperLimit();
			}

 return bResult;
}



#ifndef NDEBUG
long CModel::getIndIndex()
{
	ASSERT2(m_iTimeInd!=NOT_DEFINED);
	return m_iTimeInd;
}
#endif


///////////////////////////////////////////////////////////
// Function name	: CModel::prepareEquations
// Description	    : Helper function to reset time index and run flag - 
//                    but not start time in the CEquation class static values
// Return type		: void 
// Argument         : list<CEquation*>* pvecpEquations
///////////////////////////////////////////////////////////
#ifdef EQSTOPOPTION
void CModel::prepareEquations(list<CEquation*>* pvecpEquations)
{
	list<CEquation*>::iterator it;
	ASSERT2(pvecpEquations);

	// set time index - if known
	CEquation::setTimeData(m_iTimeInd);
	CEquation::resetSimulationStop(); // so at least we start without a stop - if you see what I mean
	for (it=pvecpEquations->begin();it!=pvecpEquations->end();it++)
			(*it)->reset();

}
#endif
