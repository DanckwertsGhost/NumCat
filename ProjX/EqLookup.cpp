// EqLookup.cpp: implementation of the CEqLookup class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EqLookup.h"
#include "csvHolderFactory.h"
#include "csvLookup.h"
#include "Symlix\ErrorFactory.h"
#include "EquationFactory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define CEL_LOOKUP_UNDEFINED -1

CEqLookup::CEqLookup():CEquation(),m_pcsvLookup(NULL),m_iLookup(CEL_LOOKUP_UNDEFINED),m_sFileName(""),m_bWarnOnce(true)
{

}

CEqLookup::CEqLookup(long iLeft,long iRight,vector<CToken*>& vExpLine, IARDataStore* pIStore, ostream& osErrReport):CEquation(),m_pcsvLookup(NULL),m_iLookup(CEL_LOOKUP_UNDEFINED),m_bWarnOnce(true)
{

	long iCacheNumber=CSVHOLDER_DEFAULT_CACHE_LEVEL;
//	vector< CToken* >::iterator itpCT;
	IARStream* pIStream = NULL;
	long iLookup;
	long iT;
	vector< long > vecFrom;
	// itpCTRight is foudn this way as I'm not sure &vExp[iRight] would produce the same result in all conditions
//	vector< CToken* >::const_iterator itpCTRight = getRightWithoutComments(iLeft,iRight,vExpLine);

	try // as were addressing array elements directly its always possible to mess up, so handle with grace
	{
	if (CEqLookup::IsWellFormedLookupEquation(iLeft,iRight,vExpLine,pIStore,osErrReport))
		{
		bool bNext=true;
		long iCount=iLeft+2;
		m_pctLeft = vExpLine[iLeft+1]; // ie token after 'lookup'
		ASSERT2(m_pctLeft);
//		m_pctAssign = vExpLine[iLeft+1];
/*ATLTRACE("\n");
for (iT=iLeft;iT<iRight;iT++)
	ATLTRACE("%d:[%s] ",iT,vExpLine[iT]->getString().c_str());
ATLTRACE("\n");*/
		
		if ((vExpLine[iLeft+2]->IsOfType(ctEquationKeyWord))&&(vExpLine[iLeft+2]->getString().compare(g_Alias)==0))
					{
					iLookup = iLeft+4;
					iCount += 4; // to go beyond the alias
					}
					else
					iLookup = iLeft+1;

		while(bNext&&(++iCount<iRight))
		{
			// ATLTRACE("iCount = %d, vExpLine[iCount] = %s\n",iCount,vExpLine[iCount]->getString().c_str());
			 ASSERT2(vExpLine[iCount]->IsOfTypeVariable()||vExpLine[iCount]->IsOfType(ctDerivative));
			 m_vpctRight.push_back(vExpLine[iCount]);
			 
			 if ((vExpLine[iCount+1]->IsOfType(ctEquationKeyWord))&&(vExpLine[iCount+1]->getString().compare(g_Alias)==0))
					{
					vecFrom.push_back(iCount+3);
					iCount +=4;
					}
					else
					vecFrom.push_back(iCount);

			 if ((vExpLine[iCount+1]->IsOfType(ctDelim))&&(vExpLine[iCount+1]->getString().compare(g_Comma)==0))
						iCount++;
						else
						bNext=false;
		}


		iCount +=3; //over the 'in' and '"'
		
		while((iCount<iRight)&&(vExpLine[iCount]->getString().compare(g_Quote)!=0))
		{
			m_sFileName += vExpLine[iCount]->getString();
			iCount++;
		}

		iCount++;

		if (iCount<iRight) // then cache instructions present
			{
			ASSERT2(vExpLine[iLeft+iCount]->getString().compare(g_Cache)==0);
			iCount++;
			ASSERT2(vExpLine[iLeft+iCount]->IsOfType(ctNumber));
			iCacheNumber = vExpLine[iLeft+iCount]->getNumber();
			}
		
		{
		CComBSTR cbFile(m_sFileName.c_str());
		enumARReadHint er = readFormatCSV;
		HRESULT hr = pIStore->tryToGetARStream(&(cbFile.m_str),er,&pIStream);
		if ((FAILED(hr))||(!pIStream))			
			{
			osErrReport << "<Error*> Unable to find data referred to as "<<m_sFileName.c_str()<<".\n";
			SYMERRORLITE2("Unable to find data referred to in stream ",m_sFileName.c_str(),errSystem);
			ASSERT2(!pIStream); // shouldn't happen
			m_eState=ceqError;
			}
			else
			{
			CcsvHolderFactory* pchf = CcsvHolderFactory::instance();
	//		m_pcsvLookup = pchf->create("lookup",m_sFileName.c_str());
			m_pcsvLookup = pchf->create("lookup",pIStream);
			ASSERT2(m_pcsvLookup); // don't think this is right
			pIStream->Release();
			}
		}
		
		ASSERT2(m_vpctRight.size()==vecFrom.size());
		if (m_vpctRight.size()!=vecFrom.size())
				{
				m_eState=ceqError;
				SYMERRORTOK("An internal problem was found when trying to read a lookup equation",errInternal,vExpLine[0]);
				return;
				}

		if (m_pcsvLookup)
			{
			CCell* pcell;
			for (iT=0;iT<vecFrom.size();iT++)
				{
				pcell = m_pcsvLookup->findFirstInRow(0,vExpLine[vecFrom[iT]]->getString().c_str());
				if (!pcell)
					{
					string sErr = "Unable to find the string '";
					sErr.append(vExpLine[ vecFrom[iT] ]->getString());
					sErr += "' in the header of the stream ";
					sErr += m_sFileName;
					SYMERRORTOK(sErr.c_str(),errSyntax,vExpLine[vecFrom[iT]]);
					osErrReport << "<Error*> "<< sErr.c_str() <<endl;
					m_eState=ceqError;
					}
					else
					m_vRefInds.push_back(m_pcsvLookup->getFocusCol()); 
				}

#ifndef NDEBUG
//#define DUMP_INPUT_TABLE
#endif
#ifdef DUMP_INPUT_TABLE
			ofstream osTemp;
			osTemp.open("c:\\temp\\dumpstable.txt");
			osTemp << (*m_pcsvLookup);
			osTemp <<"<End Line>"<<endl;
			osTemp.close(); 
#endif

			pcell = m_pcsvLookup->findFirstInRow(0,vExpLine[iLookup]->getString().c_str());

			if (pcell)
					m_iLookup = m_pcsvLookup->getFocusCol();
					else
					{
					string sErr = "Unable to find the string '";
					sErr.append(vExpLine[iLookup]->getString());
					sErr += "' in the header of the stream ";
					sErr += m_sFileName;
					SYMERRORTOK(sErr.c_str(),errSyntax,vExpLine[iLookup]);
					osErrReport << "<Error*> "<< sErr.c_str() <<endl;
					m_eState=ceqError;
					}

			if (m_eState!=ceqError)
					{
					ASSERT2(m_vRefInds.size()==m_vpctRight.size());
					if (m_vRefInds.size()==m_vpctRight.size())
								m_eState=ceqIntiated;
								else
								{
								osErrReport << "<Internal Error*> Lookup equation could not initialise indicies correctly.\n";
								SYMERROR("Lookup equation could not initialise indicies correctly in data from stream",errSystem,m_sFileName.c_str(),NOT_DEFINED,NOT_DEFINED);
								m_eState=ceqError;
								}
					}

			}
			else
			m_eState=ceqError;
		}
		else
		m_eState=ceqError; // the equation is in an error state and cannot be used
		}
		catch(...)
		{
		SYMERRORLITE("Unexpected error found whilst creating a lookup equation",errInternal);
		m_eState=ceqError;
		}

}

