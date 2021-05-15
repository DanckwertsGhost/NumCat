// SymRunProgressDlg.h : Declaration of the CSymRunProgressDlg

#ifndef __SYMRUNPROGRESSDLG_H_
#define __SYMRUNPROGRESSDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>
#include <process.h>
#include "..\CritCheck.h"
#include <atlctrls.h>
#include <string>
#include <vector>


// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

using namespace std;

#define WM_AR_TESTMESSAGE WM_USER + 1
#define BUFFETXT 10
#define TIME_ID 1

#ifndef NDEBUG
#define TIME_GAP 2000
#else
#define TIME_GAP 500
#endif

class CARRunInfo; // declare

/////////////////////////////////////////////////////////////////////////////
// CSymRunProgressDlg
class CSymRunProgressDlg : 
	public CAxDialogImpl<CSymRunProgressDlg>
{
public:
	CSymRunProgressDlg():m_bDestructionStarted(false),m_txtLen(BUFFETXT),m_parr(NULL)
	{
	InitializeCriticalSection(&m_cs); // not sure this will be needed
	InitializeCriticalSection(&m_csARI);
	m_hEventNoTextWrite = CreateEvent(NULL,TRUE,TRUE,NULL);

    m_hDialogBrush = CreateSolidBrush(RGB(255, 255, 255));
	m_vecNames.clear();

	}

	~CSymRunProgressDlg()
	{
	ThreadSafeDestroy(0); // experimental

    DeleteObject(m_hDialogBrush);
	}

	enum { IDD = IDD_SYMRUNPROGRESSDLG };



// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

BEGIN_MSG_MAP(CSymRunProgressDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
    MESSAGE_HANDLER(WM_CTLCOLORDLG, OnCtlColorDlg) //Add this macro.
	MESSAGE_HANDLER(WM_CTLCOLORSTATIC, OnCtlColor)
	MESSAGE_HANDLER(WM_TIMER, OnTimer)
	MESSAGE_HANDLER(WM_CLOSE, OnClose)
//	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	COMMAND_ID_HANDLER(WM_AR_TESTMESSAGE, OnTest)
END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		vector<string>::const_iterator cit;
		CCritCheck cc(m_cs);
	
		m_staticText.Attach(GetDlgItem(IDC_STATIC_PROG));
		m_staticTime.Attach(GetDlgItem(IDC_STATIC_TIME));

		for (cit=m_vecMessages.begin();cit!=m_vecMessages.end();cit++)
			AddText(cit->c_str());

		//m_staticText.SetWindowText("Bark\nMeow");
		//m_edText.SetWindowText("Woof");
		SetTimer(TIME_ID,TIME_GAP);

		return 1;  // Let the system set the focus
	}

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);


/*	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}*/

    LRESULT OnCtlColorDlg(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        return (long) m_hDialogBrush;
    }


	LRESULT OnCtlColor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
	 HDC hdcEdit = (HDC) wParam;    // handle to display context 
	 HWND hwndEdit = (HWND) lParam; // handle to static control 

