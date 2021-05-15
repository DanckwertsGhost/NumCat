// MainFrm.h : interface of the CSymEditMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYMEDITFRM_H__EEEE5672_8CE9_444A_85AB_917BC939A148__INCLUDED_)
#define AFX_SYMEDITFRM_H__EEEE5672_8CE9_444A_85AB_917BC939A148__INCLUDED_

#include "SymlixStore.h"
#include "SymEditor.h"
#include "aboutdlg.h"
#include "WndProcSafeSwapper.h"
#include "ARLatlSplitWndsHoriz.h"
#include "ARLatlSplitWndsVert.h"
#include "SymEdErrList.h"
#include "ctxNumCatHelp.h"

#include <atlctrlx.h>
#include <htmlHelp.h>


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define _xNOERRORSWINDOW
#define _xNOEDITORWINDOW

class CSymEditMainFrame : public CFrameWindowImpl<CSymEditMainFrame>, public CUpdateUI<CSymEditMainFrame>,
		public CMessageFilter, public CIdleHandler
{


public:
	DECLARE_FRAME_WND_CLASS(NULL, IDR_MAINFRAME)

#ifndef _NOERRORSWINDOW				
	CARLatlSplitWndsHoriz<CSymEditView,CSymEdErrList/*CARLatlBasicHoldWnd*/> m_splitWin;
#else
#ifndef _NOEDITORWINDOW
	CARLatlSplitWndsHoriz<CSymEditView,CARLatlBasicHoldWnd> m_splitWin;
#else
	CARLatlSplitWndsHoriz<CARLatlBasicHoldWnd,CARLatlBasicHoldWnd> m_splitWin;
#endif
#endif

	CSymEditView* m_pView;

	CWndProcSafeSwapper m_subclasshost;

	CCommandBarCtrl m_CmdBar;

#ifndef _NOSTATUS_BAR
	CMultiPaneStatusBarCtrl m_status;
#endif

	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		if(CFrameWindowImpl<CSymEditMainFrame>::PreTranslateMessage(pMsg))
			return TRUE;

		return m_splitWin.PreTranslateMessage(pMsg); // maybe shoudl be to specific window
	}

	virtual BOOL OnIdle()
	{
		UIUpdateToolBar();
		return FALSE;
	}

	BEGIN_UPDATE_UI_MAP(CSymEditMainFrame)
		UPDATE_ELEMENT(ID_VIEW_TOOLBAR, UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_VIEW_STATUS_BAR, UPDUI_MENUPOPUP)
	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CSymEditMainFrame)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		COMMAND_ID_HANDLER(ID_APP_EXIT, OnFileExit)
		COMMAND_ID_HANDLER(ID_FILE_NEW, OnFileNew)
		COMMAND_ID_HANDLER(ID_FILE_RUN, OnFileRun)
		COMMAND_ID_HANDLER(ID_FILE_SAVE, OnFileSave)
		COMMAND_ID_HANDLER(ID_VIEW_TOOLBAR, OnViewToolBar)
		COMMAND_ID_HANDLER(ID_VIEW_STATUS_BAR, OnViewStatusBar)
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		COMMAND_ID_HANDLER(ID_EDIT_COPY, OnEditCopy)
		COMMAND_ID_HANDLER(ID_EDIT_CUT, OnEditCut)
		COMMAND_ID_HANDLER(ID_EDIT_PASTE, OnEditPaste)
		COMMAND_ID_HANDLER(ID_EDIT_UNDO, OnEditUndo)
		COMMAND_ID_HANDLER(ID_POPUP1_EVENTS_START, OnWriteToView)
		COMMAND_ID_HANDLER(ID_POPUP1_SOLVER_RK4, OnWriteToView)
		COMMAND_ID_HANDLER(ID_POPUP1_SOLVER_RK3, OnWriteToView)
		COMMAND_ID_HANDLER(ID_POPUP1_SOLVER_RK3VS, OnWriteToView)
 		COMMAND_ID_HANDLER(ID_POPUP1_SOLVER_RK4VS, OnWriteToView)
 		COMMAND_ID_HANDLER(ID_POPUP1_SOLVER_RK4VSMT, OnWriteToView)
 		COMMAND_ID_HANDLER(ID_POPUP1_SOLVER_RK5, OnWriteToView)
 		COMMAND_ID_HANDLER(ID_POPUP1_SOLVER_RK5VS, OnWriteToView)
  		COMMAND_ID_HANDLER(ID_POPUP1_EVENTS_STOP, OnWriteToView)
 		COMMAND_ID_HANDLER(ID_POPUP1_EVENTS_RECORD, OnWriteToView)
		COMMAND_ID_HANDLER(ID_POPUP1_EVENTS_DUMP, OnWriteToView)
		COMMAND_ID_HANDLER(ID_POPUP1_EVENTS_SYNC, OnWriteToView)
		COMMAND_ID_HANDLER(ID_POPUP1_EVENTS_PACE, OnWriteToView)
		COMMAND_ID_HANDLER(ID_POPUP1_EVENTS_CHANGEVALUE, OnWriteToView)
		COMMAND_ID_HANDLER(ID_POPUP1_EVENTS_REALTIME, OnWriteToView)
		COMMAND_ID_HANDLER(ID_POPUP1_EQUATIONS_ORDINARY, OnWriteToView)
		COMMAND_ID_HANDLER(ID_POPUP1_EQUATIONS_DIFFERENTIAL, OnWriteToView)
		COMMAND_ID_HANDLER(ID_POPUP1_EQUATIONS_SWITCHCASE, OnWriteToView)
		COMMAND_ID_HANDLER(ID_POPUP1_EQUATIONS_LOOKUP, OnWriteToView)
		COMMAND_ID_HANDLER(ID_POPUP1_MACROS_INSERT, OnWriteToView)
 		COMMAND_ID_HANDLER(ID_POPUP1_MACROS_DEFINE, OnWriteToView)
 		COMMAND_ID_HANDLER(ID_POPUP1_MACROS_TYPE, OnWriteToView)
 		COMMAND_ID_HANDLER(ID_POPUP1_FUNCTIONS_SIN, OnWriteToView)
		COMMAND_ID_HANDLER(ID_POPUP1_FUNCTIONS_COS, OnWriteToView)
		COMMAND_ID_HANDLER(ID_POPUP1_FUNCTIONS_TAN, OnWriteToView)
		COMMAND_ID_HANDLER(ID_POPUP1_FUNCTIONS_ASIN, OnWriteToView)
		COMMAND_ID_HANDLER(ID_POPUP1_FUNCTIONS_ACOS, OnWriteToView)
		COMMAND_ID_HANDLER(ID_POPUP1_FUNCTIONS_ATAN, OnWriteToView)
		COMMAND_ID_HANDLER(ID_POPUP1_FUNCTIONS_LOG, OnWriteToView)
		COMMAND_ID_HANDLER(ID_POPUP1_FUNCTIONS_LN, OnWriteToView)
		COMMAND_ID_HANDLER(ID_POPUP1_FUNCTIONS_EXP, OnWriteToView)
		COMMAND_ID_HANDLER(ID_POPUP1_FUNCTIONS_ABS, OnWriteToView)
		COMMAND_ID_HANDLER(ID_POPUP1_FUNCTIONS_INT, OnWriteToView)
		COMMAND_ID_HANDLER(ID_POPUP1_FUNCTIONS_INTUP, OnWriteToView)
		COMMAND_ID_HANDLER(ID_POPUP1_ARRAYS_PLAINARRAY, OnWriteToView)
		COMMAND_ID_HANDLER(ID_POPUP1_ARRAYS_SHEET, OnWriteToView)
		COMMAND_ID_HANDLER(ID_POPUP1_ARRAYS_ARRAYFUNCTIONS_COUNT, OnWriteToView)
		COMMAND_ID_HANDLER(ID_POPUP1_ARRAYS_ARRAYFUNCTIONS_SUM, OnWriteToView)
		COMMAND_ID_HANDLER(ID_POPUP1_ARRAYS_ARRAYFUNCTIONS_AVRG, OnWriteToView)
		COMMAND_ID_HANDLER(ID_POPUP1_SOLVER_SEQFROMTO, OnWriteToView)
		COMMAND_ID_HANDLER(ID_POPUP1_SOLVER_SEQUENCESERIES, OnWriteToView)
		COMMAND_ID_HANDLER(ID_POPUP1_SOLVERS_ONCE, OnWriteToView)
		COMMAND_ID_HANDLER(ID_POPUP1_EVENTS_ITFROMTO, OnWriteToView)
		COMMAND_ID_HANDLER(ID_POPUP1_EVENTS_ITERATIONSERIES, OnWriteToView)
		COMMAND_ID_HANDLER(ID_POPUP1_INDEX_DEFINE, OnWriteToView)
		COMMAND_ID_HANDLER(ID_POPUP1_INDEX_EXPAND, OnWriteToView)
		COMMAND_ID_HANDLER(ID_POPUP1_EVENTS_DUMPEQUATIONS,OnWriteToView)	
		COMMAND_ID_HANDLER(ID_EXAMPLE_SIMPLE, OnWriteSimpleExample)
 		COMMAND_ID_HANDLER(ID_HELP_EDITOR, OnHelpEditor)
 		COMMAND_ID_HANDLER(ID_HELP_SYNTAX, OnHelpSyntax)
		CHAIN_MSG_MAP(CUpdateUI<CSymEditMainFrame>)
		CHAIN_MSG_MAP(CFrameWindowImpl<CSymEditMainFrame>)