CEqLookup::CEqLookup(const CEqLookup& ceql ):CEquation(),m_pcsvLookup(NULL),m_iLookup(CEL_LOOKUP_UNDEFINED),m_sFileName(""),m_bWarnOnce(true)
{
	copy(ceql);
}


CEqLookup::~CEqLookup()
{

}


///////////////////////////////////////////////////////////
// Function name	: CEqLookup::copy
// Description	    : 
// Return type		: void 
// Argument         : const CEqLookup& CE
///////////////////////////////////////////////////////////
void CEqLookup::copy(const CEqLookup& CE)
{
	const CEquation* eq = &CE;
	CEquation::copy(*eq);

	m_iLookup = CE.m_iLookup;
	m_pcsvLookup = CE.m_pcsvLookup;
	m_sFileName = CE.m_sFileName;
	m_vRefInds = CE.m_vRefInds;
	m_vValueInds = CE.m_vValueInds;
	m_bWarnOnce = CE.m_bWarnOnce;

}


///////////////////////////////////////////////////////////
// Function name	: CEqLookup::IsWellFormedLookupEquation
// Description	    : Check this would create a healthy Lookup Equation
// Return type		: bool 
// Argument         : long iLeft
// Argument         : long iRight
// Argument         : vector<CToken*>& vExpLine
// Argument         : IARDataStore* pIStore
// Argument         : ostream& osErrReport
///////////////////////////////////////////////////////////
bool CEqLookup::IsWellFormedLookupEquation(long iLeft,long iRight,vector<CToken*>& vExpLine, IARDataStore* pIStore, ostream& osErrReport)
{
	// the format of this type of equation should be:
	// lookup <variable> from <variable>(,) in <filename in double quotes> 
	// followed by optional cache level instruction as follows             cache <integer>
	bool bResult = true;
	long iCount = iRight-iLeft;
	long iStep = 0;


	try // as were addressing array elements directly its always possible to mess up, so handle with grace
	{


	if ((iRight==iLeft)||(iRight==0))
			{
			ASSERT2(false); // this should never have got this far
			osErrReport << "<Internal Error*> Lookup equation cannot be read and is badly formed.\n";
			SYMERRORLITE("Lookup stream cannot be read",errInternal);
			return false;
			}

	if (iLeft!=0) // I think it always should be so adding code here
			{
			ASSERT2(false);
			osErrReport << "<Warning*> Lookup equation does not appear to be left most in this expression , see line "<<vExpLine[iLeft]->getLine()<<".\n";
			SYMERRORTOK("Lookup equation does not appear to be left most in this expression",errInternal,vExpLine[iLeft]);
			}

	if (iLeft>=vExpLine.size())
			{
			ASSERT2(false); // this should never have got this far
			osErrReport << "<Error*> Lookup equation on line "<<vExpLine[iLeft]->getLine() <<" cannot be read and is badly formed.\n";
			SYMERRORTOK("Lookup equation cannot be read or is badly formed",errSyntax,vExpLine[iLeft]);
			return false;
			}

	if ((iRight-iLeft)<6) // then this just is not going to work
			{
			osErrReport << "<Error*> Lookup equation on line "<<vExpLine[iLeft]->getLine() <<" cannot be read and is badly formed.\n";
			SYMERRORTOK("Lookup equation cannot be read or is badly formed",errSyntax,vExpLine[iLeft]);
			return false;
			}
	
	if (vExpLine[iLeft]->getString().compare(g_Lookup)!=0)
			{
			osErrReport << "<Error*> Lookup equation on line "<<vExpLine[iLeft]->getLine() <<" should start with '"<<g_Lookup<<"'.\n";
			SYMERRORTOK("Lookup equation has incorrect keyword",errSyntax,vExpLine[iLeft]);
			return false;
			}

	if ((!vExpLine[iLeft+1]->IsOfTypeVariable())&&(!vExpLine[iLeft+1]->IsOfType(ctDerivative)))
			{
			osErrReport << "<Error*> Lookup equation on line "<<vExpLine[iLeft]->getLine() <<" needs to point to a variable after "<<g_Lookup<<".\n";
			SYMERRORTOK("Lookup equation needs to point to a variable",errSyntax,vExpLine[iLeft]);
			return false;
			}

//#ifndef _TEST_LHSARRAY
	if (CArrayFactory::instance()->anyArraysHere(*vExpLine[iLeft+1],true))
				{
				osErrReport << "<Error*> Trying to assign a value to an array already declared\n";
				SYMERRORTOK("Trying to assign a value to an array already declared",errSyntax,vExpLine[iLeft+1]);
				return false;
				}
//#endif


	if ((vExpLine[iLeft+2]->IsOfType(ctEquationKeyWord))&&(vExpLine[iLeft+2]->getString().compare(g_Alias)==0)) // there will be a lookup alias in quotes
			{
			if ((vExpLine[iLeft+3]->getString().compare(g_Quote)!=0)||(vExpLine[iLeft+5]->getString().compare(g_Quote)!=0))
					{
					string sErr = "Alias following as does not have quotes round it";
					SYMERRORTOK(sErr.c_str(),errSyntax,vExpLine[iLeft+2]);	
					return false;
					}	
			iLeft += 4; // ie as " name "
			if (iLeft>=iRight)
					{
					string sErr = "Lookup equation is not complete";
					SYMERRORTOK(sErr.c_str(),errSyntax,vExpLine[iLeft+2]);	
					return false;
					}
			}

	if (vExpLine[iLeft+2]->getString().compare(g_From)!=0)
			{
			osErrReport << "<Error*> Lookup equation on line "<<vExpLine[iLeft]->getLine() <<" should include a '"<<g_From<<"' statement.\n";
			string sErr = "Lookup equations needs to include the '";
			sErr.append(g_From);
			sErr.append("' statement");
			SYMERRORTOK(sErr.c_str(),errSyntax,vExpLine[iLeft]);
			return false;
			}

	bool bNext;
	iStep=2+iLeft;
	do
	{
		iStep++;
		bNext=false; // default
		if ((!vExpLine[iStep]->IsOfTypeVariable())&&(!vExpLine[iStep]->IsOfType(ctDerivative)))
				{
				osErrReport << "<Error*> Lookup equation on line "<<vExpLine[iLeft]->getLine() <<" variable not recognised '"<<vExpLine[iStep]->getString().c_str()<<"'.\n";
				SYMERRORTOK("Lookup equation variable not recognised",errSyntax,vExpLine[iStep]);
				return false;
				}

		if (iStep<iRight)
				{
				if ((vExpLine[iStep+1]->IsOfType(ctEquationKeyWord))&&(vExpLine[iStep+1]->getString().compare(g_Alias)==0))
					{
					// then next 4 should fit this bill
					if ((iStep+4)>=iRight)
							{
							string sErr = "Lookup equation is not complete";
							SYMERRORTOK(sErr.c_str(),errSyntax,vExpLine[iLeft+2]);	
							return false;

							}
					if ((vExpLine[iStep+2]->getString().compare(g_Quote)!=0)||(vExpLine[iStep+4]->getString().compare(g_Quote)!=0))
							{
							ATLTRACE("\nvExpLine[iStep+3] = %s,\tvExpLine[iStep+5] = %s\n",vExpLine[iStep+3]->getString().c_str(),vExpLine[iStep+5]->getString().c_str());
							string sErr = "Alias lookup term not stated correctly";
							SYMERRORTOK(sErr.c_str(),errSyntax,vExpLine[iStep+2]);	
							return false;
							}
					iStep += 4;
					}
				}


		if (iStep<iRight)
				{

				if ((vExpLine[iStep+1]->IsOfType(ctDelim))&&(vExpLine[iStep+1]->getString().compare(g_Comma)==0))
							{
							iStep++;
							bNext=true;
							}
				}

	}
	while((iStep<iRight)&&bNext);

	if (bNext)
		{
		osErrReport << "<Internal Error*> Lookup equation could not be parsed. Please report to vendor.\n";
		SYMERRORTOK("Lookup equation could not be parsed - report to vendor",errInternal,vExpLine[iLeft]);
		return false;
		}

	if (!bResult)
		return bResult; // as may have run out of room

	if (++iStep==iRight)
		{
		 osErrReport << "<Error*> Incomplete lookup statement on line "<<vExpLine[iLeft]->getLine()<<".\n";
		 SYMERRORTOK("Incomplete lookup statement",errSyntax,vExpLine[iStep-1]);
		 return false;	
		}

	if (((!vExpLine[iStep]->IsOfType(ctEquationKeyWord))&&(!vExpLine[iStep]->getString().compare(g_In)==0)))
			{
			osErrReport << "<Error*> Lookup equation on line "<<vExpLine[iLeft]->getLine() <<" phrase not recognised '"<<vExpLine[iStep]->getString().c_str()<<"'.\n";
			SYMERRORTOK("Phrase not recognised in Lookup equation",errSyntax,vExpLine[iStep]);
			return false;
			}

	if (++iStep==iRight)
		{
		 osErrReport << "<Error*> Incomplete lookup statement on line "<<vExpLine[iLeft]->getLine()<<".\n";
		 SYMERRORTOK("Incomplete lookup statement",errSyntax,vExpLine[iStep-1]);
		 return false;	
		}

	if (((!vExpLine[iStep]->IsOfType(ctDelim))&&(!vExpLine[iStep]->getString().compare(g_Quote)==0)))
			{
			osErrReport << "<Error*> Lookup equation on line "<<vExpLine[iLeft]->getLine() <<" phrase not recognised '"<<vExpLine[iStep]->getString().c_str()<<"', should be a '"<<g_Quote<<"' .\n";
			string sErr = "Phrase not recognised in Lookup equation, should be a '";
			sErr.append(g_Quote);
			sErr.append("'");
			SYMERRORTOK(sErr.c_str(),errSyntax,vExpLine[iStep]);
			return false;
			}

	bNext=true;
	string sFileName;
	while(bNext&&(++iStep<=iRight))
	{
	if (((vExpLine[iStep]->IsOfType(ctDelim))&&(vExpLine[iStep]->getString().compare(g_Quote)==0)))
				bNext = false;
				else
				sFileName += vExpLine[iStep]->getString().c_str();

	}


	if (iStep>=iRight)
		{
		osErrReport << "<Error*> Missing ,"<<g_Quote<<"' in lookup equation line "<<vExpLine[iLeft]->getLine()<<".\n";
		string sErr = "Missing from Lookup equation, needs a further '";
		sErr.append(g_Quote);
		sErr.append("'");
		try // because I'm 95% sure -2 is OK
		{
			SYMERRORTOK(sErr.c_str(),errSyntax,vExpLine[iStep-2]);
		}
		catch(...)
		{
			SYMERRORTOK("Check Lookup equation",errSyntax,vExpLine[iLeft]);
		}
		return false;
		}

	ASSERT2(pIStore); // grab developer attention
	if (!pIStore) // cover the int he wild case
		{
		osErrReport << "<Internal Error*> Information storage has not been recognised, please report this.\n";
		SYMERRORTOK("Information storage has not been recognised, please report this",errInternal,vExpLine[iLeft]);
		return false;
		}

	{
	CComBSTR cbFileName(sFileName.c_str());
	VARIANT_BOOL vb;
	HRESULT hr = pIStore->isAvailable(&(cbFileName.m_str),&vb);
	if (SUCCEEDED(hr))
		{
		 if (vb==0)
			{
			string sMessage("Stream ");
			sMessage.append(sFileName);
			sMessage.append(" cannot be opened");
			osErrReport << "<Error*> File "<<sFileName.c_str()<<" cannot be opened in line "<<vExpLine[iLeft]->getLine()<<".\n";
			SYMERRORTOK(sMessage.c_str(),errSystem,vExpLine[iLeft]);
			return false;
			}
		// carry on OK	
		}
		else
		{
		ATLTRACE("IARDataStore has thrown a Fail message %d \n",hr);
		ASSERT2(false);
		osErrReport << "<Error*> File "<<sFileName.c_str()<<" cannot be accessed in line "<<vExpLine[iLeft]->getLine()<<".\n";
		SYMERRORTOK("Stream failed to open",errSystem,vExpLine[iLeft]);
		return false;
		}
	

	}


	// check if optional cache staments are made
	iStep++;

	if (iStep>=iRight)
		return true; // all OK

	if (((!vExpLine[iStep]->IsOfType(ctEquationKeyWord))&&(!vExpLine[iStep]->getString().compare(g_Cache)==0)))
			{
			osErrReport << "<Error*> Lookup equation on line "<<vExpLine[iLeft]->getLine()<<" phrase not recognised '"<<vExpLine[iStep]->getString().c_str()<<"', should be a '"<<g_Cache<<"' .\n";
			SYMERRORTOK("Word not recognised or in incorrect place",errSyntax,vExpLine[iStep]);
			return false;
			}

	iStep++;

	if (iStep>=iRight)
		{
		osErrReport << "<Error*> Missing "<<g_Cache<<" level in lookup equation on line "<<vExpLine[iLeft]->getLine()<<".\n";
		SYMERRORTOK("Missing cache level at end of line",errSyntax,vExpLine[iLeft]);
		return false; 
		}

	if (!vExpLine[iStep]->IsOfType(ctNumber))
			{
			osErrReport << "<Error*> Lookup equation on line "<<vExpLine[iLeft]->getLine()<<" a number should follow '"<<g_Cache<<"' .\n";
			SYMERRORTOK("A number is missing in this expression",errSyntax,vExpLine[iStep]);
			return false;
			}
	
	if ((vExpLine[iStep]->getNumber()<CcsvLookup::getLowCacheNum())||(vExpLine[iStep]->getNumber()>CcsvLookup::getHighCacheNum()))
			{
			osErrReport << "<Error*> Cache number is out of range in lookup equation line "<<vExpLine[iLeft]->getLine()<<".\n";
			osErrReport << "        Must be in range "<<CcsvLookup::getLowCacheNum()<<" to "<<CcsvLookup::getHighCacheNum()<<".\n";
			SYMERRORTOK("Cache number is out of range in lookup equation",errSyntax,vExpLine[iStep]);
			return false;
			}
	}
	catch(...)
	{
	SYMERRORLITE("Unexpected error encountered whilst checking a lookup equation",errInternal);
	return false;
	}

	return true;
}


