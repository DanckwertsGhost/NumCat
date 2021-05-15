// SubExpression.h: interface for the CSubExpression class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SUBEXPRESSION_H__B32C9D5A_9323_4B1B_B858_3A35BD29AA9F__INCLUDED_)
#define AFX_SUBEXPRESSION_H__B32C9D5A_9323_4B1B_B858_3A35BD29AA9F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Token.h"
#include "VarRoot.h"
class CVarClassFactory; // declare
class CEquation; // declare

#include <vector>
#include <list>

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

using namespace std;

class CSubExpException
{
public:
	CSubExpException(const char* sHeading, const char* sMessage=NULL);
	~CSubExpException(){}

	ostream& out(ostream& os);
	const char* getMessage() const { return m_sMessage;}
	bool hasMessage() const { return m_sMessage!=NULL; }
	const char* getHeading() const { return m_sHeading;}
private:

	char m_sMessage[500];
	char m_sHeading[250];

};

class CSubExpression
{
public:
	CSubExpression(CToken* pct,list<CEquation*>* pvecpEquations, CVarClassFactory* pvcf);
//	CSubExpression(CVarRoot* pcvr);
	CSubExpression(CSubExpression* pcseLHS, CSubExpression* pcseMid, CSubExpression* pcseRHS, CVarClassFactory* pvcf);
	CSubExpression(CSubExpression* pcseLHS, CSubExpression* pcseRHS, CVarClassFactory* pvcf);
	CSubExpression(CSubExpression* pcseLHS, vector< CSubExpression* >& rvecRHS, CVarClassFactory* pvcf);
	CSubExpression(CSubExpression* pcseLHS, CSubExpression* pcseRHS, const char* pOp, CVarClassFactory* pcvf );
	CSubExpression(const CSubExpression& cse);


	bool operator < (const CSubExpression& cse){ return false; }

/*	CSubExpression& operator + (const CSubExpression& cse);
	CSubExpression& operator - (const CSubExpression& cse);
	CSubExpression& operator * (const CSubExpression& cse);
	CSubExpression& operator / (const CSubExpression& cse);
	CSubExpression& operator ^ (const CSubExpression& cse);*/
	CSubExpression& operator = (const CSubExpression& cse){ Copy(cse); return *this; }

	ostream& out(ostream& os) const;
	CToken* getToken() const;
	CVarRoot* getVarRoot() const;
	bool isTokenDelim() const;
	bool isNegativeValue() const { return m_bNegValue; }

	friend ostream& operator << (ostream& os, const CSubExpression cse){ return cse.out(os); }

	~CSubExpression();
private:
	void Copy(const CSubExpression& cse);
	bool isRootToken() const;


	bool m_bNegValue;
	CToken* m_pct;
	CVarRoot* m_pcvr;

};


#endif // !defined(AFX_SUBEXPRESSION_H__B32C9D5A_9323_4B1B_B858_3A35BD29AA9F__INCLUDED_)
