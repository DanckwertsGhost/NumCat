// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__003DDD25_5846_4DA6_9DFA_34190BD4ACF3__INCLUDED_)
#define AFX_STDAFX_H__003DDD25_5846_4DA6_9DFA_34190BD4ACF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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

#import "C:\Program Files\Common Files\Microsoft Shared\OFFICE11\MSO.DLL" rename( "RGB", "MSORGB" ), rename( "DocumentProperties", "MSODocProps" )
#import "C:\Program Files\Common Files\Microsoft Shared\VBA\VBA6\VBE6EXT.OLB" rename ( "Application", "VBApplication" )

namespace Excel
{
    using namespace Office;
    using namespace VBIDE;
}

#import "C:\Program Files\Microsoft Office\OFFICE11\Excel.EXE" \
    rename( "RGB", "RGB_" ), \
    rename( "CopyFile", "CopyFile_" ), \
    rename( "DialogBox", "DialogBox_" ), \
    rename( "ReplaceText", "ReplaceText_" ), \
    exclude ("IFont", "IPicture")

#import "C:\Inetpub\ftproot\cpp_new\SymlixStore\ReleaseMinDependency\ARStore.dll" raw_interfaces_only, raw_native_types, no_namespace, named_guids 

#define VB_FALSE 0
#define VB_TRUE -1

const long NOT_FOUND =-2147483648;
const long NOT_DEFINED=NOT_FOUND+1;

#ifndef newtrack // this is used for memory leak detection in main NumCat projects
	#define newtrack new
#endif

#ifndef ASSERT2
	#ifndef NDEBUG
	#include "assert.h"
		#define ASSERT2 assert

	#else
		#define ASSERT2 //
	#endif
#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.


#endif // !defined(AFX_STDAFX_H__003DDD25_5846_4DA6_9DFA_34190BD4ACF3__INCLUDED)
