// EqIterative.cpp: implementation of the CEqIterative class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EqIterative.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#ifdef EQSTOPOPTION


CEqIterative::CEqIterative(long iLeft,long iRight,vector<CToken*>& vExpLine, ostream& osErrReport/*=cerr*/):CEquation(),m_pCounter(NULL),m_xtTime(NOT_DEFINED)
{
	vector< CToken* >::const_iterator itpCT;
	vector< CToken* >::const_iterator itpCTRight;
	itpCTRight = getRightWithoutComments(iLeft,iRight,vExpLine);
	ASSERT2(IsWellFormedIterativeEquation(iLeft,iRight,vExpLine,osErrReport));
	m_eState = ceqError; // unless reset

	if (IsWellFormedIterativeEquation(iLeft,iRight,vExpLine,osErrReport))
		{
		m_eState=ceqUninitated;
	    m_pctLeft = vExpLine[iLeft]; // this has a note of the variable

		// which composition of event is it ?
		// 1. iteration N = 1 to 100 step 2
		// 2. iteration N {1,2,5,10,30}
	
		// check item iLeft + 1 ( which is now guarenteed to exist by the check )
		
		if (vExpLine[iLeft+1]->getString().compare(g_Eq)==0)
				m_bEqualFormat=true;
			else
				m_bEqualFormat=false;

		m_pctLeft = vExpLine[iLeft];

		if (m_bEqualFormat)
				{
				variable vFrom, vTo, vStep;
				itpCT = &vExpLine[iLeft+2];
				vFrom = (*itpCT)->getNumber();
				itpCT++;itpCT++;
				vTo= (*itpCT)->getNumber();
				if ((++itpCT!=itpCTRight)&&(++itpCT!=itpCTRight))
					vStep =  (*itpCT)->getNumber();
					else
					if (vFrom>vTo)
							vStep=-1;
							else
							vStep=1;
				m_pCounter = newtrack CEI_FromTo(vFrom,vTo,vStep);
				}
			else
				{
				vector< variable > vecValues;
				itpCT=&vExpLine[iLeft+1];

				while ((++itpCT)!=itpCTRight)
					vecValues.push_back((*itpCT++)->getNumber());

				m_pCounter = newtrack CEI_Sequence(vecValues);
				}

		if (!m_pCounter)
				{
				m_eState = ceqError;

				}


		}



}




CEqIterative::~CEqIterative()
{
	delete m_pCounter;
}

#define CHECKNOTENDEQ( pnt1, pntEnd) {  if (pnt1==pntEnd) \
											{ SYMERRORTOK("<Error*> Equation does not have enough information",errSyntax,vExpLine[0]); \
											  return false; \
											}}


