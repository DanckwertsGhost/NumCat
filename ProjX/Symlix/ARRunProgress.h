// ARRunProgress.h : Declaration of the CARRunProgress

#ifndef __ARRUNPROGRESS_H_
#define __ARRUNPROGRESS_H_

#include "resource.h"       // main symbols
#include <process.h>
#include <vector>
#include "SymRunProgressDlg.h"
#include "..\CritCheck.h"
#include "Symlix.h"

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

using namespace std;


// Class used to synchronising information between threads
class CARRunInfo
  {
  public:
	CARRunInfo(/*CSymRunProgressDlg& rwinProg,*/ bool bVisible, CRITICAL_SECTION& cs, HANDLE hEvent1, HANDLE hEndEvent, INumCat* pINumCat )
		:/*m_rwinProg(rwinProg),*/m_bVisible(bVisible),m_rCritSec(cs),m_hEvent1(hEvent1),m_hEndEvent(hEndEvent),m_DlgHwnd(NULL),m_hosthWnd(NULL),m_bReadyWithData(false),m_pINumCat(pINumCat),m_prDlg(NULL)
	{
		if (m_pINumCat)
			m_pINumCat->AddRef();
#ifndef NDEBUG
		m_bOriginal=true;
#endif
	}
/*	CARRunInfo( const CARRunInfo& cai)
		:m_rwinProg(cai.m_rwinProg),m_bVisible(cai.m_bVisible),m_rCritSec(cai.m_rCritSec),m_hEvent1(cai.m_hEvent1),m_hEndEvent(cai.m_hEndEvent),m_DlgHwnd(cai.m_DlgHwnd),m_hosthWnd(cai.m_hosthWnd),m_vecAllNames(cai.m_vecAllNames),m_bReadyWithData(cai.m_bReadyWithData),m_pINumCat(cai.m_pINumCat)
	{
		if (m_pINumCat)
			m_pINumCat->AddRef();
#ifndef NDEBUG
		m_bOriginal=false;
#endif
	}*/

	~CARRunInfo()
	{
		if (m_pINumCat)
			m_pINumCat->Release();
#ifndef NDEBUG
		if	(m_bOriginal)
			ATLTRACE("## Original\n");
			else
			ATLTRACE("##Copy\n");

#endif
	}
	static bool bContinue;
//	static HWND m_hwnd=NULL;
	HWND m_hosthWnd;
//	CSymRunProgressDlg& m_rwinProg; // progress dialog
	bool m_bVisible;
	CRITICAL_SECTION& m_rCritSec;
	HANDLE m_hEndEvent;
	HANDLE m_hEvent1;
	HWND m_DlgHwnd;
	vector<string> m_vecAllNames;

	bool readyWithData() const { return m_bReadyWithData; }

	void setDlgPointer(CSymRunProgressDlg* prDlg){m_prDlg=prDlg;}
	void clearDlgPointer()
	{
		CCritCheck cs(m_rCritSec);
		m_prDlg= NULL;
	}

	LRESULT SendSafeMessage(UINT message, WPARAM wParam = 0, LPARAM lParam = 0)
	{
		CCritCheck cs(m_rCritSec);
		LRESULT lr = 0;
		if (m_prDlg)
			lr = m_prDlg->SendSafeMessage( message,  wParam ,  lParam );

		return lr;
	}

	void setVectorNames(const vector<long>& rvecInds)
	{
		vector<long>::const_iterator cit;
		long iLen=m_vecAllNames.size();
		CCritCheck cc(m_rCritSec);


		for (cit=rvecInds.begin();cit!=rvecInds.end();cit++)
			if (*cit<iLen)
				m_vecVNames.push_back(m_vecAllNames[*cit]);
#ifndef NDEBUG
				else
				ATLASSERT(false);
#endif
		ATLTRACE("The number of Names is %d.\n",m_vecVNames.size());
	}

	void updateValues(const vector<double>& rvecVals)
	{
		CCritCheck cc(m_rCritSec);
		m_vecValues = rvecVals;
		ATLTRACE("The number of Values is %d.\n",m_vecValues.size());
		m_bReadyWithData=true;
	}

	void getValues(vector<double>& rvecGetValues) const
	{
		CCritCheck cc(m_rCritSec);
		rvecGetValues = m_vecValues;
	}

	void getNames(vector<string>& rvecGetNames) const
	{
		CCritCheck cc(m_rCritSec);
		rvecGetNames = m_vecVNames;
	}

	void sendStopSimulation()
	{
		HRESULT hr;

		if (m_pINumCat)
			hr = m_pINumCat->StopModel(); // don't really care about return value

	}

	void AttachProgText(LPCTSTR lpszString)
	{
		CCritCheck cs(m_rCritSec);
		if (m_prDlg)
			m_prDlg->AttachProgText(lpszString);
	}

  private:
	vector<string> m_vecVNames;
	vector<double> m_vecValues;
	bool m_bReadyWithData;
	INumCat* m_pINumCat;
	CSymRunProgressDlg* m_prDlg;
#ifndef NDEBUG
	bool m_bOriginal;
#endif

  };

/////////////////////////////////////////////////////////////////////////////
// CARRunProgress
class ATL_NO_VTABLE CARRunProgress : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CARRunProgress, &CLSID_ARRunProgress>,
	public ISupportErrorInfo,
	public IDispatchImpl<IARRunProgress, &IID_IARRunProgress, &LIBID_NumCatLib>,
	public IDispatchImpl<INumCatHostCallBack, &IID_INumCatHostCallBack, &LIBID_NumCatLib>
{
public:
	CARRunProgress()
	{
		m_hEvent1 = CreateEvent(NULL,TRUE,FALSE,NULL);
		m_hEndEvent = CreateEvent(NULL,FALSE,FALSE,NULL);
		InitializeCriticalSection(&m_csProgDialog); // not sure this will be needed
		m_pARRunInfo = NULL;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ARRUNPROGRESS)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CARRunProgress)
	COM_INTERFACE_ENTRY(IARRunProgress)
//DEL 	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY2(IDispatch, IARRunProgress)
	COM_INTERFACE_ENTRY(INumCatHostCallBack)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IARRunProgress
public:
	STDMETHOD(RunModel)(/*[in]*/ int ihwnd,/*[in]*/ INumCat* pINumCat, /*[in]*/ IARDataStore* pIStore, /*[in]*/ BSTR* pbstrRunName, /*[in]*/ VARIANT_BOOL bShow, /*[out,retval]*/ VARIANT_BOOL* pbSuccess );

private:
	HANDLE m_hEvent1;
	HANDLE m_hEndEvent;
	CRITICAL_SECTION m_csProgDialog;
	CARRunInfo* m_pARRunInfo;
	vector<double> m_vecValues;

public:
	
// INumCatHostCallBack
	STDMETHOD(TimeSignal)(LONG * piTime)
	{
		if (piTime == NULL)
			return E_POINTER;
			
#ifndef NDEBUG
		return S_OK;
#else
		return E_NOTIMPL;
#endif
	}

	STDMETHOD(Update)(SAFEARRAY ** ppsaVals, VARIANT_BOOL * pvb);
	STDMETHOD(ToUpdate)(SAFEARRAY ** ppsaInds, VARIANT_BOOL * pvb);

	STDMETHOD(ExpectEnd)(DOUBLE * pdEnd)
	{
		if (pdEnd == NULL)
			return E_POINTER;
			
#ifndef NDEBUG
		return S_OK;
#else
		return E_NOTIMPL;
#endif
	}
};

#endif //__ARRUNPROGRESS_H_
