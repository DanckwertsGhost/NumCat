// Model.h: interface for the CModel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MODEL_H__7E2D0F73_F4EA_41D2_B9B6_E2CF02CE5070__INCLUDED_)
#define AFX_MODEL_H__7E2D0F73_F4EA_41D2_B9B6_E2CF02CE5070__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include <list>

using namespace std;

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

#include "global.h"
#include "Token.h"
#include "Equation.h"
#include "EvValue.h"
#include "IModelSim.h"
#include "StrongTypeFactory.h"
#include "CritCheck.h"

#define vec_variables vector< variable >


enum eModelState{ eMSUnintialised, eMSInitIndexes,eMSInitEquations, eMSInitAll };
// CModel - holds the variables for calculating the simulation
// 
//
class CModel: public CIModelSim  
{
public:
	CModel();
	virtual ~CModel();

	virtual bool intialiseTokens(vector<CToken* >& vecIndVar,vector<CToken* >& vecDeriv, vector<CToken*>& vecDepVar,vector<CToken*>& vecSubsVar, CStrongTypeFactory* pstf );
	virtual bool intialiseEquations(list<CEquation*>* pvecpEquations);
	virtual bool intialiseEvents(vector<CEvent*>* pvecpEventss,list<CEquation*>* pvecpEquations);
    virtual	bool addUserRequestedEvents( vector<CEvent*>&  vecpEvents );

	bool TestModel(list<CEquation*>* pvecpEquations, vector<CEvent*>* pvecpEvents);
// start CIModelSim implementation
	virtual bool getModelIndexs(long& iIndVar, long& iDeriveStart, long& iDerivEnd,long& iVarStart, long& iVarEnd);
	virtual void push_back(CIEquaSim* es);
	virtual bool isReady(); // allows for a check if necessary
	virtual bool updateValue(vectorValues* vecValues );	
	virtual long getModelSize() const;	
	virtual bool prepareSimulation(vectorValues* pvecValues);
	virtual bool checkEvents(vectorValues* pvecValues,vectorValues* pvecValuesLast );
	#ifndef NDEBUG
	virtual long getIndIndex();
	#else
	virtual long getIndIndex(){return m_iTimeInd;}
	#endif
	virtual vector< varStrongType >* getpVecStrongTypes(){ return &m_vecStrongTypes; }
	virtual bool ensureEventsSync(vectorValues* pvecValues, variable& vTimeStep );
	virtual bool getMaxSolverStep(xt_value& xtMax);
	virtual void signalEndSimulation(vectorValues& rVecVals);
// end CIModelSim implementation

protected:
#ifdef EQSTOPOPTION
	virtual void prepareEquations(list<CEquation*>* pvecpEquations);
#endif
	eModelState m_eState;

// ++ Note declared in order of mangitude ie m_BeginDeriv > m_iBeginInd
	long m_iBeginInd;
	long m_iBeginDeriv;
	long m_iBeginDep;
	long m_iBeginSubs;
	long m_iEndIndex;
	long m_iTimeInd;

	// use refernces - pointed at other starts - to make code easier to read and understand
	long& m_iEndInd;
	long& m_iEndDeriv;
	long& m_iEndDep;
	long& m_iEndSubs;
// -- End of attributes declared in order
	vector< CIEquaSim* > m_vecES;
	vector< CIEquaSim* >::iterator m_itvecES;
	vector< CEvent*> m_vpEvents; // going to make a copy of this - to reduce dependancy
	vector< CEvent*> m_vpPreciseEvents; // links to events that need precise timing
	vector< CEvent*> m_vpTempEvents;
	vector< CEvent*> m_vpActiveEvents;
	vector< CEvent*> m_vpPassiveEvents;
	vector< CEvent*> m_vpLastEvents;

	vector< varStrongType > m_vecStrongTypes;

	CRITICAL_SECTION m_csUpdateValues;

};

#endif // !defined(AFX_MODEL_H__7E2D0F73_F4EA_41D2_B9B6_E2CF02CE5070__INCLUDED_)
