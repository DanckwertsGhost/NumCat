// ARRunProgress.cpp : Implementation of CARRunProgress
#include "stdafx.h"
#include "Symlix.h"
#include "ARRunProgress.h"
#include <process.h>
#include "ErrorFactory.h"

#ifndef NDEBUG
#define TRACKS
#endif


#ifdef TRACKS
#include <iostream>

ofstream* osd;

#endif


#ifdef TRACKS
#define OST( text ) \
	if ((osd)&&(osd->is_open())) \
						(*osd) << text << endl;
#else
#define OST( text ) \
	//
#endif

// CLOSEDLGTHREAD() macro used to ensure a common approach to closing the dialog thread
#define CLOSEDLGTHREAD() \
		{ arruninfo.SendSafeMessage(WM_CLOSE); \
		arruninfo.AttachProgText("closing..."); \
		if (arruninfo.m_DlgHwnd) \
				{ \
				OST("SendMessage(arruninfo.m_DlgHwnd,WM_CLOSE,NULL,NULL)") \
				SendMessage(arruninfo.m_DlgHwnd,WM_CLOSE,NULL,NULL); } \
		ATLTRACE("m_hEndEvent = %d\n",m_hEndEvent); \
		DWORD dwState = WaitForSingleObject( m_hEndEvent, 4000 ); \
		if (dwState==WAIT_TIMEOUT) \
		{ \
			dwState = WaitForSingleObject( m_hEndEvent, 2000 ); \
		} \
		m_pARRunInfo=NULL;}

//			::MessageBox(NULL,"A software error has occured when closing the run dialog down. Will pause for 4 secs to force close down after click OK.","Symlix",MB_OK|MB_ICONEXCLAMATION); \

#ifdef TRACKS
#define OSTEXIT() \
	if ((osd)&&(osd->is_open())) \
						(*osd) << "<<exit>>" << endl; \
	if (osd) \
		{ \
		osd->close(); \
		delete osd; \
		osd = NULL; \
		} 
#else
#define OSTEXIT() \
	//
#endif


bool CARRunInfo::bContinue = false;


//#define TESTWIN

void ARRunWindowThread( void* pParams )
  { 
	try
	{ // need to control scope here
	CSymRunProgressDlg winProg; // progress dialog

	OST("CSymRunProgressDlg winProg just initialised as a object")


//	long iCount;

	CARRunInfo* pari = ((static_cast<CARRunInfo*>(pParams)));
//	CCritCheck(sri.m_pHostSymlix->m_csSimulationRunning); // safeguard
//	iCount = sri.m_pHostSymlix->AddRef();
	ATLTRACE("@@@ Start ARRunWindowThread \n");

	winProg.PreCreate(pari); // so the window has access also
	

	if (!(CARRunInfo::bContinue)&&(pari)) // only if not already running - can't run twice
	{			
		// change in running status need to be protected
		{
		CCritCheck cc(pari->m_rCritSec);
		(CARRunInfo::bContinue) = true;
		}



		{ // now for the Windows bit
	//		HWND hwnd;


	/*		hwnd = ari.m_rwinProg.Create(NULL);
			if(!hwnd)
			{
				ATLTRACE(_T("Main window creation failed!\n"));
				MessageBox(NULL,_T("Failed to create Progress Dialog"),_T("Symlix"),MB_OK|MB_ICONERROR);
				SetEvent( ari.m_hEvent1 ); // all data copied
				SetEvent(ari.m_hEndEvent); // its the end
				_endthread();
			}*/
			
	//		ari.m_rwinProg.ShowWindow(SW_SHOWDEFAULT);
			ATLTRACE("@about to set m_hEvent1\n");
			SetEvent( pari->m_hEvent1 ); // all data copied

	/*		if (ari.m_hosthWnd)
				ari.m_rwinProg.DoModal(ari.m_hosthWnd);
				else
				ari.m_rwinProg.DoModal(); // some earlier versions of Excel are unable to supply hwnd info
	*/

			winProg.DoModal();//.ShowWindow(SW_SHOWDEFAULT);

			OST("About to call winProg.PostClose();")

			winProg.PostClose(); // so the window has access also


			ATLTRACE("@Dialog closed\n");


			CARRunInfo::bContinue =false; // so another window can be created

		}

	}// end test for running window


	ATLTRACE("@About to set m_hEndEvent\n");
	SetEvent(pari->m_hEndEvent); // its the end
	OST("@@@Set m_hEndEvent, End ARRunThread _endthread() and release")
	ATLTRACE("@@@End ARRunThread _endthread() and release\n");
	} // end of attempt to control scope
	catch(...)
	{
	ATLTRACE("Unhandled exception in ARRunWindowThread thread\n");
#ifndef NDEBUG
	::MessageBox(NULL,"Unhandled exception caught in ARRunWindow thread","Symlix debug message",MB_OK|MB_ICONEXCLAMATION);
#endif
	}
	OST("@@CSymRunProgressDlg out of scope")
	_endthread();
  };

