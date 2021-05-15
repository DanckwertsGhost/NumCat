// Simulation.cpp: implementation of the CSimulation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <atlbase.h>
#include "Simulation.h"
#include "EquationFactory.h"
#include "assert.h"
#include <fstream>
#include "Tokeniser.h"
#include <algorithm>
#include "SolClassFactory.h"
#include "EventFactory.h"
#include "SimRun.h"
#include "EvStart.h"
#include "csvHolderFactory.h"
#include "StrongTypeFactory.h"
#include "Symlix\ErrorFactory.h"
#include "ArrayFactory.h"
#include "IndexFactory.h"
#include "EvItValueStep.h"

//#include <objbase.h>

//#include <set>

//#define DEBUGSETS
#define REVERSE_ORDER


#define SYMLIXSTORE

class CSortTokenPointers
{
public: 
	CSortTokenPointers(){}
	~CSortTokenPointers(){}
	inline bool operator()(CToken* pCT1, CToken* pCT2) {
	 if (!pCT1)
	      if (pCT2)
				return true;
				else
				return false; // as the same
	 
//	 return pCT1->greaterThan(*pCT2); 
	 return pCT1->getString().compare(pCT2->getString().c_str())<0;
	}
};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CSimulation::CSimulation():m_pIARDataStore(NULL),m_sFile(""),m_sTag(""),m_eState(cessUninitated),m_cmModel(),m_pSolver(NULL),m_vecOrderedVarTokens(),m_pOutsideStop(NULL),m_OutsideSetData(),m_OutsideGetData()
{
	m_setPtUniqueTokens.clear(); // just to be sure
}

CSimulation::CSimulation(const string& sFileLoc):m_pIARDataStore(NULL),m_sFile(""),m_sTag(""),m_eState(cessUninitated),m_cmModel(),m_pSolver(NULL),m_vecOrderedVarTokens(),m_pOutsideStop(NULL),m_OutsideSetData(),m_OutsideGetData()
{
	m_setPtUniqueTokens.clear(); // just to be sure
	setFile(sFileLoc); // boolean return - should throw exception when implemented
	assert(sFileLoc.compare(m_sFile)==0);
}



CSimulation::CSimulation(IARDataStore* pIStore, const string& sFileLoc):m_pIARDataStore(pIStore),m_sFile(""),m_sTag(""),m_eState(cessUninitated),m_cmModel(),m_pSolver(NULL),m_vecOrderedVarTokens(),m_pOutsideStop(NULL),m_OutsideSetData(),m_OutsideGetData()
{
#ifndef NDEBUG
	int iRC = m_pIARDataStore->AddRef();
	ATLTRACE("Ref count m_pIARDataStore after AddRef = %d",iRC);
#else
	m_pIARDataStore->AddRef();

#endif
	m_setPtUniqueTokens.clear(); // just to be sure
	setFile(sFileLoc); // boolean return - should throw exception when implemented
	assert(sFileLoc.compare(m_sFile)==0);
	ASSERT2(m_pIARDataStore);
//	if (!m_pIARDataStore)
//		m_eState = ERROR -error status not yet in class
}


///////////////////////////////////////////////////////////
// Function name	: CSimulation::setFile
// Description	    : Set the internal file reference, having checked the file exits first.
//                    If returns true then internal state will be cessHasFile otherwise 
//					  cessUninitated.
// Return type		: bool 
// Argument         : const string& sFileLoc
///////////////////////////////////////////////////////////
bool CSimulation::setFile(const string& sFileLoc)
{
	if (!checkFileExists(sFileLoc))
		{
		m_eState = cessUninitated;
		return false;
		}

	m_sFile = sFileLoc;
	m_eState = cessHasFile; // if the object was initiated then it need to be cleared out
	return (sFileLoc.compare(m_sFile)==0);
}

CSimulation::~CSimulation()
{
//	ATLASSERT(false);
	if (m_pIARDataStore)
		m_pIARDataStore->Release();

	CEventFactory* pcef = CEventFactory::instance();
	pcef->finalRelease();
	// tempory for debugging - useful as know most is over here.
	cout <<"Simulation finished\n";
}


///////////////////////////////////////////////////////////
// Function name	: CSimulation::setUpSimulation
// Description	    : Read files a create list of Tokens to process
//                    as lines, equations events etc
// Return type		: bool 
///////////////////////////////////////////////////////////
bool CSimulation::setUpSimulation()
{

	mapUserDefinedKeys mapUDK; // allows info learnt from Macros to pass between parsing runs
#ifndef NDEBUG
	ostream_iterator<CToken> out(cout,"\n"); // see p53 STL book
#endif
	bool bFirstPass = true;

	wipeFactories(); // avoid data hanging over if run twice without exiting 
	m_vecOrderedVarTokens.clear();// to stop out of sync info getting out
	// Parse one - populate macros
	if (!setUpSimulationPass(bFirstPass,mapUDK))
			return false;

	bFirstPass=false;
	// Parse two - fill in macros
	if (!setUpSimulationPass(bFirstPass,mapUDK))
			return false;

	expandUserDefinedMacros(mapUDK);
#ifndef NDEBUG

		list< CToken >::iterator pTest = m_ltTokens.begin();
		copy(m_ltTokens.begin(),m_ltTokens.end(),out);
		cout << endl;
#endif
	m_eState=cessHasFile;

#ifdef NDEBUG // then let it happen
	try
#endif
	{
	GenerateLines();
	GenerateStructure();
	if (!expandIndecies(ERROR_OS)) // may need a change to states top guarentee this
			return false;
	unifyEquationTokens();

#ifndef NDEBUG
		copy(m_ltTokens.begin(),m_ltTokens.end(),out);

		cout << endl;
#endif
	if (!checkModel(ERROR_OS))
			return false;

	}
#ifdef NDEBUG
	catch(...)
		{
		ERROR_OS << "<Internal Error*> Undefined error processing input file" << endl;ERROR_OS.flush();
		SYMERROR("Undefined error processing input streams",errInternal,"",NOT_DEFINED,NOT_DEFINED);
		return false;
		}
#endif
	return true;

}



///////////////////////////////////////////////////////////
// Function name	: CSimulation::setUpSimulationPass
// Description	    : Helper function - since files must be parsed twice
// Return type		: bool 
///////////////////////////////////////////////////////////
bool CSimulation::setUpSimulationPass(bool bFirstPass, mapUserDefinedKeys& mapUDK)
{

	IARStream* pIStream = NULL;
#ifndef NDEBUG
	ostream_iterator<CToken> out(cout,"\n"); // see p53 STL book
#endif
	enumARReadHint erhint = readFormatFreeText;

	// start by resetting the simulation - MUST BE BEFORE CREATION CTokeniser
	clearSimulation(!bFirstPass);

	CTokeniser cTokeniser(g_sDelim,g_iDelim,m_setRecognisedFileNames,mapUDK); 
//	CTokeniser cTokeniser("Delim.txt",m_setRecognisedFileNames,mapUDK); 
	_ND ERROR_OS << "Start of Error Log\n";

	if (!cTokeniser.isReady())
		{
		cerr << "<Error*> Unable to initialise tokens. Check file "<<"Delim.txt"<<"\n";
		SYMERROR("Unable to initialise tokens",errInternal,"",NOT_DEFINED,NOT_DEFINED);
		return false;
		}

	bool bNoFilePointer = cTokeniser.getNoFilePointer(m_itNoFileName);
	ASSERT2(bNoFilePointer);

	if (!bNoFilePointer)
		{
		cerr << "<Internal Error*> Unable to initialise inferred tokens.\n";
		SYMERROR("Unable to initialise inferred tokens",errInternal,"",NOT_DEFINED,NOT_DEFINED);
		return false;
		}

	if (m_eState!=cessHasFile)
		{
		 // then this isn't going to work as currently only set up to read files
		 cerr << "<Internal Error*> Unable to intialise solver component. Error No "<<ERROR_EVENT_SOLVER_STATE_NOT_READY <<", report to vendor.\n";
		 SYMERROR("Unable to intialise solver component",errInternal,"",NOT_DEFINED,NOT_DEFINED);
		 return false;
		}

	if (!cTokeniser.isReady())
		{
		cerr << "<Error*> Not able to parse file due to earlier error.\n"; 
		SYMERROR("Not able to parse file due to earlier error",errSystem,"",NOT_DEFINED,NOT_DEFINED);
		return false;
		}	

	CComBSTR cbFileName(m_sFile.c_str());

	HRESULT hr = m_pIARDataStore->tryToGetARStream(&(cbFileName.m_str),erhint,&pIStream);


	if ((FAILED(hr))||(!pIStream))
		{
		cerr << "<Error*> Unable to find or open file named "<<m_sFile.c_str()<<"."<<endl;
		SYMERROR("Unable to find or open stream",errSystem,m_sFile.c_str(),NOT_DEFINED,NOT_DEFINED);
		return false;
		}

	enumARStream ess;
	hr = pIStream->get_StreamState(&ess);
	if ((FAILED(hr))||(ess!=streamLoaded))
		{
		cerr << "<Error*> Problem loading file "<<m_sFile.c_str()<<"."<<endl;
		SYMERROR("Problem loading stream",errSystem,m_sFile.c_str(),NOT_DEFINED,NOT_DEFINED);
		pIStream->Release();
		return false;
		}

	// parse file
#ifndef CRASHHARD
	try
#endif
	{
		CComBSTR cbLine;
		long lLine = 0;
		string sLine;		
		while((SUCCEEDED(pIStream->get_StreamState(&ess)))&&((ess==streamReadline)||(ess==streamLoaded))&&(SUCCEEDED(pIStream->readLine(&(cbLine.m_str)))))
		{

			{
			USES_CONVERSION;
			sLine = OLE2A(cbLine.m_str);
			}
			_ND cout << "<X>"<<sLine.c_str() << endl; // for DEBUG
			cTokeniser.tokeniseLine(lLine,sLine.c_str(),m_ltTokens,m_sFile.c_str());
			lLine++; // so the location of the Tokens are known as well as the type

		}

		pIStream->Release();

#ifndef NDEBUG
		cout << "After reading "<<m_sFile.c_str()<<endl;
		cout << "Number of Tokens = "<<m_ltTokens.size()<<endl;
		copy(m_ltTokens.begin(),m_ltTokens.end(),out);
		cout << endl << cTokeniser <<endl;
#endif

		bool bFindSyntaxError = false;

		while(expandAndSubstituteNextInclude(m_ltTokens,cTokeniser,cerr,bFindSyntaxError));

		if (bFindSyntaxError)
				return false;

		if (bFirstPass)
			{
			cTokeniser.spinUpMacroTokens(mapUDK,m_ltTokens); // must be first as mapUDK gets cleared
			// have to ensure any Tags are replaced
			CToken ctTag;
			ctTag.setString(m_sTag);
			ctTag.setType(ctNotDefined);
			list<CToken> listLocal;
			listLocal.push_back(ctTag);
			mapUDK[g_TagSub] = listLocal;
			}

#ifndef NDEBUG
		cout << "After expanding include statement "<<m_sFile.c_str()<<endl;
		cout << "Number of Tokens = "<<m_ltTokens.size()<<endl;
		copy(m_ltTokens.begin(),m_ltTokens.end(),out);
		cout << endl << cTokeniser <<endl;
#endif

	}
#ifndef CRASHHARD
	catch(...)
	{
		ERROR_OS << "<Internal Error*> Undefined error reading input file" << endl;ERROR_OS.flush();
		SYMERROR("Undefined error reading input file",errInternal,m_sFile.c_str(),NOT_DEFINED,NOT_DEFINED);
		m_eState=cessUninitated;
		return false;
	}
#endif

	return true;


}



///////////////////////////////////////////////////////////
// Function name	: CSimulation::expandUserDefinedMacros
// Description	    : 
// Return type		: void 
// Argument         : mapUserDefinedKeys& mapUDK
///////////////////////////////////////////////////////////
void CSimulation::expandUserDefinedMacros(mapUserDefinedKeys& mapUDK)
{
	mapUserDefinedKeys::iterator it;
	mapUserDefinedKeys::iterator itEnd = mapUDK.end();
	list< CToken >::iterator itTok;
	list< CToken >::iterator itTokLast = m_ltTokens.begin();
	list< CToken >::iterator itTokStep;
	vector< list< CToken >::iterator > vecToErase;
	vector< list< CToken >::iterator >::iterator itVTE;
	bool bLastTokenNotDefine=true;
	vector<CToken*> vecEmpty;
	vector<CToken*>& rvecTok = vecEmpty;
	vector<CToken*>::iterator itpT;
	CTestHoldTokeniser cht;
	string sNewLine;
	
	for(itTok=m_ltTokens.begin();itTok!=m_ltTokens.end();itTok++)
		{

		// need to check for new line - just in case mistake of just #declare
		if ((!bLastTokenNotDefine)&&(!itTok->sameLine(*itTokLast))) 
			bLastTokenNotDefine=true; // as a new line

#ifdef DEBUGSUBSMACRO
		long iCSubTemp;
		ATLTRACE("Token= %s\n",itTok->getStringRef().c_str());
#endif
		

		if (bLastTokenNotDefine)
			{
			if((itTok->IsOfType(ctUserDefined))||(itTok->IsOfType(ctMacroKeyWord))) // only check those identified - much faster
				{
				it = mapUDK.find(itTok->getString());
				if (it!=itEnd) // ie if found
						{
						list< CToken > ltSubsTokens = it->second; // to prevent alteration to location data
						for(itTokStep=ltSubsTokens.begin();itTokStep!=ltSubsTokens.end();itTokStep++)
								{
								#ifndef NDEBUG
								cout << "Before\t"<<*itTokStep << endl;
								cout << "Ref Loc\t"<<*itTok << endl;
								#endif
								itTokStep->setRelativeLocation(itTok->getLocation(),itTokStep->getLocation(),it->second.begin()->getX());
								#ifndef NDEBUG
								cout << "After\t"<<*itTokStep << endl;
								#endif
								}

						m_ltTokens.insert(itTok,ltSubsTokens.begin(),ltSubsTokens.end());	
	#ifdef DEBUGSUBSMACRO
		list< CToken >::iterator itTokTemp = itTok;
		itTokTemp--;
						for (iCSubTemp=0;iCSubTemp<=it->second.size()+1;iCSubTemp++)
						{
							cout << (*itTokTemp) << "\n";
							itTokTemp++;
						}
						cout <<"Erase token "<< *itTok <<endl;
	#endif
						vecToErase.push_back(itTok);
						}
				}
				else
				{
				if (itTok->getArrayType()==atPartOfArray) // then we can take a look inside - also necessary as it trims the index statements inside brackets
					{
					rvecTok = cht.getRefVectorOfTokenPointers(itTok->getLine(),itTok->getString().getBetweenSqrBrackets().c_str(),"subsMacro");
					sNewLine = "";
					for (itpT=rvecTok.begin();itpT!=rvecTok.end();itpT++)
						{
						if (!(*itpT)->IsOfType(ctDelim))
							{
							it = mapUDK.find((*itpT)->getString());
							if (it!=itEnd) // ie if found
									{
									list< CToken > ltSubsTokens = it->second; // to prevent alteration to location data
									for(itTokStep=it->second.begin();itTokStep!=it->second.end();itTokStep++)
											{
											sNewLine.append(itTokStep->getString());
											}
									}
									else
									sNewLine.append((*itpT)->getString());

							} //if (!(*itpT)->getType(ctDelim))
							else
							sNewLine.append((*itpT)->getString());

						} // end for (itpT=rvecTok.begin()
					#ifdef DEBUGSUBSMACRO
					ATLTRACE("Part array before subs = '%s' length %d\n",itTok->getString().c_str(),itTok->getString().length());
					#endif
					itTok->setString(itTok->getString().getSubsIntoSqrBrackets(sNewLine.c_str()).c_str());
					#ifdef DEBUGSUBSMACRO
					ATLTRACE(" sNewLine = '%s'\n",sNewLine.c_str());
					ATLTRACE("Part array after subs = '%s' length %d\n",itTok->getString().c_str(),itTok->getString().length());
					#endif

					}

				}
			} // end if (bLastTokenNotDefine)
		if ((itTok->IsOfType(ctMacroKeyWord))&&(itTok->getString().compare(g_Define)==0))
			bLastTokenNotDefine=false;
			else
			bLastTokenNotDefine=true;
				
		itTokLast=itTok;
		}

	for(itVTE=vecToErase.begin();itVTE!=vecToErase.end();itVTE++)
			m_ltTokens.erase(*itVTE);

#ifndef NDEBUG
	// designed to check that no user defined toakens get any further than this point. But don't want the over
	// head in the release version
	for(itTok=m_ltTokens.begin();itTok!=m_ltTokens.end();itTok++)
			if (itTok->IsOfType(ctUserDefined))
			{
				cout << "Token still left = " << *itTok <<endl;
//				ATLASSERT(!itTok->IsOfType(ctUserDefined));
			}
#endif

}


