// NumCatExcelLocalRes.cpp : Implementation of CNumCatExcelLocalRes
#include "stdafx.h"
#include "Symlix.h"
#include "NumCatExcelLocalRes.h"
#include "DispParam.h"
#include <string>
#include <algorithm>

/////////////////////////////////////////////////////////////////////////////
// CNumCatExcelLocalRes

STDMETHODIMP CNumCatExcelLocalRes::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_INumCatExcelLocalRes
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


///////////////////////////////////////////////////////////
// Function name	: CNumCatExcelLocalRes::SetPropertyItem
// Description	    : 
// Return type		: STDMETHODIMP 
// Argument         : BSTR *pbstrKey
// Argument         : BSTR *pbstrItem
// Argument         : VARIANT_BOOL *pvb
///////////////////////////////////////////////////////////
STDMETHODIMP CNumCatExcelLocalRes::SetPropertyItem(BSTR *pbstrKey, BSTR *pbstrItem, VARIANT_BOOL *pvb)
{
	CComBSTR cbResult;
	mapItems::iterator it;
	m_bDirty = true;

	if ((!pbstrKey)||(!pbstrItem))
				{
				(*pvb) = VB_FALSE;
				return E_INVALIDARG;
				}

	it = m_mapItems.find(*pbstrKey);

	if (it!=m_mapItems.end())
		it->second = (*pbstrItem);
		else
		m_mapItems[*pbstrKey] = *pbstrItem; // add a new item

	(*pvb) = VB_TRUE;
	return S_OK;
}


///////////////////////////////////////////////////////////
// Function name	: CNumCatExcelLocalRes::get_SheetOrder
// Description	    : 
// Return type		: STDMETHODIMP 
// Argument         : SAFEARRAY/*(BSTR
///////////////////////////////////////////////////////////
STDMETHODIMP CNumCatExcelLocalRes::get_SheetOrder(SAFEARRAY/*(BSTR)*/ **ppVal)
{

	try
	{
		CComBSTR cbSheetOrderKey;
		CComBSTR cbSheetOrder;
		mapItems::const_iterator cit;
		UINT iStart,iEnd,iElems;
		HRESULT hr;

		// Find the sheet order
		
		if (!cbSheetOrderKey.LoadString(IDS_LE_KEY_ORDEROFSHEETS))
				{
				*ppVal= SafeArrayCreateVector(VT_BSTR,0,0);
				return S_OK;
				}

		cit = m_mapItems.find(cbSheetOrderKey);

		if (cit==m_mapItems.end())
				{
				*ppVal= SafeArrayCreateVector(VT_BSTR,0,0);
				return S_OK;
				}

		iStart =1; // was 0;
		iEnd = cit->second.Length() + iStart;

		ATLASSERT(cit->second.Length()==m_vecOrder.size());

		iElems = iEnd-iStart;

		if (iElems>m_vecOrder.size())
				iElems = m_vecOrder.size();

		*ppVal= SafeArrayCreateVector(VT_BSTR,iStart,iElems);

		BSTR* prgn =0;

		hr = SafeArrayAccessData(*ppVal,(void**)&prgn);
		if (FAILED(hr))	return hr;


		for(UINT i=0;i<iElems;i++)
			prgn[i] = m_vecOrder[i].Copy();
	
	
	}
	catch(...) // to stop any leaking C++ exceptions
	{
		SafeArrayUnaccessData(*ppVal);
		ATLTRACE("Unidentified error called from %d in %s\n",__LINE__,__FILE__);
		return E_FAIL;
	}
	
	SafeArrayUnaccessData(*ppVal);



	return S_OK;
}

