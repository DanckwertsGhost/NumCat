// SymEdErrList.h: interface for the CSymEdErrList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYMEDERRLIST_H__2FD35B63_0460_4ECB_8813_B199CBA63B43__INCLUDED_)
#define AFX_SYMEDERRLIST_H__2FD35B63_0460_4ECB_8813_B199CBA63B43__INCLUDED_

#include <atlctrls.h>
#include <string>
#include <vector>
#include "symlix.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WM_SELECTAPOINT WM_USER+100

#pragma warning(disable:4786)

using namespace std;

#define HANDLE_HR_FAILURE(hr) { if (FAILED(hr)) \
				{ \
				ATLTRACE("<Error> hr=%d failure at ",hr); \
				ATLTRACE("%d",__LINE__); \
				ATLTRACE(" %s\n",__FILE__); \
				ATLASSERT(false); \
				return bResult; \
				}}

#define HANDLE_HR_FAILURE2(hr) { if (FAILED(hr)) \
				{ \
				ATLTRACE("<Error> hr=%d failure at ",hr); \
				ATLTRACE("%d",__LINE__); \
				ATLTRACE(" %s\n",__FILE__); \
				ATLASSERT(false); \
				return; \
				}}

class CSymEdErrList : public CWindowImpl<CSymEdErrList, CListViewCtrl>  
{

public:
	DECLARE_WND_SUPERCLASS(NULL, CSymEdErrList::GetWndClassName())

	BOOL PreTranslateMessage(MSG* pMsg)
	{
		pMsg;
		return FALSE;
	}

	BEGIN_MSG_MAP(CSymEdErrList)
//		MESSAGE_HANDLER(WM_RBUTTONUP, OnRButtonUp)
// 		COMMAND_ID_HANDLER(ID_POPUP1_FUNCTIONS_SIN, OnWriteEgSin)
// 		MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk)
     END_MSG_MAP()

	inline long getNumberErrors() const { return m_vecER.size(); }

	void setIErrorRun(INumCatErrorRun* pIErrorRun, const char* sStreamName )
	{

		m_sOpenStreamName = sStreamName;
		
		if (pIErrorRun)
				{
				m_pIErrorRun = pIErrorRun;
//				SET UP THERE ERROR COUNT HERE
//===========================
				{
				USES_CONVERSION;
				long iCount,iSize;
				long iLBnd,iUBnd;
				UINT iC;
				CErrorRecord cer;
				SAFEARRAY* pSAErrors = NULL; 
				INumCatError** prgn =0;
				HRESULT hr = m_pIErrorRun->get_CountErrors(&iCount);

				HANDLE_HR_FAILURE2(hr)
				
				hr = m_pIErrorRun->GetAllErrors(&pSAErrors);

				HANDLE_HR_FAILURE2(hr)

				hr = SafeArrayAccessData(pSAErrors,(void**)&prgn);
				
				HANDLE_HR_FAILURE2(hr)

				iSize = SafeArrayGetElemsize(pSAErrors);

				hr = SafeArrayGetLBound(pSAErrors,1,&iLBnd);

				HANDLE_HR_FAILURE2(hr)

				hr = SafeArrayGetUBound(pSAErrors,1,&iUBnd);
				
				HANDLE_HR_FAILURE2(hr)

				BSTR bstrName = NULL;
				BSTR bstrDescr = NULL;
				long iLine;
				long iX;
				int iErrorCount = 0;
				m_vecER.clear();
				enumNumCatErrorCode esec;
				string sString;

				for (iC=0;iC<iCount;iC++)
					{
					 hr = prgn[iC]->get_StreamName(&bstrName);

					 string sString = OLE2CA(bstrName);

					 cer.setFileName( sString.c_str() );

					 if (SUCCEEDED(hr))
						{
						 hr = prgn[iC]->get_Description(&bstrDescr);

						 if (SUCCEEDED(hr))
							{
							 hr = prgn[iC]->get_ErrCode(&esec);
							 if ((SUCCEEDED(hr))&&(esec==errSyntax)) // ignore the other errors
								{
								 hr = prgn[iC]->get_Line(&iLine);
								 if (SUCCEEDED(hr))
									{
									hr = prgn[iC]->get_XPosition(&iX);
									if (m_sOpenStreamName.compare(cer.getFileName())==0) // then its OK
										{
										// do this stuff only if its going to be used
										sString = OLE2CA(bstrDescr);
										cer.setDesc( sString.c_str());
										cer.setCode(esec);
										cer.setLine(iLine+1); // +1 to get into lines from row 1 not zero
										cer.setX(iX);

//										this->InsertItem(iErrorCount++,cer.getErrorStr());
										m_vecER.push_back(cer);
//										ATLASSERT(m_vecER.size()==iErrorCount);
										}
									}
								}
							 SysFreeString(bstrDescr);
							}
						 SysFreeString(bstrName);
						}

					
			 					
					 if (FAILED(hr)) // for debug
							{
							ATLTRACE("Failed here %s %s\n",__FILE__,__LINE__);
							}

					} // end of for loop
				hr = SafeArrayUnaccessData(pSAErrors);

				HANDLE_HR_FAILURE2(hr)

				hr = SafeArrayDestroy(pSAErrors); // this calls Release() on each SAFEARRAY member - so no need to do here

				HANDLE_HR_FAILURE2(hr)

				}


//===========================
				}
				else
				m_pIErrorRun = NULL;
	}

