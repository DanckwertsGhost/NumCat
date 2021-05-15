// AtlBasicWindow.cpp: implementation of the CARLatlBasicHoldWnd class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "ARLatlBasicHoldWnd.h"

BOOL CARLatlBasicHoldWnd::PreTranslateMessage(MSG* pMsg)
{
	pMsg;
	return FALSE;
}

LRESULT CARLatlBasicHoldWnd::OnPaint(UINT nMsg, WPARAM wparam, LPARAM lparam, BOOL& bHandled)
{
    PAINTSTRUCT ps;
    HDC         hdc = BeginPaint(&ps);
    RECT        rect; GetClientRect(&rect);
//	HPEN oldPen;
//	HPEN newPen;
	
//	newPen = GetStockObject(WHITE_PEN);
	SelectObject(hdc,GetStockObject(WHITE_PEN));
	SelectObject(hdc,GetStockObject(GRAY_BRUSH));

	Rectangle(hdc,0,0,rect.right,rect.bottom);
    DrawText(hdc, __T("Place Holder"), -1, &rect,
             DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    EndPaint(&ps);

    return 0;
}
