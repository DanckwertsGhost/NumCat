// ArrayLookup.cpp: implementation of the CArrayLookup class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ArrayLookup.h"
#include "csvHolderFactory.h"
#include "Tokeniser.h"

#include "Symlix\ErrorFactory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CArrayLookup::CArrayLookup(long iLeft,long iRight,vector<CToken*>& vExpLine, IARDataStore* pIStore,ostream& osErrReport/*=cerr*/):CArraySetValue_Impl()
{
	CcsvHolder* pcsvLookup = NULL;
	
	ASSERT2(m_pToken==NULL);

	if (!check(iLeft,iRight,vExpLine,pIStore,osErrReport)) // you should always have called the static check function first anyway
		{
		m_eState = carError;
		m_sError = "Failed internal check for creating a Lookup Array";
		SYMERRORLITE(m_sError.c_str(),errInternal);
		}
		else
		{
		string sStreamName;
		ASSERT2((iLeft>=0)&&(iLeft<vExpLine.size())); // this really should ahve been caught in the check
		vector<CToken*>::iterator it = &vExpLine[iLeft];
		vector<CToken*>::const_iterator itRight = CNavTokens::getRightWithoutComments(iLeft,iRight,vExpLine);

		m_pToken = (*it);
		it++;
		ASSERT2(it!=itRight);

		while(((*it)->getStringRef().compare(g_Quote)!=0)&&(++it!=itRight))
			{} // not much		

		ASSERT2(it!=itRight);
		it++; // as last term in while not used when quote found
				
		while((it!=itRight)&&((*it)->getStringRef().compare(g_Quote)!=0))
			{
			ATLTRACE("(*it) is '%s'\n",(*it)->getString().c_str());
			sStreamName += (*it++)->getString();
			}

		if ((it==itRight)||(sStreamName.length()<1))
				{
				m_eState = carError;
				m_sError = "Failed internal check for creating a Lookup Array";
				SYMERRORLITE(m_sError.c_str(),errInternal);
				}
				else
				{
				IARStream* pIStream = NULL;

				{ // start csv setup
				CComBSTR cbFile(sStreamName.c_str());
				enumARReadHint er = readFormatCSV;
				HRESULT hr = pIStore->tryToGetARStream(&(cbFile.m_str),er,&pIStream);
				if ((FAILED(hr))||(!pIStream))			
					{
					osErrReport << "<Error*> Unable to find data referred to as "<<sStreamName.c_str()<<".\n";
					SYMERRORLITE2("Unable to find data referred to in stream ",sStreamName.c_str(),errSystem);
					ASSERT2(!pIStream); // shouldn't happen
					m_eState = carError;
					m_sError = "Failed to get stream requested : ";
					m_sError += sStreamName;
					}
					else
					{
					CcsvHolderFactory* pchf = CcsvHolderFactory::instance();
					pcsvLookup = pchf->create("lookup",pIStream);
					ASSERT2(pcsvLookup); // don't think this is right
					pIStream->Release();
					}
				} // end csv setup

			#ifndef NDEBUG	
				{
				ofstream oshelp("c:\\temp\\pcsvLookup.txt");
				oshelp << (*pcsvLookup) << endl;
				oshelp.close();
				}
			#endif
				if ((pcsvLookup)&&(setupIndexesFromLHSToken()))
					{
					long iColIndex;
					long iColValue;
					long iCurRow;
					CCell* pCell = NULL;

					// amend token name
					cleanUpTokenNameAndSetAsArray();

					ATLTRACE("Name alone is %s\n",m_pToken->getString().getLessDerivative().c_str());
					
					pCell = pcsvLookup->findFirstInRow(0,g_JustIndex);
					if (pCell)
						{
						iColIndex = pcsvLookup->getFocusCol();
						}
						else
						{
								m_eState = carError;
								m_sError = "Unable find the column heading '";
								m_sError += g_JustIndex;
								m_sError += "' in the top row ";
								m_sError += " in this stream ";
								m_sError += sStreamName;
								SYMERRORTOK(m_sError.c_str(),errSyntax,m_pToken);
						}

					
					// identify any required token indicies
					pCell = pcsvLookup->findFirstInRow(0,m_pToken->getString().getLessDerivative().c_str());
					if (pCell)
						{
						iColValue = pcsvLookup->getFocusCol();
						ASSERT2(iColIndex!=CSVH_NOTSET); // should never happen as pCell exists
						// assume the index column is the one before - check
						//iColIndex = iColValue -1;
						if (iColIndex>=0)
							{
							vector< long >::const_iterator cit;
							bool bMissing = false;

							for (cit=m_vecIndicies.begin();cit!=m_vecIndicies.end();cit++)
								{
								pCell = pcsvLookup->findFirstInCol(iColIndex,*cit);
								if (pCell)
									{
									iCurRow = pcsvLookup->getFocusRow();
									pCell = pcsvLookup->getCell(iCurRow,iColValue);
									if (pCell) // have to allow for this
										m_vecValues.push_back(pCell->getNumber());
										else
										{
										ASSERT2(pCell);
										m_vecValues.push_back(NOT_FOUND);
										bMissing = true;
										}
									}
									else
									{
									m_vecValues.push_back(NOT_FOUND);
									bMissing = true;
									}
								#ifndef NDEBUG
								variable vTest = pCell->getNumber();
								ATLTRACE("Index [%d] = %f\n",*cit,vTest);
								#endif
								}
							
							if (bMissing)
								{
								m_eState = carError;
								m_sError = "Failed internal check for creating a Lookup Array";
								SYMERRORLITE(m_sError.c_str(),errInternal);
								}


							}
							else
							{
								m_eState = carError;
								m_sError = "Unable to index column before the value column for ";
								m_sError += m_pToken->getString();
								m_sError += " in this stream ";
								m_sError += sStreamName;
								SYMERRORTOK(m_sError.c_str(),errSyntax,m_pToken);
							}

						ASSERT2(m_vecValues.size()==m_vecIndicies.size());
						if ((m_eState!=carError)&&(m_vecValues.size()==m_vecIndicies.size()))
							m_eState = carIntiated;	
							else
							m_eState = carError;


						}
						else
						{
						m_eState = carError;
						m_sError = "Unable to find header for ";
						m_sError += m_pToken->getString();
						m_sError += " in this stream ";
						m_sError += sStreamName;
						ATLTRACE("%s\n",m_sError.c_str());
						SYMERRORTOK(m_sError.c_str(),errSyntax,m_pToken);
						}
									

					}
					else
					m_eState = carError; // just to be sure


			}// end internal issues if then


		}


}

