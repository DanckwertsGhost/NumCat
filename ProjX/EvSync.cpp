// EvSync.cpp: implementation of the CEvSync class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EvSync.h"
#include "Symlix/ErrorFactory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CEvSync::CEvSync(long iLeft, long iRight, vector<CToken*>& vecCT, ostream& oserr /*= cerr*/):CEventImpl(),m_iIndTime(NOT_DEFINED),m_tstep(NOT_DEFINED),m_tSync(NOT_DEFINED)
{
// this type of event can be intiated from construtor 

	if (check(iLeft,iRight,vecCT,oserr))
		{
		ASSERT2(vecCT[iLeft]->IsOfType(ctNumber));
		m_tstep = vecCT[iLeft]->getNumber();
		m_tSync = vecCT[iLeft+2]->getNumber();
		m_tNext = m_tSync + m_tstep;
		m_eState = cevUninitiated; // need to get time trigger

		}
		else
		{
		m_sError = "<Internal Error#> Unable to intialise sync event.";
		m_eState = cevError;
		
		}
}

CEvSync::~CEvSync()
{

}



///////////////////////////////////////////////////////////
// Function name	: CEvSync::check
// Description	    : 
// Return type		: bool 
// Argument         : long iLeft
// Argument         : long iRight
// Argument         : vector<CToken*>& vExpLine
// Argument         : ostream& osErrReport
///////////////////////////////////////////////////////////
bool CEvSync::check(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport )
{
	bool bResult = true;

	ASSERT2(iLeft<iRight);
	if (iLeft>=iRight)
			return false;

	if (vExpLine.size()<iRight)
			{
			if (vExpLine.size()>0)
				{
				osErrReport <<"<Error*> format error with "<< g_Sync <<" Event on line "<<vExpLine[0]->getLine()<<" ."<<endl;
				SYMERRORTOK2(g_Sync," format error",errSyntax,vExpLine[0]);
				}
				else
				{
				osErrReport <<"<Error*> format error with "<< g_Sync <<" Event on line."<<endl;
				SYMERRORLITE2(g_Sync," format error",errSyntax);
				}
			return false;
			}

	if ((iRight-iLeft)<3)
			{
			osErrReport << "<Error*> Event does not have enough information";
			if (vExpLine.size()>0)
				osErrReport <<" on line "<< vExpLine[0]->getLine();
			osErrReport <<".\n";
			SYMERRORTOK("Event does not have enough information",errSyntax,vExpLine[iLeft]);
			return false;
			}

	// the left most term MUST be a number
	if ((!vExpLine[iLeft]->IsOfType(ctNumber))||(vExpLine[iLeft]->getNumber()<=0))
			{
			osErrReport << "<Error*> "<< g_Sync <<" statment must be followed by a positive number '";
			osErrReport << vExpLine[iLeft]->getString().c_str() <<"' in line "<<vExpLine[iLeft]->getLine()<<".\n";
			SYMERRORTOK2(g_Sync," statement must be followed by a positive number",errSyntax, vExpLine[iLeft]);
			return false;
			}

	if ((!vExpLine[iLeft+1]->IsOfType(ctEventKeyWord))||(vExpLine[iLeft+1]->getStringRef().compare(g_Start)!=0))
			{
			osErrReport << "<Error*> "<< g_Sync <<" statment must be followed by a '"<<g_Start <<"' statment in ";
			osErrReport <<"line "<<vExpLine[iLeft]->getLine()<<".\n";
			SYMERRORTOK2("Statement must be followed by a: ",g_Start,errSyntax, vExpLine[iLeft+1]);
			return false;
			}

	if (!vExpLine[iLeft+2]->IsOfType(ctNumber))
			{
			osErrReport << "<Error*> "<< g_Sync <<" statment must be followed by a number '";
			osErrReport << vExpLine[iLeft+2]->getString().c_str() <<"' in line "<<vExpLine[iLeft]->getLine()<<".\n";
			SYMERRORTOK2(g_Sync," statement must be followed by a number",errSyntax, vExpLine[iLeft+2]);
			return false;
			}

	return bResult;
}


