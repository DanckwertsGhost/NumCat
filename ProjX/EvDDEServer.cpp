// EvDDEServer.cpp: implementation of the CEvDDEServer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EvDDEServer.h"
#include <math.h>
#include "Symlix/ErrorFactory.h"

//declare
void DDEThread1(void* pParams);


#define ERROR_UNCHECKED_FORMAT3 "Unspecified fault in event DDEServer event format"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



CEvDDEServer::CEvDDEServer( long iLeft, long iRight, vector< CToken* >& vecLine,ostream& oserr):m_vecRepTok(),m_vecResults(),m_ivecSizes(NOT_DEFINED),m_vDDETimeStep(NOT_DEFINED),m_sServer(""),m_bNotRunning(true),m_pDDEServerData(NULL)
{

	m_eState = cevUninitiated;
	ASSERT2(check(iLeft,iRight,vecLine,oserr));
	if (!check(iLeft,iRight,vecLine,oserr))
		{
		m_sError = "<Internal Error#> Unable to intialise "; // error mesage handled elsewhere
		m_sError.append(g_DDEserver);
		m_sError.append(" event.");
		m_eState = cevError;
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
			m_vecResults.resize(m_ivecSizes);
			
			iCount = getOneToRightOf(g_Quote,vecLine,iCount,iLimit);

			if (iCount!=iLimit)
					{
						m_sServer = vecLine[iCount]->getString();
					}
					else
					{
					m_eState = cevError;
					m_sError = ERROR_UNCHECKED_FORMAT3;
					}		

			iCount = getOneToRightOf(g_Every,vecLine,iCount,iLimit);

			if ((iCount!=iLimit)&&(vecLine[iCount]->IsOfType(ctNumber)))
					{
					 m_vDDETimeStep = vecLine[iCount]->getNumber();
					}
					else
					{
					m_eState = cevError;
					m_sError = ERROR_UNCHECKED_FORMAT3;
					}		

		} // end 	if (!check(iLeft,iRight,vecLine,oserr))

	m_pDDEServerData = newtrack CDDEServerData(this);

}


CEvDDEServer::~CEvDDEServer()
{

//	reset(); 

	closeDDEServer();

	delete m_pDDEServerData;
}


///////////////////////////////////////////////////////////
// Function name	: CEvDDEServer::closeDDEServer
// Description	    : Helper function to end DDE and Timer window
// Return type		: void 
///////////////////////////////////////////////////////////
void CEvDDEServer::closeDDEServer()
{

	if ((m_pDDEServerData)&&(!m_bNotRunning))
		{
		ATLTRACE("closeDDEServer called\n");
		m_pDDEServerData->SendEndOfSimulation();
		/*
		if (!m_pDDEServerData->sendEndDDEServerAndWait(10000))
				{
				ATLTRACE("SendEndOfSimulation() Time out - failed to stop window");

				}			
//		m_pDDEServerData->SendEndOfSimulation();*/
		m_bNotRunning = true;
		}
		else
		ATLTRACE("closeDDEServer called - no action\n");


}



///////////////////////////////////////////////////////////
// Function name	: CEvDDEServer::trigger
// Description	    : 
// Return type		: eEventSignal 
// Argument         :  vector< variable >* pvecVars
// Argument         : vector< variable >* pvecVarsLast
///////////////////////////////////////////////////////////
eEventSignal CEvDDEServer::trigger( vector< variable >* pvecVars, vector< variable >* pvecVarsLast  )
{
	ASSERT2(m_pDDEServerData);

	if (!m_pDDEServerData)
		{
		m_eState = cevError;
		m_sError ="<Internal Error#>  The software has exposed an internal fault - please report this.";
		}


	if (m_eState!=cevInitiated)
		  return ceesNoTrig;


	if (m_bNotRunning)
		if (!launchDDEServer())
			{
			m_eState = cevError;
			m_sError="<Error#> DDE server failed to start.";
			return ceesNoTrig;
			}

	CCritCheck cs(m_pDDEServerData->getCriticalSection()); // data update must ensure all DDE update from same time tick

	vector< long >::const_iterator cit;
	vector< variable >::iterator itV = m_vecResults.begin();

	ASSERT2(m_vecResults.size()==m_vecRepInd.size());// or else its going to get messy

	if (m_vecResults.size()!=m_vecRepInd.size())
			{
			m_eState = cevError;
			m_sError = "<Internal Error#> The software has exposed an internal fault - please report this.";
			return ceesNoTrig;
			}

 
 	for(cit = m_vecRepInd.begin();cit!=m_vecRepInd.end();cit++)
		(*itV++)=(*pvecVars)[*cit];

		
	ASSERT2(itV==m_vecResults.end()); // should be the case

	return ceesTrig;
}







