// SymlixStream.cpp : Implementation of CSymlixStream
#include "stdafx.h"
#include "SymlixStore.h"
#include "SymlixStream.h"
#include <assert.h>

#define LINE_LENGTH 255

/////////////////////////////////////////////////////////////////////////////
// CSymlixStream

STDMETHODIMP CSymlixStream::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IARStream
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

void CSymlixStream::FinalRelease()
{

	if (!m_is.is_open()) // clean up afterwards
		m_is.close();
}


///////////////////////////////////////////////////////////
// Function name	: CSymlixStream::get_StreamState
// Description	    : provides the current state of the stream
// Return type		: STDMETHODIMP 
// Argument         : enumARStream *pVal
///////////////////////////////////////////////////////////
STDMETHODIMP CSymlixStream::get_StreamState(enumARStream *pVal)
{
	(*pVal) = m_essState; // will change soon

	return S_OK;
}


///////////////////////////////////////////////////////////
// Function name	: CSymlixStream::loadStream
// Description	    : attempt to load stream and return status
// Return type		: STDMETHODIMP 
// Argument         : BSTR *pbstrKey
// Argument         : enumARReadHint esrh - hint provided to class
// Argument         : enumARStream *pVal
///////////////////////////////////////////////////////////
STDMETHODIMP CSymlixStream::loadStream(BSTR *pbstrKey, enumARReadHint esrh, enumARStream *pVal)
{

	USES_CONVERSION;

	m_sFile = OLE2A(*pbstrKey);

	if (m_is.is_open()) // in the event this is being called again
		m_is.close();

	if (m_sFile.size()==0)
			{
			m_essState = streamFail;
			(*pVal) = m_essState;
			return S_FALSE;
			}

	m_is.open(m_sFile.c_str());

	if (m_is.is_open())
		{
		m_essState = streamLoaded;		
		(*pVal) = m_essState;
		return S_OK; 
		}

	m_essState = streamFail;		
	(*pVal) = m_essState;
	return S_FALSE; 

}


///////////////////////////////////////////////////////////
// Function name	: CSymlixStream::readLine
// Description	    : 
// Return type		: STDMETHODIMP 
// Argument         : BSTR *pbstrLine
///////////////////////////////////////////////////////////
STDMETHODIMP CSymlixStream::readLine(/*[out]*/BSTR *pbstrLine)
{

	try
	{
	USES_CONVERSION;

	CComBSTR cbLine(_T(""));
//	(*pbstrLine) = SysAllocString(cbLine);
//	cbLine.Attach(*pbstrLine);
	char sLine[LINE_LENGTH+1];

	switch(m_essState) // check only appropriate states go forward
	{
	case streamLoaded:
	case streamReadline:
		// ok can go ahead
		break;
	default:
		// cannot go ahead - but must return the BSTR
		(*pbstrLine) = SysAllocString(cbLine);
//		cbLine.CopyTo(pbstrLine);
//		*pbstrLine = cbLine.Detach();
//		(*pVal) = m_essState;
		return S_FALSE;
	}

    if (!m_is.is_open())
		{
		(*pbstrLine) = SysAllocString(cbLine);
//		cbLine.CopyTo(pbstrLine);
//		*pbstrLine = cbLine.Detach();
		return E_FAIL;
		}

	m_is.getline(sLine,LINE_LENGTH);

	cbLine.Append(sLine);
		
	(*pbstrLine) = SysAllocString(cbLine);


//	cbLine.CopyTo(pbstrLine);
//	cbLine.Detach();
//	*pbstrLine = cbLine.m_str;
//	pbstrLine = &(cbLine.m_str);
//	cbLine.Detach();
	if (m_is.eof()!=0)
		m_essState = streamEnd;
		else
		m_essState = streamReadline;
//	(*pVal) = m_essState;
	return S_OK;
	}
	catch(...)
	{
	USES_CONVERSION;
	(*pbstrLine) = SysAllocString(T2COLE("<internal error> Unhandled failure reading file in SymlixStream - please report."));
	return E_FAIL;
	}
	return S_FALSE;


/* Maybe use some of the following - taken from a different context
			if (is.rdstate()==ios::failbit)
					{
					oserr << "<Error> Problem reading line - line may exceed the limit in length of "<<CSIMULATION_SIZE<< " characters\n";
					is.close();
					bFormatError=true;
					return false;					
					}
			ASSERT2(is.rdstate()!=ios::failbit); // lets come straight to the scene of the crime if developing
			ASSERT2(is.rdstate()!=ios::badbit);
			if (is.rdstate()==ios::badbit)
					{
					oserr << "<Error> Unknown input file error - please contact vendor.\n";
					is.close();
					bFormatError=true;
					return false;
					}
*/
}

STDMETHODIMP CSymlixStream::gotoFirstLine(enumARStream *pVal)
{

	try
	{

		switch(m_essState)
		{
		case streamLoaded:
		case streamReadline:
		#ifndef NDEBUG
			assert(m_is.is_open()); // otherwise states have failed
		#endif
			if (!m_is.is_open()) // this shouldn't have happened - indicates failure in code
				{
				m_essState = streamFail;
				(*pVal) = m_essState;
				return E_FAIL;
				}
			m_is.close();
			m_is.open(m_sFile.c_str());
			if (!m_is.is_open()) // been unable to get the file back - need to fail with grace
				{
				m_essState = streamFail;
				(*pVal) = m_essState;
				return S_FALSE;
				}
			ATLTRACE("[IARFileStream] - state to streamLoaded\n");
			m_essState = streamLoaded;
			(*pVal) = m_essState;
			return S_OK;
		default:
			break;
		}

		(*pVal) = m_essState; // not going to change the state
	}
	catch(...)
	{
	// crash and burn
	m_essState = streamFail;
	(*pVal) = m_essState;
	return E_FAIL;
	}

	return S_FALSE;
}


///////////////////////////////////////////////////////////
// Function name	: CSymlixStream::lastLineExtra
// Description	    : This does nothing for files - but may be supported
//                    by other users of the interface
// Return type		: STDMETHODIMP 
// Argument         : [in] enumARIODataType esType
// Argument         : [out,retval] BSTR *pbstr
///////////////////////////////////////////////////////////
STDMETHODIMP CSymlixStream::lastLineExtra(enumARIODataType esType, BSTR *pbstr)
{

	try
	{
	USES_CONVERSION;
	(*pbstr) = SysAllocString(T2COLE(""));
	}
	catch(...)
	{
		// not much I can do here if the above failed
		return E_FAIL;
	}

	return S_OK;
}

STDMETHODIMP CSymlixStream::AddWatchObject(IDispatch *pIDisp, VARIANT_BOOL *pOK)
{
	ATLTRACE("AddRef() =%d\n",pIDisp->AddRef());
	ATLTRACE("Release() =%d\n",pIDisp->Release());

	(*pOK) = VB_FALSE;

	return S_FALSE;
}


///////////////////////////////////////////////////////////
// Function name	: CSymlixStream::SetDataSystem
// Description	    : This is not yet implemented for first version,
//                    but will be required for subsequent versions.
// Return type		: STDMETHODIMP 
// Argument         : IDispatch *pIDisp
// Argument         : VARIANT_BOOL *pOK
///////////////////////////////////////////////////////////
STDMETHODIMP CSymlixStream::SetDataSystem(IDispatch *pIDisp, VARIANT_BOOL *pOK)
{
	ATLTRACE("AddRef() =%d\n",pIDisp->AddRef());
	ATLTRACE("Release() =%d\n",pIDisp->Release());

	(*pOK) = VB_FALSE; // not yet implemented

	return S_FALSE;
}
