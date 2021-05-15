// ArraySeries.cpp: implementation of the CArraySeries class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Tokeniser.h"
#include "ArraySeries.h"
#include "Symlix\ErrorFactory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CArraySeries::CArraySeries(long iLeft,long iRight,vector<CToken*>& vExpLine, ostream& osErrReport/*=cerr*/):CArraySetValue_Impl()
{

	ASSERT2(m_pToken==NULL);
	if (!check(iLeft,iRight,vExpLine,osErrReport)) // you should always have called the static check function first anyway
		{
		m_eState = carError;
		m_sError = "Failed internal check for creating a Series Array";
		SYMERRORLITE(m_sError.c_str(),errInternal);
		}
		else
		{
		ASSERT2((iLeft>=0)&&(iLeft<vExpLine.size())); // this really should ahve been caught in the check
		vector<CToken*>::iterator it = &vExpLine[iLeft];
		vector<CToken*>::const_iterator itRight = CNavTokens::getRightWithoutComments(iLeft,iRight,vExpLine);

		m_pToken = (*it);
		it++;
		ASSERT2(it!=itRight);
		

		while(((*it)->getStringRef().compare(g_CloseCurlyBracket)!=0)&&(++it!=itRight))
			{
			ATLTRACE("(*it) is '%s'\n",(*it)->getString().c_str());
			if ((*it)->IsOfType(ctNumber))
					m_vecValues.push_back((*it++)->getNumber());
			}

		if (m_vecValues.size()>0)
			m_eState = carIntiated;		


		setupIndexesFromLHSToken();


		// amend token name
		cleanUpTokenNameAndSetAsArray();
		}


}

CArraySeries::~CArraySeries()
{
	// bye cruel world
}


