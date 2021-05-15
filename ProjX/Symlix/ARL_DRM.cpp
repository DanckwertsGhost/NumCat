// ARL_DRM.cpp : Implementation of CARL_DRM
#include "stdafx.h"
#include "Symlix.h"
#include "ARL_DRM.h"

/////////////////////////////////////////////////////////////////////////////
// CARL_DRM

STDMETHODIMP CARL_DRM::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IARL_DRM
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

///////////////////////////////////////////////////////////
// Function name	: CARL_DRM::get_Version
// Description	    : return version stored in DRM
// Return type		: STDMETHODIMP 
// Argument         : float *pVal
///////////////////////////////////////////////////////////
STDMETHODIMP CARL_DRM::get_Version(float *pVal)
{
	// TODO: Add your implementation code here

	try
	{
	m_pdrm = CARDRM::instance();
	string sValue;
	sValue = m_pdrm->getEnvironmentValue("VERSIONNUMBER");
	(*pVal) = atof(sValue.c_str());

	}
	catch(...)
		{
		return E_FAIL;

		}

	return S_OK;
}


///////////////////////////////////////////////////////////
// Function name	: CARL_DRM::get_Expired
// Description	    : Has the license period expired ?
// Return type		: STDMETHODIMP 
// Argument         : VARIANT_BOOL *pVal
///////////////////////////////////////////////////////////
STDMETHODIMP CARL_DRM::get_Expired(VARIANT_BOOL *pVal)
{

	try
	{

	m_pdrm = CARDRM::instance();
	if (m_pdrm->getExpired())
		(*pVal) = VB_TRUE;
		else
		(*pVal) = VB_FALSE;

	}
	catch(...)
		{
		return E_FAIL;
		}

	return S_OK;
}


///////////////////////////////////////////////////////////
// Function name	: CARL_DRM::get_User
// Description	    : Get registered user info from DRM
// Return type		: STDMETHODIMP 
// Argument         : BSTR *pVal
///////////////////////////////////////////////////////////
STDMETHODIMP CARL_DRM::get_User(BSTR *pVal)
{
	// TODO: Add your implementation code here
	HRESULT HR;
	try
	{
	m_pdrm = CARDRM::instance();
	CComBSTR cbUser;
	cbUser = m_pdrm->getUser().c_str();
	HR = cbUser.CopyTo(pVal);

	}
	catch(...)
		{
		return E_FAIL;
		}

	return HR;
}


///////////////////////////////////////////////////////////
// Function name	: CARL_DRM::get_Key
// Description	    : Get the current DRM key
// Return type		: STDMETHODIMP 
// Argument         : BSTR *pVal
///////////////////////////////////////////////////////////
STDMETHODIMP CARL_DRM::get_Key(BSTR *pVal)
{
	// TODO: Add your implementation code here
	HRESULT HR;
	try
	{
	m_pdrm = CARDRM::instance();
	CComBSTR cbUser;
	cbUser = m_pdrm->getKey().c_str();
	HR = cbUser.CopyTo(pVal);
	}
	catch(...)
		{
		return E_FAIL;
		}

	return HR;
}


///////////////////////////////////////////////////////////
// Function name	: CARL_DRM::get_MachineFingerPrint
// Description	    : Get the machine finger print ( used for standard licenses )
// Return type		: STDMETHODIMP 
// Argument         : BSTR *pVal
///////////////////////////////////////////////////////////
STDMETHODIMP CARL_DRM::get_MachineFingerPrint(BSTR *pVal)
{
	// TODO: Add your implementation code here
	HRESULT HR;
	try
	{
	m_pdrm = CARDRM::instance();
	CComBSTR cbUser;
	cbUser = m_pdrm->getFingerPrint().c_str();
	HR = cbUser.CopyTo(pVal);
	}
	catch(...)
		{
		return E_FAIL;
		}

	return HR;
}


///////////////////////////////////////////////////////////
// Function name	: CARL_DRM::get_MachineEnhancedFingerPrint
// Description	    : Get the enhanced machine finger print
// Return type		: STDMETHODIMP 
// Argument         : BSTR *pVal
///////////////////////////////////////////////////////////
STDMETHODIMP CARL_DRM::get_MachineEnhancedFingerPrint(BSTR *pVal)
{
	// TODO: Add your implementation code here
	HRESULT HR;
	try
	{
	m_pdrm = CARDRM::instance();
	CComBSTR cbUser;
	cbUser = m_pdrm->getEnhancedFingerPrint().c_str();
	HR = cbUser.CopyTo(pVal);
	}
	catch(...)
		{
		return E_FAIL;
		}

	return HR;
}