///////////////////////////////////////////////////////////
// Function name	: CSimulation::runSimulation
// Description	    : Run the simulation - which has alreaday been set up
// Return type		: bool 
// Argument         : CIDataServicesCallBack* iSCB/*=NULL*/
///////////////////////////////////////////////////////////
bool CSimulation::runSimulation(CIDataServicesCallBack* iSCB/*=NULL*/)
{
	
	bool bResult;
	
	if (m_eState!=cessInitiated)
			return false;

	ASSERT2(m_pSolver);
	if (!m_pSolver)
			return false;

	CSimRun sr(&m_cmModel,m_pSolver);

	if (iSCB)
		bResult = sr.runSimulation(*iSCB);
		else
		{
		CIDataServicesCallBack iDSCB;
		bResult = sr.runSimulation(iDSCB);
		}

	return bResult;
}


///////////////////////////////////////////////////////////
// Function name	: CSimulation::clearSimulation
// Description	    : Prepare empty simulation
// Return type		: void 
///////////////////////////////////////////////////////////
void CSimulation::clearSimulation(bool bButNotRecognisedFileNames/*=false*/)
{
	m_vecLinesofIntrestEq.clear();
	m_vecLinesofIntrestTv.clear();
	m_vecLinesofIntrestEt.clear();
	m_vecLinesofIntrestSl.clear();
	m_vecLinesofIntrestSV.clear();
	m_vecLinesofIntrestAr.clear();
	m_vecLinesofIntrestIn.clear();
	m_vpRemove.clear();

	m_ltTokens.clear();
	if (m_sFile.length()>0)
		m_eState = cessHasFile;
		else
		m_eState = cessUninitated;

	if (!bButNotRecognisedFileNames)
			m_setRecognisedFileNames.clear();

}

//#define DEBUGGENLINES


///////////////////////////////////////////////////////////
// Function name	: CSimulation::GenerateLines
// Description	    : Take the vector of tokens and assign
//                    to a vector of token pointers to lines
//					  of type VectorLineTokenPts.
// Return type		: void 
///////////////////////////////////////////////////////////
void CSimulation::GenerateLines()
{
	ASSERT2(m_eState==cessHasFile);
	if (m_eState!=cessHasFile)// problem in release build
			throw 1;
#ifdef DEBUGGENLINES
	ostream_iterator<CToken> out(cout,"\n"); // see p53 STL book
	ostream_iterator<CToken*> out2(cout,""); // see p53 STL book
#endif
	
	list<CToken>::iterator itTok;
	list<CToken>::iterator itTokLast;
	list<CToken>::iterator itTokEndRemove;
	VectorLineTokenPts::iterator itCurrentLine;
	vector< CToken* > vecLi; // use Li rather than Line to be clear
//	long lLine;
	bool bAppendLine=false;
	bool bFirst=true;

	m_vecLines.clear();
	itCurrentLine = m_vecLines.end();

	// just to make sure - place Tokens in guarenteed order - 
	// as this could change with code modification elsewhere.
//	sort(m_ltTokens.begin(),m_ltTokens.end(),*m_ltTokens.begin());
	m_ltTokens.sort();

	//remove derivatives and extra material between quotes after consolidation
	for(itTok = m_ltTokens.begin();itTok!=m_ltTokens.end();itTok++)
		{
		 // note only bFirst tested first time - else failoure as itTokLast= end()
		 if ((bFirst)||(!itTok->sameLine(*itTokLast))) // this relies on Tokens being *in order*
			 {
			 processifDerivative(itTok); // if this line starts with a derivative - identify it
			 processifContainsNames(itTok); // convert items within quotes to ctName and reduce Token number
			 itTokLast = itTok; // as this is the new line - whilst true keep on looking
			 bFirst=false; // not again in this loop
			 }
		}
	// now to remove items from Token list
	#ifndef NDEBUG
	long iCountBefore = m_ltTokens.size();
	#endif
	vector< list<CToken>::iterator >::reverse_iterator itR;
	for (itR=m_vpRemove.rbegin();itR!=m_vpRemove.rend();itR++)
		{
		#ifndef NDEBUG
		cout << "erase "<<**itR << endl;
		#endif
		m_ltTokens.erase(*itR);
		}
	#ifndef NDEBUG
	cout <<"iCountBefore="<<iCountBefore<<" m_ltTokens.size()="<<m_ltTokens.size()<<" m_vpRemove.size()="<<m_vpRemove.size()<<endl;
	assert(iCountBefore==m_ltTokens.size()+m_vpRemove.size());
	#endif



#ifdef DEBUGGENLINES
	cout << "m_ltTokens.size() = "<<m_ltTokens.size() << endl;
#endif
	bFirst=true;
	for(itTok = m_ltTokens.begin();itTok!=m_ltTokens.end();itTok++)
		{
		 // note only bFirst tested first time - else failoure as itTokLast= end()
		 if ((bFirst)||(!itTok->sameLine(*itTokLast))) // this relies on Tokens being *in order*
			 {
			 if ((itTok->getString().compare(g_Case)==0)||
				 (itTok->getString().compare(g_Default)==0))
					bAppendLine=true;
			 if (!bAppendLine)
				{ 			
				 m_vecLines.push_back(vecLi); // get copied in a blank vector
				 itCurrentLine = m_vecLines.end();
				 itCurrentLine--; // so be have a pointer to the new vector
				}
			 bAppendLine=false;
			 itTokLast=itTok; // to compare next time
			 bFirst=false;
			 if ((itTok->getString().compare(g_Switch)==0)||
			     (itTok->getString().compare(g_Case)==0)||
				 (itTok->getString().compare(g_Default)==0))
					bAppendLine=true;
			 }
		 	
		 ASSERT2(itCurrentLine!=m_vecLines.end());

		 itCurrentLine->push_back(&(*itTok)); // the token goes to this line

		}


#ifdef DEBUGGENLINES
		cout << "void CSimulation::GenerateLines()"<<endl;
		copy(m_ltTokens.begin(),m_ltTokens.end(),out);
		for(itCurrentLine=m_vecLines.begin();itCurrentLine!=m_vecLines.end();itCurrentLine++)
			{
			for(vector< CToken* >::iterator iT=itCurrentLine->begin();iT!=itCurrentLine->end();iT++)
				cout << (*iT)->getString();
			cout <<endl;
			}
#endif
	// if everthing has worked to here then
	m_eState=cessHasLines;

}




///////////////////////////////////////////////////////////
// Function name	: CSimulation::GenerateStructure (formally GenerateEquations )
// Description	    : Create indexes of tokens by line for
//                    Equations, Solver and Events
// Return type		: void 
///////////////////////////////////////////////////////////
void CSimulation::GenerateStructure()
{
	int iCountEq, iCountAt;
	bool bComment,bKeyFound;
	VectorLineTokenPts::iterator itLines;
	vector< CToken* >::iterator itpCT;

	assert(m_eState==cessHasLines);
	m_vecLinesofIntrestEq.clear(); // just in case
	m_vecLinesofIntrestTv.clear();
	m_vecLinesofIntrestSV.clear(); 
	m_vecLinesofIntrestEt.clear();
	m_vecLinesofIntrestSl.clear();
	m_vecLinesofIntrestAr.clear();
	m_vecLinesofIntrestIn.clear();
	
	for(itLines=m_vecLines.begin();itLines!=m_vecLines.end();itLines++)
		{
		bKeyFound = false;
		bComment = false;

		#ifndef NDEBUG
		cout << __FILE__ <<" : "<<__LINE__<<"\n";
		cout << "Line "<<(*itLines)[0]->getLine()<<" = "<<(*(*itLines)[0])<<endl;
		#endif

		// keywords only at start to define event or solver line
		if (itLines->size()>0) // make sure line has tokens
			{
					switch((*itLines)[0]->getType())
					{
					case ctEventKeyWord:
						bKeyFound=true;
						m_vecLinesofIntrestEt.push_back(*itLines);
						if ((*itLines)[0]->getString().compare(g_Sequence)==0)
								m_vecLinesofIntrestSl.push_back(*itLines); // also - as it is required to fire up a solver also
								else
								if ((*itLines)[0]->getString().compare(g_Once)==0)
									m_vecLinesofIntrestSl.push_back(*itLines); // also - as it is required to fire up a solver also
						break;
					case ctSolverKeyWord:
						bKeyFound=true;
						m_vecLinesofIntrestSl.push_back(*itLines);
						break;
					case ctEquationKeyWord:
						bKeyFound=true;
						m_vecLinesofIntrestEq.push_back(*itLines);
						break;
					case ctTypeModifier:
						bKeyFound=true;
						m_vecLinesofIntrestTv.push_back(*itLines);
						break;
					case ctMacroKeyWord:
						if (((*itLines)[0]->getString().compare(g_Index)==0)||((*itLines)[0]->getString().compare(g_Expand)==0))
							{
							bKeyFound=true;
							m_vecLinesofIntrestIn.push_back(*itLines);
							}
							else
							{
							setLineToComment(itLines);
							bComment=true;
							}
						break;
					case ctArrayKeyWord:
						bKeyFound=true;
						m_vecLinesofIntrestAr.push_back(*itLines);
						break;
					default:
						// do nothing
						break;
					}
			}

		
		if (!bComment)
			{
			if (bKeyFound)
						{
						CTokeniser::assignVariables(*itLines); // call to static function
		/*				CToken* pctLast = NULL;
						bComment=false;
						for(itpCT=itLines->begin();itpCT!=itLines->end();itpCT++)
							{
								if ((pctLast)&&(!(*itpCT)->sameLine(*pctLast))) // so comments reset for each 'sub-line'
												bComment=false;

								if ((!bComment)&&((*itpCT)->getString().compare(g_Comment)==0))// is it an //
												bComment=true; // so ignore the rest of the line
								if (bComment)
									(*itpCT)->setType(ctComment);
									// not changing ctNotDefined here - as not all items will be variables
								switch((*itLines)[0]->getType())
								{
								case ctEquationKeyWord:
									if ((*itpCT)->getType()==ctNotDefined)
												(*itpCT)->setType(ctVariable);
									break;
								case ctArrayKeyWord:
									if ((*itpCT)->getType()==ctNotDefined)
												(*itpCT)->setType(ctVariable);
									break;
								default:
									// do nothing
									break;
								}

								pctLast = (*itpCT); // to check line changes

							}	*/				

						}
				else // (bKeyFound)
						{ // if not an event or a solver instruction
						iCountAt = iCountEq = 0;
						bComment=false;
						for(itpCT=itLines->begin();itpCT!=itLines->end();itpCT++)
							{
							if ((!bComment)&&((*itpCT)->getString().compare(g_Eq)==0))// is it an =
								iCountEq++;
								else
									if ((!bComment)&&((*itpCT)->getString().compare(g_At)==0))// is it an @
										iCountAt++;
										else
										if ((!bComment)&&((*itpCT)->getString().compare(g_Comment)==0))// is it an //
											bComment=true; // so ignore the result of the line
							if (bComment)
								(*itpCT)->setType(ctComment);
								else
								if ((*itpCT)->getType()==ctNotDefined)
									(*itpCT)->setType(ctVariable);
							}

						if ((iCountEq==2)&&(iCountAt==1)) // then a properly consituted value equation may exist - need to improve the detection here
								m_vecLinesofIntrestSV.push_back(*itLines);
								else
								if (iCountEq==1)
										m_vecLinesofIntrestEq.push_back(*itLines); // then a normal equation may exist
										else
											setLineToComment(itLines); // set types on this line
						} // else (bFound)
			}
	} // (bComment)


	// no longer needed
	m_vecLines.clear();

}


///////////////////////////////////////////////////////////
// Function name	: CSimulation::setLineToComment
// Description	    : Set all Tokens in this line to comment - over ride deliminator assignments
// Return type		: void 
// Argument         : VectorLineTokenPts::iterator itLine
///////////////////////////////////////////////////////////
void CSimulation::setLineToComment(VectorLineTokenPts::iterator itLine)
{
	vector< CToken* >::iterator itpCT;
	
	for(itpCT=itLine->begin();itpCT!=itLine->end();itpCT++)
		(*itpCT)->setType(ctComment);

}



///////////////////////////////////////////////////////////
// Function name	: CSimulation::unifyEquationTokens
// Description	    : 
// Return type		: void 
///////////////////////////////////////////////////////////
void CSimulation::unifyEquationTokens()
{
	VectorLineTokenPts::iterator it;
	ListLineTokenPts::iterator itList;
	vector< CToken* >::iterator itpCT;
	SetPtCTokenStringSearch::iterator itSet;

	m_setPtUniqueTokens.clear();

	// first combine any relevant derivatives into one Token and assign to type derivative
	//	Then need to reset checking to cover this.... ie derivatives know by their checking here.
	//	Will need to assign a derivative to a variable - will be needed when check problem is square.

	// first for the equations
	for (itList=m_vecLinesofIntrestEq.begin();itList!=m_vecLinesofIntrestEq.end();itList++)
		{
		 for(itpCT=itList->begin();itpCT!=itList->end();itpCT++)
			 {
				if ((*itpCT)->IsOfTypeVariable())
					{
						itSet = m_setPtUniqueTokens.find(*itpCT); // which will be used to assign parent
						if (itSet==m_setPtUniqueTokens.end())
								m_setPtUniqueTokens.insert(*itpCT);
						else
								(*itpCT)->AssignParent(*itSet);
					}
			 }
			 // check for derivative variables - and add to set - but only after real variables had all been checked
		 for(itpCT=itList->begin();itpCT!=itList->end();itpCT++)
			 {
			 if ((*itpCT)->IsOfType(ctDerivative))
					{
						_ND cout << "== found derivative ==> "<<(*itpCT)->getStringRef().c_str()<<endl;
						CToken ctog((*itpCT)->getVariableFromDerivative((*itpCT)->getString()),ctVariable,m_itNoFileName);
						itSet = m_setPtUniqueTokens.find(&ctog);
						if (itSet==m_setPtUniqueTokens.end())
							{
							m_ltTokens.push_back(ctog);
							list<CToken>::iterator itDVec = --m_ltTokens.end();
							ASSERT2(itDVec==find(m_ltTokens.begin(),m_ltTokens.end(),ctog));
							m_setPtUniqueTokens.insert(&(*itDVec));
							_ND cout << "Created variable "<< (*itDVec)<<endl;
							(*itpCT)->setDervivativeVariable((*itDVec));
							}
							else
							(*itpCT)->setDervivativeVariable((**itSet));
					}
					if ((*itpCT)->IsIterative())
						{
						_ND cout << "== found iterative ==> "<<(*itpCT)->getStringRef().c_str()<<endl;
						CToken ctog((*itpCT)->getString().getLessIterative(),ctVariable,m_itNoFileName);
						itSet = m_setPtUniqueTokens.find(&ctog);
						if (itSet==m_setPtUniqueTokens.end())
							{
							m_ltTokens.push_back(ctog);
							list<CToken>::iterator itDVec = --m_ltTokens.end();
							ASSERT2(itDVec==find(m_ltTokens.begin(),m_ltTokens.end(),ctog));
							m_setPtUniqueTokens.insert(&(*itDVec));
							_ND cout << "Created iterative linked variable "<< (*itDVec)<<endl;
							(*itpCT)->setIterativeVariable((*itDVec));
							}
							else
							(*itpCT)->setIterativeVariable((**itSet));

						}
					

			 }
		}

	//Also need to add time as a Token if it doesn't exist - perhaps it shouldn't exist
	CToken ctTime(g_Time,ctVariable,m_itNoFileName);
	if (m_setPtUniqueTokens.find(&ctTime)==m_setPtUniqueTokens.end())
				{	
				m_ltTokens.push_back(ctTime);
				list<CToken>::iterator itLast = m_ltTokens.end();
				itLast--;
				ASSERT2((*itLast)==ctTime);
				m_setPtUniqueTokens.insert(&(*itLast));
				}
//	#ifndef NDEBUG
//				else
//				ASSERT2(false); // bring attention to this failure
//	#endif

	// And now for the Statements of value
	for (it=m_vecLinesofIntrestSV.begin();it!=m_vecLinesofIntrestSV.end();it++)
		{
		 for(itpCT=it->begin();itpCT!=it->end();itpCT++)
			 {
				if ((*itpCT)->IsOfType(ctVariable))
					{
						itSet = m_setPtUniqueTokens.find(*itpCT); // which will be used to assign parent
						if (itSet==m_setPtUniqueTokens.end())
								m_setPtUniqueTokens.insert(*itpCT);
						else
								(*itpCT)->AssignParent(*itSet);
					}
								

			 }
		}

	
}

