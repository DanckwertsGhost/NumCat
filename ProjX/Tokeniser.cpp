// Tokeniser.cpp: implementation of the CTokeniser class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Tokeniser.h"

#include <assert.h>
#include <algorithm>
#include <fstream>
#include <string>

#include <iostream>
#include "Symlix/ErrorFactory.h"
#include "simulation.h" // to get a few constants for reading files

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////
// Function name	: CTokeniser::CTokeniser
// Description	    : 
// Return type		: 
// Argument         : setofwords& setFileNames
// Argument         : const mapUserDefinedKeys& cmapUDK 
///////////////////////////////////////////////////////////
CTokeniser::CTokeniser(setofwords& setFileNames, const mapUserDefinedKeys& cmapUDK ):m_rsetFileNames(setFileNames),m_iLineNo(0),m_iOffset(0),m_bState(true)
{
	m_pairTokenNoFile.second = false;
	Init(g_sDelim,g_iDelim,cmapUDK);
}



///////////////////////////////////////////////////////////
// Function name	: CTokeniser::CTokeniser
// Description	    : 
// Return type		: 
// Argument         : const char** psDelim
// Argument         : int iCountDelim
// Argument         : setofwords& setFileNames
// Argument         : const mapUserDefinedKeys& cmapUDK
///////////////////////////////////////////////////////////
CTokeniser::CTokeniser(const char** psDelim, int iCountDelim, setofwords& setFileNames, const mapUserDefinedKeys& cmapUDK  ):m_rsetFileNames(setFileNames),m_iLineNo(0),m_iOffset(0),m_bState(true)
{
	m_pairTokenNoFile.second = false;
	Init(psDelim,iCountDelim,cmapUDK);
	
}






///////////////////////////////////////////////////////////
// Function name	: CTokeniser::CTokeniser
// Description	    : 
// Return type		: 
// Argument         : const char*sDelimFile
// Argument         : setofwords& setFileNames
// Argument         : const mapUserDefinedKeys& cmapUDK 
///////////////////////////////////////////////////////////
CTokeniser::CTokeniser(const char*sDelimFile, setofwords& setFileNames, const mapUserDefinedKeys& cmapUDK  ):m_rsetFileNames(setFileNames),m_iLineNo(0),m_iOffset(0),m_bState(true)
{
	m_pairTokenNoFile.second = false;
	Init(sDelimFile,cmapUDK);
	
}

///////////////////////////////////////////////////////////
// Function name	: CTokeniser::Init
// Description	    : 
// Return type		: void 
// Argument         : const char** psDelim
// Argument         : int iCountDelim
// Argument         : const mapUserDefinedKeys& cmapUDK
///////////////////////////////////////////////////////////
void CTokeniser::Init(const char** psDelim, int iCountDelim, const mapUserDefinedKeys& cmapUDK )
{
	for (int iT=0;iT<iCountDelim;iT++)
		m_SetMathWords.insert(psDelim[iT]);
#ifndef NDEBUG
	cout << m_SetMathWords.size()<<endl;
#endif

	InitKeysandSets(cmapUDK);

}



///////////////////////////////////////////////////////////
// Function name	: CTokeniser::Init
// Description	    : 
// Return type		: void 
// Argument         : const char* sDelimFile
// Argument         : const mapUserDefinedKeys& cmapUDK
///////////////////////////////////////////////////////////
void CTokeniser::Init(const char* sDelimFile, const mapUserDefinedKeys& cmapUDK )
{

	ifstream iDelim;

	iDelim.open(sDelimFile,ios::out );

	if (!iDelim.is_open())
		{
		cerr << "<<Error*>> Unable to open deliminator file " << sDelimFile <<endl;
		SYMERRORLITE2("Unable to open deliminator stream ",sDelimFile,errSystem);
		m_bState=false;
		return;
		}
	
	try
	{
		char sBuf[CSIMULATION_SIZE];

	
		while(iDelim.rdstate()==0)
		{
		
			iDelim.getline(sBuf,CSIMULATION_SIZE);
			if ((sBuf!=NULL)&&(strlen(sBuf)>0))
				{
				string sTemp(sBuf);
				// check what happens if already enetered - as a set
				#ifndef NDEBUG
				cout << sBuf <<endl;cout.flush();
				#endif
				m_SetMathWords.insert(sTemp.c_str());
				}
		}
	}
	catch(...)
		{
		cerr << "<<Error*>> Unknown error whilst reading delimintator file "<<sDelimFile<<endl;
		SYMERRORLITE2("Unknown error whilst reading delimintator file ",sDelimFile,errInternal);
		cerr.flush();
		}


	#ifndef NDEBUG
	cout << m_SetMathWords.size() << endl; cout.flush();
	#endif

	iDelim.close();

	InitKeysandSets(cmapUDK);

}

///////////////////////////////////////////////////////////
// Function name	: CTokeniser::~CTokeniser
// Description	    : 
// Return type		: 
///////////////////////////////////////////////////////////
CTokeniser::~CTokeniser()
{
}

