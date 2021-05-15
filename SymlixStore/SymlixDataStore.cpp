// SymlixDataStore.cpp : Implementation of CSymlixDataStore
#include "stdafx.h"
#include "SymlixStore.h"
#include "SymlixDataStore.h"

/////////////////////////////////////////////////////////////////////////////
// CSymlixDataStore

STDMETHODIMP CSymlixDataStore::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IARDataStore
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}



///////////////////////////////////////////////////////////
// Function name	: CSymlixDataStore::tryToGetARStream
// Description	    : 
// Return type		: STDMETHODIMP 
// Argument         : BSTR *pbstrKey
// Argument         : IARStream **ppSymlixStream
///////////////////////////////////////////////////////////
STDMETHODIMP CSymlixDataStore::tryToGetARStream(BSTR *pbstrKey, enumARReadHint esrh, IARStream **ppSymlixStream )
{


	HRESULT hr;

//	IARStream* pTest = NULL;

	try
	{

	hr = CoCreateInstance(CLSID_ARFileStream,NULL,CLSCTX_INPROC_SERVER,IID_IARStream,(void**)ppSymlixStream);

	if (SUCCEEDED(hr))
		{
		enumARStream essR;
		ATLTRACE(_T("Create SymlixStream ref count"));
		ATLTRACE(_T("(on add %d)"),(*ppSymlixStream)->AddRef());
		ATLTRACE(_T("%d\n"),(*ppSymlixStream)->Release());
		ATLTRACE(_T("*ppSymlixStream %d\n"),*ppSymlixStream);
		// try to load file
		(*ppSymlixStream)->loadStream(pbstrKey,esrh,&essR);
		if (SUCCEEDED(hr))
			if (essR!=streamLoaded)
				hr = S_FALSE;
		}
		else
		{
		ATLTRACE(_T("Failed to create SymlixStream\n"));
		if (hr==E_INVALIDARG)
			ATLTRACE("E_INVALIDARG returned\n");
			else
			if (hr==REGDB_E_CLASSNOTREG)
				ATLTRACE("REGDB_E_CLASSNOTREG\n");
				else
				ATLTRACE("Error code %d",hr);
		}

	}
	catch(...)
	{
		// going down in flames
		return E_FAIL;
	}

	return hr;
}

bool CSymlixDataStore::checkFileExists(const string &sFile) const
{

	ifstream isTest;
	bool bResult;

	if (sFile.size()==0)
			return false;

	isTest.open(sFile.c_str());
	bResult = isTest.is_open();
	isTest.close();

	return bResult;
}

STDMETHODIMP CSymlixDataStore::doChecks(VARIANT_BOOL *pOK)
{
	// TODO: Add your implementation code here
	// TODO: Add your implementation code here
	HRESULT hr;
	IARStream* pSS=NULL;

	try
	{

		CComBSTR cbF1;
		enumARReadHint esrh = readFormatFreeText;
		cbF1 = "C:\\Inetpub\\ftproot\\cpp_new\\ProjX\\input.txt";

		hr = tryToGetARStream(&(cbF1.m_str),esrh,&pSS);

		if (SUCCEEDED(hr))
			{
			pSS->Release();
			(*pOK)=VB_TRUE;
			}
			else
			(*pOK)=VB_FALSE;
	}
	catch(...)
	{
	// aaarhhhhhh
	(*pOK)=VB_FALSE;
	return E_FAIL;
	}	

	return S_OK;
}


STDMETHODIMP CSymlixDataStore::AddWatchObject(/*[in]*/ IDispatch* pIDisp, /*[out,retval]*/ VARIANT_BOOL *pOK)
{
	
	ATLTRACE("AddRef() =%d\n",pIDisp->AddRef());
	ATLTRACE("Release() =%d\n",pIDisp->Release());

	(*pOK) = VB_FALSE;

	return S_FALSE;
}


STDMETHODIMP CSymlixDataStore::isAvailable(BSTR *pbstrKey, VARIANT_BOOL* pOK)
{

	*pOK = VB_FALSE;
	try
	{
		USES_CONVERSION;

		string sFileName = OLE2A(*pbstrKey);

		if (!checkFileExists(sFileName))
					return S_FALSE;
	}
	catch(...)
	{
	// crashing
	return E_FAIL;
	}
	*pOK = VB_TRUE;

	return S_OK;
}


