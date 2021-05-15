// IndexExpandPoint.cpp: implementation of the CIndexExpandPoint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IndexExpandPoint.h"
#include "Symlix\ErrorFactory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIndexExpandPoint::CIndexExpandPoint( long iLeft,long iRight,vector<CToken*>& vExpLine, ostream& osErrReport/*=cerr*/):m_pTokenExpandPoint(NULL),m_iOffsetLines(0)
{


#ifndef NDEBUG
	ASSERT2(check(iLeft,iRight,vExpLine,osErrReport));
#endif

	if (iLeft<vExpLine.size())
		m_pTokenExpandPoint = vExpLine[iLeft];

	ASSERT2(m_pTokenExpandPoint);
}

CIndexExpandPoint::~CIndexExpandPoint()
{

}

bool CIndexExpandPoint::check(long iLeft,long iRight,vector<CToken*>& vExpLine, ostream& osErrReport)
{

	vector< CToken* >::iterator itpCT;
	// itpCTRight is found this way as I'm not sure &vExp[iRight] would produce the same result in all conditions
	vector< CToken* >::const_iterator itpCTRight;

	itpCTRight = CNavTokens::getRightWithoutComments(iLeft,iRight,vExpLine);

	if ((iRight<=iLeft)||(iRight==0))
			{
			osErrReport << "<Internal Error*> Expand code cannot be read and is badly formed.\n";
			SYMERRORLITE("Expand instruction cannot be read",errInternal);
			return false;
			}

	if (vExpLine.size()<2) // then there cannot be enough information for this Index type
			{
			if (vExpLine.size()<iLeft)
				{
				osErrReport << "<*Error*> Index expansion point does not have enough information and is badly formated.\n";
				SYMERRORTOK(" Index expansion point does not have enough information and is badly formated",errInternal,vExpLine[iLeft]);
				}
				else
				{
				osErrReport << "<*Error*> Index expansion point does not have enough information and is badly formated.\n";
				SYMERRORTOK(" Index expansion point does not have enough information and is badly formated",errSyntax,vExpLine[iLeft]);
				}
			return false;
			}

	// so there is some prospect of this working

	itpCT = &vExpLine[iLeft];

	#ifndef NDEBUG
	osErrReport << (**itpCT) <<endl;
//	osErrReport << (*itpCT++)->getStringRef().c_str() <<endl;
//	itpCT--;
	#endif
	if (!(*itpCT)->IsOfType(ctNotDefined))
			{
				osErrReport << "<*Error*> Variable expected.\n";
				SYMERRORTOK2("Variable expected after ",g_Index,errSyntax,(*itpCT));
				#ifndef NDEBUG
				osErrReport << (**itpCT) <<endl;
				#endif
				return false;
			}


	itpCT++;
	if ((!(*itpCT)->IsOfType(ctMacroKeyWord))||((*itpCT)->getStringRef().compare(g_Here)!=0))
			{
				osErrReport << "<*Error*> " << g_Here <<" expected. "<<(**itpCT)<<"\n";
				SYMERRORTOK2(g_Here," expected",errSyntax,(*itpCT));
				return false;
			}




	return true;
}

bool CIndexExpandPoint::operator < (const CToken& rct ) const
{
	bool bResult;

	ASSERT2(m_pTokenExpandPoint);
	if (!m_pTokenExpandPoint)
		return true; // not great, but need to do something

	bResult = (*m_pTokenExpandPoint).getLocation() < rct.getLocation();

	return bResult;
}

bool CIndexExpandPoint::operator > (const CToken& rct ) const
{
	bool bResult;

	ASSERT2(m_pTokenExpandPoint);
	if (!m_pTokenExpandPoint)
		return false; // not great, but need to do something

	bResult = (*m_pTokenExpandPoint).getLocation() > rct.getLocation();

	return bResult;
}
