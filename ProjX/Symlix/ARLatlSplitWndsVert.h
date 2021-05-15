// ARLatlSplitWndsVert.h: interface for the CARLatlSplitWndsVert class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARLATLSPLITWNDSVERT_H__F8BF20EB_F61F_4035_B8F8_BDAFD36E43E0__INCLUDED_)
#define AFX_ARLATLSPLITWNDSVERT_H__F8BF20EB_F61F_4035_B8F8_BDAFD36E43E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ARLatlBasicHoldWnd.h"
#include "ARLatlDividerWnd.h"


#define CARLatlSplitWndsVertImpl CWindowImpl<CARLatlSplitWndsVert, CWindow>
#define CWinTraitsDivider CWinTraits<WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_BORDER, NULL>




template <class TWinLeft=CARLatlBasicHoldWnd, class TWinRight=CARLatlBasicHoldWnd, class TWinTraitsLeft = CControlWinTraits, class TWinTraitsRight = CControlWinTraits  >
class CARLatlSplitWndsVert : public CARLatlSplitWndsVertImpl, public CATLatlSplitWndsAttribs 
{
public:
	DECLARE_WND_SUPERCLASS(NULL, CWindow::GetWndClassName())


	BOOL PreTranslateMessage(MSG* pMsg)
	{
		pMsg;
		return FALSE;
	}

	BEGIN_MSG_MAP(CARLatlSplitWndsVert)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_USER_DIVMOVE, OnDivMove)
	END_MSG_MAP()

	CARLatlSplitWndsVert():CARLatlSplitWndsVertImpl(),CATLatlSplitWndsAttribs(){}
	~CARLatlSplitWndsVert(){}

private:

//	HWND m_chwnd[ARL_COL_COUNT];
	TWinLeft m_subLeft;
	TWinRight m_subRight;
	CARLatlDividerWndVert m_subDiv;

//	int m_iLeftOffset;

    LRESULT OnPaint(UINT nMsg, WPARAM wparam, LPARAM lparam, BOOL& bHandled) 
	{
		PAINTSTRUCT ps;
		HDC         hdc = BeginPaint(&ps);
		RECT        rect; GetClientRect(&rect);
		Rectangle(hdc,0,0,rect.right,rect.bottom);
		DrawText(hdc, __T("Hello, Windows"), -1, &rect,
				 DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		EndPaint(&ps);

		return 0;
	 }

	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		
		Invalidate();

		ReSizeChildren(HIWORD(lParam),LOWORD(lParam),m_iLeftOffset);

		return 0;
	}

	LRESULT OnDivMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{

		RECT pRC;
		POINT pMouse;

		GetClientRect(&pRC);
		pMouse.x = LOWORD( lParam );
		pMouse.y = HIWORD( lParam );

		ATLTRACE(_T("OnDivMove Screen (x=%d,y=%d) \t"),pMouse.x,pMouse.y);
		ScreenToClient(&pMouse);
		ATLTRACE(_T("OnDivMove Client (x=%d,y=%d) \n"),pMouse.x,pMouse.y);
		
		pMouse.x -= ARL_COL_WIDTH/2;
		
		ReSizeChildren(short(pRC.bottom),short(pRC.right),short(pMouse.x));

		return 0;
	}

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		int iR = ARL_COL_COUNT;

//		m_iLeftOffset = ARL_START_OFFSET;
		RECT rcNew = rcDefault;

			m_chwnd[1] = m_subDiv.Create(m_hWnd, rcNew, NULL, CWinTraitsDivider::GetWndStyle(NULL), CWinTraitsDivider::GetWndExStyle(NULL)/*WS_EX_TOOLWINDOW| WS_EX_CLIENTEDGE*/);
			m_chwnd[0] = m_subLeft.Create(m_hWnd, rcNew, NULL, TWinTraitsLeft::GetWndStyle(m_splitAttribs.getdwStyleLeft()), TWinTraitsLeft::GetWndExStyle(m_splitAttribs.getdwStyleLeftEx()) /*NULL/*WS_EX_TOOLWINDOW/*WS_EX_CLIENTEDGE*/);
			m_chwnd[2] = m_subRight.Create(m_hWnd, rcNew, NULL, TWinTraitsRight::GetWndStyle(m_splitAttribs.getdwStyleRight()), TWinTraitsRight::GetWndExStyle(m_splitAttribs.getdwStyleRightEx()) /*NULL/*WS_EX_TOOLWINDOW/*WS_EX_CLIENTEDGE*/);

		return 0;
	}

protected:

	void ReSizeChildren(short cy, short cx, short cxfirst)
	{
			static short iDivWidth = ARL_COL_WIDTH;

			short cxsecond = cx - cxfirst - iDivWidth;

			ATLTRACE(_T("cx %d cxfirst %d iDivWidth %d cxsecond %d\n"),cx,cxfirst,iDivWidth,cxsecond);
			
			ATLASSERT(cx==cxfirst+iDivWidth+cxsecond);

			for (int iC=0;iC<ARL_COL_COUNT;iC++)
					switch(iC)
						{
						case 0:
							::MoveWindow(m_chwnd[iC],0,0,cxfirst,cy,TRUE);
							break;
						case 1:
							::MoveWindow(m_chwnd[iC],cxfirst,0,iDivWidth,cy,TRUE);
							break;
						case 2:
							::MoveWindow(m_chwnd[iC],cxfirst+iDivWidth,0,cxsecond,cy,TRUE);
							break;
						default:
							ATLASSERT(false);
						}
			m_iLeftOffset = cxfirst;

	}
public:
	TWinLeft& GetWinLeft(){ return &m_subLeft; }
	TWinLeft* GetWinLeftPt(){ return &m_subLeft; }
	TWinRight& GetWinRight(){ return &m_subRight; }
	TWinRight* GetWinRightPt(){ return &m_subRight; }
};

#endif // !defined(AFX_ARLATLSPLITWNDSVERT_H__F8BF20EB_F61F_4035_B8F8_BDAFD36E43E0__INCLUDED_)