///////////////////////////////////////////////////////////
// Function name	: CSymlixDataStore::tryToGetARWriteStream
// Description	    : 
// Return type		: STDMETHODIMP 
// Argument         : BSTR *pbstrKey
// Argument         : enumARWriteHint eswh
// Argument         : IARWriteStream **ppSymlixWriteStream
///////////////////////////////////////////////////////////
STDMETHODIMP CSymlixDataStore::tryToGetARWriteStream(BSTR *pbstrKey,  enumARWriteHint eswh, IARWriteStream **ppSymlixWriteStream)
{

	HRESULT hr;

//	IARWriteStream* pTest = NULL;

	try
	{

	hr = CoCreateInstance(CLSID_ARFileWriteStream,NULL,CLSCTX_INPROC_SERVER,IID_IARWriteStream,(void**)ppSymlixWriteStream);

	if (SUCCEEDED(hr))
		{
		enumARStream essR;
		ATLTRACE(_T("Create SymlixWriteStream ref count"));
		ATLTRACE(_T("( on add %d )"),(*ppSymlixWriteStream)->AddRef());
		ATLTRACE(_T("%d\n"),(*ppSymlixWriteStream)->Release());
		ATLTRACE(_T("*ppSymlixWriteStream %d\n"),*ppSymlixWriteStream);
		// try to load file
		hr = (*ppSymlixWriteStream)->loadStream(pbstrKey,eswh, &essR);
		if (SUCCEEDED(hr))
			if (essR!=streamLoaded)
				hr = S_FALSE;
		}
		else
		{
		ATLTRACE(_T("Failed to create SymlixWriteStream\n"));
		if (hr==E_INVALIDARG)
			ATLTRACE("E_INVALIDARG returned\n");
			else
			if (hr==REGDB_E_CLASSNOTREG)
				ATLTRACE("REGDB_E_CLASSNOTREG\n");
				else
				ATLTRACE("Error code %d",hr);
		}

	}
	catch(...)
	{
		// going down in flames
		return E_FAIL;
	}

	return hr;
}

bool CSymlixDataStore::checkFileWriteable(const string &sFile) const
{
	ofstream osTest;
	bool bResult;

	if (sFile.size()==0)
			return false;

	osTest.open(sFile.c_str());
	bResult = osTest.is_open();
	osTest.close();

	return bResult;
}

STDMETHODIMP CSymlixDataStore::isAvailableForWrite(BSTR *pbstrKey, VARIANT_BOOL *pOK)
{
	*pOK = VB_FALSE;
	try
	{
		USES_CONVERSION;

		string sFileName = OLE2A(*pbstrKey);

		if (!checkFileWriteable(sFileName))
					return S_FALSE;
	}
	catch(...)
	{
	// crashing
	return E_FAIL;
	}
	*pOK = VB_TRUE;

	return S_OK;
}

STDMETHODIMP CSymlixDataStore::get_Version(float *pVal)
{
	(*pVal) = 1.3F; //27 Oct 09 added to interface Watch Objects 18Nov09 added hints for reading streams
					// 30Nov added SetDataSystem to allow future objects to pass system to use

	return S_OK;
}

STDMETHODIMP CSymlixDataStore::get_VersionDescription(BSTR *pVal)
{
	CComBSTR cbDescription;

	cbDescription.LoadString(IDS_VERSIONDESCRIPTION);
	cbDescription.Append("\ncompiled ");
	cbDescription.Append(__DATE__);
	cbDescription.Append(" at ");
	cbDescription.Append(__TIME__);
	
	cbDescription.CopyTo(pVal);

	return S_OK;
}


///////////////////////////////////////////////////////////
// Function name	: CSymlixDataStore::SetDataSystem
// Description	    : This is not yet implemented for first version,
//                    but will be required for subsequent versions.
// Return type		: STDMETHODIMP 
// Argument         : IDispatch *pIDisp
// Argument         : VARIANT_BOOL *pOK
///////////////////////////////////////////////////////////
STDMETHODIMP CSymlixDataStore::SetDataSystem(IDispatch *pIDisp, VARIANT_BOOL *pOK)
{
	ATLTRACE("AddRef() =%d\n",pIDisp->AddRef());
	ATLTRACE("Release() =%d\n",pIDisp->Release());

	(*pOK) = VB_FALSE; // not yet implemented

	return S_FALSE;
}
