// VarRoot.h: interface for the CVarRoot class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VARROOT_H__B8F46341_3195_4442_9717_6C81EE528338__INCLUDED_)
#define AFX_VARROOT_H__B8F46341_3195_4442_9717_6C81EE528338__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StdAfx.h"

#include <fstream>
#include <vector>
#include <limits>

using namespace std;

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

#ifndef xt_value
#define xt_value double // note this may change latter
#endif

// define xt_constrained_value to allow strong type info to be added
#ifndef xt_constrained_value
#define xt_constrained_value xt_value
#define XT_NODEF_CONSTRAINTS // so now use of methods used
#endif

#define xtv_NotSet -999
#define vectorValues vector< xt_value >
#define vectorConstrainedValues vector< xt_constrained_value >

/* Not yet clear if this should be used or if other exceptions such as div by zero
 should be caught*/
class CExceptionCVarRoot
{
public:
	CExceptionCVarRoot(const char* sStr):m_xtvL(xtv_NotSet),m_xtvR(xtv_NotSet)
	{strcpy(m_sHeading,"Numerical exception : ");strcpy(m_sMessage,sStr);}
	CExceptionCVarRoot(const char* sStr, const xt_value xtvL, const xt_value xtvR):m_xtvL(xtvL),m_xtvR(xtvR)
	{strcpy(m_sHeading,"Numerical exception : ");strcpy(m_sMessage,sStr);}
	CExceptionCVarRoot(const char* sStr, const xt_value xtvL):m_xtvL(xtvL),m_xtvR(xtv_NotSet)
	{strcpy(m_sHeading,"Numerical exception : ");strcpy(m_sMessage,sStr);}

	friend ostream& operator << (ostream& os, CExceptionCVarRoot& Except)
	{ os << Except.m_sHeading << Except.m_sMessage <<" ";Except.outNums(os); os.flush(); return os;}

	const char* getMessage() const{ return m_sMessage; }
	const char* getHeading() const{ return m_sHeading; }

protected:
	void outNums(ostream& os)
	{
	if ((m_xtvL!=numeric_limits<xt_value>::signaling_NaN())&&(m_xtvL==xtv_NotSet))
				return;
	os << "( " << m_xtvL;
	if ((m_xtvL!=numeric_limits<xt_value>::signaling_NaN())&&(m_xtvR!=xtv_NotSet))
			os << " , " << m_xtvR;
	os << " )";
	return;
	}	


	char m_sMessage[500];
	char m_sHeading[25];
	xt_value m_xtvL;
	xt_value m_xtvR;

};

class CVarRoot  
{
public:
	CVarRoot();
	virtual ~CVarRoot();
	
	virtual xt_value getValue( const vectorValues& vec ) =0;
	virtual void setType( const xt_constrained_value& xtExample ) =0;

	static void stepGlobalCache()
	{
		if (!m_iCacheState)
			m_iCacheState=m_iOldNextCacheState;
			else
			m_iCacheState++;

		if (m_iCacheState>10)
				m_iCacheState=1;//go back 0 = not started
	}
	static void switchCacheOff() 
	{
		m_iOldNextCacheState = m_iCacheState+1; 
		m_iCacheState = 0; 
	}

protected:
	static short m_iCacheState;
	static short m_iOldNextCacheState;
};

#endif // !defined(AFX_VARROOT_H__B8F46341_3195_4442_9717_6C81EE528338__INCLUDED_)
