// Equation.cpp: implementation of the CEquation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Equation.h"
#include "global.h"
#include "SubExpression.h"
#ifndef NDEBUG
#include <algorithm>
#endif
#include "Symlix\ErrorFactory.h"
#include "FuncIdentifierSingleton.h"
#include "EquationFactory.h"
#include "ArrayImplied.h"


#define COMBINE_CHECKS


#ifndef NDEBUG
#define DEBUGIWFE
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// static declaration
CToken* CEquation::ms_ptPlus = NULL; 

CEquation::CEquation():m_eState(ceqUninitated),m_pctLeft(NULL),m_pctAssign(NULL),m_pvrRight(NULL),m_vResult(0),m_bHasArrays(false),m_iAFBrackets(NOT_DEFINED),m_iAFCode(NOT_DEFINED),m_bHasArrayFunc(false)
{
	createPlusToken();
	m_pVarClassFactory = CVarClassFactory::instance();
}

// set up the static values.
#ifdef EQSTOPOPTION
bool CEquation::m_gStopCallFromEqs = false;
xt_value CEquation::m_gxtTimeStart = NOT_DEFINED;
long CEquation::m_giIndexTime = NOT_DEFINED;
#endif // #ifdef EQSTOPOPTION


CEquation::CEquation(const CEquation& CE):m_pvrRight(NULL),m_iAFBrackets(NOT_DEFINED),m_iAFCode(NOT_DEFINED),m_bHasArrayFunc(false)
{
	m_pVarClassFactory = CVarClassFactory::instance();
	createPlusToken();
	copy(CE);
}

CEquation::CEquation(long iLeft,long iRight,vector<CToken*>& vExpLine, ostream& osErrReport):m_eState(ceqUninitated),m_pctLeft(NULL),m_pctAssign(NULL),m_pvrRight(NULL),m_bHasArrays(false),m_iAFBrackets(NOT_DEFINED),m_iAFCode(NOT_DEFINED),m_bHasArrayFunc(false)
{

	vector< CToken* >::iterator itpCT;
	// itpCTRight is foudn this way as I'm not sure &vExp[iRight] would produce the same result in all conditions
	vector< CToken* >::const_iterator itpCTRight = getRightWithoutComments(iLeft,iRight,vExpLine);

	createPlusToken();

	if (IsWellFormedEquation(iLeft,iRight,vExpLine,osErrReport))
		{
		CArrayFactory* pAF = CArrayFactory::instance();
		m_pctLeft = vExpLine[iLeft];
		m_pctAssign = vExpLine[iLeft+1];
		startCheckArrayFunc();
		for(itpCT=&vExpLine[iLeft+2];(itpCT!=vExpLine.end())&&(itpCT!=itpCTRight);itpCT++)
			{
			checkArrayFunc(*itpCT);
			m_vpctRight.push_back(*itpCT);	
			}
		
			m_eState=ceqIntiated;
		}
		else
		m_eState=ceqError; // the equation is in an error state and cannot be used
}


CEquation::~CEquation()
{

}

void CEquation::cleanupInstance()
{
	delete ms_ptPlus;
	ms_ptPlus = NULL;
}

void CEquation::createPlusToken()
{
	if (!ms_ptPlus)
		{
		ms_ptPlus = newtrack CToken;
		ms_ptPlus->setString(g_Plus);
		ms_ptPlus->setType(ctDelim);
		atexit(&cleanupInstance);
		}
}

void CEquation::copy(const CEquation& CE)
{
	ASSERT2((CE.m_eState==ceqIntiated)||(CE.m_eState==ceqUninitated)); // don't do this once equation is ready top solve or in error

	m_eState = CE.m_eState;
	m_pctLeft = CE.m_pctLeft;
	m_pctAssign = CE.m_pctAssign;
	m_vpctRight.clear();
	m_vpctRight = CE.m_vpctRight;
//	m_pVarClassFactory = CE.m_pVarClassFactory; // should be unnecessary - however design might change latter
	m_pvrRight = CE.m_pvrRight;
	m_vResult = CE.m_vResult;
	m_bHasArrays = CE.m_bHasArrays;
    m_bHasArrayFunc = CE.m_bHasArrayFunc;
	assert(m_vpctRight==CE.m_vpctRight);
	
}

bool CEquation::operator() (const CEquation& ce1, const CEquation& ce2) const
{
 
 return ce2.greaterThan(ce1); 
 
}

bool CEquation::operator > (const CEquation& ce) const
{

 return greaterThan(ce); 

}

bool CEquation::greaterThan(const CEquation& CE) const
{

	if ((*m_pctLeft)>(*CE.m_pctLeft))
			return true;
	if ((*m_pctAssign)>(*CE.m_pctAssign))
			return true;
	if (CE.m_vpctRight<m_vpctRight) // http://www.sgi.com/tech/stl/Vector.html
			return true;
	
	return false;
}


