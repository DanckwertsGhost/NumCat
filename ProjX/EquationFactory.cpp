// EquationFactory.cpp: implementation of the CEquationFactory class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EquationFactory.h"
#include "Symlix\ErrorFactory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEquationFactory::CEquationFactory()
{
	for(int iT=0;iT<g_iEquations;iT++)
		m_mapTypes[g_sEquations[iT]]=g_cEquations[iT];
}

CEquationFactory::~CEquationFactory()
{
	vector< CEquation* >::reverse_iterator it;

	// 
	for( it=m_vecCEquation.rbegin();it!=m_vecCEquation.rend();it++)
			delete *it;

	m_mapTypes.clear();

}

CEquationFactory* CEquationFactory::m_instance = 0;

///////////////////////////////////////////////////////////
// Function name	: CEquationFactory::makeInstance
// Description	    : Create a copy of the class
// Return type		: CEquationFactory* 
///////////////////////////////////////////////////////////
CEquationFactory* CEquationFactory::makeInstance()
{
    atexit(&cleanupInstance);
    return (newtrack CEquationFactory);
}


///////////////////////////////////////////////////////////
// Function name	: CEquationFactory::cleanupInstance
// Description	    : Clean up then destroy the class factory and associated 
//                    instances
// Return type		: void 
///////////////////////////////////////////////////////////
void CEquationFactory::cleanupInstance()
{ 
   delete m_instance;
   m_instance = 0;
}



///////////////////////////////////////////////////////////
// Function name	: CEquationFactory::checkUserRequestedEquation
// Description	    : 
// Return type		: bool 
// Argument         : vector<CToken*>& vLine
// Argument         : IARDataStore* pIStore
// Argument         : ostream& oserr
///////////////////////////////////////////////////////////
bool CEquationFactory::checkUserRequestedEquation(vector<CToken*>& vLine, IARDataStore* pIStore, ostream& oserr )
{
 long iLeft =0;
 long iRight = vLine.size();

 return checkUserRequestedEquation(iLeft,iRight,vLine,pIStore,oserr);
}



///////////////////////////////////////////////////////////
// Function name	: CEquationFactory::checkUserRequestedEquation
// Description	    : 
// Return type		: bool 
// Argument         : long iLeft
// Argument         : long iRight
// Argument         : vector<CToken*>& vLine
// Argument         : IARDataStore* pIStore
// Argument         : ostream& oserr
///////////////////////////////////////////////////////////
bool CEquationFactory::checkUserRequestedEquation(long iLeft, long iRight, vector<CToken*>& vLine, IARDataStore* pIStore, ostream& oserr )
{
 long iRightNC;
 ASSERT2(iRight>iLeft); // as this should not be here
 if ((iLeft==iRight)||(iLeft<0))
		{
		oserr << "<Warning*> Line could not be processed.\n";
		SYMERRORLITE("Line could not be processed",errInternal);
		return false;
		}

 if (vLine[iLeft]->IsOfType(ctEquationKeyWord))
	{

	 MapEqStringIndex::iterator itMap;

	 itMap = m_mapTypes.find(vLine[iLeft]->getString().c_str());

	 if (itMap==m_mapTypes.end())
				{
				oserr << "<Internal Error*> Unable to check type modifier specified by "<<vLine[0]->getString().c_str() << " keyword on line "<< vLine[0]->getLine()<<".\n";
				SYMERRORTOK("Unable to check type modifier specified",errSyntax,vLine[0]);
				return false;
				}

		switch(itMap->second)
			{
			case C_EqSwitch:
				return CEqSwitch::IsWellFormedSwitchEquation(iLeft,iRight,vLine,oserr);
				break;
			case C_EqLookup:
				if (!pIStore)
					return false;
				return CEqLookup::IsWellFormedLookupEquation(iLeft,iRight,vLine,pIStore,oserr);
				break;
			case C_NotAnEquationDef:
				oserr << "<Internal Error*> A keyword not defined for starting an equation is being used ";
				SYMERRORTOK("Unable to check type modifier specified in the equation",errInternal,vLine[0]);
				ASSERT2(false);
				break;
			default:
				oserr << "<Internal Error*> A keyword not recognised for starting an equation is being used ";
				SYMERRORTOK("Unable to check type modifier specified in the equation",errInternal,vLine[0]);
				ASSERT2(false);
				break;
			break;
			}

	}
	else
	{ // vanilla equation
	 iRightNC = getPosRightWithoutComments(iLeft,vLine.size(),vLine);
	 if ((iRightNC-iLeft)<3)
			{
			oserr << "<Error*> On line " <<vLine[iLeft]->getLine() << " not enough information to produce an equation.\n";
			SYMERRORTOK("Not enough information to produce an equation",errSyntax,vLine[iLeft]);
			return false;
			}
	 // check for valilla equation
	 if (1==find(g_Eq,vLine,iLeft,iRightNC)) // then may be a vanilla equation -run full tests
				return CEquation::IsWellFormedEquation(iLeft,iRightNC,vLine,oserr); 
	 oserr << "<Internal Error*> A equation was not recognised ";
	 SYMERRORTOK("A equation was not able to be recognised",errSyntax,vLine[iLeft]);
	}	

 
 // default
 oserr << " on line " <<vLine[iLeft]->getLine() << ".\n"; 
 #ifndef NDEBUG
 oserr<<"<begin line dump> ";
 for (vector<CToken*>::iterator itvt=vLine.begin();itvt!=vLine.end();itvt++)
		oserr << (*itvt)->getString().c_str();
 oserr<<"<end line dump>"<<endl;
 #endif

 return false;
 
}



