// EqSwitch.cpp: implementation of the CEqSwitch class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EqSwitch.h"
#include "Symlix\ErrorFactory.h"
#include <string.h>
#include "ArrayFactory.h"
#include "EquationFactory.h"

#ifndef NDEBUG
#include <iostream>
#include <algorithm>
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEqSwitch::CEqSwitch():CEquation()
{

}

CEqSwitch::CEqSwitch( const CEqSwitch& CE ):CEquation()
{
	CEqSwitch::copy( CE );
	
}

CEqSwitch::CEqSwitch(long iLeft,long iRight,vector<CToken*>& vExpLine, ostream& osErrReport):CEquation()
{

	if (IsWellFormedSwitchEquation(iLeft,iRight,vExpLine,osErrReport)) // note any error in format should be caught here
		{
			
		bool bResult = true;
		long iPoint;
		long iEndOfLine;
		long iRightNC;
		long iT;
		vector< CToken* > vToks;

		// find next line
		iPoint = findStartNextLine(iLeft,vExpLine);
		iEndOfLine = findStartNextLine(iPoint,vExpLine);


		// get all the cases 
		while((iPoint<vExpLine.size())&&(vExpLine[iPoint]->getString().compare(g_Case)==0))
			{
			 iRightNC = CNavTokens::getPosRightWithoutComments(iPoint,iEndOfLine,vExpLine);

			 vToks.clear();
			 for (iT=iPoint+1;iT<iRightNC;iT++) // +1 get past 'case keyword
				vToks.push_back(vExpLine[iT]);

			 ASSERT2(vToks.size()>2);

			 m_vpctCondition.push_back(vToks);

			 iPoint=iEndOfLine;
			 iEndOfLine = findStartNextLine(iPoint,vExpLine);
			 iRightNC = CNavTokens::getPosRightWithoutComments(iPoint,iEndOfLine,vExpLine);

			 vToks.clear();
			 for (iT=iPoint+2;iT<iRightNC;iT++) // +2 as only RHS being saved all LHS should be the same
				vToks.push_back(vExpLine[iT]);

			 ASSERT2(vToks.size()>0);

			 m_vvpctRight.push_back(vToks);

			 iPoint=iEndOfLine;
			 iEndOfLine = findStartNextLine(iPoint,vExpLine);
			}

		// should be on default line not - so step forward
		ASSERT2(vExpLine[iPoint]->getString().compare(g_Default)==0); // to keep on track
		iPoint=iEndOfLine;
		iEndOfLine = findStartNextLine(iPoint,vExpLine);
		iRightNC = CNavTokens::getPosRightWithoutComments(iPoint,iEndOfLine,vExpLine);

		m_pctLeft = vExpLine[iPoint]; // as all LHS must be equal
		m_pctAssign = vExpLine[iPoint+1];

		vToks.clear();
		for (iT=iPoint+2;iT<iRightNC;iT++) // as only RHS being saved all LHS should be the same
			vToks.push_back(vExpLine[iT]);
		m_vvpctRight.push_back(vToks);

		
		ASSERT2(m_vvpctRight.size()==m_vpctCondition.size()+1);


		// check for ArrayFunctions and adjust Token's appropriately
		vector< vector< CToken* > >::iterator ivvpcT;
		vector< CToken* >::iterator itpCT;
	
		for (ivvpcT=m_vvpctRight.begin();ivvpcT!=m_vvpctRight.end();ivvpcT++)
			{
			startCheckArrayFunc();
			for(itpCT=ivvpcT->begin();itpCT!=ivvpcT->end();itpCT++)
				{
				checkArrayFunc(*itpCT);
				}
			}



		m_eState=ceqIntiated;

		}
		else
		m_eState=ceqError; // the equation is in an error state and cannot be used


	
}

CEqSwitch::~CEqSwitch()
{

}



