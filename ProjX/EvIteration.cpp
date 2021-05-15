// EvIteration.cpp: implementation of the CEvIteration class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EvIteration.h"
#include "Symlix/ErrorFactory.h"

#ifdef DEBUGEVI
#include <string>
#define TR1( loc, string, val1 ) { if (m_pos) \
								     (*m_pos) << "[" << loc << "] "<< string << "  "<< val1 << endl; \
								 }
#else
#define TR1( loc, string, val1 ) {}
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEvIteration::CEvIteration(): CEventImpl(),m_pLHS(NULL),m_pCounter(NULL),m_iIndTime(NOT_DEFINED),m_tstep(CEI_MAX_STEP),m_tSync(0.0),m_iIndexLHS(NOT_DEFINED),m_tNext(NOT_DEFINED)
{
	m_eState = cevError; // unless reset
	m_sError = "Event not set up correctly";
#ifdef DEBUGEVI
	m_pos = NULL;
#endif
}

#ifdef DEBUGEVI
bool CEvIteration::m_bOpenAlready =false;

#endif

CEvIteration::CEvIteration( long iLeft, long iRight, vector< CToken* >& vecLine, ostream& oserr): CEventImpl(),m_pLHS(NULL),m_pCounter(NULL),m_iIndTime(NOT_DEFINED),m_tstep(CEI_MAX_STEP),m_tSync(0.0),m_iIndexLHS(NOT_DEFINED),m_tNext(NOT_DEFINED)
{
	vector< CToken* >::const_iterator itpCT;
	vector< CToken* >::const_iterator itpCTRight;
	itpCTRight = getRightWithoutComments(iLeft,iRight,vecLine);
	ASSERT2(check(iLeft,iRight,vecLine,oserr));
	m_eState = cevError; // unless reset
	m_sError = "Unknown error";

#ifdef DEBUGEVI
	if (!m_bOpenAlready)
		m_pos = newtrack ofstream("c:\\temp\\TraceEvIteration.txt");

	if (m_pos)
		(*m_pos) <<"CEvIteration debug file\n\n";

	TR1( "CEvIteration::CEvIteration","TR1 test",54.34);
#endif

	if (check(iLeft,iRight,vecLine,oserr))
		{
		m_eState=cevUninitiated;
	    m_pLHS = vecLine[iLeft]; // this has a note of the variable

		// which composition of event is it ?
		// 1. iteration N = 1 to 100 step 2
		// 2. iteration N {1,2,5,10,30}
	
		// check item iLeft + 1 ( which is now guarenteed to exist by the check )
		
		if (vecLine[iLeft+1]->getString().compare(g_Eq)==0)
				m_bEqualFormat=true;
			else
				m_bEqualFormat=false;

		m_pLHS = vecLine[iLeft];

		if (m_bEqualFormat)
				{
				variable vFrom, vTo, vStep;
				itpCT = &vecLine[iLeft+2];
				vFrom = (*itpCT)->getNumber();
				itpCT++;itpCT++;
				vTo= (*itpCT)->getNumber();
				if ((++itpCT!=itpCTRight)&&(++itpCT!=itpCTRight))
					vStep =  (*itpCT)->getNumber();
					else
					if (vFrom>vTo)
							vStep=-1;
							else
							vStep=1;
				m_pCounter = newtrack CEI_FromTo(vFrom,vTo,vStep);
				}
			else
				{
				vector< variable > vecValues;
				itpCT=&vecLine[iLeft+1];

				while ((++itpCT)!=itpCTRight)
					vecValues.push_back((*itpCT++)->getNumber());

				m_pCounter = newtrack CEI_Sequence(vecValues);
				}

		if (!m_pCounter)
				{
				m_eState = cevError;
				m_sError = "Lack of memory prevented to model loading";

				}


		}
}

CEvIteration::~CEvIteration()
{
		delete m_pCounter;
#ifdef DEBUGEVI
	if (m_pos)
		{
		m_pos->close();
		delete m_pos;
		}
		
		
#endif
}

#define CHECKNOTEND( pnt1, pntEnd) {  if (pnt1==pntEnd) \
											{ SYMERRORTOK("<Error*> Event does not have enough information",errSyntax,vExpLine[0]); \
											  return false; \
											}}



