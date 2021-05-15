// DispParam.cpp: implementation of the CDispWrap class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DispParam.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDispWrap::CDispWrap():m_iArgCount(0),m_iNamedArgCount(0)
{

}

CDispWrap::~CDispWrap()
{
	ClearAllArgs();
}


void CDispWrap::ClearVariant(VARIANTARG *pvarg)
{
	pvarg->vt = VT_EMPTY;
	pvarg->wReserved1 = 0;
	pvarg->wReserved2 = 0;
	pvarg->wReserved3 = 0;
	pvarg->lVal = 0;

}

void CDispWrap::ClearAllArgs()
{
	int i;
	
	for (i = 0; i < m_iArgCount; i++) 
	{
		if (m_awFlags[i] & DISPARG_NOFREEVARIANT)
			// free the variant's contents based on type
			ClearVariant(&m_aVargs[i]);
		else
			ReleaseVariant(&m_aVargs[i]);
	}

	m_iArgCount = 0;
	m_iNamedArgCount = 0;

}

void CDispWrap::ReleaseVariant(VARIANTARG *pvarg)
{
	VARTYPE vt;
	VARIANTARG *pvargArray;
	long lLBound, lUBound, l;
	
	vt = pvarg->vt & 0xfff;		// mask off flags
	
	// check if an array.  If so, free its contents, then the array itself.
	if (V_ISARRAY(pvarg)) 
	{
		// variant arrays are all this routine currently knows about.  Since a
		// variant can contain anything (even other arrays), call ourselves
		// recursively.
		if (vt == VT_VARIANT) 
		{
			SafeArrayGetLBound(pvarg->parray, 1, &lLBound);
			SafeArrayGetUBound(pvarg->parray, 1, &lUBound);
			
			if (lUBound > lLBound) 
			{
				lUBound -= lLBound;
				
				SafeArrayAccessData(pvarg->parray, (void**)&pvargArray);
				
				for (l = 0; l < lUBound; l++) 
				{
					ReleaseVariant(pvargArray);
					pvargArray++;
				}
				
				SafeArrayUnaccessData(pvarg->parray);
			}
		}
		else 
		{
			MessageBox(NULL, _T("ReleaseVariant: Array contains non-variant type"), "Failed", MB_OK | MB_ICONSTOP);
		}
		
		// Free the array itself.
		SafeArrayDestroy(pvarg->parray);
	}
	else 
	{
		switch (vt) 
		{
			case VT_DISPATCH:
				//(*(pvarg->pdispVal->lpVtbl->Release))(pvarg->pdispVal);
				pvarg->pdispVal->Release();
				break;
				
			case VT_BSTR:
				SysFreeString(pvarg->bstrVal);
				break;
				
			case VT_I2:
			case VT_I4:
			case VT_BOOL:
			case VT_R8:
			case VT_ERROR:		// to avoid erroring on an error return from Excel
				// no work for these types
				break;
				
			default:
				MessageBox(NULL, _T("ReleaseVariant: Unknown type"), "Failed", MB_OK | MB_ICONSTOP);
				break;
		}
	}
	
	ClearVariant(pvarg);

}


///////////////////////////////////////////////////////////
// Function name	: CDispWrap::getDispParams
// Return type		: DISPPARAMS& 
///////////////////////////////////////////////////////////
DISPPARAMS& CDispWrap::getDispParams()
{
	m_params.rgdispidNamedArgs = m_aDispIds + 1;
	m_params.rgvarg = m_aVargs;
	m_params.cArgs = m_iArgCount;
	m_params.cNamedArgs = m_iNamedArgCount;

	return m_params;	
}

bool CDispWrap::AddArgStr(string &sArg)
{
	CComBSTR cb = sArg.c_str();

	if (m_iArgCount<MAX_DISP_ARGS)
		{
		m_aVargs[m_iArgCount].vt = VT_BSTR;
		m_aVargs[m_iArgCount].bstrVal = cb.Copy();
		m_iArgCount++;
		return true;
		}
	return false;
}

bool CDispWrap::AddArgStr( BSTR* pbstr )
{
	CComBSTR cb;

	if ((!pbstr)||(!*pbstr))
		return false;

	cb = (*pbstr);
	if (m_iArgCount<MAX_DISP_ARGS)
		{
		m_aVargs[m_iArgCount].vt = VT_BSTR;
		m_aVargs[m_iArgCount].bstrVal = cb.Copy();
		m_iArgCount++;
		return true;
		}
	return false;
}

