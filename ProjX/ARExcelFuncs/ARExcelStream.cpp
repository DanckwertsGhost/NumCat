// ARExcelStream.cpp : Implementation of CARExcelStream
#include "stdafx.h"
#include "ARExcelFuncs.h"
#include "ARExcelStream.h"
#include <string>

#define SAFENAME "SafeName"

#define EXCEL_NOT_IN_COLLECTION       _HRESULT_TYPEDEF_(0x800A03ECL)
#define ROW_EMPTY_LIMIT 7
#define EXCEL_COUNT_LIMIT 65535 // Excel 2007 + may go further, but this is the limit for Excel 2003

/////////////////////////////////////////////////////////////////////////////
// CARExcelStream

CARExcelStream::CARExcelStream():m_eStateExcelStream(streamEmpty),m_eARRHint(readFormatFreeText),m_cbSheet("")
{

	m_ciRowEmpty = 7;
	m_iColEnd = 1; // default
	m_iColStart = 1; // default
	m_iRow = 1; // default
	m_iRowStart = 1; // default
	m_iRowEnd = NOT_DEFINED;
	m_ptrWrkSheet = NULL; // smart pointer for worksheet


	#ifndef NDEBUG
	if (unitTests())
		ATLTRACE("Pass unit tests\n");
		else
		{
		ATLTRACE("Failed unit tests\n");
		ATLASSERT(false);
		}
	#endif

}



///////////////////////////////////////////////////////////
// Function name	: CARExcelStream::InterfaceSupportsErrorInfo
// Description	    : 
// Return type		: STDMETHODIMP 
// Argument         : REFIID riid
///////////////////////////////////////////////////////////
STDMETHODIMP CARExcelStream::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&LIBID_ARSTORELib//IID_IARExcelStream
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CARExcelStream::SetDataSystem(IDispatch * pIDisp, VARIANT_BOOL * pOK)
{
	if ((pOK == NULL)||(pIDisp == NULL ))
			return E_POINTER;


	m_spApp = pIDisp;

	if (m_spApp.p == NULL )
			{
			(*pOK) = VB_FALSE;
			return S_OK;
			}

	(*pOK) = VB_TRUE;

	return S_OK;
}

STDMETHODIMP CARExcelStream::get_StreamState(enumARStream * pVal)
{
	if (pVal == NULL)
		return E_POINTER;

	(*pVal) = m_eStateExcelStream;
			
	return S_OK;
}