bool CEquation::IsWellFormedEquation(long iLeft,long iRight,vector<CToken*>& vExpLine, ostream& osErrReport)
{
 
 // Need the same stuff here as with equations.

//	VectorLineTokenPts::iterator it;
	vector< CToken* >::iterator itpCT;
	// itpCTRight is foudn this way as I'm not sure &vExp[iRight] would produce the same result in all conditions
	vector< CToken* >::const_iterator itpCTRight = getRightWithoutComments(iLeft,iRight,vExpLine);
//	set< CToken*, CTokenStrCompare >::iterator itSet;
	bool bResult = true; // ie OK unless a fault can be found
	long iOpenBrackets, iCloseBrackets;

//	Equations need to be checked for:

//	[1] derivatives - values need to be adjusted to make a connection
//	[2] derivatives - if an individual variable doesn't exist for
//					  a derivative then a place holder token needs to be
//					  created.
//	[3] LHS and RHS need to be clearly identified
//	[4] Brackets need to used correctly
//	[5] Delimators need to be interspaced correctly
//	[6] Only one variable before Eq - thats how equations are being handled right now.
//  [7] The equation is not temrinated with an unmatched deliminator

#ifndef NDEBUG
	osErrReport << "IsWellFormedEquation ? "<<iLeft<<", "<<iRight<<" [";
	for(itpCT=&vExpLine[iLeft];(itpCT!=vExpLine.end())&&(itpCT!=itpCTRight);itpCT++)
		osErrReport << (*itpCT)->getString();
	osErrReport << "]\n";osErrReport<<"{"<<vExpLine[iRight-1]->getString()<<"}"<<endl;
	osErrReport << (*vExpLine[iRight-1])<<endl;
#endif

//	Future feature
//	==============
//	Like to try creating a map of errors by collecting error message thrown - this could
//	then be used for context sensative error reporting.
//

	if (iRight<=iLeft) // this really should not happen - but needs to be handled.
				{
				osErrReport << "<Internal Error*> Unable to evaluate expression - please contact vendor\n";
				#ifndef NDEBUG
				osErrReport << "iRight<=iLeft " << iRight <<"<="<< iLeft<<endl;osErrReport.flush();
				ASSERT2(false); // lets catch this if it happends in a debug release
				#endif
				SYMERRORLITE("Unable to evaluate expression",errInternal);
				return false; 
				}

	if (vExpLine.size()==0)
				{
				osErrReport << "<Internal Error*> Unable to evaluate expression - please contact vendor\n";
				#ifndef NDEBUG
				osErrReport << "vExpLine.size()==0\n";osErrReport.flush();
				ASSERT2(false); // lets catch this if it happends in a debug release
				#endif
				SYMERRORLITE("Unable to evaluate expression",errInternal);
				return false; 
				}

	if (vExpLine.size()<(iRight-iLeft))
				{
				osErrReport << "<Internal Error*> Unable to evaluate expression - please contact vendor\n";
				#ifndef NDEBUG
				osErrReport << "vExpLine.size()<(iRight-iLeft)\n";osErrReport.flush();
				ASSERT2(false); // lets catch this if it happends in a debug release
				#endif
				SYMERRORLITE("Unable to evaluate expression",errInternal);
				return false; 
				}


	if (iLeft>=vExpLine.size())// need to catch this
				{
				osErrReport << "<Internal Error*> Unable to evaluate expression - please contact vendor\n";
				#ifndef NDEBUG
				osErrReport << "vExpLine.size()<(iRight-iLeft)\n";osErrReport.flush();
				ASSERT2(false); // lets catch this if it happends in a debug release
				#endif
				SYMERRORLITE("Unable to evaluate expression",errInternal);
				return false; 
				}
	

		try
		{
		int iCountSymbols = 0;

		// check LHS has not been declared as an array

//#ifndef _TEST_LHSARRAY
		if (CArrayFactory::instance()->anyArraysHere(*vExpLine[iLeft],true))
				{
				osErrReport << "<Error*> Trying to assign a value to an array already declared\n";
				SYMERRORTOK("Trying to assign a value to an array already declared or implied by later equation",errSyntax,vExpLine[iLeft]);
				throw 1L;
				}
//#endif

	//	itpCT=&vExpLine[iLeft]; // delete after following it back
		for(itpCT=&vExpLine[iLeft];(itpCT!=vExpLine.end())&&(itpCT!=itpCTRight);itpCT++)
				if ((*itpCT)->getType()!=ctComment)
					iCountSymbols++;	
		// The second symbol should be '=' ie g_Eq
		if (iCountSymbols<3)
				{
				osErrReport << "<Error*> Line has too few symbols on : ";
				if (vExpLine.size()==0)
						{
						osErrReport << "unable to give location.\n";
						SYMERRORLITE("A line has too few symbols on",errInternal);
						}
						else
						{
						osErrReport << vExpLine[0]->getLine() << " line.\n";
						SYMERRORTOK("Line has too few symbols on it",errSyntax,vExpLine[0]);
						}
				throw 1L;

				} // end ((*it)->size()<3)
		// check LHS is formated OK

		//either there is one variable on the left followed by an g_Eq or a derivative
		itpCT = &vExpLine[iLeft];
		if ((!(*itpCT)->IsOfTypeVariable())&&((*itpCT)->getType()!=ctDerivative))
				{
				osErrReport << "<Error*> Left hand side should be a variable on : "<<vExpLine[iLeft]->getLine() <<(*vExpLine[0])<< " line.\n";
				SYMERRORTOK("Left hand side should be a variable",errSyntax,vExpLine[iLeft]);
				throw 1L;
				}


		// check for normal equation - if not then
		if ( vExpLine[iLeft+1]->getString().compare(g_Eq)!=0) // true if not normal equation
			{
			// check for derivative
			if (!isDerivative(vExpLine,iLeft,iRight))
					{
					osErrReport << "<Error*> Equation is not properly formed on : "<<vExpLine[iLeft]->getLine() << " line.\n";
					SYMERRORTOK("Equation is not properly formed - check derivative",errSyntax,vExpLine[iLeft]);
					throw 1L;
					} 

			}

		iOpenBrackets=iCloseBrackets=0; // reset as equal
		for(itpCT=&vExpLine[iLeft];(itpCT!=vExpLine.end())&&(itpCT!=itpCTRight);itpCT++)
				if ((*itpCT)->getType()==ctDelim)
					{
					if ( (*itpCT)->getString().compare(g_OpenBracket)==0)
							iOpenBrackets++;
							else
							if ( (*itpCT)->getString().compare(g_CloseBracket)==0)
								iCloseBrackets++;
					}

		if (iOpenBrackets!=iCloseBrackets)
				{
				osErrReport << "<Error*> Brackets don't match : "<<vExpLine[iLeft]->getLine() << " line.\n";
				SYMERRORTOK("Check brackets match",errSyntax,vExpLine[iLeft]);
				throw 1L;
				}

		// check the correct arrangement exists for the RHS 
		bool bLastDelim = true;
		itpCT=&vExpLine[iLeft];
		// role forward to the equals sign - should always be token 2 .. but this is more robust
		long iLHSLeft = iLeft;
		while(((itpCT!=vExpLine.end())&&(itpCT!=itpCTRight))&&
		     ((*itpCT)->getType()!=ctDelim)||((*itpCT)->getString().compare(g_Eq)!=0))
			{
			itpCT++;iLHSLeft++;
			}
		if ((itpCT==vExpLine.end())||(itpCT==itpCTRight)) // note changed from && 10Jun08 - assume it should catch either
				{
				osErrReport << "<Error*> Equation is not properly formed on its RHS (a): "<<vExpLine[iLeft]->getLine() << " line.\n";
				SYMERRORTOK("Equation is not properly formed on its RHS",errSyntax,vExpLine[iLeft]);
				throw 1L; 
				}

#ifdef COMBINE_CHECKS
// maybe iLHSLeft should be ++ again
#ifndef NDEBUG
		osErrReport <<"Before "<<vExpLine[iLHSLeft]->getString().c_str();
#endif
		iLHSLeft++;
#ifndef NDEBUG
		osErrReport <<" and After "<<vExpLine[iLHSLeft]->getString().c_str()<<endl;
#endif

		long iSize = getPosRightWithoutComments(iLeft,vExpLine.size(),vExpLine) - iLHSLeft;

		switch(iSize)
		{
		case 0:
			SYMERRORTOK("Problem with RHS of equation",errSyntax,vExpLine[iLHSLeft-1]);// not sure this will ever be needed
			bResult = false;
			break;
		case 1:
			if ((vExpLine[iLHSLeft]->IsOfTypeVariable())||(vExpLine[iLHSLeft]->IsOfType(ctNumber))||(vExpLine[iLHSLeft]->IsOfType(ctDerivative)))
						bResult = true;
					else
						{
						SYMERRORTOK("Problem with RHS of equation",errSyntax,vExpLine[iLHSLeft]);
						bResult = false;
						}
			break;
		case 2: // the first term had better be a minus
			if (vExpLine[iLHSLeft]->getStringRef().compare(g_Minus)!=0) // then  this isn't going to work out
				{
				SYMERRORTOK("Problem with RHS of equation",errSyntax,vExpLine[iLHSLeft]);
				bResult = false;
				}
				else
				{
				if ((vExpLine[iLHSLeft+1]->IsOfTypeVariable())||(vExpLine[iLHSLeft+1]->IsOfType(ctNumber))||(vExpLine[iLHSLeft+1]->IsOfType(ctDerivative)))
							bResult = true;
						else
							{
							SYMERRORTOK("Problem with RHS of equation",errSyntax,vExpLine[iLHSLeft+1]);
							bResult = false;
							}
				}

			break;
		default:
			bResult = IsWellFormedExpression(iLHSLeft,iRight,vExpLine,osErrReport,true);	
			break;

		}


		}
		catch(long i)
		{
		 bResult=false;
		 if (i!=1)
			 SYMERRORTOK("Error checking an equation",errSyntax,vExpLine[0]);
		 // do nothing here
		}
		catch(...)
		{
		 bResult=false;
		 SYMERRORTOK("Unhandled error checking an equation",errInternal,vExpLine[0]);
		 // do nothing here
		}; // so can break out here


		return bResult;
		
		//============================================
#else								
		itpCT++;

		while((itpCT!=vExpLine.end())&&(itpCT!=itpCTRight))
		{

		#ifndef NDEBUG
			string sTemp = (*itpCT)->getString(); // for watching value in debugger
		#endif

			if  (!(((*itpCT)->getString().compare(g_OpenBracket)==0)|| // not brackets
			((*itpCT)->getString().compare(g_CloseBracket)==0)))
				{

				if ((bLastDelim)&&(	(*itpCT)->IsOfType(ctDelim)))
						{
						// maybe g_Minus for a negative variable to follow
						if (!(((*itpCT)->getString().compare(g_Minus)==0)&&(isNegativeVarVal(itpCT,vExpLine))))
								{
								osErrReport << "<Error*> Equation is not properly formed on its RHS, two ctDelim next to each other : "<<vExpLine[iLeft]->getLine() << " line.\n";
								SYMERRORTOK("Equation is not properly formed on its RHS",errSyntax,vExpLine[iLeft]);
								throw 1L;
								}
								else
								bLastDelim=!bLastDelim; // to be reversed again latter
						}
						else
						if ((!bLastDelim)&&(((*itpCT)->IsOfTypeVariable())))
							{
							osErrReport << "<Error*> Equation is not properly formed on its RHS 2 val/variables next to each other: "<<vExpLine[iLeft]->getLine() << " line.\n";
							SYMERRORTOK("Equation is not properly formed on its RHS, variables next to each other",errSyntax,vExpLine[iLeft]);
							throw 1L;
							}

				bLastDelim=!bLastDelim;

				}
				else // barckets either opening or closing
				{
				if ((*itpCT)->getString().compare(g_OpenBracket)==0) // its an open barcket - then in effect its a varaible
						if (!bLastDelim)
							{
							osErrReport << "<Error*> RHS open bracket not preceeded by Delim: "<<vExpLine[iLeft]->getLine() << " line.\n";
							SYMERRORTOK("RHS open bracket not preceeded by an operator",errSyntax,(*itpCT));
							throw 1L;
							}
						else					
					if ((*itpCT)->getString().compare(g_CloseBracket)==0) // its an open barcket - then in effect its a varaible
							if (bLastDelim)
								{
								osErrReport << "<Error*> RHS close bracket not preceeded by Variable/Value: "<<vExpLine[iLeft]->getLine() << " line.\n";
								SYMERRORTOK("RHS close bracket not preceeded by a variable or value",errSyntax,(*itpCT));
								throw 1L;
								}

				}

			itpCT++;

		}


		}
		catch(...)
		{
		 bResult=false;
		 // do nothing here
		}; // so can break out here

	
	
	return bResult;
#endif

}