#ifndef NDEBUG
//#define DEBUGVECTOR
#endif

///////////////////////////////////////////////////////////
// Function name	: CSimulation::checkModel
// Description	    : Ensure model is ready to solve
// Return type		: bool 
// Argument         : ostream& osErrReport
///////////////////////////////////////////////////////////
bool CSimulation::checkModel(ostream& osErrReport )
{
	bool bResult = true; // by default all will be OK
	vector<CToken* > vecIndVar(m_setPtUniqueTokens.size()); // to defined all independant variables defined by Equation
	CEventFactory* pEvF = CEventFactory::instance();

#ifdef DEBUGVECTOR
	ofstream o1;
	o1.open("c:\\temp\\debugvector.txt");

	o1 << "m_setPtUniqueTokens.size() = " << m_setPtUniqueTokens.size() <<endl;
#endif
	{ // temp scope limt for bug hunting


	//SetPtCToken setIndVar; // to defined all independant variables defined by Equation
	//SetPtCToken setDepVar; // to defined all dependant variables defined by Equation
	SetPtCToken setVar; // to defined all variables defined by Equation
	vector<CToken* > vecDeriv(m_setPtUniqueTokens.size()); // to defined all variables defined by Equation
	vector<CToken* > vecVar(m_setPtUniqueTokens.size()); // to defined all dependant variables defined by Equation
	vector<CToken* > vecVarAdded; // to defined all dependant variables defined by Equation
	vector<CToken* > vecDepVar(m_setPtUniqueTokens.size()); // to defined all dependant variables defined by Equation
	vector<CToken* > vecSubsVar(m_setPtUniqueTokens.size()); // to defined all substitable variables defined by Equations
															 // these are variables defined by equations - hence results can
															 // be substituted rather than being reclaulated every time the variablre is encountered.
	vector<CToken* > vecImpliedToCheck;
//	vector<CToken* > vecVar; // to defined all dependant variables defined by Equation
	vector<CToken* >::iterator itv;

//  run body of unit tests if in debug mode
#ifndef NDEBUG
#ifdef UNITTESTS
	ATLTRACE(_T("Unit Test start\n"));
	{
//	bool bUnitTest = true;
	CErrorFactory* pef = CErrorFactory::instance();
	ASSERT2(pef);
	if (pef->numberOfCurrentErrors()==0) // as this process will wipe out any error records - if errors already exists the developer should deal with them first
		{
		CArrayFactory* paf = CArrayFactory::instance();

		bResult = paf->unitTests(m_pIARDataStore);
		if (!bResult)
			ATLTRACE(_T("FAILED Array unit tests\n"));


		CIndexFactory* pind = CIndexFactory::instance();

		if (!pind->unitTests(m_pIARDataStore))
			{
			ATLTRACE(_T("FAILED Index unit tests\n"));
			bResult = false;
			}


		if (bResult)
			pef->clearErrors(); // as some errors are generated by passing unit tests - so can carry on
		}

	// however simulation will fail if unit tests are run and fail
	bResult &= CStringPlus::runUnitTests();
	

	}
	ATLTRACE(_T("Unit Test end\n"));
#else
	ATLTRACE(_T("Unit Tests not run\n"));
#endif
#endif


	if (checkArrays(osErrReport)&&(bResult))
				bResult = makeArrays(osErrReport);
				else
				bResult = false;

#ifndef NDEBUG
	CArrayFactory::instance()->writeArrays(cout);

#ifdef DEBUGVECTOR
	o1 << "List of Arrays\n==============\n";
	CArrayFactory::instance()->writeArrays(o1);
	o1 << endl;
#endif
#endif

//	think about if should carry on if errors found by this stage


	if ((checkEquations(osErrReport))&&(bResult))
				bResult = makeEquations(osErrReport); // as something may yet go wrong
				else
				bResult = false;

#ifndef NDEBUG
	CArrayFactory::instance()->writeArrays(cout);
#endif

	if (bResult)
		bResult = expandArrays(osErrReport);

#ifndef NDEBUG
	cout <<"===Start===\n";
	for (list<CToken>::const_iterator ivct=m_ltTokens.begin();ivct!=m_ltTokens.end();ivct++)
				cout << *ivct <<endl;
	cout <<"===End===\n";
	for (SetPtCTokenStringSearch::const_iterator spct=m_setPtUniqueTokens.begin();spct!=m_setPtUniqueTokens.end();spct++)
				cout << **spct << endl;
	cout <<"===End unique list===\n";
#endif

	if ((checkValues(osErrReport))&&(bResult))
				bResult = makeValues(osErrReport);
				else
				bResult = false;

	if ((bResult)&&(checkEvents(osErrReport)))
				bResult = makeEvents(osErrReport);
				else
				bResult = false;

	if ((bResult)&&(checkSolver(osErrReport)))
				bResult = makeSolverChoices(osErrReport);
				else
				bResult = false;

	if ((checkTypes(osErrReport))&&(bResult))
				bResult = makeTypes(osErrReport);
				else
				bResult = false;

	if (!bResult) // then go no further
			return bResult;

	// assign dependant and independant variables
	list<CEquation*>::iterator itEq;
	SetPtCTokenStringSearch::iterator itSet;
	SetPtCToken setLHS; // to defined all variables defined by Equation LHS's

	for(itEq=m_vpEquations.begin();itEq!=m_vpEquations.end();itEq++)
		{
		CToken ctTag((*itEq)->getUnderlyingLHSVarString().c_str(),ctVariable,m_itNoFileName);
		_ND osErrReport << ctTag.getString().c_str() <<" "<<(*itEq)->getLHS()->getString().c_str()<<endl;

		itSet = m_setPtUniqueTokens.find(&ctTag);
		if (itSet==m_setPtUniqueTokens.end()) // then this token is missing
				{
				list<CToken>::iterator itCT;
				// Need to add handling for missing Token - how to add to existing arrays ??
				// Think about if it needs to be anywhere other than push_back on vector
				// of CTokens.
				
				// As unable to find token need to add one in
				_ND osErrReport << "Token "<<ctTag.getString().c_str()<<" is missing\n";osErrReport.flush();
				_ND osErrReport << "Before "<<(*m_ltTokens.begin())<<endl;
				m_ltTokens.push_back(ctTag);
				itCT = find(m_ltTokens.begin(),m_ltTokens.end(),ctTag);
				_ND osErrReport << "After "<<(*m_ltTokens.begin())<<endl;
				ASSERT2((*itCT)==ctTag); // which assuming find found - which it should - will work
				ASSERT2(m_setPtUniqueTokens.find(&(*itCT))==m_setPtUniqueTokens.end());
				m_setPtUniqueTokens.insert(&(*itCT));
				itSet = m_setPtUniqueTokens.find(&ctTag);
				ASSERT2(itSet!=m_setPtUniqueTokens.end()); // ensure the token has been added
				}

		if (setLHS.find((*itEq)->getLHS())!=setLHS.end())
				{
				bResult = false;
				osErrReport << "<Error*> Duplicate of LHS Variable :\n";
				osErrReport << "\t"<<(**(setLHS.find((*itEq)->getLHS()))) << ".\n";
				SYMERRORTOK("Duplicate of LHS Variable",errSyntax,(*itEq)->getLHS());
				}
				else
				setLHS.insert((*itEq)->getLHS()->getRootTokenPt());


		/* If the LHS is a derivative then need to check the variable that the derivative is part of
		   has not also been declared at a LHS variable.
		*/
		if ((*itEq)->getLHS()->IsOfType(ctDerivative))
				{
				(*itEq)->getLHS()->setDervivativeVariable(**itSet);

				// add the variable 
				if (setLHS.find(*itSet)!=setLHS.end())
						{
						bResult = false;
						osErrReport << "<Error*> Duplicate of LHS Variable with derivative :\n";
						osErrReport << "\t"<<(**(setLHS.find(*itSet))) << " and\n";
						osErrReport << "\t"<<(**itSet)<<endl;
						SYMERRORTOK("Duplicate of LHS Variable with derivative",errSyntax,(*itSet));
						}
					//	else
					//	setLHS.insert(*itSet);
						else
						vecVarAdded.push_back(*itSet);

				}

		}

	/* Confirm that each derivative has an equivalent variable in the variable type set */
	for (itSet=m_setPtUniqueTokens.begin();itSet!=m_setPtUniqueTokens.end();itSet++)
		{
		CToken* temp_pct=NULL;
		if ((*itSet)->IsOfType(ctDerivative))
			{
			if (!(*itSet)->getUnderlyingVariable(&temp_pct))
				{
				bResult=false;
				osErrReport << "<Error*> Derivative is not defined " << (**itSet) <<endl;
				SYMERRORTOK("Derivative underlying variable is not defined",errSyntax,(*itSet));
				}
				else
				{
				#ifndef NDEBUG
				ATLTRACE("Looking at %s\n",(*itSet)->getString().c_str());
				cout << (**itSet) <<endl;
				ATLTRACE("temp_pct = %d ",temp_pct);
				if (temp_pct)
					ATLTRACE(" %s\n",temp_pct->getString().c_str());
					else
					ATLTRACE("\n");
				#endif
				vecImpliedToCheck.push_back(temp_pct); // so it can be checked later
				}
			}

		}

	if (!bResult) // then go no further as LHS of equations didn't match
			return bResult;

	// Add any iteration events that are implied in equations - if any
	for(itEq=m_vpEquations.begin();itEq!=m_vpEquations.end();itEq++)
		{
		#ifndef NDEBUG
		cout << (**itEq) << endl;
		#endif
		if ((*itEq)->lhsIsIterative())
			{
			CEvItValueStep* pevItVS = newtrack CEvItValueStep( (*itEq)->getLHS() );

			if (!pevItVS)
					{
					SYMERRORLITE("Out of memory",errSystem);
					}
					else
					{
					pevItVS->findRHSvalue(m_setPtUniqueTokens);

					if (pevItVS->isInError())
							{
							SYMERRORTOK("Problem setting up iterative equation",errInternal,(*itEq)->getLHS());
							delete pevItVS;
							}
							else
							{
							pEvF->manageEvent(pevItVS);
							m_vpEvents.push_back(pevItVS);
							}
					}

			}
		}

	cascadeTokenTypes(); // just in case anything is out of sync.

#ifndef NDEBUG
	ostream_iterator<CToken*> out(cout,"\t"); // see p53 STL book

	ostream_iterator<CToken> out2(cout,"\n"); // see p53 STL book
	copy(m_ltTokens.begin(),m_ltTokens.end(),out2);
#ifdef DEBUGVECTOR
	o1 << "tokens\n";
	ostream_iterator<CToken*> out3(o1,"\n"); // see p53 STL book
	ostream_iterator<CToken*> out4(o1,"\t"); // see p53 STL book
	ostream_iterator<CToken> out5(o1,"\t"); // see p53 STL book
	copy(m_ltTokens.begin(),m_ltTokens.end(),out5);
	o1 << endl;
#endif

#endif	

	_ND osErrReport <<"Var size before "<<setVar.size()<<endl;
	for (itSet=m_setPtUniqueTokens.begin();itSet!=m_setPtUniqueTokens.end();itSet++)
		{
		if ((*itSet)->IsOfTypeVariable())
			setVar.insert(*itSet);
		}
	_ND osErrReport <<"Var size after "<<setVar.size()<<endl;
#ifdef DEBUGVECTOR
	SetPtCToken::iterator itD;
	vector<CToken* >::iterator itVD;
	o1 << "setVar\n======\n";
	copy(setVar.begin(),setVar.end(),out3);
	o1 << "\n";
	for (itD=setVar.begin();itD!=setVar.end();itD++)
		o1 << (*itD)->getString().c_str() <<"\t";
	o1 << endl;
	o1 << "setLHS\n======\n";
	copy(setLHS.begin(),setLHS.end(),out3);
	o1 << "\n";
	for (itD=setLHS.begin();itD!=setLHS.end();itD++)
		o1 << (*itD)->getString().c_str() <<"\t";
	o1 << endl;

#endif

	vecDeriv.resize(setVar.size()); // to defined all variables defined by Equation
	vecVar.resize(setVar.size()); // to defined all dependant variables defined by Equation
	vecDepVar.resize(setVar.size()); // to defined all dependant variables defined by Equation
	vecSubsVar.resize(setVar.size()); // to defined all substitable variables defined by Equations
	vecIndVar.resize(setVar.size());

	itv = set_intersection(setVar.begin(),setVar.end(),setLHS.begin(),setLHS.end(),vecVar.begin());
#ifdef DEBUGVECTOR
	o1 << "itv = " << itv << endl;
	o1 << "itv* = " << (*itv)<< endl;
	o1 << "*vecVar.end() = " << (*vecVar.end()) << endl;
	o1 << "vecVar size = " << vecVar.size() << endl;
	copy(vecVar.begin(),vecVar.end(),out3);
	o1 << endl;
	for (itVD=vecVar.begin();((itVD!=itv)&&(itVD!=vecVar.end()));itVD++)
		o1 << (*itVD)->getString().c_str() <<"\t";
	o1 << endl;
	o1.close();
#endif
	vecVar.erase(itv,vecVar.end()); // need to do this to stop try to use unassigned addresses
	vecVar.insert(vecVar.begin(),vecVarAdded.begin(),vecVarAdded.end());

	sort(vecVar.begin(),vecVar.end()); // needed to ensure set_difference works OK
	itv = set_difference(setVar.begin(),setVar.end(),vecVar.begin(),vecVar.end(),vecIndVar.begin());
	vecIndVar.erase(itv,vecIndVar.end()); // need to do this to stop try to use unassigned addresses

	itv = set_difference(setLHS.begin(),setLHS.end(),setVar.begin(),setVar.end(),vecDeriv.begin());
	vecDeriv.erase(itv,vecDeriv.end()); // need to do this to stop try to use unassigned addresses
	sort(vecDeriv.begin(),vecDeriv.end(),CSortTokenPointers());// need to keep DepVar in same order as Deriv

	sort(vecVar.begin(),vecVar.end()); // needed to ensure set_difference works OK
	itv = set_intersection(setLHS.begin(),setLHS.end(),vecVar.begin(),vecVar.end(),vecSubsVar.begin());
	vecSubsVar.erase(itv,vecSubsVar.end());

	// these two may not be necessary as vectors should be sorted - check later
	sort(vecSubsVar.begin(),vecSubsVar.end());
	sort(vecVar.begin(),vecVar.end());
	// end of section that may not be necssary
	itv = set_difference(vecVar.begin(),vecVar.end(),vecSubsVar.begin(),vecSubsVar.end(),vecDepVar.begin());
	vecDepVar.erase(itv,vecDepVar.end());
	sort(vecDepVar.begin(),vecDepVar.end(),CSortTokenPointers()); // need to keep DepVar in same order as Deriv

#ifndef NDEBUG
	osErrReport << "setVar"<<endl;
	copySetpttoStream(setVar,osErrReport);
	osErrReport << "vecDeriv"<<endl;
	copySetpttoStream(vecDeriv,osErrReport);
	osErrReport << "vecVar"<< endl;
	copySetpttoStream(vecVar,osErrReport);
	osErrReport << "vecIndVar"<< endl;
	copySetpttoStream(vecIndVar,osErrReport);
	osErrReport << "vecSubsVar"<< endl;
	copySetpttoStream(vecSubsVar,osErrReport);
	osErrReport << "vecDepVar"<< endl;
	copySetpttoStream(vecDepVar,osErrReport);
//	for (itv=vecDepVar.begin();itv!=vecDepVar.end();itv++)
//			osErrReport <<(*itv)<<" ";
//	osErrReport << endl;
	osErrReport << "setLHS"<< endl;
	copySetpttoStream(setLHS,osErrReport);

	ASSERT2(vecVar.size()==vecDepVar.size()+vecSubsVar.size());
#endif

	assignTokenTypes(vecDepVar,ctDepVariable);
	assignTokenTypes(vecIndVar,ctIndVariable);
	assignTokenTypes(vecSubsVar,ctSubsVariable);

	// time to assign index numbers
	m_cmModel.intialiseTokens(vecIndVar,vecDeriv,vecDepVar,vecSubsVar,CStrongTypeFactory::instance());


	#ifndef NDEBUG
	SetPtCToken::iterator its;
	for(itv=vecDeriv.begin();itv!=vecDeriv.end();itv++)
			osErrReport << (**itv) << "\t";

	for(its=setVar.begin();its!=setVar.end();its++)
			osErrReport << (**its) << "\t";
	osErrReport << endl;osErrReport.flush();
	#endif


	set<CToken* > setDefinedAtStart; // this set will gradually have added all the Tokens that have been defined.
//	set<CToken* >::iterator itSet;
	vector<CEvent*>::iterator itEv;

    // tsStart may have been assigned by an event - eg a CEvStart - check
	time_secs tsStart = START_SIMULATION; // default value - more specific info may be in input file
	for(itEv=m_vpEvents.begin();itEv!=m_vpEvents.end();itEv++)
		{
		if ((*itEv)->isOfType(ceetValueChangeStart))
					{
						if ((*itEv)->affectsStartTime())
							{
							tsStart = (*itEv)->giveStartTime();
							ASSERT2(tsStart!=(variable)NOT_DEFINED); // as this should have been caught bt affectsStartTime
							if (tsStart==(variable)NOT_DEFINED)
								tsStart=START_SIMULATION;
							}
					}
		}


	time_secs tsInitialStep = 1E-05;
	// for each value setting event which occurs at START_SIMULATION add to set
	CToken* pCTDefAtStartByEvent;

	for(itEv=m_vpEvents.begin();itEv!=m_vpEvents.end();itEv++)
		{
//		check type then if applies at value time.... then find out which variable is adjusted.
		pCTDefAtStartByEvent=NULL;
		if ((*itEv)->fixedAtStart())
			if (((*itEv)->isOfType(ceetValueChange))&&((*itEv)->willTriggerAtTime(tsStart)))
				{
				 ASSERT2((*itEv)->canChange()!=NULL); // only happen if action equation has not been iniated
				 pCTDefAtStartByEvent = (*itEv)->canChange()->getRootTokenPt();
				 //setDefinedAtStart.insert((*itEv)->canChange()->getRootTokenPt()); // must only deal in root tokens
				}
				else
				if (((*itEv)->isOfType(ceetValueChangeStart))&&((*itEv)->willTriggerAtTime(tsStart))) // the will trigger expression picks up on internal error
					{
					 ASSERT2((*itEv)->canChange()!=NULL); // only happen if action equation has not been iniated
					 pCTDefAtStartByEvent = (*itEv)->canChange()->getRootTokenPt();
					 //setDefinedAtStart.insert((*itEv)->canChange()->getRootTokenPt()); // must only deal in root tokens
					}
					else
					if (((*itEv)->isOfType(ceetValueChangeOnce))&&((*itEv)->willTriggerAtTime(tsStart))) // the will trigger expression picks up on internal error
						{
						 ASSERT2((*itEv)->canChange()!=NULL); // only happen if action equation has not been iniated
						 pCTDefAtStartByEvent = (*itEv)->canChange()->getRootTokenPt();
						 //setDefinedAtStart.insert((*itEv)->canChange()->getRootTokenPt()); // must only deal in root tokens
						}

		if (pCTDefAtStartByEvent)
			{
			if ((pCTDefAtStartByEvent->IsOfType(ctDepVariable))||(pCTDefAtStartByEvent->IsOfType(ctIndVariable)))
					setDefinedAtStart.insert(pCTDefAtStartByEvent);
					else
					{
					if (pCTDefAtStartByEvent->IsOfType(ctSubsVariable))
						{
						osErrReport << "<Error*> This variable cannot also be intialised "<<pCTDefAtStartByEvent->getStringRef().c_str() <<" not allowed. Only dependant variables can be initialised by events."<<endl;
						SYMERRORTOK("Variable cannot be intialised and determined by an equation",errSyntax,pCTDefAtStartByEvent);
						}
						else
						{
						osErrReport << "<Error*> Inialisation of "<<pCTDefAtStartByEvent->getStringRef().c_str() <<" not allowed. Only dependant variables can be initialised by events."<<endl;
						SYMERRORTOK("Variable cannot be initialised by an event",errSyntax,pCTDefAtStartByEvent);
						}
					bResult=false;
					}
			}

		}


	if (!bResult) // then go no further as fatal error in events setup
			return bResult;

#ifndef NDEBUG
	osErrReport << "Set of defined at start variables\n";
	copySetpttoStream(setDefinedAtStart,osErrReport);

#endif

	// run though each equation in order and insure all the RHS variables are known at time of exectution
	// therefore LHS variables are added only as each line is passed.
	// Need to check for simple equations that set variables 
	for(itEq=m_vpEquations.begin();itEq!=m_vpEquations.end();itEq++)
		{
		 _ND osErrReport <<(**itEq) <<endl;osErrReport.flush(); // check equation order to console
		 
		 (*itEq)->sentToAtlTrace();

		 if (!(*itEq)->checkAllRHSDefined(setDefinedAtStart))
			{
			SYMERRORTOK("Not all variables defined when equation presented",errSyntax,(*itEq)->getLHS());
			osErrReport << "<Error*> Not all variables defined when equation presented, see " << (**itEq) <<endl;
			osErrReport << "        where ";
			(*itEq)->checkAllRHSDefined(setDefinedAtStart,true,osErrReport);
			osErrReport << endl;
			bResult = false;
			}

        // possibly all RHS here should now be defined - regardless of if a fixed
		// expression - hence commenting out lines at end and adding LHS to setDefinedAtStart
		// every time
		setDefinedAtStart.insert((*itEq)->getLHS()->getRootTokenPt());
		/*	
		// need to add LHS to setDefinedAtStart list
		if (itEq->isAFixedExpression())// then its the same as an always firing event in terms of considering the model at start up
			setDefinedAtStart.insert(itEq->getLHS()->getRootTokenPt());
		*/
		}

// check any implied variables that may not have been defined
	for (itv=vecImpliedToCheck.begin();itv!=vecImpliedToCheck.end();itv++)
		{
			ATLTRACE("vecImpliedToCheck size = %d vecDeriv.size() %d\n",vecImpliedToCheck.size(),vecDeriv.size());
			ATLTRACE("itv =%d itv* = %d\n",itv,*itv);
			if (setDefinedAtStart.find(*itv)==setDefinedAtStart.end())
				{
				SYMERRORTOK("An implied variable is undefined at the start.",errSyntax,*itv);
				osErrReport << "<Error*>  implied variable is undefined at the start."<< (*itv)->getString().c_str() <<endl;
				bResult = false;
				}
		}


#ifndef NDEBUG
	osErrReport <<"++setDefinedAtStart "<<setDefinedAtStart.size()<<" : ";
	copy(setDefinedAtStart.begin(),setDefinedAtStart.end(),out);
	osErrReport <<"\n--End setDefinedAtStart"<<endl;
#endif
		
	if (bResult) // finish intialising the model for equations and events
		{
		bResult = m_cmModel.intialiseEquations(&m_vpEquations);
		if (bResult)
			bResult = m_cmModel.intialiseEvents(&m_vpEvents,&m_vpEquations);
		}



	#ifndef NDEBUG
	if (bResult)
		osErrReport << "** m_eState=cessInitiated **\n";
	#endif

	if (bResult)
				{
				long iIndVar = vecIndVar.size();
				long iDeriv = vecDeriv.size();
				long iDepVar = vecDepVar.size();
				long iSubsVar = vecSubsVar.size();
				long iTotal = iIndVar+iDeriv+iDepVar+iSubsVar;

				vector<CToken*>::iterator itvOVR;
				m_vecOrderedVarTokens.resize(iTotal,NULL);
				itvOVR = std::copy(vecIndVar.begin(),vecIndVar.end(),m_vecOrderedVarTokens.begin());
				iTotal -= iIndVar;
				ASSERT2((iTotal==0)||(*itvOVR==NULL));
				itvOVR = std::copy(vecDeriv.begin(),vecDeriv.end(),itvOVR);
				iTotal -= iDeriv;
				ASSERT2((iTotal==0)||(*itvOVR==NULL));
				itvOVR = std::copy(vecDepVar.begin(),vecDepVar.end(),itvOVR);
				iTotal -= iDepVar;
				ASSERT2((iTotal==0)||(*itvOVR==NULL));
				itvOVR = std::copy(vecSubsVar.begin(),vecSubsVar.end(),itvOVR);
				iTotal -= iSubsVar;
				ASSERT2((iTotal==0)||(itvOVR==m_vecOrderedVarTokens.end()));
				#ifndef NDEBUG
				copy(vecIndVar.begin(),vecIndVar.end(),out);
				copy(vecDeriv.begin(),vecDeriv.end(),out);
				copy(vecDepVar.begin(),vecDepVar.end(),out);
				copy(vecSubsVar.begin(),vecSubsVar.end(),out);
				cout << endl;

				copy(m_vecOrderedVarTokens.begin(),m_vecOrderedVarTokens.end(),out);
				cout <<endl;
				for(itvOVR=m_vecOrderedVarTokens.begin();itvOVR!=m_vecOrderedVarTokens.end();itvOVR++)
					cout << (*itvOVR)->getRootTokenPt()->getIndex() <<" ";
				cout << endl;
				
				cout<<"End dump.\n";cout.flush();


				#endif
				m_eState=cessInitiated;
				}


#ifndef NDEBUG

	if (bResult) // otherwise possible to fail as Event setups may not have happened
		{
		cout << "Start development tests\n";
		m_cmModel.TestModel(&m_vpEquations,&m_vpEvents);
		cout << "Start basic solver tests\n";
		CSolClassFactory* pscf;
		CSolver* psol;
		pscf = CSolClassFactory::instance();
		ASSERT2(pscf);
		ASSERT2(!pscf->createSolver("Woof"));
		psol = pscf->createSolver("RK4");
		ASSERT2(psol);
		psol->setup(&m_cmModel);
		psol->setIndVarStep(1E-5);
		cout << "End tempory tests"<<endl;
	//	copy(vecV.begin(),vecV.end(),out); cout << endl;
	// WHERE should the variables go - in the model ??
	// also need to think about events a reporting
		}
#endif
	/*
		Need to set variables as dependant or independant
		CheckModelSquare



	*/

ATLTRACE(_T("&vecDeriv %x\n"),&vecDeriv);
ATLTRACE(_T("&vecVar %x\n"),&vecVar);
ATLTRACE(_T("&vecVarAdded %x\n"),&vecVarAdded);
ATLTRACE(_T("&vecIndVar %x\n"),&vecIndVar);
ATLTRACE(_T("&vecDepVar %x\n"),&vecDepVar);
ATLTRACE(_T("&vecSubsVar %x\n"),&vecSubsVar);
ATLTRACE(_T("&vecImpliedToCheck %x\n"),&vecImpliedToCheck);

	} // temp scope limt for bug hunting


	return bResult;

}