///////////////////////////////////////////////////////////
// Function name	: CEqLookup::getValue
// Description	    : Lookup value in table
// Return type		: variable 
// Argument         : vector<variable>* pvecV
///////////////////////////////////////////////////////////
variable CEqLookup::getValue(vector<variable>* pvecV)
{
 vector< long >::const_iterator citL;
// variable m_vResult;
// note the use of m_vResult means strong type constraints are placed on result

 if (m_eState!=ceqReadyToSolve)
	return CANNOT_EVALUATE;

 vector< csvVariable > vVals;
 vVals.reserve(m_vValueInds.size());

 ASSERT2(m_vValueInds.size()>0); // to protect against bug being reintroduced

 for (citL = m_vValueInds.begin(); citL != m_vValueInds.end(); citL++)
	vVals.push_back(csvVariable((*pvecV)[*citL]));


 m_vResult = m_pcsvLookup->interpolate(m_vRefInds,m_iLookup,vVals);

 if ((m_bWarnOnce)&&(m_vResult==variable(CSV_CANNOT_EVALUATE)))
	{
	SYMERRORTOK("There may be a problem evaluating in the lookup equation during the run, check results.",errWarning,m_pctLeft);
	m_bWarnOnce = false;
	}

 return m_vResult; 
}	



///////////////////////////////////////////////////////////
// Function name	: CEqLookup::evaluate
// Description	    : 
// Return type		: variable 
// Argument         : vector<variable>* pvecV
///////////////////////////////////////////////////////////
variable CEqLookup::evaluate(vector<variable>* pvecV)
{

	ASSERT2(canEvaluate());
	ASSERT2(pvecV!=NULL);

	if ((!pvecV)&&(!canEvaluate()))
		return CANNOT_EVALUATE; // not great - but don't want to fail here if not debug
	

	if (m_eState!=ceqReadyToSolve)
			return CANNOT_EVALUATE;


	return getValue(pvecV);

}