/*	 if (( hwndEdit == GetDlgItem(IDC_EDIT)
	 || ( hwndEdit == GetDlgItem(IDC_COMBO))*/
	 if (( hwndEdit == GetDlgItem(IDC_STATIC_PROG) )||( hwndEdit == GetDlgItem(IDC_STATIC_TIME)))
	 {
/*	  // m_hBrush is an instance variable that stores the
	  // current Color brush. If this is the first time through
	  // we need to create it. The brush is deleted in the destructor
	  if ( m_hBrush == NULL )
	   m_hBrush = CreateSolidBrush( RGB(255,0,0)
	 )
*/
	  // Get the DC provided and set the appropriate attributes

	  SetBkMode(hdcEdit, TRANSPARENT );
	  SetBkColor(hdcEdit, RGB(255,255,255));

	  // Return a handle to the brush
	  HBRUSH far* hbr = (HBRUSH far*) m_hDialogBrush;
	  return ((DWORD) hbr);
	 }
	 return 0;
	}





	LRESULT OnTest(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		
		return 0;
	}

	bool PreCreate(CARRunInfo* parr);

	void PostClose();

	LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);


	void AttachProgText(LPCTSTR lpszString)
	{
		ATLTRACE("%%Start crit sec m_cs from AttachProgText for %s\n",lpszString);
		ResetEvent(m_hEventNoTextWrite); // signal text being writen
		{
			CCritCheck cc(m_cs);
			if (::IsWindow(m_hWnd))
				AddText(lpszString);
				else
				m_vecMessages.push_back(lpszString); // for latter use
			ATLTRACE("%%End crit sec m_cs from AttachProgText %s\n",lpszString);
		}
		ATLTRACE("Ended CS %d in AttachProgText - about to signal event TRUE\n",&m_cs);
		SetEvent(m_hEventNoTextWrite); // reset event
		Sleep(100); // so another call can't be made before a waiting thread with ThreadSafeDestroy starts
	}

	BOOL ThreadSafeDestroy(WORD wID)
	{
		BOOL bResult;

//		DWORD dwState;
		
		while(WaitForSingleObject( m_hEventNoTextWrite, 50 )!=WAIT_OBJECT_0);


		ATLTRACE("%%Start crit sec m_cs from ThreadSafeDestroy%%\n");
		CCritCheck cc(m_cs);

		ATLTRACE("#ThreadSafeDestroy called - ");
#ifndef NDEBUG
		if (m_bDestructionStarted)
			ATLTRACE("already been called\n");
#endif
		if (m_bDestructionStarted)
			return false; // as its already happened

		KillTimer(TIME_ID);

		m_bDestructionStarted=true;
		ATLTRACE("called for first time\n");

		bResult = EndDialog(wID);//DestroyWindow();
		ATLTRACE("%%End crit sec m_cs from ThreadSafeDestroy%%\n");
		return bResult;//DestroyWindow();
	}

	LRESULT SendSafeMessage(UINT message, WPARAM wParam = 0, LPARAM lParam = 0)
	{
		LRESULT lr=0;
//		ATLTRACE("%%Start SendSafeMessage with CS %d %%\n",&m_cs);
//		CCritCheck cc(m_cs);

		if (!::IsWindow(m_hWnd))
			{
			ATLTRACE("**SendSafeMessage: aborted as m_hWnd is not a window");
			return 0;
			}

		if (message==WM_CLOSE)
			ATLTRACE("**SendSafeMessage:About to send message WM_CLOSE\n");
		if (message==WM_QUIT)
			ATLTRACE("**SendSafeMessage:About to send message WM_QUIT\n");

//		lr = ::SendMessage(m_hWnd,message,wParam,lParam);
		lr = SendMessage(message,wParam);

		if (message==WM_CLOSE)
			ATLTRACE("**SendSafeMessage:Return message WM_CLOSE value = %d m_hWnd = %d\n",lr,m_hWnd);
		if (message==WM_QUIT)
			ATLTRACE("**SendSafeMessage:Return message WM_QUIT value = %d m_hWnd = %d\n",lr,m_hWnd);
//		ATLTRACE("%%End SendSafeMessage with CS %d %%\n",&m_cs);

		return lr;
	}

private:
	HWND m_hwndHost;
	bool m_bDestructionStarted;
	CRITICAL_SECTION m_cs;
	CRITICAL_SECTION m_csARI;
	HANDLE m_hEventNoTextWrite;
	CStatic m_staticText;
	CStatic m_staticTime;

//	CEdit m_edText;
	long m_txtLen;
	vector<string> m_vecMessages;
	HBRUSH m_hDialogBrush;
	CARRunInfo* m_parr;

	void AddText(LPCTSTR lpszString)
	{
	  ATLASSERT(::IsWindow(m_hWnd));
	  char *sMessage;
	  long iLen = strlen(lpszString);
	  m_txtLen += 4 + iLen;
	  sMessage = newtrack char[m_txtLen];
	  m_staticText.GetWindowText(sMessage,m_txtLen-BUFFETXT);
	  strcat(sMessage,"\n");
	  strcat(sMessage,lpszString);
	  m_staticText.SetWindowText(sMessage);
	  delete []sMessage;
	}

	vector<double> m_vecValues;
	vector<string> m_vecNames;


	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		ATLTRACE("SymRunProgressDlg::OnClose called about to call ThreadSafeDestroy(0)\n");
		ThreadSafeDestroy(0);
		return 0;
	}
};

#endif //__SYMRUNPROGRESSDLG_H_
