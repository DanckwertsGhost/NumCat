// ARDataPost.h : Declaration of the CARDataPost

#ifndef __ARDATAPOST_H_
#define __ARDATAPOST_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CARDataPost
class ATL_NO_VTABLE CARDataPost : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CARDataPost, &CLSID_ARDataPost>,
	public ISupportErrorInfo,
	public IDispatchImpl<IARDataPost, &IID_IARDataPost, &LIBID_NumCatLib>
{
public:
	CARDataPost()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ARDATAPOST)
DECLARE_NOT_AGGREGATABLE(CARDataPost)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CARDataPost)
	COM_INTERFACE_ENTRY(IARDataPost)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IARDataPost
public:
	STDMETHOD(FindTextItem)(/*[in]*/ BSTR* pbstrFirstKey, /*[in]*/ BSTR* pbstrSecondKey, /*[out,retval]*/ VARIANT_BOOL* pvbResult);
	STDMETHOD(RetrieveTextItem)(/*[in]*/ BSTR* pbstrFirstKey, /*[in]*/ BSTR* pbstrSecondKey, /*[out,retval]*/ BSTR* pbstrValue);
	STDMETHOD(AddTextItem)(/*[in]*/ BSTR* pbstrFirstKey, /*[in]*/ BSTR* pbstrSecondKey, /*[in]*/ BSTR* pbstrItem, /*[out,retval]*/ VARIANT_BOOL* pvbResult);
	STDMETHOD(FindItem)(/*[in]*/ BSTR* pbstrFirstKey, /*[in]*/ BSTR* pbstrSecondKey, /*[out,retval]*/ VARIANT_BOOL* pvbResult);
	STDMETHOD(RetrieveItem)(/*[in]*/ BSTR* pbstrFirstKey, /*[in]*/ BSTR* pbstrSecondKey,/*[out,retval]*/ double* pvValue);
	STDMETHOD(AddItem)(/*[in]*/ BSTR* pbstrFirstKey, /*[in]*/ BSTR* pbstrSecondKey, /*[in]*/ double vValue, /*[out,retval]*/ VARIANT_BOOL* pvbResult);
};

#endif //__ARDATAPOST_H_
