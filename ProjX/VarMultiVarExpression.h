// VarMultiVarExpression.h: interface for the CVarMultiVarExpression class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VARMULTIVAREXPRESSION_H__8658E73A_A644_4DE8_AEDE_B244200ECF9A__INCLUDED_)
#define AFX_VARMULTIVAREXPRESSION_H__8658E73A_A644_4DE8_AEDE_B244200ECF9A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VarExpression.h"



class CVarMultiVarExpression : public CVarExpression  
{
public:
	CVarMultiVarExpression(bool bDestroyPVRs=false );
	virtual ~CVarMultiVarExpression();
protected:

	virtual void setupMultiExp(vector< CVarRoot* >& rvecPVR ){m_vecPVR = rvecPVR;}
	vector< CVarRoot* > m_vecPVR;
	vector< CVarRoot* >::iterator m_itVP;
};


class CVarArraySum : public CVarMultiVarExpression
{
public:
	CVarArraySum( vector< CVarRoot* >& rvecPVR, bool bDestroyPVRs=false ):CVarMultiVarExpression(bDestroyPVRs)
		{ setupMultiExp(rvecPVR); }
	virtual ~CVarArraySum(){}
protected:
	virtual xt_value getNewValue( const vectorValues& vec )
		{
		 xt_value xtResult=0;
		 for (m_itVP=m_vecPVR.begin();m_itVP!=m_vecPVR.end();m_itVP++)
			xtResult += (*m_itVP)->getValue(vec);
		 
		 return xtResult;
		}
};

class CVarArrayAvrg : public CVarMultiVarExpression
{
public:
	CVarArrayAvrg( vector< CVarRoot* >& rvecPVR, bool bDestroyPVRs=false ):CVarMultiVarExpression(bDestroyPVRs)
		{ setupMultiExp(rvecPVR); m_iVecSize= static_cast<xt_value>(m_vecPVR.size()); }
	virtual ~CVarArrayAvrg(){}
protected:
	virtual xt_value getNewValue( const vectorValues& vec )
		{
		 xt_value xtResult=0;
		 for (m_itVP=m_vecPVR.begin();m_itVP!=m_vecPVR.end();m_itVP++)
			xtResult += (*m_itVP)->getValue(vec);
		 
		xtResult/=m_iVecSize;

		 return xtResult;
		}
	xt_value m_iVecSize;
};

class CVarArrayCount : public CVarMultiVarExpression
{
public:
	CVarArrayCount( vector< CVarRoot* >& rvecPVR, bool bDestroyPVRs=false ):CVarMultiVarExpression(bDestroyPVRs)
		{ setupMultiExp(rvecPVR); m_iVecSize= xt_value(m_vecPVR.size()); }
	virtual ~CVarArrayCount(){}
protected:
	virtual xt_value getNewValue( const vectorValues& vec )
		{
		 return m_iVecSize;
		}
	xt_value m_iVecSize;
};

#endif // !defined(AFX_VARMULTIVAREXPRESSION_H__8658E73A_A644_4DE8_AEDE_B244200ECF9A__INCLUDED_)
