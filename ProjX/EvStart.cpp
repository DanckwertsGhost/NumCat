// EvStart.cpp: implementation of the CEvStart class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EvStart.h"
#include "Symlix/ErrorFactory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEvStart::CEvStart(CToken* pctLHS, variable vSetValue):CEventImpl(),m_iIndex(NOT_DEFINED),m_vSetValue(vSetValue),m_pctLHS(pctLHS),m_bFired(false)
{
	if (pctLHS) // otherwise stays in cevError
		m_eState = cevUninitiated;
		else
		m_sError = "<Internal Error#> 1006 please report to vendor."; // see ERROR_EVENT_CEVENT3
}

CEvStart::~CEvStart()
{

}



///////////////////////////////////////////////////////////
// Function name	: CEvStart::setupEvent
// Description	    : Now that variable indexs have been assigned
//                    it is possible to set the index from the copy
//                    of the CToken held.
// Return type		: bool 
// Argument         : list<CEquation>* pvecEquations
///////////////////////////////////////////////////////////
bool CEvStart::setupEvent(list<CEquation*>* pvecpEquations)
{
	// m_pctLHS should now have a Token assigned to it
	if (isInError())
			return false;

	m_iIndex = m_pctLHS->getRootTokenPt()->getIndex();

	ASSERT2(m_iIndex!=NOT_DEFINED); // bring attention here in debug
	if ((m_iIndex==NOT_DEFINED)||(m_iIndex<0))
			return false;

	m_eState = cevInitiated;

	return true;
}

///////////////////////////////////////////////////////////
// Function name	: CEvStart::prepareForSimulation
// Description	    : returns true if event can be ignored after call
//                    ( if life time not managed by factory then delete event )
// Return type		: bool 
// Argument         : vector< variable >* pvecVars
// Argument         : ostream& oserr - where the error messages go
///////////////////////////////////////////////////////////
bool CEvStart::prepareForSimulation( vector< variable >* pvecVars, ostream& oserr  )
{
	if (m_eState!=cevInitiated)
			{
			oserr << "<Internal Error*> A CEvStart Event requested to prepare when not setup. Internal error "<<ERROR_EVENT_CEVENT2 <<endl;
			SYMERRORLITE("A start event was not set up as requested",errInternal);
			ASSERT2(m_eState==cevInitiated);// as this needs sorting
			return false;
			}

	ASSERT2(pvecVars->size()>m_iIndex);
	if (pvecVars->size()<=m_iIndex)
			{
			oserr << "<Internal Error*> A CEvStart Event requested a variable that can't be supplied. Internal error "<<ERROR_EVENT_CEVENT1 <<endl;
			SYMERRORLITE("Event requested a variable that can't be supplied",errInternal);
			m_eState = cevError;
			return false;
			}

	if (m_eState==cevInitiated)
			(*pvecVars)[m_iIndex] = m_vSetValue;

	m_bFired=true;

	return true; // this only gets called once
}

bool CEvStart::check(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport )
{
	bool bResult = true;
	long iRightNoComments = CNavTokens::getPosRightWithoutComments(iLeft,iRight,vExpLine);

	ASSERT2(iLeft<iRightNoComments);
	if (iLeft>=iRightNoComments)
			return false;

	if (vExpLine.size()<iRightNoComments)
			{
			if (vExpLine.size()>0)
				{
				osErrReport <<"<Error*> format error with Start Event on line "<<vExpLine[0]->getLine()<<" ."<<endl;
				SYMERRORTOK("Format error with Start Event",errSyntax,vExpLine[0]);
				}
				else
				{				
				osErrReport <<"<Error*> format error with Start Event on line."<<endl;
				SYMERRORLITE("Format error with Start Event",errSyntax);
				}
			return false;
			}

	if ((iRightNoComments-iLeft)<3)
			{
			osErrReport << "<Error*> Event does not have enough information";
			if (vExpLine.size()>0)
				osErrReport <<" on line "<< vExpLine[0]->getLine();
			osErrReport <<".\n";
			SYMERRORTOK("Event does not have enough information",errSyntax,vExpLine[iLeft]);
			return false;
			}

	if ((iRightNoComments-iLeft)>3)
			{
			osErrReport << "<Error*> Event should be variable = number.\n";
			osErrReport << "        Too much information";
			if (vExpLine.size()>0)
				osErrReport <<" on line "<< vExpLine[0]->getLine();
			osErrReport <<".\n";
			SYMERRORTOK("Event has too much information, remeber only a single numerical value on RHS",errSyntax,vExpLine[iLeft]);
			return false;
			}

	bResult = CEquation::IsWellFormedExpression(iLeft,iRightNoComments,vExpLine,osErrReport,false,true);
	
	if ((bResult)&&((vExpLine[1+iLeft]->getString().compare(g_Eq)!=0)))
			{
			osErrReport << "<Error*> Start event must use a '=' operator, not " << vExpLine[1+iLeft]->getString().c_str();
			osErrReport << " in line "<<vExpLine[1+iLeft]->getLine()<< endl;
			SYMERRORTOK2("Error found in event, expected: ",g_Eq,errSyntax,vExpLine[1+iLeft]);
			bResult = false;
			}
	// 1+iLeft must be a variable and 3+iLeft must be a number
	ATLTRACE("Variable being checked is %s on line %d\n",vExpLine[iLeft]->getString().c_str(),vExpLine[iLeft]->getLine());
	#ifndef NDEBUG
	CToken* tdebug = vExpLine[iLeft];
	if (tdebug->HasAParent())
		ATLTRACE("Parent at line %d, for %s\n",tdebug->getRootToken().getLine(),tdebug->getRootToken().getString().c_str());
	#endif
	if ((bResult)&&(!vExpLine[iLeft]->IsOfTypeVariable()))
			{
			osErrReport << "<Error*> Start event must use a variable, not " << vExpLine[iLeft]->getString().c_str();
			osErrReport << " in line "<<vExpLine[1+iLeft]->getLine()<< endl;
			#ifndef NDEBUG
			CToken* pDebugPt = vExpLine[iLeft];
			osErrReport << *pDebugPt <<endl;
			#endif
			SYMERRORTOK("Start event must use a recognised variable",errSyntax,vExpLine[iLeft]);
			bResult = false;
			}

	if ((bResult)&&(!vExpLine[2+iLeft]->IsOfType(ctNumber)))
			{
			osErrReport << "<Error*> Start event must use a number, not " << vExpLine[2+iLeft]->getString().c_str();
			osErrReport << " in line "<<vExpLine[2+iLeft]->getLine()<< endl;
			SYMERRORTOK("Start event be equal to a number",errSyntax,vExpLine[2+iLeft]);
			bResult = false;
			}

	return bResult;
}


