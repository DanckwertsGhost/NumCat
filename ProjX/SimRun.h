// SimRun.h: interface for the CSimRun class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIMRUN_H__6C9238A5_03AC_4B08_A662_5C8E37BB8A00__INCLUDED_)
#define AFX_SIMRUN_H__6C9238A5_03AC_4B08_A662_5C8E37BB8A00__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IModelSim.h"
#include "Solver.h"
#include "global.h"


class CIDataServicesCallBack
{
public:
	CIDataServicesCallBack(){}
	virtual ~CIDataServicesCallBack(){}
	virtual void startDataServices(){}
	virtual void endDataServices(){}
};


class CSimRun  
{
public:
	CSimRun(CIModelSim* im, CSolver* sol);
	virtual ~CSimRun();
	bool runSimulation(CIDataServicesCallBack& iCallServBack, variable tCutOff=10000); // need to give a default
private:
	CIModelSim* m_pIModel;
	CSolver* m_pSolver;

};

#endif // !defined(AFX_SIMRUN_H__6C9238A5_03AC_4B08_A662_5C8E37BB8A00__INCLUDED_)
