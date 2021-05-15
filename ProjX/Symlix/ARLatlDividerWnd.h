// ARLatlDividerWnd.h: interface for the CARLatlDividerWnd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARLATLDIVIDERWND_H__33797142_2C07_45EE_B3CA_25783656C687__INCLUDED_)
#define AFX_ARLATLDIVIDERWND_H__33797142_2C07_45EE_B3CA_25783656C687__INCLUDED_
 
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ARLatlBasicHoldWnd.h"

#define WM_USER_DIVMOVE WM_USER+1
#define ARL_COL_COUNT 3
#define ARL_COL_WIDTH 4
#define ARL_START_OFFSET 100

class CATLatlSpitAttributes // helper class for window attributes
{
public:
	CATLatlSpitAttributes():dwStyleLeft(NULL),dwStyleLeftEx(NULL),dwStyleRight(NULL),dwStyleRightEx(NULL){}
	CATLatlSpitAttributes( const CATLatlSpitAttributes& csa):dwStyleLeft(NULL),dwStyleLeftEx(NULL),dwStyleRight(NULL),dwStyleRightEx(NULL){ copy(csa); }
	~CATLatlSpitAttributes(){}
	inline DWORD getdwStyleLeft(){ return dwStyleLeft; }
	inline DWORD getdwStyleLeftEx(){ return dwStyleLeftEx; }
	inline DWORD getdwStyleRight(){ return dwStyleRight; }
	inline DWORD getdwStyleRightEx(){ return dwStyleRightEx; }

	inline void setdwStyleLeft(DWORD dw){ dwStyleLeft = dw; }
	inline void setdwStyleLeftEx(DWORD dw){ dwStyleLeftEx = dw; }
	inline void setdwStyleRight(DWORD dw){ dwStyleRight = dw; }
	inline void setdwStyleRightEx(DWORD dw){ dwStyleRightEx = dw; }
	CATLatlSpitAttributes& operator = ( const CATLatlSpitAttributes& csa ){ copy(csa); return *this; }

private:
	void copy(const CATLatlSpitAttributes& csa)
	{
		dwStyleLeft = csa.dwStyleLeft;
		dwStyleLeftEx = csa.dwStyleLeftEx;
		dwStyleRight = csa.dwStyleRight;
		dwStyleRightEx = csa.dwStyleRightEx;		

	}

	DWORD dwStyleLeft;
	DWORD dwStyleLeftEx;
	DWORD dwStyleRight;
	DWORD dwStyleRightEx;
};

class CATLatlSplitWndsAttribs
{
public:
	CATLatlSplitWndsAttribs():m_iLeftOffset(ARL_START_OFFSET){}
	~CATLatlSplitWndsAttribs(){}

	CATLatlSpitAttributes getSplitAttribs(){ return m_splitAttribs; }
	void setSplitAttribs(const CATLatlSpitAttributes& csa ){ m_splitAttribs = csa; }
	void setOffsetWindow(short iOffset){ m_iLeftOffset = iOffset; }
	short getOffsetWindow() const {return m_iLeftOffset; } // in case its needed
	HWND getLeftHWND(){ return m_chwnd[0]; }
	HWND getRightHWND(){ return m_chwnd[2]; }

protected:
	CATLatlSpitAttributes m_splitAttribs;
	short m_iLeftOffset;
	HWND m_chwnd[ARL_COL_COUNT];

};

#define DECLARE_WND_SUPERCLASS_NSSIZE(WndClassName, OrigWndClassName) \
static CWndClassInfo& GetWndClassInfo() \
{ \
	static CWndClassInfo wc = \
	{ \
		{ sizeof(WNDCLASSEX), 0, StartWindowProc, \
		  0, 0, NULL, NULL, NULL, NULL, NULL, WndClassName, NULL }, \
		OrigWndClassName, NULL, IDC_SIZENS, TRUE, 0, _T("") \
	}; \
	return wc; \
}

#define DECLARE_WND_SUPERCLASS_WESIZE(WndClassName, OrigWndClassName) \
static CWndClassInfo& GetWndClassInfo() \
{ \
	static CWndClassInfo wc = \
	{ \
		{ sizeof(WNDCLASSEX), 0, StartWindowProc, \
		  0, 0, NULL, NULL, NULL, NULL, NULL, WndClassName, NULL }, \
		OrigWndClassName, NULL, IDC_SIZEWE, TRUE, 0, _T("") \
	}; \
	return wc; \
}

class CARLatlDividerWndHoriz: public CWindowImpl<CARLatlDividerWndHoriz, CWindow>
{
public:

	DECLARE_WND_SUPERCLASS_NSSIZE(NULL, CWindow::GetWndClassName())

	BEGIN_MSG_MAP(CARLatlDividerWndHoriz)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUP)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
	END_MSG_MAP()

	CARLatlDividerWndHoriz();
	virtual ~CARLatlDividerWndHoriz();

