// EvDumpEquations.cpp: implementation of the CEvDumpEquations class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EvDumpEquations.h"
#include "Symlix/ErrorFactory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEvDumpEquations::CEvDumpEquations( long iLeft, long iRight, vector< CToken* >& vecLine,ostream& oserr,ListLineTokenPts& rvecEqVecs)
{
	if (check(iLeft,iRight,vecLine,oserr))
		{
		vector< CToken* >::iterator itpCT = &vecLine[iLeft+3]; // should be file name
		ofstream ofs;
		
		ofs.open((*itpCT)->getString().c_str());
	
		ofs << "Equation dump\n";
		ofs << "=============\n";

		ListLineTokenPts::const_iterator itEq;
		vector < CToken* >::const_iterator it;
		long iCount=1;

		for( itEq=rvecEqVecs.begin();itEq!=rvecEqVecs.end();itEq++)
			{
			ofs << iCount++ <<":\t";
			for ( it=itEq->begin(); it!=itEq->end();it++)
				ofs << (*it)->getString().c_str();
			ofs <<"\n";
			}

		ofs << endl;

		ofs.close();
		m_eState = cevFired;
		}
		else
		{
		SYMERRORLITE("Unable to set up dump of equations",errWarning);
		}



}

CEvDumpEquations::~CEvDumpEquations()
{

}


///////////////////////////////////////////////////////////
// Function name	: CEvDumpEquations::check
// Description	    : 
// Return type		: bool 
// Argument         : long iLeft
// Argument         : long iRight
// Argument         : vector<CToken*>& vExpLine
// Argument         : ostream& osErrReport
///////////////////////////////////////////////////////////
bool CEvDumpEquations::check(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport )
{
	vector< CToken* >::iterator itpCT;
	// itpCTRight is fouud this way as I'm not sure &vExp[iRight] would produce the same result in all conditions
	vector< CToken* >::const_iterator itpCTRight = getRightWithoutComments(iLeft,iRight,vExpLine);
	bool bDelim =true;


	if (iLeft==iRight) // may not be necessary as doesn't seem to get here.
			return false;

	if (iRight-iLeft<5)
			{
			SYMERRORTOK("Event declartion not complete.",errSyntax,vExpLine[iLeft]);
			return false;
			}

	itpCT = &vExpLine[iLeft];

	if ((!(*itpCT)->IsOfType(ctEventKeyWord))||((*itpCT)->getString().compare(g_Equations)!=0))
			{
				osErrReport << "<Error*> '" << g_Equations << "' expevcted, not '"<<(*itpCT)->getStringRef().c_str()<< "' on line "<< (*itpCT)->getLine()<<endl;
				SYMERRORTOK2(g_Equations," expected here.",errSyntax,(*itpCT));
				return false;
			}
		
	if ((!(*++itpCT)->IsOfType(ctEventKeyWord))||((*itpCT)->getString().compare(g_As)!=0))
			{
				osErrReport << "<Error*> '" << g_As << "' expevcted, not '"<<(*itpCT)->getStringRef().c_str()<< "' on line "<< (*itpCT)->getLine()<<endl;
				SYMERRORTOK2(g_As," expected here.",errSyntax,(*itpCT));
				return false;
			}

	itpCT++;

	if (itpCT==itpCTRight)
			{
			SYMERRORTOK("Part of event statement is missing",errSyntax,(*--itpCT));
			osErrReport << "<Error*> Part of event statement is missing on line "<<(*itpCT)->getLine()<<endl;
			return false;
			}

	if (!((*itpCT)->getString().compare(g_Quote)==0))
			{
			osErrReport << "<Error*> File name not in quotes on line "<<(*itpCT)->getLine()<<endl;
			SYMERRORTOK("Stream name not in quotes",errSyntax,(*itpCT));
			return false;
			}

	if (++itpCT==itpCTRight)
			{
			SYMERRORTOK("Part of event statement is missing",errSyntax,(*--itpCT));
			osErrReport << "<Error*> Part of event statement is missing on line "<<(*itpCT)->getLine()<<endl;
			return false;
			}

	if (!(*itpCT)->IsOfType(ctName))
			{
			osErrReport << "<Error*> Part of event statement is missing on line "<<(*itpCT)->getLine()<<endl;
			SYMERRORTOK("Part of event statement is missing",errSyntax,(*itpCT));
			return false;
			}

	if (++itpCT==itpCTRight)
			{
			SYMERRORTOK("Part of event statement is missing",errSyntax,(*--itpCT));
			osErrReport << "<Error*> Part of event statement is missing on line "<<(*itpCT)->getLine()<<endl;
			return false;
			}

	if (!((*itpCT)->getString().compare(g_Quote)==0))
			{
			osErrReport << "<Error*> File name not in quotes on line "<<(*itpCT)->getLine()<<endl;
			SYMERRORTOK("Stream name not in quotes",errSyntax,(*itpCT));
			return false;
			}

	return true;
}


///////////////////////////////////////////////////////////
// Function name	: CEvDumpEquations::setupEvent
// Description	    : Needed to be overridden from parent
// Return type		: bool 
// Argument         : list<CEquation*>* pvecpEquations
///////////////////////////////////////////////////////////
bool CEvDumpEquations::setupEvent(list<CEquation*>* pvecpEquations)
{
	
	if (isInError())
		return false;

	return true;

}