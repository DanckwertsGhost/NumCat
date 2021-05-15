// SolRK4VS.cpp: implementation of the CSolRK4VS class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SolRK4VS.h"
#include "Symlix/ErrorFactory.h"




//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
/*
CSolRK4VS::CSolRK4VS():CSolver(),m_SolRK4(),m_xtOverRide(DEFAULT_TIME_STEP),m_vTolerance(DEFAULT_TOLERANCE_STEP),m_bOverRideNext(false)
{
	m_bState=true; // as defining with default values

}

CSolRK4VS::CSolRK4VS(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport ):
CSolver(),m_SolRK4(),m_xtOverRide(DEFAULT_TIME_STEP),m_vTolerance(DEFAULT_TOLERANCE_STEP),m_bOverRideNext(false)
{

	m_bState = check(iLeft,iRight,vExpLine,osErrReport);

	if (this->isFormedOK()) // then check for time step info
		{
		long iEnd = getPosRightWithoutComments(iLeft,iRight,vExpLine);
		if ((iEnd-iLeft)>=3) // then information to override default time step exists
				m_tstep = vExpLine[iLeft+2]->getNumber();
		ASSERT2(m_tstep!=NOT_FOUND); // check should have prevented this
		if ((iEnd-iLeft)==5) //then information to override default time step exists
				m_vTolerance = vExpLine[iLeft+4]->getNumber();
		}
		else
		{
		osErrReport << "<Warning*> Solver not defined correctly - default values used.\n";
		SYMERRORLITE("RK4VS Solver not defined fully - default values used",errWarning);
		}

}


CSolRK4VS::~CSolRK4VS()
{

}

*/

///////////////////////////////////////////////////////////
// Function name	: CSolRK4VS::check
// Description	    : static function that checks if solver description in
//                    tokens will be successful in generating an object.
// Return type		: bool 
// Argument         : long iLeft
// Argument         : long iRight
// Argument         : vector<CToken*>& vExpLine
// Argument         : ostream& osErrReport
///////////////////////////////////////////////////////////
bool CSolRK4VS::check(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport )
{

	long iEnd = getPosRightWithoutComments(iLeft,iRight,vExpLine);
	
	if (iLeft!=iEnd-1) // then format for solver statement is wrong
		{
		if ((iEnd-iLeft)>3)
				{
				if ((iEnd-iLeft)>5)
					{
					osErrReport << "<Error*> RK4VS solver defintion has an error - try reducing the number of statements.\n";
					SYMERRORTOK("RK4VS solver defintion has an error - try reducing the number of statements",errSyntax,vExpLine[iLeft]);
					return false;
					}
				if ((iEnd-iLeft)<5) 
					{
					osErrReport << "<Error*> RK4VS solver defintion has an error - check "<< g_Tolerance <<" term or length of solver statement.\n";
					SYMERRORTOK("RK4VS solver defintion has an error",errSyntax,vExpLine[iLeft]);
					return false;
					}
				if ((!vExpLine[iLeft+3]->IsOfType(ctSolverKeyWord))||(vExpLine[iLeft+3]->getString().compare(g_Tolerance)!=0))
					{
					osErrReport << "<Error*> RK4VS solver defintion needs either a "<< g_Tolerance <<" term after step or no further terms to use default.\n";
					SYMERRORTOK2("RK4VS solver defintion looking for: ",g_Tolerance,errSyntax,vExpLine[iLeft+3]);
					return false;
					}
				if (!vExpLine[iLeft+4]->IsOfType(ctNumber))
					{
					osErrReport << "<Error*> RK4VS solver "<< g_Tolerance <<" needs to be followed by a number.\n";
					SYMERRORTOK2(g_Tolerance," for RK4VS solver needs to be followed by number",errSyntax,vExpLine[iLeft+4]);
					return false;
					}
				if (vExpLine[iLeft+4]->getNumber()<=0)
					{
					osErrReport << "<Error*> RK4VS solver "<< g_Tolerance <<" needs to be a number greater than 0.\n";
					SYMERRORTOK2(g_Tolerance," for RK4VS solver needs to be followed by positive number",errSyntax,vExpLine[iLeft+4]);
					return false;
					}
				}

		if ((iEnd-iLeft)<3)
				{
				osErrReport << "<Error*> RK4VS solver defintion has an error - the expression is missing term(s).\n";
				SYMERRORTOK("RK4VS solver defintion has an error - the expression is missing term(s)",errSyntax,vExpLine[0]);
				return false;
				}

		if ((!vExpLine[iLeft+1]->IsOfType(ctSolverKeyWord))||(vExpLine[iLeft+1]->getString().compare(g_Step)!=0))
				{
				osErrReport << "<Error*> RK4VS solver defintion needs a '"<<g_Step <<"' statement.\n";
				SYMERRORTOK2("RK4VS solver defintion needs a further statement: ",g_Step,errSyntax,vExpLine[iLeft+1]);
				return false;
				}

		if (!vExpLine[iLeft+2]->IsOfType(ctNumber))
				{
				osErrReport << "<Error*> RK4VS solver step a step size.\n";
				SYMERRORTOK("RK4VS solver step needs a step size",errSyntax,vExpLine[iLeft+2]);
				return false;
				}

		if (vExpLine[iLeft+2]->getNumber()<=0)
				{
				osErrReport << "<Error*> RK4VS solver step needs to be greater than zero .\n";
				SYMERRORTOK("RK4VS solver step needs to be greater than zero",errSyntax,vExpLine[iLeft+2]);
				return false;
				}

		}

/* Don't believe this is necessary as has already been identified in class factory
	if (vExpLine[iLeft]->getString().compare(g_RK4VS)==0)
		return true;

	return false;*/
	return true;
}