protected:

	bool m_bLBDown;
	bool m_bMouseBlocking;
	short m_iMouseLBDPointX;

	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		
		Invalidate();

		return 0;
	}


	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_bLBDown=true;
		m_iMouseLBDPointX = LOWORD( lParam );
		//SetCursor(LoadCursor(NULL, IDC_SIZEWE));
		SetCapture();
		m_bMouseBlocking=true;
		ATLTRACE(_T("OnLButtonDown\n"));
		return 0;
	}
	LRESULT OnLButtonUP(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_bLBDown=false;
		//SetCursor(LoadCursor(NULL, IDC_ARROW));
		if (m_bMouseBlocking)
			{
			ReleaseCapture();
			m_bMouseBlocking=false;
			}
		ATLTRACE(_T("OnLButtonUp\n"));
		return 0;
	}

    LRESULT OnPaint(UINT nMsg, WPARAM wparam, LPARAM lparam, BOOL& bHandled)
	{
		PAINTSTRUCT ps;
		HDC         hdc = BeginPaint(&ps);
		RECT        rect; GetClientRect(&rect);
	//	HPEN oldPen;
	//	HPEN newPen;
		
	//	newPen = GetStockObject(WHITE_PEN);
		SelectObject(hdc,GetStockObject(WHITE_PEN));

		Rectangle(hdc,0,0,rect.right,rect.bottom);
		EndPaint(&ps);

		return 0;
	}

	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		POINT pMouse;
		short cx = LOWORD(lParam);
		pMouse.x = cx;
		pMouse.y = HIWORD(lParam);

		ATLTRACE(_T("OnMouseMove Client (x=%d,y=%d) \t"),pMouse.x,pMouse.y);

		ClientToScreen(&pMouse);

		ATLTRACE(_T("OnMouseMove Screen (x=%d,y=%d) \t"),pMouse.x,pMouse.y);

		LPARAM lnew = MAKELPARAM(pMouse.x,pMouse.y);

		ATLTRACE(_T("OnMouseMove %d=(%d)-(%d) (Divider)\n"),lnew,m_iMouseLBDPointX,LOWORD(lParam));

		if (m_bMouseBlocking&&m_bLBDown)
			this->SendMessage(this->GetParent(),WM_USER_DIVMOVE,wParam,lnew);

		return 0;
	}

	LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_bLBDown=false;
		return 0;
	}


};

class CARLatlDividerWndVert: public CWindowImpl<CARLatlDividerWndVert, CWindow>
{
public:

	DECLARE_WND_SUPERCLASS_WESIZE(NULL, CWindow::GetWndClassName())

	BEGIN_MSG_MAP(CARLatlDividerWndVert)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUP)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
	END_MSG_MAP()

	CARLatlDividerWndVert();
	virtual ~CARLatlDividerWndVert();

protected:

	bool m_bLBDown;
	bool m_bMouseBlocking;
	short m_iMouseLBDPointX;

	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		
		Invalidate();

		return 0;
	}


	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_bLBDown=true;
		m_iMouseLBDPointX = LOWORD( lParam );
		//SetCursor(LoadCursor(NULL, IDC_SIZEWE));
		SetCapture();
		m_bMouseBlocking=true;
		ATLTRACE(_T("OnLButtonDown\n"));
		return 0;
	}
	LRESULT OnLButtonUP(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_bLBDown=false;
		//SetCursor(LoadCursor(NULL, IDC_ARROW));
		if (m_bMouseBlocking)
			{
			ReleaseCapture();
			m_bMouseBlocking=false;
			}
		ATLTRACE(_T("OnLButtonUp\n"));
		return 0;
	}

    LRESULT OnPaint(UINT nMsg, WPARAM wparam, LPARAM lparam, BOOL& bHandled)
	{
		PAINTSTRUCT ps;
		HDC         hdc = BeginPaint(&ps);
		RECT        rect; GetClientRect(&rect);
	//	HPEN oldPen;
	//	HPEN newPen;
		
	//	newPen = GetStockObject(WHITE_PEN);
		SelectObject(hdc,GetStockObject(WHITE_PEN));

		Rectangle(hdc,0,0,rect.right,rect.bottom);
		EndPaint(&ps);

		return 0;
	}

	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		POINT pMouse;
		short cx = LOWORD(lParam);
		pMouse.x = cx;
		pMouse.y = HIWORD(lParam);

		ATLTRACE(_T("OnMouseMove Client (x=%d,y=%d) \t"),pMouse.x,pMouse.y);

		ClientToScreen(&pMouse);

		ATLTRACE(_T("OnMouseMove Screen (x=%d,y=%d) \t"),pMouse.x,pMouse.y);

		LPARAM lnew = MAKELPARAM(pMouse.x,pMouse.y);

		ATLTRACE(_T("OnMouseMove %d=(%d)-(%d) (Divider)\n"),lnew,m_iMouseLBDPointX,LOWORD(lParam));

		if (m_bMouseBlocking&&m_bLBDown)
			this->SendMessage(this->GetParent(),WM_USER_DIVMOVE,wParam,lnew);

		return 0;
	}

	LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_bLBDown=false;
		return 0;
	}


};

#endif // !defined(AFX_ARLATLDIVIDERWND_H__33797142_2C07_45EE_B3CA_25783656C687__INCLUDED_)
