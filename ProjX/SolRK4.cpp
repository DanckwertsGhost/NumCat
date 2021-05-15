// SolRK4.cpp: implementation of the CSolRK4 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SolRK4.h"
#include "IModelSim.h"
#include "global.h"
#ifndef NDEBUG
#include "assert.h"
#endif
#include "Symlix/ErrorFactory.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSolRK4::CSolRK4():CSolver(),m_iSize(NOT_DEFINED),m_xtOverRide(DEFAULT_TIME_STEP),m_bOverRideNext(false),m_k1(),m_k2(),m_k3(),m_k4() // by default
{
	m_bState=true; // as defining with default values
}

CSolRK4::CSolRK4(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport/*=cerr*/ ):CSolver(),m_iSize(NOT_DEFINED),m_xtOverRide(DEFAULT_TIME_STEP),m_bOverRideNext(false),m_k1(),m_k2(),m_k3(),m_k4() // by default
{
	m_bState = check(iLeft,iRight,vExpLine,osErrReport);

	if (this->isFormedOK()) // then check for time step info
		{
		long iEnd = getPosRightWithoutComments(iLeft,iRight,vExpLine);
		if ((iEnd-iLeft)==3) // then information to override default time step exists
				m_tstep = vExpLine[iLeft+2]->getNumber();
		ASSERT2(m_tstep!=NOT_FOUND); // check should have prevented this
		}
		else
		{
		osErrReport << "<Warning> Solver not defined correctly - default values used.\n";
		SYMERRORLITE("RK4 Solver not defined fully - default values used",errWarning);
		}

}

CSolRK4::~CSolRK4()
{
//	ATLTRACE("call CSolRK4::~CSolRK4()");
}


///////////////////////////////////////////////////////////
// Function name	: CSolRK4::setup
// Description	    : prepare solver
// Return type		: bool 
// Argument         : CIModelSim* pims
///////////////////////////////////////////////////////////
bool CSolRK4::setup(CIModelSim* pims)
{

#ifndef NDEBUG
	assert(pims);
#endif

	if ((!pims)||(!pims->isReady()))
			return false;

	pims->getModelIndexs(m_iIndVar,m_iDerivStart,m_iDerivEnd,m_iVarStart,m_iVarEnd);
#ifndef NDEBUG
	assert((m_iDerivEnd-m_iDerivStart)==(m_iVarEnd-m_iVarStart));
#endif
	if ((m_iDerivEnd-m_iDerivStart)!=(m_iVarEnd-m_iVarStart))
				return false;
	m_iSize = m_iVarEnd-m_iVarStart;

	// let get ready for solving

	m_k1.resize(m_iSize,0);
	m_k2.resize(m_iSize,0);
	m_k3.resize(m_iSize,0);
	m_k4.resize(m_iSize,0);
	m_startpos.resize(m_iSize); // as has already been ensure iSize==m_iVarEnd-m_iVarStart
	m_pIModelSim=pims;

	return true;
}




///////////////////////////////////////////////////////////
// Function name	: CSolRK4::step
// Description	    : Make a step forward - assumes intialised
//                    Debug code has asserts to catch this - but not release
// Return type		: xt_value of IndVar
// Argument         : vectorValues* pvecValues
// Argument			: vectorConstrainedValues* pvecConST 
///////////////////////////////////////////////////////////
xt_value CSolRK4::step(vectorValues* pvecValues,vectorConstrainedValues* pvecConST )
{
	long iT;
	xt_value xtTemp;

#ifndef NDEBUG // clearly don't want to do this in release solve mode
	assert(m_iSize!=NOT_DEFINED);
	assert(m_pIModelSim);
	assert(m_pIModelSim->isReady());
#endif

	if (m_bOverRideNext) // in case need to predict to a precise point - has more meaning for variable steps
		{
		xtTemp = m_tstep;
		m_tstep = m_xtOverRide;
		}

	// back up start position for variables
	copy(&(*pvecValues)[m_iVarStart],&(*pvecValues)[m_iVarEnd],m_startpos.begin());
	
	// find k1 values
	m_pIModelSim->updateValue(pvecValues);
	copy(&(*pvecValues)[m_iDerivStart],&(*pvecValues)[m_iDerivEnd],m_k1.begin());

	// find k2 values
	for(iT=0;iT<m_iSize;iT++)
		(*pvecValues)[m_iVarStart+iT] += 0.5*m_tstep*m_k1[iT];
	(*pvecValues)[m_iIndVar] += 0.5*m_tstep;
	m_pIModelSim->updateValue(pvecValues);
	copy(&(*pvecValues)[m_iDerivStart],&(*pvecValues)[m_iDerivEnd],m_k2.begin());

	// find k3 values
	for(iT=0;iT<m_iSize;iT++)
		(*pvecValues)[m_iVarStart+iT] = m_startpos[iT] + 0.5*m_tstep*m_k2[iT];
	// No time step forward for this k value
	m_pIModelSim->updateValue(pvecValues);
	copy(&(*pvecValues)[m_iDerivStart],&(*pvecValues)[m_iDerivEnd],m_k3.begin());

	// find k4 values
	for(iT=0;iT<m_iSize;iT++)
		(*pvecValues)[m_iVarStart+iT] = m_startpos[iT] + m_tstep*m_k3[iT];
	(*pvecValues)[m_iIndVar] += 0.5*m_tstep; // to bring it up to tstep forward
	m_pIModelSim->updateValue(pvecValues);
	copy(&(*pvecValues)[m_iDerivStart],&(*pvecValues)[m_iDerivEnd],m_k4.begin());

    // Now assign those values

/*#ifndef NDEBUG // for debuggin a problem
ATLTRACE(_T("RK4:- StartCalc %d.\n",this));
	for(iT=0;iT<m_iSize;iT++)
		{
		xt_value xtChange = ((double)(1.0/6.0)*(double(m_k1[iT]+2*m_k2[iT]+2*m_k3[iT]+m_k4[iT])))*m_tstep;
		cout << "m_startpos[iT] = "<<m_startpos[iT]<<"\t";
		cout << "m_k1[iT] = "<<m_k1[iT]<<"\t";
		cout << "m_k2[iT] = "<<m_k2[iT]<<"\t";
		cout << "m_k3[iT] = "<<m_k3[iT]<<"\t";
		cout << "m_k4[iT] = "<<m_k4[iT]<<"\n";
		cout << "(1/6) = "<<(1.0/6.0)<<"\t";
		cout << "All Ks = "<<m_k1[iT]+2*m_k2[iT]+2*m_k3[iT]+m_k4[iT]<<"\t";
		cout << "overall = "<<xtChange<<"\n";

		cout << "["<<m_iVarStart+iT<<"] Before "<<m_startpos[iT]<<endl;
		(*pvecValues)[m_iVarStart+iT] = 
		m_startpos[iT]+xtChange;
		cout <<"  After "<<(*pvecValues)[m_iVarStart+iT]<<endl;
		}
ATLTRACE(_T("RK4:- EndCalc %d.\n",this));
#else */

// Note it is only necessary to enforce pvecConST strong types here as the RHD of the key expressions are already constrained
// else where. Possibly this code should be move to a common implementation level to avoid replicatio - or at least the constraint part of it.
// not decided yet.

	for(iT=0;iT<m_iSize;iT++)
		(*pvecValues)[m_iVarStart+iT] = (*pvecConST)[m_iVarStart+iT] = 
		m_startpos[iT]+((1.0L/6.0L)*(m_k1[iT]+2.0L*m_k2[iT]+2.0L*m_k3[iT]+m_k4[iT]))*m_tstep;

/*#endif
/**/
	if (m_bOverRideNext)
		{
		m_tstep = xtTemp;
		m_bOverRideNext = false;
		}

	return (*pvecValues)[m_iIndVar];
}


