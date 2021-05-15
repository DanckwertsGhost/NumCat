// SolRK4VS.h: interface for the CSolRK4VS class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOLRK4VS_H__4FB5EEBD_8804_4AE4_A511_CDD7C1D5CCA8__INCLUDED_)
#define AFX_SOLRK4VS_H__4FB5EEBD_8804_4AE4_A511_CDD7C1D5CCA8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SolRK4.h"
#include "Token.h"
#include "Equation.h"
#include <fstream>
#include <vector>

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

using namespace std;


#define POGO_START 101

template <class S, class T=CSolRK4>
class CSolVS: 
	public CSolver, 
	public CNavTokens  
{
public:

	CSolVS():CSolver(),m_Sol(),m_xtOverRide(DEFAULT_TIME_STEP),m_vTolerance(DEFAULT_TOLERANCE_STEP),m_bOverRideNext(false),m_iPogo(0),m_iPogoLast(POGO_START)
	{
		m_bState=true; // as defining with default values
		m_vTolerance90 = m_vTolerance/0.9F;
		m_vTolerance10 = m_vTolerance/0.4F;

	}

	CSolVS(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport ):
	CSolver(),m_Sol(),m_xtOverRide(DEFAULT_TIME_STEP),m_vTolerance(DEFAULT_TOLERANCE_STEP),m_bOverRideNext(false),m_iPogo(0),m_iPogoLast(POGO_START)
	{

		m_bState = S::check(iLeft,iRight,vExpLine,osErrReport);

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
		m_vTolerance90 = m_vTolerance/0.9F;
		m_vTolerance10 = m_vTolerance/0.1F;

	}


	virtual ~CSolVS(){}

// start CSolver interface
	virtual bool setup(CIModelSim* pims)
	{

		ASSERT2(pims);
		
		if (!m_Sol.setup(pims))
				return false;



		if ((!pims)||(!pims->isReady())) // will be checked by m_Sol - but repeat here to avoid hidden dependecies
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

	virtual xt_value step(vectorValues* pvecValues,vectorConstrainedValues* pvecConST )
	{

		xt_value xtvJ1,xtvJ2,xtTemp,xtError;
		long iV;
		bool bDidNotDropStep=true;


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
			 m_Sol.setIndVarStep(m_tstep);
			 m_Sol.step(&m_vecLargerJump,pvecConST);

			}

			
			// calc smaller steps
			{
			 m_Sol.setIndVarStep(xtvJ1);
			 m_Sol.step(&m_vecSmallerJump,pvecConST);
			 m_Sol.setIndVarStep(xtvJ2);
			 m_Sol.step(&m_vecSmallerJump,pvecConST);

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
						{
						bDidNotDropStep=false;
						m_tstep *= m_vTolerance/m_vError;
						}
						else
						if (m_tstep!=m_tmax)
							{
							m_tstep *=static_cast<xt_value>(2.0);
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
			if (bDidNotDropStep)
					m_tstep = xtTemp;
			m_bOverRideNext = false;
			}

		return (*pvecValues)[m_iIndVar];
	}

	virtual xt_value nextIndVarStep() const{return m_tstep;}; // return predicted next time jump - in case over ride needed
	virtual void overrideNextIndVarStep(xt_value xtNextOnly){m_xtOverRide=(xtNextOnly>0)?xtNextOnly:m_tstep;m_bOverRideNext=true;};
	virtual bool isVariableStep(){ return true; }
// end CSolver interface

protected:

	T m_Sol;
	xt_value m_vError;
	xt_value m_vTolerance;
	xt_value m_vTolerance90; // 90% of tolerance
	xt_value m_vTolerance10; // 70% of tolerance
	long m_iPogo; // to spot rebounding 
	long m_iPogoLast;


	long m_iSize;
	bool m_bOverRideNext;
	xt_value m_xtOverRide;
	vectorValues m_startpos;
	vectorValues m_vecLargerJump;
	vectorValues m_vecSmallerJump;
	vectorValues m_vecErrors;

};



/*
class CSolRK4VS : 
	public CSolver, 
	public CNavTokens  
{

public:
	CSolRK4VS();
	CSolRK4VS(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport );
	virtual ~CSolRK4VS();
// start CSolver interface
	virtual bool setup(CIModelSim* pims);
	virtual xt_value step(vectorValues* pvecValues,vectorConstrainedValues* pvecConST );
	virtual xt_value nextIndVarStep() const{return m_tstep;}; // return predicted next time jump - in case over ride needed
	virtual void overrideNextIndVarStep(xt_value xtNextOnly){m_xtOverRide=(xtNextOnly>0)?xtNextOnly:m_tstep;m_bOverRideNext=true;};
	virtual bool isVariableStep(){ return true; }
// end CSolver interface
	static bool check(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport=cerr );

protected:

	CSolRK4 m_SolRK4;
	xt_value m_vError;
	xt_value m_vTolerance;


	long m_iSize;
	bool m_bOverRideNext;
	xt_value m_xtOverRide;
	vectorValues m_startpos;
	vectorValues m_vecLargerJump;
	vectorValues m_vecSmallerJump;
	vectorValues m_vecErrors;
};
*/
class CSolRK4VS : public CSolVS<CSolRK4VS,CSolRK4>
{
public:
	CSolRK4VS():CSolVS<CSolRK4VS,CSolRK4>(){}
	CSolRK4VS(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport ):CSolVS<CSolRK4VS,CSolRK4>(iLeft,iRight,vExpLine,osErrReport){}
	virtual ~CSolRK4VS(){}
	static bool check(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport=cerr );

};

#endif // !defined(AFX_SOLRK4VS_H__4FB5EEBD_8804_4AE4_A511_CDD7C1D5CCA8__INCLUDED_)