//		MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
//		MESSAGE_HANDLER(WM_CAPTURECHANGED, OnKillFocus)
		MESSAGE_HANDLER(WM_QUIT, OnQuit)
//		MESSAGE_HANDLER(WM_CLOSE, OnQuit)
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnWriteToView(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled)
	{ 
		if (m_pView)
			{
//			ATLTRACE("UINT %d, WPARAM %d, ID_POPUP1_EVENTS_START %d\n",uMsg,wParam,ID_POPUP1_EVENTS_STOP);
		//	m_pView->OnWriteEgStart(uMsg,wParam,lParam,bHandled);
//			SendMessage(m_pView->m_hWnd,ID_POPUP1_EVENTS_START,0,0);
		//	m_pView->PostMessage(wParam);
			m_pView->WriteForThisString(wParam); // using the fact the same string IDs correspond to menu IDs
			}
		return 0;
	}

	LRESULT OnWriteSimpleExample(UINT uMsg, WPARAM wParam, HWND lParam, BOOL& bHandled)
	{ 
		if (m_pView)
			{
			m_pView->WriteForThisString(IDS_LORENZ_EXAMPLE); // using the fact the smae string IDs correspond to menu IDs
			m_pView->WriteForThisString(IDS_LORENZ_EXAMPLE2); // using the fact the smae string IDs correspond to menu IDs
			}
		return 0;
	}

	void PreCreate(BSTR* pbstrKey, IARDataStore *pIStore, INumCatErrorRun* pIErrorRun, HWND hwndHost=NULL)
	{
		m_pView = NULL;
		m_encEdCmd = esecNothing;
		try
		{
//			long iCount;
			USES_CONVERSION;
#ifndef _NOEDITORWINDOW
			m_pView = m_splitWin.GetWinLeftPt();
			
			ATLASSERT(m_pView); // catch this in debug
			if (m_pView)
#ifndef _NOSTATUS_BAR
				m_pView->PreCreate(pbstrKey,pIStore,&m_status);
#else
				m_pView->PreCreate(pbstrKey,pIStore,NULL);
#endif
#endif // ndef _NOEDITORWINDOW

#ifndef _NOERRORSWINDOW				
			m_splitWin.GetWinRightPt()->setIErrorRun(pIErrorRun,OLE2CA(*pbstrKey));

			if (!pIErrorRun) // no errors - then size error window to zero
				m_splitWin.setOffsetWindow(0);
				else
				 if (m_splitWin.GetWinRightPt()->getNumberErrors()==0)
						 m_splitWin.setOffsetWindow(0); // no errors for this stream so offset zero
#endif
			// if want to try subclassing Excel - probably not a great idea
			/*
			if (hwndHost)
				m_subclasshost.SubClass(hwndHost);
			*/

		}
		catch(...)
		{
		ATLTRACE(_T("Error caught in CSymEditMainFrame::PreCreate"));

		}

	}

	enumNumCatEditorCommand PostRunMessage(){ return m_encEdCmd; }

	LRESULT OnFileSave(UINT /*uMsg*/, WPARAM /*wParam*/, HWND /*lParam*/, BOOL& /*bHandled*/)
	{
	ATLTRACE("OnFileSave\n");
#ifndef _NOEDITORWINDOW
	ATLASSERT(m_pView); // catch this in debug
	if (m_pView)
		m_pView->SaveStream();
#endif
	return 0;
	}

	LRESULT OnEditCopy(UINT /*uMsg*/, WPARAM /*wParam*/, HWND /*lParam*/, BOOL& /*bHandled*/)
	{
	ATLTRACE("OnEditCopy\n");
#ifndef _NOEDITORWINDOW
	ATLASSERT(m_pView); // catch this in debug
	if (m_pView)
		m_pView->Copy();
#endif
	return 0;
	}

	LRESULT OnEditCut(UINT /*uMsg*/, WPARAM /*wParam*/, HWND /*lParam*/, BOOL& /*bHandled*/)
	{
	ATLTRACE("OnEditCut\n");
#ifndef _NOEDITORWINDOW
	ATLASSERT(m_pView); // catch this in debug
	if (m_pView)
		m_pView->Cut();
#endif
	return 0;
	}

	LRESULT OnEditPaste(UINT /*uMsg*/, WPARAM /*wParam*/, HWND /*lParam*/, BOOL& /*bHandled*/)
	{
	ATLTRACE("OnEditPaste\n");
#ifndef _NOEDITORWINDOW
	ATLASSERT(m_pView); // catch this in debug
	if (m_pView)
		m_pView->Paste();
#endif
	return 0;
	}

	LRESULT OnEditUndo(UINT /*uMsg*/, WPARAM /*wParam*/, HWND /*lParam*/, BOOL& /*bHandled*/)
	{
	ATLTRACE("OnEditUndo\n");
#ifndef _NOEDITORWINDOW
	ATLASSERT(m_pView); // catch this in debug
	if (m_pView)
		m_pView->Undo();
#endif
	return 0;
	}
	
	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		// create command bar window
		HWND hWndCmdBar = m_CmdBar.Create(m_hWnd, rcDefault, NULL, ATL_SIMPLE_CMDBAR_PANE_STYLE);
		// attach menu
		m_CmdBar.AttachMenu(GetMenu());
		// load command bar images
		m_CmdBar.LoadImages(IDR_MAINFRAME);
		m_CmdBar.LoadImages(IDR_TOOLBAR1);
		// remove old menu
		SetMenu(NULL);

		HWND hWndToolBar = CreateSimpleToolBarCtrl(m_hWnd, IDR_MAINFRAME, FALSE, ATL_SIMPLE_TOOLBAR_PANE_STYLE);

		CreateSimpleReBar(ATL_SIMPLE_REBAR_NOBORDER_STYLE);
		AddSimpleReBarBand(hWndCmdBar);
		AddSimpleReBarBand(hWndToolBar, NULL, TRUE);

		CreateSimpleStatusBar();