///////////////////////////////////////////////////////////
// Function name	: CTokeniser::tokeniseLine
// Description	    : 
// Return type		: long 
// Argument         : long lLine
// Argument         : const char* sLine
// Argument         : vector<CToken>& vct
// Argument         : const char* sFileName /*=NULL*/
// Argument         : bool bForPaint /*=false*/ this means reversing the order of solver and events so tokens will get the right flags for display - but this will mess up processing of the model which changes some events to solver tag latter - so only for display calls
///////////////////////////////////////////////////////////
long CTokeniser::tokeniseLine(long lLine, const char* sLine, list<CToken>& vct, const char* sFileName /*=NULL*/, bool bForPaint /*=false*/ )
{
	long lCount = 1;
	long lLast = 0;
	long lGap = 0;
	long lLen; // length of string - to avoid recalulating
//	long i;
	long lLenDelim;
	long lTokStart = vct.size();
	bool bFound = false;
	bool bNegLast = false;
	bool bInSquareBrackets = false;
	bool bPartArrayFlag = false;
	vector<CStringHolder>::iterator itSetCharEnd = m_vecDelimWords.end();	
	vector<CStringHolder>::iterator itFind;
	list<CToken>::iterator itListLineStart;
	bool bVCTEmpty=false;
	string strLine(sLine);
	list<CToken>::iterator itTokStart = vct.end();
	bool bChangeLC;
	if (vct.size()>0)
			itTokStart--;
	#ifndef NDEBUG // make sure my logic is correct here
			else
			ASSERT2(vct.begin()==vct.end());
	#endif

	string sLC = strLine;
	this->setStringLowerCase(sLC); // test in debug
	// may consider adding to std::string to aide handling....
	if ((sLine==NULL)||(strLine.length()==0))
					return 0;


	// find one before start of list
	if (vct.size()==0)
		{
		itListLineStart=vct.begin();
		bVCTEmpty=true;
		}
		else
		{
		itListLineStart=vct.end();
		itListLineStart--; // step one back
		}
	
	// need to establish and group Tokens to individual files
	pair< setofwords::iterator, bool > pairFile;
	if (sFileName)
			{
			pairFile = m_rsetFileNames.insert(sFileName);
			if (!pairFile.second)
				{
				pairFile.first = m_rsetFileNames.find(sFileName);
				ASSERT2(pairFile.first!=m_rsetFileNames.end());
				if (pairFile.first==m_rsetFileNames.end()) // then need to handle some how - even if _not_ happy
						{
						cerr <<"<Warning> Unable to add file information to Tokens - line "<<lLine <<" not read\n";
						SYMERROR("Unable to parse a line",errInternal,sFileName,lLine,0);
						return 0;
						}
				pairFile.second = true;
				}
			}
			else
			pairFile = m_pairTokenNoFile;

	ASSERT2(pairFile.second);
//	cerr << m_pairTokenNoFile.first->c_str()<<endl;
//	cerr << pairFile.first->c_str()<<endl;

	lLen = strLine.length();
	m_mnChecker.clear();

	do 
	{
	lGap = lCount - lLast; // gap will be reduced until a match is found
	bInSquareBrackets=false;
		do
		{
		#ifndef NDEBUG
		string sTest(sLC.substr(lCount-lGap,lGap));
		char c = sLC.substr(lCount-lGap,lGap).c_str()[0];
		#endif

		if (lGap==1) // then can test for square brackets and add pre number tracking
			{
			m_mnChecker.AddChar(sLC.substr(lCount-lGap,lGap).c_str()[0]);
			if ((bInSquareBrackets)&&(sLC.substr(lCount-lGap,lGap).c_str()[0]==g_CloseSquareBracket[0]))
							bPartArrayFlag=true;

			}

		if (bInSquareBrackets)
					{
					if (sLC.substr(lCount-lGap,lGap).c_str()[0]==g_CloseSquareBracket[0])
						bInSquareBrackets=false;
					}
					else
					{
					if (sLC.substr(lCount-lGap,lGap).c_str()[0]==g_OpenSquareBracket[0])
						{
						bInSquareBrackets=true;
//						bPartArrayFlag=true;
						}
					}
			
		if (bInSquareBrackets) // so everything in square brackets is a string
			lGap--;
			else
			{
//ATLTRACE("lGap %d, lCount %d substr %s\n",lGap,lCount,sLC.substr(lCount-lGap,lGap).c_str());

			itFind = find(m_vecDelimWords.begin(),m_vecDelimWords.end(),sLC.substr(lCount-lGap,lGap).c_str());
			if (itSetCharEnd!=itFind) // ie a Delim has been found
						{
							_ND int iV = sLC[lCount];cerr << iV <<endl;cerr.flush();
							if ((lGap==1)&&(lLen-lCount>0)&&(sLC[lCount-1]==c_Minus)&&
								((sLC[lCount/*as lCount = pt +1*/]>=48)&&(sLC[lCount]<=57))) // then we need to check for negative numbers
									if (lCount-lLast==1)	
										lGap--; // as its looking like a negative number
										else
										if ((lCount-lLast>1)&&(HasSpacesOnly(sLC.substr(lLast,lCount-lLast-1))))
											lGap--;
											else
											{
											//ATLTRACE("lLast %d lCount %d lGap %d\n",lLast,lCount,lGap);
											if (((lCount-lLast)>1)&&(lGap==1)&&(!m_mnChecker.Numeric()))
													bNegLast=true;
													else
													bNegLast=false;
											bFound = true;
											}
								else
									{
									bNegLast=false;
									bFound = true;
									}
						}
						else
							lGap--;
			} // end else if (bInSquareBrackets)
		}while((!bFound)&&(lGap>0)); 
		
// do stuff to make Tokens if any identified
	if (bFound)
		{
		// Search in reverse direction for largest Delim
		// it is assumed that the largest one is the one intended.
		// CStringHolders are ordered in terms of length hence
		// it 
		lLenDelim = itFind->len();
//		_ND cout <<strLine.substr(lCount-lGap,lLen-lCount+1).c_str()<<endl; 

		{
		long lNewCount=lCount;
		long lNewGap=lGap;
			itFind = FindLargest(lLast,lNewCount,lNewGap,sLC.substr(lLast,lLen-lLast),itFind);
		if ((itFind->len()>lLenDelim)&&((lNewCount-lNewGap)<=(lCount-lGap))) // then extend the search length
				{
				lCount=lNewCount;
				lGap=lNewGap;
				}
		}
/*
		itFind = FindLargest(strLine.substr(lCount-lGap,lLen-lCount+1),itFind);
		if (itFind->len()>lLenDelim) // then extend the search length
			{
			lGap += itFind->len() - lLenDelim;
			lCount += itFind->len() - lLenDelim;
			}
*/
		// there may be up to 2 strings to be assigned - the divsion between 
		// the two is given by lGap
		if (lGap != lCount-lLast) //there are two tags and this one goes first
				{
				#ifndef NDEBUG
				string sTest(strLine.substr(lLast,lCount-lLast-lGap));
				#endif
				vct.push_back(CToken(lLine,lLast,strLine.substr(lLast,lCount-lLast-lGap),pairFile.first,AssignTokenAsNumberorNot(strLine.substr(lLast,lCount-lLast-lGap)),bPartArrayFlag));
				bPartArrayFlag = false;
				}
		if (bNegLast)
				{
				lCount-=lGap; // so we will go looking for next with neg at start
				ASSERT2(lGap==1);
				ASSERT2(lCount>=0);
				}
				else
				vct.push_back(CToken(lLine,lCount-lGap,strLine.substr(lCount-lGap,lGap),pairFile.first,ctDelim));
		#ifndef NDEBUG
		string sTest(strLine.substr(lCount-lGap,lGap));
		#endif
		
		m_mnChecker.clear();
		bFound = false;
		lLast=lCount;
		}
	lCount++;


	}while(lCount<=strLine.length()); 

	//check if there is still a token to be assigned
	if (lCount>lLast+1) // then there's still a tag left
				vct.push_back(CToken(lLine,lLast,strLine.substr(lLast,lCount-lLast-lGap),pairFile.first,AssignTokenAsNumberorNot(strLine.substr(lLast,lCount-lLast-lGap)),bPartArrayFlag));	
	

	list<CToken>::iterator iT;
	
	if (bVCTEmpty)
		iT = vct.begin(); // aim to only cover the tokens from this line (speed issue)
		else
		iT = itListLineStart++;

	while(iT!=vct.end())
	{
		string sTest = iT->getString();
		iT->Trim();
		if (iT->getString().length()==0) // then must remove this element
						{
						vct.erase(iT--);
						iT++;
						}
					else
						iT++;
	}

	// Searc for any exponential numbers that are split over a number of Tokens - note positve ones detected automatically earlier
	// eg [5E],[-].[45]

	iT=itTokStart;

	if (iT==vct.end())
		iT=vct.begin();

	{ // as a precaution want to localise scope here of itEndMinus2
	list<CToken>::iterator itPlus1=iT;
	bool bLongEnough = true;
//	(iT!=vct.end());
//	(++itPlus1!=vct.end());
	if ((iT!=vct.end())&&(++itPlus1!=vct.end()))//(vct.size()>2)
		{
		list<CToken>::iterator itPlus2=itPlus1;
		if (++itPlus2!=vct.end())	
			{
			list<CToken>::iterator itEndMinus1 = vct.end(); itEndMinus1--;
			list<CToken>::iterator itEndMinus2 = itEndMinus1; itEndMinus2--;
			ASSERT2(iT!=vct.end());
			while((bLongEnough)&&(iT!=vct.end())&&(iT!=itEndMinus1)&&(iT!=itEndMinus2))
				{
				itPlus1=iT; itPlus1++; // needs to be reset every loop
				itPlus2=itPlus1; itPlus2++;
				ASSERT2(itPlus1!=vct.end());// as this would be very bad
				ASSERT2(itPlus2!=vct.end());
				_ND cout << vct.size() <<":"<< (long(vct.size())-2)<<endl;cerr.flush();
					if (iT->IsOfType(ctNumber))
							{
							long iLoc = iT->getString().rfind(g_Expon);
							if (iLoc==(iT->getString().length()-1))
									{ // maybe a negative exponent - postive exponents are spotted normally
										if ((itPlus1->IsOfType(ctDelim))&&(itPlus2->IsOfType(ctNumber))&&
											(itPlus1->getString().compare(g_Minus)==0)&&(itPlus2->getNumber()>0))
											{
												string sNew = iT->getString() + itPlus1->getString() + itPlus2->getString();
												if (IsANumber(sNew))
													{
													_ND long iBefore = vct.size();
													CToken ctNew(lLine,iT->getX(),sNew,pairFile.first,ctNumber);
													list<CToken>::iterator itIn = vct.insert(iT,ctNew);
													ASSERT2((*itIn)==ctNew);
													vct.erase(iT);
													iT=itIn; // otherwise loose track
													vct.erase(itPlus1);
													vct.erase(itPlus2);
													_ND cout << "Size before : "<<iBefore<<" and after : "<<vct.size()<<endl;cerr.flush();
													ASSERT2(iBefore==vct.size()+2);
													// note the end points have now changed so must be reassigned
													if (vct.size()<2)
															bLongEnough = false;
															else
															{		
															itEndMinus1 = vct.end(); itEndMinus1--;
															itEndMinus2 = itEndMinus1; itEndMinus2--;
															}
													}

											}



									}
									


							}


				iT++;
				}
			}
		}
	} // end itEndMinus2

	// update any ctDelim Tokens

	iT=itTokStart;

	if (iT==vct.end())
		iT=vct.begin();

	for(;iT!=vct.end();iT++)
		{
		setofwords::iterator itsow;
		setofwords::iterator itsowEnd;
		eTokenType eTok;
		string sTokstr = iT->getStringRef().c_str();
		bChangeLC = this->setStringLowerCase(sTokstr);
		if (iT->IsOfType(ctDelim))
			{

			itsow = m_SetMacroWords.find(sTokstr);
			if (itsow!=m_SetMacroWords.end())
					iT->setType(ctMacroKeyWord,bChangeLC);



			} // end (iT->IsOfType(ctDelim))
			else
			{
			if (iT->IsOfType(ctNotDefined))
				{
				/*
				IMPORTANT

				Must search for Event keywords BEFORE solver keywords as at least one word is in both
				and subsequent code requires that those words are identified as solver, not event.
				( That code deals with the event nature of the keyword ).
				eg See g_Sequence
				*/
				itsow = m_SetEquationWords.find(sTokstr);
				if (itsow!=m_SetEquationWords.end())
					iT->setType(ctEquationKeyWord,bChangeLC);
/*				itsow = m_SetEventWords.find(sTokstr);
				if (itsow!=m_SetEventWords.end())
					iT->setType(ctEventKeyWord,bChangeLC);*/
					else
					{
						//m_SetFuncWords
						itsow = m_SetFuncWords.find(sTokstr);
						if (itsow!=m_SetFuncWords.end())
							iT->setType(ctDelim,bChangeLC);
							else
							{

							if (bForPaint) // then check solver first 
								{
								itsowEnd = m_SetSolverWords.end();
								itsow = m_SetSolverWords.find(sTokstr);
								eTok = ctSolverKeyWord;
								}
								else // then check events first
								{
								itsowEnd = m_SetEventWords.end();
								itsow = m_SetEventWords.find(sTokstr);
								eTok = ctEventKeyWord;
								}

							if (itsow!=itsowEnd)
								iT->setType(eTok,bChangeLC);
								else
								{

								if (bForPaint) // then check solver next 
									{
									itsowEnd = m_SetEventWords.end();
									itsow = m_SetEventWords.find(sTokstr);
									eTok = ctEventKeyWord;
									}
									else // then check event next
									{
									itsowEnd = m_SetSolverWords.end();
									itsow = m_SetSolverWords.find(sTokstr);
									eTok = ctSolverKeyWord;
									}


								if (itsow!=itsowEnd)
									iT->setType(eTok,bChangeLC);
									else
									{
									itsow = m_SetTypeModifierWords.find(sTokstr);
									if (itsow!=m_SetTypeModifierWords.end())
										iT->setType(ctTypeModifier,bChangeLC);
										else
										{
										itsow = m_SetUserDefinedWords.find(iT->getStringRef()); // these will be case sensative
										if (itsow!=m_SetUserDefinedWords.end())
											iT->setType(ctUserDefined); // so it will be picked up later
											else
											{
											itsow = m_SetArrayWords.find(sTokstr);
											if (itsow!=m_SetArrayWords.end())
												iT->setType(ctArrayKeyWord,bChangeLC);


											}
										}

									} // end else (itsow!=m_SetEquationWords.end())

								} // end else (itsow!=m_SetEventWords.end())

							} // end else (itsow!=m_SetFuncWords.end())
						} // end else (itsow!=m_SetSolverWords.end())
					
					} // end (vct[i].IsOfType(ctNotDefined))


			}// end else (iT->IsOfType(ctDelim))

		} // end 	for(long i=lTokStart;i<vct.size();i++)

	
	return vct.size()-lTokStart;
}