STDMETHODIMP CNumCatExcelLocalRes::SetSheetOrder(/*[in]*/ SAFEARRAY/*(BSTR)*/ **ppVal, /*[out,retval]*/ VARIANT_BOOL *pvb)
{
	mapItems::const_iterator cit;
//	UINT iStart,iEnd,iElems;
	HRESULT hr;
	long iLbound, iUbound, iC;
	m_bDirty = true;

	BSTR* prgn =0;
	(*pvb) = VB_FALSE;

	try
	{

	hr = SafeArrayAccessData(*ppVal,(void**)&prgn);
	if (FAILED(hr))	return hr;

	if(SafeArrayGetDim(*ppVal) != 1)
		return E_INVALIDARG;

	hr = SafeArrayGetLBound(*ppVal, 1, &iLbound);
	if (FAILED(hr))
		{
		SafeArrayUnaccessData(*ppVal);
		return hr;
		}

	hr = SafeArrayGetUBound(*ppVal, 1, &iUbound);
	if (FAILED(hr))
		{
		SafeArrayUnaccessData(*ppVal);
		return hr;
		}

	m_vecOrder.clear();

	for (iC=0;iC<=(iUbound-iLbound);iC++)
		m_vecOrder.push_back(prgn[iC]);


	SafeArrayUnaccessData(*ppVal);
	}
	catch(...)
	{
		ATLTRACE("Unidentified error called from %d in %s\n",__LINE__,__FILE__);
		return S_FALSE;
	}

	(*pvb) = VB_TRUE;
	return S_OK;
}


///////////////////////////////////////////////////////////
// Function name	: CNumCatExcelLocalRes::GetPropertyItem
// Description	    : 
// Return type		: STDMETHODIMP 
// Argument         : BSTR *pbstr
// Argument         : BSTR *pbstrItem
///////////////////////////////////////////////////////////
STDMETHODIMP CNumCatExcelLocalRes::GetPropertyItem(BSTR *pbstr, BSTR *pbstrItem)
{
	CComBSTR cbResult;
	mapItems::const_iterator cit;

	cit = m_mapItems.find(*pbstr);

	if (cit!=m_mapItems.end())
		cbResult = cit->second;

	cbResult.CopyTo(pbstrItem);
	return S_OK;
}


///////////////////////////////////////////////////////////
// Function name	: CNumCatExcelLocalRes::ReadProperties
// Description	    : 
// Return type		: STDMETHODIMP 
// Argument         : IDispatch *pIDisp
// Argument         : VARIANT_BOOL *pvb
///////////////////////////////////////////////////////////
STDMETHODIMP CNumCatExcelLocalRes::ReadProperties(IDispatch *pIDisp, VARIANT_BOOL *pvb)
{
	HRESULT hr;
	CDispWrap dw;

	CComVariant ccvWkSheet;
	CComVariant ccvRangeL;
	string sLeft;
	string sRight;
	CComVariant ccvRangeR;
	CComBSTR cbLocalSheet;
	CComVariant ccvVLeft;
	CComVariant ccvVRight;
	CComBSTR cbRight;
	CComBSTR cb;

	mapItems::iterator it;

	m_iRow = 0; // get incremented before loop executed later
	bool bContinue = true;

	cbLocalSheet.LoadString(IDS_LE_LOCAL_OPTIONS);

	initialise();

	(*pvb) = VB_FALSE; // in case we exit early

	if (!pIDisp)
		return S_FALSE;

	if (!dw.AddArgStr(cbLocalSheet))
		return S_FALSE;

	hr = dw.CallGet(&ccvWkSheet,pIDisp,L"Worksheets");
	if (FAILED(hr))
		return S_FALSE;


	sLeft = "A"; sRight = "B";

	while((bContinue)&&(m_iRow++<100))
	{
		
		dw.AddArgStrLong(sLeft,m_iRow);
		hr = dw.CallGet(&ccvRangeL,ccvWkSheet.pdispVal,L"Range");
		if (FAILED(hr))	return hr;

		hr = dw.CallGet(&ccvVLeft,ccvRangeL.pdispVal,L"Value");
		if (FAILED(hr))	return hr;

		dw.AddArgStrLong(sRight,m_iRow);
		hr = dw.CallGet(&ccvRangeR,ccvWkSheet.pdispVal,L"Range");
		if (FAILED(hr))	return hr;

		hr = dw.CallGet(&ccvVRight,ccvRangeR.pdispVal,L"Value");
		if (FAILED(hr))	return hr;

		if (ccvVLeft.vt == VT_BSTR)
			{
			SetAsBSTR(cbRight,ccvVRight);
			it = m_mapItems.find(ccvVLeft.bstrVal);
			if (it!=m_mapItems.end())
				it->second = cbRight;
				else
				m_mapItems[ccvVLeft.bstrVal] = cbRight;
			}
			else
			bContinue=false;
	}

	DumpItemsToDebug();

	// now spin up list of results sheets
	cb.LoadString(IDS_LE_TAG_LISTRESULTSSHEETS);
	it = m_mapItems.find(cb);
	if (it!=m_mapItems.end())
		readResultsString(it->second);
	

	
	(*pvb) = VB_TRUE; 


	return S_OK;
}