///////////////////////////////////////////////////////////
// Function name	: CEqLookup::setupExpression
// Description	    : 
// Return type		: bool 
// Argument         : list<CEquation*>* pvecpEquations
// Argument         : CVarClassFactory* pvcf
// Argument         : ostream& osErrReport/*=cerr*/
///////////////////////////////////////////////////////////
bool CEqLookup::setupExpression(list<CEquation*>* pvecpEquations, CVarClassFactory* pvcf, ostream& osErrReport/*=cerr*/)
{
	bool bResult = true;
	vector< CToken* >::const_iterator cit;

	if (!pvcf) // should never happen, but need to handle as its being used
		{
		SYMERRORLITE("Undefined information in the software",errInternal);
		return false;
		}

	
	m_iIndex = m_pctLeft->getRootTokenPt()->getIndex();

	ASSERT2(m_iIndex>=0);

	for (cit=m_vpctRight.begin();cit!=m_vpctRight.end();cit++)
		m_vValueInds.push_back((*cit)->getRootTokenPt()->getIndex());



	if (m_vValueInds.size())
		m_eState = ceqReadyToSolve;
		else
		{
		m_eState = ceqError;
		osErrReport << "<Internal Error*> Unable to fully compile this equation :\n"<<(*this)<<endl;
		SYMERRORTOK("Unable to fully compile this equation",errInternal,m_pctLeft);
		bResult=false;
		}

	// must create a CVarVariable to place at the root defintion
	// note it will be updated prior to being used due to order
	// of variable defintions. ( ie a new value will be used before
	// it can used ).
	m_pvrRight = pvcf->createVariable(m_iIndex);
	m_pctLeft->getRootTokenPt()->setpVarRoot(m_pvrRight);


	return bResult;
}



