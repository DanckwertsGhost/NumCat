// VarExp.h: interface for the CVarExp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VAREXP_H__F84FAAB8_FB1C_4030_9DB4_46D02DF9F9F7__INCLUDED_)
#define AFX_VAREXP_H__F84FAAB8_FB1C_4030_9DB4_46D02DF9F9F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VarExpression.h"
#include "VarMultiVarExpression.h"
#include <math.h>

class CVarExpAdd : public CVarExpression  
{
public:
	CVarExpAdd(CVarRoot* pvrLeft, CVarRoot* pvrRight,bool bDestroyPVRs=false):CVarExpression(bDestroyPVRs){setupExp(pvrLeft,pvrRight);}
	CVarExpAdd(CVarRoot& pvrLeft, CVarRoot& pvrRight):CVarExpression(){setupExp(&pvrLeft,&pvrRight);}
	virtual ~CVarExpAdd(){}

protected:
	virtual xt_value getNewValue( const vectorValues& vec ) { return m_pvrLeft->getValue(vec) + m_pvrRight->getValue(vec); }

};


class CVarExpMinus : public CVarExpression  
{
public:
	CVarExpMinus(CVarRoot* pvrLeft, CVarRoot* pvrRight,bool bDestroyPVRs=false):CVarExpression(bDestroyPVRs){setupExp(pvrLeft,pvrRight);}
	CVarExpMinus(CVarRoot& pvrLeft, CVarRoot& pvrRight){setupExp(&pvrLeft,&pvrRight);}
	virtual ~CVarExpMinus(){}

protected:
#ifndef DEBUGVARS
	virtual xt_value getNewValue( const vectorValues& vec ) { return m_pvrLeft->getValue(vec) - m_pvrRight->getValue(vec); }
#else
	virtual xt_value getNewValue( const vectorValues& vec );// { return m_pvrLeft->getValue(vec) - m_pvrRight->getValue(vec); }
#endif
};


class CVarExpMulti : public CVarExpression  
{
public:
	CVarExpMulti(CVarRoot* pvrLeft, CVarRoot* pvrRight,bool bDestroyPVRs=false):CVarExpression(bDestroyPVRs){setupExp(pvrLeft,pvrRight);}
	CVarExpMulti(CVarRoot& pvrLeft, CVarRoot& pvrRight){setupExp(&pvrLeft,&pvrRight);}
	virtual ~CVarExpMulti(){}

protected:
	virtual xt_value getNewValue( const vectorValues& vec ) { return m_pvrLeft->getValue(vec) * m_pvrRight->getValue(vec); }

};


class CVarExpDiv : public CVarExpression  
{
public:
	CVarExpDiv(CVarRoot* pvrLeft, CVarRoot* pvrRight,bool bDestroyPVRs=false):CVarExpression(bDestroyPVRs){setupExp(pvrLeft,pvrRight);}
	CVarExpDiv(CVarRoot& pvrLeft, CVarRoot& pvrRight){setupExp(&pvrLeft,&pvrRight);}
	virtual ~CVarExpDiv(){}

protected:
	virtual xt_value getNewValue( const vectorValues& vec );

};

class CVarExpPow : public CVarExpression  
{
public:
	CVarExpPow(CVarRoot* pvrLeft, CVarRoot* pvrRight,bool bDestroyPVRs=false):CVarExpression(bDestroyPVRs){setupExp(pvrLeft,pvrRight);}
	CVarExpPow(CVarRoot& pvrLeft, CVarRoot& pvrRight){setupExp(&pvrLeft,&pvrRight);}
	virtual ~CVarExpPow(){}

protected:
	virtual xt_value getNewValue( const vectorValues& vec ) { return pow(double(m_pvrLeft->getValue(vec)), double(m_pvrRight->getValue(vec))); }

};

/*

class CVarExpLn : public CVarExpression  
{
public:
	CVarExpLn(CVarRoot* pvrLeft,bool bDestroyPVRs=false):CVarExpression(bDestroyPVRs){setupExp(pvrLeft,NULL);}
	CVarExpLn(CVarRoot& pvrLeft){setupExp(&pvrLeft,NULL);}
	virtual ~CVarExpLn(){}

protected:
	virtual xt_value getNewValue( const vectorValues& vec ) { return log(double(m_pvrLeft->getValue(vec))); }

};

class CVarExpExp : public CVarExpression  
{
public:
	CVarExpExp(CVarRoot* pvrLeft,bool bDestroyPVRs=false):CVarExpression(bDestroyPVRs){setupExp(pvrLeft,NULL);}
	CVarExpExp(CVarRoot& pvrLeft){setupExp(&pvrLeft,NULL);}
	virtual ~CVarExpExp(){}

protected:
	virtual xt_value getNewValue( const vectorValues& vec ) { return exp(double(m_pvrLeft->getValue(vec))); }

};*/


// MACRO to add math function class variables - these are C run time functions and all require double types regardless of xt_value defn.

#define CVARFUNC(name,type) class name : public CVarExpression { \
public: \
		name(CVarRoot* pvrLeft,bool bDestroyPVRs=false):CVarExpression(bDestroyPVRs){setupExp(pvrLeft,NULL);} \
		name(CVarRoot& pvrLeft){setupExp(&pvrLeft,NULL);} \
		virtual ~name(){} \