///////////////////////////////////////////////////////////
// Function name	: CNumCatExcelLocalRes::SaveProperties
// Description	    : 
// Return type		: STDMETHODIMP 
// Argument         : IDispatch *pIDisp
// Argument         : VARIANT_BOOL *pvb
///////////////////////////////////////////////////////////
STDMETHODIMP CNumCatExcelLocalRes::SaveProperties(IDispatch *pIDisp, VARIANT_BOOL *pvb)
{

	HRESULT hr;
	CDispWrap dw;

	CComVariant ccvWkSheet;
	CComVariant ccvRangeErase;
	CComVariant ccvRangeL;
	CComVariant ccvRangeR;
	CComVariant ccvNewVal;
	CComBSTR cbLocalSheet;
	CComBSTR cbNewSheetOrder;
	CComBSTR cbNewSheetOrderKey;
	CComBSTR cbRight;
	vecSheetOrder::const_iterator cvit;
	long iC;
	string sLeft = "A";
	string sRight = "B";
	string sWipe = "A1:B";
	mapItems::iterator cit;	
	
	if (!m_bDirty) // nothing to do
		{
		(*pvb)=VB_TRUE;
		return S_OK;
		}

	try
	{

		(*pvb) = VB_FALSE; // in case we exit early

		updateResultsMap();

		// Save sheet order to make sure latest info used ( could have a dirty flag to speeed up later
		cbNewSheetOrder="";
		for (cvit=m_vecOrder.begin();cvit!=m_vecOrder.end();cvit++)
			cbNewSheetOrder.Append(" ");

		for (cvit=m_vecOrder.begin(),iC=0;cvit!=m_vecOrder.end();cvit++,iC++)
			cbNewSheetOrder[iC]=(*cvit)[0];

		cbNewSheetOrderKey.LoadString(IDS_LE_KEY_ORDEROFSHEETS);

		cit = m_mapItems.find(cbNewSheetOrderKey);

		if (cit!=m_mapItems.end())
			cit->second = cbNewSheetOrder;

		// end update
		
		cbLocalSheet.LoadString(IDS_LE_LOCAL_OPTIONS);


		if (!pIDisp)
			return E_INVALIDARG;

		if (!dw.AddArgStr(cbLocalSheet))
			return S_FALSE;

		hr = dw.CallGet(&ccvWkSheet,pIDisp,L"Worksheets");
		if (FAILED(hr))
			{
			// maybe the worksheet doesn't exist yet
			CComVariant ccvWorkSheets;
			CComVariant ccvNewSheetName = cbLocalSheet;
			hr = dw.CallGet(&ccvWorkSheets,pIDisp,L"Sheets");
			if (FAILED(hr)) return hr;

			hr = dw.CallGet(&ccvWkSheet,ccvWorkSheets.pdispVal,L"Add");
			if (FAILED(hr)) return hr;

//			ATLTRACE("AddRef = %d\n",ccvWkSheet.pdispVal->AddRef());

			hr = dw.CallPut(xlSheetHidden,ccvWkSheet.pdispVal,L"Visible");
			if (FAILED(hr)) return hr;


			dw.AddArgStr(cbLocalSheet);
			hr = dw.CallPut(&ccvNewSheetName,ccvWkSheet.pdispVal,L"Name");
			if (FAILED(hr))
				{
//				ATLTRACE("Release = %d\n",ccvWkSheet.pdispVal->Release());
				return hr;
				}
//			ATLTRACE("Release = %d\n",ccvWkSheet.pdispVal->Release());
			
			}
			else
			{
			dw.AddArgStrLong(sWipe,m_iRow+5);
			hr = dw.CallGet(&ccvRangeErase,ccvWkSheet.pdispVal,L"Range");
			if (FAILED(hr)) return hr;

			hr = dw.Call(NULL,ccvRangeErase.pdispVal,L"ClearContents"); 
			if (FAILED(hr)) return hr;

#ifndef NDEBUG
			CComVariant ccvVis;
			hr = dw.CallGet(&ccvVis,ccvWkSheet.pdispVal,L"Visible");
			ATLTRACE(" Visible of local sheet Before = %d\n",ccvVis.lVal);
#endif

/*			hr = dw.CallPut(xlSheetHidden,ccvWkSheet.pdispVal,L"Visible");
			if (FAILED(hr)) return hr;
			
#ifndef NDEBUG
			hr = dw.CallGet(&ccvVis,ccvWkSheet.pdispVal,L"Visible");
			ATLTRACE(" Visible After = %d\n",ccvVis.lVal);
#endif */
			}


		DumpItemsToDebug();

		for (cit=m_mapItems.begin(),m_iRow=1;cit!=m_mapItems.end();cit++,m_iRow++)
			{

			dw.AddArgStrLong(sLeft,m_iRow);
			hr = dw.CallGet(&ccvRangeL,ccvWkSheet.pdispVal,L"Range");
			if (FAILED(hr))	return hr;

			dw.AddArgStr(cit->first);
			ccvNewVal = cit->first;
			hr = dw.CallPut(&ccvNewVal,ccvRangeL.pdispVal,L"Value");
			if (FAILED(hr))	return hr;

			dw.AddArgStrLong(sRight,m_iRow);
			hr = dw.CallGet(&ccvRangeR,ccvWkSheet.pdispVal,L"Range");
			if (FAILED(hr))	return hr;

			if ((cit->second.Length()>0)&&((cit->second[0]=='f')||(cit->second[0]=='t')))
					cbRight = L"'";
					else
					cbRight = L"";
			cbRight.Append(cit->second);
			dw.AddArgStr(cbRight);
			ccvNewVal = cbRight;
			hr = dw.CallPut(&ccvNewVal,ccvRangeR.pdispVal,L"Value");
			if (FAILED(hr))	return hr;

			}
		(*pvb) = VB_TRUE; // in case we exit early
		m_bDirty = false;
	}
	catch(...)
	{
	(*pvb) = VB_FALSE; // in case we exit early
	ATLTRACE("Unidentified error called from %d in %s\n",__LINE__,__FILE__);
	return S_FALSE;
	}
		
	return S_OK;
}