///////////////////////////////////////////////////////////
// Function name	: CEvStart::affectsStartTime
// Description	    : 
// Return type		: bool 
///////////////////////////////////////////////////////////
bool CEvStart::affectsStartTime()
{
	if (m_eState==cevError)
			return false;
	ASSERT2(m_pctLHS);

	return (m_pctLHS->getString().compare(g_Time)==0);

}

variable CEvStart::giveStartTime()
{

	ASSERT2(affectsStartTime()); // this should have been checked first
	if (!affectsStartTime())
			return (variable)CANNOT_EVALUATE;

	return m_vSetValue;

}


///////////////////////////////////////////////////////////
// Function name	: CEvStart::trigger
// Description	    : Note this event shoul have been triggered by calling
//                    prepare for simulation. This implementation is
//                    added for completeness
// Return type		: eEventSignal 
// Argument         :  vector< variable >* /*pvecVars*/
// Argument         : vector< variable >* /*pvecVarsLast*/
///////////////////////////////////////////////////////////
eEventSignal CEvStart::trigger( vector< variable >* pvecVars, vector< variable >* /*pvecVarsLast*/ )
{

 if ((m_bFired)||(m_eState!=cevInitiated))
		return ceesNoTrig;

 (*pvecVars)[m_iIndex] = m_vSetValue;
 m_bFired = true; // fire only once

 return ceesTrig;
}


///////////////////////////////////////////////////////////
// Function name	: CEvStart::setStrongType
// Description	    : Designed to pass on model strong type information
// Return type		: void 
// Argument         : const vector<varStrongType>& vecst
///////////////////////////////////////////////////////////
void CEvStart::setStrongType(const vector<varStrongType>& vecst)
{
  ASSERT2(m_iIndex!=NOT_DEFINED);
  if (m_iIndex==NOT_DEFINED)
		return;
  ASSERT2(m_iIndex<vecst.size());
  ASSERT2(m_iIndex>=0);
  variable vTemp = m_vSetValue;
  m_vSetValue.copy(vecst[m_iIndex]);
  m_vSetValue = vTemp;

}


///////////////////////////////////////////////////////////
// Function name	: CEvStartUser::setupEvent
// Description	    : 
// Return type		: bool 
// Argument         : list<CEquation*>* pvecpEquations
///////////////////////////////////////////////////////////
bool CEvStartUser::setupEvent(list<CEquation*>* pvecpEquations)
{
	// m_pctLHS should now have a Token assigned to it
	if (isInError())
			return false;

	ASSERT2(m_iIndex!=NOT_DEFINED); // bring attention here in debug
	if ((m_iIndex==NOT_DEFINED)||(m_iIndex<0))
			return false;

	m_eState = cevInitiated;

	return true;
}


///////////////////////////////////////////////////////////
// Function name	: CEvStartUser::affectsStartTime
// Description	    : 
// Return type		: bool 
///////////////////////////////////////////////////////////
bool CEvStartUser::affectsStartTime()
{
	if (m_eState==cevError)
			return false;

	return m_bIsTime;
}


#ifndef NDEBUG


///////////////////////////////////////////////////////////
// Function name	: CEvStartUser::trigger
// Description	    : Debug defintion to allow changes to be traced
// Return type		: eEventSignal 
// Argument         :  vector< variable >* pvecVars
// Argument         : vector< variable >* /*pvecVarsLast*/
///////////////////////////////////////////////////////////
eEventSignal CEvStartUser::trigger( vector< variable >* pvecVars, vector< variable >* /*pvecVarsLast*/ )
{

	return CEvStart::trigger( pvecVars,pvecVars);

}

#endif