///////////////////////////////////////////////////////////
// Function name	: CArraySeries::check
// Description	    : static function to check a line is formated acceptably
//                    if it fails it will also fail on creation of a CArraySeries object
// Return type		: bool 
// Argument         : long iLeft
// Argument         : long iRight
// Argument         : vector<CToken*>& vExpLine
// Argument         : ostream& osErrReport
///////////////////////////////////////////////////////////
bool CArraySeries::check(long iLeft,long iRight,vector<CToken*>& vExpLine, ostream& osErrReport)
{
    // eg array a[]={1,2,45,67,-6E45}
	long iIndexSize =0;
	long iValuesSize =0;
	vector< CToken* >::iterator itpCT;
	// itpCTRight is found this way as I'm not sure &vExp[iRight] would produce the same result in all conditions
	vector< CToken* >::const_iterator itpCTRight;

	itpCTRight = CNavTokens::getRightWithoutComments(iLeft,iRight,vExpLine);

	if ((iRight<=iLeft)||(iRight==0))
			{
			osErrReport << "<Internal Error*> Array series cannot be read and is badly formed.\n";
			SYMERRORLITE("Array series cannot be read",errInternal);
			return false;
			}

	if (vExpLine.size()<6) // then there cannot be enough information for this array type
			{
			if (vExpLine.size()<iLeft)
				{
				osErrReport << "<*Error*> Array series does not have enough information and is badly formated.\n";
				SYMERRORTOK("Array series does not have enough information and is badly formated",errInternal,vExpLine[iLeft]);
				}
				else
				{
				osErrReport << "<*Error*> Array series does not have enough information and is badly formated.\n";
				SYMERRORTOK("Array series does not have enough information and is badly formated",errSyntax,vExpLine[iLeft]);
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
	if (!(*itpCT)->IsOfTypeVariable())
			{
				osErrReport << "<*Error*> Variable expected.\n";
				SYMERRORTOK2("Variable expected after",g_Array,errSyntax,(*itpCT));
				#ifndef NDEBUG
				osErrReport << (**itpCT) <<endl;
				#endif
				return false;
			}

	iIndexSize = CArray::checkArrayName(**itpCT);
	if (iIndexSize<0)
			{
			osErrReport << "Problem with array declaration "<<(*itpCT)->getString().c_str()<<endl;
			// no SYMERROR needed as it will have been called in checkArrayName
			return false;

			}

	itpCT++;

	if ((!(*itpCT)->IsOfType(ctDelim))||((*itpCT)->getStringRef().compare(g_Eq)!=0))
			{
				osErrReport << "<*Error*> " << g_Eq<<" expected. "<<(**itpCT)<<"\n";
				SYMERRORTOK2(g_Eq," expected",errSyntax,(*itpCT));
				return false;
			}
	itpCT++;


	if ((!(*itpCT)->IsOfType(ctDelim))||((*itpCT)->getStringRef().compare(g_OpenCurlyBracket)!=0))
			{
				osErrReport << "<*Error*> " << g_OpenCurlyBracket<<" expected. "<<(**itpCT)<<"\n";
				SYMERRORTOK2(g_OpenCurlyBracket," expected",errSyntax,(*itpCT));
				return false;
			}

	itpCT++;
	if (!(*itpCT)->IsOfType(ctNumber))
			{
				osErrReport << "<*Error*> Number expected expected.\n";
				SYMERRORTOK2("Number expected after ",g_OpenCurlyBracket,errSyntax,(*itpCT));
				return false;
			}

	while(((++itpCT)!=itpCTRight)&&((*itpCT)->getStringRef().compare(g_Comma)==0))
	{
		if ((++itpCT)==itpCTRight)
				{
					osErrReport << "<*Error*> Number expected expected.\n";
					SYMERRORTOK2("Number expected after ",(*--itpCT)->getStringRef().c_str(),errSyntax,(*itpCT));
					return false;
				}

		if (!(*itpCT)->IsOfType(ctNumber))
				{
					osErrReport << "<*Error*> Number expected expected.\n";
					SYMERRORTOK2("Number expected after ",(*--itpCT)->getStringRef().c_str(),errSyntax,(*++itpCT));
					return false;
				}
		iValuesSize++; // check how many values
	}

	if (itpCT==itpCTRight) // then reached the end before closing brackets
			{
				osErrReport << "<*Error*> Missing " << g_CloseCurlyBracket << " at end of series array.\n";
				SYMERRORTOK2("Array statement incomplete ",g_CloseCurlyBracket,errSyntax,(*--itpCT));
				return false;
			}


	if ((*itpCT)->getStringRef().compare(g_CloseCurlyBracket)!=0)
			{
				osErrReport << "<*Error*> Misplaced or missing " << g_CloseCurlyBracket << " at end of series array.\n";
				SYMERRORTOK2("Array sequence of values not close with ",g_CloseCurlyBracket,errSyntax,(*itpCT));
				return false;
			}
	iValuesSize++; // as last number missing in index

	if ((iIndexSize!=0)&&(iIndexSize!=iValuesSize)) // if indicies have been given then they must match the values
		{
			osErrReport << "Indicies declared and implied by values don't match\n";
			ATLTRACE("Indicies %d , values %d \n",iIndexSize,iValuesSize);
			SYMERRORTOK("The Indicies and values given don't match",errSyntax,(*itpCT));
			return false;
		}

	// don't care what comes next

	return true;
}


void CArraySeries::out( ostream& os ) const
{
	int iCount=0;
	vector<long>::const_iterator cind;
	vector<variable>::const_iterator cAr;
	if (!m_pToken)
		{
		os << "[CArraySeries] Token Error"<<endl;
		return;
		}
	os << "[CArraySeries] Token '"<<m_pToken->getString().c_str()<<"'";
	os << " Array size "<<m_vecValues.size()<<"\n";

	cind=m_vecIndicies.begin();
	cAr=m_vecValues.begin();

	while((cind!=m_vecIndicies.end())&&(cAr!=m_vecValues.end()))
	{
		if (iCount<ARRAY_LINE_COUNT)
			{
			os <<"["<<*cind<<"] "<<*cAr<<"\t";
			iCount++;
			}
			else
			{
			os <<"["<<*cind<<"] "<<*cAr<<"\n";
			iCount=0;
			}
	cind++;
	cAr++;
	}
	if (iCount!=0)
		os<<"\n";

	ASSERT2(m_vecIndicies.size()==m_vecValues.size());

}


///////////////////////////////////////////////////////////
// Function name	: CArraySeries::getToken
// Description	    : return pointer to CToken* of current index
// Return type		: CToken* 
///////////////////////////////////////////////////////////
/*
CToken* CArraySeries::getToken()
{

	ASSERT2(m_iInd>=0);
	if (m_iInd>=m_vecToks.size())
		return NULL;

	return m_vecToks[m_iInd];
}


///////////////////////////////////////////////////////////
// Function name	: CArraySeries::addTokenPtVec
// Description	    : Add a vector of CToken* - only if same size as index vector
// Return type		: bool 
// Argument         : const vector< CToken* >& rvecpt
///////////////////////////////////////////////////////////
bool CArraySeries::addTokenPtVec(const vector< CToken* >& rvecpt)
{

	ASSERT2(rvecpt.size()==m_vecIndicies.size());
	// only do this if the index sizes match !
	if (rvecpt.size()!=m_vecIndicies.size())
			return false;

	m_vecToks = rvecpt;
	return true;
}
*/

#ifndef NDEBUG
///////////////////////////////////////////////////////////
// Function name	: CArraySeries::unitTests
// Description	    : Debug only function designed to catch coding faults with unit tests
// Return type		: bool 
///////////////////////////////////////////////////////////
bool CArraySeries::unitTests()
{

	bool bResults = true;
    CTestHoldTokeniser cht;
	
	//test 1 - should pass
    vector<CToken*>& rvecTok = cht.getRefVectorOfTokenPointers(1,"array a[]={1,2,3,4}","Test");
	cht.assignVariables(rvecTok);
	bResults &= CArraySeries::check(1,rvecTok.size(),rvecTok,cerr);
	
	//test 2 - should pass
	rvecTok = cht.getRefVectorOfTokenPointers(1,"array a={1,2,3,4}","Test");
	cht.assignVariables(rvecTok);
	bResults &= CArraySeries::check(1,rvecTok.size(),rvecTok,cerr);

	//test 3 - should fail
	rvecTok = cht.getRefVectorOfTokenPointers(0,"","Test");
	cht.assignVariables(rvecTok);
	bResults &= !CArraySeries::check(0,rvecTok.size(),rvecTok,cerr);

	//test 4 - should fail
    rvecTok = cht.getRefVectorOfTokenPointers(1,"a[]={1,2,3,4} // comments here a","Test");
	cht.assignVariables(rvecTok);
	bResults &= !CArraySeries::check(0,rvecTok.size(),rvecTok,cerr);

	//test 5 - should pass
    rvecTok = cht.getRefVectorOfTokenPointers(1,"array a[1,2,3:4]={1,2,3,4} // comments here a","Test");
	cht.assignVariables(rvecTok);
	bResults &= CArraySeries::check(1,rvecTok.size(),rvecTok,cerr);

	//test 6 - should fail
    rvecTok = cht.getRefVectorOfTokenPointers(1,"array a[,2,3:4]={1,2,3,4} // comments here a","Test");
	cht.assignVariables(rvecTok);
	bResults &= !CArraySeries::check(1,rvecTok.size(),rvecTok,cerr);

	//test 7 - should fail
    rvecTok = cht.getRefVectorOfTokenPointers(1,"array a[1,-2,3:4]={1,2,3,4} // comments here a","Test");
	cht.assignVariables(rvecTok);
	bResults &= !CArraySeries::check(1,rvecTok.size(),rvecTok,cerr);

	//test 8 - should fail
    rvecTok = cht.getRefVectorOfTokenPointers(1,"array a[1,2,3E02:4]={1,2,3,4} // comments here a","Test");
	cht.assignVariables(rvecTok);
	bResults &= !CArraySeries::check(1,rvecTok.size(),rvecTok,cerr);

	//test 9 - should fail
    rvecTok = cht.getRefVectorOfTokenPointers(1,"array a[1,2,:4]={1,2,3,4} // comments here a","Test");
	cht.assignVariables(rvecTok);
	bResults &= !CArraySeries::check(1,rvecTok.size(),rvecTok,cerr);

	//test 10 - should fail
    rvecTok = cht.getRefVectorOfTokenPointers(1,"array a[1,2,4,2]={1,2,3,4} // comments here a","Test");
	cht.assignVariables(rvecTok);
	bResults &= !CArraySeries::check(1,rvecTok.size(),rvecTok,cerr);

	//test 11 - should pass
    rvecTok = cht.getRefVectorOfTokenPointers(1,"array a[0,2,4,34]={1,2,3,4} // comments here a","Test");
	cht.assignVariables(rvecTok);
	bResults &= CArraySeries::check(1,rvecTok.size(),rvecTok,cerr);

	//test 12 - should fail
    rvecTok = cht.getRefVectorOfTokenPointers(1,"array a[0,2,4,34,7]={1,2,3,4} // comments here a","Test");
	cht.assignVariables(rvecTok);
	bResults &= !CArraySeries::check(1,rvecTok.size(),rvecTok,cerr);

	//test 13 - should fail
    rvecTok = cht.getRefVectorOfTokenPointers(1,"array a[4:8]={1,2,3,4} // comments here a","Test");
	cht.assignVariables(rvecTok);
	bResults &= !CArraySeries::check(1,rvecTok.size(),rvecTok,cerr);

	//test 14 - should pass
    rvecTok = cht.getRefVectorOfTokenPointers(1,"array a[5:8]={1,2,3,4} // comments here a","Test");
	cht.assignVariables(rvecTok);
	bResults &= CArraySeries::check(1,rvecTok.size(),rvecTok,cerr);

	//test 15 - should pass
    rvecTok = cht.getRefVectorOfTokenPointers(1,"array a[1]={1} // comments here a","Test");
	cht.assignVariables(rvecTok);
	bResults &= CArraySeries::check(1,rvecTok.size(),rvecTok,cerr);

	//test 16 - should pass
    rvecTok = cht.getRefVectorOfTokenPointers(1,"array a[1,4:6]={1,2,3,4} // comments here a","Test");
	cht.assignVariables(rvecTok);
	bResults &= CArraySeries::check(1,rvecTok.size(),rvecTok,cerr);


	return bResults;
}

#endif
