// EvDump.cpp: implementation of the CEvDump class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EvDump.h"
#include <math.h>
#include "Symlix/ErrorFactory.h"

#define ERROR_UNCHECKED_FORMAT2 "Unspecified fault in event recorder event format"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*
CEvDump::CEvDump():
CEventImpl(),m_sFile(""),m_iIndexTrig(NOT_DEFINED),m_vStep(NOT_DEFINED),m_vMonitor(NOT_DEFINED),m_vecRepTok(),m_pctTrig(NULL),m_bMonitorStarted(false),m_vecResults(),m_ivecSizes(NOT_DEFINED)
{
}*/

/*CEvDump::CEvDump(const char* sFile,long iIndexTrig, variable vStep, vector<long>& vecRepIndexes ):
CEventImpl(),m_sFile(sFile),m_iIndexTrig(iIndexTrig),m_vStep(vStep),m_vMonitor(NOT_DEFINED),m_vecRepTok(),m_pctTrig(NULL),m_bMonitorStarted(false),m_vecResults(),m_ivecSizes(NOT_DEFINED)
{
	ASSERT2(m_sFile.length()>0);
	ASSERT2(vStep>0);
	ASSERT2(iIndexTrig>0);
	m_ivecSizes=vecRepIndexes.size();
	m_vecRepInd.resize(m_ivecSizes);
    m_vecResults.resize(m_ivecSizes);
	copy(vecRepIndexes.begin(),vecRepIndexes.end(),m_vecRepInd.begin());
	m_ofs.open(m_sFile.c_str());
	if (m_ofs.is_open())
		{
		m_eState=cevInitiated;
		vector< CToken* >::const_iterator cit;
		for(cit=m_vecRepTok.begin();cit!=m_vecRepTok.end();cit++)
			m_ofs << (*cit)->getString().c_str() << g_CSVDelim;
		m_ofs << endl;
		}
		else
		{
		m_sError = "Unable to open file "+m_sFile;
		m_ofs.close();
		}
}*/



CEvDump::CEvDump( long iLeft, long iRight, vector< CToken* >& vecLine,ostream& oserr):CEventImpl(),m_vecvecDump(),m_bMonitorStarted(false),m_pvecResults(NULL),m_ivecSizes(NOT_DEFINED),m_iSteps(NOT_DEFINED),m_sFile(""),m_bRecording(false)
{


if (!check(iLeft,iRight,vecLine,oserr))
	{
		m_sError = "<Internal Error#> Failed to check dump event properly before creation.";
		ASSERT2(check(iLeft,iRight,vecLine,oserr));
		m_eState = cevError; // which is set in the EventImpl - but just to be clear
		
	}
		else
	{

		long iCount = iLeft;
		long iLimit = (iRight<vecLine.size()?iRight:vecLine.size());
			
		while ((iCount!=iLimit)&&(vecLine[iCount]->getString().compare(g_As)!=0))
		{
			if (vecLine[iCount]->IsOfTypeVariable())
					m_vecRepTok.push_back(vecLine[iCount]);
		
			iCount++;
		}	
		
		m_ivecSizes = m_vecRepTok.size();
//		m_vecResults.resize(m_ivecSizes);
		
		iCount = getOneToRightOf(g_Quote,vecLine,iCount,iLimit);

		if ((iCount!=iLimit)&&(checkValidFileName(vecLine[iCount]->getString().c_str())))
				{
					m_sFile = vecLine[iCount]->getString();
				}
				else
				{
				m_eState = cevError;
				m_sError = ERROR_UNCHECKED_FORMAT2;
				}		

		iCount = getOneToRightOf(g_Last,vecLine,iCount,iLimit);

		if ((iCount!=iLimit)&&(vecLine[iCount]->IsOfType(ctNumber)))
				{
					m_iSteps = vecLine[iCount]->getNumber();
					if (m_iSteps<1)
						m_iSteps=0;
				}
				{
				m_eState = cevError;
				m_sError = ERROR_UNCHECKED_FORMAT2;
				}		

/*		iCount = getOneToRightOf(g_Every,vecLine,iCount,iLimit);

		if ((iCount!=iLimit)&&(vecLine[iCount]->IsOfType(ctNumber)))
				{
				m_vStep = vecLine[iCount]->getNumber();
				}
				{
				m_eState = cevError;
				m_sError = ERROR_UNCHECKED_FORMAT2;
				}		
*/

		if (m_iSteps<1)
			{
			m_eState = cevError;
			m_sError = "No steps requested for dump";
			}
			else
			{

				setupDump();
				/*
				setCacheToDefault();

				if (m_sFile.length()>0)
					{
					m_ofs.open(m_sFile.c_str(),ios::out);
					if (m_ofs.is_open())
						{
						m_eState=cevUninitiated;
						vector< CToken* >::const_iterator cit;
						for(cit=m_vecRepTok.begin();cit!=m_vecRepTok.end();cit++)
							m_ofs << (*cit)->getString().c_str() << g_CSVDelim;
						m_ofs << endl;
						m_eState = cevUninitiated;
						}
						else
						{
						m_sError = "Unable to open file "+m_sFile;
						m_ofs.close();
						}
					}*/
			}
	}
}



