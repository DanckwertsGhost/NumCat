// SimpleEditExampleView.h : interface of the CSymEditView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYMEDITVIEW_H__79FC7297_A6AE_4CC4_83C1_DD95A682269E__INCLUDED_)
#define AFX_SYMEDITVIEW_H__79FC7297_A6AE_4CC4_83C1_DD95A682269E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "SymlixStore.h"
#include "../Token.h"
#include <list>
#include "../Tokeniser.h"
#include "resource.h"
#include <vector>
#include "SymEdLine.h"
#include "SymEdErrList.h"

#include <atlctrlx.h>
#include <atlmisc.h>

#pragma warning(disable:4786)

using namespace std;


class CHandleSymlixStreams
{
public:

	class CMainFrameStreamHolder // inner class to ensure values primed as NULL
	{
	public:
		CMainFrameStreamHolder():m_pIStore(NULL),m_pIStream(NULL),m_pIWriteStream(NULL),bReady(false){}
		~CMainFrameStreamHolder()
		{
			// in case anyone forgets
			removeWriteStream();
			removeStream();
			removeStore();
		}

		bool addStore(IARDataStore* pIStore)
		{
			try
			{
			removeStore();
			if (pIStore)
				{
				 m_pIStore = pIStore;
				 m_pIStore->AddRef();
				}
			}
			catch(...)
			{
				return false;
			}
			bReady = (m_pIStore!=NULL);
			return bReady;
		}

		bool removeStore()
		{

		bReady=false;
			try
			{
			if (m_pIStore)
				{
				m_pIStore->Release();
				m_pIStore=NULL;
				return true;
				}
			}
			catch(...)
			{
			ATLTRACE(_T("Error caught in CMainFrameStreamHolder::removeStore\n"));
			}

		return false;
		}

		bool addStream( BSTR* pbstr )
		{
			enumARReadHint erh = readFormatFreeText; // provides hint to stream if it wants to use it
			if ((!pbstr)||(!m_pIStore)) // a bit of defence
				return false;
			removeStream(); // need to ditch any exisitng streams
			
			HRESULT hr = m_pIStore->tryToGetARStream(pbstr,erh,&m_pIStream);

			if (SUCCEEDED(hr))
						return true;
			return false;
		}

		bool removeStream()
		{

			try
			{
			if (m_pIStream)
				{
				m_pIStream->Release();
				m_pIStream=NULL;
				return true;
				}
			}
			catch(...)
			{
			ATLTRACE(_T("Error caught in CMainFrameStreamHolder::removeStream\n"));
			}

		return false;
		}

		bool addWriteStream( BSTR* pbstr )
		{
			enumARWriteHint eswh = formatFreeText;
			if ((!pbstr)||(!m_pIStore)) // a bit of defence
				return false;
			removeWriteStream(); // need to ditch any exisitng streams
			
			HRESULT hr = m_pIStore->tryToGetARWriteStream(pbstr,eswh,&m_pIWriteStream);

			if (SUCCEEDED(hr))
						return true;
			
			return false;
		}

		bool removeWriteStream()
		{

			try
			{
			if (m_pIWriteStream)
				{
				enumARStream ess;
				HRESULT hr = m_pIWriteStream->closeStream(&ess);
				m_pIWriteStream->Release();
				m_pIWriteStream=NULL;
				if SUCCEEDED(hr)
						return true;
				return false;
				}
			}
			catch(...)
			{
			ATLTRACE(_T("Error caught in CMainFrameStreamHolder::removeWriteStream\n"));
			}

		return false;
		}

		bool isStoreReady(){ return bReady;}

	IARDataStore* m_pIStore;
	IARStream* m_pIStream;
	IARWriteStream* m_pIWriteStream;
	private:
		bool bReady;
	};
protected:
	CMainFrameStreamHolder strm;
};


#define POPUP_STRING_WRITE(funcName,strID) \
	LRESULT funcName(UINT uMsg, WPARAM /*wParam*/, HWND /*lParam*/, BOOL& /*bHandled*/) \
	{ \
		WriteForThisString(strID); \
		setDirty(); \
		return 0; \
	}

#define SYMEDLINE_STR_LENGTH 220

