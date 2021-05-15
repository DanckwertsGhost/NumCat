// SymlixErrorRun.h : Declaration of the CSymlixErrorRun

#ifndef __SYMLIXERRORRUN_H_
#define __SYMLIXERRORRUN_H_


#include "resource.h"       // main symbols
#include "symlix.h"

#include <objbase.h>
#include <vector>
#include <atlbase.h> // test may remove 
#include <atlcom.h>

using namespace std;

#pragma warning(disable:4786)


/////////////////////////////////////////////////////////////////////////////
// CSymlixErrorRun
class ATL_NO_VTABLE CSymlixErrorRun : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSymlixErrorRun, &CLSID_NumCatErrorRun>,
	public IDispatchImpl<INumCatErrorRun, &IID_INumCatErrorRun, &LIBID_NumCatLib>
{
public:
	CSymlixErrorRun()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SYMLIXERRORRUN)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSymlixErrorRun)
	COM_INTERFACE_ENTRY(INumCatErrorRun)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// INumCatErrorRun
public:
	STDMETHOD(get_CountErrors)(/*[out, retval]*/ long *pVal);
	STDMETHOD(GetAllErrors)(/*[out,retval]*/ SAFEARRAY **ppErrors);
	void FinalRelease();
	bool addError(INumCatError* pIErr);
private:
	vector< INumCatError* > m_vecpISymErr; // to hold refernces to all symlix error objects
};

#endif //__SYMLIXERRORRUN_H_
