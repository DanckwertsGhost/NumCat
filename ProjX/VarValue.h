// VarValue.h: interface for the CVarValue class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VARVALUE_H__0C802316_5B0B_4334_8DBC_348CFBD73D38__INCLUDED_)
#define AFX_VARVALUE_H__0C802316_5B0B_4334_8DBC_348CFBD73D38__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VarRoot.h"

class CVarValue : public CVarRoot  
{
public:
	CVarValue(xt_value xtV): m_xtvValue(xtV){}
	virtual ~CVarValue(){};

	virtual xt_value getValue( const vectorValues& vec ) { return m_xtvValue; }
	virtual void setType( const xt_constrained_value& xtExample )
		{
		xt_value xtTemp = xt_value(m_xtvValue);
		m_xtvValue = xtExample; // transfers any contraints
		m_xtvValue = xtTemp; // attempts to restore values - within new constaints
		}

protected:
	virtual void copy(const CVarValue cvr){m_xtvValue = cvr.m_xtvValue;}

	xt_constrained_value m_xtvValue;

};

#endif // !defined(AFX_VARVALUE_H__0C802316_5B0B_4334_8DBC_348CFBD73D38__INCLUDED_)
