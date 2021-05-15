// EvValue.cpp: implementation of the CEvValue class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EvValue.h"
#include <assert.h>
#include "Symlix/ErrorFactory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEvValue::CEvValue():CEventImpl(),m_vActionValue(-1),m_bFixedAtStart(true)
{
	m_eState=cevUninitiated;
}

CEvValue::CEvValue(const CEquation& ceAction, const CEquation& ceCondition):CEventImpl(),m_eqAction(ceAction),m_eqCondition(ceCondition), m_vActionValue(-1), m_bFixedAtStart(true)
{
	// If equations are set up right then state is Intiated - otherwise stays as error from CEventImpl.
	m_bFixedAtStart=m_eqAction.isAFixedExpression();

	if (m_eqAction.isReady()&&m_eqCondition.isReady())
			{
			m_eState = cevInitiated;
			}
			else
			if (m_eqAction.isCorrect()&&m_eqCondition.isCorrect())
				m_eState = cevUninitiated;
	
}


///////////////////////////////////////////////////////////
// Function name	: CEvValue::check
// Description	    : static function to ensure that the tokens to form this event are
//                    correctly arranged.
// Return type		: bool 
// Argument         : long iLeft
// Argument         : long iRight
// Argument         : vector<CToken*>& vExpLine
// Argument         : ostream& osErrReport
///////////////////////////////////////////////////////////
bool CEvValue::check(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport )
{
	bool bResult = true;
	long iAt=NOT_DEFINED;
	long iT;
	long iRightNC;

	ASSERT2(iLeft<iRight);
	if (iLeft>=iRight)
			return false;

	iRightNC = getPosRightWithoutComments(iLeft,iRight,vExpLine);

	if (vExpLine.size()<iRightNC)
			{
			if (vExpLine.size()>0)
				{
				osErrReport <<"<Error*> format error with "<< g_Sync <<" Event on line "<<vExpLine[0]->getLine()<<" ."<<endl;
				SYMERRORTOK("Change once format error",errSyntax,vExpLine[0]);
				}
				else
				{
				osErrReport <<"<Error*> format error with "<< g_Sync <<" Event on line."<<endl;
				SYMERRORLITE("Change once format error",errSyntax);
				}
			return false;
			}

	if ((iRightNC-iLeft)<7)
			{
			osErrReport << "<Error*> Event does not have enough information";
			if (vExpLine.size()>0)
				osErrReport <<" on line "<< vExpLine[0]->getLine();
			osErrReport <<".\n";
			SYMERRORTOK("Event does not have enough information",errSyntax,vExpLine[iLeft]);
			return false;
			}

	for(iT=iLeft;(iAt==NOT_DEFINED)&&(iT<=iRightNC)&&(iT<vExpLine.size());iT++)
		if (vExpLine[iT]->getStringRef().compare(g_At)==0)
					iAt=iT;

	if (iAt==NOT_DEFINED)
			{
			SYMERRORTOK2(g_At," could not be found",errSyntax,vExpLine[iLeft]);
			return false;
			}

	bResult = CEquation::IsWellFormedEquation(0,iAt,vExpLine,osErrReport);
	bResult &= CEquation::IsWellFormedEquation(iAt+1,iRightNC,vExpLine,osErrReport);

	if (!bResult)
			{
			SYMERRORTOK("Change once event equation was badly formed",errSyntax,vExpLine[iLeft]);
			return false;
			}

	// and now need to check that the last equation RHS is just a number

	if ((iRightNC-iAt)!=4) // ie 3 with iAt+1
			{
			SYMERRORTOK("The condition for this event is not correctly formed",errSyntax,vExpLine[iAt]);
			return false;
			}

//	ATLTRACE("%s\n",vExpLine[iRightNC-1]->getStringRef().c_str());
	if (!vExpLine[iRightNC-1]->IsOfType(ctNumber))
			{
			SYMERRORTOK("The condition for this event must have a number on its RHS",errSyntax,vExpLine[iRightNC-1]);
			return false;
			}


	return bResult;
}


CEvValue::CEvValue(const CEvValue& CE):CEventImpl()
{
	copy(CE);

}


CEvValue::~CEvValue()
{

}


