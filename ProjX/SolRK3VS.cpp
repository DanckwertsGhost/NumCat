// SolRK3VS.cpp: implementation of the CSolRK3VS class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SolRK3VS.h"
#include "Symlix/ErrorFactory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
// Function name	: CSolRK3VS::check
// Description	    : Assumes check run on line one token beyond solver keyword
// Return type		: bool 
// Argument         : long iLeft
// Argument         : long iRight
// Argument         : vector<CToken*>& vExpLine
// Argument         : ostream& osErrReport
///////////////////////////////////////////////////////////
bool CSolRK3VS::check(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport )
{

	long iEnd = getPosRightWithoutComments(iLeft,iRight,vExpLine);
	
	if (iLeft!=iEnd-1) // then format for solver statement is wrong
		{
		if ((iEnd-iLeft)>3)
				{
				if ((iEnd-iLeft)>5)
					{
					osErrReport << "<Error*> RK3VS solver defintion has an error - try reducing the number of statements.\n";
					SYMERRORTOK("RK3VS solver defintion has an error - try reducing the number of statements",errSyntax,vExpLine[iLeft]);
					return false;
					}
				if ((iEnd-iLeft)<5) 
					{
					osErrReport << "<Error*> RK3VS solver defintion has an error - check "<< g_Tolerance <<" term or length of solver statement.\n";
					SYMERRORTOK("RK3VS solver defintion has an error",errSyntax,vExpLine[iLeft]);
					return false;
					}
				if ((!vExpLine[iLeft+3]->IsOfType(ctSolverKeyWord))||(vExpLine[iLeft+3]->getString().compare(g_Tolerance)!=0))
					{
					osErrReport << "<Error*> RK3VS solver defintion needs either a "<< g_Tolerance <<" term after step or no further terms to use default.\n";
					SYMERRORTOK2("RK3VS solver defintion looking for: ",g_Tolerance,errSyntax,vExpLine[iLeft+3]);
					return false;
					}
				if (!vExpLine[iLeft+4]->IsOfType(ctNumber))
					{
					osErrReport << "<Error*> RK3VS solver "<< g_Tolerance <<" needs to be followed by a number.\n";
					SYMERRORTOK2(g_Tolerance," for RK3VS solver needs to be followed by number",errSyntax,vExpLine[iLeft+4]);
					return false;
					}
				if (vExpLine[iLeft+4]->getNumber()<=0)
					{
					osErrReport << "<Error*> RK3VS solver "<< g_Tolerance <<" needs to be a number greater than 0.\n";
					SYMERRORTOK2(g_Tolerance," for RK3VS solver needs to be followed by positive number",errSyntax,vExpLine[iLeft+4]);
					return false;
					}
				}

		if ((iEnd-iLeft)<3)
				{
				osErrReport << "<Error*> RK3VS solver defintion has an error - the expression is missing term(s).\n";
				SYMERRORTOK("RK3VS solver defintion has an error - the expression is missing term(s)",errSyntax,vExpLine[0]);
				return false;
				}

		if ((!vExpLine[iLeft+1]->IsOfType(ctSolverKeyWord))||(vExpLine[iLeft+1]->getString().compare(g_Step)!=0))
				{
				osErrReport << "<Error*> RK3VS solver defintion needs a '"<<g_Step <<"' statement.\n";
				SYMERRORTOK2("RK3VS solver defintion needs a further statement: ",g_Step,errSyntax,vExpLine[iLeft+1]);
				return false;
				}

		if (!vExpLine[iLeft+2]->IsOfType(ctNumber))
				{
				osErrReport << "<Error*> RK3VS solver step a step size.\n";
				SYMERRORTOK("RK3VS solver step needs a step size",errSyntax,vExpLine[iLeft+2]);
				return false;
				}

		if (vExpLine[iLeft+2]->getNumber()<=0)
				{
				osErrReport << "<Error*> RK3VS solver step needs to be greater than zero .\n";
				SYMERRORTOK("RK3VS solver step needs to be greater than zero",errSyntax,vExpLine[iLeft+2]);
				return false;
				}

		}

/* Don't believe this is necessary as has already been identified in class factory
	if (vExpLine[iLeft]->getString().compare(g_RK3VS)==0)
		return true;

	return false;*/
	return true;
}