///////////////////////////////////////////////////////////
// Function name	: CEvDump::setupDump
// Description	    : Helper function to open file
// Return type		: void 
///////////////////////////////////////////////////////////
void CEvDump::setupDump()
{
	if (m_bRecording)
		closeDump();

		setCacheToDefault();

		if (m_sFile.length()>0)
			{
			m_ofs.open(m_sFile.c_str(),ios::out);
			if (m_ofs.is_open())
						{
						m_eState=cevUninitiated;
						vector< CToken* >::const_iterator cit;
						for(cit=m_vecRepTok.begin();cit!=m_vecRepTok.end();cit++)
							m_ofs << (*cit)->getString().c_str() << g_CSVDelim;
						m_ofs << endl;
						m_eState = cevUninitiated;
						m_bRecording=true;
						}
						else
						{
						m_sError = "Unable to open file "+m_sFile;
						m_ofs.close();
						m_bRecording=false;
						}
			}

}


///////////////////////////////////////////////////////////
// Function name	: CEvDump::closeDump
// Description	    : 
// Return type		: void 
///////////////////////////////////////////////////////////
void CEvDump::closeDump()
{
	char sDump[32];
	
	if (m_ofs.is_open()) // and it shoudl be !
		{
		ostream_iterator<variable> out(m_ofs,g_CSVDelim); // see p53 STL book


		if ((m_eState==cevInitiated)&&(m_vecvecDump.size()>0))
			{
			vector< vector< variable > >::iterator itStart;
			vector<variable>::const_iterator cit;

/*			if (m_itvecvecDump==m_vecvecDump.begin())
					m_itvecvecDump=m_vecvecDump.end();*/
						
			itStart = m_itvecvecDump;

				do
				{

					if (*(m_itvecvecDump->begin())!=NOT_DEFINED)
						{
						for (cit = m_itvecvecDump->begin();cit!=m_itvecvecDump->end();cit++)
								{
								 sprintf(sDump,"%.20g",(*cit));
//								 m_ofs << double(*cit)<<g_CSVDelim;
								 m_ofs <<sDump<<g_CSVDelim;
								}
						m_ofs<<endl; 
						}

					if (++m_itvecvecDump==m_vecvecDump.end())
						m_itvecvecDump=m_vecvecDump.begin();
				}
				while(m_itvecvecDump!=itStart); // repeat untill all dumped

			}
			else
			{
			SYMERRORLITE("No data found to dump - run not started",errWarning);
			m_ofs << "Error in dumping data.\n";
			}
	

			m_ofs.close();
			m_bRecording = false;
		}


}

