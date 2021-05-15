// SymlixError.cpp : Implementation of CSymlixError
#include "stdafx.h"
#include "Symlix.h"
#include "SymlixError.h"
#include <string>

using namespace std;

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

/////////////////////////////////////////////////////////////////////////////
// CSymlixError
#ifndef NDEBUG
void CSymlixError::FinalRelease()
{
//	ASSERT2(false);// have to stop here
	ATLTRACE("Final release called on Symlix Error\n");
}
#endif


STDMETHODIMP CSymlixError::get_Description(BSTR *pVal)
{

	(*pVal) = SysAllocString(m_cbDescription);
	return S_OK;
}


STDMETHODIMP CSymlixError::get_StreamName(BSTR *pVal)
{

	(*pVal) = SysAllocString(m_cbStreamName);
	return S_OK;
}

STDMETHODIMP CSymlixError::get_Line(long *pVal)
{

	(*pVal) = m_iLine;
	return S_OK;
}

STDMETHODIMP CSymlixError::get_ErrCode(enumNumCatErrorCode *pVal)
{

	(*pVal) = m_eCode;
	return S_OK;
}

STDMETHODIMP CSymlixError::get_DevSupportDescription(BSTR *pVal)
{

	(*pVal) = SysAllocString(m_cbDevSupportText);
	return S_OK;
}

STDMETHODIMP CSymlixError::get_XPosition(long *pVal)
{

	(*pVal) = m_iX;
	return S_OK;
}

///////////////////////////////////////////////////////////
// Function name	: CSymlixError::setError
// Description	    : 
// Return type		: void 
// Argument         : const char *sDescription
// Argument         : enumNumCatErrorCode eLevel
// Argument         : const char *sSource
// Argument         : long iLine
// Argument         : long iX
// Argument         : const char* sCodeSource
// Argument         : long iCodeLine
///////////////////////////////////////////////////////////
void CSymlixError::setError(const char *sDescription, enumNumCatErrorCode eLevel, const char *sSource, long iLine, long iX, const char* sCodeSource, long iCodeLine )
{
	char sCodeLine[24]; // arbitary
	string str;
	
	m_cbDescription = sDescription;
	m_eCode = eLevel;
	m_cbStreamName = sSource;
	m_iLine = iLine;
	m_iX = iX;

	gcvt(iCodeLine,4,sCodeLine);
	str = "Line ";
	str.append(sCodeLine);
	str.append(" ");
	str.append(sCodeSource);

	m_cbDevSupportText = str.c_str();

}


STDMETHODIMP CSymlixError::get_HelpRef(long *pVal)
{
	(*pVal)=0; // just a holding value for now. Later will add help file help for each error

	return S_OK;
}