///////////////////////////////////////////////////////////
// Function name	: CEqSwitch::IsWellFormedSwitchEquation
// Description	    : static method to determine if line can make a switch
//                    equation
// Return type		: bool 
// Argument         : long iLeft
// Argument         : long iRight
// Argument         : vector<CToken*>& vExpLine
// Argument         : ostream& osErrReport
///////////////////////////////////////////////////////////
bool CEqSwitch::IsWellFormedSwitchEquation(long iLeft,long iRight,vector<CToken*>& vExpLine, ostream& osErrReport)
{
	// the format of this type of equation should be:
	// switch -- overthing that follows that line is irrelevant
	// case <expression>
	//      <equation>
	// ........... both lines above repeated until
	// default -- this term *must* be used once and only once
	//      <equation>

	vector< CToken* > vpctLHS;

	if ((iRight==iLeft)||(iRight==0))
			{
			ASSERT2(false); // this should never have got this far
			osErrReport << "<Error*> Switch equation cannot be read and is badly formed.\n";
			SYMERRORLITE("Switch equation cannot be read or is badly formed",errInternal);
			return false;
			}

	if (iLeft!=0) // I think it always should be so adding code here
			{
			ASSERT2(false);
			osErrReport << "<Warning*> Switch equation does not appear to be left most in this expression , see line "<<vExpLine[iLeft]->getLine()<<".\n";
			SYMERRORTOK("First should be the switch equation",errSyntax,vExpLine[iLeft]);
			return false;
			}

	if (iLeft>=vExpLine.size())
			{
			ASSERT2(false); // this should never have got this far
			osErrReport << "<Error*> Switch equation on line "<<vExpLine[iLeft]->getLine() <<" cannot be read and is badly formed.\n";
			SYMERRORTOK("Equation cannot be read or is badly formed",errSyntax,vExpLine[iLeft]);
			return false;
			}

	if ((iRight-iLeft)<5) // then this just is not going to work
			{
			osErrReport << "<Error*> Switch equation on line "<<vExpLine[iLeft]->getLine() <<" cannot be read and is badly formed.\n";
			SYMERRORTOK("Equation cannot be read or is badly formed",errSyntax,vExpLine[iLeft]);
			return false;
			}
	
	if (vExpLine[iLeft]->getString().compare(g_Switch)!=0)
			{
			osErrReport << "<Error*> Switch equation on line "<<vExpLine[iLeft]->getLine() <<" should start with '"<<g_Switch<<"'.\n";
			string sErr = "Equation cannot be read or is badly formed - hint start with '";
			sErr.append(g_Switch);
			sErr.append("'");
			SYMERRORTOK(sErr.c_str(),errSyntax,vExpLine[iLeft]);
			return false;
			}

	bool bResult = true;
	long iPoint;
	long iEndOfLine;

	// find next line
	iPoint = findStartNextLine(iLeft,vExpLine);

	// get all the cases 
	while((iPoint<vExpLine.size())&&(vExpLine[iPoint]->getString().compare(g_Case)==0))
	{
	 iEndOfLine = findStartNextLine(iPoint,vExpLine);
	 if (iEndOfLine!=vExpLine.size())
			{
//			iEndOfLine--;
			iPoint++;
			if (iPoint==iEndOfLine)
					{
					osErrReport << "<Error*> Switch equation is missing a condition after a 'case' statement, see line "<<vExpLine[iPoint-1]->getLine()<<".\n"; 
					SYMERRORTOK("Switch equation is missing a condition after a 'case' statement",errSyntax,vExpLine[iPoint-1]);
					return false;
					}
			if (!CEquation::IsWellFormedExpression(iPoint,iEndOfLine,vExpLine,osErrReport,true))
					{
					osErrReport << "<Error*> Switch equation 'case' statement is not well formed on line "<<vExpLine[iPoint]->getLine()<<".\n";
					SYMERRORTOK("Switch equation 'case' statement is not well formed",errSyntax,vExpLine[iPoint]);
					return false;
					}

			iPoint = iEndOfLine;
			iEndOfLine = findStartNextLine(iPoint,vExpLine);
			if (!CEquation::IsWellFormedEquation(iPoint,iEndOfLine,vExpLine,osErrReport))
					return false;
					else
					vpctLHS.push_back(vExpLine[iPoint]);

			iPoint = iEndOfLine;
			iEndOfLine = findStartNextLine(iPoint,vExpLine);

			}
			else // (itpctNext!=vExpLine.end())
			{
			osErrReport << "<Error*> Switch equation starting on line "<<vExpLine[iLeft]->getLine() <<" problem after case statment.\n";
			SYMERRORTOK("Switch equation 'case' statement is not well formed",errSyntax,vExpLine[iPoint]);
			return false;
			}
	}

	if (iPoint>=vExpLine.size())
		{
			osErrReport << "<Error*> Switch equation needs a default statement on line  "<<vExpLine[vExpLine.size()-1]->getLine() <<".\n";
			ASSERT2(iPoint==vExpLine.size());// if not then > which should not happen
			SYMERRORTOK("Switch equation needs a default statement",errSyntax,vExpLine[vExpLine.size()-1]);
			return false;
		}

	if (vExpLine[iPoint]->getString().compare(g_Default)!=0)
		{
			osErrReport << "<Error*> Switch equation needs a default statement on line  "<<vExpLine[iPoint]->getLine() <<".\n";
			SYMERRORTOK("Switch equation needs a default statement",errSyntax,vExpLine[vExpLine.size()-1]);
			return false;
		}

	iPoint = iEndOfLine;
	iEndOfLine = findStartNextLine(iPoint,vExpLine);

	if (iPoint>=vExpLine.size())
		{
			osErrReport << "<Error*> Switch equation needs a default statement on line  "<<vExpLine[vExpLine.size()-1]->getLine() <<".\n";
			ASSERT2(iPoint==vExpLine.size());// if not then > which should not happen
			return false;
		}

	if (!CEquation::IsWellFormedEquation(iPoint,iEndOfLine,vExpLine,osErrReport))
		return false;
		else
		vpctLHS.push_back(vExpLine[iPoint]);


	if (vpctLHS.size()==1)
				return true; // must just have default - pointlewss, but possible

	for (vector< CToken* >::const_iterator cit=vpctLHS.begin();cit!=vpctLHS.end();cit++)
			bResult&= (vpctLHS[0]->getRootToken()==(*cit)->getRootToken());

	if (!bResult)
		{
		osErrReport << "<Error*> For Switch equation all LHS statements must be of the same, see line "<<vExpLine[iLeft]->getLine()<<".\n";
		SYMERRORTOK("For Switch equation all LHS statements must be of the same",errSyntax,vExpLine[iLeft]);
		}

	if ((!vpctLHS[0]->IsOfTypeVariable())&&(!vpctLHS[0]->IsOfType(ctDerivative)))
		{
		osErrReport << "<Error*> The LHS of the equations in the switch statement must be a variable or derivative, see line "<<vExpLine[iLeft]->getLine()<<".\n";
		SYMERRORTOK("The LHS of the equations in the switch statement must be a variable or derivative",errSyntax,vpctLHS[0]);
		return false;
		}

	return bResult;
}