///////////////////////////////////////////////////////////
// Function name	: CSimulation::checkEquations
// Description	    : Ensure equations are well formed to be solved
// Return type		: bool 
// Argument         : ostream& osErrReport
///////////////////////////////////////////////////////////
bool CSimulation::checkEquations(ostream& osErrReport )
{

	ListLineTokenPts::iterator it;
//	vector< CToken* >::iterator itpCT;
	SetPtCTokenStringSearch::iterator itSet;
	bool bResult = true; // ie OK unless a fault can be found
	CEquationFactory* pef = CEquationFactory::instance();
	ASSERT2(pef);
//	long iOpenBrackets, iCloseBrackets;
/*
	Equations need to be checked for:

	[1] derivatives - values need to be adjusted to make a connection
	[2] derivatives - if an individual variable doesn't exist for
					  a derivative then a place holder token needs to be
					  created.
	[3] LHS and RHS need to be clearly identified
	[4] Brackets need to used correctly
	[5] Delimators need to be interspaced correctly
	[6] Only one variable before Eq - thats how equations are being handled right now.

*/

/*	Future feature
	==============
	Like to try creating a map of errors by collecting error message thrown - this could
	then be used for context sensative error reporting.
*/
	// first if in debug mode check csvHandler
	CcsvHolderFactory* pcsvHF = CcsvHolderFactory::instance();
	bResult = pcsvHF->testAllHolders(osErrReport);
	if (!bResult)
		{
		osErrReport<< "<Internal Error*> Failed csvholder tests\n";
		SYMERROR("Failed csvholder tests",errInternal,"",NOT_DEFINED,NOT_DEFINED);
		}

	for (it=m_vecLinesofIntrestEq.begin();it!=m_vecLinesofIntrestEq.end();it++)
		{

		
		bResult&=pef->checkUserRequestedEquation(*it,m_pIARDataStore,osErrReport);


		}//end for it
	
	
	
	return bResult;

}


///////////////////////////////////////////////////////////
// Function name	: CSimulation::checkValues
// Description	    : Ensure values are correctly ascibed to be solved
// Return type		: bool 
// Argument         : ostream& osErrReport
///////////////////////////////////////////////////////////
bool CSimulation::checkValues(ostream& osErrReport )
{

	VectorLineTokenPts::iterator it;
	vector< CToken* >::iterator itpCT;
	long iLHS1,iRHS1,iLHS2,iRHS2;
	long iCount,iPos;
	bool bResult = true;

	iLHS1=0; // should be every time

/*
	Values are dependant or independant.
	All dependant values need intial starting conditions.

*/
#ifndef NDEBUG

	cout << m_vecLinesofIntrestSV.size()<<endl;

	for (it=m_vecLinesofIntrestSV.begin();it!=m_vecLinesofIntrestSV.end();it++)
		{
		for(itpCT=it->begin();itpCT!=it->end();itpCT++)
			cout << (*itpCT)->getString().c_str();
		cout << endl;
		}

#endif
	// set of conditions to cover:

	// check enough variables
	// find poition of equals and at characters
	// first LHS must be of type ctVariable
	// second LHS must be of type variable
	// first RHS must be a regular expression
	// second RHS must be a regular expression
	// First and second expressions must be linked by '@'

	
	for (it=m_vecLinesofIntrestSV.begin();it!=m_vecLinesofIntrestSV.end();it++)
		{
		 iCount = it->size();
		 try
		 {
			if (iCount==0)
				{
				osErrReport << "<Error*> Empty Statement\n";
				SYMERRORLITE("Empty Statement",errInternal);
				throw(1);
				#ifndef NDEBUG
				assert(iCount!=0); // not sure this could ever happen - catch in debug
				#endif
				throw(1);
				}
			if (iCount<7) // then there are not enough tokens here
				{
				 osErrReport << "<Error*> Statement is missing some parts : "<<(*it)[0]->getLine() << " line.\n";	
				 SYMERRORTOK("Statement is missing some parts see the line of this token",errSyntax,(*it)[0]);
				 throw(1);
				}	 

			iPos = 0;
			iRHS1=iLHS2=iRHS2=NOT_FOUND; // these have not been set
			for(itpCT=it->begin();itpCT!=it->end();itpCT++)
				{

// remove after debug
				#ifndef NDEBUG
				cout << (*itpCT)->getString().c_str();
				#endif // ifndef NDEBUG
// end remove after debug


				if (iRHS1==NOT_FOUND)
						{
						if ((*itpCT)->getString().compare(g_Eq)==0)
								iRHS1 = iPos+1;	// Right hand side starts after first '='

						}
						else
						if (iLHS2==NOT_FOUND)
							{
							if ((*itpCT)->getString().compare(g_At)==0)
									iLHS2= iPos+1; // Second left hand side starts after '@'
							}
							else
							if (iRHS2==NOT_FOUND)
								{
								if ((*itpCT)->getString().compare(g_Eq)==0)
										iRHS2= iPos+1; // 
								}
				iPos++;

				} // end for(itpCT=it->begin();itpCT!=it->end();itpCT++)

			if ((iRHS1==NOT_FOUND)||(iLHS2==NOT_FOUND)||(iRHS2==NOT_FOUND))
				{
				 osErrReport << "<Error*> Statement is misformed : "<<(*it)[0]->getLine() << " line.\n";	
				 SYMERRORTOK("Statement is misformed see the line of this token",errSyntax,(*it)[0]);
				 throw(1);
				}


			if ((iRHS1-iLHS1!=2)||(!(*it)[iLHS1]->IsOfType(ctVariable)))
				{
				 osErrReport << "<Error*> 1st Left handside should be a variable : "<<(*((*it)[0])) << ".\n";	
				 SYMERRORTOK("1st Left handside should be a variable",errSyntax,(*it)[0]);
				 throw(1);
				}
			if ((iRHS2-iLHS2!=2)||(!(*it)[iLHS2]->IsOfType(ctVariable)))
				{
				 osErrReport << "<Error*> 2nd Left handside should be a variable : "<<(*((*it)[0])) << ".\n";	
				 if (iRHS2-iLHS2!=2)
						 SYMERRORTOK("2nd Left handside should be a variable - see line of this token",errSyntax,(*it)[0])
						else
						 SYMERRORTOK("2nd Left handside should be a variable",errSyntax,(*it)[iLHS2]);
				 throw(1);
				}
 
			if (!CEquation::IsWellFormedEquation(iLHS1,iLHS2-1,(*it),osErrReport))
				{
				 osErrReport << "<Error*> Left handside is misformed : "<<(*((*it)[0])) << ".\n";	
				 SYMERRORTOK("Expression to be change value is misformed",errSyntax,(*it)[0]);
				 throw(1);
				}

			if (!CEquation::IsWellFormedEquation(iLHS2,iCount/*(iCount-1)*/,(*it),osErrReport))
				{
				 osErrReport << "<Error*> Left handside is misformed : "<<(*((*it)[0])) << ".\n";	
				 SYMERRORTOK("Expression to trigger value change is misformed",errSyntax,(*it)[iLHS2]);
				 throw(1);
				}
		
		 
		 }
		 catch(...)
		 {
			 bResult=false;
		 
		 } 

		}

	return bResult;

}


