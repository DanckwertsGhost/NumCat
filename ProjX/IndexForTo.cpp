// IndexForTo.cpp: implementation of the CIndexForTo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IndexForTo.h"
#include "Tokeniser.h"
#include "Symlix\ErrorFactory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIndexForTo::CIndexForTo(long iLeft,long iRight,vector<CToken*>& vExpLine, ostream& osErrReport/*=cerr*/):CIndex(),m_iCurrent(NOT_DEFINED),m_iFrom(NOT_DEFINED),m_iStep(1L),m_iTo(NOT_DEFINED),m_bNeg(false)
{
	if (!check(iLeft,iRight,vExpLine,osErrReport)) // you should always have called the static check function first anyway
		{
		m_eState = cindError;
		m_sError = "Failed internal check for creating a Series Array";
		SYMERRORLITE(m_sError.c_str(),errInternal);
		}
		else
		{
		ASSERT2((iLeft>=0)&&(iLeft<vExpLine.size())); // this really should have been caught in the check
		vector<CToken*>::iterator it = &vExpLine[iLeft];
		vector<CToken*>::const_iterator itRight = CNavTokens::getRightWithoutComments(iLeft,iRight,vExpLine);

		m_sIndex = (*it)->getString();

		it++;
		ASSERT2(it!=itRight);
		it++;
		ASSERT2(it!=itRight);

		m_iFrom = CIndex::checkForExpression(it,itRight);

		ASSERT2(m_iFrom!=NOT_DEFINED);

		it++;
		ASSERT2(it!=itRight);
		it++;
		ASSERT2(it!=itRight);

		m_iTo = CIndex::checkForExpression(it,itRight);

		it++;
		if ((it++!=itRight)&&(it!=itRight))
			{
			m_iStep = (*it)->getNumber();
			ASSERT2((*it)->IsOfType(ctNumber));
			}
		
		m_iTo -= ((m_iTo-m_iFrom)%m_iStep); // necessary since may start from last item in series
		m_iCurrent = m_iFrom;
		m_eState = cindIntiated;
		if (m_iStep<0)
			m_bNeg = true;

		}
}

CIndexForTo::~CIndexForTo()
{

}