///////////////////////////////////////////////////////////
// Function name	: CEqSwitch::findStartNextLine
// Description	    : Helper function to find point that a new line starts at
//                    if over runs then returns vExpLine.size()
// Return type		: long 
// Argument         : long iStart
// Argument         : vector<CToken*>& vExpLine
///////////////////////////////////////////////////////////
long CEqSwitch::findStartNextLine(long iStart, vector<CToken*>& vExpLine)
{
	long iResult=iStart;
	const CToken& ct = /*dynamic_cast<CToken*>*/(*vExpLine[iStart]);

	while ((iResult!=vExpLine.size())&&(vExpLine[iResult]->sameLine(ct)))
		iResult++;

	return iResult;
} 



///////////////////////////////////////////////////////////
// Function name	: CEqSwitch::setupExpression
// Description	    : 
// Return type		: bool 
// Argument         : list<CEquation*>* pvecpEquations
// Argument         : CVarClassFactory* pvcf
// Argument         : ostream& osErrReport/*=cerr*/
///////////////////////////////////////////////////////////
bool CEqSwitch::setupExpression(list<CEquation*>* pvecpEquations, CVarClassFactory* pvcf, ostream& osErrReport/*=cerr*/)
{

	bool bResult=true;
	CVarRoot* pvr;

	if (!pvcf) // should never happen, but need to handle as its being used
		{
		SYMERRORLITE("Undefined information in the software",errInternal);
		return false;
		}

	// need to setup expressions
	vector< vector< CToken* > >::iterator itvvR;
	m_vpcvrCondition.clear();

#ifndef NDEBUG
#ifdef EXTRADEBUG
	cout << (*this) <<endl;
	cout << "LHS "<< (*m_pctLeft)<<endl;
	cout << "LHS root "<<(*(m_pctLeft->getRootTokenPt()))<<endl;
#endif
#endif

	m_iIndex = m_pctLeft->getRootTokenPt()->getIndex();

	for (itvvR=m_vpctCondition.begin();itvvR!=m_vpctCondition.end();itvvR++)
		{
		pvr = createExpression(0,itvvR->size(),*itvvR,osErrReport,pvecpEquations);
		ASSERT2(pvr);
		bResult&=(pvr!=NULL); // should always be the case - just making sure
		if (pvr)
			m_vpcvrCondition.push_back(pvr);
		}


	m_vpcvrRight.clear();

	for (itvvR=m_vvpctRight.begin();itvvR!=m_vvpctRight.end();itvvR++)
		{
		pvr = createExpression(0,itvvR->size(),*itvvR,osErrReport,pvecpEquations);
		ASSERT2(pvr);
		bResult&=(pvr!=NULL); // should always be the case - just making sure
		if (pvr)
			m_vpcvrRight.push_back(pvr);
		}

	ASSERT2(m_vpcvrCondition.size()==m_vpcvrRight.size()-1); // should always be true

	// must create a CVarVariable to place at the root defintion
	// note it will be updated prior to being used due to order
	// of variable defintions. ( ie a new value will be used before
	// it can used ).
	m_pvrRight = pvcf->createVariable(m_iIndex);
	m_pctLeft->getRootTokenPt()->setpVarRoot(m_pvrRight);

	if (bResult)
		m_eState = ceqReadyToSolve;
		else
		{
		m_eState = ceqError;
		osErrReport << "<Internal Error*> Unable to fully compile this equation :\n"<<(*this)<<endl;
		SYMERRORLITE("Unable to fully compile an switch equation",errInternal);
		}

	return bResult;

}


