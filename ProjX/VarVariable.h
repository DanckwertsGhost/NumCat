// VarVariable.h: interface for the CVarVariable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VARVARIABLE_H__9687CB58_420F_494E_BF9B_71244474E18F__INCLUDED_)
#define AFX_VARVARIABLE_H__9687CB58_420F_494E_BF9B_71244474E18F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VarRoot.h"

class CVarVariable : public CVarRoot  
{
public:
	CVarVariable(long lRef):m_lRef(lRef){};
	virtual ~CVarVariable();

	virtual xt_value getValue( const vectorValues& vec )
		 {
		 #ifndef XT_NODEF_CONSTRAINTS
		 xt_cv = vec[m_lRef];
/*		 #ifdef EXTRADEBUG
		 cout << "CVarVariable::getValue ref ind = "<<m_lRef<<" Value = "<<xt_cv<<endl;
		 #endif*/
		 return xt_cv; 
		 #else
		  return vec[m_lRef];
		 #endif
		 }
	#ifndef XT_NODEF_CONSTRAINTS
	virtual void setType( const xt_constrained_value& xtExample )		{
		xt_value xtTemp = xt_value(xt_cv);
		xt_cv.copy(xtExample); // transfers any contraints
		xt_cv = xtTemp; // attempts to restore values - within new constaints
		}
	#else
	virtual void setType( const xt_constrained_value& xtExample ){};
	#endif
protected:
	virtual void copy(const CVarVariable cvr){m_lRef = cvr.m_lRef;}

	#ifndef XT_NODEF_CONSTRAINTS
	xt_constrained_value xt_cv;
	#endif

	long m_lRef;

};

#endif // !defined(AFX_VARVARIABLE_H__9687CB58_420F_494E_BF9B_71244474E18F__INCLUDED_)
