//
#include "stdafx.h"

#include <atlctrls.h>
#include "SymEditor.h"
#include "resource.h"

#define DEBUGEDITLINE
/*
///////////////////////////////////////////////////////////
// Function name	: CSymEditView::CSymHoldTokeniser::CSymHoldTokeniser
// Description	    : Constructor that hides the construction of Tokeniser
//                    for use inside the CSymEditor
// Return type		: 
///////////////////////////////////////////////////////////
CSymEditView::CSymHoldTokeniser::CSymHoldTokeniser():m_pTokeniser(NULL)
{
	m_pTokeniser = newtrack CTokeniser(g_sDelim,g_iDelim,m_setRecognisedFileNames,m_mapUDK);
	ATLASSERT(m_pTokeniser);
}


///////////////////////////////////////////////////////////
// Function name	: CSymEditView::CSymHoldTokeniser::~CSymHoldTokeniser
// Description	    : 
// Return type		: 
///////////////////////////////////////////////////////////
CSymEditView::CSymHoldTokeniser::~CSymHoldTokeniser()
{
	if (m_pTokeniser)
		delete m_pTokeniser;

}

list<CToken>& CSymEditView::CSymHoldTokeniser::getTokenisedList(long iLine, const char* sLine, const char* sStreamName )
{
	
	if (!m_pTokeniser) // then things are desperately wrong
		{
		ATLTRACE("<Error> CSymEditView::CSymHoldTokeniser::m_pTokeniser is NULL.\n");
		return m_lToks; // have to do something
		}
	m_lToks.clear();
	m_pTokeniser->tokeniseLine(iLine,sLine,m_lToks,sStreamName,true);

	return m_lToks;
}
*/