bool CIndexForTo::check(long iLeft,long iRight,vector<CToken*>& vExpLine, ostream& osErrReport)
{
	variable vFrom =0; // not integer as will check that they are latter
	variable vTo =0;
	variable vStep=1;
	long iFrom=NOT_DEFINED;
	long iTo=NOT_DEFINED;
	long iStep=NOT_DEFINED;
	variable vError;
	vector< CToken* >::iterator itpCT;
	// itpCTRight is found this way as I'm not sure &vExp[iRight] would produce the same result in all conditions
	vector< CToken* >::const_iterator itpCTRight;

	itpCTRight = CNavTokens::getRightWithoutComments(iLeft,iRight,vExpLine);

	if ((iRight<=iLeft)||(iRight==0))
			{
			osErrReport << "<Internal Error*> Index series cannot be read and is badly formed.\n";
			SYMERRORLITE("Index series cannot be read",errInternal);
			return false;
			}

	if (vExpLine.size()<6) // then there cannot be enough information for this Index type
			{
			if (vExpLine.size()<iLeft)
				{
				osErrReport << "<*Error*> Index series does not have enough information and is badly formated.\n";
				SYMERRORTOK("Index series does not have enough information and is badly formated",errInternal,vExpLine[iLeft]);
				}
				else
				{
				osErrReport << "<*Error*> Index series does not have enough information and is badly formated.\n";
				SYMERRORTOK("Index series does not have enough information and is badly formated",errSyntax,vExpLine[iLeft]);
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
	if ((!(*itpCT)->IsOfType(ctDelim))||((*itpCT)->getStringRef().compare(g_Eq)!=0))
			{
				osErrReport << "<*Error*> " << g_Eq<<" expected. "<<(**itpCT)<<"\n";
				SYMERRORTOK2(g_Eq," expected",errSyntax,(*itpCT));
				return false;
			}

	itpCT++;


	vFrom = CIndex::checkForExpression(itpCT,itpCTRight);

	if (itpCT==itpCTRight)
			{
				osErrReport << "<*Error*> expression not complete\n";
				SYMERRORTOK("Index expression not complete",errSyntax,vExpLine[iLeft]);
				return false;
			}

	if (vFrom==NOT_DEFINED)
			{
				osErrReport << "<*Error*> a number expected. "<<(**itpCT).getString().c_str()<<"\n";
				SYMERRORTOK("A number or simple expression expected",errSyntax,(*itpCT));
				return false;
			}

	if ((++itpCT==itpCTRight)||((*itpCT)->getString().compare(g_FullColon)!=0))
			{
				osErrReport << "<*Error*> '"<< g_FullColon << "' expected.\n";
				SYMERRORTOK2(g_FullColon," expected.",errSyntax,(*itpCT));
				return false;
			}

	vTo = CIndex::checkForExpression(++itpCT,itpCTRight);

	if (vTo==NOT_DEFINED)
			{
				if (itpCT==itpCTRight)
							{
								osErrReport << "<*Error*> expression not complete\n";
								SYMERRORTOK("Index expression not complete",errSyntax,vExpLine[iLeft]);
								return false;
							}

				osErrReport << "<*Error*> a number expected. "<<(**itpCT).getString().c_str()<<"\n";
				SYMERRORTOK("A number expected or simple expression expected",errSyntax,(*itpCT));
				return false;
			}

	if ((itpCT!=itpCTRight)&&(++itpCT!=itpCTRight))
		{
		if ((*itpCT)->getString().compare(g_Step)!=0)
			{
				#ifndef NDEBUG
				CToken& rT = (**itpCT); // to help with debuging
				#endif
				osErrReport << "<*Error*> expected "<< g_Step <<" , but had "<<(**itpCT).getString().c_str()<<"\n";
				SYMERRORTOK2("Expected a ",g_Step,errSyntax,(*itpCT));
				return false;
			}

		itpCT++;
		if (itpCT==itpCTRight)
			{
				osErrReport << "<*Error*> missing number after "<< g_Step <<" ."<<(**--itpCT).getString().c_str()<<"\n";
				SYMERRORTOK2("A number expected after ",g_Step,errSyntax,(*itpCT));
				return false;
			}
		if (!(*itpCT)->IsOfType(ctNumber))
			{
				osErrReport << "<*Error*> a number expected. "<<(**itpCT).getString().c_str()<<"\n";
				SYMERRORTOK("A number expected",errSyntax,(*itpCT));
				return false;
			}

		vStep = (*itpCT)->getNumber();
		ATLTRACE("CIndexForTo::check after step number '%s' = %f\n",(*itpCT)->getString().c_str(),vStep);

		} // endif (itpCT!=	itpCTRight)
		
	// don't care what comes next

	// now check all number are integers - or at least close
	iFrom = vFrom;
	iTo = vTo;
	iStep = vStep;

	vError = fabs(float(iFrom)-vFrom)+fabs(float(iTo)-vTo)+fabs(float(iStep)-vStep);

	if (vError>1E-5)
		{
		osErrReport << "<*Error*> only intgers can be used ."<<(**--itpCT).getString().c_str()<<"\n";
		SYMERRORTOK2("Only integers can be used in a ",g_Index,errSyntax,(*itpCT));
		return false;
		}

	if (abs(iFrom+iStep-iTo)>abs(iFrom-iTo))
		{
		osErrReport << "<*Error*> The index doesn't converge with it step .\n";
		SYMERRORTOK("The index series diverges and is infinite.",errSyntax,*--itpCT);
		return false;
		}

	return true;
}




#ifndef NDEBUG

bool CIndexForTo::next()
{
	bool bResult;
	m_iCurrent += m_iStep;
	bResult = (m_bNeg?(m_iCurrent>=m_iTo):(m_iCurrent<=m_iTo));
	return bResult;	 
}

bool CIndexForTo::previous()
{
	bool bResult;
	m_iCurrent -= m_iStep; 
	bResult = (m_bNeg?(m_iCurrent<=m_iFrom):(m_iCurrent>=m_iFrom));
	return bResult;
}

long CIndexForTo::getValue() const
{
 return m_iCurrent;
}


///////////////////////////////////////////////////////////
// Function name	: CIndexForTo::unitTests
// Description	    : 
// Return type		: bool 
///////////////////////////////////////////////////////////
bool CIndexForTo::unitTests()
{

	bool bResults = true;
    CTestHoldTokeniser cht;
	
	//test 1 - should pass
    vector<CToken*>& rvecTok = cht.getRefVectorOfTokenPointers(1,"#index n=1:10","Test");
	cht.assignVariables(rvecTok);
//	for (vector< CToken* >::iterator it = rvecTok.begin();it!=rvecTok.end();it++)
//		cout << (**it) <<"\n";
//	cout <<endl;
	bResults &= CIndexForTo::check(1,rvecTok.size(),rvecTok,cerr);
	
	//test 2 - should fail
	rvecTok = cht.getRefVectorOfTokenPointers(1,"#index n=10:1","Test");
	cht.assignVariables(rvecTok);
	bResults &= !CIndexForTo::check(1,rvecTok.size(),rvecTok,cerr);

	//test 3 - should pass
	rvecTok = cht.getRefVectorOfTokenPointers(1,"#index n=10:1 step-2","Test");
	cht.assignVariables(rvecTok);
	bResults &= CIndexForTo::check(1,rvecTok.size(),rvecTok,cerr);

	//test 4 - should fail
	rvecTok = cht.getRefVectorOfTokenPointers(1,"#index n=10:1 step2","Test");
	cht.assignVariables(rvecTok);
	bResults &= !CIndexForTo::check(1,rvecTok.size(),rvecTok,cerr);

	//test 5 - should pass as reduce number to integers
	rvecTok = cht.getRefVectorOfTokenPointers(1,"#index n= 1   : 6.7 step 2","Test");
	cht.assignVariables(rvecTok);
	bResults &= CIndexForTo::check(1,rvecTok.size(),rvecTok,cerr);

	//test 6 - should fail
	rvecTok = cht.getRefVectorOfTokenPointers(1,"#index n=-5:-10 step 1","Test");
	cht.assignVariables(rvecTok);
	bResults &= !CIndexForTo::check(1,rvecTok.size(),rvecTok,cerr);

	//test 7 - should pass
	rvecTok = cht.getRefVectorOfTokenPointers(1,"#index n=-5:-10 step-1","Test");
	cht.assignVariables(rvecTok);
	bResults &= CIndexForTo::check(1,rvecTok.size(),rvecTok,cerr);

	//test 8 - should pass
	rvecTok = cht.getRefVectorOfTokenPointers(1,"#index n=5:-5 step-1","Test");
	cht.assignVariables(rvecTok);
	bResults &= CIndexForTo::check(1,rvecTok.size(),rvecTok,cerr);

	//test 9 - should pass
	rvecTok = cht.getRefVectorOfTokenPointers(1,"#index n=5:50 step 15","Test");
	cht.assignVariables(rvecTok);
	bResults &= CIndexForTo::check(1,rvecTok.size(),rvecTok,cerr);

	//test 10 - should pass
	rvecTok = cht.getRefVectorOfTokenPointers(1,"#index n=0:9 step 2","Test");
	cht.assignVariables(rvecTok);
	bResults &= CIndexForTo::check(1,rvecTok.size(),rvecTok,cerr);
	CIndexForTo i1(1,rvecTok.size(),rvecTok,cerr);
	bResults &= ((i1.last())&&(i1.getValue()==8)); // 
//	ATLTRACE("i1.getValue() = %d\n",i1.getValue());
	bResults &= ((i1.first())&&(i1.getValue()==0));
//	ATLTRACE("i1.getValue() = %d\n",i1.getValue());

	//test 11 - should pass
	rvecTok = cht.getRefVectorOfTokenPointers(1,"#index n=5:-6 step -2","Test");
	cht.assignVariables(rvecTok);
	bResults &= CIndexForTo::check(1,rvecTok.size(),rvecTok,cerr);
	CIndexForTo i2(1,rvecTok.size(),rvecTok,cerr);
	bResults &= ((i2.last())&&(i2.getValue()==-5)); // 
	ATLTRACE("i2.getValue() = %d\n",i2.getValue());
	bResults &= ((i2.first())&&(i2.getValue()==5));
	ATLTRACE("i2.getValue() = %d\n",i2.getValue());

	//test 12 - should pass
	rvecTok = cht.getRefVectorOfTokenPointers(1,"#index n=6+4-3:1+4-4 step-1","Test");
	cht.assignVariables(rvecTok);
	bResults &= CIndexForTo::check(1,rvecTok.size(),rvecTok,cerr);

	//test 13 - should fail
	rvecTok = cht.getRefVectorOfTokenPointers(1,"#index n=6+4-3:1+4-4","Test");
	cht.assignVariables(rvecTok);
	bResults &= !CIndexForTo::check(1,rvecTok.size(),rvecTok,cerr);

	//test 14 - should fail
	rvecTok = cht.getRefVectorOfTokenPointers(1,"#index n=6+4-3:1+4*4 step-1","Test");
	cht.assignVariables(rvecTok);
	bResults &= !CIndexForTo::check(1,rvecTok.size(),rvecTok,cerr);

	return bResults;

}

#endif