///////////////////////////////////////////////////////////
// Function name	: CTokeniser::TrimForChar
// Description	    : Triming for set character
// Return type		: void 
// Argument         : string& sToken
// Argument         : const char c
///////////////////////////////////////////////////////////
void CTokeniser::TrimForChar(string& sToken, const char c)
{
long lleft=0;
long lright=sToken.length()-1;
bool bStop = false;

while((!bStop)&&(lleft<lright))
	{
	if (sToken[lleft]==c)
				lleft++;
			else
				bStop=true;
	}
bStop=false;
while((!bStop)&&(lright>lleft))
	{
	long lTok = sToken[lright];
	if (sToken[lright]==c)
				lright--;
			else
				bStop=true;
	}
sToken = sToken.substr(lleft,lright-lleft+1);

}

bool CTokeniser::IsANumber(const string str )
{
	bool bResult = true;
	int iStops =0;
	string sTest;
	string::const_iterator iEnd;
	string::const_iterator iExp;
	string::const_iterator iEndPlusOne;

	sTest = str;
	TrimForChar(sTest,' ');

	iEnd = sTest.end();
	iExp = iEnd;
	iEndPlusOne = iEnd;

	for (string::const_iterator iS = sTest.begin();iS!=iEnd;iS++)
		{
		 if (bResult&&(!((*iS>=48)&&(*iS<=57)))) // then may show its not a number -- nb NAN not supported.
				if (((iStops==0)&&(*iS=='.'))&&(iEnd==iExp)) // ensure not in expoent part for decimal point
					iStops++;
				else
					if ((*iS=='E')&&(iEnd==iExp)) // it could be an exponent
						{
						 iExp=iS;iEndPlusOne=iS;iEndPlusOne++;
							
						}
						else
						if (!((*iS=='-')&&((iS==sTest.begin())||(iS==iEndPlusOne)))) // not too sure if +1 is OK for pointers
							bResult = false;
		}

	return bResult;
}