#define LIMITREADINGTEXT 500
///////////////////////////////////////////////////////////
// Function name	: CSymEditView::FormatText
// Description	    : This function formats text between the twp
//                    defined points
// Return type		: bool 
// Argument         : long iStart
// Argument         : long iEnd
///////////////////////////////////////////////////////////
bool CSymEditView::FormatText(long iStart, long iEnd)
{


	long iT;
	long iLen;
	long iFrom,iTo;
	bool bGreyOut = false;
	char c[] = " ";
	char str[LIMITREADINGTEXT];
	CHARFORMAT2 cf;
	COLORREF colorDef;
	list<CToken>::const_iterator iter;
	list<CToken>::const_iterator iterNext;


	// first check iEnd isn't over the length of the text
	iT = this->GetTextLength();

	if (iEnd>iT)
		return false;

	GetDefaultCharFormat(cf);
	colorDef = cf.crTextColor;

	if ((iEnd-iStart)>=LIMITREADINGTEXT)
		return false;

	SetSel(iStart,iEnd);
	iLen = GetSelText(str);
	list<CToken>& 	rlToks = m_hldTokeniser.getTokenisedList(iLen,str,"Woof");
	

	if (rlToks.size()>0)
		{
	
		iFrom = iStart;
		// Need to step through the list making the appropriate charater coding
		iterNext = rlToks.begin();
		for(iter=rlToks.begin();iter!=rlToks.end();iter++)
			{
			ATLTRACE(iter->getString().c_str());
			ATLTRACE(" [%d] ",iter->getX());
			if (++iterNext!=rlToks.end())
					iTo = iterNext->getX() + iStart;
				else
					iTo=iEnd;

			SetSel(iFrom,iTo);
				
			cf.crTextColor = colorDef; // for the caes with no edit value	

			if (bGreyOut)
				{
				cf.crTextColor = RGB(150,150,150);
				}
				else
				{
					switch (iter->getType())
					{
					case ctDefinedNotAssigned:
						ATLTRACE(" ctDefinedNotAssigned\n");
							break;
					case ctComment:
						ATLTRACE(" ctComment\n");
							break;
					case ctDerivative:
						ATLTRACE(" ctDerivative\n");
							break;
					case ctVariable:
						ATLTRACE(" ctVariable\n");
							break;
					case ctDelim:
						strcpy(str,"//");
						if (strcmp("//",(iter->getString().c_str()))==0)
								{
								bGreyOut = true;
								cf.crTextColor = RGB(150,150,150);
								}	
								else
								cf.crTextColor = RGB(0,175,10);
						ATLTRACE(" ctDelim\n");
							break;
					case ctNotDefined:
						ATLTRACE(" ctNotDefined\n");
							break;
					case ctNumber:
						cf.crTextColor = RGB(10,175,200);	
						ATLTRACE(" ctNumber\n");
							break;
					case ctName:
						ATLTRACE(" ctName\n");
							break;
					case ctDepVariable:
						ATLTRACE(" ctDepVariable\n");
							break;
					case ctIndVariable:
						ATLTRACE(" ctIndVariable\n");
							break;
					case ctSubsVariable:
						ATLTRACE(" ctSubsVariable\n");
							break;
					case ctEventKeyWord:
						cf.crTextColor = RGB(200,100,50);	
						ATLTRACE(" ctEventKeyWord\n");
							break;
					case ctSolverKeyWord:
						cf.crTextColor = RGB(0,128,192);	
						ATLTRACE(" ctSolverKeyWord\n");
							break;
					case ctEquationKeyWord:
						cf.crTextColor = RGB(251,0,0);	
						ATLTRACE(" ctEquationKeyWord\n");
							break;
					case ctArrayKeyWord:
						cf.crTextColor = RGB(156,132,198);	
						ATLTRACE(" ctArrayKeyWord\n");
							break;
					case ctMacroKeyWord:
						cf.crTextColor = RGB(219,36,215);	
						ATLTRACE(" ctMacroKeyWord\n");
							break;
					case ctTypeModifier:
						cf.crTextColor = RGB(255,0,128);	
						ATLTRACE(" ctTypeModifier\n");
							break;
					default :
						ATLTRACE(" default\n");
							break;
					}
				}
		if (hasFormula(iFrom))
			cf.crBackColor = RGB(255,255,0); // yellow
			else
			cf.crBackColor = RGB(255,255,255);

		m_iCurrentFormatCount++; //a further format action taken
		if (!SetSelectionCharFormat(cf))
					{
						ATLTRACE(_T("Update failed for char format\n"));
						m_iCurrentFormatCount--;  //may as well keep this in step
					}
		iFrom = iTo; // for the next loop

		} // end for(iter=rlToks.begin();iter!=rlToks.end();iter++)

	} // end (rlToks.size>0)

/*	
	strcpy(str," ");



//	cf.cbSize = sizeof(cf);
//	cf.dwMask = CFM_COLOR;
//	cf.crTextColor = RGB(200,130,0);
//	cf.dwEffects = CFE_STRIKEOUT;
	
	for(iT=iStart;iT<=iEnd;iT++)
		{
		this->SetSel(iT,iT+1);
		iLen = this->GetSelText(str);
		ATLTRACE("[");
		ATLTRACE(str);
		ATLTRACE("] ");

		switch (str[0])
			{
			case '=':
			case '*':
			case '/':
			case '+':
			case '-':
				cf.crTextColor = RGB(20,70,200);	
				if (!SetSelectionCharFormat(cf))
						{
							ATLTRACE(_T("Update failed for char format\n"));
						}
				break;
			case '\\':
				cf.crTextColor = RGB(75,75,75);	
				if (!SetSelectionCharFormat(cf))
						{
							ATLTRACE(_T("Update failed for char format\n"));
						}
				break;
			default:
				cf.crTextColor = colorDef;	
				if (!SetSelectionCharFormat(cf))
						{
							ATLTRACE(_T("Update failed for char format\n"));
						}
				break;


			}




		}

*/

	return true;
}