///////////////////////////////////////////////////////////
// Function name	: CEvIteration::check
// Description	    : Carry out syntax checks for this event
// Return type		: bool 
// Argument         : long iLeft
// Argument         : long iRight
// Argument         : vector<CToken*>& vExpLine
// Argument         : ostream& osErrReport/*=cerr*/
///////////////////////////////////////////////////////////
bool CEvIteration::check( long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport/*=cerr*/ )
{

	vector< CToken* >::iterator itpCT;
	// itpCTRight is fouud this way as I'm not sure &vExp[iRight] would produce the same result in all conditions
	vector< CToken* >::const_iterator itpCTRight;

	ASSERT2(iLeft<iRight);
	if (iLeft>=iRight)
			return false;

	if (vExpLine.size()<iRight)
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

	itpCTRight = getRightWithoutComments(iLeft,iRight,vExpLine);
	itpCT = &vExpLine[iLeft];

			
	/* legal implementations 
	iteration N = 1 to 100 step 2
	iteration N = 1 to 100
	iteration N {1,2,5,10,30}
	*/

	if ((iRight-iLeft)<5) // this won't catch all cases, but is just a first test
			{
			osErrReport << "<Error*> Event does not have enough information";
			if (vExpLine.size()>0)
				osErrReport <<" on line "<< vExpLine[0]->getLine();
			osErrReport <<".\n";
			SYMERRORTOK("Event does not have enough information",errSyntax,vExpLine[iLeft]);
			return false;
			}

	// let the checking begin
	if ((itpCT==itpCTRight)||(!(*itpCT)->IsOfTypeVariable()))
			{
			if (itpCT!=itpCTRight)
				{
				SYMERRORTOK("Variable not found for event",errSyntax,(*itpCT));
				}
				else
				{
				SYMERRORTOK("Variable not found for event",errSyntax,vExpLine[iLeft]);
				}
			return false;
			}

	itpCT++;

	// Next should either be curly brackets, lookup or a number

	CHECKNOTEND( itpCT, itpCTRight );

	if ((*itpCT)->getStringRef().compare(g_OpenCurlyBracket)==0)
		{
		bool bOK = true;
		bool bNumberNext = true;
		while (bOK&&(++itpCT!=itpCTRight)&&((*itpCT)->getString().compare(g_CloseCurlyBracket)!=0))
			{
			if (bNumberNext)
				{
				bOK = (*itpCT)->IsOfType(ctNumber);
				bNumberNext = false;
				}
				else
				{
				bOK = ((*itpCT)->getString().compare(g_Comma)==0);
				bNumberNext = true;
				}
			}
		CHECKNOTEND( itpCT, itpCTRight );
		if (!bOK)
			if (bNumberNext)
				{
				SYMERRORTOK("A comma was expected here",errSyntax,(*itpCT));
				return false;
				}
				else
				{
				SYMERRORTOK("A number or bracket close was expected here",errSyntax,(*itpCT));
				return false;
				}
		
		}
		else
		{
		variable vFrom, vTo, vStep;


		if ((*itpCT)->getString().compare(g_Eq)!=0)
			{
				SYMERRORTOK2("Was expecting ",g_Eq,errSyntax,(*itpCT));
				return false;
			}

		CHECKNOTEND( ++itpCT, itpCTRight );
		if (!(*itpCT)->IsOfType(ctNumber))
			{
				SYMERRORTOK2("Was expecting a number after ",g_Eq,errSyntax,(*itpCT));
				return false;
			}
		vFrom=(*itpCT)->getNumber();

		CHECKNOTEND( ++itpCT, itpCTRight );
		if ((*itpCT)->getString().compare(g_To)!=0)
			{
				SYMERRORTOK2("Was expecting ",g_To,errSyntax,(*itpCT));
				return false;
			}

		CHECKNOTEND( ++itpCT, itpCTRight );
		if (!(*itpCT)->IsOfType(ctNumber))
			{
				SYMERRORTOK2("Was expecting a number after ",g_To,errSyntax,(*itpCT));
				return false;
			}
		vTo=(*itpCT)->getNumber();

		// would be fine if no further tokens to consider
		if (++itpCT==itpCTRight)
				return true; // note no convergence test needed as step is implied

		if ((*itpCT)->getString().compare(g_Step)!=0)
			{
				SYMERRORTOK2("Was expecting ",g_Step,errSyntax,(*itpCT));
				return false;
			}

		CHECKNOTEND( ++itpCT, itpCTRight );
		if (!(*itpCT)->IsOfType(ctNumber))
			{
				SYMERRORTOK2("Was expecting a number after ",g_Step,errSyntax,(*itpCT));
				return false;
			}
		vStep=(*itpCT)->getNumber();

		// Now need to check this series will converge
		if (vStep==0)
					{
					SYMERRORTOK("Step is set for zero !",errModel,(*itpCT));
					return false;
					}

		if (vFrom>vTo)
			{
			if (vStep>0)
				{
				SYMERRORTOK("The From, To , Step sequence doesn't converge",errModel,(*itpCT));
				return false;
				}
			}
			else
			if (vFrom<vTo)
				{
				if (vStep<0)
					{
					SYMERRORTOK("The From, To , Step sequence doesn't converge",errModel,(*itpCT));
					return false;
					}
				}
				


		} // end if else

	return true;

}


