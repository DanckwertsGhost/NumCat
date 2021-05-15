// EvRecorder.cpp: implementation of the CEvRecorder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EvRecorder.h"
#include <math.h>
#include "Symlix/ErrorFactory.h"

#define ERROR_UNCHECKED_FORMAT2 "Unspecified fault in event recorder event format"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEvRecorder::CEvRecorder():
CEventImpl(),m_sFile(""),m_iIndexTrig(NOT_DEFINED),m_vStep(NOT_DEFINED),m_vMonitor(NOT_DEFINED),m_vecRepTok(),m_pctTrig(NULL),m_bMonitorStarted(false),m_vecResults(),m_ivecSizes(NOT_DEFINED),m_pIARWriteStream(NULL),m_bReport(true)
{
}
/*
CEvRecorder::CEvRecorder(const char* sFile,long iIndexTrig, variable vStep, vector<long>& vecRepIndexes ):
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
		m_sError = "Unable to open stream "+m_sFile;
		m_ofs.close();
		}
}*/

CEvRecorder::CEvRecorder( long iLeft, long iRight, vector< CToken* >& vecLine, IARDataStore* pIARDataStore, ostream& oserr):m_vecRepTok(),m_pctTrig(NULL),m_vStep(-1),m_vMonitor(NOT_DEFINED),m_bMonitorStarted(false),m_vecResults(),m_ivecSizes(NOT_DEFINED),m_pIARWriteStream(NULL),m_bReport(true)
{

	ASSERT2(check(iLeft,iRight,vecLine,pIARDataStore,oserr));
	if (!check(iLeft,iRight,vecLine,pIARDataStore,oserr))
		{
		m_sError = "<Internal Error#> Unable to intialise ";
		m_sError.append(g_Record);
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

			if ((iCount!=iLimit)&&(checkValidFileName(vecLine[iCount]->getString().c_str())))
					{
						m_sFile = vecLine[iCount]->getString();
					}
					else
					{
					m_eState = cevError;
					m_sError = ERROR_UNCHECKED_FORMAT2;
					}		

			iCount = getOneToRightOf(g_For,vecLine,iCount,iLimit);

			if ((iCount!=iLimit)&&(vecLine[iCount]->IsOfTypeVariable()))
					{
					 m_pctTrig = vecLine[iCount]->getRootTokenPt();
					}
					else
					{
					m_eState = cevError;
					m_sError = ERROR_UNCHECKED_FORMAT2;
					}		

			iCount = getOneToRightOf(g_Every,vecLine,iCount,iLimit);

			if ((iCount!=iLimit)&&(vecLine[iCount]->IsOfType(ctNumber)))
					{
					m_vStep = vecLine[iCount]->getNumber();
					}
					else
					{
					m_eState = cevError;
					m_sError = ERROR_UNCHECKED_FORMAT2;
					}		

			if ((m_sFile.length()>0)&&(m_pctTrig)&&(m_vStep>0))
				{
				CComBSTR cbFileName(m_sFile.c_str());
				HRESULT hr = pIARDataStore->tryToGetARWriteStream(&(cbFileName.m_str),formatCSV,&m_pIARWriteStream);
				
				if FAILED(hr)
					{
					m_sError ="Problem retrieving stream"+m_sFile;
					m_eState = cevError;
					}
					else
					{
					if (!m_pIARWriteStream)
						{
						SYMERRORLITE2("Unable to create stream ",m_sFile.c_str(),errSystem);
						m_sError ="Problem retrieving stream"+m_sFile;
						m_eState = cevError;
						}
						else
						{
						#ifndef NDEBUG
						m_pIARWriteStream->AddRef();
						ATLTRACE("The remaining count is %d\n",m_pIARWriteStream->Release());
						#endif
						enumARStream ess;
						CComBSTR cbLine;
						m_eState=cevUninitiated;
						vector< CToken* >::const_iterator cit;
						for(cit=m_vecRepTok.begin();cit!=m_vecRepTok.end();cit++)
							{
							cbLine.Append((*cit)->getString().c_str());
							cbLine.Append(g_CSVDelim);
							}
						hr = m_pIARWriteStream->writeLine(&(cbLine.m_str),&ess);
						if (FAILED(hr))
								{
								SYMERRORLITE2("Unexpected failure to write line to stream ",m_sFile.c_str(),errSystem);
								m_sError ="Problem retrieving stream"+m_sFile;
								m_eState = cevError;
								}
								else
								if (ess!=streamWriteLine)
									{
									SYMERRORLITE2("Unexpected failure to write line to stream ",m_sFile.c_str(),errSystem);
									m_sError ="Problem retrieving stream"+m_sFile;
									m_eState = cevError;
									}


						} //	end	if (!m_pIARWriteStream)


					} // end 	if FAILED(hr)


			} // end 	if ((m_sFile.length()>0)&&(m_pctTrig)&&(m_vStep>0))

		} // end if(!check(iLeft,iRight,vecLine,oserr))
}