///////////////////////////////////////////////////////////
// Function name	: CSymEditView::OnChar
// Description	    : 
// Return type		: LRESULT 
// Argument         : UINT uMsg
// Argument         : WPARAM wParam
// Argument         : LPARAM lParam
// Argument         : BOOL& bHandled
///////////////////////////////////////////////////////////
LRESULT CSymEditView::OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{

	long iSelStart,iSelEnd,iX;
	LRESULT bResult;
	long iLine=-1;
	long iLF,iLR;

	GetSel(iX,iSelStart);

			
	if (IsSelectionFormulaBlocked())
					{
		/* This warnign will be issued by On Key down */
					//LoadString(_Module.m_hInst,IDS_EDITOR_CANTOVRFORM,m_sStr,SYMEDLINE_STR_LENGTH); 
					//MessageBox(m_sStr);
					return false;
					}



	StoreSelectPoint();

	dumpList();
	setDirty();

	bResult = DefWindowProc(uMsg,wParam,lParam); // character added

	GetSel(iX,iSelEnd);

	iLF = LineFromChar(iX); // as lines are counted from 1 not 0
	iLR = LineFromChar(iSelEnd); // as above
	iLine= LineFromChar(iSelEnd);
	// has another line been added ?

	ATLASSERT(iLR<m_lEdLines.size()); // or there will be trouble
	
	ActionForNewSelectPoint();


	// try a different way of getting this information
	iLine = LineFromChar(iSelEnd);
	iSelStart = LineIndex(iLine);
	iX = LineIndex(iLine+1);
	if (iX==-1)
			iX = GetTextLength(); // as this was the last line
			else
			iX--;

	LockWindowUpdate(true);

	FormatText(iSelStart,iX);
	push_Edit();
	
	SetSel(iSelEnd,iSelEnd);
	LockWindowUpdate(false);

	dumpList();
	
	return bResult;
}


///////////////////////////////////////////////////////////
// Function name	: CSymEditView::AppendText
// Description	    : Over loaded so as to enforce formating
// Return type		: int 
// Argument         : LPCTSTR lpstrText
// Argument         : BOOL bCanUndo
///////////////////////////////////////////////////////////
int CSymEditView::AppendText(LPCTSTR lpstrText, BOOL bCanUndo )
{
	long iBefore,iAfter,iX;
	int iResult;

	GetSel(iBefore,iX);

	LockWindowUpdate(true);

	iResult = CRichEditCtrl::AppendText(lpstrText,bCanUndo);

	GetSel(iX,iAfter);


	FormatText(iBefore,iAfter);
	
	SetSel(iAfter,iAfter);

	LockWindowUpdate(false);


	return iResult;
}


///////////////////////////////////////////////////////////
// Function name	: CSymEditView::ReplaceSel
// Description	    : 
// Return type		: void 
// Argument         : LPCTSTR lpszNewText
// Argument         : BOOL bCanUndo
///////////////////////////////////////////////////////////
void CSymEditView::ReplaceSel(LPCTSTR lpszNewText, BOOL bCanUndo  )
{
	long iBefore,iAfter,iX;

	GetSel(iBefore,iX);
	iX = LineFromChar(iBefore);
	iBefore = LineIndex(iX);

	LockWindowUpdate(true);

	StoreSelectPoint();
	StorePoint();

	CRichEditCtrl::ReplaceSel(lpszNewText,bCanUndo);

	GetSel(iX,iAfter);

	FormatToCurrentPoint();
	
	SetSel(iAfter,iAfter);

	ActionForNewSelectPoint(); // just added

	LockWindowUpdate(false);


	return;

}