///////////////////////////////////////////////////////////
// Function name	: CEquation::IsWellFormedExpression
// Description	    : Helper static function
// Return type		: bool 
// Argument         : long iLeft
// Argument         : long iRight
// Argument         : vector<CToken*>& vExpLine
// Argument         : ostream& osErrReport
// Argument         : bool bArrayFuncs - default false
// Argument         : bool bEqualsOK - default false
///////////////////////////////////////////////////////////
bool CEquation::IsWellFormedExpression(long iLeft,long iRight,vector<CToken*>& vExpLine, ostream& osErrReport, bool bArrayFuncs, bool bEqualsOK )
{
 // Need the same stuff here as with equations.

//	VectorLineTokenPts::iterator it;
	vector< CToken* >::iterator itpCT;
	// itpCTRight is foudn this way as I'm not sure &vExp[iRight] would produce the same result in all conditions
	vector< CToken* >::const_iterator itpCTRight = getRightWithoutComments(iLeft,iRight,vExpLine);
//	set< CToken*, CTokenStrCompare >::iterator itSet;
	bool bResult = true; // ie OK unless a fault can be found
	long iOpenBrackets, iCloseBrackets;
	CFuncIdentifierSingleton* fis = CFuncIdentifierSingleton::instance();
	long iArrayFuncCount = 0;

//	Equations need to be checked for:

//	[1] derivatives - values need to be adjusted to make a connection
//	[2] derivatives - if an individual variable doesn't exist for
//					  a derivative then a place holder token needs to be
//					  created.
//	[3] LHS and RHS need to be clearly identified
//	[4] Brackets need to used correctly
//	[5] Delimators need to be interspaced correctly
//	[6] Only one variable before Eq - thats how equations are being handled right now.

#ifndef NDEBUG
	osErrReport << "IsWellFormedExpression ? "<<iLeft<<", "<<iRight<<" [";
	for(itpCT=&vExpLine[iLeft];(itpCT!=vExpLine.end())&&(itpCT!=itpCTRight);itpCT++)
		osErrReport << (*itpCT)->getString();
	osErrReport << "]\n";osErrReport<<"{"<<vExpLine[iRight-1]->getString()<<"}"<<endl;
#endif

//	Future feature
//	==============
//	Like to try creating a map of errors by collecting error message thrown - this could
//	then be used for context sensative error reporting. ** Done **
//

	if (iRight<=iLeft) // this really should not happen - but needs to be handled.
				{
				osErrReport << "<Internal Error*> Unable to evaluate expression - please contact vendor\n";
				SYMERRORLITE("Unable to evaluate expression",errInternal);
				#ifndef NDEBUG
				osErrReport << "iRight<=iLeft " << iRight <<"<="<< iLeft<<endl;osErrReport.flush();
				assert(false); // lets catch this if it happends in a debug release
				#endif
				return false; 
				}

	if (vExpLine.size()==0)
				{
				osErrReport << "<Internal Error*> Unable to evaluate expression - error code "<<ERROR_EQUATION_1 << " please contact vendor\n";
				SYMERRORLITE("Unable to evaluate expression",errInternal);
				#ifndef NDEBUG
				osErrReport << "vExpLine.size()==0\n";osErrReport.flush();
				assert(false); // lets catch this if it happends in a debug release
				#endif
				return false; 
				}

	if (vExpLine.size()<(iRight-iLeft))
				{
				osErrReport << "<Internal Error*> Unable to evaluate expression - error code "<<ERROR_EQUATION_1 << " please contact vendor\n";
				SYMERRORLITE("Unable to evaluate expression",errInternal);
				#ifndef NDEBUG
				osErrReport << "vExpLine.size()<(iRight-iLeft)\n";osErrReport.flush();
				assert(false); // lets catch this if it happends in a debug release
				#endif
				return false; 
				}
	
		try
		{
		int iCountSymbols = 0;
		bool bHasAt = false; // to catch equations that were meant to be g_at events
	//	itpCT=&vExpLine[iLeft]; // delete after following it back
		for(itpCT=&vExpLine[iLeft];(itpCT!=vExpLine.end())&&(itpCT!=itpCTRight);itpCT++)
				{
				if ((*itpCT)->getType()!=ctComment)
					iCountSymbols++;
				if ((*itpCT)->getString().compare(g_At)==0)
					{
					string sErrorMes;
					sErrorMes = "Equation cannot have '";
					sErrorMes.append(g_At);
					sErrorMes.append("' symbol in it. Check if poorly formated event was intended");
					SYMERRORTOK(sErrorMes.c_str(),errSyntax,(*itpCT));
					throw 1L;
					}
				}
		// iCountSymbols 
		if (iCountSymbols<1)
				{
				osErrReport << "vExpLine[iLeft] = " << *vExpLine[iLeft] <<" and iLeft = "<<iLeft<<endl;
				osErrReport << "itpCTRight = " << **itpCTRight <<endl;
				osErrReport << "<Error*> Line has too few symbols on : ";
				SYMERRORTOK("Line does not have enough information to be an equation",errSyntax,vExpLine[iLeft]);
				if (vExpLine.size()==0)
						osErrReport << "unable to give location.\n";
						else
						osErrReport << vExpLine[0]->getLine() << " line.\n";
				throw 1L;
				} // end ((*it)->size()<3)

		itpCT = &vExpLine[iLeft];


		iOpenBrackets=iCloseBrackets=0; // reset as equal
		for(itpCT=&vExpLine[iLeft];(itpCT!=vExpLine.end())&&(itpCT!=itpCTRight);itpCT++)
				if ((*itpCT)->getType()==ctDelim)
					{
					if ( (*itpCT)->getString().compare(g_OpenBracket)==0)
							iOpenBrackets++;
							else
							if ( (*itpCT)->getString().compare(g_CloseBracket)==0)
								iCloseBrackets++;
					}

		if (iOpenBrackets!=iCloseBrackets)
				{
				osErrReport << "<Error*> Brackets don't match : "<<vExpLine[iLeft]->getLine() << " line.\n";
				SYMERRORTOK("Brackets do not match",errSyntax,vExpLine[iLeft]);
				throw 1L;
				}

#ifdef DEBUGIWFE
		for(itpCT=&vExpLine[iLeft];(itpCT!=vExpLine.end())&&(itpCT!=itpCTRight);itpCT++)
			ATLTRACE("%s",(*itpCT)->getString().c_str());
		ATLTRACE("\n");
#endif

		// check the correct arrangement exists for the RHS 
		bool bLastDelim = true;
		bool bNextOpenBrackets = false; // so can track after a function
		itpCT=&vExpLine[iLeft];
/*		// role forward to the equals sign - should always be token 2 .. but this is more robust
		while(((itpCT!=vExpLine.end())&&(itpCT!=itpCTRight))&&
		     ((*itpCT)->getType()!=ctDelim)||((*itpCT)->getString().compare(g_Eq)!=0))
			{
			itpCT++;
			}   */
		if ((itpCT==vExpLine.end())&&(itpCT==itpCTRight))
				{
				osErrReport << "<Error*> Expression is not properly formed (a): "<<vExpLine[iLeft]->getLine() << " line.\n";
				SYMERRORTOK("Expression is not properly formed",errSyntax,vExpLine[iLeft]);
				throw 1L; 
				}		

		// check first expression is legal
		if ((*itpCT)->IsOfType(ctDelim)) // not sure this is necessary
				{
#ifndef NDEBUG
				osErrReport << (*itpCT)->getString().c_str()<<endl;
#endif
				if ((*itpCT)->getString().compare(g_OpenBracket)!=0)
						if ((*itpCT)->getString().compare(g_Minus)!=0)
							if ((*itpCT)->getString().compare(g_Plus)!=0)
								if (fis->identify((*itpCT)->getString())==C_NotAFunc)
										{
										SYMERRORTOK("The RHS is badly formed at the start",errSyntax,(*itpCT));
										throw 1L;
										}
				}




		while((itpCT!=vExpLine.end())&&(itpCT!=itpCTRight))
		{

		#ifndef NDEBUG
			string sTemp = (*itpCT)->getString(); // for watching value in debugger
		#ifdef DEBUGIWFE
			ATLTRACE("%s\t",sTemp.c_str());
			switch((*itpCT)->getType())
			{
				case ctDefinedNotAssigned:
					ATLTRACE("ctDefinedNotAssigned");
					break;
				case ctComment:
					ATLTRACE("ctComment");
					break;
				case ctDerivative:
					ATLTRACE("ctDerivative");
					break;
				case ctVariable:
					ATLTRACE("ctVariable");
					break;
				case ctDelim:
					ATLTRACE("ctDelim");
					break;
				case ctNotDefined:
					ATLTRACE("ctNotDefined");
					break;
				case ctNumber:
					ATLTRACE("ctNumber");
					break;
				default:
					ATLTRACE("type(%d)",(*itpCT)->getType());
					break;
			}
			ATLTRACE("\n");

		#endif
		#endif

			// check for illegal Delim's at this point
			if ((*itpCT)->IsOfType(ctDelim))
				{
					switch ((*itpCT)->getString()[0])
					{
						case '+':
						case '-':
						case '>':
						case '<':
						case '(':
						case ')':
						case '^':
						case '/':
						case '*':
							// all OK
							break;
						case '=':
							if (bEqualsOK) // then its OK
								break;
						default:
							ASSERT2(fis);
							if (fis->identify((*itpCT)->getString())==C_NotAFunc)
									{
									// not so good.
									SYMERRORTOK("Illegal operator found in expression",errSyntax,(*itpCT));
									throw 1L;
									}
							break;

					}


				}




			if ((bArrayFuncs)&&(iArrayFuncCount>0)) // every line a winner
				{
				iArrayFuncCount++;
				if (iArrayFuncCount>4)
					{
						SYMERRORTOK("Expected open brackets after a function call",errSyntax,(*itpCT));
						throw 1L;
					}
				if ((iArrayFuncCount==3)&&(!(*itpCT)->IsOfTypeVariable()))
					{
						SYMERRORTOK("An array function needs a variable.",errSyntax,(*itpCT));
						throw 1L;
					}
				}

			if  (!(((*itpCT)->getString().compare(g_OpenBracket)==0)|| // not brackets
			((*itpCT)->getString().compare(g_CloseBracket)==0)))
				{
				if (bNextOpenBrackets)
						{
						SYMERRORTOK("Expected open brackets after a function call",errSyntax,(*itpCT));
						throw 1L;
						}

				if ((bLastDelim)&&(	(*itpCT)->IsOfType(ctDelim)))
						{
						// maybe g_Minus for a negative variable to follow
						if (!(((*itpCT)->getString().compare(g_Minus)==0)&&(isNegativeVarVal(itpCT,vExpLine))))
								if (fis->identify((*itpCT)->getString())==C_NotAFunc)
									{
									osErrReport << "<Error*> Expression is not properly formed on its RHS, two ctDelim next to each other : "<<vExpLine[iLeft]->getLine() << " line.\n";
									SYMERRORTOK("Expression is not properly formed on its RHS",errSyntax,(*itpCT));
									throw 1L;
									}
								else
								bNextOpenBrackets=true; // a function will be followed by open brackets
						 bLastDelim=!bLastDelim; // to be reversed again latter
						}
						else
						{
						if ((!bLastDelim)&&(((*itpCT)->IsOfTypeVariable())))
							{
							osErrReport << "<Error*> Expression is not properly formed on its RHS 2 val/variables next to each other: "<<vExpLine[iLeft]->getLine() << " line.\n";
							SYMERRORTOK("Expression is not properly formed on its RHS",errSyntax,(*itpCT));
							throw 1L;
							}
						}

				if ((*itpCT)->IsOfType(ctNumber)&&(!bLastDelim)&&((*itpCT)->getNumber()<0))
						{
						// why do this ? As the negative number is also a delim number
						bLastDelim=!bLastDelim; // to be reversed latter 
						}

				if ((bArrayFuncs)&&((*itpCT)->IsOfType(ctArrayKeyWord)))
					{
					if (iArrayFuncCount>0)
						{
							osErrReport << "<Error*> Array function directly following another "<<vExpLine[iLeft]->getLine() << " line.\n";
							SYMERRORTOK("Array functions not seperated by operator",errSyntax,(*itpCT));
							throw 1L;
						}
					
					if (!bLastDelim)
						{	
							osErrReport << "<Error*> Check before this array function"<<vExpLine[iLeft]->getLine() << " line.\n";
							SYMERRORTOK("Character proceeding array function not correct.",errSyntax,(*itpCT));
							throw 1L;
						}

					if (!(fis->identifyArrayFunc((*itpCT)->getString())!=C_NotAFunc))
										{
										osErrReport << "<Error*> Expression is not properly formed on its RHS, two ctDelim next to each other : "<<vExpLine[iLeft]->getLine() << " line.\n";
										SYMERRORTOK("Expression is not properly formed on its RHS",errSyntax,(*itpCT));
										throw 1L;
										}
					iArrayFuncCount=1;
					bNextOpenBrackets=true;
					bLastDelim=!bLastDelim; // to be reversed again latter
					}

				bLastDelim=!bLastDelim;

				}
				else // brackets either opening or closing
				{
				if ((*itpCT)->getString().compare(g_OpenBracket)==0) // its an open barcket - then in effect its a varaible bLastDelim in this context also
						{
						if ((bArrayFuncs)&&(iArrayFuncCount!=0)&&(iArrayFuncCount!=2)) 
							{
							osErrReport << "<Error*> RHS Array function not followed by '"<< g_OpenBracket<<"': "<<vExpLine[iLeft]->getLine() << " line.\n";
							SYMERRORTOK("RHS Array function not followed by an open bracket",errSyntax,(*itpCT));
							throw 1L;
							}

						if (!bLastDelim)
							{
							osErrReport << "<Error*> RHS open bracket not preceeded by Delim: "<<vExpLine[iLeft]->getLine() << " line.\n";
							SYMERRORTOK("RHS open bracket must not be preceeded an operator",errSyntax,(*itpCT));
							throw 1L;
							}
						bNextOpenBrackets=false;
						}
						else
						{
						if ((bArrayFuncs)&&(iArrayFuncCount!=0))
							if (iArrayFuncCount!=4) 
								{
								osErrReport << "<Error*> RHS Array function can only have one array in brackets: "<<vExpLine[iLeft]->getLine() << " line.\n";
								SYMERRORTOK("RHS Array function can only have one array in brackets",errSyntax,(*itpCT));
								throw 1L;
								}
							else
								{
								iArrayFuncCount=0; // last one
								}

						if (bNextOpenBrackets)
								{
								SYMERRORTOK("Expected an open bracket after a function",errSyntax,(*itpCT));
								throw 1L;
								}
						if ((*itpCT)->getString().compare(g_CloseBracket)==0) // its an open bracket - then in effect its a varaible
							if (bLastDelim)
								{
								osErrReport << "<Error*> RHS close bracket not preceeded by Variable/Value: "<<vExpLine[iLeft]->getLine() << " line.\n";
								SYMERRORTOK("RHS close bracket not preceeded by Variable/Value",errSyntax,(*itpCT));
								throw 1L;
								}
						}
				}

			itpCT++;

		} // while

		// need to check status of last symbol

		if ((*(--itpCT))->IsOfType(ctDelim))
				{
				if ((*itpCT)->getString().compare(g_CloseBracket)!=0)
						{
						SYMERRORTOK("The RHS is badly formed at the end",errSyntax,(*itpCT));
						throw 1L;
						}
				}
		if (bNextOpenBrackets)
			{
			SYMERRORTOK("Expected an open bracket after a function",errSyntax,(*itpCT));
			throw 1L;
			}

		}
		catch(...)
		{
		 bResult=false;
		 // do nothing here
		}; // so can break out here

	
	
	return bResult;

}