CEvRecorder::~CEvRecorder()
{

}


///////////////////////////////////////////////////////////
// Function name	: CEvRecorder::finalRelease
// Description	    : Release intrest in any COM objects
// Return type		: void 
///////////////////////////////////////////////////////////
void CEvRecorder::finalRelease()
{

	enumARStream ess;

	if (m_pIARWriteStream) // tempory measue whilst sort of problem
	{

	HRESULT hr = m_pIARWriteStream->closeStream(&ess);

	if (FAILED(hr))
		{
		SYMERRORLITE2("Unhandled error when trying to close stream : ",m_sFile.c_str(),errSystem);
		}
	}


#ifndef NDEBUG
	long iCount;
	if (m_pIARWriteStream)
		{
		iCount = m_pIARWriteStream->AddRef();
		iCount = m_pIARWriteStream->Release();
		iCount = m_pIARWriteStream->Release();
		ATLTRACE("IARWriteStream count on close %d\n",iCount);
		m_pIARWriteStream=NULL;
		}
#else
	if (m_pIARWriteStream)
		{
		m_pIARWriteStream->Release();
		m_pIARWriteStream=NULL;
		}
#endif


}



eEventSignal CEvRecorder::trigger( vector< variable >* pvecVars, vector< variable >* pvecVarsLast  )
{
	eEventSignal eesResult = trigCalc(pvecVars,pvecVarsLast);
//	ostream_iterator<variable> out(m_ofs,g_CSVDelim); // see p53 STL book


	if ((eesResult==ceesTrig)&&(m_bReport))
		{
//		Then write results
		CComBSTR cbLine;
		enumARStream ess;
		for (vector<variable>::const_iterator cit = m_vecResults.begin();cit!=m_vecResults.end();cit++)
				{
				cbLine.Append(_gcvt((*cit),SIZE_BUFFER_CONV,m_sTemp));
				cbLine.Append(g_CSVDelim);
				}
			ASSERT2(m_pIARWriteStream);
			if (!m_pIARWriteStream)
				{
				SYMERRORLITE("Write stream has been lost by event recorder",errInternal);
				m_bReport = false; // to avoid repeating this error many times
				}
				else
				{
				HRESULT hr = m_pIARWriteStream->writeLine(&(cbLine.m_str),&ess);
				if (FAILED(hr))
						{
						ATLTRACE("Error on write to stream %d",hr);
						SYMERRORLITE("Error on write to stream from record event",errSystem);
						m_bReport = false;
						}
						else
						if (ess!=streamWriteLine)
							{
							ATLTRACE("Error on write to stream - ess = %d",ess);
							SYMERRORLITE("Error on write to stream from record event",errSystem);
							m_bReport = false;
							}
				}
				
		}
	return eesResult;
}

