// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__C2AA3B9D_957D_4A0A_A603_0DA1F16CE3D4__INCLUDED_)
#define AFX_STDAFX_H__C2AA3B9D_957D_4A0A_A603_0DA1F16CE3D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/* copied to StdAfxCommon.h
#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif
#define _ATL_APARTMENT_THREADED

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>
*/
#include "../StdAfxCommon.h"
#include <atlwin.h>

#ifdef _SYMLIX
//#define NALPERION
#ifdef NDEBUG // release only
#define SOFTWAREPASSPORT
#endif
#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.


#endif // !defined(AFX_STDAFX_H__C2AA3B9D_957D_4A0A_A603_0DA1F16CE3D4__INCLUDED)