STDMETHODIMP CARExcelStream::loadStream(BSTR * pbstrKey, enumARReadHint esrh, enumARStream * pVal)
{
	HRESULT hr;
	string sSafeName;
	string sKey;
	string sLocalR1C1;
	string sTest;
	bool bRangeAssigned = false;

	if ((pVal == NULL)||(pbstrKey == NULL))
		return E_POINTER;

	if (m_spApp==NULL)
		{
		(*pVal) = m_eStateExcelStream = streamEmpty;
		return S_FALSE;
		}


    try
    {
		m_eARRHint = esrh; // to remeber the hint
		m_cbSheet.Empty();

//		m_cbSheet.Attach(*pbstrKey);
		m_cbSheet = (*pbstrKey);


		_variant_t vtsheetName(m_cbSheet.m_str);
		Excel::_WorkbookPtr wb;
		hr = m_spApp->get_ActiveWorkbook(&wb);
		if (!SUCCEEDED(hr))
			{
			(*pVal) = m_eStateExcelStream = streamEmpty;
			return S_FALSE;
			}
		m_ptrWrkSheet = wb->Sheets->GetItem( vtsheetName );

		
		if (m_ptrWrkSheet==NULL) // it won't get this far if it failed to load
			{
			(*pVal) = m_eStateExcelStream = streamEmpty;
			return S_OK;
			}

		(*pVal) = m_eStateExcelStream = streamLoaded; // even if there's nothing there
		
		// see if this stream has a named range already - if so use it coordinates
		// otherwise assume square data layout from top left.
		USES_CONVERSION;

		sKey = OLE2A(m_cbSheet.m_str);
			
		if (getSafeName(sKey,sSafeName))
				{
				Excel::NamesPtr ptrAllNames;
				Excel::NamePtr ptrUsedName;
				string sFullName = sKey;
				sFullName += "!";
				sFullName += sSafeName;
//				_variant_t varSafeName(sSafeName.c_str());
				_variant_t varSafeName(sFullName.c_str());
				_variant_t varLocalR1C1;
//				ptrAllNames = wb->GetNames(); // assume this always succeeds
				ptrAllNames = m_ptrWrkSheet->GetNames(); // assume this always succeeds


//				getNameInWorkSheet(sFullName,ptrUsedName);
/*
				try
				{
					ptrUsedName = ptrAllNames->Item(varSafeName);
				}
				catch(_com_error& e)
				{
				if (e.Error()!=EXCEL_NOT_IN_COLLECTION)
					throw e;	// unexpected - handle this at the next level
				}
*/
				if ((getNameInWorkSheet(sFullName,ptrUsedName))&&(ptrUsedName!=NULL))
					{
					// next is it on the safe sheet ?
					varLocalR1C1 = ptrUsedName->RefersToR1C1Local; // this should return vtBSTR
					sLocalR1C1 = OLE2A(varLocalR1C1.bstrVal);

					bRangeAssigned = findRangeLimits(sLocalR1C1,m_iColStart,m_iColEnd,m_iRowStart,m_iRowEnd,sKey);

					}

				}

		// if we haven't been able to find the range limits then find them from scratch, then assign new name.
		if (!bRangeAssigned)
			{
			
			m_iRowStart = 1; // by default
			establishLimitsOfRange(m_iColStart,m_iColEnd,m_iRowStart,m_iRowEnd);
			if ((m_iColEnd-m_iColStart > 1)&&(sSafeName.size()>0)) // don't do this for single columns
				assignNameRange(sSafeName,m_iColStart,m_iColEnd,m_iRowStart,m_iRowEnd);			

			} // end 

		m_iRow = m_iRowStart;

#ifdef OLD_DEBUGCASE_BEING_USED  // this code related to a particular test sheet - I'm leaving it in as it shows some techniques that could eb useful
 		// can we find a range on that sheet with the safe name ?
		Excel::NamesPtr ptrNames;
		Excel::NamePtr ptrName;
//		CComQIPtr<Excel::INames> pqiNames;
		Excel::RangePtr ptrRange;
		_variant_t varName("woof");
		_variant_t varFirstName("FirstName");
		_bstr_t sbstr;

		ptrNames = wb->GetNames();
		ptrNames = wb->Names;

		if (ptrNames)
			ATLTRACE("ptrNames Names count %d\n",ptrNames->Count);

//		pqiNames = ptrNames.GetInterfacePtr();
		
//		if (pqiNames)
//			ATLTRACE("Names count %d\n",pqiNames->Count);	
			
		long iT;
		for (iT=1;iT<=ptrNames->Count;iT++)
			{
			ptrName = ptrNames->Item(iT);
			varName = ptrName->Value;
//			ptrName->GetName(&sbstr);
			sbstr = ptrName->NameLocal;
			varName = ptrName->RefersToLocal;
			varName = ptrName->RefersToR1C1Local;
			varName = ptrName->RefersTo;
			varName = ptrName->RefersToR1C1;
			ATLTRACE("Count [%d], Name = [%s], RefR1C1 = [%s]\n",iT,OLE2A(sbstr),OLE2A(varName.bstrVal));
			ptrRange = ptrName->RefersToRange;
			}
		try // this code is just for development and relates to a specific sheet
		{
		ptrName = ptrNames->Item(varFirstName);
		ptrName = ptrNames->Item(varName);
		}
		catch( _com_error& e)
		{
		hr = e.Error();
		ATLTRACE("%X %s\n",e.Error(),e.ErrorMessage());
		if (hr!=EXCEL_NOT_IN_COLLECTION)
			throw e;	
				
		}	
#endif // def OLD_DEBUGCASE_BEING_USED



	}
	catch( _com_error& e )
    {
		// ERROR REPORT HERE
		(*pVal) = m_eStateExcelStream = streamEmpty;
		hr = SetErrorInfo(0,e.ErrorInfo());
	//	_resetstkoflw; // in case of overflow issue with XP see http://msdn.microsoft.com/en-us/library/89f73td2(v=vs.71).aspx
		return hr;
    }
    catch( ... )
    {
		(*pVal) = m_eStateExcelStream = streamEmpty;
	//	_resetstkoflw; // in case of overflow issue with XP see http://msdn.microsoft.com/en-us/library/89f73td2(v=vs.71).aspx
		return E_FAIL;
    }
			
	return S_OK;
}