///////////////////////////////////////////////////////////
// Function name	: CEquationFactory::createEquation
// Description	    : 
// Return type		: CEquation* 
// Argument         : long iLeft
// Argument         : long iRight
// Argument         : vector<CToken*>& vLine
// Argument         : IARDataStore* pIStore
// Argument         : ostream& osErrReport
// Argument         : bool bManageLife
///////////////////////////////////////////////////////////
CEquation* CEquationFactory::createEquation(long iLeft, long iRight, vector<CToken*>& vLine, IARDataStore* pIStore, ostream& osErrReport, bool bManageLife )
{
	
 ASSERT2(iRight>iLeft); // as this should not be here
 CEquation* pEq=NULL;

 if ((iLeft==iRight)||(iLeft<0))
		{
		osErrReport << "<Warning> Line could not be processed to create an equation.\n";
		SYMERRORLITE("Line could not be processed",errInternal);
		return NULL;
		}

 if (!checkUserRequestedEquation(iLeft,iRight,vLine,pIStore,osErrReport))
				{
				ASSERT2(false); // stop here is debug version
				osErrReport << "<Error*> Unable to check equation type specified by "<<vLine[iLeft]->getString().c_str() << " keyword on line "<< vLine[iLeft]->getLine()<<".\n";
				SYMERRORTOK("Unable to check equation type specified",errInternal,vLine[iLeft]);
				return NULL;
				}

 if (vLine[iLeft]->getType()==ctEquationKeyWord)
	{

	 MapEqStringIndex::iterator itMap;

	 itMap = m_mapTypes.find(vLine[iLeft]->getString().c_str());

	 if (itMap==m_mapTypes.end())
				{
				ASSERT2(false); // stop here is debug version
				osErrReport << "<Internal Error*> Unable to check equation type specified by "<<vLine[iLeft]->getString().c_str() << " keyword on line "<< vLine[iLeft]->getLine()<<".\n";
				SYMERRORTOK("Unable to check equation type specified",errInternal,vLine[iLeft]);
				return NULL;
				}

	 switch(itMap->second)
		{
			case C_EqSwitch:
				pEq =newtrack CEqSwitch(iLeft,iRight,vLine,osErrReport);
				break;
			case C_EqLookup:
				ASSERT2(pIStore);
				if (!pIStore) // cover the in the wild screw up
						{
						osErrReport << "<Internal Error*> Error in information retrieval system in software please report :- "<<vLine[iLeft]->getString().c_str() << " keyword on line "<< vLine[iLeft]->getLine()<<".\n";
						SYMERRORTOK("Unable to retrieve data from stream specified",errSystem,vLine[iLeft]);
						return NULL;
						}
				pEq =newtrack CEqLookup(iLeft,iRight,vLine,pIStore,osErrReport);
				break;
			case C_NotAnEquationDef:
				osErrReport << "<Underdevelopment*> Unable to create these equations ...\n";
				SYMERRORTOK("Equation format is not recognised",errSyntax,vLine[iLeft]);
				return NULL;
				break;
			default:
				osErrReport << "<Internal Error*> Unable to check equation type specified by "<<vLine[iLeft]->getString().c_str() << " keyword on line "<< vLine[iLeft]->getLine()<<".\n";
				SYMERRORTOK("Equation format is not recognised",errSyntax,vLine[iLeft]);
				return NULL;
		}

	}
	else
	{
		pEq = newtrack CEquation(iLeft,iRight,vLine,osErrReport);
	}

	if ((pEq)&&(!pEq->isCorrect()))
		{
		delete pEq;
		pEq=NULL;
		}

	if (pEq)
		m_vecCEquation.push_back(pEq); // which now manages life cycle
		else
		{
//		ASSERT2(false); // this is bad and should have been caught with checks before
		osErrReport << "<Internal Error*> Unable to create equation on line "<<vLine[iLeft]->getString().c_str()<<".\n";
		SYMERRORTOK("Unable to create equation on line ",errSystem,vLine[iLeft]);
		}

	return pEq;

}


///////////////////////////////////////////////////////////
// Function name	: CEquationFactory::expandArrayEquations
// Description	    : create all the equations that the LHS array requires
// Return type		: long 
// Argument         : CEquation* pEqMaster
// Argument         : list<CToken>& ltToks
// Argument         : vector<CEquation*>& rvecNewEqs
///////////////////////////////////////////////////////////
long CEquationFactory::expandArrayEquations( CEquation* pEqMaster, list<CToken>& ltToks, vector<CEquation*>& rvecNewEqs, SetPtCTokenStringSearch& rsetPtToksUnique )
{
//	vector<CEquation*>::const_iterator cit;
	if (!pEqMaster)
			return -1;

	rvecNewEqs.clear(); // precaution
	pEqMaster->expandArrayEquations(ltToks,rvecNewEqs,rsetPtToksUnique);

	return rvecNewEqs.size(); 
}


///////////////////////////////////////////////////////////
// Function name	: CEquationFactory::lookAfterLifeCycle
// Description	    : Allow other equations life cycle to be
//                    handled by the factory
// Return type		: bool 
// Argument         : CEquation* pe
///////////////////////////////////////////////////////////
bool CEquationFactory::lookAfterLifeCycle(CEquation* pe)
{
	if (!pe)
		return false;

	m_vecCEquation.push_back(pe);
	return true;
}
