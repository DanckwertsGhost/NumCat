// Symlix.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To merge the proxy/stub code into the object DLL, add the file 
//      dlldatax.c to the project.  Make sure precompiled headers 
//      are turned off for this file, and add _MERGE_PROXYSTUB to the 
//      defines for the project.  
//
//      If you are not running WinNT4.0 or Win95 with DCOM, then you
//      need to remove the following define from dlldatax.c
//      #define _WIN32_WINNT 0x0400
//
//      Further, if you are running MIDL without /Oicf switch, you also 
//      need to remove the following define from dlldatax.c.
//      #define USE_STUBLESS_PROXY
//
//      Modify the custom build rule for Symlix.idl by adding the following 
//      files to the Outputs.
//          Symlix_p.c
//          dlldata.c
//      To build a separate proxy/stub DLL, 
//      run nmake -f Symlixps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "Symlix.h"
#include "dlldatax.h"

#include "Symlix_i.c"
#include "SymlixComp.h"
#include "SymlixError.h"
#include "SymlixErrorRun.h"

#include <atlapp.h>

#include <atlwin.h>
#include <atlctrls.h>
#include "SymlixEditor.h"
#include "ARDataPost.h"
#include "ARRunProgress.h"
#include "NumCatResource.h"

#include "NumCatExcelLocalRes.h"
//#include "NumCatDRM.h"
#include "ARL_DRM.h"
#ifdef _MERGE_PROXYSTUB
extern "C" HINSTANCE hProxyDll;
#endif

CAppModule _Module;

HMODULE hInstRich;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_NumCat, CSymlix)
OBJECT_ENTRY(CLSID_NumCatError, CSymlixError)
OBJECT_ENTRY(CLSID_NumCatErrorRun, CSymlixErrorRun)
OBJECT_ENTRY(CLSID_NumCatEditor, CSymlixEditor)
OBJECT_ENTRY(CLSID_ARDataPost, CARDataPost)
OBJECT_ENTRY(CLSID_ARRunProgress, CARRunProgress)
OBJECT_ENTRY(CLSID_NumCatResource, CNumCatResource)
OBJECT_ENTRY(CLSID_NumCatExcelLocalRes, CNumCatExcelLocalRes)
OBJECT_ENTRY(CLSID_ARL_DRM, CARL_DRM)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    lpReserved;
#ifdef _MERGE_PROXYSTUB
    if (!PrxDllMain(hInstance, dwReason, lpReserved))
        return FALSE;
#endif
    if (dwReason == DLL_PROCESS_ATTACH)
    {
		// this resolves ATL window thunking problem when Microsoft Layer for Unicode (MSLU) is used
		// start support WTL
		::DefWindowProc(NULL, 0, 0, 0L);

		AtlInitCommonControls(ICC_COOL_CLASSES | ICC_BAR_CLASSES);	// add flags to support other controls

		hInstRich = ::LoadLibrary(CRichEditCtrl::GetLibraryName());
		ATLASSERT(hInstRich != NULL);
		// end support WTL
		
		_Module.Init(ObjectMap, hInstance, &LIBID_NumCatLib);
        DisableThreadLibraryCalls(hInstance);
    }
    else if (dwReason == DLL_PROCESS_DETACH)
		{
 		if (hInstRich)
			::FreeLibrary(hInstRich);
        _Module.Term();
		}
    return TRUE;    // ok
}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
#ifdef _MERGE_PROXYSTUB
    if (PrxDllCanUnloadNow() != S_OK)
        return S_FALSE;
#endif
    return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
#ifdef _MERGE_PROXYSTUB
    if (PrxDllGetClassObject(rclsid, riid, ppv) == S_OK)
        return S_OK;
#endif
    return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
#ifdef _MERGE_PROXYSTUB
    HRESULT hRes = PrxDllRegisterServer();
    if (FAILED(hRes))
        return hRes;
#endif
    // registers object, typelib and all interfaces in typelib
    return _Module.RegisterServer(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
#ifdef _MERGE_PROXYSTUB
    PrxDllUnregisterServer();
#endif
    return _Module.UnregisterServer(TRUE);
}


#include "ARL_DRM.h"
