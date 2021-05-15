// NumCatResource.cpp : Implementation of CNumCatResource
#include "stdafx.h"
#include "Symlix.h"
#include "NumCatResource.h"
#include <htmlHelp.h>

/////////////////////////////////////////////////////////////////////////////
// CNumCatResource

STDMETHODIMP CNumCatResource::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_INumCatResource
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CNumCatResource::get_Picture(short iPict, IPictureDisp **pVal)
{

	IPictureDisp* pPicDisp;
	PICTDESC pd;

    pd.picType = PICTYPE_BITMAP;

	switch(iPict)
	{
	case 1:
	    pd.bmp.hbitmap = LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(IDB_BITMAPNUMCATON));
		break;
	case 2:
		pd.bmp.hbitmap = LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(IDB_BITMAPNUMCATOFF));
		break;
	case 3:
		pd.bmp.hbitmap = LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(IDB_NUMCATTRADE));
		break;
	case 4:
		pd.bmp.hbitmap = LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(IDB_BITMAPHELP1));
		break;
	case 5:
		pd.bmp.hbitmap = LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(IDB_BITMAPRUN1));
		break;
	case 6:
		pd.bmp.hbitmap = LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(IDB_BITMAPNUMCAT2007));
		break;
	case 7:
		pd.bmp.hbitmap = LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(IDB_BITMAPNUMCAT2007INACT));
		break;
	case 8:
	case 9:
		pd.bmp.hbitmap = LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(IDB_BITMAPNUMCATBUYNOW));
		break;
	case 10:
		pd.bmp.hbitmap = LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(IDB_BITMAPBUYNOWICON));
		break;
	default:
		pd.bmp.hbitmap = LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(IDB_BITMAPNUMCATOFF));

		break;
	}

	pd.cbSizeofstruct = sizeof(pd);
    OleCreatePictureIndirect(&pd,IID_IPictureDisp,TRUE,(void **)(&pPicDisp));

//	DeleteObject(pd.bmp.hbitmap);

	(*pVal) = pPicDisp;

	return S_OK;
}

STDMETHODIMP CNumCatResource::get_Mask(short iMask, IPictureDisp **pVal)
{
	// Just ignoring iMask right now - latter it allows for more pictures to be served up with no interface change

	IPictureDisp* pPicDisp;
	PICTDESC pd;

    pd.picType = PICTYPE_BITMAP;

	switch(iMask)
	{
	case 1:
		pd.bmp.hbitmap = LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(IDB_BITMAPMASK1));
		break;
	case 4:	
		pd.bmp.hbitmap = LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(IDB_BITMAPHELP1MASK));
		break;
	case 5:
		pd.bmp.hbitmap = LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(IDB_BITMAPRUNMASK1));
		break;
	default:
		pd.bmp.hbitmap = LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(IDB_BITMAPMASK1));
		break;
	}

	pd.cbSizeofstruct = sizeof(pd);
    OleCreatePictureIndirect(&pd,IID_IPictureDisp,TRUE,(void **)(&pPicDisp));

	(*pVal) = pPicDisp;

	return S_OK;
}

STDMETHODIMP CNumCatResource::get_String(short iString, BSTR *pVal)
{
	CComBSTR cbDescription;

	switch(iString)
	{
	case 1:
		cbDescription = _T("Numerical catalyst - Add model sheet");
		break;
	case 2:
		cbDescription = _T("New model sheet");
		break;
	case 3:
		cbDescription = _T("Use postfix");
		break;
	case 4:
		cbDescription = _T("Use local postfix");
		break;
	case 5:
		cbDescription = _T("None");
		break;


	default:
		cbDescription = _T("Not yet implmented");
		break;
	}

	
	cbDescription.CopyTo(pVal);

	return S_OK;
}

STDMETHODIMP CNumCatResource::get_Version(float *pVal)
{
	(*pVal) = 1.2F;

	return S_OK;
}

STDMETHODIMP CNumCatResource::get_VersionDescription(BSTR *pVal)
{
	CComBSTR cbDescription;

	cbDescription.LoadString(IDS_VERSIONDESCRIPTIONRES);
	cbDescription.Append(_T("\ncompiled "));
	cbDescription.Append(__DATE__);
	cbDescription.Append(_T(" at "));
	cbDescription.Append(__TIME__);
	
	cbDescription.CopyTo(pVal);

	return S_OK;
}

STDMETHODIMP CNumCatResource::CallHTMLHelp(long hWnd, enumNumCatHelp eHelp, long iRef, VARIANT_BOOL *pVal)
{
	HWND h =0;
	(*pVal) = VB_FALSE; // default

	if (m_sHelpFile.size()<1)
		{ // look up the registry value
		CRegKey crkHelp;
		long iR = crkHelp.Open(HKEY_CURRENT_USER,TEXT("Software\\VB and VBA Program Settings\\NumCatAddIn\\Help"),KEY_READ);

		if (iR != ERROR_SUCCESS) // Houston we have a problem
				m_sHelpFile = "";
			else
			{
#define KEYLEN_HELP 250
				char szLocation[KEYLEN_HELP];
				DWORD dwLen = KEYLEN_HELP - 2;

				iR = crkHelp.QueryValue(szLocation,"Location",&dwLen);

				if (iR != ERROR_SUCCESS)
					{
					m_sHelpFile="";
					return Error(_T("Unable find Numerical Catalyst helpfile in registry."));
					}
					else
					{
					m_sHelpFile = szLocation;
					if (m_sHelpFile.substr(m_sHelpFile.length()-3,3).compare("chm")!=0)
						m_sHelpFile=""; // as it hasn't been located

					}
			crkHelp.Close();
			}
		}


	if (m_sHelpFile.size()>0)
				h = HtmlHelp(HWND(hWnd),m_sHelpFile.c_str(),eHelp,iRef);
				else
				return Error(_T("The Numerical Catalyst helpfile record in the registry seems to be empty."));

	if (!h)
		 return Error(_T("For some unknown reason the help window could not be created."));
			
	
	(*pVal) = VB_TRUE;

	return S_OK;
}