#define _BUFF_LENGTH 64

STDMETHODIMP CARExcelStream::readLine(BSTR * pbstrLine)
{

	char sBuff[_BUFF_LENGTH+4];

	if (pbstrLine == NULL)
		return E_POINTER;


	try
	{
	long iC;

	USES_CONVERSION;

	CComBSTR cbLine(_T(""));
	string sLine;
	string sStr;

	if ((m_iRow>m_iRowEnd)||(m_iRow<m_iRowStart))
		{
		m_eStateExcelStream = streamFail;
		(*pbstrLine) = SysAllocString(cbLine);
		return E_FAIL;

		}



	switch(m_eStateExcelStream) // check only appropriate states go forward
	{
		case streamLoaded:
		case streamReadline:
			// ok can go ahead
			break;
		default:
			// cannot go ahead - but must return the BSTR
			(*pbstrLine) = SysAllocString(cbLine);
			return S_FALSE;
	}

    if (m_ptrWrkSheet==NULL)
		{
		(*pbstrLine) = SysAllocString(cbLine);
		m_eStateExcelStream = streamFail;
		return E_FAIL;
		}

	// need to assign sLine

	try
	{
	_variant_t varCell;
	Excel::RangePtr ptrRange;
	Excel::RangePtr ptrCells;
	_variant_t varX;
	_variant_t	varY(m_iRow);
	ATLASSERT(m_ptrWrkSheet!=NULL); // since this should just not happen

	ptrCells = m_ptrWrkSheet->Cells; // avoid repeated calls

	for (iC=m_iColStart;iC<=m_iColEnd;iC++)
		{
		varX = iC;		
		ptrRange = ptrCells->GetItem(varY,varX);
		varCell = ptrRange->Value2;

		switch(varCell.vt)
			{
			case VT_R8:
						sStr = gcvt(varCell.dblVal,_BUFF_LENGTH,sBuff);
						removeTrailingPoint(sStr);
						sLine += sStr;
						break;
			case VT_R4:
						sStr = gcvt(varCell.fltVal,_BUFF_LENGTH,sBuff);
						removeTrailingPoint(sStr);
						sLine += sStr;
						break;
			case VT_I4:
						sLine += ltoa(varCell.lVal,sBuff,10);
						break;
			case VT_I2:
						sLine += itoa(varCell.iVal,sBuff,10);
						break;
			case VT_BSTR:
						sLine += OLE2A(varCell.bstrVal);
						break;
			case VT_DATE:
			case VT_CY: // currentcy
							ATLTRACE("Currency or Date found in cell - not handled here\n");
							ATLASSERT(false);
			case VT_EMPTY:
			default:
						sLine += "";
			break;
			}
		if (iC<m_iColEnd)
			sLine += ",";

		}
		
		cbLine = sLine.c_str();
		(*pbstrLine) = SysAllocString(cbLine);

	}
	catch( _com_error& e )
	{
	(*pbstrLine) = SysAllocString(e.Description());
	m_eStateExcelStream = streamFail;

	return e.Error();
	}

	if (++m_iRow>m_iRowEnd)
		m_eStateExcelStream = streamEnd;
		else
		m_eStateExcelStream = streamReadline;

	return S_OK;
	}
	catch(...)
	{
	USES_CONVERSION;
	(*pbstrLine) = SysAllocString(T2COLE("<internal error> Unhandled failure reading stream - please report."));
	m_eStateExcelStream = streamFail;
	return E_FAIL;
	}
	return S_FALSE;

/* // VBA equivalent
Private Function IARStream_readLine() As String
    Dim iCount As Long
    
    m_iRC = m_iRC + 1
    
    If m_iRC > iCountLimit Then
                IARStream_readLine = "//<Beyond limit of rows at " & iCountLimit & ">"
                sLogPrint "<Warning> Exceed row limit"
                iRow = iRow + 1
                ess = streamEnd
                Exit Function
                End If
                
    sLogPrint "Line " & m_iRC, eTrace2
    
    If ess <> streamLoaded And ess <> streamReadline Then
                IARStream_readLine = ""
                Else
                iCount = iColStart
                Do While (iCount <= iColEnd)
                        IARStream_readLine = IARStream_readLine & sht.Cells(iRow, iCount)
                        If (iColEnd > iColStart) Then 'its a CSV
                                IARStream_readLine = IARStream_readLine & ","
                                End If
                        iCount = iCount + 1
                Loop
               iRow = iRow + 1
               If iRow > iRowEnd Then
                        ess = streamEnd
                        Else
                        ess = streamReadline
                        End If
                End If
 
End Function

*/
}