#ifndef _NOSTATUS_BAR
		// subclass the status bar as multipane
		m_status.SubclassWindow(m_hWndStatusBar);

		// set status bar panes
		int arrPanes[] = { ID_DEFAULT_PANE, IDR_STATUS_STREAM, IDR_STATUS_LINE };
		m_status.SetPanes(arrPanes, sizeof(arrPanes) / sizeof(int), false);

		// set status bar pane widths using local workaround
		int arrWidths[] = { 0, 210, 70 };
		SetPaneWidths(arrWidths, sizeof(arrWidths) / sizeof(int));

		m_status.SetPaneText(IDR_STATUS_STREAM, "Woof");
#endif		
		
		CATLatlSpitAttributes attribsSplit;

		attribsSplit.setdwStyleLeft(WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_HSCROLL | WS_VSCROLL | ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE | ES_NOHIDESEL | ES_SAVESEL);
		attribsSplit.setdwStyleLeftEx(WS_EX_CLIENTEDGE);

		attribsSplit.setdwStyleRight(WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_HSCROLL | WS_VSCROLL | LVS_LIST | !LVS_NOSCROLL | LVS_SINGLESEL );
		attribsSplit.setdwStyleRightEx(WS_EX_CLIENTEDGE | LVS_EX_GRIDLINES /*| LVS_EX_GRIDLINES*/);

		m_splitWin.setSplitAttribs(attribsSplit); // needs to happen before .Create called

		m_hWndClient = m_splitWin.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | ES_SAVESEL, WS_EX_CLIENTEDGE);