eEventSignal CEvRecorder::trigCalc( vector< variable >* pvecVars, vector< variable >* pvecVarsLast )
{

	if (!pvecVarsLast) // then no recording possible
		return ceesNoTrig;

	if ((!m_bMonitorStarted)&&(m_vMonitor==NOT_DEFINED))
		{
		m_bMonitorStarted = true; // so only do this once	
		m_vMonitor=(*pvecVars)[m_iIndexTrig];
		return ceesNoTrig; // may wish to change this as it doesn't record starting point
		}

	if (willTrigger(pvecVars))
		{
		//vector< long >::const_iterator cit;
		long iCount;
		variable vSign;
		variable vFrac;

		vFrac = (*pvecVarsLast)[m_iIndexTrig] - (*pvecVars)[m_iIndexTrig];

		if (vFrac==0) // since willTrigger should catch this this should not happen, but handle anyway then allow failure
			{
//			m_ofs << "Attempt to divide by zero - error in code to allow this. Please report.\n";m_ofs.flush();// as error will be triggered shortly
			cerr << "<Error*> Attempt to divide by zero - error in code to allow this. Please report.\n";// as error will be triggered shortly
			cerr << "(*pvecVarsLast)[m_iIndexTrig] :"<<(*pvecVarsLast)[m_iIndexTrig]<<"\t(*pvecVars)[m_iIndexTrig] :"<<(*pvecVars)[m_iIndexTrig]<<endl;
			SYMERRORLITE("Divide by zero caught from event recorder",errInternal);
			ASSERT2(false);
			}

		vFrac = (m_vMonitor - (*pvecVars)[m_iIndexTrig])/vFrac;


		if (vFrac==1) // then this can all be done much faster - but may hardly ever evaluate. Need to think if a threshold isn't needed here
			{
			for(iCount=0;iCount<m_ivecSizes;iCount++)
				m_vecResults[iCount] = (*pvecVarsLast)[m_vecRepInd[iCount]];
			}
			else
			{
			for(iCount=0;iCount<m_ivecSizes;iCount++)
				m_vecResults[iCount] = (*pvecVars)[m_vecRepInd[iCount]]+((*pvecVarsLast)[m_vecRepInd[iCount]]-(*pvecVars)[m_vecRepInd[iCount]])*vFrac;
			}

		// now adjust for the next trigger
		if (((*pvecVars)[m_iIndexTrig]-m_vMonitor)>0)
				{
				vSign=1.0;
//				while((*pvecVars)[m_iIndexTrig]-m_vMonitor>0)
					m_vMonitor+=m_vStep;
				}
				else
				{
				vSign=-1.0;
//				while((*pvecVars)[m_iIndexTrig]-m_vMonitor<0)
					m_vMonitor-=m_vStep;
				}

		return ceesTrig;
		}
	return ceesNoTrig;
}

bool CEvRecorder::willTrigger( vector< variable >* pvecVars )
{
#ifndef NDEBUG
	variable iV = (*pvecVars)[m_iIndexTrig];
#endif
	return (fabs(m_vMonitor-(*pvecVars)[m_iIndexTrig])>m_vStep);
}