///////////////////////////////////////////////////////////
// Function name	: CTokeniser::HasSpacesOnly
// Description	    : Function to check only spaces in string.
// Return type		: bool 
// Argument         : const string& sCheck
///////////////////////////////////////////////////////////
bool CTokeniser::HasSpacesOnly(const string& sCheck ) const
{
	bool bResult=true;
	long iLen = sCheck.length();
	for (long i=0;i<iLen;i++)
		bResult &= (sCheck[i]==' ');

	return bResult;
}


ostream& CTokeniser::DumpDelim(ostream& os) const
{
	ostream_iterator<CStringHolder> out(cout," [Delim]\n"); // see p53 STL book
	
//	cout << m_SetDelimWords.size()<<endl;
//	copy(m_SetDelimWords.begin() ,m_SetDelimWords.end(),out);
	cout << m_vecDelimWords.size()<<endl;
	copy(m_vecDelimWords.begin() ,m_vecDelimWords.end(),out);


	return os;
}


///////////////////////////////////////////////////////////
// Function name	: CTokeniser::FindLargest
// Description	    : 
// Return type		: vector<CStringHolder>::iterator 
// Argument         : const string& sExp
// Argument         : vector<CStringHolder>::iterator& it
///////////////////////////////////////////////////////////
vector<CStringHolder>::iterator CTokeniser::FindLargest(const string& sExp, vector<CStringHolder>::iterator& it) const
{
	vector<CStringHolder>::const_iterator itEnd;
	vector<CStringHolder>::iterator itLook;
	vector<CStringHolder>::iterator itResult = it; // default value
	
	itEnd = m_vecDelimWords.end();

	itLook = ++it;

//	cout << "\n<<CTokeniser::FindLargest >>\n";
//	cout << sExp.c_str()<<endl;
//	cout << "Initial delim = "<<it->c_str()<<endl;

	while(itEnd!=itLook)
		{
		if (sExp.find(itLook->c_str())==0) // assumes set ordered in correct way
			{
//			cout << itLook->c_str()<<" to replace "<<itResult->c_str()<<endl; cout.flush();
			itResult = itLook;
			}
		itLook++;
		}

	return itResult;

}