protected: \
		   virtual xt_value getNewValue( const vectorValues& vec ) { return type(double(m_pvrLeft->getValue(vec))); } \
}

// Implementation of math single parameter functions

CVARFUNC(CVarExpLog,log10);
CVARFUNC(CVarExpLn,log);
CVARFUNC(CVarExpSin,sin);
CVARFUNC(CVarExpCos,cos);
CVARFUNC(CVarExpTan,tan);
CVARFUNC(CVarExpASin,asin);
CVARFUNC(CVarExpACos,acos);
CVARFUNC(CVarExpATan,atan);
CVARFUNC(CVarExpAbs,abs);
CVARFUNC(CVarExpExp,exp);

class CVarExpInteger : public CVarExpression  
{
public:
	CVarExpInteger(CVarRoot* pvrLeft,bool bDestroyPVRs=false):CVarExpression(bDestroyPVRs){setupExp(pvrLeft,NULL);}
	CVarExpInteger(CVarRoot& pvrLeft){setupExp(&pvrLeft,NULL);}
	virtual ~CVarExpInteger(){}

protected:
	virtual xt_value getNewValue( const vectorValues& vec ) { return long(m_pvrLeft->getValue(vec)+1E-05); }

};

class CVarExpIntegerUp : public CVarExpression  
{
public:
	CVarExpIntegerUp(CVarRoot* pvrLeft,bool bDestroyPVRs=false):CVarExpression(bDestroyPVRs){setupExp(pvrLeft,NULL);}
	CVarExpIntegerUp(CVarRoot& pvrLeft){setupExp(&pvrLeft,NULL);}
	virtual ~CVarExpIntegerUp(){}

protected:
	virtual xt_value getNewValue( const vectorValues& vec ) { return long((m_pvrLeft->getValue(vec)+0.5)); }

};


class CVarExpNeg : public CVarExpression  
{
public:
	CVarExpNeg(CVarRoot* pvrLeft,bool bDestroyPVRs=false):CVarExpression(bDestroyPVRs){setupExp(pvrLeft,NULL);}
	CVarExpNeg(CVarRoot& pvrLeft){setupExp(&pvrLeft,NULL);}
	virtual ~CVarExpNeg(){}

protected:
	virtual xt_value getNewValue( const vectorValues& vec ) { return m_pvrLeft->getValue(vec)*(-1); }

};



class CVarExpGT : public CVarExpression  
{
public:
	CVarExpGT(CVarRoot* pvrLeft, CVarRoot* pvrRight,bool bDestroyPVRs=false):CVarExpression(bDestroyPVRs){setupExp(pvrLeft,pvrRight);}
	CVarExpGT(CVarRoot& pvrLeft, CVarRoot& pvrRight):CVarExpression(){setupExp(&pvrLeft,&pvrRight);}
	virtual ~CVarExpGT(){}

protected:
#ifdef DEBUGVARS
	virtual xt_value getNewValue( const vectorValues& vec );// { return (m_pvrLeft->getValue(vec) > m_pvrRight->getValue(vec)); }
#else
	virtual xt_value getNewValue( const vectorValues& vec ) { return (m_pvrLeft->getValue(vec) > m_pvrRight->getValue(vec)); }
#endif
};

class CVarExpLT : public CVarExpression  
{
public:
	CVarExpLT(CVarRoot* pvrLeft, CVarRoot* pvrRight,bool bDestroyPVRs=false):CVarExpression(bDestroyPVRs){setupExp(pvrLeft,pvrRight);}
	CVarExpLT(CVarRoot& pvrLeft, CVarRoot& pvrRight):CVarExpression(){setupExp(&pvrLeft,&pvrRight);}
	virtual ~CVarExpLT(){}

protected:
	virtual xt_value getNewValue( const vectorValues& vec ) { return (m_pvrLeft->getValue(vec) < m_pvrRight->getValue(vec)); }

};

/*
class CVarExpIntgrate : public CVarExpression  
{
	DO MORE HERE

		Have memory of last value returned and time last to get time step ( maybe don't want this calculated every time - perhaps an special type of variable
		or 
		This class needs to know about the time variable's location - maybe should be achieved with a compile flag ? 
	
		The problem is this is just as time dependant as the differentaite variables.
	
	
public:
	CVarExpIntgrate(CVarRoot* pvrLeft,bool bDestroyPVRs=false):CVarExpression(bDestroyPVRs){setupExp(pvrLeft,NULL);}
	CVarExpIntgrate(CVarRoot& pvrLeft){setupExp(&pvrLeft,NULL);}
	virtual ~CVarExpIntgrate(){}

protected:
	virtual xt_value getNewValue( const vectorValues& vec ) { return m_pvrLeft->getValue(vec)*(-1); }

	xt_value m_xtLastTime;
	xt_value m_xtLastPoint;
};*/

#endif // !defined(AFX_VAREXP_H__F84FAAB8_FB1C_4030_9DB4_46D02DF9F9F7__INCLUDED_)