///////////////////////////////////////////////////////////
// Function name	: CEqIterative::IsWellFormedIterativeEquation
// Description	    : Check this will form a correct Iterative equation
// Return type		: bool 
// Argument         :  long iLeft
// Argument         : long iRight
// Argument         : vector<CToken*>& vExpLine
// Argument         : ostream& osErrReport/*=cerr*/
///////////////////////////////////////////////////////////
bool CEqIterative::IsWellFormedIterativeEquation( long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport/*=cerr*/ )
{

	vector< CToken* >::iterator itpCT;
	// itpCTRight is fouud this way as I'm not sure &vExp[iRight] would produce the same result in all conditions
	vector< CToken* >::const_iterator itpCTRight;

	ASSERT2(iLeft<iRight);
	if (iLeft>=iRight)
			return false;

	if (vExpLine.size()<iRight)
			{
			if (vExpLine.size()>0)
				{
				osErrReport <<"<Error*> format error with "<< g_Sync <<" Equation on line "<<vExpLine[0]->getLine()<<" ."<<endl;
				SYMERRORTOK("Change once format error",errSyntax,vExpLine[0]);
				}
				else
				{
				osErrReport <<"<Error*> format error with "<< g_Sync <<" Equation on line."<<endl;
				SYMERRORLITE("Change once format error",errSyntax);
				}
			return false;
			}

	itpCTRight = getRightWithoutComments(iLeft,iRight,vExpLine);
	itpCT = &vExpLine[iLeft];

			
	/* legal implementations 
	iteration N = 1 to 100 step 2
	iteration N = 1 to 100
	iteration N {1,2,5,10,30}
	*/

	if ((iRight-iLeft)<5) // this won't catch all cases, but is just a first test
			{
			osErrReport << "<Error*> Equation does not have enough information";
			if (vExpLine.size()>0)
				osErrReport <<" on line "<< vExpLine[0]->getLine();
			osErrReport <<".\n";
			SYMERRORTOK("Equation does not have enough information",errSyntax,vExpLine[iLeft]);
			return false;
			}

	// let the checking begin
	if ((itpCT==itpCTRight)||(!(*itpCT)->IsOfTypeVariable()))
			{
			if (itpCT!=itpCTRight)
				{
				SYMERRORTOK("Variable not found for equation",errSyntax,(*itpCT));
				}
				else
				{
				SYMERRORTOK("Variable not found for equation",errSyntax,vExpLine[iLeft]);
				}
			return false;
			}

	itpCT++;

	// Next should either be curly brackets, lookup or a number

	CHECKNOTENDEQ( itpCT, itpCTRight );

	if ((*itpCT)->getStringRef().compare(g_OpenCurlyBracket)==0)
		{
		bool bOK = true;
		bool bNumberNext = true;
		while (bOK&&(++itpCT!=itpCTRight)&&((*itpCT)->getString().compare(g_CloseCurlyBracket)!=0))
			{
			if (bNumberNext)
				{
				bOK = (*itpCT)->IsOfType(ctNumber);
				bNumberNext = false;
				}
				else
				{
				bOK = ((*itpCT)->getString().compare(g_Comma)==0);
				bNumberNext = true;
				}
			}
		CHECKNOTENDEQ( itpCT, itpCTRight );
		if (!bOK)
			if (bNumberNext)
				{
				SYMERRORTOK("A comma was expected here",errSyntax,(*itpCT));
				return false;
				}
				else
				{
				SYMERRORTOK("A number was expected here",errSyntax,(*itpCT));
				return false;
				}
		
		}
		else
		{
		variable vFrom, vTo, vStep;


		if ((*itpCT)->getString().compare(g_Eq)!=0)
			{
				SYMERRORTOK2("Was expecting ",g_Eq,errSyntax,(*itpCT));
				return false;
			}

		CHECKNOTENDEQ( ++itpCT, itpCTRight );
		if (!(*itpCT)->IsOfType(ctNumber))
			{
				SYMERRORTOK2("Was expecting a number after ",g_Eq,errSyntax,(*itpCT));
				return false;
			}
		vFrom=(*itpCT)->getNumber();

		CHECKNOTENDEQ( ++itpCT, itpCTRight );
		if ((*itpCT)->getString().compare(g_To)!=0)
			{
				SYMERRORTOK2("Was expecting ",g_To,errSyntax,(*itpCT));
				return false;
			}

		CHECKNOTENDEQ( ++itpCT, itpCTRight );
		if (!(*itpCT)->IsOfType(ctNumber))
			{
				SYMERRORTOK2("Was expecting a number after ",g_To,errSyntax,(*itpCT));
				return false;
			}
		vTo=(*itpCT)->getNumber();

		// would be fine if no further tokens to consider
		if (++itpCT==itpCTRight)
				return true; // note no convergence test needed as step is implied

		if ((*itpCT)->getString().compare(g_Step)!=0)
			{
				SYMERRORTOK2("Was expecting ",g_Step,errSyntax,(*itpCT));
				return false;
			}

		CHECKNOTENDEQ( ++itpCT, itpCTRight );
		if (!(*itpCT)->IsOfType(ctNumber))
			{
				SYMERRORTOK2("Was expecting a number after ",g_Step,errSyntax,(*itpCT));
				return false;
			}
		vStep=(*itpCT)->getNumber();

		// Now need to check this series will converge
		if (vStep==0)
					{
					SYMERRORTOK("Step is set for zero !",errModel,(*itpCT));
					return false;
					}

		if (vFrom>vTo)
			{
			if (vStep>0)
				{
				SYMERRORTOK("The From, To , Step sequence doesn't converge",errModel,(*itpCT));
				return false;
				}
			}
			else
			if (vFrom<vTo)
				{
				if (vStep<0)
					{
					SYMERRORTOK("The From, To , Step sequence doesn't converge",errModel,(*itpCT));
					return false;
					}
				}
				


		} // end if else

	return true;

}



