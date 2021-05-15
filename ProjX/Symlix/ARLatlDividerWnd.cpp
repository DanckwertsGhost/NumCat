// ARLatlDividerWnd.cpp: implementation of the CARLatlDividerWnd class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ARLatlDividerWnd.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CARLatlDividerWndHoriz::CARLatlDividerWndHoriz():CWindowImpl<CARLatlDividerWndHoriz, CWindow>(),m_bLBDown(false),m_iMouseLBDPointX(-1),m_bMouseBlocking(false)
{
ATLTRACE("CARLatlDividerWndHoriz\n");
}

CARLatlDividerWndHoriz::~CARLatlDividerWndHoriz()
{

}



CARLatlDividerWndVert::CARLatlDividerWndVert():CWindowImpl<CARLatlDividerWndVert, CWindow>(),m_bLBDown(false),m_iMouseLBDPointX(-1),m_bMouseBlocking(false)
{
}

CARLatlDividerWndVert::~CARLatlDividerWndVert()
{

}