class CSymEditView : public CWindowImpl<CSymEditView, CRichEditCtrl>, public CHandleSymlixStreams
{

private:
/*
	class CSymHoldTokeniser
	{
	private:
		CTokeniser*	m_pTokeniser;
		setofwords m_setRecognisedFileNames; // not populated - but needed 
		mapUserDefinedKeys m_mapUDK; // not populated - but needed
		list<CToken> m_lToks;

	public:
		CSymHoldTokeniser();
		~CSymHoldTokeniser();
		CTokeniser* getTokeniser(){ return m_pTokeniser; }
		list<CToken>& getTokenisedList(long iLine, const char* sLine, const char* sStreamName );
	};
*/
	class CSymHoldLines // class created to ensure no attempts an accessing unallocated memory
	{
	public:
		CSymHoldLines():m_lDummy(){}
		~CSymHoldLines(){}
		CSymEdLine& operator[] (long iIndex)
			{
			if ((iIndex>=0)&&(iIndex<m_lLines.size()))
					return m_lLines[iIndex];
			ATLTRACE("<Warning> Out of range index call on CSymHoldLines %d where size was %d\n",iIndex,m_lLines.size());
			return m_lDummy;
			}
		long size(){ return m_lLines.size(); }
		void push_back(CSymEdLine& rsel){ m_lLines.push_back(rsel); }
		vector<CSymEdLine>::iterator begin(){ return m_lLines.begin(); }
		vector<CSymEdLine>::iterator end(){ return m_lLines.end(); }
		vector<CSymEdLine>::iterator erase(vector<CSymEdLine>::iterator it){ return m_lLines.erase(it); }
		vector<CSymEdLine>::iterator insert(vector<CSymEdLine>::iterator it, const CSymEdLine& cel )
		{
				
		if (it==&m_lDummy)
			{
			ATLTRACE("<Warning> attempt to insert pointer when index out of range\n");
			return m_lLines.end();
			}

		return m_lLines.insert(it,cel);
		}

	private:
		vector<CSymEdLine> m_lLines;
		CSymEdLine m_lDummy;

	};


	CMultiPaneStatusBarCtrl* m_pStatusBar;
	CComBSTR m_cbStreamName;
	CHoldTokeniser m_hldTokeniser;
	POINT m_point;
	HMENU m_hMenu;
//	vector<CSymEdLine> m_lEdLines;
	CSymHoldLines m_lEdLines;
	bool m_bFormulaLock;
	char m_sStr[SYMEDLINE_STR_LENGTH+20];
	long m_iLeftChar;
	long m_iRightChar;
	long m_iLeftLine;
	long m_iRightLine;
	long m_iNumLines;
	long m_iNumChars;
	long m_iLineLength;
	vector<long> m_vFormatActions;
	long m_iCurrentFormatCount;
	bool m_bDirty;

	inline void setDirty(){ m_bDirty=true; }
	inline void setClean(){ m_bDirty=false; }

#ifdef NDEBUG
	inline void dumpList(){} // so does nothing
#else
	void dumpList();
#endif

public:
	DECLARE_WND_SUPERCLASS(NULL, CRichEditCtrl::GetWndClassName())

	BOOL PreTranslateMessage(MSG* pMsg)
	{
		pMsg;
		return FALSE;
	}

