// SolClassFactory.cpp: implementation of the CSolClassFactory class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SolClassFactory.h"
#include "global.h"
#include "SolRK3.h"
#include "SolRK3VS.h"
#include "SolRK4.h"
#include "SolRK4VS.h"
#include "SolRK4VSMT.h"
#include "SolRK5.h"
#include "SolRK5VS.h"
#include "SolOneStep.h"
#include "Symlix/ErrorFactory.h"
#ifndef NDEBUG
#include <assert.h>
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//#define C_RK4 1
//#define C_RK5VS 2

///////////////////////////////////////////////////////////
// Function name	: CSolClassFactory::CSolClassFactory
// Description	    : protected constructor
// Return type		: 
///////////////////////////////////////////////////////////
CSolClassFactory::CSolClassFactory()
{
	m_vecCSolver.reserve(20);
//	m_mapTypes["RK4"]=C_RK4;
//	m_mapTypes["RK5VS"]=C_RK5VS;
	for(long i=0;i<g_iSolvers;i++)
		m_mapTypes[g_sSolvers[i]]=g_cSolvers[i];


}


///////////////////////////////////////////////////////////
// Function name	: CSolClassFactory::~CSolClassFactory
// Description	    : protected destructor
// Return type		: 
///////////////////////////////////////////////////////////
CSolClassFactory::~CSolClassFactory()
{
	vector< CSolver* >::reverse_iterator it;

	// 
	for( it=m_vecCSolver.rbegin();it!=m_vecCSolver.rend();it++)
			delete *it;

	m_mapTypes.clear();
}

CSolClassFactory* CSolClassFactory::m_instance = 0;


///////////////////////////////////////////////////////////
// Function name	: CSolClassFactory::cleanupInstance
// Description	    : delete singleton instance
// Return type		: void 
///////////////////////////////////////////////////////////
void CSolClassFactory::cleanupInstance()
{ 
   delete m_instance;
   m_instance = 0;
}
         



///////////////////////////////////////////////////////////
// Function name	: CSolClassFactory::makeInstance
// Description	    : create singleton and add function to delete object to atexit()
// Return type		: CSolClassFactory* 
///////////////////////////////////////////////////////////
CSolClassFactory* CSolClassFactory::makeInstance()
{
    atexit(&cleanupInstance);
    return (newtrack CSolClassFactory);
}


CSolver* CSolClassFactory::createSolver(const char* sType, bool bManageLife)
{
	return createSolver(sType,NOT_DEFINED,NOT_DEFINED,NULL,cerr,bManageLife);
}

CSolver* CSolClassFactory::createSolver(const char* sType, long iLeft, long iRight, vector<CToken*>* pvExpLine, ostream& osErrReport, bool bManageLife )
{
	CSolver* sol = NULL;
	MapStringIndex::iterator itMap;

	itMap = m_mapTypes.find(sType);

	if (itMap==m_mapTypes.end())
				return NULL;

	switch(itMap->second)
	{
	case C_RK3Solver:
		if ((iLeft!=NOT_DEFINED)&&(iRight!=NOT_DEFINED)&&(pvExpLine)) 
				sol = newtrack CSolRK3(iLeft,iRight,*pvExpLine,osErrReport);
				else
				sol = newtrack CSolRK3(); // default
		break;
	case C_RK3VSSolver:
		if ((iLeft!=NOT_DEFINED)&&(iRight!=NOT_DEFINED)&&(pvExpLine)) 
				sol = newtrack CSolRK3VS(iLeft,iRight,*pvExpLine,osErrReport);
				else
				sol = newtrack CSolRK3VS(); // default
		break;
	case C_RK4Solver:
		if ((iLeft!=NOT_DEFINED)&&(iRight!=NOT_DEFINED)&&(pvExpLine)) 
				sol = newtrack CSolRK4(iLeft,iRight,*pvExpLine,osErrReport);
				else
				sol = newtrack CSolRK4(); // default
		break;
	case C_RK4VSSolver:
		if ((iLeft!=NOT_DEFINED)&&(iRight!=NOT_DEFINED)&&(pvExpLine)) 
				sol = newtrack CSolRK4VS(iLeft,iRight,*pvExpLine,osErrReport);
				else
				sol = newtrack CSolRK4VS(); // default
		break;
	case C_RK4VSMTSolver:
		if ((iLeft!=NOT_DEFINED)&&(iRight!=NOT_DEFINED)&&(pvExpLine)) 
				sol = newtrack CSolRK4VSMT(iLeft,iRight,*pvExpLine,osErrReport);
				else
				sol = newtrack CSolRK4VSMT(); // default
		break;
	case C_RK5Solver:
		if ((iLeft!=NOT_DEFINED)&&(iRight!=NOT_DEFINED)&&(pvExpLine)) 
				sol = newtrack CSolRK5(iLeft,iRight,*pvExpLine,osErrReport);
				else
				sol = newtrack CSolRK5(); // default
		break;
	case C_RK5VSSolver:
		if ((iLeft!=NOT_DEFINED)&&(iRight!=NOT_DEFINED)&&(pvExpLine)) 
				sol = newtrack CSolRK5VS(iLeft,iRight,*pvExpLine,osErrReport);
				else
				sol = newtrack CSolRK5VS(); // default
		break;
	case C_SequenceSolver:
	case C_OnceSolver:
	case C_AdvanceSolver:
		sol = newtrack CSolOneStep();
		break;
	default:
	ASSERT2(false); // bring attention to this - should not have passed find
	
	break;
	}

	if ((bManageLife)&&(sol)) // if requested to manage life of object then add to vector
		m_vecCSolver.push_back(sol); // so life cycle managed by factory

	return sol;
}



