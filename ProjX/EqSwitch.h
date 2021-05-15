// EqSwitch.h: interface for the CEqSwitch class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EQSWITCH_H__A6884644_A4AA_4090_A099_75AA52B5C2FA__INCLUDED_)
#define AFX_EQSWITCH_H__A6884644_A4AA_4090_A099_75AA52B5C2FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Equation.h"

class CEqSwitch : public CEquation  
{
public:
	CEqSwitch();
	CEqSwitch(const CEqSwitch& CE);
	CEqSwitch(long iLeft,long iRight,vector<CToken*>& vExpLine, ostream& osErrReport=cerr);
	virtual ~CEqSwitch();

	static bool IsWellFormedSwitchEquation(long iLeft,long iRight,vector<CToken*>& vExpLine, ostream& osErrReport);

	virtual bool setupExpression(list<CEquation*>* pvecpEquations, CVarClassFactory* pvcf, ostream& osErrReport=cerr);
	virtual variable updateValue(vector< variable >* pvecVar);
	virtual variable evaluate(vector<variable>* pvecV);
	virtual bool checkAllRHSDefined(const set<CToken* > setDef, bool bReport=false, ostream& oserr=cerr ) const;
	virtual void setStrongType(const vector< varStrongType >& vecst);

	virtual bool checkImpliedArrays(CArrayFactory* pAF);
	virtual bool createImpliedArray( CArrayFactory* pAF );
	virtual long expandArrayEquations( list<CToken>& ltToks, vector<CEquation*>& rvecNewEqs, SetPtCTokenStringSearch& rsetPtToksUnique ) const;
	virtual bool postCreationCheck(CArrayFactory* pAF); // implement if equation type needs more checks
	virtual bool setArrayIndex(long iIndex, list<CToken>& ltToks, SetPtCTokenStringSearch& rsetPtToksUnique);
	virtual bool expandArrayFunctions(list<CToken>& rLToks, SetPtCTokenStringSearch& rSetUnique); // check the state then expand

	#ifndef NDEBUG
	virtual void sentToAtlTrace() const;
	#endif


protected:
	virtual void sendtostream(ostream& os) const;
	static long findStartNextLine(long iStart, vector<CToken*>& vExpLine);
	virtual variable getValue(vector<variable>* pvecV);	
	void copy(const CEqSwitch& CE);


	vector< CVarRoot* > m_vpcvrRight;
	vector< CVarRoot* > m_vpcvrCondition;
	vector< vector< CToken* > > m_vvpctRight;
	vector< vector< CToken* > > m_vpctCondition;


};

#endif // !defined(AFX_EQSWITCH_H__A6884644_A4AA_4090_A099_75AA52B5C2FA__INCLUDED_)