	BEGIN_MSG_MAP(CSymEditView)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_CHAR, OnChar)
		MESSAGE_HANDLER(WM_RBUTTONUP, OnRButtonUp)
		COMMAND_ID_HANDLER(ID_EDIT_COPY, OnEditCopy)
		COMMAND_ID_HANDLER(ID_EDIT_CUT, OnEditCut)
		COMMAND_ID_HANDLER(ID_EDIT_PASTE, OnEditPaste)
		COMMAND_ID_HANDLER(ID_POPUP1_EVENTS_START, OnWriteEgStart)
 		COMMAND_ID_HANDLER(ID_POPUP1_SOLVER_RK3, OnWriteEgRK3)
 		COMMAND_ID_HANDLER(ID_POPUP1_SOLVER_RK3VS, OnWriteEgRK3VS)
 		COMMAND_ID_HANDLER(ID_POPUP1_SOLVER_RK4, OnWriteEgRK4)
 		COMMAND_ID_HANDLER(ID_POPUP1_SOLVER_RK4VS, OnWriteEgRK4VS)
 		COMMAND_ID_HANDLER(ID_POPUP1_SOLVER_RK4VSMT, OnWriteEgRK4VSMT)
 		COMMAND_ID_HANDLER(ID_POPUP1_SOLVER_RK5, OnWriteEgRK5)
 		COMMAND_ID_HANDLER(ID_POPUP1_SOLVER_RK5VS, OnWriteEgRK5VS)
  		COMMAND_ID_HANDLER(ID_POPUP1_EVENTS_STOP, OnWriteEgStop)
 		COMMAND_ID_HANDLER(ID_POPUP1_EVENTS_RECORD, OnWriteEgRecord)
		COMMAND_ID_HANDLER(ID_POPUP1_EVENTS_DUMP, OnWriteEgDump)
		COMMAND_ID_HANDLER(ID_POPUP1_EVENTS_SYNC, OnWriteEgSync)
		COMMAND_ID_HANDLER(ID_POPUP1_EVENTS_PACE, OnWriteEgPace)
		COMMAND_ID_HANDLER(ID_POPUP1_EVENTS_CHANGEVALUE, OnWriteEgChangeVal)
		COMMAND_ID_HANDLER(ID_POPUP1_EVENTS_REALTIME, OnWriteEgRealtime)
		COMMAND_ID_HANDLER(ID_POPUP1_EQUATIONS_ORDINARY, OnWriteEgOrd)
		COMMAND_ID_HANDLER(ID_POPUP1_EQUATIONS_DIFFERENTIAL, OnWriteEgDiff)
		COMMAND_ID_HANDLER(ID_POPUP1_EQUATIONS_SWITCHCASE, OnWriteEgSwitch)
		COMMAND_ID_HANDLER(ID_POPUP1_EQUATIONS_LOOKUP, OnWriteEgLkup)
		COMMAND_ID_HANDLER(ID_POPUP1_MACROS_INSERT, OnWriteEgInsert)
 		COMMAND_ID_HANDLER(ID_POPUP1_MACROS_DEFINE, OnWriteEgDefine)
 		COMMAND_ID_HANDLER(ID_POPUP1_MACROS_TYPE, OnWriteEgType)
 		COMMAND_ID_HANDLER(ID_POPUP1_FUNCTIONS_SIN, OnWriteEgSin)
 		COMMAND_ID_HANDLER(ID_POPUP1_FUNCTIONS_COS, OnWriteEgCos)
		COMMAND_ID_HANDLER(ID_POPUP1_FUNCTIONS_TAN, OnWriteEgTan)
  		COMMAND_ID_HANDLER(ID_POPUP1_FUNCTIONS_ASIN, OnWriteEgASin)
 		COMMAND_ID_HANDLER(ID_POPUP1_FUNCTIONS_ACOS, OnWriteEgACos)
		COMMAND_ID_HANDLER(ID_POPUP1_FUNCTIONS_ATAN, OnWriteEgATan)
 		COMMAND_ID_HANDLER(ID_POPUP1_FUNCTIONS_LOG, OnWriteEgLog)
 		COMMAND_ID_HANDLER(ID_POPUP1_FUNCTIONS_LN, OnWriteEgLn)
		COMMAND_ID_HANDLER(ID_POPUP1_FUNCTIONS_ABS, OnWriteEgAbs)
		COMMAND_ID_HANDLER(ID_POPUP1_FUNCTIONS_EXP, OnWriteEgExp)
		COMMAND_ID_HANDLER(ID_POPUP1_FUNCTIONS_INT, OnWriteEgInt)
		COMMAND_ID_HANDLER(ID_POPUP1_FUNCTIONS_INTUP, OnWriteEgIntup)
		COMMAND_ID_HANDLER(ID_POPUP1_ARRAYS_PLAINARRAY, OnWriteEgArray)
		COMMAND_ID_HANDLER(ID_POPUP1_ARRAYS_SHEET, OnWriteEgArraySheet)
		COMMAND_ID_HANDLER(ID_POPUP1_ARRAYS_ARRAYFUNCTIONS_COUNT, OnWriteEgCount)
		COMMAND_ID_HANDLER(ID_POPUP1_ARRAYS_ARRAYFUNCTIONS_SUM, OnWriteEgSum)
		COMMAND_ID_HANDLER(ID_POPUP1_ARRAYS_ARRAYFUNCTIONS_AVRG, OnWriteEgAvrg)
		COMMAND_ID_HANDLER(ID_POPUP1_SOLVER_SEQFROMTO, OnWriteEgSeqToFrom)
		COMMAND_ID_HANDLER(ID_POPUP1_SOLVER_SEQUENCESERIES, OnWriteEgSeqSeries)
		COMMAND_ID_HANDLER(ID_POPUP1_SOLVERS_ONCE, OnWriteEgOnce)
		COMMAND_ID_HANDLER(ID_POPUP1_EVENTS_ITFROMTO, OnWriteEgIterToFrom)
		COMMAND_ID_HANDLER(ID_POPUP1_EVENTS_ITERATIONSERIES, OnWriteEgIterSeries)
		COMMAND_ID_HANDLER(ID_POPUP1_INDEX_DEFINE, OnWriteEgIndexDefine)
		COMMAND_ID_HANDLER(ID_POPUP1_INDEX_EXPAND, OnWriteEgIndexExpand)
		COMMAND_ID_HANDLER(ID_POPUP1_EVENTS_DUMPEQUATIONS,OnWriteEgDumpEquations)	
		MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
		MESSAGE_HANDLER(WM_SELECTAPOINT, OnSelectAPoint)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUP)
		MESSAGE_HANDLER(WM_KEYUP, OnKeyUp)
     END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual BOOL Undo();

	void PreCreate(BSTR* pbstrKey, IARDataStore *pIStore, CMultiPaneStatusBarCtrl* pStatusBar)
	{

		try
		{
			m_pStatusBar = pStatusBar;
			m_cbStreamName = *pbstrKey;
			if (strm.addStore(pIStore))
			{
			 strm.addStream(pbstrKey);

			}
		}
		catch(...)
		{
		ATLTRACE(_T("Error caught in CMainFrame::PreCreate\n"));

		}

	}

	void SaveStream()
	{


	try
	{
	if ((strm.addWriteStream(&m_cbStreamName))&&(strm.m_pIWriteStream))
			{
			enumARStream ess;
			char* sBuff;
			long iLineBuff = 255;
			long iLineLen;
			long iEnd;
			long iCount =0;
			long iLines = GetLineCount();
			bool bNotWildFailure = (iLines>=m_lEdLines.size()); // to cover production cases of a failure here - so less messy
			VARIANT_BOOL vbFlag;
			sBuff = new char[iLineBuff+2];
			HRESULT hr = strm.m_pIWriteStream->get_StreamState(&ess);
//			ATLASSERT(ess==streamLoaded);
			ATLTRACE("streamLoaded = %d\n",streamLoaded);
			ATLTRACE("ess = %d\n",ess);
			if (SUCCEEDED(hr)&&(ess==streamLoaded))
				{
					char cEOL = 13;
					ATLTRACE(_T("GetLimitText = %d\n"),GetLimitText());
					ATLASSERT(iLines>=m_lEdLines.size()); // or else nasty thing will happen
					long iCharLineStart = 0;
					do
					{
						CComBSTR cbWrite(_T(""));
						iCharLineStart = LineIndex(iCount);
						iLineLen = LineLength(iCharLineStart);
						ATLTRACE(_T("iCount %d LineLength = %d, "),iCount,iLineLen);
						ATLTRACE(_T(" iCharLineStart %d LineLength = %d, "),iCharLineStart,LineLength(iCharLineStart));
					//	iCharLineStart = iLineLen;
						if (iLineLen>iLineBuff)
							{
							delete []sBuff;
							sBuff = new char[iLineLen+12];
							iLineBuff = iLineLen+10;// to avoid repeating too often
							}
						iEnd = GetLine(iCount,sBuff,iLineBuff);
						ATLASSERT(iEnd<=iLineBuff);
						if ((iEnd>0)&&(sBuff[iEnd-1]==cEOL))	
								iEnd--;
						char cTemp = NULL;
						sBuff[iEnd] = cTemp;//'\n';
//						sBuff[iEnd+1]= NULL;

						// going to add Formula info before the line is written ( same for ofther data for line )
						if ((bNotWildFailure)&&(m_lEdLines[iCount].hasFunction()))
							{
							cbWrite = m_lEdLines[iCount].getFormula();
							hr = strm.m_pIWriteStream->prepareLineWriteExtra(esioFormula,&cbWrite,&vbFlag);
							ATLASSERT(SUCCEEDED(hr));
							if (vbFlag!=-1)
								{
								ATLTRACE("<Warning> Unable to send formula line %d : %s",iCount,m_lEdLines[iCount].getFormula());
								}
							}

						cbWrite = sBuff;
						ATLTRACE(_T("strlen(sBuff) = %d "),strlen(sBuff));
						ATLTRACE(_T("cbWrite.Length() = %d "),cbWrite.Length());
						ATLTRACE(_T("["));
						ATLTRACE(sBuff);
						ATLTRACE("]\n");
						ATLASSERT(strlen(sBuff)==cbWrite.Length());
						if (SUCCEEDED(hr)) // otherwise we need to exit anyway
							hr = strm.m_pIWriteStream->writeLine(&cbWrite,&ess);
						iCount++;

					}
					while((iCount<iLines)&&(SUCCEEDED(hr))&&(ess==streamWriteLine));
					ATLASSERT(SUCCEEDED(hr)); //call attention in debug to problems here 
				} // endif
			delete []sBuff;
			setClean();
			}
	}
	catch(...)
		{
		ATLTRACE(_T("<Error> Unhandled error thrown in CSymEditView::SaveStream\n"));
		ATLASSERT(false);
		
		}

	}

	void Paste() // to prevent pasting in OLE objects and formated text etc
	{

		PasteSpecial(CF_TEXT);

	}

	void PasteSpecial(UINT uClipFormat, DWORD dwAspect = 0, HMETAFILE hMF = 0);

	int AppendText(LPCTSTR lpstrText, BOOL bCanUndo = FALSE);
    void ReplaceSel(LPCTSTR lpszNewText, BOOL bCanUndo = FALSE );

	void WriteForThisString(unsigned int uiID );
	bool hasChanges() const { return m_bDirty; }