bool CEvIteration::prepareForSimulation( vector< variable >* /*pvecVars*/, ostream& /*oserr*/ )
{


 
 if ((!m_pLHS)||(m_eState==cevError))
		{
		m_eState = cevError;
		return false;
		}

 m_eState = cevInitiated;

 if ((m_iIndTime==NOT_DEFINED)||(m_iIndexLHS==NOT_DEFINED))
	{
	m_eState = cevError;
	return false;
	}

 return true;

}


///////////////////////////////////////////////////////////
// Function name	: CEvIteration::willTriggerAtTime
// Description	    : This override is needed as iteration always initialises variable
// Return type		: bool 
// Argument         : const variable& vValue
// Argument         : const string& sTrig // = g_Time
///////////////////////////////////////////////////////////
bool CEvIteration::willTriggerAtTime( const variable& vValue, const string& sTrig /*= g_Time*/)
{
 if ((m_eState==cevUninitiated)&&(m_tNext==NOT_DEFINED))
			return true;

 return willTriggerOverTime((vValue-DEFAULT_SMALL_NUMBER/2.0),DEFAULT_SMALL_NUMBER,sTrig); 
}


///////////////////////////////////////////////////////////
// Function name	: CEvIteration::willTriggerOverTime
// Description	    : This event will trigger as each second is crossed
// Return type		: bool 
// Argument         :  const variable& vValue
// Argument         : const variable& vValueStep
// Argument         : const string& sTrig/* = g_Time*/
///////////////////////////////////////////////////////////
bool CEvIteration::willTriggerOverTime( const variable& vValue, const variable& vValueStep, const string& sTrig/* = g_Time*/)
{
#ifndef NDEBUG // to help debug logic only
 bool b1,b2,b3;
#endif

/* ASSERT2(m_eState==cevInitiated);

 if (m_eState!=cevInitiated)
		return false;
*/

 ASSERT2(sTrig.compare(g_Time)==0);
 
 if (sTrig.compare(g_Time)!=0)
				return false; // then this doesn't apply.

 getNextTriggerPoint(vValue); // sets m_tNext

#ifndef NDEBUG // to make logic easily visible during debug
 b1 = vValue<m_tNext;
 b2 = vValue>(m_tNext-vValueStep);
 b3 = b1&&b2;

 assert(b3==((vValue<m_tNext)&&(vValue>(m_tNext-vValueStep))));
#endif

 return ((vValue<m_tNext)&&(vValue>(m_tNext-vValueStep)));
}


///////////////////////////////////////////////////////////
// Function name	: CEvIteration::getNextTriggerPoint
// Description	    : 
// Return type		: variable& 
// Argument         : const variable& vTime
///////////////////////////////////////////////////////////
variable& CEvIteration::getNextTriggerPoint( const variable& vTime)
{

	while(m_tNext<=vTime)
		m_tNext += m_tstep;
	return m_tNext;

}


///////////////////////////////////////////////////////////
// Function name	: CEvIteration::getLastTriggerPoint
// Description	    : 
// Return type		: variable 
// Argument         : const variable& vTime
///////////////////////////////////////////////////////////
variable CEvIteration::getLastTriggerPoint( const variable& vTime)
{
	return (getNextTriggerPoint(vTime) - m_tstep);

}


///////////////////////////////////////////////////////////
// Function name	: CEvIteration::hasAPreciseTimeTrigger
// Description	    : 
// Return type		: bool 
// Argument         : const long iTime
///////////////////////////////////////////////////////////
bool CEvIteration::hasAPreciseTimeTrigger(const long iTime)
{
	ASSERT2(iTime>=0);

	m_iIndTime = iTime;
	if ((m_eState==cevUninitiated)&&(m_iIndexLHS!=NOT_DEFINED)&&(m_iIndexLHS!=NOT_DEFINED))
		m_eState=cevInitiated;
	return true;
}


