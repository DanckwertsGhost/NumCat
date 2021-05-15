// TempSetFix.cpp: implementation of the CTempSetFix class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TempSetFix.h"
#define TEMPSETFIX 5 // as create all these objects keep value smaller
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////
// Function name	: CTempSetFix::CTempSetFix
// Description	    : Default constructor
///////////////////////////////////////////////////////////
CTempSetFix::CTempSetFix():m_iStep(TEMPSETFIX),m_iLength(0)
{
	m_ppSetWords = newtrack setofwords::const_iterator[m_iStep];
}

CTempSetFix::~CTempSetFix()
{

	// since we don't have STL to play with here - lets do it the old fashioned way
	delete[] m_ppSetWords;
}


///////////////////////////////////////////////////////////
// Function name	: CTempSetFix::insert
// Description	    : Try to insert a version - but return a copy of the
//                    version ultimately held in the set
// Return type		: setofwords::const_iterator 
// Argument         : setofwords::const_iterator& cit
///////////////////////////////////////////////////////////
setofwords::const_iterator CTempSetFix::insert(setofwords::const_iterator& cit )
{
	if (!find(cit))
			add(cit);

	return cit; // yes we really can do this
}


///////////////////////////////////////////////////////////
// Function name	: CTempSetFix::add
// Description	    : add iterator to array. Extend array if necessary
//                    Note the array is fully populated - only a 
//                    record of how much of it has been assigned is kept.
// Return type		: void 
// Argument         : setofwords::const_iterator& cit
///////////////////////////////////////////////////////////
void CTempSetFix::add(setofwords::const_iterator& cit)
{
	long iNext = m_iLength+1;
	long iT;

	if (iNext>=m_iStep)
		{
		 setofwords::const_iterator* ppTemp= newtrack setofwords::const_iterator[m_iLength];
		 
		 for(iT=0;iT<m_iLength;iT++)
			{
			 ppTemp[iT] = m_ppSetWords[iT];
			}

		 delete[] m_ppSetWords;	
		 
		 m_iStep+=TEMPSETFIX;
		 
		 m_ppSetWords = newtrack setofwords::const_iterator[m_iStep]; 

		 for(iT=0;iT<m_iLength;iT++)
			{
			m_ppSetWords[iT] = ppTemp[iT];
			}

		 delete[] ppTemp;		 

		}
	m_ppSetWords[m_iLength] = cit;
	m_iLength++;


}



///////////////////////////////////////////////////////////
// Function name	: CTempSetFix::find
// Description	    : find iterator on set
// Return type		: bool 
// Argument         : const setofwords::const_iterator& cit
///////////////////////////////////////////////////////////
bool CTempSetFix::find(const setofwords::const_iterator& cit) const
{
	bool bResult = false;
	long iCount=0;
	while((!bResult)&&(iCount<m_iLength))
		bResult= (m_ppSetWords[iCount++]==cit);

	return bResult;
}


///////////////////////////////////////////////////////////
// Function name	: friend operator << 
// Description	    : Mostly for debug
// Return type		: ostream& operator 
// Argument         : ostream& os
// Argument         : const CTempSetFix& ctsf
///////////////////////////////////////////////////////////
ostream& operator << (ostream& os, const CTempSetFix& ctsf )
{
	for (long iT=0;iT<ctsf.m_iLength;iT++)
		{
		os << ctsf.m_ppSetWords[iT]->c_str();
		if (iT<ctsf.m_iLength-1)
					os <<"\t";
		}

	return os;

}