///////////////////////////////////////////////////////////
// Function name	: CSimulation::checkEvents
// Description	    : 
// Return type		: bool 
// Argument         : ostream& osErrReport
///////////////////////////////////////////////////////////
bool CSimulation::checkEvents(ostream& osErrReport )
{
	VectorLineTokenPts::iterator it;
	vector< CToken* >::iterator itpCT;
	CEventFactory* pcev=NULL;
	bool bResult = true;
	// first check event key word is first in all case
	for (it=m_vecLinesofIntrestEt.begin();it!=m_vecLinesofIntrestEt.end();it++)
		{
		if ((*it).size()==0)
			{
			osErrReport << "<Error*> Event identified by parser, but has no contents\n";
		    SYMERRORLITE("Event identified by parser but has no contents",errInternal);
			ASSERT2(false); // pretty sure this should never happen - but not certain
			bResult=false;
			}
		if ((*it).size()<1)
			{
			osErrReport << "<Error*> Event not properly formed : "<<*((*it)[0])<<endl;
		    SYMERRORTOK("Event not properly formed",errSyntax,(*it)[0]);
			return false; // don't want to proceed with this error
			}

		if (!(*it)[0]->IsOfType(ctEventKeyWord))
			{
			osErrReport<< "<Error*> Line "<<(*it)[0]->getLine()<< " should be started by an Event Keyword, or the line should not specify an Event.\n";
		    SYMERRORTOK("Event not properly formed, should be started by event keyword",errSyntax,(*it)[0]);
			bResult = false;
			}
		}

	// need to redesignate all not defined tokens - check they have equivalents in variables etc
	for (it=m_vecLinesofIntrestEt.begin();it!=m_vecLinesofIntrestEt.end();it++)
		{
		SetPtCTokenStringSearch::iterator itSetpCTVars;
 		for(itpCT=it->begin();itpCT!=it->end();itpCT++)
			{
			cerr << (**itpCT) <<endl; osErrReport.flush();
				switch((*itpCT)->getType())
					{
					case ctNotDefined:
						itSetpCTVars = m_setPtUniqueTokens.find(*itpCT);
						if (itSetpCTVars!=m_setPtUniqueTokens.end())
								{
								(*itpCT)->setType(ctVariable); // or else Parent cannot be assigned
								(*itpCT)->AssignParent((*itSetpCTVars)->getRootTokenPt());
								(*itpCT)->setToParentType();
			cerr << "Set to ->" <<(**itpCT) <<endl; osErrReport.flush();
								}
								else
								{ // this variable hasn't been identified in unique list - add
								m_setPtUniqueTokens.insert(*itpCT);
								(*itpCT)->setType(ctVariable); // or else Parent cannot be assigned
			cerr << "Also set unique ->" <<(**itpCT) <<endl; osErrReport.flush();
								}
						break;
					default:
						break;
					}
			}
		}

	// now it will be necessary to check each event in accordance with its keyword
	pcev = CEventFactory::instance();
	ASSERT2(pcev);
	if (!pcev)
			return false;

	for (it=m_vecLinesofIntrestEt.begin();it!=m_vecLinesofIntrestEt.end();it++)
		{
		bResult &= pcev->checkUserRequestedEvent(*it,m_pIARDataStore,osErrReport);
		}


	return bResult;
}


///////////////////////////////////////////////////////////
// Function name	: CSimulation::checkSolver
// Description	    : 
// Return type		: bool 
// Argument         : ostream& osErrReport
///////////////////////////////////////////////////////////
bool CSimulation::checkSolver(ostream& osErrReport )
{
	VectorLineTokenPts::iterator it;
	CSolClassFactory* pcsol=NULL;
	bool bResult = true;
	// At the moment only one Solver statement is allowed:
	//   if this changes then alterations to makeSolverChoices will also be required
	if (m_vecLinesofIntrestSl.size()<1)
		{
		osErrReport << "<Error*> Solver statement needed.\n";
		SYMERRORLITE("Solver statement needed",errSyntax);
		bResult=false;
		return bResult; // go no further
		}
	if (m_vecLinesofIntrestSl.size()>1)
		{
		osErrReport << "<Error*> Only one solver statement allowed.\n";

		for (it=m_vecLinesofIntrestSl.begin();it!=m_vecLinesofIntrestSl.end();it++)
			{
			if ((*it).size()>0)
				{
				SYMERRORTOK("Only one solver statement is allowed",errSyntax,(*it)[0]);
				}
				else
				{
				SYMERRORLITE("Solver statement identified by parser, but has no contents",errInternal);
				}
			}
		
		bResult=false;
		return bResult; // go no further
		}

	// check event key word is first in all case
	for (it=m_vecLinesofIntrestSl.begin();it!=m_vecLinesofIntrestSl.end();it++)
		{
		if ((*it).size()==0)
			{
			osErrReport << "<Error*> Solver statement identified by parser, but has no contents\n";
			SYMERRORLITE("Solver statement identified by parser, but has no contents",errSyntax);
			ASSERT2(false); // pretty sure this should never happen - but not certain
			bResult=false;
			}
		if ((*it).size()<1) // isn't this the same as the line above 13May10 - still doing no harm
			{
			osErrReport << "<Error*> Solver statement not properly formed : "<<*((*it)[0])<<endl;
			SYMERRORTOK("Solver statement not properly formed",errSyntax,(*it)[0]);
			return false; // don't want to proceed with this error
			}

		if ((!(*it)[0]->IsOfType(ctSolverKeyWord))&&((*it)[0]->getString().compare(g_Sequence)!=0)) // sequence key word is a special case - both event and solver
			{
			osErrReport<< "<Error*> Line "<<(*it)[0]->getLine()<< " should be started by a Solver Keyword, or the line should not specify Solver information.\n";
			SYMERRORTOK("This should be a solver keyword or the line should not specifiy solver information",errSyntax,(*it)[0]);
			bResult = false;
			}
		}


	// now it will be necessary to check each solver in accordance with its keyword
	pcsol = CSolClassFactory::instance();
	ASSERT2(pcsol);
	if (!pcsol)
			return false;

	for (it=m_vecLinesofIntrestSl.begin();it!=m_vecLinesofIntrestSl.end();it++)
		{
		bResult &= pcsol->checkUserRequestedSolver(*it,osErrReport);
		}


	return bResult;

}


///////////////////////////////////////////////////////////
// Function name	: CSimulation::checkTypes
// Description	    : Check format of type commands - before they are implmented
// Return type		: bool 
// Argument         : ostream& osErrReport
///////////////////////////////////////////////////////////
bool CSimulation::checkTypes(ostream& osErrReport )
{
	VectorLineTokenPts::iterator it;
	CStrongTypeFactory* pcstf=NULL;
	bool bResult = true;

	// check event key word is first in all case
	for (it=m_vecLinesofIntrestTv.begin();it!=m_vecLinesofIntrestTv.end();it++)
		{
		if ((*it).size()==0)
			{
			osErrReport << "<Error*> Type modifier statement identified by parser, but has no contents\n";
			SYMERRORLITE("Type modifier statement identified by parser, but has no contents",errSyntax);
			ASSERT2(false); // pretty sure this should never happen - but not certain
			bResult=false;
			}
		if ((*it).size()<1)
			{
			osErrReport << "<Error*> Type modifier statement not properly formed : "<<*((*it)[0])<<endl;
			SYMERRORTOK("Type modifier statement not properly formed",errSyntax,(*it)[0]);
			return false; // don't want to proceed with this error
			}

		if (!(*it)[0]->IsOfType(ctTypeModifier))
			{
			osErrReport<< "<Error*> Line "<<(*it)[0]->getLine()<< " should be started by a Solver Keyword, or the line should not specify Solver information.\n";
			SYMERRORTOK("Solver Keyword should be present, or the line should not specify Solver information",errSyntax,(*it)[0]);
			bResult = false;
			}
		}


	// now it will be necessary to check each event in accordance with its keyword
	pcstf = CStrongTypeFactory::instance();
	ASSERT2(pcstf);
	if (!pcstf)
			return false;

	for (it=m_vecLinesofIntrestTv.begin();it!=m_vecLinesofIntrestTv.end();it++)
		{
		bResult &= pcstf->checkUserRequestedStrongType(*it,osErrReport);
		}


	return bResult;
}


///////////////////////////////////////////////////////////
// Function name	: CSimulation::processifDerivative
// Description	    : 
// Return type		: bool 
// Argument         : list<CToken>::iterator& it
///////////////////////////////////////////////////////////
bool CSimulation::processifDerivative(list<CToken>::iterator& it)
{
	bool bResult = false;
	list<CToken>::iterator it0,it1,it2,it3;
	long iCount = 4;
	string sNew;

	if (it->IsOfType(ctDerivative))
		return true;

	// Check vectors of Tokens haven't been created. This action must not happen if they have.
	ASSERT2(m_vecLines.size()==0);
	ASSERT2(m_vecLinesofIntrestEq.size()==0);
	ASSERT2(m_vecLinesofIntrestSV.size()==0);

	it0=it;
	// first check there are enough tokens left to be looked at
	while((iCount>0)&&(it0!=m_ltTokens.end()))
	{
	it0++;
	iCount--;
	}
	if (iCount!=0)
				return false; // as there won't be enough tokens to work with

	it3=it0=it;
	it1=++it3;
	it2=++it3;
	it3++;


	if ( (it1->getString().compare(g_Slash)==0) && (it3->getString().compare(g_Eq)==0) ) // then may be a derivative
					{
					if  (( (it0->getString()[0]==g_cDeriv) && (it2->getString()[0]==g_cDeriv) ))
							{
							bResult = true;
							// now assign the first derivative - combine it and delete the result
							sNew = it0->getString() + it1->getString() + it2->getString();
							it0->setString(sNew);
							it0->setType(ctDerivative);

							// these two tokens are no contained within it0 - so remove them
							/***************************
							/ WARNING: 
							/ This must only be done before Lines and equation vectors of CToken* have been 
							/ assigned. Otherwise a massive mess will result.
							/***************************/

							// the order here matters. ( as it2 will point to something different if it1 erased first )
							m_ltTokens.erase(it2);
							m_ltTokens.erase(it1);
							}
					}	
					


	return bResult;
}


///////////////////////////////////////////////////////////
// Function name	: CSimulation::processifContainsNames
// Description	    : Move any string in quotes to one ctName Token
//                    to be used before assigning lines.
//                    Returns true if any within quote rearrangement has taken place.
//					  The tokens are not themselves removed but copies added to the vector
//					  m_vRemove.
// Return type		: bool 
// Argument         : list<CToken>::iterator it
///////////////////////////////////////////////////////////
bool CSimulation::processifContainsNames(list<CToken>::iterator it)
{
	bool bResult = false;
	bool bInQuote = false;
	list<CToken>::iterator itEndLine,itEndQuote,itStartQuote,itStartName,itEndName;
	list<CToken>::iterator itStart=it;
//	vector<CToken*> vpTokens;
//	vector<CToken*>::iterator itpT;
	string sNew;

	ASSERT2(it!=m_ltTokens.end());

	if (it==m_ltTokens.end())
			return false;
	
	const CToken& ct = (*it);
	// firts find end of line
	while((it!=m_ltTokens.end())&&(it->sameLine(ct)))
		it++;

	itEndLine=it;
	it=itStart;

	while(it!=itEndLine)
	{
		if (it->getString().compare(g_Quote)==0)
			{
			
			if (bInQuote)
				{
				itEndQuote=it;
				list<CToken>::iterator itFirst=itStartQuote; itFirst++;
				list<CToken>::iterator itQ;

				sNew = "";
				for (itQ=itFirst;itQ!=itEndQuote;itQ++)
					{
					if (itQ!=itFirst)
						m_vpRemove.push_back(itQ);
					sNew += itQ->getString().c_str();
					}

				itFirst->setString(sNew);
				itFirst->setType(ctName);

				bInQuote=false;
				bResult=true;

				}
				else
				{
				itStartQuote=it;	
				bInQuote=true;
				}		
			
			}	

		it++;
	}
	


	return bResult;
}



///////////////////////////////////////////////////////////
// Function name	: CSimulation::cascadeTokenTypes
// Description	    : 
// Return type		: void 
///////////////////////////////////////////////////////////
void CSimulation::cascadeTokenTypes()
{
	list< CToken >::iterator it;
	#ifndef NDEBUG
	assert(m_eState!=cessInitiated); // only crash if in debug mode
	#endif
	if (m_eState==cessInitiated)
			return; // do nothing.

	// for every Token, ensure it has the type of any parent - if any
	for (it=m_ltTokens.begin();it!=m_ltTokens.end();it++)
#ifdef DEBUGEXPAND
			{
			ATLTRACE("[it = %x, ",it);
			ATLTRACE("%s]\t",(*it).getString().c_str());
			cout << (*it) <<endl;
			it->setToParentType();
			}
	ATLTRACE("\n");
#else
			it->setToParentType();
#endif
}


void CSimulation::assignStatusofVariables()
{

/*
Equations and Set Value should have been created by this stage......

Think about how these should behave 18Jan05
*/



}



	// ensure CToken's identify Delims

	// check for line types then assign then to the correct type

	// need to think about creating variables
	// also think about a separte solving class from the relation (so could
	// be optimised for numerical considerations - eg size of variables. Could
	// assign a trace element as important eg H2S