///////////////////////////////////////////////////////////
// Function name	: CEquation::isDerivative
// Description	    : 
// Return type		: bool 
// Argument         : vector< CToken* >& vecLine
// Argument         : long lLeft
// Argument         : long lRight
///////////////////////////////////////////////////////////
bool CEquation::isDerivative(vector< CToken* >& vecLine, long lLeft, long lRight)
{
	bool bResult = false;

	if ((lRight-lLeft)<1) // too small and need to avoid referncing none existant CTokens - of course this really should no happen
		{
		#ifndef NDEBUG
		assert(false);
		#endif
		return false;
		}

	if (vecLine.size()<lRight)
		{
		ASSERT2(false);
		return false;
		}

	if (vecLine[lLeft]->IsOfType(ctDerivative))
		return true;

	if ((lRight-lLeft)<4) // too small and need to avoid referncing none existant CTokens
		return false;

	if ( (vecLine[lLeft+1]->getString().compare(g_Slash)==0) && (vecLine[lLeft+3]->getString().compare(g_Eq)==0) ) // then may be a derivative
					{
					if  (( (vecLine[lLeft]->getString()[0]==g_cDeriv) && (vecLine[lLeft+2]->getString()[0]==g_cDeriv) ))
							bResult = true;
					}		


	return bResult;
}


///////////////////////////////////////////////////////////
// Function name	: CEquation::isDerivative
// Description	    : 
// Return type		: bool 
// Argument         : VectorLineTokenPts::iterator it
///////////////////////////////////////////////////////////
bool CEquation::isDerivative(VectorLineTokenPts::iterator it)
{
	bool bResult = false;

	if ((*it).size()<1) // too small and need to avoid referncing none existant CTokens
		return false;

	if ((*it)[0]->IsOfType(ctDerivative))
		return true;

	if ((*it).size()<4) // too small and need to avoid referncing none existant CTokens
		return false;

	if ( ((*it)[1]->getString().compare(g_Slash)==0) && ((*it)[3]->getString().compare(g_Eq)==0) ) // then may be a derivative
					{
					if  (( ((*it)[0]->getString()[0]==g_cDeriv) && ((*it)[2]->getString()[0]==g_cDeriv) ))
							bResult = true;
					}		


	return bResult;
}


///////////////////////////////////////////////////////////
// Function name	: CEquation::sendtostream const
// Description	    : 
// Return type		: void 
// Argument         : ostream& os
///////////////////////////////////////////////////////////
void CEquation::sendtostream(ostream& os) const
{

	vector< CToken* >::const_iterator iter;

	if ((m_eState!=ceqIntiated)&&(m_eState!=ceqReadyToSolve))
			{
			os << "<Warning> Equation no initialised.";
			return;
			}


	ASSERT2((m_pctLeft!=NULL)&&(m_pctAssign!=NULL)); // catch unexpected bug - yes I know :-)

	os << m_pctLeft->getString().c_str() << m_pctAssign->getString().c_str();

	for (iter = m_vpctRight.begin();iter!=m_vpctRight.end();iter++)
		os << (*iter)->getString();

}

#ifndef NDEBUG

void CEquation::sentToAtlTrace() const
{

	vector< CToken* >::const_iterator iter;

	if ((m_eState!=ceqIntiated)&&(m_eState!=ceqReadyToSolve))
			{
			ATLTRACE("<Warning> Equation no initialised.\n");
			return;
			}


	ASSERT2((m_pctLeft!=NULL)&&(m_pctAssign!=NULL)); // catch unexpected bug - yes I know :-)

	ATLTRACE("%s%s",m_pctLeft->getString().c_str(),m_pctAssign->getString().c_str());

	for (iter = m_vpctRight.begin();iter!=m_vpctRight.end();iter++)
		ATLTRACE("%s",(*iter)->getString().c_str());

	ATLTRACE("\n");

}
#endif

///////////////////////////////////////////////////////////
// Function name	: CEquation::lhsIsDerivative
// Description	    : 
// Return type		: bool 
///////////////////////////////////////////////////////////
bool CEquation::lhsIsDerivative()
{
	if (m_pctLeft->IsOfType(ctDerivative))
		return true;
	return false;
}


///////////////////////////////////////////////////////////
// Function name	: CEquation::getUnderlyingLHSVarString const
// Description	    : 
// Return type		: string 
///////////////////////////////////////////////////////////
string CEquation::getUnderlyingLHSVarString() const
{
	if (m_pctLeft->IsOfType(ctDerivative))
		return getVariableFromDerivative(m_pctLeft->getString());
	
	return m_pctLeft->getString();
}


///////////////////////////////////////////////////////////
// Function name	: CEquation::getVariableFromDerivative
// Description	    : 
// Return type		: string 
// Argument         : const string& sDerv
///////////////////////////////////////////////////////////
string CEquation::getVariableFromDerivative(const string& sDerv)
{

	return CToken::getVariableFromDerivative(sDerv);

}


///////////////////////////////////////////////////////////
// Function name	: CEquation::isNegativeVarVal
// Description	    : looking if negative value or varaiable is pointed to by '-'
// Return type		: bool 
// Argument         : vector< CToken* >::const_iterator it
// Argument         : const vector< CToken* >& vpct
///////////////////////////////////////////////////////////
bool CEquation::isNegativeVarVal(vector< CToken* >::const_iterator it, const vector< CToken* >& vpct)
{
	bool bResult;
	vector< CToken* >::const_iterator itp1 = it;
	itp1++;

	ASSERT2((*it)->getString().compare(g_Minus)==0);
	if ((*it)->getString().compare(g_Minus)!=0)
			return false;

	if (itp1==vpct.end())
			return false;

	switch((*itp1)->getType())
	{
		case ctVariable:
		case ctDepVariable:
		case ctIndVariable:
			bResult = true;
			break;
		default:
			bResult = false;
	}

	return bResult;

}


///////////////////////////////////////////////////////////
// Function name	: CEquation::checkAllRHSDefined
// Description	    : Optional arguments allow for reporting
//                    which items are not defined.
// Return type		: bool 
// Argument         : const set<CToken* > setDef
// Argument         : bool bReport/*=false*/
// Argument         : ostream& oserr/*=cerr*/
///////////////////////////////////////////////////////////
bool CEquation::checkAllRHSDefined(const set<CToken* > setDef, bool bReport/*=false*/, ostream& oserr/*=cerr*/ ) const
{
	vector<CToken* >::const_iterator itv;
	vector<CToken* >::const_iterator itvError = m_vpctRight.begin(); //shoudl not ever be needed - but don't want undefined pointers floating around
	set<CToken* >::const_iterator cits = setDef.end();
	bool bResult = true;
	string sErr = "";
	for (itv=m_vpctRight.begin();itv!=m_vpctRight.end();itv++)
		if ((*itv)->IsOfTypeVariable())
				//bResult &= (cits!=setDef.find((*itv)->getRootTokenPt()));
				if (cits==setDef.find((*itv)->getRootTokenPt()))
					{
					if ((bReport)&&(!bResult))
						{
						oserr << ", ";
						sErr.append(", ");
						}
					bResult=false;
					if (bReport)
						{
						oserr << (*itv)->getString().c_str();
						sErr.append((*itv)->getString().c_str());
						itvError=itv;
						}
					}
	if ((bReport)&&(!bResult))
			{
			SYMERRORTOK("The following variable was undefined in an equation "/*,sErr.c_str()*/,errSyntax,(*itvError));
			oserr << " undefined at simulation start.";
			}
	return bResult;

}


///////////////////////////////////////////////////////////
// Function name	: CEquation::canEvaluate
// Description	    : 
// Return type		: bool 
///////////////////////////////////////////////////////////
bool CEquation::canEvaluate()
{
	// If the equation now has assigned variables then evalute those 
	// alternatively see if RHS is just one number
	if (m_eState==ceqReadyToSolve)
			return true;
	if (isAFixedExpression())
			return true;

	return false;

}