///////////////////////////////////////////////////////////
// Function name	: CEvDDEServer::check
// Description	    : 
// Return type		: bool 
// Argument         : long iLeft
// Argument         : long iRight
// Argument         : vector<CToken*>& vExpLine
// Argument         : ostream& osErrReport
///////////////////////////////////////////////////////////
bool CEvDDEServer::check(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport )
{
	vector< CToken* >::iterator itpCT;
	// itpCTRight is fouud this way as I'm not sure &vExp[iRight] would produce the same result in all conditions
	vector< CToken* >::const_iterator itpCTRight = getRightWithoutComments(iLeft,iRight,vExpLine);
	bool bResult = true;
	bool bDelim =true;

	itpCT = &vExpLine[iLeft];

	if (iLeft==iRight) // may not be necessary as doesn't seem to get here.
			return false;

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
				SYMERRORTOK("Need to check operators, was expecting a variable",errSyntax,(*itpCT));
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
				SYMERRORTOK("Need to check variable, two next to each other",errSyntax,(*itpCT));
				}

			}
		itpCT++;
	}

	if (itpCT==itpCTRight)
		{
		osErrReport << "<Error*> Part of event statement is missing on line "<<(*itpCT)->getLine()<<endl;
		SYMERRORTOK("Part of event statement is missing",errSyntax,(*itpCT));
		bResult=false;
		}

	if (!bResult)
			return bResult;

	if ((*itpCT)->getString().compare(g_As)==0)
			itpCT++;
			else
			{ // must have this as constructor relies upon it
			osErrReport << "<Error*> Part of event statement is missing the term '"<< g_As<<"' on line "<<(*itpCT)->getLine()<<endl;
			SYMERRORTOK("Part of event statement is missing",errSyntax,(*itpCT));
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
			SYMERRORTOK("File name not in quotes",errSyntax,(*itpCT));
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
			SYMERRORTOK("File name not in quotes",errSyntax,(*itpCT));
			return false;
			}

	if (++itpCT==itpCTRight)
			{
			SYMERRORTOK("Part of event statement is missing",errSyntax,(*--itpCT));
			osErrReport << "<Error*> Part of event statement is missing on line "<<(*itpCT)->getLine()<<endl;
			return false;
			}

	if (!((*itpCT)->getString().compare(g_Every)==0))
			{
			osErrReport << "<Error*> Omission of key word "<< g_Every<<" on line "<<(*itpCT)->getLine()<<endl;
			SYMERRORTOK2("Omission of key word ",g_Every,errSyntax,(*itpCT));
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
			osErrReport << "<Error*> Omission of key variable on line "<<(*itpCT)->getLine()<<endl;
			SYMERRORTOK("Omission of a number",errSyntax,(*itpCT));
			return false;
			}

	if (((*itpCT)->getNumber()==NOT_FOUND)||((*itpCT)->getNumber()<0))
			{
			osErrReport << "<Error*> Time gap is incorrect at line "<<(*itpCT)->getLine()<<endl;
			SYMERRORTOK("Time gap is incorrect",errSyntax,(*itpCT));
			return false;
			}

	if (++itpCT==itpCTRight)
			{
			SYMERRORTOK("Part of event statement is missing",errSyntax,(*--itpCT));
			osErrReport << "<Error*> Part of event statement is missing on line "<<(*itpCT)->getLine()<<endl;
			return false;
			}

	if (!(((*itpCT)->getString().compare(g_Secs)==0)||((*itpCT)->getString().compare(g_Sec)==0)))
			{
			osErrReport << "<Error*> Omission of key word "<< g_Secs<<" or "<< g_Sec <<" on line "<<(*itpCT)->getLine()<<endl;
			SYMERRORTOK2("Omission of key word ",g_Secs,errSyntax,(*itpCT));
			return false;
			}	

	return bResult;
}


