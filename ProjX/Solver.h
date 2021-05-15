// Solver.h: interface for the CSolver class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOLVER_H__14DA8F8C_490C_4BB2_81F2_CAEDEE812564__INCLUDED_)
#define AFX_SOLVER_H__14DA8F8C_490C_4BB2_81F2_CAEDEE812564__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VarRoot.h"
//#include "IModelSim.h"
class CIModelSim;

/*
class CExceptionCSolver
{
public:

	CExceptionCSolver(const char* sHeader, const char* sBody=NULL)
	{
	strcpy(m_sHeading,"Solver Exception : ");
	strcat(m_sHeading,sHeader);
	if (sBody)
		strcpy(m_sMessage,sBody);		
		else
		strcpy(m_sMessage,"");

	}

	friend ostream& operator << (ostream& os, CExceptionCSolver& Except)
	{ os << Except.m_sHeading <<" "<< Except.m_sMessage; os.flush(); return os;}
protected:

	char m_sMessage[500];
	char m_sHeading[25];

};
*/
class CSolver  
{
public:
	CSolver():m_pIModelSim(NULL),m_bState(false),m_tmax(1),m_tstep(DEFAULT_TIME_STEP){};
	virtual ~CSolver(){};
	virtual bool setup(CIModelSim* /*pims*/)=0;
	virtual void setIndVarStep(xt_value ivStep);
	virtual xt_value step(vectorValues* /*pvecValues*/,vectorConstrainedValues* /*pvecConST*/ )=0;
	virtual xt_value nextIndVarStep() const=0; // return predicted next time jump - in case over ride needed
	virtual void overrideNextIndVarStep(xt_value /*xtNextOnly*/) = 0;
	virtual bool isFormedOK(){ return m_bState; }
	virtual void setMaxStep(xt_value xt_max);
	virtual bool isVariableStep(){ return false; }
	virtual bool lessThanMinStep(xt_value xt_min){ return xt_min<MIN_TIME_STEP; }


protected:
	long m_iIndVar;
	long m_iDerivStart;
	long m_iDerivEnd;
	long m_iVarStart;
	long m_iVarEnd;
	bool m_bState; // is OK for solving
	CIModelSim* m_pIModelSim;
	xt_value m_tmax;
	xt_value m_tstep;
};

#endif // !defined(AFX_SOLVER_H__14DA8F8C_490C_4BB2_81F2_CAEDEE812564__INCLUDED_)