	void SetLinkToEditor(HWND hwndEditor){ m_hwndEditor=hwndEditor; }

private:

	class CErrorRecord
	{
	public:
		CErrorRecord():m_sDesc(""),m_sFile(""),m_iLine(NOT_DEFINED),m_iX(NOT_DEFINED){}
		CErrorRecord(const CErrorRecord& cer ){ copy(cer); }
		~CErrorRecord(){}

		inline const char* getFileName() const { return m_sFile.c_str(); }
		inline const char* getDesc() const { return m_sDesc.c_str(); }
		inline long getLine() const { return m_iLine; }
		inline long getX() const { return m_iX; }
		inline enumNumCatErrorCode getCode() const { return m_eCode; }
		inline void setFileName(const char* sName){ m_sFile=sName; }
		inline void setDesc( const char* sDesc ){ m_sDesc=sDesc; }
		inline void setLine( long iLine ){ m_iLine = iLine; }
		inline void setX( long iX ){ m_iX = iX; }
		inline void setCode( enumNumCatErrorCode eCode ){ m_eCode = eCode; }
		const char* getErrorStr() {
									char sBuff[100];
									m_sFullDesc = m_sDesc;
									m_sFullDesc.append(" Line ");
									m_sFullDesc.append(_itoa(m_iLine,sBuff,10));
									return m_sFullDesc.c_str();
									}

		bool operator > (const CErrorRecord& cer) const
				{

				if (m_sDesc.compare(cer.m_sDesc)>0)
								return true;
								else
								if (m_sDesc.compare(cer.m_sDesc)<0)
										return false;

				if (m_iLine>cer.m_iLine)
								return true;
								else
								if (m_iLine<cer.m_iLine)
										return false;

				if (m_iX>cer.m_iX)
								return true;
								else
								if (m_iX<cer.m_iX)
										return false;

				return (m_sDesc.compare(cer.m_sDesc)>0);
				}

		bool operator < (const CErrorRecord& cer ) const { return (cer > *this); }
		CErrorRecord& operator = ( const CErrorRecord& cer ) { copy(cer); return *this; }

	private:
		void copy( const CErrorRecord& cer ){
				m_sFile = cer.m_sFile;
				m_sDesc = cer.m_sDesc;
				m_iLine = cer.m_iLine;
				m_iX = cer.m_iX;
				m_eCode = cer.m_eCode;
				}


		string m_sFile;
		string m_sDesc;
		string m_sFullDesc; // need to outlive request for value
		long m_iLine;
		long m_iX;
		enumNumCatErrorCode m_eCode;

	};


	vector<CErrorRecord> m_vecER;
	INumCatErrorRun* m_pIErrorRun;
	string m_sOpenStreamName;
	HWND m_hwndEditor;

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		// TODO : Add Code for message handler. Call DefWindowProc if necessary.
		ATLTRACE("OnLButtonDblClk WPARAM %d, LPARAM %d\n",wParam,lParam);
		ATLTRACE("Current selection is %d\n",GetSelectedIndex());
		long iLine = GetSelectedIndex();
		ATLTRACE("GetSelectedIndex returned %d\n",iLine);

		if (iLine<0) // ie -1 - out of range, so no action
			return 0;

		ATLASSERT(iLine<m_vecER.size());
		long iCodeLine = m_vecER[iLine].getLine();

		::PostMessage(m_hwndEditor,WM_SELECTAPOINT,iCodeLine,-1);
		return 0;
	}
};

#endif // !defined(AFX_SYMEDERRLIST_H__2FD35B63_0460_4ECB_8813_B199CBA63B43__INCLUDED_)
