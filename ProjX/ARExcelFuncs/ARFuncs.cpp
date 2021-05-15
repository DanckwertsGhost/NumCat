// ARFuncs.cpp : Implementation of CARFuncs
#include "stdafx.h"
#include "ARExcelFuncs.h"
#include "ARFuncs.h"
#include "ARExcelStream.h"
#include "../csvLookup.h"

/////////////////////////////////////////////////////////////////////////////
// CARFuncs

STDMETHODIMP CARFuncs::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IARFuncs
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CARFuncs::OnConnection(IDispatch * Application, ext_ConnectMode ConnectMode, IDispatch * AddInInst, SAFEARRAY * * custom)
{
	ATLTRACE(_T("OnConnection called\n"));
//	HRESULT hr;

	if (Application == NULL)
		return E_POINTER;

    m_spApp = Application; 
    ATLASSERT(m_spApp);

	if (!m_spApp)
		return E_FAIL;
/*
	hr = m_spApp->DisplayXMLSourcePane();

	hr = m_spApp->Volatile();
*/


	return S_OK; //E_NOTIMPL;
}

///////////////////////////////////////////////////////////
// Function name	: CARFuncs::get_Version
// Description	    : A standard property for Aston Read items.
// Return type		: STDMETHODIMP 
// Argument         : float *pVal
///////////////////////////////////////////////////////////
STDMETHODIMP CARFuncs::get_Version(float *pVal)
{

	if (pVal == NULL)
		return E_POINTER;

	(*pVal) = VERSION_ARFUNCS;

	return S_OK;
}


///////////////////////////////////////////////////////////
// Function name	: CARFuncs::Interpolate
// Description	    : Interpolate a value
// Return type		: STDMETHODIMP 
// Argument         : BSTR *Key
// Argument         : VARIANT *KeyValue
// Argument         : BSTR *LookupKey
// Argument         : BSTR *Sheet
// Argument         : VARIANT *vReturn
///////////////////////////////////////////////////////////
STDMETHODIMP CARFuncs::Interpolate(BSTR *Key, VARIANT *KeyValue, BSTR *LookupKey, BSTR *Sheet, VARIANT *vReturn)
{

	CcsvHolder* pHolder = NULL;

	if (vReturn == NULL)
		return E_POINTER;

	(*vReturn).dblVal = NOT_DEFINED;
	(*vReturn).vt = VT_R8;

	if ((Key == NULL)||(LookupKey == NULL)||(Sheet == NULL))
		return S_FALSE;

	// TODO: Add your implementation code here
	try
	{
	string sSheet;
	string sKey;
	string sLookup;
	csvVariable fValue;
	enumARReadHint erh = readFormatFreeText;
	enumARStream eStr = streamFail;


	switch(KeyValue->vt)
	{
		case VT_R8:
			fValue = KeyValue->dblVal;
			break;
		case VT_R4:
			fValue = KeyValue->fltVal;
			break;
		case VT_I4:
			fValue = KeyValue->lVal;
			break;
		case VT_I2:
			fValue = KeyValue->iVal;
			break;
		default:
			return S_FALSE;
	}

	MapStringIndexHolderCCF::const_iterator cit;
	HRESULT hr;
	VARIANT_BOOL vb;

	// can the sheet be found ?
	USES_CONVERSION;

	sSheet = OLE2A(*Sheet);
	sKey = OLE2A(*Key);
	sLookup = OLE2A(*LookupKey);

	cit = m_mapHolders.find(sSheet);

	if (cit==m_mapHolders.end()) // then we will have to create one
			{
			IARStream* pIStream = NULL;
			IDispatch* pIDispatch = NULL;
//			IARExcelStream* pIARE = NULL;

			// NEED TO CHECK SCOPES ON SOME COM pointer life times here

			hr = CoCreateInstance(CLSID_ARExcelStream,NULL,/*CLSCTX_INPROC_HANDLER*/CLSCTX_INPROC_SERVER,IID_IARStream/*IID_IARExcelStream*/,(void**)&pIStream);

			if (FAILED(hr))
					return ("Problems with opening the Excel table",GUID_NULL,hr);

			// test interface stuff
//			hr = pIStream->QueryInterface(&pIARE);
//			if (FAILED(hr))
//					return E_FAIL;
//			ATLTRACE("pIARE->AddRef() = %d\n",pIARE->AddRef());
//			float fV=-99.9F;
//			hr = pIARE->get_Version(&fV);
//			ATLTRACE("Version = %f\n",fV);
			// next tell it about Excel
			hr = m_spApp.QueryInterface(&pIDispatch);
			pIDispatch->AddRef();
			
//			if ((FAILED(hr))||(pIDispatch==NULL))
//				return E_FAIL;
			ATLTRACE("pIStream->AddRef() %d\n", pIStream->AddRef());

//			hr = pIARE->TestCallOne(pIDispatch,&vb);
//			ATLTRACE("pIARE->Release() = %d\n",pIARE->Release());
			hr = pIStream->SetDataSystem(pIDispatch,&vb);
			pIDispatch->Release();
			ATLTRACE("pIStream->Release() %d\n", pIStream->Release());

			if (FAILED(hr))
					return ("Problems with opening the Excel table",GUID_NULL,hr);

			if (vb==VB_FALSE)
				return S_FALSE;

			

			hr = pIStream->loadStream(Sheet,erh,&eStr);

			if (FAILED(hr))
					return ("Problems with opening the Excel table",GUID_NULL,hr);

			if (eStr!=streamLoaded)
					return S_FALSE;

			ATLTRACE("pIStream = %X, pIARE = NULL, pIDispatch = %X\n",pIStream,pIDispatch);

			pHolder = new CcsvLookup(pIStream);

			if (!pHolder)
					return ("Problems with opening the Excel table",GUID_NULL,E_OUTOFMEMORY);
		
			m_vecpHolders.push_back(pHolder);
			m_mapHolders[sSheet] = pHolder;

			pIStream->Release();
			}
			else
			pHolder = cit->second;

	ATLASSERT(pHolder);

	(*vReturn).fltVal = pHolder->interpolate(sKey,sLookup,fValue);


	}
	catch(...)
	{

	return Error("Failure in interpolation",GUID_NULL,E_FAIL);
	}

//	(*vReturn).fltVal = -99.F;
	return S_OK;
}
