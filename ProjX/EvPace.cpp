// EvPace.cpp: implementation of the CEvPace class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EvPace.h"
#include "Symlix/ErrorFactory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEvPace::CEvPace(long iLeft, long iRight, vector<CToken*>& vecCT, ostream& oserr /*= cerr*/):CEventImpl()
{
// this type of event can be intiated from construtor 

	if (check(iLeft,iRight,vecCT,oserr))
		{
		ASSERT2(vecCT[iLeft]->IsOfType(ctNumber));
		m_maxTime = vecCT[iLeft]->getNumber();
		m_eState = cevInitiated;

		}
		else
		{
		m_sError = "<Internal Error#> Unable to intialise pace event.";
		m_eState = cevError;
		
		}
}

CEvPace::~CEvPace()
{

}

///////////////////////////////////////////////////////////
// Function name	: CEventImpl::prepareForSimulation
// Description	    : returns true if event can be ignored after call
//                    ( if life time not managed by factory then delete event )
// Return type		: bool 
// Argument         : vector< variable >* pvecVars
// Argument         : ostream& oserr - where the error messages go
///////////////////////////////////////////////////////////
bool CEvPace::prepareForSimulation( vector< variable >* /*pvecVars*/, ostream& /*oserr*/  )
{
 return true; // as this shouldn't be needed after simualtion start as its info passed to solver
}

///////////////////////////////////////////////////////////
// Function name	: CEvPace::check
// Description	    : 
// Return type		: bool 
// Argument         : long iLeft
// Argument         : long iRight
// Argument         : vector<CToken*>& vExpLine
// Argument         : ostream& osErrReport
///////////////////////////////////////////////////////////
bool CEvPace::check(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport )
{
	bool bResult = true;

	ASSERT2(iLeft<iRight);
	if (iLeft>=iRight)
			return false;

	if (vExpLine.size()<iRight)
			{
			if (vExpLine.size()>0)
				{
				osErrReport <<"<Error*> format error with pace Event on line "<<vExpLine[0]->getLine()<<" ."<<endl;
				SYMERRORTOK("Format error with event",errSyntax,vExpLine[0]);
				}
				else
				{
				osErrReport <<"<Error*> format error with pace Event on line."<<endl;
				SYMERRORLITE("Format error with pace event",errSyntax);
				}
			return false;
			}

	if ((iRight-iLeft)<1)
			{
			osErrReport << "<Error*> Event does not have enough information";
			if (vExpLine.size()>0)
				osErrReport <<" on line "<< vExpLine[0]->getLine();
			osErrReport <<".\n";
			SYMERRORTOK("Event does not have enough information",errSyntax,vExpLine[0]);
			return false;
			}

	// the left most term MUST be a number
	if ((!vExpLine[iLeft]->IsOfType(ctNumber))||(vExpLine[iLeft]->getNumber()<=0))
			{
			osErrReport << "<Error*> Pace statment must e followed by a positive number '";
			osErrReport << vExpLine[iLeft]->getString().c_str() <<"' in line "<<vExpLine[iLeft]->getLine()<<".\n";
			SYMERRORTOK("Pace statement must be followed by a positive number",errSyntax,vExpLine[iLeft]);
			bResult = false;
			}
	
	return bResult;
}
