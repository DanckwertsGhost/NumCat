// SymlixHiddenDlg.h : Declaration of the CSymlixHiddenDlg

#ifndef __SYMLIXHIDDENDLG_H_
#define __SYMLIXHIDDENDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>
#include "SymlixStore.h"

// start window 
#include <atlwin.h>
#include <atlframe.h>
#include <atlctrls.h>
#include <atldlgs.h>
#include <atlctrlw.h>

#include "SymEditMainFrm.h"


template <class T> class CHiddenParentDlg: 
	public CAxDialogImpl<CHiddenParentDlg>
{
public:
	CHiddenParentDlg()
	{
	}

	~CHiddenParentDlg()
	{
	}

	enum { IDD = IDD_SYMLIXHIDDENDLG };

BEGIN_MSG_MAP(CSymlixHiddenDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	T m_wndMain;


/*	bool PreCreate(BSTR* pbstrKey, IARDataStore *pIStore, INumCatErrorRun* pIErrorRun, HWND hwndHost=NULL)
	{
		try
		{
			m_wndMain.PreCreate(pbstrKey,pIStore, pIErrorRun, hwndHost);

		}
		catch(...)
		{
		ATLTRACE(_T("Error caught in CHiddenParentDlg::PreCreate"));
		return false;
		}
		return true;
	}*/


	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{

	CMessageLoop theLoop;
	_Module.AddMessageLoop(&theLoop);


//	m_wndMain.PreCreate(pbstrKey,pIStore, (HWND)ihwnd);

	ATLTRACE("About to try and create a window with parent HWND = %d\n",m_hWnd);
//	if(wndMain.CreateEx(NULL,NULL,DS_MODALFRAME) == NULL)
//	if(wndMain.CreateEx(HWND(ihwnd)) == NULL)

	try
	{
		if(m_wndMain.CreateEx(m_hWnd) == NULL)
	//	if(wndMain.CreateEx() == NULL)
		{
			ATLTRACE(_T("Main window creation failed!\n"));
			MessageBox(_T("Failed to create Code Editor"),_T("Symlix"),MB_OK|MB_ICONERROR);
			PostMessage(WM_CLOSE);
			return 1; 
		}

		m_wndMain.ShowWindow(SW_SHOWDEFAULT);

		int nRet = theLoop.Run();

	}
	catch(...)
	{
		ATLTRACE("<Exception> caught in %s at line %d\n",__FILE__,__LINE__);
		if (!m_wndMain.m_hWnd)
			::SendMessage(m_wndMain.m_hWnd,WM_CLOSE,NULL,NULL);
	}

	_Module.RemoveMessageLoop();		
		
		
	// OK time to clear up
	PostMessage(WM_CLOSE);
				
	return 1;  // Let the system set the focus
	}

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
};


/////////////////////////////////////////////////////////////////////////////
// CSymlixHiddenDlg

class CSymlixHiddenDlg :
	public CHiddenParentDlg<CSymEditMainFrame>
{
public:
	CSymlixHiddenDlg()
	{
	}

	~CSymlixHiddenDlg()
	{
	}

	bool PreCreate(BSTR* pbstrKey, IARDataStore *pIStore, INumCatErrorRun* pIErrorRun, HWND hwndHost=NULL)
	{
		try
		{
			m_wndMain.PreCreate(pbstrKey,pIStore, pIErrorRun, hwndHost);

		}
		catch(...)
		{
		ATLTRACE(_T("Error caught in CSymlixHiddenDlg::PreCreate"));
		return false;
		}
		return true;
	}

	enumNumCatEditorCommand PostRunMessage(){ return m_wndMain.PostRunMessage(); }
};

/////////////////////////////////////////////////////////////////////////////
// CSymRunProgressDlg
/*
class CSymlixRunHiddenDlg :
	public CHiddenParentDlg<CSymRunProgressDlg>
{
public:
	CSymlixRunHiddenDlg()
	{
	}

	~CSymlixRunHiddenDlg()
	{
	}

	bool PreCreate(HWND hwndHost, HWND& rhwndClient)
	{
		try
		{
			m_wndMain.PreCreate(hwndHost,rhwndClient);

		}
		catch(...)
		{
		ATLTRACE(_T("Error caught in CSymlixHiddenDlg::PreCreate"));
		return false;
		}
		return true;
	}
};*/
/*	
class CSymlixHiddenDlg : 
	public CAxDialogImpl<CSymlixHiddenDlg>
{
public:
	CSymlixHiddenDlg()
	{
	}

	~CSymlixHiddenDlg()
	{
	}

	enum { IDD = IDD_SYMLIXHIDDENDLG };

BEGIN_MSG_MAP(CSymlixHiddenDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	CSymEditMainFrame m_wndMain;


	bool PreCreate(BSTR* pbstrKey, IARDataStore *pIStore, INumCatErrorRun* pIErrorRun, HWND hwndHost=NULL)
	{
		try
		{
			m_wndMain.PreCreate(pbstrKey,pIStore, pIErrorRun, hwndHost);

		}
		catch(...)
		{
		ATLTRACE(_T("Error caught in CSymlixHiddenDlg::PreCreate"));
		return false;
		}
		return true;
	}


	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{

	CMessageLoop theLoop;
	_Module.AddMessageLoop(&theLoop);


//	m_wndMain.PreCreate(pbstrKey,pIStore, (HWND)ihwnd);

	ATLTRACE("About to try and create a window with parent HWND = %d\n",m_hWnd);
//	if(wndMain.CreateEx(NULL,NULL,DS_MODALFRAME) == NULL)
//	if(wndMain.CreateEx(HWND(ihwnd)) == NULL)
	if(m_wndMain.CreateEx(m_hWnd) == NULL)
//	if(wndMain.CreateEx() == NULL)
	{
		ATLTRACE(_T("Main window creation failed!\n"));
		MessageBox(_T("Failed to create Code Editor"),_T("Symlix"),MB_OK|MB_ICONERROR);
		PostMessage(WM_CLOSE);
		return 1; 
	}

	m_wndMain.ShowWindow(SW_SHOWDEFAULT);

	int nRet = theLoop.Run();


	_Module.RemoveMessageLoop();		
		
		
	// OK time to clear up
	PostMessage(WM_CLOSE);
				
	return 1;  // Let the system set the focus
	}

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
};*/

#endif //__SYMLIXHIDDENDLG_H_