///////////////////////////////////////////////////////////
// Function name	: CSimulation::makeEquations
// Description	    : Create vector of CEquation objects
//                    assumes equation lines ( a different form of the equations )
//                    have first been checked. Otherwise equations will be invalid.
// Return type		: bool 
// Argument         : ostream& osErrReport
///////////////////////////////////////////////////////////
bool CSimulation::makeEquations(ostream& osErrReport)
{
	ListLineTokenPts::iterator it;
//	list<CEquation*>::const_iterator ipEq;
	CEquationFactory* pef = CEquationFactory::instance();
	CArrayFactory* paf = CArrayFactory::instance();
	CEquation* peq;
	list<CEquation*>::iterator itEq;

	bool bNewArray;
	bool bResult = true;
	long iLoopCount =0;	

	m_vpEquations.clear();
	for (it=m_vecLinesofIntrestEq.begin();it!=m_vecLinesofIntrestEq.end();it++)
		{
		peq =pef->createEquation(0,it->size(),*it,m_pIARDataStore,osErrReport);

		if (peq)
			{
			m_vpEquations.push_back(peq);

			}
			else
			{
			SYMERRORTOK("Unable to create equation",errSystem,(*it)[0]);
			bResult = false;
			}

		}//end for it

	for (itEq=m_vpEquations.begin();itEq!=m_vpEquations.end();)
	{
			(*itEq)->sentToAtlTrace();

			(*itEq)->setLHSArrayStatus(paf);

			if ((*itEq)->checkImpliedArrays(paf)) // if an array has been implied create it - LHS is array case has been checked in IsWellFormedEquation
					bNewArray = (*itEq)->createImpliedArray(paf); 
					else
					bNewArray = false;

			// for those equation types that are dependent on knowing all implied arrays to check
			// final checks must be carried out now after the equation has been created
		
			if (!(*itEq)->postCreationCheck(paf))
					bResult = false;

			if (bResult&&bNewArray)
					{
					if (iLoopCount<m_vpEquations.size()) // then we are stuck
							itEq = m_vpEquations.begin(); // start again
							else
							itEq++;
					iLoopCount++;

					ASSERT2(iLoopCount<=m_vpEquations.size());
					if (iLoopCount>m_vpEquations.size()) // then we are stuck	
							{
							SYMERRORLITE("Caught in an internal loop assesing arrays",errInternal); // very bad
							}
					 // check if there is a underlying variable on the LHS which means checking of earlier arrays is necessary again
					/*Try to make implied arrays then signal create array section needs to start again if they can be found int he 
					equations that have already been processed ( perhaps should target those equations rather than makign 
					a recursing loop. )*/
					}
					else
					itEq++;

	}


	return bResult;
}


///////////////////////////////////////////////////////////
// Function name	: CSimulation::makeValues
// Description	    : Create vector of CEvent objects
//                    assumes equation lines ( a different form of the equations )
//                    have first been checked. Otherwise equations within events will be invalid.
// Return type		: bool 
// Argument         : ostream& osErrReport
///////////////////////////////////////////////////////////
bool CSimulation::makeValues(ostream& osErrReport)
{
	VectorLineTokenPts::iterator it;
	vector<CEvent*>::const_iterator itpEv;
	CEventFactory* pef = CEventFactory::instance();
	CEvent* pev = NULL;
	bool bResult = true;
	long lPosAt = NOT_FOUND;
	string sAt(g_At);	

	if (!pef)
			{
			osErrReport << "<<Error*>> Unable to start creating events - internal error.\n";
			SYMERRORLITE("Unable to start creating events",errSystem);
			return false;
			}

	m_vpEvents.clear();
	for (it=m_vecLinesofIntrestSV.begin();(bResult)&&(it!=m_vecLinesofIntrestSV.end());it++)
		{
			lPosAt = findPlaceInLine(*it,sAt);
			ASSERT2(lPosAt!=NOT_FOUND); // all m_vecLinesofIntrestSV should have @ if not then things should not have got this far.	
			bResult &= pef->checkSVEvent(g_EvEvent,*it,osErrReport);
			if (bResult)
				{
				pev = pef->createEvent(g_EvEvent,CEquation(0,lPosAt,*it,osErrReport), CEquation(lPosAt+1,it->size(),*it,osErrReport));
				if (pev)
					m_vpEvents.push_back(pev);
				}
		}//end for it

	if (bResult)
		for(itpEv=m_vpEvents.begin();itpEv!=m_vpEvents.end();itpEv++)
			bResult &= (*itpEv)->isCorrect();

	return bResult;
}


///////////////////////////////////////////////////////////
// Function name	: CSimulation::makeEvents
// Description	    : Create events 
// Return type		: bool 
// Argument         : ostream& osErrReport
///////////////////////////////////////////////////////////
bool CSimulation::makeEvents(ostream& osErrReport)
{
 VectorLineTokenPts::iterator itvLpCT;
 CEventFactory* pevf = CEventFactory::instance();
 bool bResult = true;
 CEvent* pev;
 CArrayFactory* paf = CArrayFactory::instance();
 CArray* pa;

 if (paf->first())
 do
 {
	pa = paf->getCurrentArray();
	if ((pa->assignsValues())&&(pa->first()))
		{
			do
			{
				pev = newtrack CEvStart( pa->getToken(), pa->getValue() );
				bResult &= bool(pev);
				if (pev)
					{
					pevf->manageEvent(pev);
					m_vpEvents.push_back(pev);
					}
			}
			while( pa->next());
		}
 }
 while(paf->next());


 for (itvLpCT=m_vecLinesofIntrestEt.begin();itvLpCT!=m_vecLinesofIntrestEt.end();itvLpCT++)
	{
	pev = pevf->createEvent(0,itvLpCT->size(),*itvLpCT,m_pIARDataStore,osErrReport, m_vecLinesofIntrestEq);
	if (pev)
		m_vpEvents.push_back(pev);
	bResult &= bool(pev);

	}

 pev = addSystemEvent(eseOutsideStop,osErrReport,m_vpEvents);

 if (pev)
		m_pOutsideStop = pev;
		else
		bResult=false;

 m_vpEvents.push_back(&m_OutsideSetData);
 m_vpEvents.push_back(&m_OutsideGetData);
			
 

 return bResult; 
 }


///////////////////////////////////////////////////////////
// Function name	: CSimulation::addSystemEvent
// Description	    : Helper function
// Return type		: CEvent* 
// Argument         : const eSysEvents eNewSysEvent
// Argument         : ostream& osErrReport
// Argument         : vector<CEvent*>& rvEvents
///////////////////////////////////////////////////////////
CEvent* CSimulation::addSystemEvent(const eSysEvents eNewSysEvent, ostream& osErrReport,vector<CEvent*>& rvEvents)
{
	CEvent* pev;
	CEventFactory* pevf = CEventFactory::instance();

	pev = pevf->createSystemEvent(eNewSysEvent);

	if (pev)
		rvEvents.push_back(pev);

	return pev;
}


///////////////////////////////////////////////////////////
// Function name	: CSimulation::addUserEvents
// Description	    : 
// Return type		: bool 
// Argument         : const vector<long>& vecInd
// Argument         : const vector<variable>& vecValue
// Argument         : const vector<eUserEvents>& vecEvType
///////////////////////////////////////////////////////////
bool CSimulation::addUserEvents( const vector<long>& vecInd, const vector<variable>& vecValue, const vector<eUserEvents>& vecEvType )
{

	vector<CEvent*> vecpEvents;
	CEvent* pev;

	bool bResult = false;
	long iCount;

	CEventFactory* pevf = CEventFactory::instance();

	// check simulation if the rigth state
	if (m_eState!=cessInitiated)
			return false;

	// generate events
	ASSERT2(pevf);

	if (pevf==NULL) // catch in production
		{
		SYMERRORLITE("Unable to create user events when requested.",errInternal);
		return false;
		}

	// pass events to model

	ASSERT2((vecInd.size()==vecValue.size())==(vecValue.size()==vecEvType.size())); // this should ahve been stopped before the call ( on debug )
	if ((vecInd.size()!=vecValue.size())||(vecValue.size()!=vecEvType.size()))
		{
		SYMERRORLITE("Unable to create user events when requested.",errInternal);
		return false;
		}


	for (iCount=0;iCount<vecInd.size();iCount++)
		{
		switch(vecEvType[iCount])
			{
			case eueStart:
				pev = pevf->createUserEvent(vecEvType[iCount],vecInd[iCount],vecValue[iCount],(m_cmModel.getIndIndex()==vecInd[iCount]));
				break;
			case eueStop:
				pev = pevf->createUserEvent(vecEvType[iCount],vecInd[iCount],vecValue[iCount],(m_cmModel.getIndIndex()==vecInd[iCount]));
				break;
			default:
				pev = NULL;
				break;
			}
		if (pev)
			vecpEvents.push_back(pev);
		}

	bResult = m_cmModel.addUserRequestedEvents(vecpEvents);


	return bResult;
}


///////////////////////////////////////////////////////////
// Function name	: CSimulation::addRunTimeEvent
// Description	    : Add an event just before running
// Return type		: bool 
// Argument         : CEvent* pEvCallBack
///////////////////////////////////////////////////////////
bool CSimulation::addRunTimeEvent( CEvent* pEvCallBack )
{
	bool bResult;
	vector<CEvent*> vecpEv;

	if (!pEvCallBack)
		return false;

	vecpEv.push_back(pEvCallBack);

	bResult = m_cmModel.addUserRequestedEvents(vecpEv);

	return bResult;
}


///////////////////////////////////////////////////////////
// Function name	: CSimulation::findPlaceInLine
// Description	    : Returns the position in th eline of a matching string.
// Return type		: long 
// Argument         : const vector< CToken* >& vptLine
// Argument         : const string& sFind
///////////////////////////////////////////////////////////
long CSimulation::findPlaceInLine(const vector< CToken* >& vptLine, const string& sFind) const
{
	vector< CToken* >::const_iterator it;
	long lPos = 0;
	it = vptLine.begin();

	while((it!=vptLine.end())&&(sFind!=(*it)->getString()))
	{
	it++;
	lPos++;
	}
	

	if (it==vptLine.end())
		lPos = NOT_FOUND;

	return lPos;
}


///////////////////////////////////////////////////////////
// Function name	: CSimulation::expandAndSubstituteNextInclude
// Description	    : expands include macro statements
// Return type		: bool 
// Argument         : list<CToken>& listTokens
// Argument         : CTokeniser& cTokeniser
// Argument         : ostream& oserrr
// Argument         : bool bFormatError - signify error status to stop simulation
///////////////////////////////////////////////////////////
bool CSimulation::expandAndSubstituteNextInclude(list<CToken>& listTokens, CTokeniser& cTokeniser, ostream& oserr, bool& bFormatError )
{
	IARStream* pIStream = NULL; // as refered to in catch latter
	list<CToken>::iterator itInclude;
	list<CToken>::iterator itTok;
	list<CToken>::iterator itTest;
	vector< list<CToken>::iterator > vecpLine;
	list<CToken> listInclude;
	bool bFound = false;
	enumARReadHint erh = readFormatFreeText;

	// find an the next include macro if not return false
	itTok = listTokens.begin();

	if (itTok==listTokens.end())
			return false;

	while((itTok!=listTokens.end())&&(!bFound))
		{
		if ((itTok->IsOfType(ctMacroKeyWord))&&(itTok->getString().compare(g_Include)==0))
					bFound=true;
					else
					itTok++;
		}

	if (!bFound)
		return false;

	ASSERT2(itTok!=listTokens.end()); // stands to reason of course

	// need to get the line that this include instruction is on

	// make sure its first in line
	if (itTok!=listTokens.begin())
		{
		itTest = itTok; itTest--;
		#ifndef NDEBUG
		long iLineTest = itTest->getLine();
		#endif
		if (itTest->sameLine(*itTok)) // need to cover case where line before in blank and has no Tokens
			{
			bFormatError=true;
			oserr << "<Error*> " << itTok->getString().c_str() << " needs to be the first term on line "<<itTok->getLine()<<"."<<endl;
			SYMERRORTOK("Must be first item on line",errSyntax,&(*itTok));
			return false; // ie go no further
			}
		}

	itTest=itTok;
	while((itTest!=listTokens.end())&&(itTest->sameLine(*itTok)))
		vecpLine.push_back(itTest++);

	// check format of line
	if (vecpLine.size()<4) // can't have stated term correctly
		{
			bFormatError=true;
			oserr << "<Error*> Format error on line "<<itTok->getLine()<<"."<<endl;
			SYMERRORTOK("Format error",errSyntax,&(*itTok));
			return false; // ie go no further
		}

	if (vecpLine[1]->getString().compare(g_Quote)!=0)
		{
			bFormatError=true;
			oserr << "<Error*> Format error on line "<<vecpLine[0]->getLine()<<", missing "<<g_Quote <<" ."<<endl;
			SYMERRORTOK("Missing quote ",errSyntax,&(*itTok));
			return false; // ie go no further
		}

	string sFileName;
	long iT=2;

	while((iT<vecpLine.size())&&(vecpLine[iT]->getString().compare(g_Quote)!=0))
		{
		sFileName += vecpLine[iT]->getString().c_str();
		iT++;
		}

	if (iT==vecpLine.size()) // then no quote found
		{
			bFormatError=true;
			oserr << "<Error*> Format error on line "<<vecpLine[0]->getLine()<<", missing second "<<g_Quote <<" ."<<endl;
			SYMERRORTOK("Missing second quote",errSyntax,&(*(vecpLine[0])));
			return false; // ie go no further
		}

	if (sFileName.length()<1)
		{
			bFormatError=true;
			oserr << "<Error*> Format error on line "<<vecpLine[0]->getLine()<<", missing second "<<g_Quote <<" ."<<endl;
			SYMERRORTOK("Missing second quote",errSyntax,&(*(vecpLine[0])));
			return false; // ie go no further
		}


	// check the file exist and doesn't give an error
	CComBSTR cbFileName(sFileName.c_str());

	ASSERT2(m_pIARDataStore);
	if (!m_pIARDataStore) // incase a production problem time
		{
		oserr << "<Internal Error*> Internal data store manager cannot be accessed." << endl;
		SYMERRORLITE("Internal data store manager cannot be accessed",errSystem);
		m_eState=cessUninitated;
		return false;
		}


	if (!checkFileExists(sFileName))
		{
		oserr << "<Error*> The following include data cannot be found - "<<sFileName.c_str()<<" at line "<<vecpLine[0]->getLine()<<"."<<endl;
		string sErr = "The stream for the include data ";
		sErr.append(sFileName);
		sErr.append(" cannot be found");
		SYMERRORLITE(sErr.c_str(),errSystem);
		m_eState=cessUninitated;
		return false;
		}


// upload the file into a list of CTokens - noting the file these are from
//listInclude

	HRESULT hr = m_pIARDataStore->tryToGetARStream(&(cbFileName.m_str),erh,&pIStream);

	if ((FAILED(hr))||(!pIStream))
		{
		oserr << "<Internal Error*> The following include data stream cannot be loaded - "<<sFileName.c_str()<<" at line "<<vecpLine[0]->getLine()<<"."<<endl;
		SYMERRORTOK2("The following include data stream cannot be loaded - ",sFileName.c_str(),errSystem,&(*(vecpLine[0])));
		m_eState=cessUninitated;
		if (!pIStream)
			pIStream->Release();
		return false;
		}

	enumARStream ess;

	hr = pIStream->get_StreamState(&ess);

	if ((FAILED(hr))||(ess!=streamLoaded))
		{
		oserr << "<Internal Error*> The following include data stream cannot be properly loaded - "<<sFileName.c_str()<<" at line "<<vecpLine[0]->getLine()<<"."<<endl;
		string sErr = "The following include data stream cannot be loaded properly - ";
		sErr.append(sFileName);
		SYMERRORTOK(sErr.c_str(),errSystem,&(*(vecpLine[0])));
		m_eState=cessUninitated;
		if (!pIStream)
			pIStream->Release();
		return false;
		}

	try
	{
		CComBSTR cbLine;
		string sLine;
		long lLine = 0;

		while((SUCCEEDED(pIStream->get_StreamState(&ess)))&&((ess==streamReadline)||(ess==streamLoaded))&&(SUCCEEDED(pIStream->readLine(&(cbLine.m_str)))))
		{
		
			USES_CONVERSION;
			sLine = OLE2A(cbLine.m_str);
			cTokeniser.tokeniseLine(lLine,sLine.c_str(),listInclude,sFileName.c_str());
			lLine++; // so the location of the Tokens are known as well as the type
		}

		pIStream->Release();

	}
	catch(...)
	{
		oserr << "<Internal Error*> Undefined error reading input include file" << endl;
		SYMERRORLITE2("Undefined error reading input include file - ",sFileName.c_str(),errInternal);
		m_eState=cessUninitated;

		if (pIStream)
			pIStream->Release();

		return false;
	}

	// set macro line to comment and insert the file after that line
	for (iT=0;iT<vecpLine.size();iT++)
		vecpLine[iT]->setType(ctComment);

	// lets insert the items after itTok
	for (list<CToken>::iterator it=listInclude.begin();it!=listInclude.end();it++)
		it->setRootLocation(itTok->getLocation());

	listTokens.insert(itTok,listInclude.begin(),listInclude.end());	

	return true; 
}


bool CSimulation::isModelSquare()
{
	bool bResult = false;



	return bResult; // TBI
}