///////////////////////////////////////////////////////////
// Function name	: CARExcelStream::findLastRow
// Description	    : 
// Return type		: long - return NOT_DEFINED on error
// Argument         : long iFirstRow /*=1*/
///////////////////////////////////////////////////////////
long CARExcelStream::findLastRow( long iFirstRow /*=1*/ )
{

	// if a range is defined for this sheet then just return the end of it
	bool bResult = false;
	const long ciRowEmpty = ROW_EMPTY_LIMIT;
	const long ciCountLimit = EXCEL_COUNT_LIMIT;
	long iLast = iFirstRow;
	long iCount = iFirstRow;
	long iCountBlank =0;

	ATLASSERT(iFirstRow>0);

	if (iFirstRow<1)
		return NOT_DEFINED;

	if ((m_eStateExcelStream!=streamLoaded)&&(m_eStateExcelStream!=streamReadline))
		return NOT_DEFINED; // we're just not doing this


	try
	{
	long iCol=1;
	long iRow=1;
	_variant_t varCell;
	Excel::RangePtr ptrRange;
	Excel::RangePtr ptrCells;
	_variant_t varX(iCol);
	_variant_t	varY(iRow);
	ATLASSERT(m_ptrWrkSheet!=NULL); // since this should just not happen
	if (m_ptrWrkSheet==NULL) // but just in case
		return NOT_DEFINED;

	ptrCells = m_ptrWrkSheet->Cells; // so don't interogate m_ptrWrkSheet every loop

	while( (iCountBlank< ciRowEmpty)&&(iCount<ciCountLimit))
		{
		varY = iCount;
		ptrRange = ptrCells->GetItem(varY,varX);
		varCell = ptrRange->Value2;


		if (varCell.vt==VT_EMPTY)
				{
				iCountBlank++;
				}
				else
				{
				iCountBlank=0;
				iLast = iCount;
				}
		iCount++;
		}

	}
	catch( _com_error& )
	{

		return NOT_DEFINED;

	}

	return iLast;

}


///////////////////////////////////////////////////////////
// Function name	: CARExcelStream::getSafeName
// Description	    : static helper fucntion that returns  a SafeName
//                    for a given name
//					  These names are safe as use for a range name in Excel
//                    This is necessary as Excel 2003 and maybe others won't allow
//                    some chartacters to be used in ranges.
// Return type		: bool - if returns false if default name used
// Argument         : const string& sFullName
// Argument         : string& sSafeName
///////////////////////////////////////////////////////////
bool CARExcelStream::getSafeName( const string& sFullName, string& sSafeName )
{

	long iT;
	int iAsc;

ATLTRACE("%s\n",sFullName.c_str());

	sSafeName.erase(); // just to be sure

	for (iT=0;iT<sFullName.length();iT++)
		{
		iAsc = sFullName[iT];
ATLTRACE("%s",sFullName.substr(iT,1).c_str());

		if ((iAsc>64)&&(iAsc<91)) // between A and Z
				sSafeName.append(sFullName.substr(iT,1));
				else
				if ((iAsc>96)&&(iAsc<123)) // between a and z
						sSafeName.append(sFullName.substr(iT,1));
						else
						if ((iAsc>47)&&(iAsc<58)) // between 0 and 9
								sSafeName.append(sFullName.substr(iT,1));
		}
ATLTRACE("\n");
ATLTRACE("%s\n",sSafeName.c_str());

	if (sSafeName.length()==0)
		{
		sSafeName = SAFENAME;
		return false;
		}

	return true;

}