///////////////////////////////////////////////////////////
// Function name	: CEvValue::sendtostream
// Description	    : 
// Return type		: void 
// Argument         : ostream& os
///////////////////////////////////////////////////////////
void CEvValue::sendtostream(ostream& os) const
{
	switch(m_eState)
	{
	case cevUninitiated:
		os << "<Warning#> CEvValue object uniniated state";
	break;
	case cevError:
		os << "<<Error#>> CEvValue object in error state";
	break;
	case cevFired:
		os << "[Fired] ";
	case cevInitiated:
		os << m_eqAction << " @ " << m_eqCondition;
	break;
	default:
	assert(false); // this is a bad error state
	}


}


///////////////////////////////////////////////////////////
// Function name	: CEvValue::copy
// Description	    : 
// Return type		: void 
// Argument         : const CEvValue& CE
///////////////////////////////////////////////////////////
void CEvValue::copy(const CEvValue& CE)
{
	m_eState = CE.m_eState;
	m_eqAction = CE.m_eqAction;
	m_eqCondition = CE.m_eqCondition;
	m_vActionValue = CE.m_vActionValue;
	m_bFixedAtStart = CE.m_bFixedAtStart;
}


///////////////////////////////////////////////////////////
// Function name	: CEvValue::greaterThan
// Description	    : 
// Return type		: bool 
// Argument         : const CEvValue& CE
///////////////////////////////////////////////////////////
bool CEvValue::greaterThan(const CEvValue& CE) const
{
	if (m_eState>CE.m_eState) // as these have numerical value
				return true;

	if (m_eqAction>CE.m_eqAction)
				return true;

	if (m_eqCondition>CE.m_eqCondition)
				return true;

	return false; // default
}


///////////////////////////////////////////////////////////
// Function name	: CEvValue::triggerAction
// Description	    : 
// Return type		: bool 
// Argument         : const variable& vTime
// Argument         : const variable& vTimeStep
///////////////////////////////////////////////////////////
bool CEvValue::triggerAction( const variable& vTime, const variable& vTimeStep )
{


	assert(false); //NYI
	return false; //NYI
}


///////////////////////////////////////////////////////////
// Function name	: CEvValue::canChange
// Description	    : 
// Return type		: CToken* 
///////////////////////////////////////////////////////////
CToken* CEvValue::canChange()
{
	return m_eqAction.getLHS();
}



///////////////////////////////////////////////////////////
// Function name	: CEvValue::willTriggerOverTime
// Description	    : 
// Return type		: bool 
// Argument         : const variable& vValue
// Argument         : const variable& vValueStep
// Argument         : const string& sTrig
///////////////////////////////////////////////////////////
bool CEvValue::willTriggerOverTime( const variable& vValue, const variable& vValueStep, const string& sTrig  )
{
#ifndef NDEBUG // to help debug logic only
 bool b1,b2,b3;
#endif
 variable vActionValue;	

 if (m_eState==cevFired)
		return false;// event has been used once - don't ask further

// ASSERT2(m_eState==cevInitiated); this fails - need to check that isn't a real problem
 
 if (sTrig.compare(m_eqCondition.getLHS()->getString())!=0)
				return false; // then this doesn't apply.

 if (!m_eqCondition.canEvaluate())
			return false;

 vActionValue = m_eqCondition.evaluate();

#ifndef NDEBUG // to make logic easily visible during debug
 b1 = vValue<vActionValue;
 b2 = vValue>(vActionValue-vValueStep);
 b3 = b1&&b2;

 assert(b3==((vValue<vActionValue)&&(vValue>(vActionValue-vValueStep))));
#endif

 return ((vValue<vActionValue)&&(vValue>(vActionValue-vValueStep)));
}



///////////////////////////////////////////////////////////
// Function name	: CEvValue::hasAPreciseTimeTrigger
// Description	    : returns true if time is the trigger
// Return type		: bool 
// Argument         : const long
///////////////////////////////////////////////////////////
bool CEvValue::hasAPreciseTimeTrigger(const long )
{

 ASSERT2(m_eState==cevInitiated);

 // will add some code to allow relaxed events altter - maybe even another class

 return  (m_eqCondition.getLHS()->getString().compare(g_Time)==0);

}