CArrayLookup::~CArrayLookup()
{

}




///////////////////////////////////////////////////////////
// Function name	: CArrayLookup::getToken
// Description	    : 
// Return type		: CToken* 
///////////////////////////////////////////////////////////
/*
CToken* CArrayLookup::getToken()
{

	ASSERT2(m_iInd>=0);
	if (m_iInd>=m_vecToks.size())
		return NULL;

	return m_vecToks[m_iInd];
}
*/


///////////////////////////////////////////////////////////
// Function name	: CArrayLookup::check
// Description	    : 
// Return type		: bool 
// Argument         : long iLeft
// Argument         : long iRight
// Argument         : vector<CToken*>& vExpLine
// Argument         : IARDataStore* pIStore
// Argument         : ostream& osErrReport
///////////////////////////////////////////////////////////
bool CArrayLookup::check(long iLeft,long iRight,vector<CToken*>& vExpLine, IARDataStore* pIStore, ostream& osErrReport)
{
    // eg arraylookup a[1:3,5] in "filename"
	long iIndexSize =0;
	long iValuesSize =0;
	string sFile;
	vector< CToken* >::iterator itpCT;
	// itpCTRight is found this way as I'm not sure &vExp[iRight] would produce the same result in all conditions
	vector< CToken* >::const_iterator itpCTRight;

	itpCTRight = CNavTokens::getRightWithoutComments(iLeft,iRight,vExpLine);

	if ((iRight<=iLeft)||(iRight==0))
			{
			osErrReport << "<Internal Error*> ArrayLookup cannot be read and is badly formed.\n";
			SYMERRORLITE("ArrayLookup cannot be read",errInternal);
			return false;
			}

	if (vExpLine.size()<6) // then there cannot be enough information for this array type
			{
			if (vExpLine.size()<iLeft)
				{
				osErrReport << "<*Error*> ArrayLookup does not have enough information and is badly formated.\n";
				SYMERRORTOK("ArrayLookup does not have enough information and is badly formated",errInternal,vExpLine[iLeft]);
				}
				else
				{
				osErrReport << "<*Error*> ArrayLookup does not have enough information and is badly formated.\n";
				SYMERRORTOK("ArrayLookup does not have enough information and is badly formated",errSyntax,vExpLine[iLeft]);
				}
			return false;
			}
	// so there is some prospect of this working

	itpCT = &vExpLine[iLeft];

	#ifndef NDEBUG
	osErrReport << (**itpCT) <<endl;
//	osErrReport << (*itpCT++)->getStringRef().c_str() <<endl;
//	itpCT--;
	#endif
	if (!(*itpCT)->IsOfTypeVariable())
			{
				osErrReport << "<*Error*> Variable expected.\n";
				SYMERRORTOK2("Variable expected after ",g_LookupArray,errSyntax,(*itpCT));
				#ifndef NDEBUG
				osErrReport << (**itpCT) <<endl;
				#endif
				return false;
			}

	iIndexSize = CArray::checkArrayName(**itpCT);

	if (iIndexSize<0)
			{
			osErrReport << "Problem with array declaration "<<(*itpCT)->getString().c_str()<<endl;
			// no SYMERROR needed as it will have been called in checkArrayName
			return false;

			}

	itpCT++;

	if ((!(*itpCT)->IsOfType(ctEquationKeyWord))||((*itpCT)->getStringRef().compare(g_In)!=0))
			{
				osErrReport << "<Error*> " << g_In<<" expected. "<<(**itpCT)<<"\n";
				SYMERRORTOK2(g_In," expected",errSyntax,(*itpCT));
				return false;
			}
	itpCT++;


	if ((!(*itpCT)->IsOfType(ctDelim))||((*itpCT)->getStringRef().compare(g_Quote)!=0))
			{
				osErrReport << "<*Error*> " << g_Quote<<" expected. "<<(**itpCT)<<"\n";
				SYMERRORTOK2(g_Quote," expected",errSyntax,(*itpCT));
				return false;
			}

	while(((++itpCT)!=itpCTRight)&&((*itpCT)->getStringRef().compare(g_Quote)!=0))
			sFile += (*itpCT)->getString();

	if (itpCT==itpCTRight)
		{
			osErrReport << "<*Error*> expected "<<g_Quote<<" to be closed. "<<(**--itpCT)<<"\n";
			SYMERRORTOK("Expected closure of quotes.",errSyntax,(*itpCT)); // relies on line above
			return false;
		}

	//check store name exists

	ASSERT2(pIStore);

	if (!pIStore)
		{
		osErrReport << "<*Error*> Internal error - invalid store pointer.\n";
		SYMERRORTOK("Problem loading lookup data",errInternal,(*--itpCT));
		return false;
		}

	{
	CComBSTR cbFileName(sFile.c_str());
	VARIANT_BOOL vb;
	HRESULT hr = pIStore->isAvailable(&(cbFileName.m_str),&vb);
	if (SUCCEEDED(hr))
		{
		 if (vb==0)
			{
			osErrReport << "<Error*> File "<<sFile.c_str()<<" cannot be opened in line "<<vExpLine[iLeft]->getLine()<<".\n";
			SYMERRORTOK("Stream specified cannot be opened",errSystem,vExpLine[iLeft]);
			return false;
			}
		// carry on OK	
		}
		else
		{
		ATLTRACE("IARDataStore has thrown a Fail message %d \n",hr);
		ASSERT2(false);
		osErrReport << "<Error*> File "<<sFile.c_str()<<" cannot be accessed in line "<<vExpLine[iLeft]->getLine()<<".\n";
		SYMERRORTOK("Stream failed to open",errSystem,vExpLine[iLeft]);
		return false;
		}

	}
	

	return true;

}