///////////////////////////////////////////////////////////
// Function name	: CEvDump::~CEvDump
// Description	    : Destructor that also dumps last steps to file
//                    the aim is to allow tracing in the event of failures
// Return type		: 
///////////////////////////////////////////////////////////
CEvDump::~CEvDump()
{

	closeDump();
	/*
	if (m_ofs.is_open()) // and it shoudl be !
		{
		ostream_iterator<variable> out(m_ofs,g_CSVDelim); // see p53 STL book


		if ((m_eState==cevInitiated)&&(m_vecvecDump.size()>0))
			{
			vector< vector< variable > >::iterator itStart;
			vector<variable>::const_iterator cit;

						
			itStart = m_itvecvecDump;

				do
				{

					if (*(m_itvecvecDump->begin())!=NOT_DEFINED)
						{
						for (cit = m_itvecvecDump->begin();cit!=m_itvecvecDump->end();cit++)
								 m_ofs << float(*cit)<<g_CSVDelim;
						m_ofs<<endl; 
						}

					if (++m_itvecvecDump==m_vecvecDump.end())
						m_itvecvecDump=m_vecvecDump.begin();
				}
				while(m_itvecvecDump!=itStart); // repeat untill all dumped

			}
			else
			{
			SYMERRORLITE("No data found to dump - run not started",errWarning);
			m_ofs << "Error in dumping data.\n";
			}
	

			m_ofs.close();
		}
		*/

}




///////////////////////////////////////////////////////////
// Function name	: CEvDump::trigger
// Description	    : Always returns no trigger - but records values in a cache
//                    that over writes itself.
// Return type		: eEventSignal 
// Argument         :  vector< variable >* pvecVars
// Argument         : vector< variable >* pvecVarsLast
///////////////////////////////////////////////////////////
eEventSignal CEvDump::trigger( vector< variable >* pvecVars, vector< variable >*   )
{
	eEventSignal eesResult = ceesNoTrig; // always claims not have been triggered, but keeps a copy


	// copy value to next vector then step alone one
	if (m_eState==cevInitiated)
		{
		for(long iCount=0;iCount<m_ivecSizes;iCount++)
				(*m_itvecvecDump)[iCount] = (*pvecVars)[m_vecRepInd[iCount]];
		if (++m_itvecvecDump==m_vecvecDump.end())
			m_itvecvecDump=m_vecvecDump.begin(); // keeps rolling forward.
		}

	return eesResult;
}




