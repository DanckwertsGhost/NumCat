// SymRunProgressDlg.cpp : Implementation of CSymRunProgressDlg
#include "stdafx.h"
#include "SymRunProgressDlg.h"
#include "Symlix.h"
#include "ARRunProgress.h"


/////////////////////////////////////////////////////////////////////////////
// CSymRunProgressDlg

bool CSymRunProgressDlg::PreCreate(CARRunInfo* parr)
{
	CCritCheck cc(m_csARI);
	m_parr = parr;
	if (m_parr)
		m_parr->setDlgPointer(this);

	return true;
}

void CSymRunProgressDlg::PostClose()
{
	CCritCheck cc(m_csARI);
	if (m_parr)
			{
			m_parr->m_DlgHwnd=NULL;
			m_parr->clearDlgPointer(); // disconnect
			}
	m_parr=NULL;
}


LRESULT CSymRunProgressDlg::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ATLTRACE("OnTimer %d\n",wParam);
	CCritCheck cs(m_csARI);

	if ((m_parr)&&(m_parr->readyWithData()))
		{
		string sMessage;
		char sTime[155];
		if (m_vecNames.size()<1)
			m_parr->getNames(m_vecNames);

		m_parr->getValues(m_vecValues);

		ATLTRACE("m_vecNames.size() %d,m_vecValues.size() %d ",m_vecNames.size(), m_vecValues.size());

		if ((m_vecNames.size()>0)&&(m_vecValues.size()>0)) // avoid a bad crash
			{
			ATLTRACE("About to append time message");
			sMessage = m_vecNames[0];
			sMessage.append(" = ");
			gcvt(m_vecValues[0],6,sTime);
			sMessage.append(sTime);
	//		sMessage.append(" secs"); no units assumed

			 m_staticTime.SetWindowText(sMessage.c_str());
			}
#ifndef NDEBUG
			else
			{
			ATLTRACE("Failure to fill vectors when signalled ready\n");
			ATLTRACE("m_vecNames.size() = %d , m_vecValues.size() = %d\n",m_vecNames.size(),m_vecValues.size());
			ATLASSERT(false);
			}
#endif
			ATLTRACE("\n");
		}



	return 0;
}

LRESULT CSymRunProgressDlg::OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CCritCheck cs(m_csARI);
		if (m_parr)
			{
			AttachProgText("Cancel called...");
			m_parr->sendStopSimulation(); // which stops the model running in the other thread
			}

//		ThreadSafeDestroy(wID); - not needed as the other thread will reply with a call to sendsafe message to close this dialog
		return 0;
}