#ifndef _NOERRORSWINDOW
		if (m_hWndClient!=NULL)
		{
			m_splitWin.GetWinRightPt()->SetLinkToEditor(m_splitWin.getLeftHWND());

		}
#endif
		
		UIAddToolBar(hWndToolBar);
		UISetCheck(ID_VIEW_TOOLBAR, 1);
		UISetCheck(ID_VIEW_STATUS_BAR, 1);

		// register object for message filtering and idle updates
		CMessageLoop* pLoop = _Module.GetMessageLoop();
		ATLASSERT(pLoop != NULL);
		pLoop->AddMessageFilter(this);
		pLoop->AddIdleHandler(this);

		CRegKey crkHelp;
		long iR = crkHelp.Open(HKEY_CURRENT_USER,TEXT("Software\\VB and VBA Program Settings\\NumCatAddIn\\Help"),KEY_READ);

		if (iR != ERROR_SUCCESS) // Houston we have a problem
				m_sHelpFile = "";
			else
			{
#define KEYLEN 250
				char szLocation[KEYLEN];
				DWORD dwLen = KEYLEN - 2;

				iR = crkHelp.QueryValue(szLocation,"Location",&dwLen);

				if (iR != ERROR_SUCCESS)
					m_sHelpFile="";
					else
					{
					m_sHelpFile = szLocation;
					if (m_sHelpFile.substr(m_sHelpFile.length()-3,3).compare("chm")!=0)
						m_sHelpFile=""; // as it hasn't been located

					}
			crkHelp.Close();
			}


		return 0;
	}

	// this workaround solves a bug in CMultiPaneStatusBarCtrl
	// (in SetPanes() method) that limits the size of all panes
	// after the default pane to a combined total of 100 pixels  