///////////////////////////////////////////////////////////
// Function name	: CEvDump::check
// Description	    : 
// Return type		: bool 
// Argument         : long iLeft
// Argument         : long iRight
// Argument         : vector<CToken*>& vExpLine
// Argument         : ostream& osErrReport
///////////////////////////////////////////////////////////
bool CEvDump::check(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport )
{
	vector< CToken* >::iterator itpCT;
	// itpCTRight is fouud this way as I'm not sure &vExp[iRight] would produce the same result in all conditions
	vector< CToken* >::const_iterator itpCTRight = getRightWithoutComments(iLeft,iRight,vExpLine);
	bool bResult = true;
	bool bDelim =true;


	if (iLeft==iRight) // may not be necessary as doesn't seem to get here.
			return false;

	if (iLeft>=vExpLine.size())
			{
			ATLTRACE("iLeft was %d and vExpLine.Sixe() was %d\n",iLeft,vExpLine.size());
			SYMERRORLITE("Unexpacted error creating a Dump event",errInternal);
			return false;
			}

	itpCT = &vExpLine[iLeft];

	if (iRight-iLeft<5)
			{
			SYMERRORTOK("Event declartion not complete.",errSyntax,(*itpCT));
			return false;
			}


	while((itpCT!=itpCTRight)&&(((*itpCT)->getStringRef().compare(g_As)!=0)&&((*itpCT)->getStringRef().compare(g_Quote)!=0)))
	{
		if (bDelim)
			{
			if ((*itpCT)->IsOfTypeVariable())
				bDelim=false; // should be a ctDelim next
				else
				{
				bResult=false; // fail this check
				osErrReport << "<Error*> 2 deliminators next to each other - see '"<<(*itpCT)->getStringRef().c_str()<< "' on line "<< (*itpCT)->getLine()<<endl;
				SYMERRORTOK("Two operators next to each other",errSyntax,(*itpCT));
				}			
			}
			else
			{
			if ((*itpCT)->IsOfType(ctDelim))
				bDelim=true;
				else
				{
				bResult=false;
				osErrReport << "<Error*> 2 variables next to each other - see '"<<(*itpCT)->getStringRef().c_str()<< "' on line "<< (*itpCT)->getLine()<<endl;
				SYMERRORTOK("Two variables next to each other",errSyntax,(*itpCT));
				}

			}
		itpCT++;
	}

	if (itpCT==itpCTRight)
		{
		SYMERRORTOK("Part of event statement is missing",errSyntax,(*--itpCT));
		osErrReport << "<Error*> Part of event statement is missing on line "<<(*itpCT)->getLine()<<endl;
		bResult=false;
		}

	if (!bResult)
			return bResult;

	if ((*itpCT)->getString().compare(g_As)==0)
			itpCT++;
			else
			{
			osErrReport << "<Error*> Part of event statement is missing the term '"<< g_As<<"' on line "<<(*itpCT)->getLine()<<endl;
			SYMERRORTOK2("Part of event statement is missing the term ",g_As,errSyntax,(*itpCT));
			return false;
			}


	if (itpCT==itpCTRight)
			{
			SYMERRORTOK("Part of event statement is missing",errSyntax,(*--itpCT));
			osErrReport << "<Error*> Part of event statement is missing on line "<<(*itpCT)->getLine()<<endl;
			return false;
			}

	if (!((*itpCT)->getString().compare(g_Quote)==0))
			{
			osErrReport << "<Error*> File name not in quotes on line "<<(*itpCT)->getLine()<<endl;
			SYMERRORTOK("Stream name not in quotes",errSyntax,(*itpCT));
			return false;
			}

	if (++itpCT==itpCTRight)
			{
			SYMERRORTOK("Part of event statement is missing",errSyntax,(*--itpCT));
			osErrReport << "<Error*> Part of event statement is missing on line "<<(*itpCT)->getLine()<<endl;
			return false;
			}

	if (!(*itpCT)->IsOfType(ctName))
			{
			osErrReport << "<Error*> Part of event statement is missing on line "<<(*itpCT)->getLine()<<endl;
			SYMERRORTOK("Part of event statement is missing",errSyntax,(*itpCT));
			return false;
			}

	if (++itpCT==itpCTRight)
			{
			SYMERRORTOK("Part of event statement is missing",errSyntax,(*--itpCT));
			osErrReport << "<Error*> Part of event statement is missing on line "<<(*itpCT)->getLine()<<endl;
			return false;
			}

	if (!((*itpCT)->getString().compare(g_Quote)==0))
			{
			osErrReport << "<Error*> File name not in quotes on line "<<(*itpCT)->getLine()<<endl;
			SYMERRORTOK("Stream name not in quotes",errSyntax,(*itpCT));
			return false;
			}

	if (++itpCT==itpCTRight)
			{
			SYMERRORTOK("Part of event statement is missing",errSyntax,(*--itpCT));
			osErrReport << "<Error*> Part of event statement is missing on line "<<(*itpCT)->getLine()<<endl;
			return false;
			}

	if (!((*itpCT)->getString().compare(g_For)==0))
			{
			osErrReport << "<Error*> Omission of key word '"<< g_For<<"' on line "<<(*itpCT)->getLine()<<endl;
			SYMERRORTOK2("Key word missing: ",g_For,errSyntax,(*itpCT));
			return false;
			}
	
	if (++itpCT==itpCTRight)
			{
			SYMERRORTOK("Part of event statement is missing",errSyntax,(*--itpCT));
			osErrReport << "<Error*> Part of event statement is missing on line "<<(*itpCT)->getLine()<<endl;
			return false;
			}

	if (!((*itpCT)->getString().compare(g_Last)==0))
			{
			osErrReport << "<Error*> Omission of key word '"<< g_Last<<"' on line "<<(*itpCT)->getLine()<<endl;
			SYMERRORTOK2("Key word missing: ",g_Last,errSyntax,(*itpCT));
			return false;
			}
	
	if (++itpCT==itpCTRight)
			{
			SYMERRORTOK("Part of event statement is missing",errSyntax,(*--itpCT));
			osErrReport << "<Error*> Part of event statement is missing on line "<<(*itpCT)->getLine()<<endl;
			return false;
			}
			
	if (!((*itpCT)->IsOfType(ctNumber)))
			{
			osErrReport << "<Error*> Omission of integer on line "<<(*itpCT)->getLine()<<endl;
			SYMERRORTOK("Integer missing",errSyntax,(*itpCT));
			return false;
			}

	if (++itpCT==itpCTRight)
			{
			SYMERRORTOK("Part of event statement is missing",errSyntax,(*--itpCT));
			osErrReport << "<Error*> Part of event statement is missing on line "<<(*itpCT)->getLine()<<endl;
			return false;
			}

	// accept g_Step also in case of one
	if ((!((*itpCT)->getString().compare(g_Steps)==0))&&(!((*itpCT)->getString().compare(g_Step)==0)))
			{
			osErrReport << "<Error*> Omission of key word '"<< g_Steps<<"' on line "<<(*itpCT)->getLine()<<endl;
			SYMERRORTOK2("Missing key word: ",g_Steps,errSyntax,(*itpCT));
			return false;
			}


	

	return bResult;
}