///////////////////////////////////////////////////////////
// Function name	: CTokeniser::FindLargest
// Description	    : 
// Return type		: vector<CStringHolder>::iterator 
// Argument         : long lLast
// Argument         : long& lCount
// Argument         : long& lGap
// Argument         : const string& sExp
// Argument         : vector<CStringHolder>::iterator& pit
///////////////////////////////////////////////////////////
vector<CStringHolder>::iterator CTokeniser::FindLargest(long lLast,long& lCount, long& lGap, const string& sExp, vector<CStringHolder>::iterator& it) const
{
	vector<CStringHolder>::iterator itResult = it; // default value
	vector<CStringHolder>::iterator itLast = it; // default value
	vector<CStringHolder>::const_iterator itEnd;
	vector<CStringHolder>::iterator itLook;
	long lStart=lCount-lGap;


	itEnd = m_vecDelimWords.end();

	_ND cerr << sExp.c_str()<<endl;cerr.flush();

	// Working from far left up until lCoount-lGap
	long lT1 = lCount-lGap;
	bool bFound = false;
	long lLimit = (lCount-lGap-lLast);

/*
	string sTest("Woofer");
	long lPoint = sTest.find("Woof");
	lPoint = sTest.find("oof");
	lPoint = sTest.find("Wvvf");
	lPoint = sTest.find("oo");
*/
	lT1=0;
	while((!bFound)&&(lT1<=lLimit))// NEED TO ADJUST SO DOESN@T GO TO FAR LEFT
	{
		ASSERT2(lT1<sExp.length());
		itLook=itResult; // to avoid researching ( :-) )
		
		while(itLook!=itEnd)
			{
			if (sExp.substr(lT1,sExp.length()-lT1).find(itLook->c_str())==0)
				{
				itResult = itLook;
				lStart=lT1;
				}
			itLook++;

			}

		lT1++;
	}

	_ND cerr << (*itResult)<<":"<<lStart<<endl; cerr.flush();		

	lCount=lLast+lStart+itResult->len();
	lGap=itResult->len();

	_ND cerr <<"lCount="<<lCount<<" lGap="<<lGap<<" and lLast was "<<lLast<<endl;

	return itResult;
}
	