///////////////////////////////////////////////////////////
// Function name	: CEquation::evaluate
// Description	    : 
// Return type		: variable 
// Argument         : vector<variable>* pvecV/*=NULL*/
///////////////////////////////////////////////////////////
variable CEquation::evaluate(vector<variable>* pvecV/*=NULL*/)
{

	ASSERT2(canEvaluate());
	if (!canEvaluate())
		return -1; // not great - but don't want to fail here if not debug

	if (isAFixedExpression()) // may have to move this latter
			return m_vpctRight[0]->getStringRef().getNumber();


	if (!ceqReadyToSolve)
			return CANNOT_EVALUATE;

	if ((m_vpctRight.size()==1)&&(m_vpctRight[0]->IsOfType(ctNumber)))
			return m_vpctRight[0]->getNumber();
		
	ASSERT2(pvecV/*assert not Null*/);
	if (!pvecV)
		return CANNOT_EVALUATE; // will need to improve this response

	return m_pctLeft->getRootTokenPt()->getValue(pvecV);

}



///////////////////////////////////////////////////////////
// Function name	: CEquation::isAFixedExpression
// Description	    : 
// Return type		: bool 
///////////////////////////////////////////////////////////
bool CEquation::isAFixedExpression()
{
/*	if (!canEvaluate())
		return false;*/

	return (m_vpctRight.size()==1)&&(m_vpctRight[0]->IsOfType(ctNumber));
}


#define FINDTHENSWAPTWO( fund_desc ) { if (bNotSwapped) \
{ \
			itse = find( fund_desc ,itseLeft,itseRight); \
			if ((itse!=itseRight)&&(itse!=itseRightLessOne)) \
				bNotSwapped = !swapTwoForOne(vecExp,itse,pvcf);\
} }




///////////////////////////////////////////////////////////
// Function name	: CEquation::createExpression
// Description	    : 
// Return type		: CVarRoot* 
// Argument         : long iLeft
// Argument         : long iRight
// Argument         : vector<CToken*>& vecTok
// Argument         : ostream& oserr
// Argument         : list<CEquation*>* pvecpEquations
///////////////////////////////////////////////////////////
CVarRoot* CEquation::createExpression(long iLeft, long iRight, vector<CToken*>& vecTok, ostream& oserr, list<CEquation*>* pvecpEquations )
{
	bool bNotSwapped;
	vector< CToken* >::iterator itv;
	vector< CToken* >::const_iterator citRight = CNavTokens::getRightWithoutComments(iLeft,iRight,vecTok);
	vector< CSubExpression > vecExp; // this stack will be worked untill one expression is left
	vector< CSubExpression >::iterator itseLeft; 
	vector< CSubExpression >::iterator itseRight; 
	vector< CSubExpression >::iterator itseRightLessOne; 
	vector< CSubExpression >::iterator itseRightArrayFunc; 
	vector< CSubExpression >::iterator itse; 
	vector< CSubExpression >::iterator itseTemp; 
	CSubExpression* pSubExp;
	CVarClassFactory* pvcf = CVarClassFactory::instance();

	long lDepth,lLastDepth,lLastLength;
	// first set up stack

	#ifndef NDEBUG
	ostream_iterator<CSubExpression> outCSE(oserr," "); // see p53 STL book
	#endif

	try
	{

		
		{

//		m_tPlus.setString(g_Plus);
//		m_tPlus.setType(ctDelim);
		bool bNumOrVarBefore = false;


		for( itv=&vecTok[iLeft];itv!=citRight;itv++)
			{
			if (!(*itv)->IsOfType(ctComment))
					{
					if (bNumOrVarBefore&&((*itv)->IsOfType(ctNumber))&&((*itv)->getNumber()<0))
							{
							ASSERT2(ms_ptPlus);
							pSubExp = newtrack CSubExpression(ms_ptPlus,pvecpEquations,pvcf);
							vecExp.push_back(*pSubExp);
							delete pSubExp;
							// and of course bNumOrVarBefore stays true
							}
							else
							if (((*itv)->IsOfType(ctNumber))||((*itv)->IsOfTypeVariable())||((*itv)->getString().compare(g_CloseBracket)==0))
									bNumOrVarBefore = true;
									else
									bNumOrVarBefore = false;	


					pSubExp = newtrack CSubExpression(*itv,pvecpEquations,pvcf);
					vecExp.push_back(*pSubExp);
					delete pSubExp;
					}
			}
		}

		while(vecExp.size()>1)
		{
		 // need to look for expression to combine

		 // first work way to deepest point in brackets
		lDepth=0;
		lLastLength = vecExp.size();

		#ifndef NDEBUG
		std::copy(vecExp.begin(),vecExp.end(),outCSE);oserr<<endl;
		#endif

		itse=vecExp.begin();
		itseLeft=itse; //default if no brackets found
		do
		{
			lLastDepth=lDepth;
			if (itse->isTokenDelim()) // then has a token and may be a bracket - but ignore reserved tokens
				{
				if ((!itse->getToken()->isReserved())&&(itse->getToken()->getStringRef().compare(g_OpenBracket)==0))
						{
						lDepth++;
						itseLeft = itse;
						itseLeft++;
						}
						else
						if ((!itse->getToken()->isReserved())&&(itse->getToken()->getStringRef().compare(g_CloseBracket)==0))
							lDepth--;
				}

			if (lDepth>=lLastDepth)
						itse++;
		}
		while((lDepth>=lLastDepth)&&(itse!=vecExp.end()));
		
		itseRight = itse;
		itseRightLessOne = itseRight;
		itseRightLessOne--; // since not looking for some symbols at the end of expression


		bNotSwapped = true;
		// order of precidence brackets
		//                     functions
		//                     /
		//                     *
		//					   -
		//					   +
		//                     >
		//                     <
		if (itseRight!=vecExp.end()) // then brackets must have been encoutered - check if only one SubExpression left
			{
			itseTemp = itseRight; itseTemp--;
			if (itseTemp==itseLeft) // then only one item in brackets
				{
				vecExp.erase(itseRight);
				itseLeft--;
				vecExp.erase(itseLeft);
				bNotSwapped = false;
				}

			}

		
		if (bNotSwapped)
			{
			itse = find(g_Sum,itseLeft,itseRight);
			if ((itse!=itseRight)&&(itse!=itseRightLessOne)) // then its been found and isn't the last statment
				{
				itseRightArrayFunc = itse;
				itseRightArrayFunc++;
				if ((itseRightArrayFunc->isTokenDelim())&&(itseRightArrayFunc->getToken()->getString().compare(g_OpenBracket)==0))
						{
						bool bCarryOn=true;
						vector< CSubExpression* > vecpSubExps;
						itseRightArrayFunc++;
						while((bCarryOn)&&(itseRightArrayFunc!=itseRight)&&(itseRightArrayFunc->getToken()->isReserved()))
							{
							if ((itseRightArrayFunc->isTokenDelim())&&((itseRightArrayFunc->getToken()->getString().compare(g_CloseBracket)==0)))
									bCarryOn=false;
									else
									vecpSubExps.push_back(itseRightArrayFunc++);									
							}
						if (!bCarryOn)				
							bNotSwapped = !swapManyForOne(vecExp,itse,vecpSubExps,pvcf);
						vecpSubExps.clear();
						}
						else
						{	
						ASSERT2(false); // very very bad - must be stopped before this
						SYMERRORTOK("Error with Array function",errInternal,itseRightArrayFunc->getToken());
						}
				}
			}

		if (bNotSwapped)
			{
			itse = find(g_Count,itseLeft,itseRight);
			if ((itse!=itseRight)&&(itse!=itseRightLessOne)) // then its been found and isn't the last statment
				{
				itseRightArrayFunc = itse;
				itseRightArrayFunc++;
				if ((itseRightArrayFunc->isTokenDelim())&&(itseRightArrayFunc->getToken()->getString().compare(g_OpenBracket)==0))
						{
						bool bCarryOn=true;
						vector< CSubExpression* > vecpSubExps;
						itseRightArrayFunc++;
						while((bCarryOn)&&(itseRightArrayFunc!=itseRight)&&(itseRightArrayFunc->getToken()->isReserved()))
							{
							if ((itseRightArrayFunc->isTokenDelim())&&((itseRightArrayFunc->getToken()->getString().compare(g_CloseBracket)==0)))
									bCarryOn=false;
									else
									vecpSubExps.push_back(itseRightArrayFunc++);									
							}
						if (!bCarryOn)				
							bNotSwapped = !swapManyForOne(vecExp,itse,vecpSubExps,pvcf);
						vecpSubExps.clear();
						}
						else
						{	
						ASSERT2(false); // very very bad - must be stopped before this
						SYMERRORTOK("Error with Array function",errInternal,itseRightArrayFunc->getToken());
						}
				}
			}

		if (bNotSwapped)
			{
			itse = find(g_Avrg,itseLeft,itseRight);
			if ((itse!=itseRight)&&(itse!=itseRightLessOne)) // then its been found and isn't the last statment
				{
				itseRightArrayFunc = itse;
				itseRightArrayFunc++;
				if ((itseRightArrayFunc->isTokenDelim())&&(itseRightArrayFunc->getToken()->getString().compare(g_OpenBracket)==0))
						{
						bool bCarryOn=true;
						vector< CSubExpression* > vecpSubExps;
						itseRightArrayFunc++;
						while((bCarryOn)&&(itseRightArrayFunc!=itseRight)&&(itseRightArrayFunc->getToken()->isReserved()))
							{
							if ((itseRightArrayFunc->isTokenDelim())&&((itseRightArrayFunc->getToken()->getString().compare(g_CloseBracket)==0)))
									bCarryOn=false;
									else
									vecpSubExps.push_back(itseRightArrayFunc++);									
							}
						if (!bCarryOn)				
							bNotSwapped = !swapManyForOne(vecExp,itse,vecpSubExps,pvcf);
						vecpSubExps.clear();
						}
						else
						{	
						ASSERT2(false); // very very bad - must be stopped before this
						SYMERRORTOK("Error with Array function",errInternal,itseRightArrayFunc->getToken());
						}
				}
			}

					
		FINDTHENSWAPTWO(g_Abs);
		FINDTHENSWAPTWO(g_Ln);
//		FINDTHENSWAPTWO(g_Power);
		FINDTHENSWAPTWO(g_Exp);
		FINDTHENSWAPTWO(g_Sin);
		FINDTHENSWAPTWO(g_Cos);
		FINDTHENSWAPTWO(g_Tan);
		FINDTHENSWAPTWO(g_Log);
		FINDTHENSWAPTWO(g_IntFunc);
		FINDTHENSWAPTWO(g_IntRoundUpFunc);
/*
		if (bNotSwapped)
			{
			itse = find(g_Ln,itseLeft,itseRight);
			if ((itse!=itseRight)&&(itse!=itseRightLessOne)) // then its been found and isn't the last statment
				bNotSwapped = !swapTwoForOne(vecExp,itse,pvcf);
			}*/
/*		if (bNotSwapped)
			{
			itse = find(g_Power,itseLeft,itseRight);
			if ((itse!=itseRight)&&(itse!=itseRightLessOne)) // then its been found and isn't the last statment
				bNotSwapped = !swapTwoForOne(vecExp,itse,pvcf);
			}*/
/*
		if (bNotSwapped)
			{
			itse = find(g_Exp,itseLeft,itseRight);
			if ((itse!=itseRight)&&(itse!=itseRightLessOne)) // then its been found and isn't the last statment
				bNotSwapped = !swapTwoForOne(vecExp,itse,pvcf);
			}*/

		if (bNotSwapped)
			{
			itse = find(g_Pow,itseLeft,itseRight);
			if ((itse!=itseRight)&&(itse!=itseLeft)&&(itse!=itseRightLessOne)) // then its been found and isn't the last statment
				bNotSwapped = !swapThreeForOne(vecExp,itse,pvcf);
			}

		
		
		
		
		
		if (bNotSwapped)
			{
			itse = find(g_Div,itseLeft,itseRight);
			if ((itse!=itseRight)&&(itse!=itseLeft)&&(itse!=itseRightLessOne)) // then its been found and isn't the last statment
				bNotSwapped = !swapThreeForOne(vecExp,itse,pvcf);
			}

		if (bNotSwapped)
			{
			itse = find(g_Mult,itseLeft,itseRight);
			if ((itse!=itseRight)&&(itse!=itseLeft)&&(itse!=itseRightLessOne)) // then its been found and isn't the last statment
				bNotSwapped = !swapThreeForOne(vecExp,itse,pvcf);
			}

		if (bNotSwapped) // check for leading Minus case
						 // assumes itseLeft + 1 is not a Delim,
						 // the case where its a function should have been
						 // handled by colapsing those expressions earlier.
			{
			if ((itseLeft->isTokenDelim())&&(itseLeft->getToken()->getStringRef().compare(g_Minus)==0))
				{ // the first symbol is a minus and therefore a function needs to be carried out on the next expression
				bNotSwapped = !swapTwoForOne(vecExp,itseLeft,pvcf);
				}
			}

		if (bNotSwapped)
			{
			itse = find(g_Minus,itseLeft,itseRight);
			if ((itse!=itseRight)&&(itse!=itseLeft)&&(itse!=itseRightLessOne)) // then its been found and isn't the last statment
				bNotSwapped = !swapThreeForOne(vecExp,itse,pvcf);
			}

		// check for negative number with variable or number before it
		if (bNotSwapped)
			{
			bool bTrig = false;
			itse = itseLeft;
			itseTemp = itse;
			while((!bTrig)&&(++itse!=itseRight)&&(bNotSwapped))
				{
				if ((!itseTemp->isTokenDelim())&&(itse->isNegativeValue())) // only interested in last was a variable
					{
					bNotSwapped = !swapAddTwo(vecExp,itseTemp,itse,pvcf);
					bTrig = true; // must not use itse & itseTemp until new values assigned
					}
					else
					itseTemp = itse;


				}


			}

		if (bNotSwapped)
			{
			itse = find(g_Plus,itseLeft,itseRight);
			if ((itse!=itseRight)&&(itse!=itseLeft)&&(itse!=itseRightLessOne)) // then its been found and isn't the last statment
				bNotSwapped = !swapThreeForOne(vecExp,itse,pvcf);
			}

		if (bNotSwapped)
			{
			itse = find(g_GT,itseLeft,itseRight);
			if ((itse!=itseRight)&&(itse!=itseLeft)&&(itse!=itseRightLessOne)) // then its been found and isn't the last statment
				bNotSwapped = !swapThreeForOne(vecExp,itse,pvcf);
			}

		if (bNotSwapped)
			{
			itse = find(g_LT,itseLeft,itseRight);
			if ((itse!=itseRight)&&(itse!=itseLeft)&&(itse!=itseRightLessOne)) // then its been found and isn't the last statment
				bNotSwapped = !swapThreeForOne(vecExp,itse,pvcf);
			}

		#ifndef _SYMLIX
		#ifndef NDEBUG // only stop for debug in console mode
		if (lLastLength<=vecExp.size())
			{
			ATLTRACE("lLastLength = %d vecExp.size() = %d\n",lLastLength,vecExp.size());
			}
		ASSERT2(lLastLength>vecExp.size());
		#endif // can't be stuck in a loop
		#endif
		if (lLastLength==vecExp.size())
			throw newtrack CSubExpException("Unable to process expression","This is a programme error - please report");

		}


	}
	catch(CSubExpException* psee)
	{
		if (psee->hasMessage())
				{
				SYMERRORLITE2(psee->getHeading(),psee->getMessage(),errInternal);
				}
		else
				{
				SYMERRORLITE(psee->getHeading(),errInternal);
				}
		
		
		psee->out(oserr);
		delete psee;
		return NULL;
	}


	return vecExp[0].getVarRoot();
}


