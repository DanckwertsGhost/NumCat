// EqIterative.h: interface for the CEqIterative class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EQITERATIVE_H__D0F97C21_F828_489D_B5B6_0B0BD3A0B113__INCLUDED_)
#define AFX_EQITERATIVE_H__D0F97C21_F828_489D_B5B6_0B0BD3A0B113__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Equation.h"
#include <vector>

#pragma warning(disable:4786)

using namespace std;

#ifdef EQSTOPOPTION

class CEqIterative : public CEquation  
{
public:
	//CEqIterative();
	CEqIterative(long iLeft,long iRight,vector<CToken*>& vExpLine, ostream& osErrReport=cerr);
	virtual ~CEqIterative();

	static bool IsWellFormedIterativeEquation(long iLeft,long iRight,vector<CToken*>& vExpLine, ostream& osErrReport);

	virtual bool setupExpression(list<CEquation*>* pvecpEquations, CVarClassFactory* pvcf, ostream& osErrReport=cerr);
	virtual variable updateValue(vector< variable >* pvecVar);
	virtual variable evaluate(vector<variable>* pvecV);

	virtual bool isAFixedExpression(){ return false; }
	virtual void setStrongType(const vector< varStrongType >& vecst);


	virtual bool checkAllRHSDefined(const set<CToken* > setDef, bool bReport=false, ostream& oserr=cerr ) const { return true; } // always true

	virtual void reset();

protected:
	bool m_bEqualFormat;
	xt_value m_xtTime;

	virtual variable getValue(vector<variable>* pvecV);

	class CEI_Counter
	{
		public:
		CEI_Counter(){}
		virtual ~CEI_Counter(){}
		virtual bool first() =0;
		virtual variable value() =0;
		virtual bool next() =0;
		virtual void reset(){ first(); }
		virtual long size(){ return NOT_DEFINED; }
		virtual bool isLast() =0;
	};

	class CEI_FromTo: public CEI_Counter
	{
	public:
		CEI_FromTo( variable vFrom, variable vTo, variable vStep ):m_vFrom(vFrom),m_vCurrent(vFrom),m_vTo(vTo),m_vStep(vStep){m_bNegSlope =(m_vTo<m_vFrom);}
		virtual ~CEI_FromTo(){}
		virtual bool first(){ m_vCurrent=m_vFrom; return test(m_vCurrent); }
		virtual bool next(){ m_vCurrent+=m_vStep; return test(m_vCurrent); }
		virtual variable value(){ return m_vCurrent; }
		virtual bool isLast(){ return test(m_vCurrent+m_vStep); }
	private:
		bool test(const vVal ){ if (m_bNegSlope)
								 return vVal>=m_vTo;
								return vVal<=m_vTo;}
		variable m_vFrom;
		variable m_vTo;
		variable m_vStep;
		variable m_vCurrent;
		bool m_bNegSlope;
	};

	class CEI_Sequence: public CEI_Counter
	{
	public:
		CEI_Sequence( vector< variable >& rvec ):m_iCount(0){ m_vecVals = rvec; m_iSize = m_vecVals.size(); }
		virtual ~CEI_Sequence(){}
		virtual bool first(){ m_iCount=0; return m_iCount<m_iSize; }
		virtual bool next(){ return (++m_iCount)<m_iSize; }
		virtual variable value(){ if (m_iCount<m_iSize) 
										return m_vecVals[m_iCount];
										else
										return NOT_DEFINED; }
		virtual bool isLast(){ return (m_iCount+1>=m_iSize); }
	private:
		vector< variable > m_vecVals;
		long m_iSize;
		long m_iCount;

	};


	CEI_Counter* m_pCounter;

/*	CEqLookup();
    CEqLookup(long iLeft,long iRight,vector<CToken*>& vExpLine, IARDataStore* pIStore, ostream& osErrReport);
	virtual ~CEqLookup();

	static bool IsWellFormedLookupEquation(long iLeft,long iRight,vector<CToken*>& vExpLine, IARDataStore* pIStore, ostream& osErrReport);

	virtual bool setupExpression(list<CEquation*>* pvecpEquations, CVarClassFactory* pvcf, ostream& osErrReport=cerr);
	virtual variable updateValue(vector< variable >* pvecVar);
	virtual variable evaluate(vector<variable>* pvecV);
	virtual bool isAFixedExpression(){ return false; }
	virtual void setStrongType(const vector< varStrongType >& vecst);

protected:
	virtual void sendtostream(ostream& os) const;
	virtual variable getValue(vector<variable>* pvecV);

	CcsvHolder* m_pcsvLookup;
	vector< long > m_vRefInds;
//    string m_sGet;
	long m_iLookup;
	vector< long > m_vValueInds;
	string m_sFileName;*/
};
#endif //#ifdef EQSTOPOPTION

#endif // !defined(AFX_EQITERATIVE_H__D0F97C21_F828_489D_B5B6_0B0BD3A0B113__INCLUDED_)