/////////////////////////////////////////////////////////////////////////////
// CARRunProgress

STDMETHODIMP CARRunProgress::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IARRunProgress
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


///////////////////////////////////////////////////////////
// Function name	: CARRunProgress::RunModel
// Description	    : 
// Return type		: STDMETHODIMP 
// Argument         : int ihwnd
// Argument         : INumCat *pINumCat
// Argument         : IARDataStore *pIStore
// Argument         : BSTR *pbstrRunName
// Argument         : VARIANT_BOOL bShow
// Argument         : VARIANT_BOOL *pbSuccess
///////////////////////////////////////////////////////////
STDMETHODIMP CARRunProgress::RunModel(int ihwnd, INumCat *pINumCat, IARDataStore *pIStore, BSTR *pbstrRunName, VARIANT_BOOL bShow, VARIANT_BOOL *pbSuccess)
{
	
#ifdef TRACKS
	osd = new ofstream;
	if (osd)
		osd->open("traceThread.txt");	
#endif

	OST("Test line");
	
	// First up lets check the data thats being passed here
	vector<string> vecVarNames; // going to need a copy
	

	if (!pbSuccess)
		return Error(_T("Failure to defined return type"));

	*pbSuccess=VB_FALSE;
	if (!pINumCat)
		return Error(_T("No model passed to Run"));

	if (!pIStore)
		return Error(_T("No data store passed to Run"));

	if ((!pbstrRunName)||(!*pbstrRunName))
		return Error(_T("No model name passed to Run"));

#ifdef NDEBUG
	pINumCat->AddRef();
	pIStore->AddRef();
#else
	ATLTRACE("%d = pINumCat->AddRef()\n",pINumCat->AddRef());
	ATLTRACE("%d = pIStore->AddRef()\n",pIStore->AddRef());
#endif

	try
	{
//		CSymRunProgressDlg winProg; // progress dialog
		HRESULT hr;
		VARIANT_BOOL vb;
		HWND hwndProg = NULL;

		CARRunInfo arruninfo((bShow==VB_TRUE),m_csProgDialog,m_hEvent1,m_hEndEvent,pINumCat);
		m_pARRunInfo = &arruninfo; // odd way of doing things, but scope was local
		//pINumCat->AddRef(); - think its Addreffed when you come in
		//pIStore->AddRef();
//		winProg.PreCreate(m_pARRunInfo); // so the window has access also
////		arruninfo.m_hosthWnd = (HWND)ihwnd; - causes lots of grief
	
		// launch progress thread
		unsigned long ithrd = _beginthread(ARRunWindowThread,0,&arruninfo);
		if (ithrd==-1) // then thread has failed
						{
						ResetEvent(m_hEvent1);
						(*pbSuccess)=VB_FALSE; 
						SYMERRORLITE("Unable to create Progress Window",errSystem);
						ATLTRACE("<Error#> Could not create thread in %s line %d",__FILE__,__LINE__);
						pINumCat->Release();
						pIStore->Release();
						m_pARRunInfo=NULL;
						OSTEXIT()
						return Error(_T("Unable to create Progress Window"));
						}

		WaitForSingleObject( m_hEvent1, 5000 ); // lets wait for the dialog to appear but can't wait for ever
		ResetEvent(m_hEvent1);


		// load model
//		winProg.AttachProgText("Loading model...");
		arruninfo.AttachProgText("Loading model...");

		OST( "About to load model")
		hr = pINumCat->LoadModel(pbstrRunName,pIStore,&vb);
		OST( "Loaded model" )
		if (FAILED(hr))
				{
				OST("Model FAILED")
				CLOSEDLGTHREAD()
				pINumCat->Release();
				pIStore->Release();
				OSTEXIT()
				return E_FAIL;
				}

		if (vb==VB_FALSE)
				{
				OST("Model had error messages")
				CLOSEDLGTHREAD()
				pINumCat->Release();
				pIStore->Release();
				OSTEXIT()
				return S_FALSE;
				}

		OST("Model loaded fine")
		// now lets get the names from it
		{
		SAFEARRAY* pSA;
		UINT i;
		USES_CONVERSION;
		long iLBound, iUBound, iElems;

		hr = pINumCat->get_VariableNames(&pSA); // which I'm going to have to clean up

		if (FAILED(hr))
				{
				OST("Model FAILED to get variable names")
				CLOSEDLGTHREAD()
				pINumCat->Release();
				pIStore->Release();
				OSTEXIT()
				return Error(_T("Failed to copy variable names"));
				}

		BSTR* prgn =0;

		ATLASSERT(SafeArrayGetDim(pSA)==1);
		
		if (SafeArrayGetDim(pSA)==1) // else somethign wrong
			{
			
			hr = SafeArrayGetLBound(pSA,1,&iLBound);
			if (SUCCEEDED(hr))
				hr= SafeArrayGetUBound(pSA,1,&iUBound);


			if (SUCCEEDED(hr))
				hr = SafeArrayAccessData(pSA,(void**)&prgn);

			iElems=iUBound-iLBound+1;

			if (SUCCEEDED(hr))
				{
				for(i=0;i<iElems;i++)
					{
					arruninfo.m_vecAllNames.push_back(OLE2A(prgn[i]));
//					SysFreeString(prgn[i]);
					ATLTRACE("vecVarNames[%d] = %s\n",i,arruninfo.m_vecAllNames[i].c_str());
					}
				SafeArrayUnaccessData(pSA);
				}

			
			}// end (SafeArrayGetDim(pSA)==1)		
		
		
		
		hr = SafeArrayDestroy(pSA);

		if (hr==DISP_E_ARRAYISLOCKED)
				{
				Sleep(1500); // may as well try again, perhaps its been released
				hr = SafeArrayDestroy(pSA);
				if (hr==DISP_E_ARRAYISLOCKED)
					{
					OST("Failed to get an array to copy variable names");
					CLOSEDLGTHREAD()
					pINumCat->Release();
					pIStore->Release();
					OSTEXIT()
					return Error(_T("Failed to get an array to copy variable names"));
					}
					else
					if (FAILED(hr))
					{
					OST("Failed to open array")
					arruninfo.SendSafeMessage(WM_CLOSE);
					CLOSEDLGTHREAD()
					pINumCat->Release();
					pIStore->Release();
					OSTEXIT()
					return Error(_T("Failed to open array"));
					}
				}
				else
				{
				if (FAILED(hr))
						{
						OST("Failed to get an array")
						CLOSEDLGTHREAD()
						pINumCat->Release();
						pIStore->Release();
						OSTEXIT()
						return Error(_T("Failed to get an array"));
						}
				}

		
		}

		OST("About to run model")
		// run model
		arruninfo.AttachProgText("Running model...");
		hr = pINumCat->RunModel(NULL,this,&vb);
		OST("Model Run complete")
		ATLTRACE("**RunModel finished returning %d .\n",hr);
		if (FAILED(hr))
				{
				OST("Model run FAILED")
				CLOSEDLGTHREAD()
				pINumCat->Release();
				pIStore->Release();
				OSTEXIT()
				return E_FAIL;
				}

		if (vb==VB_FALSE)
				{
				CLOSEDLGTHREAD()
				pINumCat->Release();
				pIStore->Release();
				OSTEXIT()
				return S_FALSE;
				}

//		winProg.AttachProgText("Run finished.");
			
		*pbSuccess=VB_TRUE;

		CLOSEDLGTHREAD();
/*		
		arruninfo.SendSafeMessage(WM_CLOSE);
		if (arruninfo.m_DlgHwnd)
				SendMessage(arruninfo.m_DlgHwnd,WM_CLOSE,NULL,NULL);
		ATLTRACE("m_hEndEvent = %d\n",m_hEndEvent);
		DWORD dwState = WaitForSingleObject( m_hEndEvent, 5000 ); // lets wait for the dialog to appear but can't wait for ever
//		ATLASSERT(!::IsWindow(winProg.m_hWnd));
		ATLASSERT(WAIT_OBJECT_0==dwState); // in case things haven't exited right
		if (dwState==WAIT_TIMEOUT)
			{
			::MessageBox(NULL,"An software error has occured when closing the run dialog down","Symlix",MB_OK|MB_ICONEXCLAMATION);
			dwState = WaitForSingleObject( m_hEndEvent, 5000 ); // try again
			}
		m_pARRunInfo=NULL;*/
	}
	catch(...)
	{

//		m_pARRunInfo=NULL;
		OST("Unhandled error caught by catch")
		OST("Return E_FAIL")
		OSTEXIT()

		return E_FAIL;
	}
#ifndef NDEBUG
		{
		int iRC;
		iRC = pINumCat->Release();
		ATLTRACE(" %d = pINumCat->Release()\n",iRC);
		iRC = pIStore->Release();
		ATLTRACE(" %d = pIStore->Release()\n",iRC);
		}
#else
		pINumCat->Release();
		pIStore->Release();
#endif

OSTEXIT()

	return S_OK;
}



