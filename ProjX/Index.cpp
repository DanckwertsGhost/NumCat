// Index.cpp: implementation of the CIndex class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Index.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIndex::CIndex():m_eState(cindUninitated),m_bHaveFirstUse(false),m_pExpand(NULL)
{

}

CIndex::~CIndex()
{

}


/*friend*/ ostream& operator << (ostream& os, const CIndex* pI)
{
	pI->out(os);

	return os;
}

///////////////////////////////////////////////////////////
// Function name	: CIndex::checkForExpression
// Description	    : Helper static function to see that 
//                    a series of numbers anddelims is OK
//                    ritpCT is returned with the value after the last number
// Return type		: long 
// Argument         : vector< CToken* >::iterator& ritpCT
// Argument         : vector< CToken* >::const_iterator citEnd
///////////////////////////////////////////////////////////
long CIndex::checkForExpression(vector< CToken* >::iterator& ritpCT, vector< CToken* >::const_iterator citEnd)
{
/*
	Looking for number, recognised delim, number
	if anything else then return pointing to that Token
*/
	bool bDelim = false;
	bool bCarryOn = true;
	long iResult = NOT_DEFINED;
	bool bPlus = true;
	bool bFirst=true;

	if (ritpCT==citEnd)
			return NOT_DEFINED;

	do
	{
	if (bDelim)
		{
		bDelim = false;
		if (!(*ritpCT)->IsOfType(ctDelim))
			if ((*ritpCT)->IsOfType(ctNumber)) // happens if macro subsitution of numbers
					iResult+=(*ritpCT)->getNumber(); // covers negative number also
					else
					bCarryOn=false;
			else
			if ((*ritpCT)->getString().compare(g_Minus)==0)
				{
				bPlus = false;
				}
				else
				if ((*ritpCT)->getString().compare(g_Plus)==0)
					{
					bPlus = true;
					}
					else
					bCarryOn=false;
		}
		else
		{
		if ((*ritpCT)->IsOfType(ctNumber))
			{
			if (bFirst)
				{
				iResult = (*ritpCT)->getNumber();
				bFirst = false;
				}
				else
				if (bPlus)
					iResult += (*ritpCT)->getNumber();
					else
					iResult -= (*ritpCT)->getNumber();
			}
			else
			bCarryOn = false;
		bDelim=true;
		}

	if (bCarryOn)
		ritpCT++;

	}
	while((ritpCT!=citEnd)&&(bCarryOn));

	ritpCT--; // so the misplaced symbol will be picked up

	return iResult;
} 



