// SymlixError.h : Declaration of the CSymlixError

#ifndef __SYMLIXERROR_H_
#define __SYMLIXERROR_H_


#include "resource.h"       // main symbols


/////////////////////////////////////////////////////////////////////////////
// CSymlixError
class ATL_NO_VTABLE CSymlixError : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSymlixError, &CLSID_NumCatError>,
	public IDispatchImpl<INumCatError, &IID_INumCatError, &LIBID_NumCatLib>
{
public:
	CSymlixError():m_iX(-1),m_iLine(-1)
	{
	}
#ifndef NDEBUG
	void FinalRelease();
#endif

DECLARE_REGISTRY_RESOURCEID(IDR_SYMLIXERROR)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSymlixError)
	COM_INTERFACE_ENTRY(INumCatError)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// INumCatError
public:
	STDMETHOD(get_HelpRef)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_XPosition)(/*[out, retval]*/ long *pVal);
	void setError(const char *sDescription, enumNumCatErrorCode eLevel, const char *sSource, long iLine, long iX, const char* sCodeSource, long iCodeLine );
	STDMETHOD(get_DevSupportDescription)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_ErrCode)(/*[out, retval]*/ enumNumCatErrorCode *pVal);
	STDMETHOD(get_Line)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_StreamName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_Description)(/*[out, retval]*/ BSTR *pVal);

private:
	long m_iX;
	CComBSTR m_cbDevSupportText;
	CComBSTR m_cbDescription;
	CComBSTR m_cbStreamName;
	long m_iLine;
	enumNumCatErrorCode m_eCode;
};

#endif //__SYMLIXERROR_H_