///////////////////////////////////////////////////////////
// Function name	: CSimulation::copySetpttoStream
// Description	    : 
// Return type		: void 
// Argument         : SetPtCToken& setptTokens
// Argument         : ostream& os
///////////////////////////////////////////////////////////

/*static*/ void CSimulation::copySetpttoStream(SetPtCToken& setptTokens, ostream& os)
{
	SetPtCToken::iterator itset;

	for(itset=setptTokens.begin();itset!=setptTokens.end();itset++)
#ifndef DEBUGSETS
			os << (*itset)->getString().c_str() << "\t";
#else
			os <<  (**itset) << *itset<<"\n";
#endif
	os << endl;
	#ifndef NDEBUG
	os.flush();
	#endif

}

/*static*/ void CSimulation::copySetptSearchtoStream(SetPtCTokenStringSearch& setptTokens, ostream& os)
{
	SetPtCTokenStringSearch::iterator itset;

	for(itset=setptTokens.begin();itset!=setptTokens.end();itset++)
#ifndef DEBUGSETS
			os << (*itset)->getString().c_str() << "\t";
#else
			os <<  (**itset) << *itset<<"\n";
#endif
	os << endl;
	#ifndef NDEBUG
	os.flush();
	#endif

}

/*static*/ void CSimulation::copySetpttoStream(vector<CToken*>& vecptTokens, ostream& os)
{
	vector<CToken*>::const_iterator itvec;

	for(itvec=vecptTokens.begin();itvec!=vecptTokens.end();itvec++)
#ifndef DEBUGSETS
			os << (*itvec)->getString().c_str() << "\t";os.flush();
#else
			os <<  (**itvec) << *itvec<<"\n";
#endif
	os << endl;
	#ifndef NDEBUG
	os.flush();
	#endif

}


///////////////////////////////////////////////////////////
// Function name	: CSimulation::assignTokenTypes
// Description	    : Assign type to underlying parent then cascade
//					  that type to all other occurances.
// Return type		: void 
// Argument         : vector<CToken*>& vec
// Argument         : eTokenType eT
///////////////////////////////////////////////////////////
void CSimulation::assignTokenTypes(vector<CToken*>& vec, eTokenType eT )
{
	vector<CToken*>::iterator itv;

	for (itv=vec.begin();itv!=vec.end();itv++)
		(*itv)->getRootTokenPt()->setType(eT);

	cascadeTokenTypes();

}



///////////////////////////////////////////////////////////
// Function name	: CSimulation::makeSolverChoices
// Description	    : Set up solver options based on input 
//                    information gathered. CheckSolver should
//                    have been called before hand.
// Return type		: bool 
// Argument         : ostream& osErrReport
///////////////////////////////////////////////////////////
bool CSimulation::makeSolverChoices(ostream& osErrReport)
{
 int iIndex;
 bool bOnce = false;

 CSolClassFactory* psf = CSolClassFactory::instance();

 if (m_vecLinesofIntrestSl.size()!=1)
			{
			SYMERRORLITE(_T("No solver choices found"),errSyntax);
			return false;
			}

 if (m_vecLinesofIntrestSl[0].size()<1)
			{
			SYMERRORLITE(_T("Unhandled problem with reading solver keywords."),errInternal);
			return false;
			}

 bOnce = (((m_vecLinesofIntrestSl[0][0])->getString().compare(g_Once)==0)||((m_vecLinesofIntrestSl[0][0])->getString().compare(g_Advance)==0));

 if ((!bOnce)&&(m_vecLinesofIntrestSl[0].size()<2))
				{
				SYMERRORTOK(_T("Not enough information on the solver"),errSyntax,m_vecLinesofIntrestSl[0][0]);
				return false;
				}

// m_pSolver = psf->createSolver((m_vecLinesofIntrestSl[0][1])->getString().c_str());			
//NEED TO SORT SOLVER CREATION OUT HERE ..... should be the one specified
 if ((bOnce)||((m_vecLinesofIntrestSl[0][0])->getString().compare(g_Sequence)==0))
	iIndex =0;
	else
	iIndex =1;

 m_pSolver = psf->createSolver((m_vecLinesofIntrestSl[0][iIndex])->getString().c_str(),1,(m_vecLinesofIntrestSl[0]).size(),&(m_vecLinesofIntrestSl[0]),cerr);

 return (m_pSolver!=NULL);//just to make it easier to read ... return m_pSolver would have been fine  
}



///////////////////////////////////////////////////////////
// Function name	: CSimulation::makeTypes
// Description	    : set up the map of types
//                    which needs to be used else where
// Return type		: bool 
// Argument         : ostream& osErrReport
///////////////////////////////////////////////////////////
bool CSimulation::makeTypes(ostream& osErrReport)
{
 bool bResult=true;
 VectorLineTokenPts::iterator it;
 CStrongTypeFactory::clear(); // make sure its a new list of types - must be before call to instance !
 CStrongTypeFactory* pstf = CStrongTypeFactory::instance();

 for (it=m_vecLinesofIntrestTv.begin();it!=m_vecLinesofIntrestTv.end();it++)
		{
		bResult &= pstf->addTypeDeclaration(0,it->size(),*it,osErrReport);
		}

 return bResult;
}


///////////////////////////////////////////////////////////
// Function name	: CSimulation::checkFileExists
// Description	    : Check file exists - static function
// Return type		: bool 
// Argument         : const string &sFile
///////////////////////////////////////////////////////////
bool CSimulation::checkFileExists(const string &sFile)
{


	bool bResult;
	CComBSTR cbFileName(sFile.c_str());
	ASSERT2(m_pIARDataStore);
	if (!m_pIARDataStore)
		return false;

	VARIANT_BOOL bOK;
	if (FAILED(m_pIARDataStore->isAvailable(&(cbFileName.m_str),&bOK)))
		return false;
	bResult = (bOK!=0);

	return bResult;
}


///////////////////////////////////////////////////////////
// Function name	: CSimulation::getCopyVariableList
// Description	    : Get a copy of the variable strings -
//                    in the order that the solver will handle them in.
// Return type		: bool 
// Argument         : vector< string >& vecVL
///////////////////////////////////////////////////////////
bool CSimulation::getCopyVariableList(vector< string >& vecVL )
{
	vector< CToken* >::const_iterator cit;
	vecVL.clear(); // empty it anyway

	if ((m_eState!=cessInitiated)||(m_vecOrderedVarTokens.size()==0))
		return false;
	
	vecVL.reserve(m_vecOrderedVarTokens.size());

	for(cit=m_vecOrderedVarTokens.begin();cit!=m_vecOrderedVarTokens.end();cit++)
		vecVL.push_back((*cit)->getStringRef());

	ASSERT2(m_vecOrderedVarTokens.size()==vecVL.size());

	return true;
}


///////////////////////////////////////////////////////////
// Function name	: CSimulation::findIndexOfVar
// Description	    : Find position in ordered array of variables or
//                    return NOT_FOUND
// Return type		: long 
// Argument         : const string &sFind
///////////////////////////////////////////////////////////
long CSimulation::findIndexOfVar(const string &sFind)
{

	long iResult=0;
	vector< CToken* >::const_iterator cit = m_vecOrderedVarTokens.begin();

	while((cit!=m_vecOrderedVarTokens.end())&&(sFind.compare((*cit)->getStringRef().c_str())!=0))
		{
			iResult++;
			cit++;
		}

	if (cit==m_vecOrderedVarTokens.end())
		return NOT_FOUND;

	return iResult;
}


///////////////////////////////////////////////////////////
// Function name	: CSimulation::requestEndOfSimulation
// Description	    : Set event to request a stop.
//                    Main use when running solver in a seperate thread.
// Return type		: bool // true if successful in sending message 
///////////////////////////////////////////////////////////
bool CSimulation::requestEndOfSimulation()
{
	if (!m_pOutsideStop) // the event has not been create yet
		return false;

	m_pOutsideStop->setFlag(true); // no critical sections used as doesn't matter if run for another cycle

	return true;
}


///////////////////////////////////////////////////////////
// Function name	: CSimulation::setTag
// Description	    : Set the user defined tag that will substitute for a defined user tag 
// Return type		: void 
// Argument         : const cstring &sNewTag
///////////////////////////////////////////////////////////
void CSimulation::setTag(const string &sNewTag)
{
	m_sTag = sNewTag;
}


///////////////////////////////////////////////////////////
// Function name	: CSimulation::checkArrays
// Description	    : make sure arrays declared directly in input file
//                    are formated acceptably.
// Return type		: bool 
// Argument         : ostream &osErrReport
///////////////////////////////////////////////////////////
bool CSimulation::checkArrays(ostream &osErrReport)
{
	VectorLineTokenPts::iterator it;
	CArrayFactory* pcaf = CArrayFactory::instance();
	bool bResult = true;

	for(it=m_vecLinesofIntrestAr.begin();it!=m_vecLinesofIntrestAr.end();it++)
			bResult &= pcaf->checkArray(*it, m_pIARDataStore, osErrReport);
	
	return bResult;
}


///////////////////////////////////////////////////////////
// Function name	: CSimulation::makeArrays
// Description	    : Make arrays explicitly declared
//                    note: other arrays may be implied and 
//                          created later.
// Return type		: bool 
// Argument         : ostream &osErrReport
///////////////////////////////////////////////////////////
bool CSimulation::makeArrays(ostream &osErrReport)
{

/* to delete shortly
	if (m_vecLinesofIntrestAr.size()==0)
		return true; // temp fix to allow code to be tested
*/
	VectorLineTokenPts::iterator it;

	// note CArrayFactory should have been reset at the start of creating a bew model - see wipeFactories()

	CArrayFactory* pcaf = CArrayFactory::instance();
	bool bResult = true;
//	vector< CArray* > vecArrays;
	CArray* pAr;
	CToken* pNew;
	SetPtCTokenStringSearch::iterator itSet;

	for(it=m_vecLinesofIntrestAr.begin();it!=m_vecLinesofIntrestAr.end();it++)
			{
			pAr= pcaf->createArray(*it,m_pIARDataStore,osErrReport);
			if ((pAr)&&((*it).size()>0)&&(!pAr->IsInError()))
				{
				bResult &= true;
//				vecArrays.push_back(pAr);
				vector< CToken* > vecpNewToks;
				vector< CToken* >& rpvecT= (*it);
				CToken tok(**(rpvecT.begin()));
				tok.setType(ctVariable);
				tok.setAsPartArray();
				if ((pAr->first())&&(pAr->assignsValues()))
						do
						{
							tok.setString(pAr->getString());	
							m_ltTokens.push_back(tok); // will copy token
							pNew = &(m_ltTokens.back()); // need a pointer to the master Token, not tok which goes out of scope
							vecpNewToks.push_back(pNew);
							itSet = m_setPtUniqueTokens.find(pNew);
							if (itSet==m_setPtUniqueTokens.end())
								m_setPtUniqueTokens.insert(pNew);
								else
								pNew->AssignParent(*itSet);
						}
						while(pAr->next());

				if (!pAr->addTokenPtVec(vecpNewToks))
					{
					SYMERRORTOK("Failed to construct an array correctly",errInternal,pNew);
					bResult &= false;
					ASSERT2(false);
					}
				}
				else
				bResult &= false;
			}

	return bResult;

}


///////////////////////////////////////////////////////////
// Function name	: CSimulation::expandArrays
// Description	    : Helper function that takes equations that have arrays
//                    and expands them
// Return type		: bool 
// Argument         : ostream &osErr
///////////////////////////////////////////////////////////
bool CSimulation::expandArrays(ostream &osErr)
{

	list<CEquation*>::iterator it;
	list<CEquation*>::iterator itRemove;
	vector<CEquation*> vecNewEqs; // where copies of new equations will be placed before sliding them in.
	vector<CEquation*> vecRemove; // the equations to be removed from the simulation list
	long iNewCount=0;

#ifndef NDEBUG
	osErr << "List of Equations with arrays\n";
	for (it=m_vpEquations.begin();it!=m_vpEquations.end();it++)
		if ((*it)->hasExpandableArrays())
			osErr << (**it) <<endl;
	osErr <<endl;
#endif

	for (it=m_vpEquations.begin();it!=m_vpEquations.end();it++)
		if ((*it)->hasExpandableArrays())
			{
			vecNewEqs.clear();

			iNewCount = CEquationFactory::instance()->expandArrayEquations((*it),m_ltTokens,vecNewEqs,m_setPtUniqueTokens);

			ASSERT2(iNewCount==vecNewEqs.size());

			if (vecNewEqs.size()>0)
				{
				m_vpEquations.insert(it,vecNewEqs.begin(),vecNewEqs.end());
				itRemove=it;
				it--; // which exists as more than one CEq pointer added before it
				m_vpEquations.erase(itRemove); // as m_vpEquations is a list this is OK
				}

			}

#ifndef NDEBUG
	osErr << "List of Equations with arrays\n";
	for (it=m_vpEquations.begin();it!=m_vpEquations.end();it++)
		if ((*it)->hasExpandableArrays())
			osErr << (**it) <<endl;
	osErr <<endl;
#endif

	for (it=m_vpEquations.begin();it!=m_vpEquations.end();it++)
		(*it)->expandArrayFunctions(m_ltTokens,m_setPtUniqueTokens);

	return true;
}

#define LLTPIT list< ListLineTokenPts::iterator >::iterator

