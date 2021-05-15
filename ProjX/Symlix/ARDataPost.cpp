// ARDataPost.cpp : Implementation of CARDataPost
#include "stdafx.h"
#include "Symlix.h"
#include "ARDataPost.h"
#include "ARDataPostOffice.h"

#include <string>



/////////////////////////////////////////////////////////////////////////////
// CARDataPost

STDMETHODIMP CARDataPost::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IARDataPost
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CARDataPost::AddItem(BSTR *pbstrFirstKey, BSTR *pbstrSecondKey, double vValue, VARIANT_BOOL *pvbResult)
{
	try
	{
		USES_CONVERSION;
		CARDataPostOffice* po = CARDataPostOffice::instance();

		if (!po)
			{
			(*pvbResult) = VB_FALSE;
			return E_OUTOFMEMORY;
			}
			
		if (po->AddItem(OLE2A(*pbstrFirstKey),OLE2A(*pbstrSecondKey),vValue))
				{
				(*pvbResult) = VB_TRUE;
				return S_OK;
				}
		(*pvbResult) = VB_FALSE;

	}
	catch(...) // last line of defence against COM disaster
	{
		ATLTRACE("Unexpect error caught here %s : %d\n",__FILE__,__LINE__);
		ATLASSERT(false);
		return E_ABORT;
	}
	return S_FALSE;
}

STDMETHODIMP CARDataPost::RetrieveItem(BSTR *pbstrFirstKey, BSTR *pbstrSecondKey, double *pvValue)
{

	try
	{
		USES_CONVERSION;
		CARDataPostOffice* po = CARDataPostOffice::instance();

		if (!po)
			{
			(*pvValue) = NOT_DEFINED;
			return E_OUTOFMEMORY;
			}
			
		if (po->retrieveItem(OLE2A(*pbstrFirstKey),OLE2A(*pbstrSecondKey),*pvValue))
				return S_OK;

		(*pvValue) = NOT_FOUND;

	}
	catch(...) // last line of defence against COM disaster
	{
		ATLTRACE("Unexpect error caught here %s : %d\n",__FILE__,__LINE__);
		ATLASSERT(false);
		return E_ABORT;
	}
	return S_FALSE;

}

STDMETHODIMP CARDataPost::FindItem(BSTR *pbstrFirstKey, BSTR *pbstrSecondKey, VARIANT_BOOL *pvbResult)
{
	try
	{
		USES_CONVERSION;
		CARDataPostOffice* po = CARDataPostOffice::instance();

		if (!po)
			{
			(*pvbResult) = false;
			return E_OUTOFMEMORY;
			}
			
		if (po->findItem(OLE2A(*pbstrFirstKey),OLE2A(*pbstrSecondKey)))
				{
				(*pvbResult) = VB_TRUE;
				return S_OK;
				}
		(*pvbResult) = VB_FALSE;

	}
	catch(...) // last line of defence against COM disaster
	{
		ATLTRACE("Unexpect error caught here %s : %d\n",__FILE__,__LINE__);
		ATLASSERT(false);
		return E_ABORT;
	}
	return S_FALSE;
}

STDMETHODIMP CARDataPost::AddTextItem(BSTR *pbstrFirstKey, BSTR *pbstrSecondKey, BSTR *pbstrItem, VARIANT_BOOL *pvbResult)
{
	try
	{
		USES_CONVERSION;
		CARDataPostOffice* po = CARDataPostOffice::instance();

		if (!po)
			{
			(*pvbResult) = VB_FALSE;
			return E_OUTOFMEMORY;
			}
			
		if (po->AddTextItem(OLE2A(*pbstrFirstKey),OLE2A(*pbstrSecondKey),OLE2A(*pbstrItem)))
				{
				(*pvbResult) = VB_TRUE;
				return S_OK;
				}
		(*pvbResult) = VB_FALSE;

	}
	catch(...) // last line of defence against COM disaster
	{
		ATLTRACE("Unexpect error caught here %s : %d\n",__FILE__,__LINE__);
		ATLASSERT(false);
		return E_ABORT;
	}
	return S_FALSE;
}

STDMETHODIMP CARDataPost::RetrieveTextItem(BSTR *pbstrFirstKey, BSTR *pbstrSecondKey, BSTR *pbstrValue)
{
	try
	{
		USES_CONVERSION;
		CARDataPostOffice* po = CARDataPostOffice::instance();
		std::string sResult="";
		CComBSTR cbResult;

		if (!po)
			{
			(*pbstrValue) = NULL;
			return E_OUTOFMEMORY;
			}
			
		if (po->retrieveTextItem(OLE2A(*pbstrFirstKey),OLE2A(*pbstrSecondKey),sResult))
				{
				cbResult.Attach(*pbstrValue);
				cbResult = sResult.c_str();
				*pbstrValue = cbResult.Detach();
				//*pbstrValue = SysAllocString(sResult.c_str());
				if (*pbstrValue)
					return S_OK;
					else
					return E_OUTOFMEMORY;

				}
		*pbstrValue = NULL;

	}
	catch(...) // last line of defence against COM disaster
	{
		*pbstrValue = NULL;
		ATLTRACE("Unexpect error caught here %s : %d\n",__FILE__,__LINE__);
		ATLASSERT(false);
		return E_ABORT;
	}
	return S_FALSE;
}

STDMETHODIMP CARDataPost::FindTextItem(BSTR *pbstrFirstKey, BSTR *pbstrSecondKey, VARIANT_BOOL *pvbResult)
{
	try
	{
		USES_CONVERSION;
		CARDataPostOffice* po = CARDataPostOffice::instance();

		if (!po)
			{
			(*pvbResult) = false;
			return E_OUTOFMEMORY;
			}
			
		if (po->findTextItem(OLE2A(*pbstrFirstKey),OLE2A(*pbstrSecondKey)))
				{
				(*pvbResult) = VB_TRUE;
				return S_OK;
				}
		(*pvbResult) = VB_FALSE;

	}
	catch(...) // last line of defence against COM disaster
	{
		ATLTRACE("Unexpect error caught here %s : %d\n",__FILE__,__LINE__);
		ATLASSERT(false);
		return E_ABORT;
	}
	return S_FALSE;
}
