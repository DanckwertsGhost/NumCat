// SymlixWriteStream.cpp : Implementation of CSymlixWriteStream
#include "stdafx.h"
#include "SymlixStore.h"
#include "SymlixWriteStream.h"

/////////////////////////////////////////////////////////////////////////////
// CSymlixWriteStream

STDMETHODIMP CSymlixWriteStream::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IARWriteStream
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


///////////////////////////////////////////////////////////
// Function name	: CSymlixWriteStream::loadStream
// Description	    : 
// Return type		: STDMETHODIMP 
// Argument         : BSTR *pbstrKey
// Argument         : enumARWriteHint hint
// Argument         : enumARStream *pVal
///////////////////////////////////////////////////////////
STDMETHODIMP CSymlixWriteStream::loadStream(BSTR *pbstrKey, enumARWriteHint hint, enumARStream *pVal)
{

	USES_CONVERSION;

	m_sFile = OLE2A(*pbstrKey);

	if (m_os.is_open()) // in the event this is being called again
		m_os.close();

	m_bFirstLine=true;
	
	if (m_sFile.size()==0)
			{
			m_essState = streamFail;
			(*pVal) = m_essState;
			return S_FALSE;
			}

	m_os.open(m_sFile.c_str());

	if (m_os.is_open())
		{
		m_essState = streamLoaded;		
		(*pVal) = m_essState;
		m_hint = hint; // not sure this will be useful here
		return S_OK; 
		}

	m_essState = streamFail;		
	(*pVal) = m_essState;
	return S_FALSE; 


}


///////////////////////////////////////////////////////////
// Function name	: CSymlixWriteStream::writeLine
// Description	    : 
// Return type		: STDMETHODIMP 
// Argument         : BSTR *pbstrKey
// Argument         : enumARStream *pVal
///////////////////////////////////////////////////////////
STDMETHODIMP CSymlixWriteStream::writeLine(BSTR *pbstrKey, enumARStream *pVal)
{
	// TODO: Add your implementation code here
	char* sLine;


	if (!m_os.is_open())
		{
		m_essState = streamFail;
		(*pVal) = m_essState;
		return S_FALSE;
		}

	try
	{
		sLine = NULL;
		USES_CONVERSION;
		
		if (m_bFirstLine)
			m_bFirstLine = false;
			else
			m_os << "\n";
		
		m_os << OLE2A(*pbstrKey);
		m_essState = streamWriteLine;
		(*pVal) = m_essState;

	}
	catch(...) // though shalt not throw exceptions out of COM objects
	{
	m_essState = streamFail;
	(*pVal) = m_essState;
	return E_FAIL;
	}
	
	
	delete []sLine;
	return S_OK;
}


///////////////////////////////////////////////////////////
// Function name	: CSymlixWriteStream::get_StreamState
// Description	    : 
// Return type		: STDMETHODIMP 
// Argument         : enumARStream *pVal
///////////////////////////////////////////////////////////
STDMETHODIMP CSymlixWriteStream::get_StreamState(enumARStream *pVal)
{
	(*pVal) = m_essState; // will change soon

	return S_OK;
}


///////////////////////////////////////////////////////////
// Function name	: CSymlixWriteStream::closeStream
// Description	    : Allow for a stream to be flushed and closed
// Return type		: STDMETHODIMP 
// Argument         : enumARStream *pVal
///////////////////////////////////////////////////////////
STDMETHODIMP CSymlixWriteStream::closeStream(enumARStream *pVal)
{
	// TODO: Add your implementation code here
	if (!m_os.is_open())
		m_os.close();
	m_essState = streamEmpty;

	return S_OK;
}


///////////////////////////////////////////////////////////
// Function name	: CSymlixWriteStream::FinalRelease
// Description	    : Ensure the strean is closed correctly - if still open
// Return type		: void 
///////////////////////////////////////////////////////////
void CSymlixWriteStream::FinalRelease()
{

	if (!m_os.is_open()) // clean up afterwards
		m_os.close();
}

STDMETHODIMP CSymlixWriteStream::prepareLineWriteExtra(enumARIODataType esType, BSTR *pbstr, VARIANT_BOOL *pVal)
{
	// Nothing to do here - just add some debug code to allow this to be checked
#ifndef NDEBUG
	try
	{
		USES_CONVERSION;
		ATLTRACE(" CSymlixWriteStream::prepareLineWriteExtra => ");
		ATLTRACE(OLE2A(*pbstr));
		ATLTRACE("\n");
		

	}
	catch(...)
	{
		return E_FAIL;
	}

#endif

	(*pVal) = VB_FALSE; // as this isn't implemented

	return S_OK;
}

STDMETHODIMP CSymlixWriteStream::AddWatchObject(IDispatch *pIDisp, VARIANT_BOOL *pOK)
{
	ATLTRACE("AddRef() =%d\n",pIDisp->AddRef());
	ATLTRACE("Release() =%d\n",pIDisp->Release());

	(*pOK) = VB_FALSE;

	return S_FALSE;
}


///////////////////////////////////////////////////////////
// Function name	: CSymlixWriteStream::SetDataSystem
// Description	    : This is not yet implemented for first version,
//                    but will be required for subsequent versions.
// Return type		: STDMETHODIMP 
// Argument         : IDispatch *pIDisp
// Argument         : VARIANT_BOOL *pOK
///////////////////////////////////////////////////////////
STDMETHODIMP CSymlixWriteStream::SetDataSystem(IDispatch *pIDisp, VARIANT_BOOL *pOK)
{
	ATLTRACE("AddRef() =%d\n",pIDisp->AddRef());
	ATLTRACE("Release() =%d\n",pIDisp->Release());

	(*pOK) = VB_FALSE; // not yet implemented

	return S_FALSE;
}