///////////////////////////////////////////////////////////
// Function name	: CEquation::setupExpression
// Description	    : 
// Return type		: bool 
// Argument         : list<CEquation*>* pvecpEquations
// Argument         : CVarClassFactory* pvcf
// Argument         : ostream& osErrReport/*=cerr*/
///////////////////////////////////////////////////////////
bool CEquation::setupExpression(list<CEquation*>* pvecpEquations, CVarClassFactory* pvcf, ostream& osErrReport/*=cerr*/)
{

#ifndef NDEBUG
#ifdef EXTRADEBUG
	cout << (*this) <<endl;
#endif
#endif

	m_pvrRight = createExpression(0,m_vpctRight.size(),m_vpctRight,osErrReport,pvecpEquations);
//	ASSERT2(m_pvrRight);
	if (!m_pvrRight)
			return false;
	m_pctLeft->getRootTokenPt()->setpVarRoot(m_pvrRight); // need to assign a CVarRoot for the LHS Token
	m_iIndex = m_pctLeft->getRootTokenPt()->getIndex();

	m_eState = ceqReadyToSolve;

	return true;

}

vector<CSubExpression>::iterator CEquation::find(const char* sPhrase, vector<CSubExpression>::iterator itseLeft, vector<CSubExpression>::iterator itseRight)
{
 bool bFound = false;
 vector<CSubExpression>::iterator itAns = itseRight;
 vector<CSubExpression>::iterator it;
 
 it = itseLeft;

 while((!bFound)&&(it!=itseRight))
 {
#ifdef EXTRADEBUG
	if (it->getToken())
		ATLTRACE("it = %s or type %d\n",it->getToken()->getString().c_str(),it->getToken()->getType());
#endif
	if (it->isTokenDelim())
		{
		if (it->getToken()->getStringRef().compare(sPhrase)==0)
				{
				itAns = it;
				bFound = true;
				}
		}
	it++;
 }

	return itAns;
}


bool CEquation::swapTwoForOne(vector<CSubExpression>& vecExp, vector<CSubExpression>::iterator itse, CVarClassFactory* pvcf)
{

	CSubExpression* pSubExp=NULL;
	vector<CSubExpression>::iterator itseRight;
	itseRight=itse;
	itseRight++;

	ASSERT2(itse);
	ASSERT2(itse!=vecExp.end());
	ASSERT2(itseRight!=vecExp.end());

		try
		{
			pSubExp = newtrack CSubExpression(itse,itseRight,pvcf); // copy of new Sub Expression
			// now remove old expressions
			itseRight++;// as need to go one beyond for erase
			vecExp.erase(itse,itseRight);
			vecExp.insert(itse,*pSubExp);
		}
		catch(CSubExpException* psee)
		{
		delete pSubExp;
		throw psee; // just needed to clean up pSubExp here
		}

	delete pSubExp;

	return true;
}

bool CEquation::swapThreeForOne(vector<CSubExpression>& vecExp, vector<CSubExpression>::iterator itse, CVarClassFactory* pvcf)
{

	CSubExpression* pSubExp;
	vector<CSubExpression>::iterator itseLeft;
	vector<CSubExpression>::iterator itseMid;
	vector<CSubExpression>::iterator itseRight;
	itseLeft=itse;
	itseLeft--;
	itseMid=itse;
	itseRight = itseMid;
	itseRight++;

	#ifndef NDEBUG // do more checks in debug mode
	ASSERT2(itse!=vecExp.begin());
	ASSERT2(itseLeft);
	ASSERT2(itseLeft!=vecExp.end());
	ASSERT2(itseMid!=vecExp.end());
	ASSERT2(itseRight!=vecExp.end());
	#else
	if (itse==vecExp.begin())
		throw newtrack CSubExpException("Format error","Deliminator is at the beginning when it should be second");
	#endif

		try
		{
			pSubExp = newtrack CSubExpression(itseLeft,itseMid,itseRight,pvcf); // copy of new Sub Expression
			// now remove old expressions
			itseRight++;// as need to go one beyond for erase
			vecExp.erase(itseLeft,itseRight);
			vecExp.insert(itseLeft,*pSubExp);
		}
		catch(CSubExpException* psee)
		{
		delete pSubExp;
		throw psee; // just needed to clean up pSubExp here
		}

	delete pSubExp;

	return true;
}