void CNumCatExcelLocalRes::initialise()
{
	CComBSTR cb;
	CComBSTR cbTrue(_T("true"));
	CComBSTR cbFalse(_T("false"));
	CComBSTR cbDefaultTag(_T("sym"));
	CComBSTR cbNegOne(_T("-1"));

	m_mapItems.clear();
	m_listResults.clear();
	m_vecOrder.clear();
	m_bDirty = true;

	cb.LoadString(IDS_LE_KEY_LOCALPREFIX);
	m_mapItems[cb] = cbDefaultTag;

	cb.LoadString(IDS_LE_KEY_USELOCALPREFIX);
	m_mapItems[cb] = cbFalse;

	cb.LoadString(IDS_LE_KEY_HIDELOCALMODELS);
	m_mapItems[cb] = cbFalse;

	cb.LoadString(IDS_LE_KEY_AUTOORGANISESHEETS);
	m_mapItems[cb] = cbFalse;

	cb.LoadString(IDS_LE_KEY_LASTRUNVERSION);
	m_mapItems[cb] = cbNegOne;

	cb.LoadString(IDS_LE_KEY_EXTRADEBUG);
	m_mapItems[cb] = cbFalse;

	cb.LoadString(IDS_LE_TAG_LISTRESULTSSHEETS);
	m_mapItems[cb] =  _T("0#");

	cb.LoadString(IDS_LE_KEY_ORDEROFSHEETS);
	m_mapItems[cb] = _T("SCMR"); // may need to change this latter on

	cb.LoadString(IDS_ORDER_RESULTS);
	m_vecOrder.push_back(cb);
	
	cb.LoadString(IDS_ORDER_MODELS);
	m_vecOrder.push_back(cb);
	
	cb.LoadString(IDS_ORDER_CHARTS);
	m_vecOrder.push_back(cb);
		
	cb.LoadString(IDS_ORDER_SHEETS);
	m_vecOrder.push_back(cb);


}

