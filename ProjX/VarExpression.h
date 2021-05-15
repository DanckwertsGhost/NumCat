// VarExpression.h: interface for the CVarExpression class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VAREXPRESSION_H__4E7F697A_F425_4110_BC2A_7679D5065770__INCLUDED_)
#define AFX_VAREXPRESSION_H__4E7F697A_F425_4110_BC2A_7679D5065770__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VarRoot.h"

class CVarExpression : public CVarRoot  
{
public:
	CVarExpression(bool bDestroyPVRs=false/*CVarRoot* pvrLeft, CVarRoot* pvrRight*/);
	virtual ~CVarExpression();

	virtual xt_value getValue( const vectorValues& vec ) 
	{
		if ((!m_iCacheState)||(m_iLocalCacheState!=m_iCacheState))
			{
			m_xtCacheValue = getNewValue( vec );
			if (m_iCacheState) // only if cache states are being used
				m_iLocalCacheState=m_iCacheState;
			}
	
	 return m_xtCacheValue; 
	}

	virtual void setType( const xt_constrained_value& xtExample )
	{
		xt_value xtTemp = xt_value(m_xtCacheValue);
		m_xtCacheValue.copy(xtExample); // transfers any contraints
		m_xtCacheValue = xtTemp; // attempts to restore values - within new constaints
	}

	// May drop these after debug
//	CVarRoot* getLeft(){return m_pvrLeft; };
//	CVarRoot* getRight(){return m_pvrRight; };

protected:
	virtual xt_value getNewValue( const vectorValues& vec ){ return xtv_NotSet; }
	virtual void setupExp(CVarRoot* pvrLeft, CVarRoot* pvrRight){m_pvrLeft=pvrLeft;m_pvrRight=pvrRight;}

	CVarRoot* m_pvrLeft;
	CVarRoot* m_pvrRight;
	bool m_bDestroyPVRs;
	xt_constrained_value m_xtCacheValue; // need to confirm if constrianed variables are needed here
	short m_iLocalCacheState;

};

#endif // !defined(AFX_VAREXPRESSION_H__4E7F697A_F425_4110_BC2A_7679D5065770__INCLUDED_)