#ifndef NDEBUG
///////////////////////////////////////////////////////////
// Function name	: CARExcelStream::unitTests
// Description	    : DEBUG only
// Return type		: bool 
///////////////////////////////////////////////////////////
bool CARExcelStream::unitTests()
{

	bool bResult = true;
	long iColStart = NOT_DEFINED;
	long iColEnd = NOT_DEFINED;
	long iRowStart = NOT_DEFINED;
	long iRowEnd = NOT_DEFINED;

	string sTest = "Woofer_123";
	string sKey;
	string sResult;

	getSafeName(sTest,sResult);
	ATLTRACE("%s -> %s\nDone\n",sTest.c_str(),sResult.c_str());
	bResult &= (sResult.compare("Woofer123")==0);

	sTest = "__$££$$@";
	getSafeName(sTest,sResult);
	ATLTRACE("%s -> %s\nDone\n",sTest.c_str(),sResult.c_str());
	bResult &= (sResult.compare(SAFENAME)==0);

	sTest = "AZaz10##";
	getSafeName(sTest,sResult);
	ATLTRACE("%s -> %s\nDone\n",sTest.c_str(),sResult.c_str());
	bResult &= (sResult.compare("AZaz10")==0);

	sTest="=Sheet1!R1C4:R4C7";
	bResult &= findRangeLimits(sTest,iColStart,iColEnd,iRowStart,iRowEnd);
	bResult &= (iColStart==4);
	bResult &= (iColEnd==7);
	bResult &= (iRowStart==1);
	bResult &= (iRowEnd==4);

	sKey="Sheet1";
	bResult &= findRangeLimits(sTest,iColStart,iColEnd,iRowStart,iRowEnd,sKey);
 
	sTest="=Sheet1!R9C4:R4C7"; // error in ref
	bResult &= !findRangeLimits(sTest,iColStart,iColEnd,iRowStart,iRowEnd);


	sTest="=Sheet1R1C4:R4C7"; // error in ref
	bResult &= !findRangeLimits(sTest,iColStart,iColEnd,iRowStart,iRowEnd);

	sTest="=Sheet1!R1C4:R4C700";
	bResult &= findRangeLimits(sTest,iColStart,iColEnd,iRowStart,iRowEnd);
	bResult &= (iColEnd==700);
	
	sTest="=Sheet1!R1C4";
	iColStart = -456;
	bResult &= !findRangeLimits(sTest,iColStart,iColEnd,iRowStart,iRowEnd);
	bResult &= (iColStart==-456);

	sTest = "100";
	sResult = "100";
	removeTrailingPoint(sTest);
	bResult &= (sTest.compare(sResult)==0);

	sTest = "1";
	sResult = "1";
	removeTrailingPoint(sTest);
	bResult &= (sTest.compare(sResult)==0);

	sTest = "1.";
	sResult = "1";
	removeTrailingPoint(sTest);
	bResult &= (sTest.compare(sResult)==0);

	sTest = "1.0";
	sResult = "1.0";
	removeTrailingPoint(sTest);
	bResult &= (sTest.compare(sResult)==0);

	return bResult;
}

#endif