///////////////////////////////////////////////////////////
// Function name	: CARRunProgress::ToUpdate
// Description	    : Implements the INumCatHostCallBack method
// Return type		: STDMETHODIMP 
// Argument         : SAFEARRAY ** ppsaInds
// Argument         : VARIANT_BOOL * pvb
///////////////////////////////////////////////////////////
STDMETHODIMP CARRunProgress::ToUpdate(SAFEARRAY ** ppsaInds, VARIANT_BOOL * pvb)
{
	UINT i;
	long iLBound, iUBound, iElems;
	HRESULT hr;
	vector<long> vecInds;

	long* prgn =0;

	
	if (pvb == NULL)
		return E_POINTER;
			

	if (!m_pARRunInfo)
		{
		(*pvb) = VB_FALSE;
		hr = SafeArrayDestroy(*ppsaInds);
		if FAILED(hr)
			return hr;
		return S_FALSE;
		}
	


	ATLASSERT((ppsaInds)&&(*ppsaInds));
	if ((ppsaInds)&&(*ppsaInds))
		{

		ATLASSERT(SafeArrayGetDim(*ppsaInds)==1);
		
		if (SafeArrayGetDim(*ppsaInds)==1) // else somethign wrong
			{
			
			hr = SafeArrayGetLBound(*ppsaInds,1,&iLBound);
			if (SUCCEEDED(hr))
				hr= SafeArrayGetUBound(*ppsaInds,1,&iUBound);


			if (SUCCEEDED(hr))
				hr = SafeArrayAccessData(*ppsaInds,(void**)&prgn);

			iElems=iUBound-iLBound+1;

			if (SUCCEEDED(hr))
				{
				for(i=0;i<iElems;i++)
					vecInds.push_back(prgn[i]);

				SafeArrayUnaccessData(*ppsaInds);
				}

			
			}// end (SafeArrayGetDim(pSA)==1)	
	} // end ((ppSA)&&(*ppSA))



	hr = SafeArrayDestroy(*ppsaInds);

	if (hr==DISP_E_ARRAYISLOCKED)
				{
				Sleep(1500); // may as well try again, perhaps its been released
				hr = SafeArrayDestroy(*ppsaInds);
				if (hr==DISP_E_ARRAYISLOCKED)
					{
					m_pARRunInfo=NULL;
					(*pvb) = VB_FALSE;
					return Error(_T("Problem handling update array"));
					}
					else
					if (FAILED(hr))
					{
					m_pARRunInfo=NULL;
					(*pvb) = VB_FALSE;
					return Error(_T("Problem handling update array"));
					}
				}
				else
				{
				if (FAILED(hr))
						{
						m_pARRunInfo=NULL;
						(*pvb) = VB_FALSE;
						return Error(_T("Failed to get an array"));
						}
				}

	m_pARRunInfo->setVectorNames(vecInds);

	(*pvb) = VB_TRUE;

	return S_OK;
}


