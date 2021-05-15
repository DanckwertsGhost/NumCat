// ARExcelStream.h : Declaration of the CARExcelStream

#ifndef __AREXCELSTREAM_H_
#define __AREXCELSTREAM_H_

#include "resource.h"       // main symbols
#include <string>


using namespace std;

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

#pragma warning(disable:4049)


/////////////////////////////////////////////////////////////////////////////
// CARExcelStream
class ATL_NO_VTABLE CARExcelStream : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CARExcelStream, &CLSID_ARExcelStream>,
	public ISupportErrorInfo,
//	public IDispatchImpl<IARExcelStream, &IID_IARExcelStream, &LIBID_AREXCELFUNCSLib>,
	public IDispatchImpl<IARStream, &IID_IARStream, &LIBID_ARSTORELib>
{
public:
	CARExcelStream();

DECLARE_REGISTRY_RESOURCEID(IDR_AREXCELSTREAM)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CARExcelStream)
//	COM_INTERFACE_ENTRY(IARExcelStream)
 	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IARStream)
//	COM_INTERFACE_ENTRY2(IDispatch, IARExcelStream)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IARExcelStream
public:
	STDMETHOD(TestCallOne)(/*[in]*/ IDispatch* pIDisp, /*[out,retval]*/ VARIANT_BOOL* pVal);
	STDMETHOD(get_Version)(/*[out, retval]*/ float *pVal);

	static bool findRangeLimits( string sAddr, long& iColStart, long& iColEnd, long& iRowStart, long& iRowEnd, string sKey = "");

#ifndef NDEBUG
	static bool unitTests();
#endif

	static bool getSafeName( const string& sFullName, string& sSafeName );

// IARStream
	STDMETHOD(get_StreamState)(enumARStream * pVal);
	STDMETHOD(loadStream)(BSTR * pbstrKey, enumARReadHint esrh, enumARStream * pVal);
	STDMETHOD(readLine)(BSTR * pbstrLine);
	STDMETHOD(gotoFirstLine)(enumARStream * pVal);
	STDMETHOD(lastLineExtra)(enumARIODataType esType, BSTR * pbstr);

	STDMETHOD(AddWatchObject)(IDispatch * pIDisp, VARIANT_BOOL * pOK)
	{
		if (pOK == NULL)
			return E_POINTER;

		(*pOK) = VB_FALSE; // as we don't do this just now
			
		return S_OK;
	}

	STDMETHOD(SetDataSystem)(IDispatch * pIDisp, VARIANT_BOOL * pOK);

private:
	static void removeTrailingPoint( string& rsString );
	void assignNameRange( const string& sSafeName, long iColStart, long iColEnd, long iRowStart, long iRowEnd );
	long findFarRightColumn( long iFirstRow, long iLastRow,long iFirstCol=1);
	bool establishLimitsOfRange( long& iColStart, long& iColEnd, long& iRowStart, long& iRowEnd);
	bool getNameInWorkSheet( string sName, Excel::NamePtr& rptrName); 
	long findLastRow( long iFirstRow=1);
	CComQIPtr<Excel::_Application> m_spApp; 
	Excel::_WorksheetPtr m_ptrWrkSheet;
	enumARStream m_eStateExcelStream;
	enumARReadHint m_eARRHint;
	long m_iRow;
	long m_iRowStart;
	long m_iRowEnd;
	long m_iColStart;
	long m_iColEnd;
	long m_ciRowEmpty;
	CComBSTR m_cbSheet;



/*
// IARStream
	STDMETHOD(get_StreamState)(enumARStream * pVal)
	{
		if (pVal == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(loadStream)(BSTR * pbstrKey, enumARReadHint esrh, enumARStream * pVal)
	{
		if (pVal == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(readLine)(BSTR * pbstrLine)
	{
		if (pbstrLine == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(gotoFirstLine)(enumARStream * pVal)
	{
		if (pVal == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(lastLineExtra)(enumARIODataType esType, BSTR * pbstr)
	{
		if (pbstr == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(AddWatchObject)(IDispatch * pIDisp, VARIANT_BOOL * pOK)
	{
		if (pOK == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(SetDataSystem)(IDispatch * pIDisp, VARIANT_BOOL * pOK)
	{
		if (pOK == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}*/
};

#endif //__AREXCELSTREAM_H_