void CNumCatExcelLocalRes::SetAsBSTR(CComBSTR &sHolder, const CComVariant &ccvIn)
{

	char sBuff[70];
//	double v;
//	long i;

	switch(ccvIn.vt)
	{
	case VT_NULL:
		sHolder = L"";
		break;
	case VT_BOOL:
		if (ccvIn.boolVal==VB_TRUE)
			sHolder = L"true";
			else
			sHolder = L"false";
		break;
	case VT_I2:
		sHolder = _itoa(ccvIn.iVal,sBuff,10);
		break;
	case VT_I4:
		sHolder = _ltoa(ccvIn.lVal,sBuff,10);
		break;

	case VT_R4:
		sHolder = _gcvt(ccvIn.fltVal,10,sBuff); 
		break;

	case VT_R8:
		sHolder = _gcvt(ccvIn.dblVal,10,sBuff); 
		break;


	case VT_BSTR:
		sHolder = ccvIn.bstrVal;
		break;

	default:
		// do nothing
		ATLASSERT(false);
		sHolder = "";
	}

}

void CNumCatExcelLocalRes::DumpItemsToDebug()
{
#ifndef NDEBUG
	string sLeft, sRight;
	mapItems::const_iterator cit;

	USES_CONVERSION;
	
	for (cit=m_mapItems.begin();cit!=m_mapItems.end();cit++)
		{
		sLeft = OLE2A(cit->first);
		sRight = OLE2A(cit->second);
		ATLTRACE("[%s]  [%s]\n",sLeft.c_str(),sRight.c_str());
		}
#endif
}

STDMETHODIMP CNumCatExcelLocalRes::get_TagCharts(BSTR *pVal)
{
	(*pVal) = GetBSTRForID(IDS_ORDER_CHARTS);

	return S_OK;
}

STDMETHODIMP CNumCatExcelLocalRes::get_TagModels(BSTR *pVal)
{
	(*pVal) = GetBSTRForID(IDS_ORDER_MODELS);

	return S_OK;
}

STDMETHODIMP CNumCatExcelLocalRes::get_TagSheets(BSTR *pVal)
{
	(*pVal) = GetBSTRForID(IDS_ORDER_SHEETS);

	return S_OK;
}

STDMETHODIMP CNumCatExcelLocalRes::get_TagResults(BSTR *pVal)
{
	(*pVal) = GetBSTRForID(IDS_ORDER_RESULTS);

	return S_OK;
}

BSTR CNumCatExcelLocalRes::GetBSTRForID(long iD) const
{
	CComBSTR cb;
	cb.LoadString(iD);
	return cb.Copy();
}

STDMETHODIMP CNumCatExcelLocalRes::get_Version(float *pVal)
{
	(*pVal) = 1.000F;

	return S_OK;
}

STDMETHODIMP CNumCatExcelLocalRes::get_VersionDescription(BSTR *pVal)
{
	CComBSTR cbDescription;

	cbDescription.LoadString(IDS_NUMCATLOCRESDES);
	cbDescription.Append("\ncompiled ");
	cbDescription.Append(__DATE__);
	cbDescription.Append(" at ");
	cbDescription.Append(__TIME__);
	
	cbDescription.CopyTo(pVal);


	return S_OK;
}

STDMETHODIMP CNumCatExcelLocalRes::AddResultName(BSTR *pbstrResult, long *piCount)
{
	CComBSTR cb;
	listResults::iterator it;
	m_bDirty = true;

	if (pbstrResult)
		{
		cb = *pbstrResult;
		it = find(m_listResults.begin(),m_listResults.end(),cb);
		if (it==m_listResults.end())
			m_listResults.push_back(cb);
		}

	(*piCount) = m_listResults.size();
		
	return S_OK;
}

STDMETHODIMP CNumCatExcelLocalRes::IsAResultName(BSTR *pbstrsResultName, VARIANT_BOOL *pVal)
{
	CComBSTR cb;
	cb = *pbstrsResultName;
	listResults::iterator cit;
	cit = find(m_listResults.begin(),m_listResults.end(),cb);
	if (cit!=m_listResults.end())
		(*pVal) = VB_TRUE;
		else
		(*pVal) = VB_FALSE;


	return S_OK;
}


