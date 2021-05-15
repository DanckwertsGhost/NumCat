// ARL_DRM.h : Declaration of the CARL_DRM

#ifndef __ARL_DRM_H_
#define __ARL_DRM_H_

#include "resource.h"       // main symbols
#include "ARDRM.h"

/////////////////////////////////////////////////////////////////////////////
// CARL_DRM
class ATL_NO_VTABLE CARL_DRM : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CARL_DRM, &CLSID_ARL_DRM>,
	public ISupportErrorInfo,
	public IDispatchImpl<IARL_DRM, &IID_IARL_DRM, &LIBID_NumCatLib>
{
public:
	CARL_DRM()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ARL_DRM)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CARL_DRM)
	COM_INTERFACE_ENTRY(IARL_DRM)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IARL_DRM
public:
	STDMETHOD(get_Verified)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_CountUses)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_DaysLeft)(/*[out, retval]*/ long *pVal);
	STDMETHOD(OpenBuyNowURL)(/*[optional,in,defaultvalue(NULL)]*/ int parent_hwnd,/*[out, retval]*/ VARIANT_BOOL* pvb);
	STDMETHOD(OpenUserRegisterDialog)(/*[optional,in,defaultvalue(NULL)]*/ int parent_hwnd, /*[out,retval]*/ VARIANT_BOOL* pvb);
	STDMETHOD(GetValue)(/*[in]*/ BSTR* sIndex, /*[out,retval]*/ BSTR* sValue);
	STDMETHOD(Register)(/*[in]*/ BSTR* sUser, /*[in]*/ BSTR* sKey, /*[out,retval]*/ VARIANT_BOOL* pvbResult);
	STDMETHOD(get_MachineEnhancedFingerPrint)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_MachineFingerPrint)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_Key)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_User)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_Expired)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_Version)(/*[out, retval]*/ float *pVal);

private:
	CARDRM* m_pdrm;
};

#endif //__ARL_DRM_H_