private:
	bool hasFormula( long iSel );
	bool IsSelectionFormulaBlocked(long iP = -1);
	void ActionForNewSelectPoint();
	void StoreSelectPoint();
	bool FormatToCurrentPoint(bool bKeepPoint=false);
	void StorePoint();
	long m_iStoreLine;
	long m_iStoreX;

	void push_Edit(){
		m_vFormatActions.push_back(m_iCurrentFormatCount);
		m_iCurrentFormatCount = 0;
	}

	long pop_Edit()
	{
		long iResult;
		
		if (m_vFormatActions.size()<1) // safety
			return 0;
		
		long& rResult = m_vFormatActions.back();
		iResult = rResult;
		m_vFormatActions.pop_back();
		return iResult;

	}


	POPUP_STRING_WRITE(OnWriteEgStop,ID_POPUP1_EVENTS_STOP)
	POPUP_STRING_WRITE(OnWriteEgRecord,ID_POPUP1_EVENTS_RECORD)
	POPUP_STRING_WRITE(OnWriteEgDump,ID_POPUP1_EVENTS_DUMP)
	POPUP_STRING_WRITE(OnWriteEgStart,ID_POPUP1_EVENTS_START)
	POPUP_STRING_WRITE(OnWriteEgSync, ID_POPUP1_EVENTS_SYNC)
	POPUP_STRING_WRITE(OnWriteEgPace, ID_POPUP1_EVENTS_PACE)
	POPUP_STRING_WRITE(OnWriteEgChangeVal, ID_POPUP1_EVENTS_CHANGEVALUE)
	POPUP_STRING_WRITE(OnWriteEgRealtime, ID_POPUP1_EVENTS_REALTIME)


	POPUP_STRING_WRITE(OnWriteEgRK3,ID_POPUP1_SOLVER_RK3)
	POPUP_STRING_WRITE(OnWriteEgRK3VS,ID_POPUP1_SOLVER_RK3VS)
	POPUP_STRING_WRITE(OnWriteEgRK4,ID_POPUP1_SOLVER_RK4)
	POPUP_STRING_WRITE(OnWriteEgRK4VS,ID_POPUP1_SOLVER_RK4VS)
	POPUP_STRING_WRITE(OnWriteEgRK4VSMT,ID_POPUP1_SOLVER_RK4VSMT)
	POPUP_STRING_WRITE(OnWriteEgRK5,ID_POPUP1_SOLVER_RK5)
	POPUP_STRING_WRITE(OnWriteEgRK5VS,ID_POPUP1_SOLVER_RK5VS)

	POPUP_STRING_WRITE(OnWriteEgOrd,ID_POPUP1_EQUATIONS_ORDINARY)
	POPUP_STRING_WRITE(OnWriteEgDiff,ID_POPUP1_EQUATIONS_DIFFERENTIAL)
	POPUP_STRING_WRITE(OnWriteEgSwitch,ID_POPUP1_EQUATIONS_SWITCHCASE)
	POPUP_STRING_WRITE(OnWriteEgLkup,ID_POPUP1_EQUATIONS_LOOKUP)

	POPUP_STRING_WRITE(OnWriteEgInsert,ID_POPUP1_MACROS_INSERT)
	POPUP_STRING_WRITE(OnWriteEgDefine,ID_POPUP1_MACROS_DEFINE)
	POPUP_STRING_WRITE(OnWriteEgType,ID_POPUP1_MACROS_TYPE)

	POPUP_STRING_WRITE(OnWriteEgSin,ID_POPUP1_FUNCTIONS_SIN)
	POPUP_STRING_WRITE(OnWriteEgCos,ID_POPUP1_FUNCTIONS_COS)
	POPUP_STRING_WRITE(OnWriteEgTan,ID_POPUP1_FUNCTIONS_TAN)
	POPUP_STRING_WRITE(OnWriteEgASin,ID_POPUP1_FUNCTIONS_ASIN)
	POPUP_STRING_WRITE(OnWriteEgACos,ID_POPUP1_FUNCTIONS_ACOS)
	POPUP_STRING_WRITE(OnWriteEgATan,ID_POPUP1_FUNCTIONS_ATAN)
	POPUP_STRING_WRITE(OnWriteEgLog,ID_POPUP1_FUNCTIONS_LOG)
	POPUP_STRING_WRITE(OnWriteEgLn,ID_POPUP1_FUNCTIONS_LN)
	POPUP_STRING_WRITE(OnWriteEgAbs,ID_POPUP1_FUNCTIONS_ABS)
	POPUP_STRING_WRITE(OnWriteEgExp,ID_POPUP1_FUNCTIONS_EXP)
	POPUP_STRING_WRITE(OnWriteEgArray,ID_POPUP1_ARRAYS_PLAINARRAY)
	POPUP_STRING_WRITE(OnWriteEgArraySheet,ID_POPUP1_ARRAYS_SHEET)
	POPUP_STRING_WRITE(OnWriteEgCount,ID_POPUP1_ARRAYS_ARRAYFUNCTIONS_COUNT)
	POPUP_STRING_WRITE(OnWriteEgSum,ID_POPUP1_ARRAYS_ARRAYFUNCTIONS_SUM)
	POPUP_STRING_WRITE(OnWriteEgAvrg,ID_POPUP1_ARRAYS_ARRAYFUNCTIONS_AVRG)
	POPUP_STRING_WRITE(OnWriteEgSeqToFrom,ID_POPUP1_SOLVER_SEQFROMTO)
	POPUP_STRING_WRITE(OnWriteEgSeqSeries,ID_POPUP1_SOLVER_SEQUENCESERIES)
	POPUP_STRING_WRITE(OnWriteEgOnce,ID_POPUP1_SOLVERS_ONCE)
	POPUP_STRING_WRITE(OnWriteEgIterToFrom,ID_POPUP1_EVENTS_ITFROMTO)
	POPUP_STRING_WRITE(OnWriteEgIterSeries,ID_POPUP1_EVENTS_ITERATIONSERIES)
	POPUP_STRING_WRITE(OnWriteEgIndexDefine,ID_POPUP1_INDEX_DEFINE)
	POPUP_STRING_WRITE(OnWriteEgIndexExpand,ID_POPUP1_INDEX_EXPAND)
	POPUP_STRING_WRITE(OnWriteEgDumpEquations,ID_POPUP1_EVENTS_DUMPEQUATIONS)	
	POPUP_STRING_WRITE(OnWriteEgInt,ID_POPUP1_FUNCTIONS_INT)
	POPUP_STRING_WRITE(OnWriteEgIntup,ID_POPUP1_FUNCTIONS_INTUP)
	LRESULT OnEditCopy(UINT /*uMsg*/, WPARAM /*wParam*/, HWND /*lParam*/, BOOL& /*bHandled*/)
	{
	ATLTRACE("OnEditCopy\n");
		Copy();
	return 0;
	}

	LRESULT OnEditCut(UINT /*uMsg*/, WPARAM /*wParam*/, HWND /*lParam*/, BOOL& /*bHandled*/)
	{
	ATLTRACE("OnEditCut\n");
		Cut();
	return 0;
	}

	LRESULT OnEditPaste(UINT /*uMsg*/, WPARAM /*wParam*/, HWND /*lParam*/, BOOL& /*bHandled*/)
	{
	ATLTRACE("OnEditPaste\n");
		setDirty();
		Paste();
	return 0;
	}

	LRESULT OnEditUndo(UINT /*uMsg*/, WPARAM /*wParam*/, HWND /*lParam*/, BOOL& /*bHandled*/)
	{
	ATLTRACE("OnEditUndo\n");
		Undo();
	return 0;
	}


	bool FormatText(long iStart, long iEnd);

	LRESULT OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnRButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{

		m_point.x = LOWORD (lParam);
		m_point.y = HIWORD (lParam);
		ClientToScreen(&m_point);
		TrackPopupMenu(m_hMenu,TPM_RIGHTBUTTON, m_point.x, m_point.y, 0, this->m_hWnd, NULL );

		return 0;
	}


