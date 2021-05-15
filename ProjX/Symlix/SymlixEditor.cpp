// SymlixEditor.cpp : Implementation of CSymlixEditor
#include "stdafx.h"
#include "Symlix.h"
#include "SymlixEditor.h"

// start window 
#include <atlwin.h>
#include <atlframe.h>
#include <atlctrls.h>
#include <atldlgs.h>
#include <atlctrlw.h>

//#include "SymEditMainFrm.h"
#include "SymlixHiddenDlg.h"


/////////////////////////////////////////////////////////////////////////////
// CSymlixEditor

STDMETHODIMP CSymlixEditor::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_INumCatEditor
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

#ifdef _DEBUGMEM
#include "../MemLEakRecord.h"
#endif

///////////////////////////////////////////////////////////
// Function name	: CSymlixEditor::OpenToEdit
// Description	    : 
// Return type		: STDMETHODIMP 
// Argument         : [in] int ihwnd
// Argument         : [in] BSTR *pbstrKey
// Argument         : [in] IARDataStore *pIStore
// Argument         : [in] INumCatErrorRun* pIErrorRun 
// Argument         : [in] IARTrace* pIARTrace
// Argument         : [out,retval] enumNumCatEditorCommand* pVal
///////////////////////////////////////////////////////////
STDMETHODIMP CSymlixEditor::OpenToEdit( int ihwnd, BSTR *pbstrKey, IARDataStore *pIStore, INumCatErrorRun* pIErrorRun, IARTrace* pIARTrace, enumNumCatEditorCommand* pVal)
{

#ifdef _DEBUGMEM
	CMemLeakRecord* pcmlrFind;

	pcmlrFind = newtrack CMemLeakRecord;
#endif	

	(*pVal) = esecNothing; // default value - will vary latter on
	
	
	bool bHasErrorRun = false;
	VARIANT_BOOL vbResult;
	HRESULT hr;
	long iRefCount;

	if (pIARTrace)
		{
		iRefCount = pIARTrace->AddRef();
		ATLTRACE("Ref count %d after pIARTrace->AddRef()\n",iRefCount);
		}

	if (pIARTrace)
		{
			USES_CONVERSION;
			BSTR bstrTest = SysAllocString( T2OLE(_T("OpenToEdit has recieved Trace ref")));
			hr = pIARTrace->Trace(&bstrTest,&vbResult); // don't care what happens to hr - if fails were in deep anyway
			SysFreeString(bstrTest);
		}



	if (!pIStore)
		{
		if (pIARTrace)
			{
			USES_CONVERSION;
			BSTR bstrTest = SysAllocString( T2OLE(_T("Failed to find a Store object")));
			hr = pIARTrace->Trace(&bstrTest,&vbResult); // don't care what happens to hr - if fails were in deep anyway
			SysFreeString(bstrTest);
			pIARTrace->Release();
			}
		return Error(_T("Unable to access model stream. Please report this error."));
		//return E_FAIL;
		}

	try
	{
		VARIANT_BOOL vb;


		pIStore->AddRef();
		if (pIErrorRun) // the Lords of COM demand
			{
			iRefCount = pIErrorRun->AddRef();
			ATLTRACE(_T("pIErrorRun->AddRef() = %d\n"),iRefCount);
			bHasErrorRun = true;
			}
#ifndef NDEBUG
			else
			{
			ATLTRACE("pIErrorRun = NULL\n");

			}
#endif


		HRESULT hr = pIStore->isAvailable(pbstrKey,&vb);
		
		if (vb==0)
			{
			if (pIARTrace)
				{
				USES_CONVERSION;
				BSTR bstrTest = SysAllocString( T2OLE(_T("Store for the key was unavailable")));
				hr = pIARTrace->Trace(&bstrTest,&vbResult); // don't care what happens to hr - if fails were in deep anyway
				SysFreeString(bstrTest);
				pIARTrace->Release();
				}
			return S_FALSE;
			}
	}
	catch(...)
	{
	// crashing
	if (pIARTrace)
		{
		USES_CONVERSION;
		BSTR bstrTest = SysAllocString( T2OLE(_T("Unhandled crash caught when setting up streams")));
		hr = pIARTrace->Trace(&bstrTest,&vbResult); // don't care what happens to hr - if fails were in deep anyway
		SysFreeString(bstrTest);
		iRefCount = pIARTrace->Release();
		}
	ATLTRACE("Exception caught pIARTrace->Release() ref count after = %d\n",iRefCount);
	return Error(_T("An unexpected error occured when trying to find the model stream."));
//	return E_FAIL;
	}
	
	
	try
	{

	CSymlixHiddenDlg dlg;

	if (dlg.PreCreate(pbstrKey,pIStore, pIErrorRun, (HWND)ihwnd))
		{
		BSTR bstrTest;
		if (pIARTrace)
			{
			USES_CONVERSION;
			bstrTest = SysAllocString( T2OLE(_T("SymlixEditor::Dlg")));
			hr = pIARTrace->TraceS(&bstrTest,&vbResult); // don't care what happens to hr - if fails were in deep anyway
			SysFreeString(bstrTest);
			}

		dlg.DoModal((HWND)ihwnd);

		(*pVal) = dlg.PostRunMessage(); // any instructions for the host application ?

		if (pIARTrace)
			{
			USES_CONVERSION;
			SysReAllocString(&bstrTest,T2OLE(_T("SymlixEditor::Dlg")));
			hr = pIARTrace->TraceE(&bstrTest,&vbResult); // don't care what happens to hr - if fails were in deep anyway
			SysFreeString(bstrTest);
			}
		}

	pIStore->Release();
	if (bHasErrorRun)
		{
		iRefCount = pIErrorRun->Release();
		ATLTRACE(_T("pIErrorRun->Release() = %d\n"),iRefCount);
		}
	}
	catch(...)
	{
	ATLTRACE("CSymlixEditor::OpenToEdit Failed to create Editor\n");
	if (pIARTrace)
		{
		USES_CONVERSION;
		BSTR bstrTest = SysAllocString( T2OLE("Failed to create Editor"));
		hr = pIARTrace->Trace(&bstrTest,&vbResult); // don't care what happens to hr - if fails we're in deep anyway
		SysFreeString(bstrTest);
		iRefCount = pIARTrace->Release();
		ATLTRACE("Exception caught pIARTrace->Release() ref count after = %d\n",iRefCount);
		}
	return Error(_T("An unexpected error occured when using the editor."));
//	return E_FAIL;
	}


	if (pIARTrace)
		{
		iRefCount = pIARTrace->Release();
		ATLTRACE("pIARTrace->Release() ref count after = %d\n",iRefCount);
		}
#ifdef _DEBUGMEM
	delete pcmlrFind;
#endif


	return S_OK;
}