///////////////////////////////////////////////////////////
// Function name	: CARExcelStream::findRangeLimits
// Description	    : Helper function that returns range limits for a named range
//                    given in =sheet!R1C1:R9C9 format
// Return type		: bool - returns true if format could be read and values assigned, else returns false
// Argument         : string sAddr
// Argument         : long &iColStart - value changed in range can be established
// Argument         : long &iColEnd - as above
// Argument         : long &iRowStart - as above
// Argument         : long &iRowEnd - as above
// Argument         : string sKey = "" optional
///////////////////////////////////////////////////////////
bool CARExcelStream::findRangeLimits(string sAddr, long &iColStart, long &iColEnd, long &iRowStart, long &iRowEnd, string sKey)
{

	bool bResult = false;
	string sLocalR1C1 = sAddr;

	sLocalR1C1 = sLocalR1C1.substr(1,sLocalR1C1.size()-1);

	ATLTRACE("sKey = [%s], sLocalR1C1.substr(0,sKey.size()) = [%s]\n",sKey.c_str(),sLocalR1C1.substr(0,sKey.size()).c_str());

					
		if ((sKey.size()==0)||(sKey.compare(sLocalR1C1.substr(0,sKey.size()))==0))
							{
							long iPos;
							long iX;

							iPos = sLocalR1C1.find(":");
							// is there a range here ?
							if (iPos!=string::npos ) // only do this if we have a range
								{

								iX = sLocalR1C1.find("!");

								if (iX!=string::npos)
									{
									sLocalR1C1 = sLocalR1C1.substr(iX+1);

									if (sLocalR1C1.size()>0)
										{
										long iC;
										iPos -= iX+1;
										ATLASSERT(iPos>0);
										string sFrom = sLocalR1C1.substr(0,iPos); 
										string sTo = sLocalR1C1.substr(iPos+1);
					
										iC = sFrom.find("C");
										ATLASSERT(iC!=string::npos);					
										iRowStart = atol(sFrom.substr(1,iC-1).c_str());
										iColStart = atol(sFrom.substr(iC+1).c_str());

										iC = sTo.find("C");
										ATLASSERT(iC!=string::npos);					
										iRowEnd = atol(sTo.substr(1,iC-1).c_str());
										iColEnd = atol(sTo.substr(iC+1).c_str());

										if ((iRowStart<=iRowEnd)&&
										    (iColStart<=iColEnd)&&
											(iRowStart)&&
											(iRowEnd)&&
											(iColStart)&&
											(iColEnd))										
													bResult = true;
										}
									}
								}

							}
							#ifndef NDEBUG
							else
							{ // we have a problem
							ATLTRACE("Key and sheet don't match: Key %s, NamedKey %s\n",sKey.c_str(),sLocalR1C1.substr(0,sKey.size()).c_str());
							}
							#endif

	return bResult;


}


///////////////////////////////////////////////////////////
// Function name	: CARExcelStream::establishLimitsOfRange
// Description	    : By inspecting the sheet establish limits on range
// Return type		: bool 
// Argument         : long &iColStart
// Argument         : long &iColEnd
// Argument         : long &iRowStart
// Argument         : long &iRowEnd
///////////////////////////////////////////////////////////
bool CARExcelStream::establishLimitsOfRange( long &iColStart, long &iColEnd, long &iRowStart, long &iRowEnd)
{

	long iAnsRowEnd;
	long iAnsColEnd;

	iAnsRowEnd = this->findLastRow(iRowStart);

	if (iAnsRowEnd==NOT_DEFINED)
				return false;


	iAnsColEnd = this->findFarRightColumn(iRowStart,iAnsRowEnd,iColStart);

	if (iAnsColEnd==NOT_DEFINED)
				return false;

	ATLTRACE("Last Row = %d, LastCol = %d\n",iAnsRowEnd,iAnsColEnd);

	// make changes now
	iRowEnd = iAnsRowEnd;
	iColEnd = iAnsColEnd;

	return true;
}


///////////////////////////////////////////////////////////
// Function name	: CARExcelStream::findFarRightColumn
// Description	    : helper function to find the furthest right column
//                    for last row given
// Return type		: long - return NOT_DEFINED if unable to locate
// Argument         : long iFirstRow
// Argument         : long iLastRow
// Argument         : long iFirstCol /*=1*/
///////////////////////////////////////////////////////////
long CARExcelStream::findFarRightColumn(long iFirstRow, long iLastRow, long iFirstCol /*=1*/ )
{
	const long ciCountLimit = EXCEL_COUNT_LIMIT;
	long iCol = iFirstCol;
	long iRow = iFirstRow;
	long iLast = NOT_DEFINED;
	long iLastCol = NOT_DEFINED;
	bool bEndOfRow = false;

	// assumed that last row has already been found
	if (iLastRow==NOT_DEFINED)
			return NOT_DEFINED; // as there's nothing doing

	ATLASSERT(iFirstCol>0);

	if (iFirstCol<1)
		return NOT_DEFINED;

	if ((m_eStateExcelStream!=streamLoaded)&&(m_eStateExcelStream!=streamReadline))
		return NOT_DEFINED; // we're just not doing this

	// count right to find limit on first row

	try
	{
	_variant_t varCell;
	Excel::RangePtr ptrRange;
	Excel::RangePtr ptrCells;
	_variant_t varX;
	_variant_t	varY(iRow);
	ATLASSERT(m_ptrWrkSheet!=NULL); // since this should just not happen
	if (m_ptrWrkSheet==NULL) // but just in case
		return NOT_DEFINED;

	ptrCells = m_ptrWrkSheet->Cells; // avoid repeated calls

	while(iRow<=iLastRow)
		{
		bEndOfRow = false;
		varY = iRow;
		iLast= iCol = iFirstCol;
		while((!bEndOfRow)&&(iCol<ciCountLimit))
			{
			varX = iCol;
			ptrRange = ptrCells->GetItem(varY,varX);
			varCell = ptrRange->Value2;

			if (varCell.vt==VT_EMPTY)
					bEndOfRow = true;
					else
					{
					iLast = iCol;
					if ((iLastCol!=NOT_DEFINED)&&(iCol>=iLastCol)) // then no further
							bEndOfRow = true;
					}
			iCol++;
			}
		if ((iLastCol==NOT_DEFINED)||(iLast<iLastCol))
			iLastCol = iLast;
		iRow++;
		}

	}
	catch( _com_error& )
	{

		return NOT_DEFINED;

	}


	return iLastCol;
}