#ifndef _NOSTATUS_BAR
	void SetPaneWidths(int* arrWidths, int nPanes)
	{
		// find the size of the borders
		int arrBorders[3];
		m_status.GetBorders(arrBorders);

		// calculate right edge of default pane
		arrWidths[0] += arrBorders[2];
		for (int i = 1; i < nPanes; i++)
			arrWidths[0] += arrWidths[i];

		// calculate right edge of remaining panes
		for (int j = 1; j < nPanes; j++)
			arrWidths[j] += arrBorders[2] + arrWidths[j - 1];

		// set the pane widths
		m_status.SetParts(m_status.m_nPanes, arrWidths);
	}
#endif

	LRESULT OnFileRun(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		m_encEdCmd = esecRun; // will be picked up later
		
		return OnFileExit(wNotifyCode,wID,hWndCtl,bHandled);
	}

	LRESULT OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
#ifndef _NOEDITORWINDOW
	ATLASSERT(m_pView); // catch this in debug
//	if ((m_pView)&&(m_pView->hasChanges())&&(IDYES==MessageBox("Changes haven't been saved, do you want to save now ?","Numerical Catalyst Editor",MB_YESNOCANCEL | MB_ICONWARNING | MB_APPLMODAL )))
	if ((m_pView)&&(m_pView->hasChanges()))
		{
		long iReturn = MessageBox("Changes haven't been saved, do you want to save now ?","Numerical catalyst editor",MB_YESNOCANCEL | MB_ICONWARNING | MB_APPLMODAL );
		ATLTRACE("Return value = %d\n",iReturn);
		if (iReturn==IDCANCEL)
			return 0;

		if (iReturn==IDYES)
			m_pView->SaveStream();
		}