///////////////////////////////////////////////////////////
// Function name	: CARL_DRM::Register
// Description	    : Try to register a new key
// Return type		: STDMETHODIMP 
// Argument         : BSTR *sUser
// Argument         : BSTR *sKey
// Argument         : VARIANT_BOOL *pvbResult
///////////////////////////////////////////////////////////
STDMETHODIMP CARL_DRM::Register(BSTR *sUser, BSTR *sKey, VARIANT_BOOL *pvbResult)
{
	// TODO: Add your implementation code here

	try
	{

	string strUser;
	string strKey;
	m_pdrm = CARDRM::instance();

	if (!(*sUser)) // handle the BSTR = NULL case
		{
		(*pvbResult)=VB_FALSE;
		return S_FALSE;
		}	

	if (!(*sKey)) // handle the BSTR = NULL case
		{
		(*pvbResult)=VB_FALSE;
		return S_FALSE; 
		}	


		USES_CONVERSION;

		strUser = OLE2A(*sUser);
		strKey = OLE2A(*sKey);

		if (m_pdrm->installCode(strUser.c_str(),strKey.c_str()))
			(*pvbResult) = VB_TRUE;
			else
			(*pvbResult) = VB_FALSE;
	}
	catch(...)
		{
		return E_FAIL;
		}

	return S_OK;
}


///////////////////////////////////////////////////////////
// Function name	: CARL_DRM::GetValue
// Description	    : Make a query of the DRM software
// Return type		: STDMETHODIMP 
// Argument         : BSTR *sIndex
// Argument         : BSTR *sValue
///////////////////////////////////////////////////////////
STDMETHODIMP CARL_DRM::GetValue(BSTR *sIndex, BSTR *sValue)
{
	// TODO: Add your implementation code here
	HRESULT hr;
	try
	{
		string strIndex;
		string strReturn;
		CComBSTR cbReturn("Not found");
		m_pdrm = CARDRM::instance();

		if (!(*sIndex)) // handle the BSTR = NULL case
			{
			cbReturn.CopyTo(sValue);
			return S_FALSE;
			}	

		USES_CONVERSION;

		strIndex = OLE2A(*sIndex);
		strReturn = m_pdrm->getEnvironmentValue(strIndex.c_str());
		cbReturn = strReturn.c_str();
		
		hr = cbReturn.CopyTo(sValue);

	}
	catch(...)
		{
		return E_FAIL;
		}

	return hr;
}


///////////////////////////////////////////////////////////
// Function name	: CARL_DRM::OpenUserRegisterDialog
// Description	    : Use the internal DRM dialog for this task
// Return type		: STDMETHODIMP 
// Argument         : int parent_hwnd
// Argument         : VARIANT_BOOL *pvb
///////////////////////////////////////////////////////////
STDMETHODIMP CARL_DRM::OpenUserRegisterDialog(int parent_hwnd, VARIANT_BOOL *pvb)
{
	// TODO: Add your implementation code here
	try
	{
	m_pdrm = CARDRM::instance();

	m_pdrm->showEnterKeyDialog(HWND(parent_hwnd));

	(*pvb) = VB_TRUE;
	}
	catch(...)
		{
		(*pvb) = VB_FALSE;
		return E_FAIL;
		}

	return S_OK;
}


///////////////////////////////////////////////////////////
// Function name	: CARL_DRM::OpenBuyNowURL
// Description	    : Make the DRM based appeal to the buy now URL
// Return type		: STDMETHODIMP 
// Argument         : int parent_hwnd
// Argument         : VARIANT_BOOL *pvb
///////////////////////////////////////////////////////////
STDMETHODIMP CARL_DRM::OpenBuyNowURL(int parent_hwnd, VARIANT_BOOL *pvb)
{
	// TODO: Add your implementation code here
	try
	{
	m_pdrm = CARDRM::instance();

	m_pdrm->callBuyNowURL(HWND(parent_hwnd));

	(*pvb) = VB_TRUE;
	}
	catch(...)
		{
		(*pvb) = VB_FALSE;
		return E_FAIL;
		}

	return S_OK;
}


///////////////////////////////////////////////////////////
// Function name	: CARL_DRM::get_DaysLeft
// Description	    : Days left till Expired
// Return type		: STDMETHODIMP 
// Argument         : long *pVal
///////////////////////////////////////////////////////////
STDMETHODIMP CARL_DRM::get_DaysLeft(long *pVal)
{

	try
	{
	m_pdrm = CARDRM::instance();
	(*pVal) = m_pdrm->getDaysLeft();

	}
	catch(...)
		{
		return E_FAIL;

		}

	return S_OK;
}


///////////////////////////////////////////////////////////
// Function name	: CARL_DRM::get_CountUses
// Description	    : The number of times this software loaded
// Return type		: STDMETHODIMP 
// Argument         : long *pVal
///////////////////////////////////////////////////////////
STDMETHODIMP CARL_DRM::get_CountUses(long *pVal)
{
	try
	{
	m_pdrm = CARDRM::instance();
	m_pdrm->updateEnvironment();
	(*pVal) = m_pdrm->getTotalUses();

	}
	catch(...)
		{
		return E_FAIL;

		}

	return S_OK;
}


///////////////////////////////////////////////////////////
// Function name	: CARL_DRM::get_Verified
// Description	    : Has the current key been verified
// Return type		: STDMETHODIMP 
// Argument         : VARIANT_BOOL **pVal
///////////////////////////////////////////////////////////
STDMETHODIMP CARL_DRM::get_Verified(VARIANT_BOOL *pVal)
{
	try
	{

	m_pdrm = CARDRM::instance();
	if (m_pdrm->getVerified())
		(*pVal) = VB_TRUE;
		else
		(*pVal) = VB_FALSE;

	}
	catch(...)
		{
		return E_FAIL;
		}

	return S_OK;
}