///////////////////////////////////////////////////////////
// Function name	: CEqSwitch::setStrongType
// Description	    : 
// Return type		: void 
// Argument         : const vector< varStrongType >& vecst
///////////////////////////////////////////////////////////
void CEqSwitch::setStrongType(const vector< varStrongType >& vecst)
{

//	vector< CVarRoot* >::iterator itV;

	if (m_eState!=ceqReadyToSolve)
		{
		ASSERT2(m_eState==ceqReadyToSolve);
		return;
		}

	ASSERT2(m_iIndex!=NOT_DEFINED);
	ASSERT2(m_iIndex<vecst.size());

/*	for(itV=m_vpcvrRight.begin();itV!=m_vpcvrRight.end();itV++)
			{
			ASSERT2(*itV);
			(*itV)->setType(vecst[m_iIndex]);
			}*/
	m_pvrRight->setType( vecst[m_iIndex] );

	m_vResult.copy(vecst[m_iIndex]); // set up strong type info

}

///////////////////////////////////////////////////////////
// Function name	: CEqSwitch::updateValue
// Description	    : Evaluate RHS and set LHS to that value
//                    and return the new LHS value.
// Return type		: variable 
// Argument         : vector< variable >* pvecVar
///////////////////////////////////////////////////////////
variable CEqSwitch::updateValue(vector< variable >* pvecVar)
{
	

	if (m_eState!=ceqReadyToSolve)
			return CANNOT_EVALUATE;

#ifndef NDEBUG

	long iIndex; // may make class variable soon
	iIndex = m_pctLeft->getRootTokenPt()->getIndex();
	ASSERT2(m_iIndex==iIndex);

	ASSERT2(iIndex!=NOT_DEFINED);
	ASSERT2(iIndex<pvecVar->size());

#endif

	(*pvecVar)[m_iIndex] = m_vResult = getValue(pvecVar);

	return (*pvecVar)[m_iIndex];
}


//#define LOGICDEBUG
///////////////////////////////////////////////////////////
// Function name	: CEqSwitch::getValue
// Description	    : Protected function to place complex 
//                    code for generating values in one place.
// Return type		: variable 
// Argument         : vector<variable>* pvecV
///////////////////////////////////////////////////////////
variable CEqSwitch::getValue(vector<variable>* pvecV)
{
	variable vResult;
	vector< CVarRoot* >::iterator itV;
	long iCount=0;
	bool bNotFound = true;

	itV = m_vpcvrCondition.begin();

	while((bNotFound)&&(itV!=m_vpcvrCondition.end()))
	{
	 if ((*itV)->getValue(*pvecV)==1) // ie is True
			bNotFound=false;
			else
			{
			itV++;
			iCount++;
			}
	}

#ifndef LOGICDEBUG
	if (itV==m_vpcvrCondition.end())
			{	
			itV = m_vpcvrRight.end();
			itV--;
			vResult= (*itV)->getValue(*pvecV);
			}
			else
			vResult = m_vpcvrRight[iCount]->getValue(*pvecV);
#else
	vector< CToken* >::const_iterator cit;
//	cerr << "x1 "<<(*pvecV)[1]<<" ";
	if (itV==m_vpcvrCondition.end())
			{	
			itV = m_vpcvrRight.end();
			itV--;
			vResult= (*itV)->getValue(*pvecV);
			cerr << "Default\n";
			}
			else
			{
			vResult = m_vpcvrRight[iCount]->getValue(*pvecV);
			for(cit=m_vpctCondition[iCount].begin();cit!=m_vpctCondition[iCount].end();cit++)
				cerr << (*cit)->getString().c_str();
			cerr<<endl;
			}
#endif

	return vResult;
}	