///////////////////////////////////////////////////////////
// Function name	: CARRunProgress::Update
// Description	    : Implements the INumCatHostCallBack method
// Return type		: STDMETHODIMP 
// Argument         : SAFEARRAY ** ppsaVals
// Argument         : VARIANT_BOOL * pvb
///////////////////////////////////////////////////////////
STDMETHODIMP CARRunProgress::Update(SAFEARRAY ** ppsaVals, VARIANT_BOOL * pvb)
{
	UINT i;
	long iLBound, iUBound, iElems;
	HRESULT hr;

	double* prgn =0;

	
	if (pvb == NULL)
		return E_POINTER;
			

	if (!m_pARRunInfo)
		{
		(*pvb) = VB_FALSE;
		hr = SafeArrayDestroy(*ppsaVals);
		if FAILED(hr)
			return hr;
		return S_FALSE;
		}
	


	ATLASSERT((ppsaVals)&&(*ppsaVals));
	if ((ppsaVals)&&(*ppsaVals))
		{

		ATLASSERT(SafeArrayGetDim(*ppsaVals)==1);
		
		if (SafeArrayGetDim(*ppsaVals)==1) // else somethign wrong
			{
			
			hr = SafeArrayGetLBound(*ppsaVals,1,&iLBound);
			if (SUCCEEDED(hr))
				hr= SafeArrayGetUBound(*ppsaVals,1,&iUBound);


			if (SUCCEEDED(hr))
				hr = SafeArrayAccessData(*ppsaVals,(void**)&prgn);

			iElems=iUBound-iLBound+1;

			if (SUCCEEDED(hr))
				{
				if (m_vecValues.size()!=iElems)
					m_vecValues.resize(iElems,NOT_DEFINED);

				for(i=0;i<iElems;i++)
					m_vecValues[i]=prgn[i];

				SafeArrayUnaccessData(*ppsaVals);
				}

			
			}// end (SafeArrayGetDim(pSA)==1)	
	} // end ((ppSA)&&(*ppSA))



	hr = SafeArrayDestroy(*ppsaVals);

	if (hr==DISP_E_ARRAYISLOCKED)
				{
				Sleep(1500); // may as well try again, perhaps its been released
				hr = SafeArrayDestroy(*ppsaVals);
				if (hr==DISP_E_ARRAYISLOCKED)
					{
					m_pARRunInfo=NULL;
					(*pvb) = VB_FALSE;
					return Error(_T("Problem handling update array"));
					}
					else
					if (FAILED(hr))
					{
					m_pARRunInfo=NULL;
					(*pvb) = VB_FALSE;
					return Error(_T("Problem handling update array"));
					}
				}
				else
				{
				if (FAILED(hr))
						{
						m_pARRunInfo=NULL;
						(*pvb) = VB_FALSE;
						return Error(_T("Failed to get an array"));
						}
				}

	m_pARRunInfo->updateValues(m_vecValues);

	(*pvb) = VB_TRUE;

	return S_OK;
}
