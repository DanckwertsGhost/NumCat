// NumCatResource.h : Declaration of the CNumCatResource

#ifndef __NUMCATRESOURCE_H_
#define __NUMCATRESOURCE_H_

#include "resource.h"       // main symbols
#include <string>

/////////////////////////////////////////////////////////////////////////////
// CNumCatResource
class ATL_NO_VTABLE CNumCatResource : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CNumCatResource, &CLSID_NumCatResource>,
	public ISupportErrorInfo,
	public IDispatchImpl<INumCatResource, &IID_INumCatResource, &LIBID_NumCatLib>
{
public:
	CNumCatResource():m_sHelpFile("")
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_NUMCATRESOURCE)
DECLARE_NOT_AGGREGATABLE(CNumCatResource)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CNumCatResource)
	COM_INTERFACE_ENTRY(INumCatResource)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// INumCatResource
public:
	STDMETHOD(CallHTMLHelp)(/*[in]*/ long hWnd, /*[in]*/ enumNumCatHelp eHelp, /*[in]*/ long iRef, /*[out,retval]*/ VARIANT_BOOL* pVal);
	STDMETHOD(get_VersionDescription)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_Version)(/*[out, retval]*/ float *pVal);
	STDMETHOD(get_String)(/*[in]*/ short iString, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_Mask)(/*[in]*/ short iMask, /*[out, retval]*/ IPictureDisp* *pVal);
	STDMETHOD(get_Picture)(/*[in]*/ short iPict, /*[out, retval]*/ IPictureDisp* *pVal);
private:
	std::string m_sHelpFile;
};

#endif //__NUMCATRESOURCE_H_