///////////////////////////////////////////////////////////
// Function name	: setStrongType
// Description	    : 
// Return type		: void 
// Argument         : const vector< varStrongType >& vecst
///////////////////////////////////////////////////////////
/*void setStrongType(const vector< varStrongType >& vecst)
{






}*/


void CEqLookup::setStrongType(const vector< varStrongType >& vecst)
{

	if (m_eState!=ceqReadyToSolve)
		{
		ASSERT2(m_eState==ceqReadyToSolve);
		return;
		}

	ASSERT2(m_iIndex!=NOT_DEFINED);
	ASSERT2(m_iIndex<vecst.size());

	m_pvrRight->setType( vecst[m_iIndex] );
	
	m_vResult.copy(vecst[m_iIndex]); // set up strong type info


}
///////////////////////////////////////////////////////////
// Function name	: CEqLookup::updateValue
// Description	    : 
// Return type		: variable 
// Argument         : vector< variable >* pvecVar
///////////////////////////////////////////////////////////
variable CEqLookup::updateValue(vector< variable >* pvecVar)
{

	if (m_eState!=ceqReadyToSolve)
			return CANNOT_EVALUATE;

#ifndef NDEBUG

	long iIndex; // may make class variable soon
	iIndex = m_pctLeft->getRootTokenPt()->getIndex();
	ASSERT2(m_iIndex==iIndex);

	ASSERT2(iIndex!=NOT_DEFINED);
	ASSERT2(iIndex<pvecVar->size());

#endif

	(*pvecVar)[m_iIndex] = getValue(pvecVar);

	return (*pvecVar)[m_iIndex];
}