///////////////////////////////////////////////////////////
// Function name	: CSymEditView::OnCreate
// Description	    : 
// Return type		: LRESULT 
// Argument         : UINT uMsg
// Argument         : WPARAM wParam
// Argument         : LPARAM lParam
// Argument         : BOOL& bHandled
///////////////////////////////////////////////////////////
LRESULT CSymEditView::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{

		 LRESULT bResult = DefWindowProc(uMsg,wParam,lParam); // need to do this first for line numbers
	
		 CHARFORMAT2 cf;

 	     m_hMenu = LoadMenu(_Module.GetResourceInstance(),MAKEINTRESOURCE(IDR_POPUP1)); //IDR_POPUP1
    	 m_hMenu = GetSubMenu(m_hMenu,0);
		 
		 m_bFormulaLock = true; //true;

		 GetDefaultCharFormat(cf);
		 //cf.dwMask = cf.dwMask | CFM_COLOR;
		 //cf.crTextColor = 7;
		// Modify the default character format so that all new
		// text is striked out and not bold.
		cf.dwMask = /*CFM_STRIKEOUT|CFM_BOLD|*/CFM_COLOR|CFM_BACKCOLOR;
		cf.crTextColor = RGB(72,72,72);
		cf.crBackColor = RGB(255,255,255);

		if (cf.dwEffects & CFE_AUTOCOLOR )
				cf.dwEffects ^= CFE_AUTOCOLOR;

		if (cf.dwEffects & CFE_AUTOBACKCOLOR )
					cf.dwEffects ^= CFE_AUTOBACKCOLOR;



		 if (!SetDefaultCharFormat(cf))
			 {
				ATLTRACE(_T("Update failed for char format\n"));
			 }


		if ((strm.isStoreReady())&&(strm.m_pIStream))
				{
				 enumARStream ess;

		if (m_pStatusBar)
				 {
				 USES_CONVERSION;
				 m_pStatusBar->SetPaneText(IDR_STATUS_STREAM, OLE2T(m_cbStreamName));
				 }

				 HRESULT hr = strm.m_pIStream->gotoFirstLine(&ess);

				 if ((SUCCEEDED(hr))&&(ess==streamLoaded))
						{
							bool bFirst = true;
							long iLine = 1;
							CSymEdLine sel;
							do
							{
								USES_CONVERSION;
								BSTR bstr=NULL;
								BSTR bstrFormula=NULL;
								BSTR bstrNotes=NULL;
								BSTR bstrOldRev=NULL;
								hr = strm.m_pIStream->readLine(&bstr);
								if (SUCCEEDED(hr))
									{
									hr = strm.m_pIStream->get_StreamState(&ess);

									if (SUCCEEDED(hr))
										{

										// Need to think carefully if how handle BSTR across COM interface
												
										if (bFirst) // so not adding a line by mistake at the end
													bFirst=false;
													else
													AppendText(_T("\n"));


										hr = strm.m_pIStream->lastLineExtra(esioFormula,&bstrFormula);
										if (SUCCEEDED(hr))
											{
											hr = strm.m_pIStream->lastLineExtra(esioNotes,&bstrNotes);
											if (SUCCEEDED(hr))
												{
												hr = strm.m_pIStream->lastLineExtra(esioLastRev,&bstrOldRev);
												if (SUCCEEDED(hr))
														{
														sel.setBothLine(iLine);
														sel.setFormula(OLE2CT(bstrFormula));
														sel.setNotes(OLE2CT(bstrNotes));
														sel.setOldRev(OLE2CT(bstrOldRev));
														m_lEdLines.push_back(sel);
														SysFreeString(bstrOldRev);
														}
												SysFreeString(bstrNotes);
												}
											SysFreeString(bstrFormula);
											iLine++;
											}

										AppendText(OLE2CT(bstr)); // needs to be after 	m_lEdLines.push_back(sel)

										SysFreeString(bstr);


										}
								}
							}
							while((SUCCEEDED(hr))&&(ess==streamReadline));


						}


				}
		
//		AppendText("<Woof>");
		SetSel(0,0); // hopefully fix scroll bar bug

		dumpList();
		m_iCurrentFormatCount = 0; // needs to happen at the end
		setClean();

		SetLineNumberInStatus();

//		long iLines = this->GetLineCount(); // used to debug problem with line numbers before DefWindowProc called
		
		return bResult;
}

#ifndef NDEBUG

///////////////////////////////////////////////////////////
// Function name	: CSymEditView::dumpList
// Description	    : Debug only call to print out list
// Return type		: void 
///////////////////////////////////////////////////////////
void CSymEditView::dumpList()
{
#ifdef DEBUGEDITLINE
		// check the list of lines
		ofstream os("c:\\temp\\checklist.txt");
		ostream_iterator<CSymEdLine> out(os,"\n"); // see p53 STL book
		copy(m_lEdLines.begin(),m_lEdLines.end(),out);
		os << "end."<<endl;
		os.close();

#endif
}
#endif


