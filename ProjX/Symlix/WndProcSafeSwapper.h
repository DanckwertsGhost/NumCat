// WndProcSafeSwapper.h: interface for the CWndProcSafeSwapper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WNDPROCSAFESWAPPER_H__275EBB6C_E23D_4A35_8FE5_CC03482A3B43__INCLUDED_)
#define AFX_WNDPROCSAFESWAPPER_H__275EBB6C_E23D_4A35_8FE5_CC03482A3B43__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// start window 
#include <atlwin.h>


class CWndProcSafeSwapper  
{

private:

		HWND m_hwndSwap;

public:
		CWndProcSafeSwapper();
		~CWndProcSafeSwapper();


		void SubClass(HWND hwndHost);

};



#endif // !defined(AFX_WNDPROCSAFESWAPPER_H__275EBB6C_E23D_4A35_8FE5_CC03482A3B43__INCLUDED_)