///////////////////////////////////////////////////////////
// Function name	: OnSelectAPoint
// Description	    : 
// Return type		: LRESULT 
// Argument         : UINT uMsg
// Argument         : WPARAM wParam
// Argument         : LPARAM lParam
// Argument         : BOOL& bHandled
///////////////////////////////////////////////////////////
	LRESULT OnSelectAPoint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bool bStuck = false;
		bool bUp=true;
		bool bHasUsedLineRef=false;
		long iLine,iChar,iEndChar,iTemp,iTry;

		bHandled = true;
		iLine = wParam-1;

		ATLTRACE("WM_SELECTAPOINT Message recieved value %d\n",iLine);
		// need to translate line number to editor line number
		if ((iLine<0)||(iLine>=m_lEdLines.size())) // must make sure in range		
				{
				ATLTRACE("Line signalled (%d) in OnSelectAPoint is outside m_lEdLines Size (%d) \n",iLine,m_lEdLines.size());
				return 0;
				}
		
		iTemp = m_lEdLines[iLine].getOldLine()-1;
		iTry = iLine;

		while((!bStuck)&&(iTemp!=iLine))
		{
		if (iTemp==NOT_FOUND) // then keep on going in the same direction
			{
			if (bUp)
				iTry++;
				else
				iTry--;
			}
			else
			{
			if (iTemp>iLine)
				{
				iTry--;
				if ((bHasUsedLineRef)&&(bUp)) // then this is reverse and means we're stuck
					bStuck = true; // will exit
				bUp = false;
				}
				else
				{
				iTry++;
				if ((bHasUsedLineRef)&&(!bUp)) // then this is reverse and means we're stuck
					bStuck = true; // will exit
				bUp = true;
				}
			bHasUsedLineRef=true; // to show a line ref has been used
			}

		if ((iTry<0)||(iTry>=m_lEdLines.size())) // must make sure in range	
			{
			if ((iTry<0)&&(!bHasUsedLineRef)) // looking for case where part of lines haven't been searched as all NOT_DEFINED returned
					{                         // its assume that if a line ref has been used then the search has been in the rigth direction.
					iTry=0;
					bUp=true; // go the other way
					bHasUsedLineRef=true; // so this isn't done at the other end and we get a loop
					}
					else
					if ((iTry>=m_lEdLines.size())&&(!bHasUsedLineRef))
						{
						iTry = m_lEdLines.size()-1;
						bUp=false; // go the other way
						bHasUsedLineRef=true;
						}
						else
						bStuck = true; // thats it then - its possible the original line has been deleted
			}
			else
			iTemp = m_lEdLines[iTry].getOldLine()-1;


		}


		if (bStuck)
				{
				ATLTRACE("Unable to locate line (%d) in OnSelectAPoint note m_lEdLines Size (%d) \n",iTry,m_lEdLines.size());
				return 0;
				}

		iLine = iTry;
		iChar = LineIndex(iLine);
		iEndChar = LineIndex(iLine+1);


		if (iEndChar<0)
				iEndChar = GetTextLength();
				else
				iEndChar--;
		
		
		SetSel(iChar,iEndChar);
		
		SetLineNumberInStatus();


		return 0;
	}


