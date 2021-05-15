// SymlixEditor.h : Declaration of the CSymlixEditor

#ifndef __SYMLIXEDITOR_H_
#define __SYMLIXEDITOR_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSymlixEditor
class ATL_NO_VTABLE CSymlixEditor : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSymlixEditor, &CLSID_NumCatEditor>,
	public ISupportErrorInfo,
	public IDispatchImpl<INumCatEditor, &IID_INumCatEditor, &LIBID_NumCatLib>
{
public:
/*	CSymlixEditor()
	{
	}*/

DECLARE_REGISTRY_RESOURCEID(IDR_SYMLIXEDITOR)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSymlixEditor)
	COM_INTERFACE_ENTRY(INumCatEditor)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// INumCatEditor
public:
	STDMETHOD(OpenToEdit)(/*[in]*/ int ihwnd, /*[in]*/ BSTR* pbstrKey, /*[in]*/ IARDataStore* pIStore, /*[in]*/ INumCatErrorRun* pIErrorRun, /*[in]*/ IARTrace* pIARTrace, /*[out,retval]*/ enumNumCatEditorCommand* pVal);
};

#endif //__SYMLIXEDITOR_H_