eTokenType CTokeniser::AssignTokenAsNumberorNot(const string& str)
{
 if (IsANumber(str))
	 return ctNumber;
 return ctNotDefined;

}


///////////////////////////////////////////////////////////
// Function name	: CTokeniser::InitEventKeys
// Description	    : Populate set of Event key words
//                    to be used to determine CToken types
// Return type		: void 
///////////////////////////////////////////////////////////
void CTokeniser::InitEventKeys()
{
	for (int iT=0;iT<g_iEvents;iT++)
		m_SetEventWords.insert(g_sEvents[iT]);
//	_ND cout << g_DDEserver << endl;
//	_ND cout << m_SetEventWords.size()<<endl;cout.flush();

}


///////////////////////////////////////////////////////////
// Function name	: CTokeniser::InitSolverKeys
// Description	    : Populate set of Solver key words
//                    to be used to determine CToken types
// Return type		: void 
///////////////////////////////////////////////////////////
void CTokeniser::InitSolverKeys()
{
	for (int iT=0;iT<g_iSolvers;iT++)
		m_SetSolverWords.insert(g_sSolvers[iT]);
//	_ND cout << m_SetSolverWords.size()<<endl;cout.flush();

}


///////////////////////////////////////////////////////////
// Function name	: CTokeniser::InitEquationKeys
// Description	    : Populate set of Equation key words
//                    to be used to determine CToken types
// Return type		: void 
///////////////////////////////////////////////////////////
void CTokeniser::InitEquationKeys()
{
	for (int iT=0;iT<g_iEquations;iT++)
		m_SetEquationWords.insert(g_sEquations[iT]);

}


///////////////////////////////////////////////////////////
// Function name	: CTokeniser::InitArrayKeys
// Description	    : Populate set of Array key words
//                    to be used to determine CToken types
// Return type		: void 
///////////////////////////////////////////////////////////
void CTokeniser::InitArrayKeys()
{
	for (int iT=0;iT<g_iArrays;iT++)
		m_SetArrayWords.insert(g_sArrays[iT]);

}

///////////////////////////////////////////////////////////
// Function name	: CTokeniser::InitTypeModifierKeys
// Description	    : Populate set of Equation key words
//                    to be used to determine CToken types
// Return type		: void 
///////////////////////////////////////////////////////////
void CTokeniser::InitTypeModifierKeys()
{
	for (int iT=0;iT<g_iTypeModifier;iT++)
		m_SetTypeModifierWords.insert(g_sTypeModifiers[iT]);

}
///////////////////////////////////////////////////////////
// Function name	: CTokeniser::InitMacroKeys
// Description	    : Populate set of Macro key words
//                    to be used to determine CToken types
// Return type		: void 
///////////////////////////////////////////////////////////
void CTokeniser::InitMacroKeys()
{
	for (int iT=0;iT<g_iMacros;iT++)
		m_SetMacroWords.insert(g_sMacros[iT]);

}



///////////////////////////////////////////////////////////
// Function name	: CTokeniser::InitFuncVec
// Description	    : Populate function keys
// Return type		: void 
///////////////////////////////////////////////////////////
void CTokeniser::InitFuncKeys()
{
	for (int iT=0;iT<g_iFuncs;iT++)
		m_SetFuncWords.insert(g_sFuncs[iT]);

}

///////////////////////////////////////////////////////////
// Function name	: CTokeniser::InitUserDefinedKeys
// Description	    : 
// Return type		: void 
// Argument         : const mapUserDefinedKeys& cmapUDK
///////////////////////////////////////////////////////////
void CTokeniser::InitUserDefinedKeys(const mapUserDefinedKeys& cmapUDK)
{
	for(mapUserDefinedKeys::const_iterator cit = cmapUDK.begin(); cit != cmapUDK.end(); cit++)
		if (cit->first != g_TagSub ) // otherwise it gets into the list twice - not that important, but cleaner this way
			m_SetUserDefinedWords.insert(cit->first.c_str());

}


///////////////////////////////////////////////////////////
// Function name	: CTokeniser::InitDelimVec
// Description	    : create a vector of merged key words
// Return type		: void 
///////////////////////////////////////////////////////////
void CTokeniser::InitDelimVec()
{

	// lets get ready 
	m_vecDelimWords.resize(m_SetMathWords.size()
						   +m_SetMacroWords.size());


	vector<CStringHolder>::iterator itDelim;//ostream_iterator<int>(cout, " ")
	#ifndef NDEBUG
	cout <<m_SetEquationWords.size()<<endl;
	#endif

	itDelim = set_union(m_SetMathWords.begin(),m_SetMathWords.end(),m_SetMacroWords.begin(),m_SetMacroWords.end(),m_vecDelimWords.begin());

	sort(m_vecDelimWords.begin(),m_vecDelimWords.end());

#ifndef NDEBUG
	DumpDelim(cout);
#endif

}



