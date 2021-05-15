// TestObject3.h : Declaration of the CTestObject3

#ifndef __TESTOBJECT3_H_
#define __TESTOBJECT3_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestObject3
class ATL_NO_VTABLE CTestObject3 : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTestObject3, &CLSID_TestObject3>,
	public IDispatchImpl<ITestObject3, &IID_ITestObject3, &LIBID_SYMLIXSTORELib>
{
public:
	CTestObject3()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_TESTOBJECT3)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTestObject3)
	COM_INTERFACE_ENTRY(ITestObject3)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// ITestObject3
public:
	STDMETHOD(loadStream)(/*[in]*/ BSTR* pbstrKey, /*[out,retval]*/ enumARStream* pVal){return S_FALSE;};
	STDMETHOD(get_StreamState)(/*[out, retval]*/ enumARStream *pVal){return S_FALSE;};
	STDMETHOD(gotoFirstLine)(/*[out,retval]*/ enumARStream *pVal){return S_FALSE;};
	STDMETHOD(readLine)(/*[out,retval]*/ BSTR* pbstrLine){return S_FALSE;};
	//, /*[out,retval]*/ enumARStream* pVal){return S_FALSE;};
	STDMETHOD(twoPlusTwo)(/*[out,retval]*/ long* pVal);
};

#endif //__TESTOBJECT3_H_