///////////////////////////////////////////////////////////
// Function name	: CEqSwitch::evaluate
// Description	    : Overloaded function that evaluates the RHS
//                    but does not change the LHS value.
// Return type		: variable 
// Argument         : vector<variable>* pvecV
///////////////////////////////////////////////////////////
variable CEqSwitch::evaluate(vector<variable>* pvecV)
{

	ASSERT2(canEvaluate());
	ASSERT2(pvecV!=NULL);

	if ((!pvecV)&&(!canEvaluate()))
		return CANNOT_EVALUATE; // not great - but don't want to fail here if not debug
	

	if (m_eState!=ceqReadyToSolve)
			return CANNOT_EVALUATE;


	return getValue(pvecV);

}


///////////////////////////////////////////////////////////
// Function name	: CEqSwitch::sendtostream
// Description	    : So overloaded operator calls correct function
// Return type		: void 
// Argument         : ostream& os
///////////////////////////////////////////////////////////
void CEqSwitch::sendtostream(ostream& os) const
{

	vector< CToken* >::const_iterator iter;

	if ((m_eState!=ceqIntiated)&&(m_eState!=ceqReadyToSolve))
			{
			os << "<Warning> Equation no initialised.";
			return;
			}


	ASSERT2((m_pctLeft!=NULL)&&(m_pctAssign!=NULL)); // catch unexpected bug - yes I know :-)

	os <<"Switch Equation\n";

	vector< vector< CToken* > >::const_iterator citC;
	vector< vector< CToken* > >::const_iterator citR;

	citC = m_vpctCondition.begin();
	citR = m_vvpctRight.begin();

	while(citC!=m_vpctCondition.end())
	{
		ASSERT2(citR!=m_vvpctRight.end());
		os << "case ";
		for(iter=citC->begin();iter!=citC->end();iter++)
			os << (*iter)->getString().c_str();
		os <<endl;
		os << "\t"<< m_pctLeft->getString().c_str() << m_pctAssign->getString().c_str();
		for(iter=citR->begin();iter!=citR->end();iter++)
			os << (*iter)->getString().c_str();
		os <<endl;
		citC++;
		citR++;
	}
	ASSERT2(citR!=m_vvpctRight.end());
	os <<"default \n";
	os << "\t"<<m_pctLeft->getString().c_str() << m_pctAssign->getString().c_str();
	for(iter=citR->begin();iter!=citR->end();iter++)
		os << (*iter)->getString().c_str();
	
}

#ifndef NDEBUG

///////////////////////////////////////////////////////////
// Function name	: CEqSwitch::sentToAtlTrace
// Description	    : 
// Return type		: void 
///////////////////////////////////////////////////////////
void CEqSwitch::sentToAtlTrace() const
{

	vector< CToken* >::const_iterator iter;

	if ((m_eState!=ceqIntiated)&&(m_eState!=ceqReadyToSolve))
			{
			ATLTRACE("<Warning> Equation no initialised.\n");
			return;
			}


	ASSERT2((m_pctLeft!=NULL)&&(m_pctAssign!=NULL)); // catch unexpected bug - yes I know :-)

	ATLTRACE("Switch Equation\n");

	vector< vector< CToken* > >::const_iterator citC;
	vector< vector< CToken* > >::const_iterator citR;

	citC = m_vpctCondition.begin();
	citR = m_vvpctRight.begin();

	while(citC!=m_vpctCondition.end())
	{
		ASSERT2(citR!=m_vvpctRight.end());
		ATLTRACE("case ");
		for(iter=citC->begin();iter!=citC->end();iter++)
			ATLTRACE("%s",(*iter)->getString().c_str());
		ATLTRACE("\n");
		ATLTRACE("\t%s%s",m_pctLeft->getString().c_str(),m_pctAssign->getString().c_str());
		for(iter=citR->begin();iter!=citR->end();iter++)
			ATLTRACE("%s",(*iter)->getString().c_str());
		ATLTRACE("\n");
		citC++;
		citR++;
	}
	ASSERT2(citR!=m_vvpctRight.end());
	ATLTRACE("default \n");
	ATLTRACE("\t%s%s",m_pctLeft->getString().c_str(),m_pctAssign->getString().c_str());
	for(iter=citR->begin();iter!=citR->end();iter++)
		ATLTRACE("%s",(*iter)->getString().c_str());

	ATLTRACE("\n");

}