///////////////////////////////////////////////////////////
// Function name	: CEqIterative::setupExpression
// Description	    : 
// Return type		: bool 
// Argument         : list<CEquation*>* pvecpEquations
// Argument         : CVarClassFactory* pvcf
// Argument         : ostream& osErrReport/*=cerr*/
///////////////////////////////////////////////////////////
bool CEqIterative::setupExpression(list<CEquation*>* pvecpEquations, CVarClassFactory* pvcf, ostream& osErrReport/*=cerr*/)
{
	bool bResult = true;
//	vector< CToken* >::const_iterator cit;

	if (!pvcf) // should never happen, but need to handle as its being used
		{
		SYMERRORLITE("Undefined information in the software",errInternal);
		return false;
		}

	ASSERT2(m_pctLeft);
	
	m_iIndex = m_pctLeft->getRootTokenPt()->getIndex();

	ASSERT2(m_iIndex>=0);


	// must create a CVarVariable to place at the root defintion
	// note it will be updated prior to being used due to order
	// of variable defintions. ( ie a new value will be used before
	// it can used ).
	m_pvrRight = pvcf->createVariable(m_iIndex);
	m_pctLeft->getRootTokenPt()->setpVarRoot(m_pvrRight);

	if ((m_giIndexTime!=NOT_DEFINED)&&(m_gxtTimeStart!=NOT_DEFINED))
				m_eState = ceqReadyToSolve;
				else
				{
				ASSERT2(false); // draw attention here
				SYMERRORLITE("A problem was detected setting up the iteration equation",errInternal); 
				return false;
				}

	return bResult;
}


///////////////////////////////////////////////////////////
// Function name	: CEqIterative::setStrongType
// Description	    : 
// Return type		: void 
// Argument         : const vector< varStrongType >& vecst
///////////////////////////////////////////////////////////
void CEqIterative::setStrongType(const vector< varStrongType >& vecst)
{

	if (m_eState!=ceqReadyToSolve)
		{
		ASSERT2(m_eState==ceqReadyToSolve);
		return;
		}

	ASSERT2(m_iIndex!=NOT_DEFINED);
	ASSERT2(m_iIndex<vecst.size());
	ASSERT2(m_pvrRight);

	m_pvrRight->setType( vecst[m_iIndex] );
	
	m_vResult.copy(vecst[m_iIndex]); // set up strong type info


}


///////////////////////////////////////////////////////////
// Function name	: CEqIterative::evaluate
// Description	    : 
// Return type		: variable 
// Argument         : vector<variable>* pvecV
///////////////////////////////////////////////////////////
variable CEqIterative::evaluate(vector<variable>* pvecV)
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
// Function name	: CEqIterative::updateValue
// Description	    : 
// Return type		: variable 
// Argument         : vector< variable >* pvecVar
///////////////////////////////////////////////////////////
variable CEqIterative::updateValue(vector< variable >* pvecVar)
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

	(*pvecVar)[m_iIndex] = getValue(pvecVar);

	return (*pvecVar)[m_iIndex];
}


///////////////////////////////////////////////////////////
// Function name	: CEqIterative::reset
// Description	    : reset the sequence beiung iterated through
// Return type		: void 
///////////////////////////////////////////////////////////
void CEqIterative::reset()
{

	ASSERT2(m_pCounter);

	m_xtTime = m_gxtTimeStart;

	if (m_pCounter)
		m_pCounter->reset();
		else
		m_eState = ceqError;

}


///////////////////////////////////////////////////////////
// Function name	: CEqIterative::getValue
// Description	    : 
// Return type		: variable 
// Argument         : vector<variable>* pvecV
///////////////////////////////////////////////////////////
variable CEqIterative::getValue(vector<variable>* pvecV)
{

	ASSERT2(m_eState==ceqReadyToSolve);
	// if time has moved by one then update value
	if ((*pvecV)[m_giIndexTime]-m_xtTime>1)
			{
			m_pCounter->next();
			if (m_pCounter->isLast())
				m_gStopCallFromEqs=true;
			}

	m_vResult = m_pCounter->value(); // to enforce strong types
	return m_vResult;
}


#endif // #ifdef EQSTOPOPTION



