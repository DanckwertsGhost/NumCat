// SymlixStream.h : Declaration of the CSymlixStream

#ifndef __SYMLIXSTREAM_H_
#define __SYMLIXSTREAM_H_

#include "resource.h"       // main symbols
#include <string>
#include <fstream>

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CSymlixStream
class ATL_NO_VTABLE CSymlixStream : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSymlixStream, &CLSID_ARFileStream>,
	public ISupportErrorInfo,
	public IDispatchImpl<IARStream, &IID_IARStream, &LIBID_ARSTORELib>
{
public:
	CSymlixStream():m_essState(streamEmpty),m_sFile(""),m_is()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SYMLIXSTREAM)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSymlixStream)
	COM_INTERFACE_ENTRY(IARStream)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IARStream
public:
	STDMETHOD(SetDataSystem)(/*[in]*/ IDispatch* pIDisp, /*[out,retval]*/ VARIANT_BOOL *pOK);
	STDMETHOD(AddWatchObject)(/*[in]*/ IDispatch* pIDisp, /*[out,retval]*/ VARIANT_BOOL *pOK);
	STDMETHOD(lastLineExtra)(/*[in]*/ enumARIODataType esType, /*[out,retval]*/ BSTR* pbstr);
	STDMETHOD(loadStream)(/*[in]*/ BSTR* pbstrKey, /*[in]*/ enumARReadHint esrh, /*[out,retval]*/ enumARStream* pVal);
	STDMETHOD(get_StreamState)(/*[out, retval]*/ enumARStream *pVal);
	STDMETHOD(gotoFirstLine)(/*[out,retval]*/ enumARStream *pVal);
	STDMETHOD(readLine)(/*[out,retval]*/ BSTR* pbstrLine);
    void FinalRelease();
private:
	enumARStream m_essState;
	string m_sFile;
	ifstream m_is;
};

#endif //__SYMLIXSTREAM_H_
