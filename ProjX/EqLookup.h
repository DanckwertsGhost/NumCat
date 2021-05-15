// EqLookup.h: interface for the CEqLookup class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EQLOOKUP_H__9B13BE64_0CDF_451C_A7A3_FA1838AF03AE__INCLUDED_)
#define AFX_EQLOOKUP_H__9B13BE64_0CDF_451C_A7A3_FA1838AF03AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Equation.h"
#include "csvHolder.h"
#include <vector>
#include <string>
#include "SymlixStore.h"

#pragma warning(disable:4786)

using namespace std;

class CEqLookup : public CEquation  
{
public:
	CEqLookup();
    CEqLookup(long iLeft,long iRight,vector<CToken*>& vExpLine, IARDataStore* pIStore, ostream& osErrReport);
	virtual ~CEqLookup();

	static bool IsWellFormedLookupEquation(long iLeft,long iRight,vector<CToken*>& vExpLine, IARDataStore* pIStore, ostream& osErrReport);

	virtual bool setupExpression(list<CEquation*>* pvecpEquations, CVarClassFactory* pvcf, ostream& osErrReport=cerr);
	virtual variable updateValue(vector< variable >* pvecVar);
	virtual variable evaluate(vector<variable>* pvecV);
	virtual bool isAFixedExpression(){ return false; }
	virtual void setStrongType(const vector< varStrongType >& vecst);

//	virtual bool checkImpliedArrays(CArrayFactory* pAF); - CEquation handles this OK for RHS
//	virtual bool createImpliedArray( CArrayFactory* pAF ) - CEquation handles this OK
	virtual long expandArrayEquations( list<CToken>& ltToks, vector<CEquation*>& rvecNewEqs, SetPtCTokenStringSearch& rsetPtToksUnique ) const;
//	virtual bool setArrayIndex(long iIndex, list<CToken>& ltToks, SetPtCTokenStringSearch& rsetPtToksUnique) - CEquation handles this OK
	virtual bool expandArrayFunctions(list<CToken>& rLToks, SetPtCTokenStringSearch& rSetUnique){ return true; } // as there's nothing to do
	#ifndef NDEBUG
	virtual void sentToAtlTrace() const;
	#endif

protected:
	virtual void sendtostream(ostream& os) const;
	virtual variable getValue(vector<variable>* pvecV);
	void copy(const CEqLookup& CE);

	CcsvHolder* m_pcsvLookup;
	vector< long > m_vRefInds;
//    string m_sGet;
	long m_iLookup;
	vector< long > m_vValueInds;
	string m_sFileName;
	bool m_bWarnOnce;
private:
	CEqLookup(const CEqLookup& ceql );


};

#endif // !defined(AFX_EQLOOKUP_H__9B13BE64_0CDF_451C_A7A3_FA1838AF03AE__INCLUDED_)