struct ltstrListLineTokenPts
{
  bool operator()( const LLTPIT s1, const LLTPIT s2) const
  {
    return ( (*s1)->begin() < (*s2)->begin() );
  }
};
///////////////////////////////////////////////////////////
// Function name	: CSimulation::expandIndecies
// Description	    : Helper function that creates indicies
//                    then updates equations for them
// Return type		: bool 
// Argument         : ostream& osErr
///////////////////////////////////////////////////////////
bool CSimulation::expandIndecies( ostream& osErr )
{
	bool bResult = true;
	VectorLineTokenPts::iterator it;
	CIndexFactory* pif = CIndexFactory::instance();
	list< ListLineTokenPts::iterator > vecLTP_partArrays;
	list< ListLineTokenPts::iterator >::iterator itLLNext;
	list< ListLineTokenPts::iterator >::iterator itLL;
	ListLineTokenPts::iterator itEq;
	vector< CToken >::iterator itT;
	vector< CToken* >::iterator itpTok;
	vector< CToken* >::iterator itpTok2;
	vector< CToken* >::iterator itpTok3;
	bool bFound;
	CIndex* pIndex;
	CTestHoldTokeniser cht;
	vector<CToken*> vecEmpty;
	vector<CToken*>& rvecTok = vecEmpty;
	bool bNewLines=false;
//	vector< CToken* > vecInsert;
	set< LLTPIT, ltstrListLineTokenPts > setLinesToDelete;

#ifdef DEBUGEXPAND

	ofstream osTemp;
	osTemp.open("c:\\temp\\dumpsindexdata.txt");
	ostream& osW = osTemp;
//  ostream& osW& = osErr;
#endif

	ASSERT2(pif);
	if (!pif)
		{
		SYMERRORLITE("Out of memory",errSystem);
		return false;
		}

	// make the indecies
	for (it=m_vecLinesofIntrestIn.begin();it!=m_vecLinesofIntrestIn.end();it++)
		{
		bResult &= pif->checkIndex(*it,m_pIARDataStore,osErr);
		if (bResult)
			bResult = pif->createIndex(*it,m_pIARDataStore,osErr);
		}

	if (!bResult)
		{
		pif->clear();
		return bResult;
		}


	// the fastest way to do this is to create a list of lines of interest and then maintain it
//	vecLTP_partArrays.reserve(this->m_vecLines.size()*4); // to help speed up at the expense of memory allocation

	// search for all lines with part array in which are in equation lines if interest
	for(itEq=m_vecLinesofIntrestEq.begin();itEq!=m_vecLinesofIntrestEq.end();itEq++)
		{
		itpTok=itEq->begin();
		bFound=false;
		while((itpTok!=itEq->end())&&(!bFound))
			{
			if (((*itpTok)->IsOfTypeVariable())&&(atPartOfArray==(*itpTok)->getArrayType()))
					{
					// does it have a index in it ?
					rvecTok = cht.getRefVectorOfTokenPointers((*itpTok)->getLine(),(*itpTok)->getString().getBetweenSqrBrackets().c_str(),"temp");
					if (rvecTok.size()>1) // since some arithmatic present
						bFound=true;
						else
						for(itpTok2=rvecTok.begin();(!bFound)&&(itpTok2!=rvecTok.end());itpTok2++)
							{
							if ((!(*itpTok2)->IsOfType(ctDelim))&&(pif->exists((*itpTok2)->getString().c_str())))
													bFound=true;			
							}
					}
			itpTok++;
			}

		if (bFound)
			vecLTP_partArrays.push_back(itEq); // so arrays are not copied, since equation lines in a list pointer stays valid when lines added etc
		}
/*
	Now run through each line to expand arrays if they are found in the list of indexes
	try to use variable arithmatic code to create variables etc to do the calculations
*/
//	pif->first() has already been called and returned true


	if ((!pif->first())&&(vecLTP_partArrays.size()==0))// then nothing to do, but successful anyway
		{
		pif->clear();
		return true;
		}

#ifdef DEBUGEXPAND
	writeEquationsInfo(osW,vecLTP_partArrays,"Before");
#endif

	if (pif->first()) // since will need to clean up any expressions cause by macro expansion latter
		{
			do
			{
				list< ListLineTokenPts::iterator >::iterator itLL; 
		//		vector< CToken > vecNew;
		//		bool bCopy;
		//		bool bPlus;
		//		bool bFail;
		//		long iCount =0;

				pIndex = pif->getCurrentIndex();

				if (!pIndex) // internal failure
								{
								SYMERRORLITE("Failure to correctly store index information",errInternal);
								ASSERT2(pIndex);
								return false;
								}

		#ifndef REVERSE_ORDER
				if (!pIndex->last()) // very serious
		#else
				if (!pIndex->first()) // very serious
		#endif
							{
							SYMERRORLITE2("Index found without any values, see ",pIndex->getIndexName().c_str(),errInternal); 
							return false;
							}

				do
				{

					for(itLL=vecLTP_partArrays.begin();itLL!=vecLTP_partArrays.end();itLL++)
						{
							bNewLines = false;

							
						if (!instantiateIndexEquation(pIndex,itLL,vecLTP_partArrays,bNewLines))
									return false;

							if (bNewLines)
								{
								ATLTRACE("Add this line to delete %d %s\n",(*((*itLL)->begin()))->getLine(),(*((*itLL)->begin()))->getString().c_str());
								setLinesToDelete.insert( itLL ); // get that line latter on
								}


						} // end for(itLL=vecLTP_partArrays.begin();itLL!=vecLTP_partArrays.end();itLL++)


					}
		#ifndef REVERSE_ORDER
					while(pIndex->previous());
		#else
					while(pIndex->next());
		#endif


					if (setLinesToDelete.size()>0) // last check to show 
							{
								set< LLTPIT, ltstrListLineTokenPts >::iterator itSetLL;

								ATLTRACE("Erase lines:\n");

								for (itSetLL=setLinesToDelete.begin();itSetLL!=setLinesToDelete.end();itSetLL++)
									{
									itEq = (**itSetLL);

									// before we lose track set these tokens to comment
									for(itpTok=itEq->begin();itpTok!=itEq->end();itpTok++)
										(*itpTok)->setType(ctComment);

									ATLTRACE("\tline %d %s %x ",(*(itEq->begin()))->getLine(),(*(itEq->begin()))->getString().c_str(),itSetLL);
									ATLTRACE("%x %x\n",*itSetLL,**itSetLL);
									vecLTP_partArrays.erase(*itSetLL);
									m_vecLinesofIntrestEq.erase(itEq);
									}
								
							}

			}
			while (pif->next());
		}// end if pif->first
#ifdef DEBUGEXPAND
	osW <<"< Before compute indexes:>\n";
	writeEveryEquation(osW);
#endif
	char sBuff[64];
	string sNewIndex;
#ifdef DEBUGEXPAND
	string sNew;
#endif

	for (itLL=vecLTP_partArrays.begin();itLL!=vecLTP_partArrays.end();itLL++)
		{
		for (itpTok=(*itLL)->begin();itpTok!=(*itLL)->end();itpTok++)
			{
			if (((*itpTok)->IsOfTypeVariable())&&((*itpTok)->getArrayType()==atPartOfArray))
				{ // may be of interest
					rvecTok = cht.getRefVectorOfTokenPointers((*itpTok)->getLine(),(*itpTok)->getString().getBetweenSqrBrackets().c_str(),"temp");
					if (rvecTok.size()>1) // since some arithmatic present
						{
						itpTok2 = rvecTok.begin();
						itpTok3 = rvecTok.end();
						long iIndex = CIndex::checkForExpression(itpTok2,itpTok3);				
						sNewIndex = _ltoa(iIndex,sBuff,10);
						#ifdef DEBUGEXPAND
						sNew = (*itpTok)->getString().getSubsIntoSqrBrackets(sNewIndex.c_str());
						ATLTRACE("Subs in %s to replace %s\n",sNew.c_str(),(*itpTok)->getString().c_str());
						#endif
						(*itpTok)->setString((*itpTok)->getString().getSubsIntoSqrBrackets(sBuff));
						}

				}

			}


		}


#ifdef DEBUGEXPAND
	osW <<"\n< After compute indexes:>\n";
	writeEquationsInfo(osW,vecLTP_partArrays,"After");
	writeEveryEquation(osW);
#endif


	pif->clear();

	
#ifdef DEBUGEXPAND

	osTemp.close();

#endif


	return bResult;
}

#ifdef DEBUGEXPAND

void CSimulation::writeEquationsInfo( ostream& os, list< ListLineTokenPts::iterator >& rListPtEq, const char* sTag )
{
ListLineTokenPts::const_iterator itEq;
list< ListLineTokenPts::iterator >::const_iterator itLL;
ostream_iterator<CToken> out(os,"\n"); // see p53 STL book
list<CToken>::const_iterator cit;

CToken* pT;

os << sTag<<"\n";
ATLTRACE("%s\n",sTag);
// write a copy of all equation information
os << "All equations\n";
ATLTRACE("All equations\n=============\n");
os << "=============\n";
for(itEq=m_vecLinesofIntrestEq.begin();itEq!=m_vecLinesofIntrestEq.end();itEq++)
	{
	pT = (*(itEq->begin()));
	os <<itEq->begin()<<":"<< pT->getString().c_str()<<"\t";
	ATLTRACE("%d:%s\t",itEq->begin(),pT->getString().c_str());
	}
os<<"\n";
ATLTRACE("\n");
os << "Equations with indexes\n";
os << "======================\n";
ATLTRACE("Equations with indexes\n======================\n");
for(itLL=rListPtEq.begin();itLL!=rListPtEq.end();itLL++)
	{
	pT = (*((*itLL)->begin())); 
	os << (*itLL)->begin()<<":"<<pT->getString().c_str()<<"\t";
	ATLTRACE("%d:%s\t",(*itLL)->begin(),pT->getString().c_str());
	}
os<< endl;
ATLTRACE("\n");
/*
os << "All tokens in <list> = "<<m_ltTokens.size()<<"\n"  ;
os << "==================\n";
copy(m_ltTokens.begin(),m_ltTokens.end(),out);
os << "\n";


	long iLine = NOT_DEFINED;

	for (cit=m_ltTokens.begin();cit!=m_ltTokens.end();cit++)
	{
		if (cit->getLine()!=iLine)
			{
			os <<"\n";
			iLine = cit->getLine();
			}
		os << cit->getString().c_str();
	} 
	os <<"<END>"<<endl;
*/
}


///////////////////////////////////////////////////////////
// Function name	: CSimulation::writeEveryEquation
// Description	    : Helper function
// Return type		: void 
// Argument         : ostream& os
///////////////////////////////////////////////////////////
void CSimulation::writeEveryEquation( ostream& os )
{

ListLineTokenPts::const_iterator itEq;
vector < CToken* >::const_iterator it;
long iCount=1;

os <<"\n\n** Equations in order **\n";
for( itEq=m_vecLinesofIntrestEq.begin();itEq!=m_vecLinesofIntrestEq.end();itEq++)
	{
	os << iCount++ <<":\t";
	for ( it=itEq->begin(); it!=itEq->end();it++)
		os << (*it)->getString().c_str();
	os <<"\n";
	}

os << endl;

}

#endif


///////////////////////////////////////////////////////////
// Function name	: CSimulation::instantiateIndexEquation
// Description	    : Helper function to simplify another function's code
// Return type		: bool - false if error found 
// Argument         : CIndex *pIndex
// Argument         : list< ListLineTokenPts::iterator >::iterator& ritL
///////////////////////////////////////////////////////////
bool CSimulation::instantiateIndexEquation(CIndex *pIndex, list< ListLineTokenPts::iterator >::iterator& ritLL, list< ListLineTokenPts::iterator >& rvecLTP_partArrays, bool& rbNewLines )
{

	vector< CToken > vecNew;
	vector< CToken* >::iterator itpTok;
	vector< CToken* >::iterator itpTok2;
	vector< CToken >::iterator itT;
	ListLineTokenPts::iterator itEq;
	bool bPlus;
	bool bFail;
	vector< CToken* > vecInsert;
	vector<CToken*> vecEmpty;
	vector<CToken*>& rvecTok = vecEmpty;
	CTestHoldTokeniser cht;
	long iVal;
	bool bCopy = false;
	string sNew;
	string sNewName;
	char sBuff[64];



//			vecNew.clear();
			vecNew.reserve((*ritLL)->size());
			for(itpTok=(*ritLL)->begin();itpTok!=(*ritLL)->end();itpTok++) // make sepearte copy
				#ifndef DEBUGEXPAND
				vecNew.push_back(**itpTok);
				#else
				{
				vecNew.push_back(**itpTok);
				ATLTRACE("%s",(*itpTok)->getString().c_str());
				}
			ATLTRACE("\n");
				#endif

			bPlus=true;
			bFail=false;

			for(itT=vecNew.begin();itT!=vecNew.end();itT++)
					{
					ATLTRACE("(itT) = '%s'\n",itT->getString().c_str());
					if (itT->IsOfTypeVariable())
						if (atPartOfArray==itT->getArrayType())
							{
							iVal=NOT_DEFINED;
							sNew="";

							// does it have a index in it ? at least one in this line will
							rvecTok = cht.getRefVectorOfTokenPointers(itT->getLine(),itT->getString().getBetweenSqrBrackets().c_str(),"expand");
							for(itpTok2=rvecTok.begin();itpTok2!=rvecTok.end();itpTok2++)
								{
								 ATLTRACE("	(*itpTok2) = %s\n",(*itpTok2)->getString().c_str());
								 if ((!(*itpTok2)->IsOfType(ctDelim))&&(pIndex->getIndexName().compare((*itpTok2)->getString().c_str())==0))
										{
										bCopy=true;	
										(*itpTok2)->setString(pIndex->getValueString());
										(*itpTok2)->setType(ctNumber);	
/*										if (iVal!=NOT_DEFINED) Think this is wrong need to trigger on unidentified token
											{
											sNew.append(_ltoa(iVal,sBuff,10));
											sNew.append(g_Plus);
											iVal=0;
											}*/
										}

								switch((*itpTok2)->getType())
									{
										case ctNumber:
														if (iVal==NOT_DEFINED)
															iVal = (*itpTok2)->getNumber();
															else
															if (bPlus)
																iVal += (*itpTok2)->getNumber();
																else
																iVal -= (*itpTok2)->getNumber();
														break;
										case ctDelim:	
														if ((*itpTok2)->getString().compare(g_Minus)==0)
															bPlus=false;
															else
															if ((*itpTok2)->getString().compare(g_Plus)==0)
																bPlus=true;
																else
																{
																ASSERT2(false);
																bFail = true;
																}
														break;
										case ctVariable:
										case ctNotDefined:
														if (iVal!=NOT_DEFINED)
															{
															sNew.append(_ltoa(iVal,sBuff,10));
															sNew.append(g_Plus);
															iVal=0;
															}
														sNew.append((*itpTok2)->getString());
														bPlus=true;

														break;
										default:
														ASSERT2(false);
														bFail = true;
														break;

									}




								} // end for(itpTok2=rvecTok.begin();itpTok2!=rvecTok.end();itpTok2++)
							
							if ((iVal!=NOT_DEFINED)&&(!bFail))
								{
								if (iVal!=0)
									{
									if ((sNew.size()>0)&&(iVal>0)) // then other variables etc found and a plus, rather than minus will be needed
										sNew.append(g_Plus);
									sNew.append(_ltoa(iVal,sBuff,10));
									}
									else
									{ // as zero is an index also
									if (sNew.size()==0)
										sNew.append(_ltoa(iVal,sBuff,10));
									}

								sNewName = itT->getString().getSubsIntoSqrBrackets(sNew.c_str());
								if (sNewName.size()<1)
									{
									ASSERT2(sNewName.size()>0);
									SYMERRORLITE2("Failed to read brackets values correctly ",itT->getString().c_str(),errInternal);
									return false;
									}
									else
									itT->setString(sNewName);
								}
							} // end if (atPartOfArray==(*itpTok)->getArrayType())

					} // end for(itT=vecNew.begin();itT!=vecNew.end();itT++)

		if (bCopy)
			{
				// add tokens to Token list
				//	list< ListLineTokenPts::iterator >::iterator ritLL2;
				vecInsert.clear();
				vecInsert.reserve(vecNew.size());
				for (itT=vecNew.begin();itT!=vecNew.end();itT++)
					{
					m_ltTokens.push_back(*itT); // copies token into master list
					vecInsert.push_back(&(*m_ltTokens.rbegin())); // copy the pointer to the new token
					
					}
				if (pIndex->hasExpansionPoint())
					{
					CIndexExpandPoint* pExpand = pIndex->getExpansionPoint();
					long iOffset = pExpand->addOffset();
//					ListLineTokenPts::reverse_iterator ritEq;
//					ritEq = m_vecLinesofIntrestEq.rbegin();
					if (!pIndex->getPointInEqList(itEq)) // this will only work once
							{
							itEq = m_vecLinesofIntrestEq.end();
							itEq--;
							ATLTRACE("Line beginning -> %s\n",(*(vecInsert.begin()))->getString().c_str());
							while((itEq!=m_vecLinesofIntrestEq.begin())&&(pExpand->lessThan(**(itEq->begin()))))
								itEq--;
							pIndex->setPointInEqList(itEq); // caches this so equations are not run through again
							}
					ATLTRACE("Before #Index %s line %d \n",(*(itEq->begin()))->getString().c_str(),(*(itEq->begin()))->getLine());

					if ((itEq==m_vecLinesofIntrestEq.begin())&&(pExpand->lessThan(**(itEq->begin()))))
								{
								SYMERRORTOK("Failure to place expanded index equations were requested",errInternal,pExpand->getLocationTokenPt());
								return false;
								}
						else
							{
							bool bOK = true;
							long iCount=0;
							while((bOK)&&(++iCount<=iOffset))
								{
								if (++itEq==m_vecLinesofIntrestEq.end())
									bOK=false;
								}


							if (!bOK)
								{
								m_vecLinesofIntrestEq.push_back(vecInsert);
								itEq=m_vecLinesofIntrestEq.end();
								itEq--;
								}
								else
								#ifndef NDEBUG
								{
								ATLTRACE("Before iEq %s line %d ",(*(itEq->begin()))->getString().c_str(),(*(itEq->begin()))->getLine());
								ATLTRACE("About to insert before -> %s line %d\n",(*(itEq->begin()))->getString().c_str(),(*(itEq->begin()))->getLine());
								#endif
								itEq = m_vecLinesofIntrestEq.insert(itEq,vecInsert);
								#ifndef NDEBUG
								}
								#endif

							}
					}
					else
					itEq = m_vecLinesofIntrestEq.insert(*ritLL,vecInsert);

				rvecLTP_partArrays.insert(ritLL,itEq);
//				iCount++;
			}
	rbNewLines|=bCopy;

	return true;
}


///////////////////////////////////////////////////////////
// Function name	: CSimulation::wipeFactories
// Description	    : Helper function that resets all factories 
//                    that manage the life cycle of simulation objects
// Return type		: void 
///////////////////////////////////////////////////////////
void CSimulation::wipeFactories()
{
	CCellFactory::reset();
	CEventFactory::reset();
	CEquationFactory::reset();
	CIndexFactory::reset();
	CSolClassFactory::reset();
	CStrongTypeFactory::reset();
	CVarClassFactory::reset();
	CArrayFactory::reset();


}