#endif

///////////////////////////////////////////////////////////
// Function name	: CEqSwitch::checkAllRHSDefined
// Description	    : 
// Return type		: bool 
// Argument         : const set<CToken* > setDef
// Argument         : bool bReport/*=false*/
// Argument         : ostream& oserr/*=cerr*/
///////////////////////////////////////////////////////////
bool CEqSwitch::checkAllRHSDefined(const set<CToken* > setDef, bool bReport/*=false*/, ostream& oserr/*=cerr*/ ) const
{
	vector<CToken* >::const_iterator citv;
	vector< vector< CToken* > >::const_iterator citR;
	set<CToken* >::const_iterator cits = setDef.end();
	bool bResult = true;
	string sErr = "The following variables were undefined at the simulation start :";


	for (citR=m_vvpctRight.begin();citR!=m_vvpctRight.end();citR++)
		for (citv=citR->begin();citv!=citR->end();citv++)
			if ((*citv)->IsOfTypeVariable())
					//bResult &= (cits!=setDef.find((*citv)->getRootTokenPt()));
					if (cits==setDef.find((*citv)->getRootTokenPt()))
						{
						if ((bReport)&&(!bResult))
							{
							sErr.append(", ");
							oserr << ", ";
							}
						bResult=false;
						if (bReport)
							{
							sErr.append((*citv)->getString().c_str());
							oserr << (*citv)->getString().c_str();
							}
						}

	if ((bReport)&&(!bResult))
			{
			SYMERRORLITE(sErr.c_str(),errSyntax);
			oserr << " undefined at simulation start.";
			}
	return bResult;

}


///////////////////////////////////////////////////////////
// Function name	: CEqSwitch::createImpliedArray
// Description	    : 
// Return type		: bool 
// Argument         : CArrayFactory *pAF
///////////////////////////////////////////////////////////
bool CEqSwitch::createImpliedArray(CArrayFactory *pAF)
{
	bool bResult = false;
	vector< vector< CToken* > >::iterator citvv;
	
	if (!pAF)
			return false;

	// check for each RHS

/*
	Notes: Since this created LHS array carry on until RHS forces an array creation.
	Latter postCreation check makes sure that only one form of RHS array mix is used
	(an error which will continue past this point ).

*/
	citvv = m_vvpctRight.begin();

	while((citvv!=m_vvpctRight.end())&&(!m_bHasArrays))
	{
		if (pAF->createImpliedArray(*citvv,m_pctLeft,m_bHasArrays))
				bResult = true;
		citvv++;
	}

/*	for (citvv=m_vvpctRight.begin();citvv!=m_vvpctRight.end();citvv++)
		{
		if (pAF->createImpliedArray(*citvv,m_pctLeft))
				m_bHasArrays = true;
		}
*/
	return bResult;
}


///////////////////////////////////////////////////////////
// Function name	: CEqSwitch::checkImpliedArrays
// Description	    : Will return true if any arrays on the
//                    RHS sides ( does not mean they are legal )
// Return type		: bool 
// Argument         : CArrayFactory *pAF
///////////////////////////////////////////////////////////
bool CEqSwitch::checkImpliedArrays(CArrayFactory *pAF)
{
	bool bResult;
	vector< vector< CToken* > >::iterator it;

	ASSERT2(m_vvpctRight.size()!=0);
	if ((!pAF)&&(m_vvpctRight.size()==0))
		return false;

	it=m_vvpctRight.begin();
	bResult = pAF->anyArraysHere(*it);


	for (;it!=m_vvpctRight.end();it++)
		{		
		bResult |= pAF->anyArraysHere(*it); // so picks up any positives
		}

	return bResult;

}