void CArrayLookup::out( ostream& os ) const
{
	int iCount=0;
	vector<long>::const_iterator cind;
	vector<variable>::const_iterator cAr;
	if (!m_pToken)
		{
		os << "[CArrayLoopup] Token Error"<<endl;
		return;
		}
	os << "[CArrayLookup] Token '"<<m_pToken->getString().c_str()<<"'";
	os << " Array size "<<m_vecValues.size()<<"\n";

	cind=m_vecIndicies.begin();
	cAr=m_vecValues.begin();

	while((cind!=m_vecIndicies.end())&&(cAr!=m_vecValues.end()))
	{
		if (iCount<ARRAY_LINE_COUNT)
			{
			os <<"["<<*cind<<"] "<<*cAr<<"\t";
			iCount++;
			}
			else
			{
			os <<"["<<*cind<<"] "<<*cAr<<"\n";
			iCount=0;
			}
	cind++;
	cAr++;
	}
	if (iCount!=0)
		os<<"\n";

	ASSERT2(m_vecIndicies.size()==m_vecValues.size());

}


#ifndef NDEBUG

///////////////////////////////////////////////////////////
// Function name	: CArrayLookup::unitTests
// Description	    : Debug only function designed to catch coding faults with unit tests
// Return type		: bool 
// Argument         : IARDataStore* pIStore
///////////////////////////////////////////////////////////
bool CArrayLookup::unitTests(IARDataStore* pIStore)
{

	bool bResults = true;
    CTestHoldTokeniser cht;

	ASSERT2(pIStore);
	
	//test 1 - should pass
    vector<CToken*>& rvecTok = cht.getRefVectorOfTokenPointers(1,"arraylookup a[1:3,7] in \"unittestfile.csv\"","Test");
	cht.assignVariables(rvecTok);
	bResults &= CArrayLookup::check(1,rvecTok.size(),rvecTok,pIStore,cerr);

	//test 2 - should fail
    rvecTok = cht.getRefVectorOfTokenPointers(1,"arraylookup a[1:3,7] = \"unittestfile.csv\"","Test");
	cht.assignVariables(rvecTok);
	bResults &= !CArrayLookup::check(1,rvecTok.size(),rvecTok,pIStore,cerr);

	//test 3 - should fail
    rvecTok = cht.getRefVectorOfTokenPointers(1,"arraylookup a(1:3,7) in \"unittestfile.csv\"","Test");
	cht.assignVariables(rvecTok);
	bResults &= !CArrayLookup::check(1,rvecTok.size(),rvecTok,pIStore,cerr);

	//test 4 - should fail
    rvecTok = cht.getRefVectorOfTokenPointers(1,"arraylookup a[1,2,3] in \"NotHereunittestfile.csv\"","Test");
	cht.assignVariables(rvecTok);
	bResults &= !CArrayLookup::check(1,rvecTok.size(),rvecTok,pIStore,cerr);

	//test 5 - should pass
    rvecTok = cht.getRefVectorOfTokenPointers(1,"arraylookup a[1,2,3] in \"unittestfile.csv\"","Test");
	cht.assignVariables(rvecTok);
	bResults &= CArrayLookup::check(1,rvecTok.size(),rvecTok,pIStore,cerr);


	return bResults;
}

#endif