///////////////////////////////////////////////////////////
// Function name	: CEvDDEServer::setupEvent
// Description	    : 
// Return type		: bool 
// Argument         : list<CEquation*>* pvecpEquations
///////////////////////////////////////////////////////////
bool CEvDDEServer::setupEvent(list<CEquation*>* pvecpEquations)
{

	ASSERT2(m_ivecSizes!=NOT_DEFINED);
	ASSERT2(m_vecResults.size()==m_ivecSizes);
	
	if (isInError())
		return false;

	if (m_eState==cevUninitiated)
		{
		vector< CToken* >::const_iterator cit;
		CCritCheck cs(m_pDDEServerData->getCriticalSection()); // just to be sure
		
		// because by this time the information now exists
		long iCount =0;
		for (cit=m_vecRepTok.begin();cit!=m_vecRepTok.end();cit++)
				{
				ASSERT2((*cit)->getRootTokenPt()->getIndex()!=NOT_DEFINED);
				if ((*cit)->getRootTokenPt()->getIndex()==NOT_DEFINED) // to protect release version
						return false;
				m_vecRepInd.push_back((*cit)->getRootTokenPt()->getIndex());
				m_mapWatches[(*cit)->getStringRef()] = iCount++;
				}

		if (m_vecRepInd.size()>0)
				m_eState = cevInitiated;

		}


	return m_eState == cevInitiated;

}


///////////////////////////////////////////////////////////
// Function name	: CEvDDEServer::launchDDEServer
// Description	    : 
// Return type		: bool 
///////////////////////////////////////////////////////////
bool CEvDDEServer::launchDDEServer()
{
	if (m_bNotRunning)
		m_bNotRunning=false;
		else
		return false; // can only do this once

	unsigned long ithrd = _beginthread(DDEThread1,0,m_pDDEServerData);
	if (ithrd==-1) // then thread has failed
		{
		 // failed
		return false;
		}

	return true;

}


///////////////////////////////////////////////////////////
// Function name	: CEvDDEServer::findVariable
// Description	    : Return true if finds variable
// Return type		: bool 
// Argument         : const char* sVar
///////////////////////////////////////////////////////////
bool CEvDDEServer::findVariable( const char* sVar)
{
	if (m_eState!=cevInitiated)
		return false; // do no more

	if (m_mapWatches.find(sVar)!=m_mapWatches.end())
		return true;

	return false;

}


///////////////////////////////////////////////////////////
// Function name	: CEvDDEServer::getSizeResults const
// Description	    : 
// Return type		: long 
///////////////////////////////////////////////////////////
long CEvDDEServer::getSizeResults() const
{
	CCritCheck cs(m_pDDEServerData->getCriticalSection());
	return m_vecResults.size();
}



///////////////////////////////////////////////////////////
// Function name	: CEvDDEServer::getValue
// Description	    : 
// Return type		: variable 
// Argument         : const char* sVar
///////////////////////////////////////////////////////////
variable CEvDDEServer::getValue( const char* sVar) const
{
	MapStringDDE::const_iterator cit = m_mapWatches.find(sVar);

	if (cit==m_mapWatches.end())
			return NOT_DEFINED;

	return m_vecResults[cit->second];
}



///////////////////////////////////////////////////////////
// Function name	: CEvDDEServer::updateWithResults
// Description	    : Assumes order in vecResults as in internal copy
//                    need map of values to locate the correct items.
// Return type		: bool 
// Argument         : vector<variable>& vecResults
///////////////////////////////////////////////////////////
bool CEvDDEServer::updateWithResults( vector<variable>& vecResults) const
{

	ASSERT2(vecResults.size()==m_ivecSizes); // this really should be true
	if (vecResults.size()!=m_ivecSizes)
			vecResults.resize(m_ivecSizes,NOT_DEFINED);

	CCritCheck cs(m_pDDEServerData->getCriticalSection());

	copy(m_vecResults.begin(),m_vecResults.end(),vecResults.begin());

	return true;
}


///////////////////////////////////////////////////////////
// Function name	: CEvDDEServer::copyIndexMap
// Description	    : 
// Return type		: bool 
// Argument         : MapStringDDE newMap
///////////////////////////////////////////////////////////
bool CEvDDEServer::copyIndexMap(MapStringDDE& newMap) const
{

	if (m_mapWatches.size()==0)
		return false;

	newMap = m_mapWatches;

	return true;
}


///////////////////////////////////////////////////////////
// Function name	: CEvDDEServer::reset
// Description	    : 
// Return type		: void 
///////////////////////////////////////////////////////////
void CEvDDEServer::reset()
{



//	m_mapWatches.clear();


}

void CEvDDEServer::simulationEnd()
{
	closeDDEServer(); // checks if launched with bool flag

}