///////////////////////////////////////////////////////////
// Function name	: CNumCatExcelLocalRes::readResultsString
// Description	    : Helper function to convert string into series of results names
// Return type		: void 
// Argument         : const CComBSTR& rcbResults
///////////////////////////////////////////////////////////
void CNumCatExcelLocalRes::readResultsString(const CComBSTR& rcbResults)
{
	long iCount;
	long iRes;
	long iNum;
	long iLen;
	long iLenName;
	CComBSTR cb;
	string sResults;
	wstring swName;
	listResults::iterator cit;
	


	iCount=0;
	
	m_listResults.clear();

	iLen = rcbResults.Length();

	if (iLen<1)
		return;
	
	sResults="";
	while ((iCount<iLen)&&(rcbResults[iCount]!='#'))
		sResults += rcbResults[iCount++];

	iNum = atol(sResults.c_str());

	iRes = 0;
	iCount++;

	while((iRes++<iNum)&&(iCount<iLen))
	{
		sResults = "";
		while ((iCount<iLen)&&(rcbResults[iCount]!='#'))
			sResults += rcbResults[iCount++];
		
		iCount++;
		iLenName = atol(sResults.c_str()) + iCount;
		swName =L"";

		while ((iCount<iLen)&&(iCount<iLenName))
			swName += rcbResults[iCount++];

		cb = swName.c_str();

		cit = find(m_listResults.begin(),m_listResults.end(),cb);
		if (cit==m_listResults.end())
			m_listResults.push_back(cb);
	}

	ATLASSERT(iCount==iLen);

}


///////////////////////////////////////////////////////////
// Function name	: CNumCatExcelLocalRes::updateResultsMap
// Description	    : Helper fucntion to syncronise results map with vector of result names
// Return type		: void 
///////////////////////////////////////////////////////////
void CNumCatExcelLocalRes::updateResultsMap()
{
	wchar_t swTemp[100];
	long iC,iL;
	wstring swLine;
	CComBSTR cb;
	mapItems::iterator it;
	listResults::iterator rit;

	cb.LoadString(IDS_LE_TAG_LISTRESULTSSHEETS);
	it = m_mapItems.find(cb);

	ATLASSERT(it!=m_mapItems.end());
	if (it==m_mapItems.end())
		return;

	_itow(m_listResults.size(),swTemp,10);
	swLine = swTemp;
	swLine += L"#";
	for (rit=m_listResults.begin();rit!=m_listResults.end();rit++)
	{
		iL = rit->Length();
		_itow(iL,swTemp,10);
		swLine += swTemp;
		swLine += L"#";
		for (iC=0;iC<iL;iC++)
			swLine += (*rit)[iC];
	}
	ATLTRACE("swLine = %s\n",swLine.c_str());

	it->second = swLine.c_str();

}


///////////////////////////////////////////////////////////
// Function name	: CNumCatExcelLocalRes::get_LocalSheetName
// Description	    : To help ensure that the sheet name is only given at one place in code !
// Return type		: STDMETHODIMP 
// Argument         : BSTR *pVal
///////////////////////////////////////////////////////////
STDMETHODIMP CNumCatExcelLocalRes::get_LocalSheetName(BSTR *pVal)
{
	CComBSTR cbLocalSheet;

	cbLocalSheet.LoadString(IDS_LE_LOCAL_OPTIONS);


	(*pVal) = cbLocalSheet.Copy();

	return S_OK;
}

STDMETHODIMP CNumCatExcelLocalRes::GetPropertyNumber(BSTR *pbstr, float *pValue)
{
	HRESULT hr;
	CComBSTR cbItem;
	hr = GetPropertyItem(pbstr,&(cbItem.m_str));
	if (SUCCEEDED(hr))
			{
				USES_CONVERSION;
				string str;
				str = OLE2CA(cbItem.m_str);
				(*pValue) = atof(str.c_str());

			}
			else
			{
				(*pValue) = static_cast<float>(NOT_DEFINED);
				return hr;
			}

	return S_OK;
}



///////////////////////////////////////////////////////////
// Function name	: CNumCatExcelLocalRes::SetPropertyNumber
// Description	    : Allows number to be stored up to 6 places
// Return type		: STDMETHODIMP 
// Argument         : BSTR *pbstrKey
// Argument         : float *pValue
// Argument         : VARIANT_BOOL *pvb
///////////////////////////////////////////////////////////
STDMETHODIMP CNumCatExcelLocalRes::SetPropertyNumber(BSTR *pbstrKey, float *pValue, VARIANT_BOOL *pvb)
{
//	int iDec,iSign;
//	CComBSTR cbNum(_fcvt((*pValue),6,&iDec,&iSign));
	char sNum[64];
	_gcvt((*pValue),32,sNum);
	CComBSTR cbNum(sNum);

	return SetPropertyItem(pbstrKey,&(cbNum.m_str),pvb);
}
