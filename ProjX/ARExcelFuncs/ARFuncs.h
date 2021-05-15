// ARFuncs.h : Declaration of the CARFuncs

#ifndef __ARFUNCS_H_
#define __ARFUNCS_H_

#include "resource.h"       // main symbols
#include <string>
#include <vector>
#include <map>
#include "../csvHolder.h"
#import "C:\Program Files\Common Files\DESIGNER\MSADDNDR.DLL" raw_interfaces_only, raw_native_types, no_namespace, named_guids 

using namespace std;

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

#define VERSION_ARFUNCS 0.1F


struct SStringCompareCSVHolder
{
  bool operator()(const string& s1, const string& s2) const
  {
    return s1.compare(s2) < 0;
  }
};

#define MapStringIndexHolderCCF map<string,CcsvHolder*,SStringCompareCSVHolder>
#define VectorHolders vector<CcsvHolder*>

/////////////////////////////////////////////////////////////////////////////
// CARFuncs
class ATL_NO_VTABLE CARFuncs : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CARFuncs, &CLSID_ARFuncs>,
	public ISupportErrorInfo,
	public IDispatchImpl<IARFuncs, &IID_IARFuncs, &LIBID_AREXCELFUNCSLib>,
	public IDispatchImpl<_IDTExtensibility2, &IID__IDTExtensibility2, &LIBID_AddInDesignerObjects>
{
public:
	CARFuncs()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ARFUNCS)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CARFuncs)
	COM_INTERFACE_ENTRY(IARFuncs)
//DEL 	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY2(IDispatch, IARFuncs)
	COM_INTERFACE_ENTRY(_IDTExtensibility2)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IARFuncs
public:
	STDMETHOD(Interpolate)(/*[in]*/ BSTR* Key, /*[in]*/ VARIANT* KeyValue, /*[in]*/ BSTR* LookupKey, /*[in]*/ BSTR* Sheet, /*[out, retval]*/ VARIANT* vReturn);
	STDMETHOD(get_Version)(/*[out, retval]*/ float *pVal);
// _IDTExtensibility2
	STDMETHOD(OnConnection)(IDispatch * Application, ext_ConnectMode ConnectMode, IDispatch * AddInInst, SAFEARRAY * * custom);
	STDMETHOD(OnDisconnection)(ext_DisconnectMode RemoveMode, SAFEARRAY * * custom)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(OnAddInsUpdate)(SAFEARRAY * * custom)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(OnStartupComplete)(SAFEARRAY * * custom)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(OnBeginShutdown)(SAFEARRAY * * custom)
	{
		VectorHolders::iterator it;	

		try
		{
		m_spApp.Release();
		for (it=m_vecpHolders.begin();it!=m_vecpHolders.end();it++)
			{
			delete (*it);
			}
		m_mapHolders.clear();
		m_vecpHolders.clear();
		}
		catch(...) // as this is not a risk free operation
		{
		ATLASSERT(false); // if we're debuging then draw attention
		// otherwise fingers crossed
		return Error("Unidentified error closing Interpolate add-in",GUID_NULL,E_FAIL);
		}

		return S_OK;
	}

private:
	CComQIPtr<Excel::_Application> m_spApp; 
	VectorHolders m_vecpHolders;
	MapStringIndexHolderCCF m_mapHolders;

};

#endif //__ARFUNCS_H_
