// Equation.h: interface for the CEquation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EQUATION_H__72E84CE9_BD25_426A_9598_E078F260FACC__INCLUDED_)
#define AFX_EQUATION_H__72E84CE9_BD25_426A_9598_E078F260FACC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <assert.h>
#include "Token.h"
#include <vector>
#include <list>
#include <set>
#include <fstream>

using namespace std;

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

#include "global.h"
#include "VarClassFactory.h"
#include "IModelSim.h"
#include "ArrayFactory.h"

enum eEquationState{ceqUninitated,ceqError,ceqIntiated,ceqReadyToSolve};

class CSubExpression; // early declaration

/*
	CNavTokens
	A class to provide common Token vector navigation functions, as required.
	Class is stateless and all methods are static.
*/
class CNavTokens
{
	public:

	static vector<CToken*>::const_iterator getRightWithoutComments(long iLeft, long iRight, vector<CToken*>& vExpLine );
	static long getPosRightWithoutComments(long iLeft, long iRight, vector<CToken*>& vExpLine );
	static long getOneToRightOf( const char* sTerm, vector<CToken*>& vExpLine,long iStart, long iRight=NOT_DEFINED );
	static long find( const char* sTerm, vector<CToken*>& vExpLine,long iStart, long iRight=NOT_DEFINED );
};


/*
	CEquation:
	CEquation is a class for holding equation material in terms of pointers to CTokens.
	It does not manage the life cycle of the CTokens it holds pointers for and any change in the
	array of CTokens will render all CEquation object invalid. ** IMPORTANT **

*/
class CEquation: public CIEquaSim, public CNavTokens  
{
public:
	CEquation();
	CEquation(const CEquation& CE);
	CEquation(long iLeft,long iRight,vector<CToken*>& vExpLine, ostream& osErrReport=cerr);
	virtual ~CEquation();

	static bool IsWellFormedEquation(long iLeft,long iRight,vector<CToken*>& vExpLine, ostream& osErrReport);
	static bool IsWellFormedExpression(long iLeft,long iRight,vector<CToken*>& vExpLine, ostream& osErrReport, bool bArrayFuncs=false, bool bEqualsOK=false );
	static bool isDerivative(vector< CToken* >& vecLine, long lLeft, long lRight);
	static bool isDerivative(VectorLineTokenPts::iterator it);
	static CVarRoot* createExpression(long iLeft, long iRight, vector<CToken*>& vecTok, ostream& oserr, list<CEquation*>* pvecpEquations/*=NULL*/ );

//	virtual CEquation& operator = (const CEquation& CE){ copy(CE); return *this; }
	virtual bool isCorrect() const{	return m_eState!=ceqError;}
	virtual bool isReady() const{	return m_eState==ceqReadyToSolve;}
	virtual bool lhsIsDerivative();
	virtual bool lhsIsIterative(){ return ( m_pctLeft ? m_pctLeft->getString().isIterative() : false ); } 
	virtual CToken* getLHS(){return m_pctLeft->getRootTokenPt();} // assume LHS is only ever one token
	virtual string getUnderlyingLHSVarString() const;
	virtual bool checkAllRHSDefined(const set<CToken* > setDef, bool bReport=false, ostream& oserr=cerr ) const;

	virtual bool canEvaluate();
	virtual variable evaluate(vector<variable>* pvecV=NULL);
//	virtual variable evaluateRHS(){ assert(false); return NOT_DEFINED; } // TBI
	virtual bool isAFixedExpression(); // needs further work for complex fixed expressions eg 10*5

