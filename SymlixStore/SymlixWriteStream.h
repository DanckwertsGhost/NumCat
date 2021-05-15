// SymlixWriteStream.h : Declaration of the CSymlixWriteStream

#ifndef __SYMLIXWRITESTREAM_H_
#define __SYMLIXWRITESTREAM_H_

#include "resource.h"       // main symbols
#include <string>
#include <fstream>

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CSymlixWriteStream
class ATL_NO_VTABLE CSymlixWriteStream : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSymlixWriteStream, &CLSID_ARFileWriteStream>,
	public ISupportErrorInfo,
	public IDispatchImpl<IARWriteStream, &IID_IARWriteStream, &LIBID_ARSTORELib>
{
public:
	CSymlixWriteStream():m_hint(formatFreeText),m_bFirstLine(true)
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SYMLIXWRITESTREAM)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSymlixWriteStream)
	COM_INTERFACE_ENTRY(IARWriteStream)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IARWriteStream
public:
	STDMETHOD(SetDataSystem)(/*[in]*/ IDispatch* pIDisp, /*[out,retval]*/ VARIANT_BOOL *pOK);
	STDMETHOD(AddWatchObject)(/*[in]*/ IDispatch* pIDisp, /*[out,retval]*/ VARIANT_BOOL *pOK);
	STDMETHOD(prepareLineWriteExtra)(/*[in]*/ enumARIODataType esType, /*[in]*/ BSTR* pbstr, /*[out,retval]*/ VARIANT_BOOL* pVal);
	STDMETHOD(closeStream)(/*[out,retval]*/ enumARStream* pVal);
	STDMETHOD(get_StreamState)(/*[out, retval]*/ enumARStream *pVal);
	STDMETHOD(writeLine)(/*[in]*/ BSTR* pbstrKey, /*[out,retval]*/ enumARStream* pVal);
	STDMETHOD(loadStream)(/*[in]*/ BSTR* pbstrKey, /*[in]*/ enumARWriteHint hint, /*[out,retval]*/ enumARStream* pVal);
    void FinalRelease();
private:
	enumARWriteHint m_hint; // to allow some knowledge of format to be given, eg csv. Useful when writing to spread sheets etc
	enumARStream m_essState;
	string m_sFile;
	ofstream m_os;
	bool m_bFirstLine;
};

#endif //__SYMLIXWRITESTREAM_H_