///////////////////////////////////////////////////////////
// Function name	: CEqSwitch::postCreationCheck
// Description	    : Check all RHS are OK if they involve arrays
// Return type		: bool 
// Argument         : CArrayFactory* pAF
///////////////////////////////////////////////////////////
bool CEqSwitch::postCreationCheck(CArrayFactory* pAF)
{

	#ifndef NDEBUG
	ostream_iterator<string> out(cout,", "); // see p53 STL book
	#endif
	// I suspect these checks could be carried out a lot more efficiently

	vector< vector< CToken* > >::iterator it;
	bool bResult = true;

	if (!pAF)
		return false;

	it = m_vvpctRight.begin();

	if (it==m_vvpctRight.end()) // since this should never be called when there are no RHS sides
			{
			SYMERRORLITE("A lookup equation produced an unexpected error, please report.",errInternal);
			return false; // check fails due to internal error
			}

	SetStringAR& rSetFirst = pAF->setOfArraysHere(*it);
	
	while((++it!=m_vvpctRight.end())&&(rSetFirst.size()==0)) // so step forward until first array response
		{
		rSetFirst = pAF->setOfArraysHere(*it);
		}

	#ifndef NDEBUG
	cout << "rSetFirst {";
	std::copy(rSetFirst.begin(),rSetFirst.end(),out);
	cout << "}" <<endl;
	#endif

	for (;(bResult)&&(it!=m_vvpctRight.end());it++)
		{
		vector<string> vecMismatch;
		vector<string>::iterator itMis;
		SetStringAR& rSetNext = pAF->setOfArraysHere(*it);
		if (rSetNext.size()>rSetFirst.size())
				vecMismatch.resize(rSetNext.size(),"");
				else
				vecMismatch.resize(rSetFirst.size(),"");

		itMis = set_symmetric_difference(rSetFirst.begin(),rSetFirst.end(),rSetNext.begin(),rSetNext.end(),vecMismatch.begin());
		vecMismatch.erase(itMis,vecMismatch.end());
		if (vecMismatch.size()!=0)
			{
			#ifndef NDEBUG
			cout << "rSetNext {";
			std::copy(rSetNext.begin(),rSetNext.end(),out);
			cout << "}\n";
			cout << "vecMismatch {";
			std::copy(vecMismatch.begin(),vecMismatch.end(),out);
			cout << "}"<<endl;
			#endif
			cerr <<"<Error*> Mismatch between arrays on RHS of switch equation.\n";
			SYMERRORTOK("For a switch equation each of the RHS must include the same arrays.",errSyntax,((*(it->begin()))));
			bResult=false;
			}

		}

	return bResult;

}


///////////////////////////////////////////////////////////
// Function name	: CEqSwitch::setArrayIndex
// Description	    : 
// Return type		: bool 
// Argument         : long iIndex
// Argument         : list<CToken>& ltToks
// Argument         : SetPtCTokenStringSearch& rsetPtToksUnique
///////////////////////////////////////////////////////////
bool CEqSwitch::setArrayIndex(long iIndex, list<CToken>& ltToks, SetPtCTokenStringSearch& rsetPtToksUnique)
{

	list<CToken>::iterator it;
	SetPtCTokenStringSearch::iterator itSet;
	CToken tLHS(*m_pctLeft);
	vector< CToken* >::iterator itTok;
	vector< vector < CToken* > >::iterator itRHS;

	if (tLHS.IsOfType(ctDerivative))
		tLHS.setString(tLHS.getString().withDerivBracketedIndex(iIndex));
		else
		tLHS.setString(tLHS.getString().withBracketedIndex(iIndex));
	tLHS.setAsPartArray();
	ltToks.push_back(tLHS);
	m_pctLeft = &(ltToks.back());
	itSet = rsetPtToksUnique.find(m_pctLeft);
	if (itSet==rsetPtToksUnique.end()) // need to add any new unique tokens here
		{
		rsetPtToksUnique.insert(m_pctLeft);
		m_pctLeft->ClearParent();
		}	
		else
		m_pctLeft->AssignParent(*itSet); // point at parent

	ASSERT2((*m_pctLeft)==tLHS); // check

	// now assign to equivalent variable if its a derivative and not already defined.
	if (m_pctLeft->IsOfType(ctDerivative))
			{
			CToken tImplied;
			tImplied.setString( m_pctLeft->getStringWithoutDeriv() );
			itSet = rsetPtToksUnique.find(&tImplied);
			if (itSet==rsetPtToksUnique.end()) // then it needs to be added
				{
				tImplied.setType(ctVariable);
				tImplied.setAsPartArray();
				ltToks.push_back(tImplied);
				rsetPtToksUnique.insert(&(ltToks.back()));
				}
			}


// need to check each token will have been assigned as an array where necessary by now
	CArrayFactory* pa = CArrayFactory::instance();

	ASSERT2(pa);
	if (!pa)
		{
		SYMERRORLITE("Out of memory",errSystem);	
		return false;
		}

	for(itRHS=m_vvpctRight.begin();itRHS!=m_vvpctRight.end();itRHS++)
		for(itTok=itRHS->begin();itTok!=itRHS->end();itTok++)
			{
			 ATLTRACE("Array type %d name %s\n",(*itTok)->getType(),(*itTok)->getStringRef().c_str());

//			 if ((*itTok)->getRootTokenPt()->getArrayType()==atArray) // needs to be getRootTokenPt as only first RHS with Arrays will have array links
			 if (((*itTok)->IsOfTypeVariable())&&(pa->anyArraysHere(**itTok,true,true))) // find array if of type variable
					{
					CToken t2(**itTok);
					t2.setString(t2.getString().withBracketedIndex(iIndex));
					t2.setAsPartArray();
					ltToks.push_back(t2);
					(*itTok) = &(ltToks.back());
					ASSERT2((**itTok)==t2);
					itSet = rsetPtToksUnique.find(*itTok);
					if (itSet==rsetPtToksUnique.end()) // need to add any new unique tokens here
						{
						rsetPtToksUnique.insert(*itTok);
						(*itTok)->ClearParent();
						}	
						else
						(*itTok)->AssignParent(*itSet); // point at parent
		
					}

			}

	return true;
}