///////////////////////////////////////////////////////////
// Function name	: CEvRecorder::check
// Description	    : 
// Return type		: bool 
// Argument         : long iLeft
// Argument         : long iRight
// Argument         : vector<CToken*>& vExpLine
// Argument         : ostream& osErrReport
///////////////////////////////////////////////////////////
bool CEvRecorder::check(long iLeft, long iRight, vector<CToken*>& vExpLine, IARDataStore *pIARDataStore, ostream& osErrReport )
{
	vector< CToken* >::iterator itpCT;
	// itpCTRight is fouud this way as I'm not sure &vExp[iRight] would produce the same result in all conditions
	vector< CToken* >::const_iterator itpCTRight = getRightWithoutComments(iLeft,iRight,vExpLine);
	bool bResult = true;
	bool bDelim =true;

	itpCT = &vExpLine[iLeft];

	if (!pIARDataStore)
		{
		SYMERRORLITE("No data store service found",errInternal);
		return false;
		}

	if (iLeft==iRight) // may not be necessary as doesn't seem to get here.
			{
			SYMERRORLITE("Unable to check a recorder event",errInternal);
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
			{ // must have this as constructor relies upon it
			osErrReport << "<Error*> Part of event statement is missing the term '"<< g_As<<"' on line "<<(*itpCT)->getLine()<<endl;
			SYMERRORTOK2("Part of event statement is missing the term: ",g_As,errSyntax,(*itpCT));
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
			osErrReport << "<Error*> Stream name not in quotes on line "<<(*itpCT)->getLine()<<endl;
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
			SYMERRORTOK("Stream name for reocrding data to is missing",errSyntax,(*itpCT));
			return false;
			}

	if (!pIARDataStore)
			{
			SYMERRORTOK("There is a problem with the component that offers write streams - report to vendor",errInternal,(*itpCT));
			return false;	
			}

	{
	VARIANT_BOOL vbResult;
	CComBSTR cbName((*itpCT)->getString().c_str());
	HRESULT hr=E_FAIL;

	try
	{
	#ifndef NDEBUG
		pIARDataStore->AddRef();
		ATLTRACE("Count %d \n",pIARDataStore->Release());
	#endif
		hr = pIARDataStore->isAvailableForWrite(&(cbName.m_str),&vbResult);
	}
	catch(...)
	{
		SYMERRORLITE2("Unable to check the following stream due to unexpected crash ",(*itpCT)->getString().c_str(),errSystem);
		ATLTRACE("Unexpected exception thrown in CEvRecorder::check - hr =%d \n",hr);
		return false;
	}

	if (FAILED(hr))
			{
			SYMERRORTOK2("The specified write stream could not be made available see - ",(*itpCT)->getString().c_str(),errInternal,(*itpCT));
			return false;
			}

	if (vbResult==0)
			{
			SYMERRORTOK2("The specified write stream could not be made available see - ",(*itpCT)->getString().c_str(),errSystem,(*itpCT));
			return false;	
			}

	}

	if (++itpCT==itpCTRight)
			{
			SYMERRORTOK("Part of event statement is missing",errSyntax,(*--itpCT));
			osErrReport << "<Error*> Part of event statement is missing on line "<<(*itpCT)->getLine()<<endl;
			return false;
			}

	if (!((*itpCT)->getString().compare(g_Quote)==0))
			{
			osErrReport << "<Error*> Stream name not in quotes on line "<<(*itpCT)->getLine()<<endl;
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
			osErrReport << "<Error*> Omission of key word "<< g_For<<" on line "<<(*itpCT)->getLine()<<endl;
			SYMERRORTOK2("Omission of a key word",g_For,errSyntax,(*itpCT));
			return false;
			}
	
	if (++itpCT==itpCTRight)
			{
			SYMERRORTOK("Part of event statement is missing",errSyntax,(*--itpCT));
			osErrReport << "<Error*> Part of event statement is missing on line "<<(*itpCT)->getLine()<<endl;
			return false;
			}

	if (!((*itpCT)->IsOfTypeVariable()))
			{
			osErrReport << "<Error*> Omission of key variable on line "<<(*itpCT)->getLine()<<endl;
			SYMERRORTOK("Omission of key variable",errSyntax,(*itpCT));
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
			osErrReport << "<Error*> Omission of key word "<< g_For<<" on line "<<(*itpCT)->getLine()<<endl;
			SYMERRORTOK2("Omission of key word: ",g_For,errSyntax,(*itpCT));
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
	

	return bResult; // TBI
}


///////////////////////////////////////////////////////////
// Function name	: CEvRecorder::setupEvent
// Description	    : 
// Return type		: bool 
// Argument         : vector<CEquation*>* pvecpEquations
///////////////////////////////////////////////////////////
bool CEvRecorder::setupEvent(vector<CEquation*>* pvecpEquations)
{

	ASSERT2(m_ivecSizes!=NOT_DEFINED);
	ASSERT2(m_vecResults.size()==m_ivecSizes);
	
	if (isInError())
		return false;

	if (m_eState==cevUninitiated)
		{
		vector< CToken* >::const_iterator cit;
		
		ASSERT2(m_pctTrig);
		if (!m_pctTrig) // handle in release case
			return false;

		// it should now be possible to get the needed Indexs etc
		m_iIndexTrig = m_pctTrig->getRootTokenPt()->getIndex();
		ASSERT2(m_iIndexTrig!=NOT_DEFINED);
		if (m_iIndexTrig==NOT_DEFINED)
			return false;

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

