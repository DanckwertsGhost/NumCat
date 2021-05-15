// NumCatExcelLocalRes.h : Declaration of the CNumCatExcelLocalRes

#ifndef __NUMCATEXCELLOCALRES_H_
#define __NUMCATEXCELLOCALRES_H_

#include "resource.h"       // main symbols
#include <map>
#include <vector>
#include <set>

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

#define mapItems map<CComBSTR,CComBSTR,ltkey>
#define vecSheetOrder vector<CComBSTR>
#define listResults vector<CComBSTR>
//#define listResults set<CComBSTR,ltkey>


/////////////////////////////////////////////////////////////////////////////
// CNumCatExcelLocalRes
class ATL_NO_VTABLE CNumCatExcelLocalRes : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CNumCatExcelLocalRes, &CLSID_NumCatExcelLocalRes>,
	public ISupportErrorInfo,
	public IDispatchImpl<INumCatExcelLocalRes, &IID_INumCatExcelLocalRes, &LIBID_NumCatLib>
{
public:
	CNumCatExcelLocalRes():m_iRow(-1),m_bDirty(false)
	{
		initialise();
	}

DECLARE_REGISTRY_RESOURCEID(IDR_NUMCATEXCELLOCALRES)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CNumCatExcelLocalRes)
	COM_INTERFACE_ENTRY(INumCatExcelLocalRes)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// INumCatExcelLocalRes
public:
	STDMETHOD(SetPropertyNumber)(/*[in]*/ BSTR* pbstrKey, /*[in]*/ float* pValue, /*[out,retval]*/ VARIANT_BOOL* pvb);
	STDMETHOD(GetPropertyNumber)(/*[in]*/ BSTR* pbstr, /*[out,retval]*/ float* pValue);
	STDMETHOD(get_LocalSheetName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(IsAResultName)(/*[in]*/ BSTR* pbstrsResultName, /*[out,retval]*/ VARIANT_BOOL* pVal);
	STDMETHOD(AddResultName)(/*[in]*/ BSTR* pbstrResult, /*[out,retval]*/ long* piCount);
	STDMETHOD(get_VersionDescription)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_Version)(/*[out, retval]*/ float *pVal);
	STDMETHOD(get_TagResults)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_TagSheets)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_TagModels)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_TagCharts)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(SaveProperties)(/*[in]*/ IDispatch* pIDisp, /*[ out,retval]*/ VARIANT_BOOL* pvb);
	STDMETHOD(ReadProperties)(/*[in]*/ IDispatch* pIDisp, /*[out,retval]*/ VARIANT_BOOL* pvb);
	STDMETHOD(GetPropertyItem)(/*[in]*/ BSTR* pbstr, /*[out,retval]*/ BSTR* pbstrItem);
	STDMETHOD(get_SheetOrder)(/*[out, retval]*/ SAFEARRAY/*(BSTR)*/ **ppVal);
	STDMETHOD(SetSheetOrder)(/*[in]*/ SAFEARRAY/*(BSTR)*/ **ppVal, /*[out,retval]*/ VARIANT_BOOL* pvb);
//	STDMETHOD(putref_SheetOrder)(/*[in]*/ SAFEARRAY/*(BSTR)*/ *pVal);
	STDMETHOD(SetPropertyItem)(/*[in]*/ BSTR* pbstrKey,/*[in]*/ BSTR* pbstrItem,/*[out,retval]*/ VARIANT_BOOL* pvb);

private:
	void updateResultsMap();
	void readResultsString( const CComBSTR& rcbResults );
	BSTR GetBSTRForID( long iD ) const;
	void DumpItemsToDebug();
	void initialise();
	struct ltkey
	{
		  bool operator()(const CComBSTR& s1, const CComBSTR& s2) const
		  {
			return (s1<s2);
		  }
	};

	mapItems m_mapItems;
	long m_iRow;
	vecSheetOrder m_vecOrder;
	listResults m_listResults;
	bool m_bDirty;

protected:
	void SetAsBSTR( CComBSTR& sHolder, const CComVariant& ccvIn);
};

#endif //__NUMCATEXCELLOCALRES_H_