///////////////////////////////////////////////////////////
// Function name	: CEqSwitch::expandArrayEquations
// Description	    : 
// Return type		: long 
// Argument         : list<CToken>& ltToks
// Argument         : vector<CEquation*>& rvecNewEqs
// Argument         : SetPtCTokenStringSearch& rsetPtToksUnique
///////////////////////////////////////////////////////////
long CEqSwitch::expandArrayEquations( list<CToken>& ltToks, vector<CEquation*>& rvecNewEqs, SetPtCTokenStringSearch& rsetPtToksUnique ) const
{
//ool bCarryOn;
 CArray* pa = m_pctLeft->getArray();
 CEquationFactory* peqf = CEquationFactory::instance();

 if ((!pa)||(!peqf))
	return -1;

 if (!pa->first())
	return -1;

 do
 {
	CEquation* pe = newtrack CEqSwitch(*this);
	if (!pe)
		{
		SYMERRORLITE("Low memory",errSystem);
		return -1;
		}
	
	peqf->lookAfterLifeCycle(pe); // life cycle managed by factory
	rvecNewEqs.push_back(pe); 
	pe->setArrayIndex(pa->getIndex(),ltToks,rsetPtToksUnique);

 }
 while(pa->next());

 return rvecNewEqs.size();
}


///////////////////////////////////////////////////////////
// Function name	: CEqSwitch::copy
// Description	    : 
// Return type		: void 
// Argument         : const CEqSwitch& CE
///////////////////////////////////////////////////////////
void CEqSwitch::copy(const CEqSwitch& CE)
{
	const CEquation* eq = &CE;
	CEquation::copy(*eq);

	m_vpctCondition = CE.m_vpctCondition;
	m_vpcvrCondition = CE.m_vpcvrCondition;
	m_vpcvrRight = CE.m_vpcvrRight;
	m_vvpctRight = CE.m_vvpctRight;

}

///////////////////////////////////////////////////////////
// Function name	: CEqSwitch::expandArrayFunctions
// Description	    : 
// Return type		: bool 
// Argument         : list<CToken>& rLToks
// Argument         : SetPtCTokenStringSearch& rSetUnique
///////////////////////////////////////////////////////////
bool CEqSwitch::expandArrayFunctions(list<CToken>& rLToks, SetPtCTokenStringSearch& rSetUnique)
{
	bool bResult = true;
	vector< vector< CToken* > >::iterator itV;

	if (!m_bHasArrayFunc) // already know there are no array functions so don't need to check
			return true;

	for (itV=m_vvpctRight.begin();itV!=m_vvpctRight.end();itV++)
		bResult &= expandArrayFunctionsForRHS(rLToks,(*itV),rSetUnique);
	
	return bResult;
}