/*

///////////////////////////////////////////////////////////
// Function name	: CSolRK4VS::setup
// Description	    : 
// Return type		: bool 
// Argument         : CIModelSim* pims
///////////////////////////////////////////////////////////
bool CSolRK4VS::setup(CIModelSim* pims)
{

	ASSERT2(pims);
	
	if (!m_SolRK4.setup(pims))
			return false;



	if ((!pims)||(!pims->isReady())) // will be checked by m_SOlRK4 - but repeat here to avoid hidden dependecies
			return false;

	pims->getModelIndexs(m_iIndVar,m_iDerivStart,m_iDerivEnd,m_iVarStart,m_iVarEnd);

	ASSERT2((m_iDerivEnd-m_iDerivStart)==(m_iVarEnd-m_iVarStart));

	if ((m_iDerivEnd-m_iDerivStart)!=(m_iVarEnd-m_iVarStart))
				return false;
	m_iSize = m_iVarEnd-m_iVarStart;

	// let get ready for solving

	m_startpos.resize(m_iSize,0); // as has already been ensure iSize==m_iVarEnd-m_iVarStart
	m_vecLargerJump.resize(pims->getModelSize(),0); // assumes order of variables
    m_vecSmallerJump.resize(pims->getModelSize(),0); // assumes order of variables
	m_vecErrors.resize(m_iSize,0);
	m_pIModelSim=pims;

	return true;
}


///////////////////////////////////////////////////////////
// Function name	: CSolRK4VS::step
// Description	    : 
// Return type		: xt_value 
// Argument         : vectorValues* pvecValues
// Argument         : vectorConstrainedValues* pvecConST
///////////////////////////////////////////////////////////
xt_value CSolRK4VS::step(vectorValues* pvecValues,vectorConstrainedValues* pvecConST )
{

	xt_value xtvJ1,xtvJ2,xtTemp,xtError;
	long iV;


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


	do
	{

		xtvJ1 = m_tstep/static_cast<xt_value>(2);
		xtvJ2 = m_tstep - xtvJ1; // to catch any numerical rouding stuff

		ASSERT2((xtvJ1+xtvJ2)==m_tstep);



		ASSERT2(pvecValues->size()==m_vecLargerJump.size());
		ASSERT2(pvecValues->size()==m_vecSmallerJump.size());
		copy(pvecValues->begin(),pvecValues->end(),m_vecLargerJump.begin());
		copy(pvecValues->begin(),pvecValues->end(),m_vecSmallerJump.begin());

		//calc larger jump - to go into another thread latter
		{
		 m_SolRK4.setIndVarStep(m_tstep);
		 m_SolRK4.step(&m_vecLargerJump,pvecConST);

		}

		
		// calc smaller steps
		{
		 m_SolRK4.setIndVarStep(xtvJ1);
		 m_SolRK4.step(&m_vecSmallerJump,pvecConST);
		 m_SolRK4.setIndVarStep(xtvJ2);
		 m_SolRK4.step(&m_vecSmallerJump,pvecConST);

		}

		m_vError = 0;
		#ifndef NDEBUG
		xtError = 0;// not needed - but make debuging easier
		#endif
		// find largest error
		for(long iC=m_iVarStart;iC<(m_iSize+m_iVarStart);iC++)
			{
			iV = iC-m_iVarStart;
			m_vecErrors[iV] = (m_vecSmallerJump[iC] - m_vecLargerJump[iC]);
			m_vecSmallerJump[iC] += m_vecErrors[iV]/static_cast<xt_value>(15); // adding correction

			// Find largest relative error - ignoring cases where the value is close to zero
			if (fabs(m_vecSmallerJump[iC])>DEFAULT_SMALL_NUMBER)
					{
					xtError = fabs(m_vecErrors[iV]/m_vecSmallerJump[iC]);
					if (xtError>m_vError)
							m_vError = xtError;
					}

			}

		// calculate new time step indicated
		if ((m_vError>DEFAULT_SMALL_NUMBER)||(m_vError>m_vTolerance))
					m_tstep *= m_vTolerance/m_vError;
					else
					if (m_tstep!=m_tmax)
						{
						m_tstep *=2;
						if (m_tstep>m_tmax)
							m_tstep=m_tmax;
						}

	}
	while (m_vError>m_vTolerance); 


#ifdef EXTRADEBUG
	cout << "m_vError = "<<m_vError<<", m_vTolerance = "<<m_vTolerance<<", m_tstep = "<<m_tstep<<endl;
	
#endif

	// update new values
	copy(m_vecSmallerJump.begin(),m_vecSmallerJump.end(),pvecValues->begin());


	if (m_bOverRideNext)
		{
		m_tstep = xtTemp;
		m_bOverRideNext = false;
		}

	return (*pvecValues)[m_iIndVar];
}
*/