bool CDispWrap::AddArgStr( const CComBSTR& cb )
{

	if (m_iArgCount<MAX_DISP_ARGS)
		{
		m_aVargs[m_iArgCount].vt = VT_BSTR;
		m_aVargs[m_iArgCount].bstrVal = cb.Copy();
		m_iArgCount++;
		return true;
		}
	return false;
}


bool CDispWrap::AddArgLong(long i)
{

	if (m_iArgCount<MAX_DISP_ARGS)
		{
		m_aVargs[m_iArgCount].vt = VT_I4;
		m_aVargs[m_iArgCount].lVal = i;
		m_iArgCount++;
		return true;
		}
	return false;
}

bool CDispWrap::AddArgBOOL(BOOL b)
{

	if (m_iArgCount<MAX_DISP_ARGS)
		{
		m_aVargs[m_iArgCount].vt = VT_BOOL;
		m_aVargs[m_iArgCount].boolVal = b ? VB_TRUE : VB_FALSE;
		m_iArgCount++;
		return true;
		}
	return false;
}

bool CDispWrap::AddArgDbl(double d)
{

	if (m_iArgCount<MAX_DISP_ARGS)
		{
		m_aVargs[m_iArgCount].vt = VT_R8;
		m_aVargs[m_iArgCount].dblVal = d;
		m_iArgCount++;
		return true;
		}
	return false;
}

bool CDispWrap::AddArgStrLong( string sArg, long iNum )
{
	char str[32];

	if (abs(iNum)>10000000000)
		return false;

	sArg += itoa(iNum,str,10);

	return AddArgStr(sArg);

}


HRESULT CDispWrap::WrapCall(int autoType, VARIANT *pvResult, IDispatch *pDisp, LPOLESTR ptName, bool bClearArrays /*=true*/ ) 
{
    // Begin variable-argument list...
//    va_list marker;
//    va_start(marker, cArgs);

    if(!pDisp) {
//        MessageBox(NULL, "NULL IDispatch passed to AutoWrap()", "Error", 0x10010);
//        _exit(0);
			if (bClearArrays)
				ClearAllArgs();
			return E_NOINTERFACE;
    }

    // Variables used...
//    DISPPARAMS dp = { NULL, NULL, 0, 0 };
    DISPID dispidNamed = DISPID_PROPERTYPUT;
    DISPID dispID;
    HRESULT hr;
//    char buf[200];
//    char szName[200];

    
    // Convert down to ANSI
//    WideCharToMultiByte(CP_ACP, 0, ptName, -1, szName, 256, NULL, NULL);
    
    // Get DISPID for name passed...
    hr = pDisp->GetIDsOfNames(IID_NULL, &ptName, 1, LOCALE_USER_DEFAULT, &dispID);
    if(FAILED(hr)) {
 //       sprintf(buf, "IDispatch::GetIDsOfNames(\"%s\") failed w/err 0x%08lx", szName, hr);
 //       MessageBox(NULL, buf, "AutoWrap()", 0x10010);
 //       _exit(0);
 		if (bClearArrays)
				ClearAllArgs();
       return hr;
    }

    
    // Allocate memory for arguments...
//    VARIANT *pArgs = new VARIANT[cArgs+1];
    // Extract arguments...
//    for(int i=0; i<cArgs; i++) {
//        pArgs[i] = va_arg(marker, VARIANT);
//    }
    
    // Build DISPPARAMS
//    dp.cArgs = cArgs;
//    dp.rgvarg = pArgs;
    getDispParams();
    // Handle special-case for property-puts!
    if(autoType & DISPATCH_PROPERTYPUT) {
        m_params.cNamedArgs = 1;
        m_params.rgdispidNamedArgs = &dispidNamed;
    }
    
    // Make the call!
    hr = pDisp->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, autoType, &m_params, pvResult, NULL, NULL);
 /*   if(FAILED(hr)) {
        sprintf(buf, "IDispatch::Invoke(\"%s\"=%08lx) failed w/err 0x%08lx", szName, dispID, hr);
        MessageBox(NULL, buf, "AutoWrap()", 0x10010);
        _exit(0);
        return hr;
    }*/
    // End variable-argument section...
//   va_end(marker);
    
//   delete [] pArgs;

	if (bClearArrays)
			ClearAllArgs();
    
    return hr;
}