///////////////////////////////////////////////////////////
// Function name	: CARExcelStream::assignNameRange
// Description	    : 
// Return type		: void 
// Argument         : const string &sSafeName
// Argument         : long iColStart
// Argument         : long iColEnd
// Argument         : long iRowStart
// Argument         : long iRowEnd
///////////////////////////////////////////////////////////
void CARExcelStream::assignNameRange(const string &sSafeName, long iColStart, long iColEnd, long iRowStart, long iRowEnd)
{
	// first check the basics

	if (iColStart==iColEnd)
		return; // don't assign names to single columns - this protects columns used for code


	ATLASSERT(iColStart<iColEnd);
	ATLASSERT(iRowStart<=iRowEnd);

	if (iRowStart>iRowEnd)
		return;

	ATLASSERT(m_ptrWrkSheet!=NULL);

	if ((m_ptrWrkSheet==NULL)||((m_eStateExcelStream==streamEmpty)||(m_eStateExcelStream==streamFail)))
		return;

	try
	{

		Excel::NamesPtr ptrNames;
		Excel::NamePtr ptrName;
		string sbName;
		string sbLocationR1C1;
		char sBuffer[32];

		USES_CONVERSION;

		sbName = "'";
		sbName += OLE2A(m_cbSheet.m_str);
		sbName += "'!";
		sbName += sSafeName.c_str();

//    sRange = "='" & sht.name & "'!R1C1:R" & iRowEnd & "C" & iColRight


		sbLocationR1C1 = "='";
		sbLocationR1C1 += OLE2A(m_cbSheet.m_str);

		sbLocationR1C1 += "'!R";
	    _itoa( iRowStart, sBuffer, 10 );
		sbLocationR1C1 += sBuffer;
		sbLocationR1C1 += "C";
	    _itoa( iColStart, sBuffer, 10 );
		sbLocationR1C1 += sBuffer;

		sbLocationR1C1 += ":R";
	    _itoa( iRowEnd, sBuffer, 10 );
		sbLocationR1C1 += sBuffer;
		sbLocationR1C1 += "C";
	    _itoa( iColEnd, sBuffer, 10 );
		sbLocationR1C1 += sBuffer;

		ptrNames = m_ptrWrkSheet->GetNames();

//Look at adding normal string calcs ( not sure how strings are working here - unless they are instiating _variant_t's before being passed. )

		ptrName = ptrNames->Add(sbName.c_str(),vtMissing,VARIANT_TRUE,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,sbLocationR1C1.c_str(),vtMissing);
/*
    NamePtr Add (
        const _variant_t & Name = vtMissing,
        const _variant_t & RefersTo = vtMissing,
        const _variant_t & Visible = vtMissing,
        const _variant_t & MacroType = vtMissing,
        const _variant_t & ShortcutKey = vtMissing,
        const _variant_t & Category = vtMissing,
        const _variant_t & NameLocal = vtMissing,
        const _variant_t & RefersToLocal = vtMissing,
        const _variant_t & CategoryLocal = vtMissing,
        const _variant_t & RefersToR1C1 = vtMissing,
        const _variant_t & RefersToR1C1Local = vtMissing );
*/

	}
	catch( _com_error& e)
	{
	ATLTRACE("_com_error [%s] thrown and caught in CARExcelStream::assignNameRange\n",e.ErrorMessage());
	}

}