void CEqLookup::sendtostream(ostream& os) const 
{

	bool bFirst=true;
	if ((m_eState!=ceqIntiated)&&(m_eState!=ceqReadyToSolve))
			{
			os << "<Warning> Equation no initialised.";
			return;
			}


	ASSERT2(m_pctLeft!=NULL); // catch unexpected bug - yes I know :-)

	os << "lookup "<<m_pctLeft->getString().c_str()<<" from ";

	for(vector< long >::const_iterator it = m_vRefInds.begin();it!=m_vRefInds.end();it++)
		{
		if (bFirst) // do this once only
			os <<",";
			else
			bFirst=false;
		os << m_pcsvLookup->getCell(0,*it)->getString();
		}
	os << " in \""<<m_sFileName.c_str()<<"\" cache "<<m_pcsvLookup->getCacheLevel();

	return;
}

#ifndef NDEBUG

void CEqLookup::sentToAtlTrace() const
{
	bool bFirst=true;
	if ((m_eState!=ceqIntiated)&&(m_eState!=ceqReadyToSolve))
			{
			ATLTRACE("<Warning> Equation no initialised.\n");
			return;
			}


	ASSERT2(m_pctLeft!=NULL); // catch unexpected bug - yes I know :-)

	ATLTRACE("lookup %s from ",m_pctLeft->getString().c_str());

	for(vector< long >::const_iterator it = m_vRefInds.begin();it!=m_vRefInds.end();it++)
		{
		if (bFirst) // do this once only
			ATLTRACE(",");
			else
			bFirst=false;
		ATLTRACE("%s",m_pcsvLookup->getCell(0,*it)->getString());
		}
	ATLTRACE(" in \"%s\" cache %d\n",m_sFileName.c_str(),m_pcsvLookup->getCacheLevel());

	return;
}
#endif



///////////////////////////////////////////////////////////
// Function name	: CEqLookup::expandArrayEquations
// Description	    : 
// Return type		: long 
// Argument         : list<CToken>& ltToks
// Argument         : vector<CEquation*>& rvecNewEqs
// Argument         : SetPtCTokenStringSearch& rsetPtToksUnique
///////////////////////////////////////////////////////////
long CEqLookup::expandArrayEquations( list<CToken>& ltToks, vector<CEquation*>& rvecNewEqs, SetPtCTokenStringSearch& rsetPtToksUnique ) const
{
 CArray* pa = m_pctLeft->getArray();
 CEquationFactory* peqf = CEquationFactory::instance();

 if ((!pa)||(!peqf))
	return -1;

 if (!pa->first())
	return -1;

 do
 {
	CEquation* pe = newtrack CEqLookup(*this);
	if (!pe)
		{
		SYMERRORLITE("Low memory",errSystem);
		return -1;
		}
	
	peqf->lookAfterLifeCycle(pe); // life cycle managed by factory
	rvecNewEqs.push_back(pe); 
	pe->setArrayIndex(pa->getIndex(),ltToks,rsetPtToksUnique);
 }
 while(pa->next());

 return rvecNewEqs.size();
}