void CSymEditView::WriteForThisString(unsigned int uiID )
{

		LoadString(_Module.m_hInst,uiID,m_sStr,SYMEDLINE_STR_LENGTH); 
		ReplaceSel(m_sStr,true);
		setDirty();
}

///////////////////////////////////////////////////////////
// Function name	: CSymEditView::StorePoint
// Description	    : Save the first point currently selected
// Return type		: void 
///////////////////////////////////////////////////////////
void CSymEditView::StorePoint()
{
	long iTemp;
	GetSel(m_iStoreX,iTemp);
	m_iStoreLine = LineFromChar(m_iStoreX);
}


///////////////////////////////////////////////////////////
// Function name	: CSymEditView::FormatToCurrentPoint
// Description	    : Format from the point selected with StorePoint untill 
//                    the end of the current selection;
// Return type		: bool 
// Argument         : bool bKeepPoint /*=false*/ - don't change select point at end
///////////////////////////////////////////////////////////
bool CSymEditView::FormatToCurrentPoint(bool bKeepPoint /*=false*/)
{
	long iTemp, iXEnd, iXStart, iTempEnd;
	long iStartX, iLineEnd;
	bool bResult = true;

	GetSel(iXStart,iXEnd);

	if (m_iStoreX>iXEnd)
			return false;
	
	iLineEnd = LineFromChar(iXEnd);

	if ((iLineEnd<0)||(m_iStoreLine<0))
			return false;


	for (iTemp=m_iStoreLine;iTemp<=iLineEnd;iTemp++)
		{
		iStartX = LineIndex(iTemp);

		iTempEnd = LineIndex(iTemp+1); // find the start of the line beyond
		if (iTempEnd==-1) // then there is no other line - take the lastchar instead
			iTempEnd = GetTextLength( );
			else
			iTempEnd--; // so its back in line

		bResult &= FormatText(iStartX,iTempEnd);
		}

	if (bKeepPoint)
			SetSel(iXStart,iXEnd);
			else
			SetSel(iTempEnd,iTempEnd);

	return bResult;

}


///////////////////////////////////////////////////////////
// Function name	: CSymEditView::PasteSpecial
// Description	    : 
// Return type		: void 
// Argument         : UINT uClipFormat
// Argument         : DWORD dwAspect = 0
// Argument         : HMETAFILE hMF = 0
///////////////////////////////////////////////////////////
void CSymEditView::PasteSpecial(UINT uClipFormat, DWORD dwAspect, HMETAFILE hMF)
{


	StoreSelectPoint();
	
	LockWindowUpdate(true);

	StorePoint();
	CRichEditCtrl::PasteSpecial(uClipFormat,dwAspect,hMF); 
	ActionForNewSelectPoint();
	LockWindowUpdate(false);
	FormatToCurrentPoint(); 
	push_Edit();

//	PostMessage(WM_INVALIDATE);

	RECT CR;
	GetClientRect(&CR);
	InvalidateRect(&CR,TRUE);

}


void CSymEditView::StoreSelectPoint()
{
	char s1[10];
	GetSel(m_iLeftChar,m_iRightChar);
	m_iLeftLine = LineFromChar(m_iLeftChar);
	m_iRightLine = LineFromChar(m_iRightChar);
	m_iNumLines = GetLineCount();
	m_iNumChars = GetTextLength();
	m_iLineLength = LineLength(m_iLeftChar);

	if (m_iLeftChar<m_iRightChar)
			{
			LockWindowUpdate(true); // stop any flashing
		
			SetSel(m_iRightChar-1,m_iRightChar);
			GetSelText(s1);
			ATLTRACE("\nLast Character = '%s'",s1);
			ATLTRACE(" char =%d \n",s1[0]);
			SetSel(m_iLeftChar,m_iRightChar); // put things back
				
			LockWindowUpdate(false);

			if (s1[0]==13) // watch out for the control character at the end of lines that is counted by the control on the next line
				m_iRightLine--;
			}
	
}


