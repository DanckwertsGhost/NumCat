// WndProcSafeSwapper.cpp: implementation of the CWndProcSafeSwapper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WndProcSafeSwapper.h"


#ifndef EXCELWNDPROC
#define EXCELWNDPROC

WNDPROC g_lpfnOldExcelWndProc;


LRESULT CALLBACK WndProcExcelModal (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
     {
     case WM_LBUTTONDOWN: // oh no you don't
		 ATLTRACE("WM_LBUTTONDOWN intercepted\n");
		 return 0;
     case WM_LBUTTONUP: // oh no you don't
		 ATLTRACE("WM_LBUTTONUP intercepted\n");
		 return 0;

	 case WM_NCLBUTTONDOWN:
		 ATLTRACE("WM_NCLBUTTONDOWN ");
		 break;
	 case WM_SETCURSOR:
		 ATLTRACE("WM_SETCURSOR ");
		 break;
	 case WM_STYLECHANGING:
		 ATLTRACE("WM_STYLECHANGING ");
		 break;
	 case 49614:
		 ATLTRACE("Command 49614 ");
//		 return 0;
		 break;
	 case WM_KILLFOCUS:
		 ATLTRACE("WM_KILLFOCUS ");
		 break;
	 case WM_SETFOCUS:
		 ATLTRACE("WM_SETFOCUS ");
		 break;
	 case WM_CAPTURECHANGED:
		 ATLTRACE("WM_CAPTURECHANGED ");
		 break;
	 case WM_STYLECHANGED:
		 ATLTRACE("WM_STYLECHANGED ");
		 break;
	 case WM_CLOSE:
		 ATLTRACE("Stop WM_CLOSE\n");
//		 return 0;
		 break;
	 case WM_QUIT:
		 ATLTRACE("Stop WM_QUIT\n");
//		 return 0;
		 break;
	 case WM_DESTROY:
		 ATLTRACE("Stop WM_DESTROY\n");
//		 return 0;
		 break;
	 case WM_NCACTIVATE:
		 ATLTRACE("Stop WM_NCACTIVATE\n");
//		 return 0;		 
		 break;
	 case WM_ACTIVATE:
		 ATLTRACE("Stop WM_ACTIVATE\n");
//		 return 0;
		 break;
	 default:
		 break;
	}



	ATLTRACE("Intecepted Excel signal %d\n",message);
	return CallWindowProc(g_lpfnOldExcelWndProc,hwnd, message, wParam, lParam);
//			return ::DefWindowProc (hwnd, message, wParam, lParam) ;
};

#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWndProcSafeSwapper::CWndProcSafeSwapper():m_hwndSwap(NULL)
{
	g_lpfnOldExcelWndProc=NULL;
}

CWndProcSafeSwapper::~CWndProcSafeSwapper()
{
	ATLTRACE("Before restore %d ",g_lpfnOldExcelWndProc);
	if (m_hwndSwap)
			g_lpfnOldExcelWndProc = (WNDPROC)::SetWindowLongPtr(m_hwndSwap,GWL_WNDPROC, (DWORD) g_lpfnOldExcelWndProc);
	ATLTRACE("after %d \n",g_lpfnOldExcelWndProc);
}

void CWndProcSafeSwapper::SubClass(HWND hwndHost)
{
	g_lpfnOldExcelWndProc = NULL;
	m_hwndSwap = hwndHost;
	if (m_hwndSwap)
			{
				g_lpfnOldExcelWndProc = (WNDPROC)::SetWindowLongPtr(m_hwndSwap,GWL_WNDPROC, (DWORD) WndProcExcelModal);
				ATLASSERT(g_lpfnOldExcelWndProc!=WndProcExcelModal);
				ATLTRACE("Old Excel = %d ",g_lpfnOldExcelWndProc);
				ATLTRACE("new proc = %d \n",WndProcExcelModal);
			}			

}