///////////////////////////////////////////////////////////
// Function name	: CTokeniser::InitKeysandSets
// Description	    : 
// Return type		: void 
// Argument         : const mapUserDefinedKeys& cmapUDK
///////////////////////////////////////////////////////////
void CTokeniser::InitKeysandSets(const mapUserDefinedKeys& cmapUDK)
{
	if (m_rsetFileNames.size()==0)
			m_pairTokenNoFile = m_rsetFileNames.insert(g_TokenNoFile);
			else
			{
			m_pairTokenNoFile.first = m_rsetFileNames.find(g_TokenNoFile);
			if (m_pairTokenNoFile.first!=m_rsetFileNames.end())
						m_pairTokenNoFile.second = true;
						else
						m_pairTokenNoFile.second = false;
			}

//	ASSERT2(m_pairTokenNoFile.first==m_rsetFileNames.begin());
//	cerr << m_pairTokenNoFile.first->c_str()<<endl;

	InitEventKeys();
	InitSolverKeys();
	InitFuncKeys();
	InitEquationKeys();
	InitArrayKeys();
	InitTypeModifierKeys();
	InitMacroKeys();
	InitUserDefinedKeys(cmapUDK);
	InitDelimVec();
}


///////////////////////////////////////////////////////////
// Function name	: CTokeniser::getNoFilePointer
// Description	    : To provide a copy of the pointer to no file
// Return type		: bool : return false if this iterator has not yet been allocated.
// Argument         : setofwords::const_iterator& cit
///////////////////////////////////////////////////////////
bool CTokeniser::getNoFilePointer(setofwords::const_iterator& cit)
{

	cit = m_pairTokenNoFile.first;

	return m_pairTokenNoFile.second;
}



///////////////////////////////////////////////////////////
// Function name	: CTokeniser::spinUpMacroTokens
// Description	    : assign everything after a g_Define macro statement to 
//                    an entry in the macro define map.
// Return type		: bool 
// Argument         : mapUserDefinedKeys& mapUDK
// Argument         : const list<CToken>& vct
///////////////////////////////////////////////////////////
bool CTokeniser::spinUpMacroTokens( mapUserDefinedKeys& mapUDK, const list<CToken>& vct )
{

	mapUDK.clear();
	string sFile="";
	string strkey="";
	bool bRecordingLine = false;
	bool bCommentLine = false;
	bool bFirst = false;
	list<CToken> listLocal;

	list<CToken>::const_iterator cit = vct.begin();
	list<CToken>::const_iterator citLast;

	while(cit!=vct.end())
	{

		if (bRecordingLine) // always false for first pass - therefore sameLine method OK 
			{
//			if ((!cit->sameLine(*citLast)/*cit->getLine()!=iLine*/)||(sFile.compare(cit->getLocation().getRefFile()->c_str())!=0))
			if (!cit->sameLine(*citLast))
					{
					bRecordingLine=false;
					bCommentLine=false;// maybe unecessary
					ASSERT2(strkey.length()>0);
					mapUDK[strkey] = listLocal;
					}
					else
					if (bFirst)
							{
							strkey=cit->getString().c_str();
							bFirst=false;
							}
							else
							if ((cit->IsOfType(ctDelim))&&(cit->getString().compare(g_Comment)==0))
									{
									bRecordingLine=false; // the rest are comments
									bCommentLine=true; // in case further macro stuff follows that has been commented out
									ASSERT2(strkey.length()>0);
									mapUDK[strkey] = listLocal;
									}
									else
									listLocal.push_back(*cit); // add a *copy* of CToken

			}

		if (!bRecordingLine) // since we could be at the start of a new line
			{
			if ((bCommentLine)&&(!cit->sameLine(*citLast))) // as bCommentLine=false first run citLast is always assigned
					bCommentLine=false;
	
			if ((cit->IsOfType(ctDelim))&&(cit->getString().compare(g_Comment)==0))
					bCommentLine=true;

			if ((!bCommentLine)&&(cit->IsOfType(ctMacroKeyWord))&&(cit->getString().compare(g_Define)==0))
					{
					bRecordingLine=true;
				//	sFile = cit->getLocation().getRefFile()->c_str();
					listLocal.clear();	
					bFirst=true;
					}

			}
	citLast=cit;
	cit++;

	}

	if (bRecordingLine)
		mapUDK[strkey] = listLocal;

	return (mapUDK.size()>0);
}



///////////////////////////////////////////////////////////
// Function name	: CTokeniser::setStringLowerCase const
// Description	    : Helper function to turn string into lower case
// Return type		: void 
// Argument         : string& rsStr
///////////////////////////////////////////////////////////
/*void CTokeniser::setStringLowerCase(string& rsStr) const
{
	long iC;

	for(iC=0;iC<rsStr.length();iC++)
		{
		ATLTRACE("[%s] count=%d ascii %d ",rsStr.c_str(),iC,rsStr[iC]);
		if ((rsStr[iC] < 90)&&(rsStr[iC]>64))
				rsStr[iC]+=32;
		ATLTRACE(" after [%s]\n",rsStr.c_str());
		}
}*/