#endif
		PostMessage(WM_CLOSE);
		return 0;
	}

	LRESULT OnFileNew(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		// TODO: add code to initialize document

		return 0;
	}

	LRESULT OnViewToolBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		static BOOL bVisible = TRUE;	// initially visible
		bVisible = !bVisible;
		CReBarCtrl rebar = m_hWndToolBar;
		int nBandIndex = rebar.IdToIndex(ATL_IDW_BAND_FIRST + 1);	// toolbar is 2nd added band
		rebar.ShowBand(nBandIndex, bVisible);
		UISetCheck(ID_VIEW_TOOLBAR, bVisible);
		UpdateLayout();
		return 0;
	}

	LRESULT OnViewStatusBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		BOOL bVisible = !::IsWindowVisible(m_hWndStatusBar);
		::ShowWindow(m_hWndStatusBar, bVisible ? SW_SHOWNOACTIVATE : SW_HIDE);
		UISetCheck(ID_VIEW_STATUS_BAR, bVisible);
		UpdateLayout();
		return 0;
	}

	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CAboutDlg dlg;
		dlg.DoModal();
		return 0;
	}

	LRESULT OnHelpEditor(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if (m_sHelpFile.length()>0)
			{		
			HWND h = HtmlHelp(m_hWnd,m_sHelpFile.c_str(),HH_HELP_CONTEXT,IDH_SYMEDITOR);
			ATLTRACE("HWND for helpfile =%d %s\n",h,m_sHelpFile.c_str());
			}
			else
				::MessageBox(m_hWnd,"Unable to locate help file","Numerical Catalyst",MB_OK|MB_ICONWARNING);
		return 0;
	}

	LRESULT OnHelpSyntax(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if (m_sHelpFile.length()>0)
			{		
			HWND h = HtmlHelp(m_hWnd,m_sHelpFile.c_str(),HH_HELP_CONTEXT,IDH_SYMLANG);
			ATLTRACE("HWND for helpfile =%d %s\n",h,m_sHelpFile.c_str());
			}
			else
				::MessageBox(m_hWnd,"Unable to locate help file","Numerical Catalyst",MB_OK|MB_ICONWARNING);
		return 0;
	}
	
	LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		// TODO : Add Code for message handler. Call DefWindowProc if necessary.
		if (m_hWnd != ::GetParent(HWND(wParam)))
			::SetFocus(m_hWnd);

		if (HWND(wParam)==GetParent())
			::SetFocus(m_hWnd);
		
		ATLTRACE("KillFocus HWND %d ",wParam);
		ATLTRACE(", m_hWnd = %d\n",m_hWnd);
		
		return 0;
	}


	LRESULT OnQuit(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		ATLTRACE("OnQuit\n");
		// TODO : Add Code for message handler. Call DefWindowProc if necessary.
		
		return 0;
	}
protected:
	string m_sHelpFile;
	enumNumCatEditorCommand m_encEdCmd;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYMEDITFRM_H__EEEE5672_8CE9_444A_85AB_917BC939A148__INCLUDED_)