///////////////////////////////////////////////////////////
// Function name	: CSymEditView::ActionForNewSelectPoint
// Description	    : Helper function - paired with StoreSelectPoint
//                    This function keeps records for m_lEdLines in step
//                    box with the edit
// Return type		: void 
///////////////////////////////////////////////////////////
void CSymEditView::ActionForNewSelectPoint()
{
	long iStep;
	long iLeftChar;
	long iRightChar;
	long iLeftLine;
	long iRightLine;
	long iNumLines;
	long iNumChars;
	long iLineLength;
	bool bLineChange=false;
	bool bNewLineChange=true;

	// Check we start well
	//ATLASSERT(m_lEdLines.size()==GetLineCount());

	GetSel(iLeftChar,iRightChar);
	iLeftLine = LineFromChar(iLeftChar);
	iRightLine = LineFromChar(iRightChar);
	iNumLines = GetLineCount();
	iNumChars = GetTextLength();
	iLineLength = LineLength(m_iLeftChar);


	ATLTRACE(" Before [%d-%d,",m_iLeftLine,m_iLeftChar);
	ATLTRACE("%d-%d] ",m_iRightLine,m_iRightChar);
	ATLTRACE(" After [%d-%d,",iLeftLine,iLeftChar);
	ATLTRACE("%d-%d]\n",iRightLine,iRightChar);

	
	// make changes for destruction of previous selection
	if ((m_iLeftChar!=iLeftChar)||(m_iRightChar!=iRightChar)||(m_iLeftLine!=iLeftLine)||(m_iRightLine!=iRightLine)
		||(m_iNumLines!=iNumLines)||(m_iNumChars!=iNumChars)) // the we have change
		{
		// the line that hold the left point has changed - collapse the selection if necessary
//		ATLTRACE("Before m_lEdLines[%d].reset() ",m_iLeftLine);
		m_lEdLines[m_iLeftLine].reset(); // this line has been edited
//		ATLTRACE(" after - PASSED\n");
		if ((m_iLeftLine!=iLeftLine)||(m_iRightLine!=iRightLine))
				bLineChange = true;
		for (iStep = m_iRightLine;iStep>m_iLeftLine;iStep--)
			m_lEdLines.erase(&m_lEdLines[iStep]);


		
		if (m_iNumLines>iNumLines)
			{
			if ((iLeftLine==m_iLeftLine)&&(iRightLine==m_iRightLine)) // then we have pressed delete and a line went
				{
				m_lEdLines.erase(&m_lEdLines[m_iLeftLine+1]); // note m_iLeftLine+1 always OK as in case m_iLeftLine = m_iNumLines at least one of the second two provisions are false
				bLineChange = true;
				}
				else
				if ((iLeftLine==m_iLeftLine-1)&&(iLeftLine==iRightLine)) // then backspace
					{
					m_lEdLines.erase(&m_lEdLines[m_iLeftLine]);
					bLineChange = true;
					}
					else
					if (m_lEdLines.size()>iNumLines) // a delete here also
						{
						m_lEdLines.erase(&m_lEdLines[iLeftLine]);
						bLineChange = true;
						bNewLineChange = false; // since the whole line went
						}
			}
		// now add lines as necessary

		if (iRightLine>iLeftLine) // then new lines are needed as multiple selection lines have been removed above
			{
			CSymEdLine sel;
			bLineChange = true;
			for (iStep = iLeftLine+1;iStep<=iRightLine;iStep++)
				{
//				sel.setCurrentLine(iStep + 1); // as lines are counted from 1 not 0 *done twice *
				m_lEdLines.insert(&m_lEdLines[iLeftLine],sel);
				}
			}
			else
			if (iLeftLine>m_iLeftLine) // this is a <CR> by itself - only one line - have to allow for the case where a selection is replaced
				{
				CSymEdLine sel;
				bLineChange = true;
				for (iStep = m_iLeftLine+1;iStep<=iLeftLine;iStep++)
					m_lEdLines.insert(&m_lEdLines[m_iLeftLine],sel);

				}

		if (bNewLineChange)
			m_lEdLines[iLeftLine].reset(); // this line has been edited also ( may be the same as m_iLeftLine )
			
		if (bLineChange) // need to refresh current line numbers
			{
				for (iStep = m_iLeftLine;(iStep<=m_lEdLines.size())&&(iStep<m_lEdLines.size());iStep++) // added check to avoid accessing unallocated memory
						m_lEdLines[iStep].setCurrentLine(iStep+1);
			}

		}

	
	// lets guarentee all is well - debug code
	if (m_lEdLines.size()!=GetLineCount())
			ATLTRACE("<Check warning> EdLines = %d, GetLineCount() = %d\n",m_lEdLines.size(),GetLineCount());
//	ATLASSERT(m_lEdLines.size()==GetLineCount());
	dumpList();
}