///////////////////////////////////////////////////////////
// Function name	: CHoldTokeniser::CHoldTokeniser
// Description	    : Constructor that hides the construction of Tokeniser
// Return type		: 
///////////////////////////////////////////////////////////
CHoldTokeniser::CHoldTokeniser():m_pTokeniser(NULL)
{
	m_pTokeniser = newtrack CTokeniser(g_sDelim,g_iDelim,m_setRecognisedFileNames,m_mapUDK);
	ATLASSERT(m_pTokeniser);
}


///////////////////////////////////////////////////////////
// Function name	: CHoldTokeniser::~CHoldTokeniser
// Description	    : 
// Return type		: 
///////////////////////////////////////////////////////////
CHoldTokeniser::~CHoldTokeniser()
{
	if (m_pTokeniser)
		delete m_pTokeniser;

}


///////////////////////////////////////////////////////////
// Function name	: CHoldTokeniser::getTokenisedList
// Description	    : 
// Return type		: list<CToken>& 
// Argument         : long iLine
// Argument         : const char* sLine
// Argument         : const char* sStreamName
///////////////////////////////////////////////////////////
list<CToken>& CHoldTokeniser::getTokenisedList(long iLine, const char* sLine, const char* sStreamName )
{
	
	if (!m_pTokeniser) // then things are desperately wrong
		{
		ATLTRACE("<Error> CHoldTokeniser::CSymHoldTokeniser::m_pTokeniser is NULL.\n");
		ASSERT2(false);
		return m_lToks; // have to do something
		}
	m_lToks.clear();
	m_pTokeniser->tokeniseLine(iLine,sLine,m_lToks,sStreamName,true);

	return m_lToks;
}


///////////////////////////////////////////////////////////
// Function name	: CHoldTokeniser::assignVariables
// Description	    : Assign variables that can be infered in a line
// Return type		: void 
// Argument         : vector<CToken*>& rvecLpts
///////////////////////////////////////////////////////////
void CHoldTokeniser::assignVariables( vector<CToken*>& rvecLpts ) const
{
	CTokeniser::assignVariables(rvecLpts);

}


vector<CToken*>& CTestHoldTokeniser::getRefVectorOfTokenPointers(long iLine, const char* sLine, const char* sStreamName )
{
//		vector<CToken*> m_vecCToks;
/*#ifndef NDEBUG
	ostream_iterator<CToken> out(cout,"\t"); // see p53 STL book
#endif*/

	list<CToken>::iterator cit;
	m_vecCToks.clear();
	getTokenisedList(iLine,sLine,sStreamName);
	

/*#ifndef NDEBUG

	copy(m_lToks.begin(),m_lToks.end(),out);
	cout << endl;
#endif*/

	m_vecCToks.reserve(m_lToks.size());
	for(cit=m_lToks.begin();cit!=m_lToks.end();cit++)
		m_vecCToks.push_back(&(*cit));

	return m_vecCToks;
}


void CTokeniser::assignVariables(vector<CToken*>& rvecLpts)
{

	vector< CToken* >::iterator itpCT;
	CToken* pctLast = NULL;
	bool bComment=false;
	eTokenType eTT;
	
	if (rvecLpts.size()==0)
			return;

	eTT = (*(rvecLpts.begin()))->getType();

	for(itpCT=rvecLpts.begin();itpCT!=rvecLpts.end();itpCT++)
				{
				if ((pctLast)&&(!(*itpCT)->sameLine(*pctLast))) // so comments reset for each 'sub-line'
												bComment=false;

				if ((!bComment)&&((*itpCT)->getString().compare(g_Comment)==0))// is it an //
												bComment=true; // so ignore the rest of the line
				if (bComment)
									(*itpCT)->setType(ctComment);
									// not changing ctNotDefined here - as not all items will be variables
				switch(eTT)
							{
							case ctEquationKeyWord:
									if ((*itpCT)->getType()==ctNotDefined)
												(*itpCT)->setType(ctVariable);
									break;
							case ctArrayKeyWord:
								#ifndef NDEBUG
								cout << (**itpCT) <<endl;
								#endif
									if ((*itpCT)->getType()==ctNotDefined)
												(*itpCT)->setType(ctVariable);
								#ifndef NDEBUG
								cout << (**itpCT) <<endl;
								#endif
									break;
							default:
									// do nothing
									break;
							}

				pctLast = (*itpCT); // to check line changes
				}



}

void CTokeniser::CMaybeNumber::AddChar( char c )
{
	m_bLastNumeric = m_bNumeric;

	if (!m_bNumeric)
		return; // nothing more to do

	switch(c)
	{
		case c_Minus:
				
				if (m_bStartNeg)
						m_bNumeric=false;
						else
						if (m_bFirst)
								m_bStartNeg=true;
								else
								m_bNumeric=false;
			break;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			break;
		case 'e':
				if (m_bLastE)
					m_bNumeric=false;
					else
					m_bLastE=true;
			break;
		case '.':
				if ((m_bHasDecimal)||(m_bLastE))
					m_bNumeric=false;
					else
					m_bHasDecimal=true;
			break;


		default:
			m_bNumeric = false;
			break;

	};


	m_bFirst=false;


}