///////////////////////////////////////////////////////////
// Function name	: CEvValue::reset
// Description	    : If event has been fired, for example in testing code, then reset
// Return type		: void 
///////////////////////////////////////////////////////////
void CEvValue::reset()
{
	if (m_eState==cevFired)
			m_eState=cevInitiated;
	// if its not intiated then do nothing


}



///////////////////////////////////////////////////////////
// Function name	: CEvValue::getTimeTillTrigger
// Description	    : return a value for the time until trigger
// Return type		: variable 
// Argument         : const variable& vCurrentTime
///////////////////////////////////////////////////////////
variable CEvValue::getTimeTillTrigger(const variable& vCurrentTime)
{

 ASSERT2(m_eqCondition.canEvaluate()); // don't expect this to fail, but equally want to avoid the code in an oten repeated call

 return m_eqCondition.evaluate() - vCurrentTime; 
}


///////////////////////////////////////////////////////////
// Function name	: CEvValue::setupEvent
// Description	    : Prepare event by setting up underlying equations
// Return type		: bool 
// Argument         : list<CEquation>* pvecEquations
///////////////////////////////////////////////////////////
bool CEvValue::setupEvent(list<CEquation*>* pvecpEquations)
{

	bool bResult;

	bResult = m_eqCondition.setupExpression(pvecpEquations,CVarClassFactory::instance(),cerr);
	bResult &= m_eqAction.setupExpression(pvecpEquations,CVarClassFactory::instance(),cerr);

	if (bResult)
			m_eState = cevInitiated;

	return bResult; 
}

eEventSignal CEvValue::trigger( vector< variable >* pvecVars, vector< variable >* pvecVarsLast )
{
	if (willTrigger(pvecVars))
		{
		m_eqAction.updateValue(pvecVars);
		m_eState = cevFired; // only use this event once
		return ceesTrig;
		}
	return ceesNoTrig;
}

bool CEvValue::willTrigger( vector< variable >* pvecVars )
{

	double vDiff; // using double other wise loads on conversions will be made
	variable vCondition;
	long iLeft = m_eqCondition.getLHS()->getRootTokenPt()->getIndex();
	#ifndef NDEBUG
	assert(iLeft!=NOT_DEFINED);
	assert(pvecVars);
	#else
	if (iLeft==NOT_DEFINED)
		{
		cerr << "<Error*> Left hand condition is not defined:\n"<<*(m_eqCondition.getLHS())<<endl;
		SYMERRORTOK("Left hand condition is not defined as attempt to solve",errInternal,m_eqCondition.getLHS());
		return false;
		}
	#endif

	#ifdef EXTRADEBUG
	cout << " Value = "<<(*pvecVars)[iLeft]<<" == m_eqCondition.evaluate = "<<m_eqCondition.evaluate(pvecVars)<<endl;
	if (m_eState!=cevFired)
			cout <<" and m_eState != cevFired"<<endl;
	if ((*pvecVars)[iLeft]==m_eqCondition.evaluate(pvecVars))
			cout <<"Both sides equal"<<endl;
			else
			if ((*pvecVars)[iLeft]<m_eqCondition.evaluate(pvecVars))
				cout <<"Value less than trigger "<<((*pvecVars)[iLeft]-m_eqCondition.evaluate(pvecVars))<<endl;
				else
				cout <<"Value more than trigger "<<((*pvecVars)[iLeft]-m_eqCondition.evaluate(pvecVars))<<endl;
	#endif

	if (m_eState==cevFired)
			return false; // to save processing
	
	vCondition = m_eqCondition.evaluate(pvecVars); // do this only once
	vDiff = fabs((*pvecVars)[iLeft]-vCondition);

	if (fabs(vCondition)>DEFAULT_SMALL_NUMBER) // avoid divide by zero
			vDiff /= fabs(vCondition);

	if (vDiff<static_cast<double>(DEFAULT_SMALL_NUMBER))
			return true;	


	return false;

}

void CEvValue::setStrongType(const vector<varStrongType>& vecst)
{
	m_eqAction.setStrongType(vecst);
}