bool CEquation::swapManyForOne(vector<CSubExpression>& vecExp, vector<CSubExpression>::iterator itse, vector< CSubExpression* >& rvecpExp, CVarClassFactory* pvcf )
{
	CSubExpression* pSubExp;
	long iT;
	vector<CSubExpression>::iterator itseLeft;
	vector<CSubExpression>::iterator itseRight;
	itseLeft=itse;
//	itseLeft--;
	itseRight = itse;
  #ifdef EXTRADEBUG
	CToken* pleft = itseLeft->getToken();
	CToken* pse = itse->getToken();
	vector<CSubExpression>::iterator it;
 
	if (pleft&&pse)
		ATLTRACE("itseLeft %s, itse %s\n",pleft->getString().c_str(),pse->getString().c_str());
  #endif

	if (vecExp.size()<1)
		throw newtrack CSubExpException("Format error");

		try
		{
			pSubExp = newtrack CSubExpression(itse,rvecpExp,pvcf);
			// now remove old expressions
			itseRight++; // "("
			for (iT=0;iT<=rvecpExp.size();iT++) // will step one over as <=
				if (itseRight++==vecExp.end())
					throw newtrack CSubExpException("Format error");

			itseRight++;// as need to go one beyond for erase
#ifdef EXTRADEBUG
			for (it=vecExp.begin();it!=vecExp.end();it++)
				it->out(cout);
			cout <<endl;
#endif

			vecExp.erase(itseLeft,itseRight);
#ifdef EXTRADEBUG
			for (it=vecExp.begin();it!=vecExp.end();it++)
				it->out(cout);
			cout <<endl;
#endif
			vecExp.insert(itseLeft,*pSubExp);
#ifdef EXTRADEBUG
			for (it=vecExp.begin();it!=vecExp.end();it++)
				it->out(cout);
			cout <<endl;
#endif
		}
		catch(CSubExpException* psee)
		{
		delete pSubExp;
		throw psee; // just needed to clean up pSubExp here
		}

	delete pSubExp;


	return true;
}

bool CEquation::swapAddTwo(vector<CSubExpression>& vecExp,vector<CSubExpression>::iterator itseBefore,vector<CSubExpression>::iterator itseNegNum,CVarClassFactory* pvcf)
{
	CSubExpression* pSubExp;
	vector<CSubExpression>::iterator itseRight;

	#ifndef NDEBUG // do more checks in debug mode
	ASSERT2(itseNegNum!=vecExp.begin());
	ASSERT2(itseNegNum);
	ASSERT2(itseBefore);
	ASSERT2(itseNegNum!=vecExp.end());
	ASSERT2(itseBefore!=vecExp.end());
	#else
	if (itseNegNum==vecExp.begin())
		throw newtrack CSubExpException("Internal error","A problem encountered when compiling a line");
	#endif

		try
		{
			pSubExp = newtrack CSubExpression(itseBefore,itseNegNum,g_Plus,pvcf); // copy of new Sub Expression
			// now remove old expressions
			itseRight = itseNegNum; 
			itseRight++;// as need to go one beyond for erase
			vecExp.erase(itseBefore,itseRight);
			vecExp.insert(itseBefore,*pSubExp);
		}
		catch(CSubExpException* psee)
		{
		delete pSubExp;
		throw psee; // just needed to clean up pSubExp here
		}

	delete pSubExp;

	return true;

}

///////////////////////////////////////////////////////////
// Function name	: CEquation::updateValue
// Description	    : Updates the value in pvecVar to the result for the RHS
//                    given the contents of pvecVar
// Return type		: variable 
// Argument         : vectorValues* pvecVar
///////////////////////////////////////////////////////////
variable CEquation::updateValue(vectorValues* pvecVar)
{
	
	ASSERT2(pvecVar!=NULL);

	if (m_eState!=ceqReadyToSolve)
			return CANNOT_EVALUATE;

	ASSERT2(m_iIndex!=NOT_DEFINED);
	ASSERT2(m_iIndex<pvecVar->size());


#ifdef _DEBUGSTRONGTYPE
	variable vTest = m_pvrRight->getValue(*pvecVar);
	if (m_vResult.getType()==eCSTLowLimit)
		{	
		cout<<"Before "<<vTest<<" "<<m_vResult<<endl;
		ATLTRACE("Before %f %f\n",vTest,float(m_vResult));
		m_vResult = vTest;
		ATLTRACE("After %f %f\n",vTest,float(m_vResult));
		vTest = m_vResult;
		ATLTRACE("After2 %f %f\n",vTest,float(m_vResult));
		cout<<"After2 "<<vTest<<" "<<m_vResult<<endl;	
		}
#endif

#ifndef NDEBUG
	try
	{
#endif	
	(*pvecVar)[m_iIndex] = m_vResult = m_pvrRight->getValue(*pvecVar);
#ifndef NDEBUG
	}
	catch(CExceptionCVarRoot* pcecvr)
	{
	ATLTRACE("CExceptionCVarRoot* thrown in:\t");
	this->sentToAtlTrace();
	ATLTRACE("\n");
	throw pcecvr;
	}
#endif

	return (*pvecVar)[m_iIndex];

}


///////////////////////////////////////////////////////////
// Function name	: CEquation::setStrongType
// Description	    : 
// Return type		: void 
// Argument         : const vector< varStrongType >& vecst
///////////////////////////////////////////////////////////
void CEquation::setStrongType(const vector< varStrongType >& vecst)
{
	if (m_eState!=ceqReadyToSolve)
		{
		ASSERT2(m_eState==ceqReadyToSolve);
		return;
		}

#ifdef _DEBUGSTRONGTYPE
	cout << float(vecst[m_iIndex]) << endl;
#endif

	ASSERT2(m_iIndex!=NOT_DEFINED);
	ASSERT2(m_iIndex<vecst.size());

	m_pvrRight->setType( vecst[m_iIndex] );
	m_vResult.copy(vecst[m_iIndex]); // set up strong type info

}


///////////////////////////////////////////////////////////
// Function name	: CNavTokens::getRightWithoutComments
// Description	    : Identify where the right hand limit on a expression will be - ignoring comments
// Return type		: vector<CToken*>::const_iterator 
// Argument         : long iLeft
// Argument         : long iRight
// Argument         : vector<CToken*>& vExpLine
///////////////////////////////////////////////////////////
vector<CToken*>::const_iterator CNavTokens::getRightWithoutComments(long iLeft, long iRight, vector<CToken*>& vExpLine )
{

	if (iLeft>=iRight)
		{
		SYMERRORLITE("The parser has made a mistake - please report",errInternal);
		cerr <<"Going to be trouble !!\n";
		if (iLeft<vExpLine.size())
			return &vExpLine[iLeft];
		return vExpLine.begin(); // so nothing gets processed
		}
	ASSERT2(iLeft<iRight);
	ASSERT2(iLeft<vExpLine.size());
	vector<CToken*>::const_iterator itReturn;
	long iCount = iLeft;
	
	if (iLeft>=vExpLine.size())
			return vExpLine.end();

	itReturn = &vExpLine[iLeft];

	while((itReturn!=vExpLine.end())&&(iCount<iRight)&&(!(*itReturn)->IsOfType(ctComment)))
	{
		iCount++;
		itReturn++;
	}

	return itReturn;

}


///////////////////////////////////////////////////////////
// Function name	: CNavTokens::getPosRightWithoutComments
// Description	    : Identify where the right hand limit on a expression will be - ignoring comments
// Return type		: long 
// Argument         : long iLeft
// Argument         : long iRight
// Argument         : vector<CToken*>& vExpLine
///////////////////////////////////////////////////////////
long CNavTokens::getPosRightWithoutComments(long iLeft, long iRight, vector<CToken*>& vExpLine )
{

	ASSERT2(iLeft<iRight);
	ASSERT2(iLeft<vExpLine.size());
	vector<CToken*>::const_iterator itReturn;
	long iCount = iLeft;
	
	if (iLeft>=vExpLine.size())
			return vExpLine.size();

	itReturn = &vExpLine[iLeft];

	while((itReturn!=vExpLine.end())&&(iCount<iRight)&&(!(*itReturn)->IsOfType(ctComment)))
	{
		iCount++;
		itReturn++;
	}

	return iCount;

}

///////////////////////////////////////////////////////////
// Function name	: CNavTokens::getOneToRightOf
// Description	    : Returns either the long one past the point
//                    or the extereme Right / End of vector count
//                    (Whichever is the less)
// Return type		: long 
// Argument         :  const char* sTerm
// Argument         : vector<CToken*>& vExpLine
// Argument         : long iStart
// Argument         : long iRight
///////////////////////////////////////////////////////////
long CNavTokens::getOneToRightOf( const char* sTerm, vector<CToken*>& vExpLine,long iStart, long iRight )
{

	long iReturn = iStart;
	long iStop;
	if (iRight!=NOT_DEFINED)
			iStop = (iRight<vExpLine.size()?iRight:vExpLine.size());
			else
			iStop = vExpLine.size();

	iReturn = find(sTerm,vExpLine,iStart,iStop);

	iReturn++; // so 1 step over

	if (iReturn>iStop)
			return iStop;
	
	return iReturn;
}

///////////////////////////////////////////////////////////
// Function name	: CNavTokens::find
// Description	    : Returns either the long one past the point
//                    or the extereme Right / End of vector count
//                    (Whichever is the less)
// Return type		: long 
// Argument         :  const char* sTerm
// Argument         : vector<CToken*>& vExpLine
// Argument         : long iStart
// Argument         : long iRight
///////////////////////////////////////////////////////////
long CNavTokens::find( const char* sTerm, vector<CToken*>& vExpLine,long iStart, long iRight )
{

	long iReturn = iStart;
	long iStop;
	if (iRight!=NOT_DEFINED)
			iStop = (iRight<vExpLine.size()?iRight:vExpLine.size());
			else
			iStop = vExpLine.size();

	while ((iReturn!=iStop)&&(vExpLine[iReturn]->getString().compare(sTerm)!=0))
	{
		iReturn++;
	}

	if (iReturn>iStop)
			return iStop;

	
	return iReturn;
}


///////////////////////////////////////////////////////////
// Function name	: CEquation::createImpliedArray
// Description	    : Create any arrays which are implied by
//                    arrays included in the RHS
// Return type		: bool // true if an array has been created
// Argument         : CArrayFactory *pAF
///////////////////////////////////////////////////////////
bool CEquation::createImpliedArray(CArrayFactory *pAF)
{
	if (!pAF)
			return false;
	return pAF->createImpliedArray(m_vpctRight,m_pctLeft,m_bHasArrays);
}