///////////////////////////////////////////////////////////
// Function name	: CEvIteration::reset
// Description	    : 
// Return type		: void 
///////////////////////////////////////////////////////////
void CEvIteration::reset()
{
	TR1( "CEvIteration::reset", "m_tNext was before reset ", m_tNext)
	if (m_pCounter)
		m_pCounter->reset();
	m_tNext = m_tSync;
}


///////////////////////////////////////////////////////////
// Function name	: CEvIteration::setStrongType
// Description	    : Record strong type information for the variable to be set
// Return type		: void 
// Argument         : const vector<varStrongType>& vecst
///////////////////////////////////////////////////////////
void CEvIteration::setStrongType(const vector<varStrongType>& vecst)
{

  ASSERT2(m_iIndexLHS!=NOT_DEFINED);

  if (m_iIndexLHS!=NOT_DEFINED)
	  m_vStrongType.copy(vecst[m_iIndexLHS]);

}


///////////////////////////////////////////////////////////
// Function name	: CEvIteration::willTrigger
// Description	    : 
// Return type		: bool 
// Argument         : vector< variable >* pvecVars
///////////////////////////////////////////////////////////
bool CEvIteration::willTrigger( vector< variable >* pvecVars )
{

	double vDiff; // using double other wise loads on conversions will be made
//	variable vCondition;

	ASSERT2(m_iIndTime!=NOT_DEFINED);
	ASSERT2(m_iIndTime<pvecVars->size());
	ASSERT2(m_pCounter);
	ASSERT2(m_iIndexLHS!=NOT_DEFINED);

#ifdef NDEBUG
	vDiff = fabs(getLastTriggerPoint((*pvecVars)[m_iIndTime]) - (*pvecVars)[m_iIndTime]);
#else
	variable vtemp = getLastTriggerPoint((*pvecVars)[m_iIndTime]);
	vDiff = fabs(vtemp-(*pvecVars)[m_iIndTime]);
	ATLTRACE("Test %f\n",0.01234567);
	ATLTRACE(" vtemp - (*pvecVars)[m_iIndTime] = %f - %f\n",vtemp,(*pvecVars)[m_iIndTime]);
	TR1("CEvIteration::willTrigger 1","getLastTriggerPoint",vtemp);
	TR1("CEvIteration::willTrigger 2","(*pvecVars)[m_iIndTime]", (*pvecVars)[m_iIndTime]);
#endif


#ifndef NDEBUG
	if (vDiff<static_cast<double>(DEFAULT_SMALL_NUMBER))
		ATLTRACE("vDiff = %f at time %f\n",vDiff,(*pvecVars)[m_iIndTime]);	
#endif

	if (vDiff<static_cast<double>(DEFAULT_SMALL_NUMBER))
			return true;	

/*	vDiff -= m_tNext;

	if (vDiff<static_cast<double>(DEFAULT_SMALL_NUMBER))
			return true;	
*/

	return false;
}


///////////////////////////////////////////////////////////
// Function name	: CEvIteration::trigger
// Description	    : 
// Return type		: eEventSignal 
// Argument         :  vector< variable >* pvecVars
// Argument         : vector< variable >* pvecVarsLast
///////////////////////////////////////////////////////////
eEventSignal CEvIteration::trigger( vector< variable >* pvecVars, vector< variable >* pvecVarsLast )
{
	ASSERT2(m_pCounter);
	ASSERT2(m_iIndexLHS!=NOT_DEFINED);
	// check not carried out for release version as speed issues
	TR1( "CEvIteration::trigger","","");

	if (willTrigger(pvecVars))
	 	{
		(*pvecVars)[m_iIndexLHS]=m_vStrongType=m_pCounter->value();
	    TR1( "CEvIteration::trigger","willTrigger new value",m_vStrongType);
		if (m_pCounter->next())
					return ceesTrig;
					else
					return ceesEndSimulation; // as we've reached the end of the sequence
		}
	return ceesNoTrig;

}


///////////////////////////////////////////////////////////
// Function name	: CEvIteration::setupEvent
// Description	    : 
// Return type		: bool 
// Argument         : list<CEquation*>* pvecpEquations
///////////////////////////////////////////////////////////
bool CEvIteration::setupEvent(list<CEquation*>* pvecpEquations)
{

 
 if (!m_pLHS)
		return false;

 m_iIndexLHS = m_pLHS->getRootTokenPt()->getIndex();


 return true; 
}