	virtual bool setupExpression(list<CEquation*>* pvecpEquations, CVarClassFactory* pvcf, ostream& osErrReport=cerr);
	virtual variable updateValue(vectorValues* pvecVar);
	virtual void setStrongType(const vector< varStrongType >& vecst);
	virtual bool checkImpliedArrays(CArrayFactory* pAF);
	virtual bool createImpliedArray( CArrayFactory* pAF );
	virtual bool hasExpandableArrays() const { return m_bHasArrays; }
	virtual long expandArrayEquations( list<CToken>& ltToks, vector<CEquation*>& rvecNewEqs, SetPtCTokenStringSearch& rsetPtToksUnique ) const;
	virtual bool postCreationCheck(CArrayFactory* pAF){ return true; } // implement if equation type needs more checks
	virtual bool setArrayIndex(long iIndex, list<CToken>& ltToks, SetPtCTokenStringSearch& rsetPtToksUnique);
	virtual bool expandArrayFunctions(list<CToken>& rLToks, SetPtCTokenStringSearch& rSetUnique); // check the state then expand
	virtual void setLHSArrayStatus(CArrayFactory* pAF);

#ifdef EQSTOPOPTION
	virtual void reset(){} // so history dependent equations can be reset
	static void setTimeData(const long iTime){ m_giIndexTime=iTime; }
	static void setStartTimeData(const xt_value xtStart){ m_gxtTimeStart=xtStart; }
	virtual bool simulationStop() const { return m_gStopCallFromEqs; }
	static void resetSimulationStop(){ m_gStopCallFromEqs=false; }
#endif

	bool operator() (const CEquation& ce1, const CEquation&ce2) const;
	bool operator> (const CEquation& ce) const;

	#ifdef NDEBUG
	inline void sentToAtlTrace() const {}
	#else
	virtual void sentToAtlTrace() const;
	#endif

	// need to add metods for getting and checking states
	friend ostream& operator << (ostream& os,  const CEquation& cT){ cT.sendtostream(os); return os; }

protected:

//	virtual CVarRoot* processSubExpression( vector< CToken* >::iterator itbegin, vector< CToken* >::iterator itend);
#ifdef EQSTOPOPTION
	static bool m_gStopCallFromEqs;
	static xt_value m_gxtTimeStart;
	static long m_giIndexTime;
#endif // #ifdef EQSTOPOPTION

	static void cleanupInstance();
	void createPlusToken();

	virtual void sendtostream(ostream& os) const;
	virtual void startCheckArrayFunc(){ m_iAFBrackets=0; m_iAFCode=0; }
	virtual void checkArrayFunc( CToken* pct );
	virtual bool expandArrayFunctionsForRHS(list<CToken>& rLToks, vector< CToken* >& rvpTokRHS, SetPtCTokenStringSearch& rSetUnique ); // check the state then expand


	long m_iAFBrackets;
	long m_iAFCode;
//	static vector<CToken*>::const_iterator getRightWithoutComments(long iLeft, long iRight, vector<CToken*>& vExpLine );
	void copy(const CEquation& CE);

	eEquationState m_eState;
 
	CToken* m_pctLeft;
	CToken* m_pctAssign;
	vector< CToken* > m_vpctRight;

	CVarClassFactory* m_pVarClassFactory;
	CVarRoot* m_pvrRight;
	long m_iIndex; // index of variable - set during setup
	varStrongType m_vResult;
	bool m_bHasArrays;
	bool m_bHasArrayFunc;
	static CToken* ms_ptPlus;

private:
	static string getVariableFromDerivative(const string& sDerv);
	static bool isNegativeVarVal(vector< CToken* >::const_iterator it, const vector< CToken* >& vpct);

	static vector<CSubExpression>::iterator find(const char* sPhrase, vector<CSubExpression>::iterator itseLeft, vector<CSubExpression>::iterator itseRight);
	static bool swapTwoForOne(vector<CSubExpression>& vecExp, vector<CSubExpression>::iterator itse, CVarClassFactory* pvcf);
	static bool swapThreeForOne(vector<CSubExpression>& vecExp, vector<CSubExpression>::iterator itse, CVarClassFactory* pvcf);
	static bool swapManyForOne(vector<CSubExpression>& vecExp, vector<CSubExpression>::iterator itse, vector< CSubExpression* >& rvecpExp, CVarClassFactory* pvcf );
    static bool swapAddTwo(vector<CSubExpression>& vecExp,vector<CSubExpression>::iterator itseBefore,vector<CSubExpression>::iterator itseNegNum,CVarClassFactory* pvcf);

	bool greaterThan(const CEquation& CE) const;


};

#endif // !defined(AFX_EQUATION_H__72E84CE9_BD25_426A_9598_E078F260FACC__INCLUDED_)
