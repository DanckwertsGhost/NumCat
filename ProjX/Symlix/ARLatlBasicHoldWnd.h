// ARLatlBasicHoldWnd.h: interface for the CAtlBasicWindow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARLATLBASICHOLDWND_H__1B6C9FFF_F9C6_4126_A538_5848DF3D7E5C__INCLUDED_)
#define AFX_ARLATLBASICHOLDWND_H__1B6C9FFF_F9C6_4126_A538_5848DF3D7E5C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define DECLARE_WND_SUPERCLASS_ARROW(WndClassName, OrigWndClassName) \
static CWndClassInfo& GetWndClassInfo() \
{ \
	static CWndClassInfo wc = \
	{ \
		{ sizeof(WNDCLASSEX), 0, StartWindowProc, \
		  0, 0, NULL, NULL, NULL, NULL, NULL, WndClassName, NULL }, \
		OrigWndClassName, NULL, IDC_ARROW, TRUE, 0, _T("") \
	}; \
	return wc; \
}

class CARLatlBasicHoldWnd  : public CWindowImpl<CARLatlBasicHoldWnd, CWindow>  
{
public:

	DECLARE_WND_SUPERCLASS_ARROW(NULL, CWindow::GetWndClassName())

	BOOL PreTranslateMessage(MSG* pMsg);

	BEGIN_MSG_MAP(CAtlBasicWindow)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
	END_MSG_MAP()
protected:

    LRESULT OnPaint(UINT nMsg, WPARAM wparam, LPARAM lparam, BOOL& bHandled);

	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		
		Invalidate();
		return 0;
	}

};


#endif // !defined(AFX_ARLATLBASICHOLDWND_H__1B6C9FFF_F9C6_4126_A538_5848DF3D7E5C__INCLUDED_)
