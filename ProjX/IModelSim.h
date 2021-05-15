// IModelSim.h: interface for the IModelSim class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMODELSIM_H__C36A01BF_FDD9_46B7_95E5_280213207D9B__INCLUDED_)
#define AFX_IMODELSIM_H__C36A01BF_FDD9_46B7_95E5_280213207D9B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VarRoot.h"

//#define EQSTOPOPTION

/* Interface for Allowing for equation information to pass to a standard
   model and solver.
*/
class CIEquaSim
{
public:
	virtual xt_value updateValue(vectorValues* /*pvecVar*/)=0;
	virtual void setStrongType(const vector< varStrongType >& /*vecst*/)=0;
#ifdef EQSTOPOPTION
	virtual void reset()=0;
	virtual bool simulationStop() const =0;
#endif

};

/*  Interface for holding model information to pass to a standard solver.
	Reason for the interface 
*/
class CIModelSim  
{
public:

	virtual bool getModelIndexs(long& /*iIndVar*/, long& /*iDeriveStart*/, long& /*iDerivEnd*/,long& /*iVarStart*/, long& /*iVarEnd*/)=0;
	virtual void push_back(CIEquaSim* /*es*/)=0;
	virtual bool isReady()=0; // allows for a check if necessary
	virtual bool updateValue(vectorValues* /*vecValues*/)=0;
	virtual long getModelSize() const =0;
	virtual bool prepareSimulation(vectorValues* /*pvecValues*/)=0;
	virtual bool checkEvents(vectorValues* /*pvecValues*/,vectorValues* /*pvecValuesLast*/ )=0;
	virtual long getIndIndex()=0;
	virtual vector< varStrongType >* getpVecStrongTypes()=0;
	virtual bool ensureEventsSync(vectorValues* /*pvecValues*/, variable& /*vTimeStep*/ )=0;
	virtual bool getMaxSolverStep(xt_value& xtMax)=0;
	virtual void signalEndSimulation(vectorValues& rVecVals)=0;

};

class CExceptionSimulation
{
public:
	CExceptionSimulation(const char* sStr):m_xtvL(xtv_NotSet),m_xtvR(xtv_NotSet)
	{strcpy(m_sHeading,"CExceptionSimulation : ");strcpy(m_sMessage,sStr);}
	CExceptionSimulation(const char* sStr, const xt_value xtvL, const xt_value xtvR):m_xtvL(xtvL),m_xtvR(xtvR)
	{strcpy(m_sHeading,"CExceptionSimulation : ");strcpy(m_sMessage,sStr);}
	CExceptionSimulation(const char* sStr, const xt_value xtvL):m_xtvL(xtvL),m_xtvR(xtv_NotSet)
	{strcpy(m_sHeading,"CExceptionSimulation : ");strcpy(m_sMessage,sStr);}

	friend ostream& operator << (ostream& os, CExceptionSimulation& Except)
	{ os << Except.m_sHeading << Except.m_sMessage <<" ";Except.outNums(os); os.flush(); return os;}
protected:
	void outNums(ostream& os)
	{
	if (m_xtvL==xtv_NotSet)
				return;
	os << "( " << m_xtvL;
	if (m_xtvR!=xtv_NotSet)
			os << " , " << m_xtvR;
	os << " )";
	return;
	}	


	char m_sMessage[500];
	char m_sHeading[25];
	xt_value m_xtvL;
	xt_value m_xtvR;


};

#endif // !defined(AFX_IMODELSIM_H__C36A01BF_FDD9_46B7_95E5_280213207D9B__INCLUDED_)
