// SymEdErrList.cpp: implementation of the CSymEdErrList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SymEdErrList.h"





LRESULT CSymEdErrList::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{

	m_hwndEditor = NULL;
	LRESULT bResult = DefWindowProc(uMsg,wParam,lParam);
	vector<CErrorRecord>::iterator it;
	int iErrorCount = 0;

	if (m_vecER.size()>0)
		{
		for (it=m_vecER.begin();it!=m_vecER.end();it++)
			this->InsertItem(iErrorCount++,it->getErrorStr());
		ATLASSERT(m_vecER.size()==iErrorCount);

		}
	// temporary debug
//	this->InsertItem(0,"Hello Mum");
//	this->InsertItem(1,"Woof_Woof"); 

	// find all the relevant errors
/*	if (m_pIErrorRun)
		{
		USES_CONVERSION;
		long iCount,iSize;
		long iLBnd,iUBnd;
		UINT iC;
		CErrorRecord cer;
		SAFEARRAY* pSAErrors = NULL; 
		INumCatError** prgn =0;
		HRESULT hr = m_pIErrorRun->get_CountErrors(&iCount);

		HANDLE_HR_FAILURE(hr)
		
		hr = m_pIErrorRun->GetAllErrors(&pSAErrors);

		HANDLE_HR_FAILURE(hr)

		hr = SafeArrayAccessData(pSAErrors,(void**)&prgn);
		
		HANDLE_HR_FAILURE(hr)

		iSize = SafeArrayGetElemsize(pSAErrors);

		hr = SafeArrayGetLBound(pSAErrors,1,&iLBnd);

		HANDLE_HR_FAILURE(hr)

		hr = SafeArrayGetUBound(pSAErrors,1,&iUBnd);
		
		HANDLE_HR_FAILURE(hr)

		BSTR bstrName = NULL;
		BSTR bstrDescr = NULL;
		long iLine;
		long iX;
		int iErrorCount = 0;
		m_vecER.clear();
		enumNumCatErrorCode esec;
		string sString;

		for (iC=0;iC<iCount;iC++)
			{
			 hr = prgn[iC]->get_StreamName(&bstrName);

			 string sString = OLE2CA(bstrName);

			 cer.setFileName( sString.c_str() );

			 if (SUCCEEDED(hr))
				{
				 hr = prgn[iC]->get_Description(&bstrDescr);

				 if (SUCCEEDED(hr))
					{
					 hr = prgn[iC]->get_ErrCode(&esec);
					 if ((SUCCEEDED(hr))&&(esec==errSyntax)) // ignore the other errors
						{
						 hr = prgn[iC]->get_Line(&iLine);
						 if (SUCCEEDED(hr))
							{
							hr = prgn[iC]->get_XPosition(&iX);
							if (m_sOpenStreamName.compare(cer.getFileName())==0) // then its OK
								{
								// do this stuff only if its going to be used
								sString = OLE2CA(bstrDescr);
								cer.setDesc( sString.c_str());
								cer.setCode(esec);
								cer.setLine(iLine+1); // +1 to get into lines from row 1 not zero
								cer.setX(iX);

								this->InsertItem(iErrorCount++,cer.getErrorStr());
								m_vecER.push_back(cer);
								ATLASSERT(m_vecER.size()==iErrorCount);
								}
							}
						}
					 SysFreeString(bstrDescr);
					}
				 SysFreeString(bstrName);
				}

			
			 			
			 if (FAILED(hr)) // for debug
					{
					ATLTRACE("Failed here %s %s\n",__FILE__,__LINE__);
					}

			} // end of for loop
		hr = SafeArrayUnaccessData(pSAErrors);

		HANDLE_HR_FAILURE(hr)

		hr = SafeArrayDestroy(pSAErrors); // this calls Release() on each SAFEARRAY member - so no need to do here

		HANDLE_HR_FAILURE(hr)

		}*/
	
	return bResult;
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