///////////////////////////////////////////////////////////
// Function name	: CEquation::checkImpliedArrays
// Description	    : Check impied arrays are formated correctly
// Return type		: bool // true if successful - false if not in which case abandon simulation
// Argument         : CArrayFactory *pAF
///////////////////////////////////////////////////////////
bool CEquation::checkImpliedArrays(CArrayFactory *pAF)
{
	return ((pAF != NULL) ? ( pAF->anyArraysHere(m_vpctRight) ): false);

//  Think this is wrong - but leave it in case I figure why I queried the LHS
//	return ((pAF != NULL) ? ( pAF->anyArraysHere(m_vpctRight)||pAF->anyArraysHere(*m_pctLeft) ): false);
}


///////////////////////////////////////////////////////////
// Function name	: CEquation::expandArrayEquations
// Description	    : 
// Return type		: long 
// Argument         : list<CToken>& ltToks
// Argument         : vector<CEquation*>& rvecNewEqs
///////////////////////////////////////////////////////////
long CEquation::expandArrayEquations( list<CToken>& ltToks, vector<CEquation*>& rvecNewEqs, SetPtCTokenStringSearch& rsetPtToksUnique ) const
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
	CEquation* pe = newtrack CEquation(*this);
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
// Function name	: CEquation::setArrayIndex
// Description	    : Helper functio to set the array indicies on
//                    all the array elements for this equation
// Return type		: bool 
// Argument         : long iIndex
// Argument         : list<CToken>& ltToks
// Argument         : SetPtCTokenStringSearch& rsetPtToksUnique
///////////////////////////////////////////////////////////
bool CEquation::setArrayIndex(long iIndex, list<CToken>& ltToks, SetPtCTokenStringSearch& rsetPtToksUnique)
{

	list<CToken>::iterator it;
	SetPtCTokenStringSearch::iterator itSet;
	CToken tLHS(*m_pctLeft);
	vector< CToken* >::iterator itTok;
	CArrayFactory* pa = CArrayFactory::instance();

	ASSERT2(pa);
	if (!pa)
		{
		SYMERRORLITE("Out of memory",errSystem);	
		return false;
		}

	if (tLHS.IsOfType(ctDerivative))
		tLHS.setString(tLHS.getString().withDerivBracketedIndex(iIndex));
		else
		tLHS.setString(tLHS.getString().withBracketedIndex(iIndex));

	tLHS.setAsPartArray();
	ltToks.push_back(tLHS);
	m_pctLeft = &(ltToks.back());
	ATLTRACE("m_pctLeft = %s\n",m_pctLeft->getString().c_str());
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
				ATLTRACE("implied Token being created %s\n",tImplied.getString().c_str());
				rsetPtToksUnique.insert(&(ltToks.back()));
				}
			}


// need to check each token will have been assigned as an array where necessary by now

	for(itTok=m_vpctRight.begin();itTok!=m_vpctRight.end();itTok++)
		{
//		 if ((*itTok)->getArrayType()==atArray)
		 if (((*itTok)->IsOfTypeVariable())&&(pa->anyArraysHere(**itTok,true,true))) // find array if of type variable
				{
				CToken t2(**itTok);
				t2.setString(t2.getString().withBracketedIndex(iIndex));
				t2.setAsPartArray();
				ltToks.push_back(t2);
				(*itTok) = &(ltToks.back());
				ASSERT2((**itTok)==t2);
				ATLTRACE("Search for |%s|\n",t2.getString().c_str());
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
// Function name	: CEquation::checkArrayFunc
// Description	    : Helper function to set Token type info for Array functions and 
//                    associated Tokens
// Return type		: void 
// Argument         : CToken* pct
///////////////////////////////////////////////////////////
void CEquation::checkArrayFunc( CToken* pct )
{
	long iFunc;

	ASSERT2(m_iAFBrackets!=NOT_DEFINED); // ie haven't put cleat code first
	ASSERT2(m_iAFCode!=NOT_DEFINED);
	ASSERT2(pct);

	if (!pct)
			{
			SYMERRORLITE("Internal problem checking for array functions.",errInternal); // terrible - but need to report
			return;
			}

	if ((m_iAFBrackets>0)&&(m_iAFCode>0))
		{
		pct->setReserveType(m_iAFCode);
		if (pct->getString().compare(g_CloseBracket)==0)
			 startCheckArrayFunc(); // ie reset
		}
		else
		{
		if (pct->IsOfType(ctArrayKeyWord))
				{
				CFuncIdentifierSingleton* fis = CFuncIdentifierSingleton::instance();
				iFunc = fis->identifyArrayFunc(pct->getString());
				if (iFunc!=C_NotAFunc)
					{
					m_iAFCode = iFunc;
					m_iAFBrackets=1;
					pct->setReserveType(m_iAFCode);
					m_bHasArrayFunc = true;
					}
				}
		}

}


///////////////////////////////////////////////////////////
// Function name	: CEquation::expandArrayFunctions
// Description	    : Expand arrays in array functions
// Return type		: bool 
// Argument         : list<CToken>& rLToks
// Argument         : SetPtCTokenStringSearch& rSetUnique
///////////////////////////////////////////////////////////
bool CEquation::expandArrayFunctions(list<CToken>& rLToks, SetPtCTokenStringSearch& rSetUnique )
{
	if (!m_bHasArrayFunc) // already know there are no array functions so don't need to check
			return true;

	return expandArrayFunctionsForRHS(rLToks,m_vpctRight,rSetUnique);
}


///////////////////////////////////////////////////////////
// Function name	: CEquation::expandArrayFunctionsForRHS
// Description	    : Helper function so that other equation classes can use same code
//                    for expaning RHS statements.
// Return type		: bool 
// Argument         : list<CToken>& rLToks
// Argument         : vector< CToken* >& rvpTokRHS
///////////////////////////////////////////////////////////
bool CEquation::expandArrayFunctionsForRHS(list<CToken>& rLToks, vector< CToken* >& rvpTokRHS, SetPtCTokenStringSearch& rSetUnique  )
{

	vector< CToken* >::iterator ipTok = rvpTokRHS.begin();
	CArrayFactory* paf = CArrayFactory::instance();
	SetPtCTokenStringSearch::iterator itSet;
	vector< CToken* > vecNew;
	vector< CToken* >::iterator it;
	bool bChange = false;

#ifndef NDEBUG
	ATLTRACE("<Before expandArrayFunctionsForRHS>\n");
	for (ipTok=rvpTokRHS.begin();ipTok!=rvpTokRHS.end();ipTok++)
		ATLTRACE("%s",(*ipTok)->getString().c_str());
	ATLTRACE("\n");
	ipTok = rvpTokRHS.begin();
#endif

	ASSERT2(paf);
	if (!paf)
		{
		SYMERRORLITE("Out of memory",errSystem);
		return false;
		}

	while(ipTok!=rvpTokRHS.end())
	{
		#ifndef NDEBUG
		ATLTRACE("%s %d",(*ipTok)->getString().c_str(),(*ipTok)->getReserveType());
		if ((*ipTok)->getArrayType()==atArray)
			ATLTRACE(" Array\n");
			else
			ATLTRACE("\n");
		#endif
		if (((*ipTok)->isReserved())&&((*ipTok)->IsOfTypeVariable()))
			{
			if (paf->findArrayHere(**ipTok))
				{
				CToken cT = (**ipTok); // copy this token
				cT.ClearParent();
				CToken* pNewTok = NULL;
				CArray* pA = paf->getCurrentArray();
				bChange=true;

				if (!pA->first())
					{
					ASSERT2(pA->first()); // hey developer - look here
					SYMERRORTOK("Internal problem with array function.",errInternal,*ipTok); // v bad, but at leats handled
					return false;
					}

				do
					{
						cT.setString(pA->getString());
						cT.setAsPartArray();
						rLToks.push_back(cT);
						pNewTok = &rLToks.back();
						vecNew.push_back(pNewTok);
					}
				while(pA->next());

				}
				else
				vecNew.push_back(*ipTok);

			}
			else
			vecNew.push_back(*ipTok);

	ipTok++;

	}

	if (bChange) // else speed past
		{
		for (it=vecNew.begin();it!=vecNew.end();it++)
			{
			itSet = rSetUnique.find(*it);

			if (((*it)->IsOfTypeVariable())&&((*itSet)!=(*it)))
				if (itSet==rSetUnique.end())
					{
					ATLTRACE("Insert %s to unique Tokens %x\n",(*it)->getString().c_str(),*it);
					rSetUnique.insert(*it); // a new unique token
					}
					else
					{
					ATLTRACE("Assign parent for %s to unique Tokens %x\n",(*itSet)->getString().c_str(),*it);
					(*it)->AssignParent(*itSet);
					}

			}
		rvpTokRHS = vecNew;		
		}

#ifndef NDEBUG
	ATLTRACE("<After expandArrayFunctionsForRHS>\n");
	for (ipTok=rvpTokRHS.begin();ipTok!=rvpTokRHS.end();ipTok++)
		ATLTRACE("%s",(*ipTok)->getString().c_str());
	ATLTRACE("\n");
#endif

	return true;
}




///////////////////////////////////////////////////////////
// Function name	: CEquation::setLHSArrayStatus
// Description	    : Update LHS for its array status
// Return type		: void 
// Argument         : CArrayFactory* pAF
///////////////////////////////////////////////////////////
void CEquation::setLHSArrayStatus(CArrayFactory* pAF)
{
	if (!pAF)
		pAF = CArrayFactory::instance();

	if (!pAF)
		{
		SYMERRORLITE("Out of memory",errSystem);
		return;
		}

	if (pAF->anyArraysHere(*m_pctLeft))
			{
			m_bHasArrays = true;

			if (m_pctLeft->getArrayType()!=atArray)
					{
					CArray* pAr = NULL; 
					if (pAF->findUnderlyingArray(*m_pctLeft))
						{
						pAr = newtrack CArrayImplied(m_pctLeft);
					
						if (!pAr)
							{
							SYMERRORLITE("Out of memory",errSystem);
							return;
							}
					
						pAr->CatArray(pAF->getCurrentArray());

						if (!pAF->manageArray(pAr))
							{
							ASSERT2(false); // this shouldn't happen, should be prevented by earlier code
							delete pAr;
							SYMERRORTOK("Problem handling arrays",errInternal,m_pctLeft);
							return;
							}

						if (m_pctLeft->linkToArray(pAr))
								m_pctLeft->setAsArray();
								else
								{
								ASSERT2(false);
								SYMERRORTOK("Problem creating an array",errInternal,m_pctLeft);
								return;
								}
	
						}




					}
			}	

}