///////////////////////////////////////////////////////////
// Function name	: CARExcelStream::getNameInWorkSheet
// Description	    : Helper function that finds a name in the names
//                    of the workbook stored in the object.
// Return type		: bool - true is succeeded, otherwise false
// Argument         : string sName
// Argument         : Excel::NamePtr& rptrName - value assigned if true
///////////////////////////////////////////////////////////
bool CARExcelStream::getNameInWorkSheet( string sName, Excel::NamePtr& rptrName)
{

	Excel::NamePtr ptrName;
	Excel::NamesPtr ptrNames;
	long iCount;
	long iT;
	_bstr_t sbstr;
	bool bResult = false;

	USES_CONVERSION;


	ATLASSERT(m_ptrWrkSheet!=NULL);
	if (m_ptrWrkSheet==NULL)
			return false;

	try
	{
		ptrNames = m_ptrWrkSheet->GetNames(); // assume this always succeeds
		iCount = ptrNames->Count;

		iT=1; // names run from index 1
		while((!bResult)&&(iT<=iCount))
			{
			ptrName = ptrNames->Item(iT);
			sbstr = ptrName->NameLocal;
			if (sName.compare(OLE2A(sbstr))==0)
					bResult = true;
			iT++;
			}

		if (bResult)
			rptrName = ptrName;
			else
			rptrName = NULL; // necessary in case it did point to something as false implies it doesn't anymore

#ifndef NDEBUG
		if (bResult)
			{
			_variant_t var = rptrName->RefersToR1C1Local;
			ATLTRACE("Index [%d], search name = [%s], name [%s]",(iT-1),sName.c_str(),OLE2A(sbstr));
			ATLTRACE(", RefersToR1C1Local [%s]\n",OLE2A(var.bstrVal));



			}

#endif

	}
	catch( _com_error& e)
	{
		ATLTRACE("_com_error [%s] thrown and caught in CARExcelStream::getNameInWorkSheet\n",e.ErrorMessage());		
		return false;
	}

	return bResult;
}

void CARExcelStream::removeTrailingPoint(string &rsString)
{
	long iLen = rsString.length();

	if (iLen<2)
		  return;

	ATLTRACE("String = [%s], length = [%d], length-1 = [%d]",rsString.c_str(),rsString.length(),rsString.length()-1);
	ATLTRACE(", substring = [%s]\n",rsString.substr(0,rsString.length()-1).c_str());

	if (rsString.substr(iLen-1).compare(".")==0)
		rsString = rsString.substr(0,iLen-1);

	ATLTRACE(" string afterwards = [%s]\n",rsString.c_str());
}

STDMETHODIMP CARExcelStream::gotoFirstLine(enumARStream * pVal)
{
	if (pVal == NULL)
		return E_POINTER;

	switch(m_eStateExcelStream)
	{
		case streamLoaded:
		case streamReadline:
			m_iRow = m_iRowStart;

			break;
		case streamEnd:
			m_iRow = m_iRowStart;
			m_eStateExcelStream = streamReadline;
			break;
		default:
			(*pVal) = m_eStateExcelStream;
			return S_FALSE;
			break;
	}

	(*pVal) = m_eStateExcelStream;
			
	return S_OK;
}

///////////////////////////////////////////////////////////
// Function name	: CARExcelStream::lastLineExtra
// Description	    : This does nothing for this Excel reader - but may be supported
//                    by other users of the interface
// Return type		: STDMETHODIMP 
// Argument         : [in] enumARIODataType esType
// Argument         : [out,retval] BSTR *pbstr
///////////////////////////////////////////////////////////
STDMETHODIMP CARExcelStream::lastLineExtra(enumARIODataType esType, BSTR *pbstr)
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



STDMETHODIMP CARExcelStream::get_Version(float *pVal)
{
	if (pVal == NULL)
		return E_POINTER;

	(*pVal) = 0.1F;

	return S_OK;
}

STDMETHODIMP CARExcelStream::TestCallOne(IDispatch *pIDisp, VARIANT_BOOL *pVal)
{
	// TODO: Add your implementation code here

	return SetDataSystem(pIDisp,pVal);
}
