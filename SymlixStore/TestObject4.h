// TestObject4.h : Declaration of the CTestObject4

#ifndef __TESTOBJECT4_H_
#define __TESTOBJECT4_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestObject4
class ATL_NO_VTABLE CTestObject4 : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTestObject4, &CLSID_TestObject4>,
	public ISupportErrorInfo,
	public IDispatchImpl<ITestObject4, &IID_ITestObject4, &LIBID_SYMLIXSTORELib>
{
public:
	CTestObject4()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_TESTOBJECT4)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTestObject4)
	COM_INTERFACE_ENTRY(ITestObject4)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITestObject4
public:
	STDMETHOD(twoPlusTwo)(/*[out,retval]*/ long* pVal);
};

#endif //__TESTOBJECT4_H_