///////////////////////////////////////////////////////////
// Function name	: OnKeyDown
// Description	    : 
// Return type		: LRESULT 
// Argument         : UINT uMsg
// Argument         : WPARAM wParam
// Argument         : LPARAM lParam
// Argument         : BOOL& bHandled
///////////////////////////////////////////////////////////
	LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT bResult;
		bool bAction;
		bool bNoCharAlso=true;

		// if not cursor keys and formual lock not on
		if (((wParam>40)||(wParam<37))&&IsSelectionFormulaBlocked())
					{
					LoadString(_Module.m_hInst,IDS_EDITOR_CANTOVRFORM,m_sStr,SYMEDLINE_STR_LENGTH); 
					MessageBox(m_sStr);
					return false;
					}


		switch(wParam)
		{
			case 8:		// BS
				// if the next character will reduce the line count and that line is protected then refuse
				{
					long iNext,iX;
					GetSel(iNext,iX);
					iNext--;
					if ((iNext>0)&&IsSelectionFormulaBlocked(iNext))
						{
						LoadString(_Module.m_hInst,IDS_EDITOR_CANTOVRFORM,m_sStr,SYMEDLINE_STR_LENGTH); 
						MessageBox(m_sStr);
						return false;
						}

				}
				bNoCharAlso = false;
				bAction = true;
				break;
			case 13:	// CR
				bNoCharAlso = false;
				bAction = true;
				break;
			case 9:		// Tab 
			case 46:	// Del
				bAction = true;
				break;
			//case 37:	// Left arrow
			//case 38:	// Up arrow
			//case 39:    // Right arrow
			//case 40:	// Down arrow
			default:
				bAction = false;
		}

		if (bAction)
			{
			StorePoint();
			StoreSelectPoint();
			}
		ATLTRACE("\nOnKeyDown WPARAM %d, LPARAM %d\n",wParam,lParam);
		setDirty();

		bResult = DefWindowProc(uMsg,wParam,lParam);

		if (bAction)
			{
			ActionForNewSelectPoint();
			FormatToCurrentPoint(true);
			//m_iCurrentFormatCount++;
			if (bNoCharAlso)
					push_Edit();
			}
		return bResult;
	}

	void SetLineNumberInStatus()
	{

	CString sLine;
	long iXEnd, iXStart;
	long iLine;

	GetSel(iXStart,iXEnd);

	iLine = LineFromChar(iXStart) + 1; // as the user counts lines from 1

	sLine.Format(" Line %i",iLine);

	if (m_pStatusBar) // as it may not have been passed
		m_pStatusBar->SetPaneText(IDR_STATUS_LINE, sLine);

	}

	LRESULT OnLButtonUP(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		SetLineNumberInStatus();
		
		return DefWindowProc(uMsg,wParam,lParam);
	}

	LRESULT OnKeyUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		SetLineNumberInStatus();
		
		return DefWindowProc(uMsg,wParam,lParam);
	}
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYMEDITVIEW_H__79FC7297_A6AE_4CC4_83C1_DD95A682269E__INCLUDED_)