///////////////////////////////////////////////////////////
// Function name	: CSymEditView::IsSelectionFormulaBlocked
// Description	    : Helper function to determine if formula blocked.
// Return type		: bool 
///////////////////////////////////////////////////////////
bool CSymEditView::IsSelectionFormulaBlocked(long iP /*= -1*/)
{
	long iSelStart,iX;
	bool bResult = false;
	long iStep;
	long iLine=-1;
	long iLF,iLR;

	if (iP<0)
		GetSel(iX,iSelStart);
		else
		iX = iSelStart = iP; //  have been given a point

	// is this a formula line ? If so nothing further can happen
	iLF = LineFromChar(iX); // as lines are counted from 1 not 0
	iLR = LineFromChar(iSelStart); // as above
	if (m_bFormulaLock)
		{
		// its possible that more than one line will be deleted and replaced here

		ATLASSERT(iLR<m_lEdLines.size());
		ATLTRACE("iLR = %d m_lEdLines.size() = %d\n",iLR,m_lEdLines.size());

		try
		{
			for(iStep=iLF;(m_lEdLines.size()>=iStep)&&(!bResult)&&(iStep<=iLR);iStep++)
				{
				if (m_lEdLines[iStep].hasFunction())
						bResult=true;		
				}
		}
		catch(...)
			{
				// This is here just to avoid the programme crashing in the wild - its still very serrious
				ATLTRACE("<Error> in checking for formula locks - check index used on vector\n");
			}

		}

	return bResult;

}


///////////////////////////////////////////////////////////
// Function name	: CSymEditView::Undo
// Description	    : Overloaded undo function that reverses automatic formating
// Return type		: BOOL 
///////////////////////////////////////////////////////////
BOOL CSymEditView::Undo()
{
	BOOL bResult = TRUE;
	long iCount = pop_Edit() + 1; // +1 to do the original edit item the rest is formating
	long iT;

	StoreSelectPoint();

	for (iT=0;iT<iCount;iT++)
		bResult &= CRichEditCtrl::Undo();

	ActionForNewSelectPoint();
	StorePoint();
	FormatToCurrentPoint(true);

	return bResult;

}



///////////////////////////////////////////////////////////
// Function name	: CSymEditView::hasProtection
// Description	    : Helper fucntion to determine if line has protection
// Return type		: bool 
// Argument         : long iSel
///////////////////////////////////////////////////////////
bool CSymEditView::hasFormula(long iSel)
{
	long iLine = LineFromChar(iSel);
	bool bResult = false; // need a default
	
	if (iLine<0) // or else there's trouble
		return false;

	try
	{
		bResult = m_lEdLines[iLine].hasFunction();
	}
	catch(...) // say no to balls ups by def iLine should be < size m_lEdLines
	{
#ifndef NDEBUG
		ATLTRACE("<Error> with bResult = m_lEdLines[iLine].hasFunction();\n");
		ATLASSERT(iLine>m_lEdLines.size());
		ATLASSERT(false);
#endif
		bResult = false;
	}
	return bResult;
}