bool CEvDump::setupEvent(list<CEquation*>* pvecpEquations)
{

	ASSERT2(m_ivecSizes!=NOT_DEFINED);
//	ASSERT2(m_vecResults.size()==m_ivecSizes);
	
	if (isInError())
		return false;

	if (m_eState==cevUninitiated)
		{
		vector< CToken* >::const_iterator cit;
		

		for (cit=m_vecRepTok.begin();cit!=m_vecRepTok.end();cit++)
				{
				ASSERT2((*cit)->getRootTokenPt()->getIndex()!=NOT_DEFINED);
				if ((*cit)->getRootTokenPt()->getIndex()==NOT_DEFINED) // to protect release version
						return false;
				m_vecRepInd.push_back((*cit)->getRootTokenPt()->getIndex());
				}

		if (m_vecRepInd.size()>0)
				m_eState = cevInitiated;

		}


	return m_eState == cevInitiated;

}


///////////////////////////////////////////////////////////
// Function name	: CEvDump::setCacheToDefault
// Description	    : here rather than reset as used in constructor
//                    and other functionality might be added to reset
//                    latter on
// Return type		: void 
///////////////////////////////////////////////////////////
void CEvDump::setCacheToDefault()
{
	ASSERT2(m_ivecSizes>0);
	ASSERT2(m_iSteps>=0);

	vector< variable > vec;
	vec.resize(m_ivecSizes,NOT_DEFINED);

	m_vecvecDump.resize(m_iSteps);
	for (m_itvecvecDump=m_vecvecDump.begin();m_itvecvecDump!=m_vecvecDump.end();m_itvecvecDump++)
			(*m_itvecvecDump) = vec;

	m_itvecvecDump = m_vecvecDump.begin(); // to start it off
}


///////////////////////////////////////////////////////////
// Function name	: CEvDump::reset
// Description	    : 
// Return type		: void 
///////////////////////////////////////////////////////////
void CEvDump::reset()
{

	setCacheToDefault();

}


///////////////////////////////////////////////////////////
// Function name	: CEvDump::simulationEnd
// Description	    : Lets close the dump
// Return type		: void 
// Argument         : vector< variable >& rvecVars
///////////////////////////////////////////////////////////
void CEvDump::simulationEnd(vector< variable >& rvecVars)
{

	closeDump();

}