///////////////////////////////////////////////////////////
// Function name	: CSolClassFactory::checkUserRequestedSolver
// Description	    : Before solver objects created - check if information
//                    is correctly formatted and if not provide appropriate error
//                    messages.
// Return type		: bool 
// Argument         : vector<CToken*>& vLine
// Argument         : ostream& oserr
///////////////////////////////////////////////////////////
bool CSolClassFactory::checkUserRequestedSolver(vector<CToken*>& vLine, ostream& oserr )
{

	bool bResult = false; // be default
	MapStringIndex::iterator itMap;
	bool bOnce;
	if (vLine.size()==0)
				{
				oserr << "<Internal Error*> Malformed solver statement passed from parser. Internal error.\n"<<endl;
				SYMERRORLITE("Malformed solver statement passed from parser",errInternal);
				ASSERT2(false); // should not happen
				return false;
				}

	bOnce = (vLine[0]->getString().compare(g_Once)==0)||(vLine[0]->getString().compare(g_Advance)==0);

	if ((!bOnce)&&(vLine.size()<2))
				{
				oserr << "<Error*> Malformed solver statement on line "<<vLine[0]->getLine()<<endl;
				SYMERRORTOK("Malformed solver statement",errSyntax,vLine[0]);
				return false;
				}

	if (!vLine[0]->IsOfType(ctSolverKeyWord))
				{
				oserr << "<Internal Error*> first token of an solver statement must be a solver keyword.\n";
				SYMERRORTOK("First token of an solver statement must be a solver keyword",errInternal,vLine[0]);
				return false;
				}
#ifndef NDEBUG
//	cerr << "vLine size "<<vLine.size()<<" vLine[0] = "<< vLine[0]->getString().c_str()<<endl;
//	cerr << "vLine size "<<vLine.size()<<" vLine[1] = "<< vLine[1]->getString().c_str()<<endl;	
//	cerr << "vLine size "<<vLine.size()<<" vLine[2] = "<< vLine[2]->getString().c_str()<<endl;	
//	cerr << "vLine size "<<vLine.size()<<" vLine[3] = "<< vLine[3]->getString().c_str()<<endl;	
#endif

	if ((vLine[0]->getString().compare(g_Sequence)==0)||(bOnce))
		itMap = m_mapTypes.find(vLine[0]->getString().c_str());
		else
		itMap = m_mapTypes.find(vLine[1]->getString().c_str());



	if (itMap==m_mapTypes.end())
				{
				oserr << "<Error*> Solver type '"<<vLine[1]->getString().c_str()<<"' not recognised.\n";
				SYMERRORTOK("Solver type not recognised",errSyntax,vLine[1]);
				return false;
				}

	switch(itMap->second)
	{
	case C_RK3Solver:
		bResult = CSolRK3::check(1,vLine.size(),vLine,oserr);
		// check stuff to go here
		break;
	case C_RK3VSSolver:
		bResult = CSolRK3VS::check(1,vLine.size(),vLine,oserr);
		// check stuff to go here
		break;
	case C_RK4Solver:
		bResult = CSolRK4::check(1,vLine.size(),vLine,oserr);
		// check stuff to go here
		break;
	case C_RK4VSSolver:
		bResult = CSolRK4VS::check(1,vLine.size(),vLine,oserr);
		// check stuff to go here
		break;
	case C_RK4VSMTSolver:
		bResult = CSolRK4VSMT::check(1,vLine.size(),vLine,oserr);
		// check stuff to go here
		break;
	case C_RK5Solver:
		bResult = CSolRK5::check(1,vLine.size(),vLine,oserr);
		// check stuff to go here
		break;
	case C_RK5VSSolver:
		bResult = CSolRK5VS::check(1,vLine.size(),vLine,oserr);
		// check stuff to go here
		break;
	case C_SequenceSolver:
    case C_OnceSolver:
	case C_AdvanceSolver:
		bResult = true; // no further checks - they are carried out in the equivalent event or not at all for advance
		break;
	default:
		ASSERT2(false); // bring attention to this - should not have passed find
		
		break;

	}


	return bResult;


}



