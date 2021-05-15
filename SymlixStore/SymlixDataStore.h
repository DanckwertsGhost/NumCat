// SymlixDataStore.h : Declaration of the CSymlixDataStore

#ifndef __SYMLIXDATASTORE_H_
#define __SYMLIXDATASTORE_H_

#include "resource.h"       // main symbols
#include <string>
#include <fstream>

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CSymlixDataStore
class ATL_NO_VTABLE CSymlixDataStore : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSymlixDataStore, &CLSID_ARFileDataStore>,
	public ISupportErrorInfo,
	public IDispatchImpl<IARDataStore, &IID_IARDataStore, &LIBID_ARSTORELib>
{
public:
	CSymlixDataStore()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SYMLIXDATASTORE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSymlixDataStore)
	COM_INTERFACE_ENTRY(IARDataStore)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IARDataStore
public:
	STDMETHOD(SetDataSystem)(/*[in]*/ IDispatch* pIDisp, /*[out,retval]*/ VARIANT_BOOL *pOK);
	STDMETHOD(AddWatchObject)(/*[in]*/ IDispatch* pIDisp, /*[out,retval]*/ VARIANT_BOOL *pOK);
	STDMETHOD(get_VersionDescription)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_Version)(/*[out, retval]*/ float *pVal);
	STDMETHOD(isAvailableForWrite)(/*[in]*/ BSTR *pbstrKey, /*[out,retval]*/ VARIANT_BOOL *pOK);
	STDMETHOD(tryToGetARWriteStream)(/*[in]*/ BSTR *pbstrKey,  /*[in]*/ enumARWriteHint eswh, /*[out,retval]*/ IARWriteStream** ppSymlixWriteStream);
	STDMETHOD(isAvailable)(/*[in]*/ BSTR* pbstrKey, /*[out,retval]*/ VARIANT_BOOL* pOK);
	STDMETHOD(doChecks)(/*[out,retval]*/ VARIANT_BOOL* pOK);
	STDMETHOD(tryToGetARStream)(/*[in]*/ BSTR* pbstrKey, /*[in]*/ enumARReadHint esrh, /*[out,retval]*/ IARStream** ppSymlixStream );
private:
	bool checkFileWriteable(const string& sFile ) const;
	bool checkFileExists( const string& sFile) const;
};

#endif //__SYMLIXDATASTORE_H_