///////////////////////////////////////////////////////////
// Function name	: CEvSync::willTriggerOverTime
// Description	    : 
// Return type		: bool 
// Argument         : const variable& vValue
// Argument         : const variable& vValueStep
// Argument         : const string& sTrig /*= g_Time*/
///////////////////////////////////////////////////////////
bool CEvSync::willTriggerOverTime( const variable& vValue, const variable& vValueStep, const string& sTrig /*= g_Time*/)
{
#ifndef NDEBUG // to help debug logic only
 bool b1,b2,b3;
#endif

 ASSERT2(m_eState==cevInitiated);

 if (m_eState!=cevInitiated)
		return false;


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
// Function name	: CEvSync::trigger
// Description	    : 
// Return type		: eEventSignal 
// Argument         : vector< variable >* pvecVars
// Argument         : vector< variable >* /*pvecVarsLast*/ - not used.
///////////////////////////////////////////////////////////
eEventSignal CEvSync::trigger( vector< variable >* pvecVars, vector< variable >* /*pvecVarsLast*/ )
{

	if (willTrigger(pvecVars)) // actually dop nothing - but force the solve to change step to be in sync
		return ceesTrig;

	return ceesNoTrig;
}


///////////////////////////////////////////////////////////
// Function name	: CEvSync::willTrigger
// Description	    : 
// Return type		: bool 
// Argument         : vector< variable >* pvecVars
///////////////////////////////////////////////////////////
bool CEvSync::willTrigger( vector< variable >* pvecVars )
{
	double vDiff; // using double other wise loads on conversions will be made
//	variable vCondition;

	ASSERT2(m_iIndTime!=NOT_DEFINED);
	ASSERT2(m_iIndTime<pvecVars->size());

	#ifdef EXTRADEBUG
	#endif

	vDiff = fabs(getLastTriggerPoint((*pvecVars)[m_iIndTime]) - (*pvecVars)[m_iIndTime]);

	if (vDiff<static_cast<double>(DEFAULT_SMALL_NUMBER))
			return true;	

	vDiff -= m_tNext;

	if (vDiff<static_cast<double>(DEFAULT_SMALL_NUMBER))
			return true;	


	return false;
}




///////////////////////////////////////////////////////////
// Function name	: CEvSync::hasAPreciseTimeTrigger
// Description	    : 
// Return type		: bool 
// Argument         : const long iTime
///////////////////////////////////////////////////////////
bool CEvSync::hasAPreciseTimeTrigger(const long iTime)
{
	ASSERT2(iTime>=0);

	m_iIndTime = iTime;
	if (m_eState==cevUninitiated)
		m_eState=cevInitiated;
	return true;
}



///////////////////////////////////////////////////////////
// Function name	: CEvSync::getTimeTillTrigger
// Description	    : 
// Return type		: variable 
// Argument         : const variable& vCurrentTime
///////////////////////////////////////////////////////////
variable CEvSync::getTimeTillTrigger(const variable& vCurrentTime)
{
#ifdef EXTRADEBUG

	variable tgap = getNextTriggerPoint( vCurrentTime) - vCurrentTime;

#endif


	return (getNextTriggerPoint( vCurrentTime) - vCurrentTime);

}



///////////////////////////////////////////////////////////
// Function name	: CEvSync::getLastTriggerPoint
// Description	    : 
// Return type		: variable 
// Argument         : const variable& vTime
///////////////////////////////////////////////////////////
variable CEvSync::getLastTriggerPoint( const variable& vTime)
{
	return (getNextTriggerPoint(vTime) - m_tstep);

}




///////////////////////////////////////////////////////////
// Function name	: CEvSync::getNextTriggerPoint
// Description	    : 
// Return type		: variable& 
// Argument         : const variable& vTime
///////////////////////////////////////////////////////////
variable& CEvSync::getNextTriggerPoint( const variable& vTime)
{

	while(m_tNext<=vTime)
		m_tNext += m_tstep;
	return m_tNext;

}

void CEvSync::reset()
{
	m_tNext = m_tSync;
}


