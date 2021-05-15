// CNumCatLocalValues.h : Declaration of the CCNumCatLocalValues

#ifndef __CNUMCATLOCALVALUES_H_
#define __CNUMCATLOCALVALUES_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCNumCatLocalValues
class ATL_NO_VTABLE CCNumCatLocalValues : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCNumCatLocalValues, &CLSID_NumCatLocalValues>,
	public ISupportErrorInfo,
	public IDispatchImpl<INumCatLocalValues, &IID_INumCatLocalValues, &LIBID_NumCatLib>
{
public:
	CCNumCatLocalValues()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_CNUMCATLOCALVALUES)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCNumCatLocalValues)
	COM_INTERFACE_ENTRY(INumCatLocalValues)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// INumCatLocalValues
public:
};

#endif //__CNUMCATLOCALVALUES_H_