///////////////////////////////////////////////////////////
// Function name	: CSolRK4::nextIndVarStep
// Description	    : To find out what the next step will be - 
//                    as RK4 is a fixed step technique this is easy here.
// Return type		: xt_value 
///////////////////////////////////////////////////////////
xt_value CSolRK4::nextIndVarStep() const // return predicted next time jump - in case over ride needed
{

	return m_tstep;
}


///////////////////////////////////////////////////////////
// Function name	: CSolRK4::overrideNextIndVarStep
// Description	    : 
// Return type		: void 
// Argument         : xt_value xtNextOnly
///////////////////////////////////////////////////////////
void CSolRK4::overrideNextIndVarStep(xt_value xtNextOnly)
{
	m_bOverRideNext = true;
	m_xtOverRide = xtNextOnly;

}


///////////////////////////////////////////////////////////
// Function name	: CSolRK4::check
// Description	    : Assumes check run on line one token beyond solver keyword
// Return type		: bool 
// Argument         : long iLeft
// Argument         : long iRight
// Argument         : vector<CToken*>& vExpLine
// Argument         : ostream& osErrReport
///////////////////////////////////////////////////////////
bool CSolRK4::check(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport )
{

	long iEnd = getPosRightWithoutComments(iLeft,iRight,vExpLine);
	
	if (iLeft!=iEnd-1) // then format for solver statement is wrong
		{
		if ((iEnd-iLeft)>3)
				{
				osErrReport << "<Error*> RK4 solver defintion has an error - try reducing the number of statements.\n";
				SYMERRORTOK("RK4 solver defintion has an error - try reducing the number of statements",errSyntax,vExpLine[iLeft]);
				return false;
				}
		if ((iEnd-iLeft)<3)
				{
				osErrReport << "<Error*> RK4 solver defintion has an error - the expression is missing term(s).\n";
				if ((iEnd-iLeft)>1)
					{
					SYMERRORTOK("RK4 solver defintion has an error - the expression is missing term(s)",errSyntax,vExpLine[iLeft]);
					}
					else
					{
					SYMERRORLITE("RK4 solver defintion has an error",errSyntax);
					}
				return false;
				}

		if ((!vExpLine[iLeft+1]->IsOfType(ctSolverKeyWord))&&(vExpLine[iLeft+1]->getString().compare(g_Step)!=0))
				{
				osErrReport << "<Error*> RK4 solver defintion needs a '"<<g_Step <<"' statement.\n";
				SYMERRORTOK2("RK4 solver defintion missing the following statement :",g_Step,errSyntax,vExpLine[iLeft+1]);
				return false;
				}

		if ((!vExpLine[iLeft+2]->IsOfType(ctNumber))&&(vExpLine[iLeft+2]->getNumber()<=0))
				{
				osErrReport << "<Error*> RK4 solver step needs to be greater than zero .\n";
				SYMERRORTOK("RK4 solver step needs to be greater than zero",errSyntax,vExpLine[iLeft+2]);
				return false;
				}

		}

/* Don't believe this is necessary as has already been identified in class factory
	if (vExpLine[iLeft]->getString().compare(g_RK4)==0)
		return true;

	return false;*/
	return true;
}
