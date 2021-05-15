// Array.cpp: implementation of the Array class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Array.h"
#include "Symlix\ErrorFactory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CArray::CArray():m_pToken(NULL),m_eState(carUninitated),bIndiciesSet(false),m_iInd(0)
{
//	ATLTRACE("CArray constructor called for %x", this);
}

CArray::~CArray()
{

}

const string CArray::m_sNoString = "<Error> No string";

///////////////////////////////////////////////////////////
// Function name	: CArray::checkArrayName
// Description	    : Returns the total array size that would
//                    be indicated by this syntax.
// Return type		: long : 0 if no brackets, -1 if fail otherwise number of index memebers indicated
// Argument         : const CToken& ct
///////////////////////////////////////////////////////////
long CArray::checkArrayName(const CToken& ct)
{
	long iOpen = NOT_DEFINED;
	long iClose = NOT_DEFINED;
	long iCount;
	char cDelim = ' ';
	const string& str = ct.getString();
	bool bDelimNext = false;

	iOpen = str.find(g_OpenSquareBracket);
	iClose = str.find(g_CloseSquareBracket);

	if ((iOpen<0)||(iClose<0))
		return 0; // as no pairs of brakets used

	if (iClose<iOpen)
		{
		SYMERRORTOK("Brackets are round the wrong way",errSyntax,&ct);
		return -1;
		}

	// acceptable syntax N,N,N:N ( either , or full colon )
	// not acceptable signs, or exponents or decimals


	string sNum;
	long iLast = -1;
	long iThis;
	long iInds =0;

	for(iCount=iOpen+1;iCount<iClose;iCount++)
	{
	
	
		if ((str[iCount]>57)||(str[iCount]<48)) // then its not number
			{
			if ((!bDelimNext)||((str[iCount]!=g_Comma[0])&&(str[iCount]!=g_FullColon[0]))) // and it noty a delim
					{
					// well this won't work will it
					SYMERRORTOK2(str.substr(iOpen,iClose).c_str()," unrecognised character used in array declaration",errSyntax,&ct);
					return -1;
					}
					else
					{
					bDelimNext=false; // can't have two in a row
					iThis = atoi(sNum.c_str());
					if (iThis<=iLast)
							{
							SYMERRORTOK("Index values need to increase left to right",errSyntax,&ct);
							return -1;
							}
						// add indicies
					if ((iLast>0)&&(cDelim==g_FullColon[0]))
							iInds+=iThis-iLast-1;
					iInds++;
					cDelim = str[iCount]; // for next time

					iLast = iThis;
					sNum.erase();
					}
			}
			else
			{
			bDelimNext=true;
			sNum += str[iCount];
			}
	}

	if (iLast>0) // ie there were numbers
		{
			iThis = atoi(sNum.c_str());
			if (iThis<=iLast)
					{
					SYMERRORTOK("Index values need to increase left to right",errSyntax,&ct);
					return -1;
					}
					if ((iLast>0)&&(cDelim==g_FullColon[0]))
							iInds+=iThis-iLast-1;
					iInds++;

		}


	return iInds;


}


///////////////////////////////////////////////////////////
// Function name	: CArray::setIndiciesFromString
// Description	    : 
// Return type		: bool 
// Argument         : const string& str
///////////////////////////////////////////////////////////
bool CArray::setIndiciesFromString(const string& str)
{
	long iOpen = NOT_DEFINED;
	long iClose = NOT_DEFINED;
	long iCount;
	char cDelim = ' ';
	bool bDelimNext = false;
	long iX;
	string sNum;
	long iLast = -1;
	long iThis;
	long iInds =0;

	m_vecIndicies.clear();

	iOpen = str.find(g_OpenSquareBracket);
	iClose = str.find(g_CloseSquareBracket);


	if ((iOpen<0)||(iClose<0))
		return false; // as no pairs of brakets used

	if (iClose<iOpen)
		{
		SYMERRORLITE("Brackets are round the wrong way",errInternal);
		return false;
		}

	// acceptable syntax N,N,N:N ( either , or full colon )
	// not acceptable signs, or exponents or decimals



	for(iCount=iOpen+1;iCount<iClose;iCount++)
	{
	
	
		if ((str[iCount]>57)||(str[iCount]<48)) // then its not number
			{
			if ((!bDelimNext)||((str[iCount]!=g_Comma[0])&&(str[iCount]!=g_FullColon[0]))) // and it noty a delim
					{
					// well this won't work will it
					SYMERRORLITE2(str.substr(iOpen,iClose).c_str()," unrecognised character used in array declaration",errInternal);
					return false;
					}
					else
					{
					bDelimNext=false; // can't have two in a row
					iThis = atoi(sNum.c_str());
					if (iThis<=iLast)
							{
							if (m_pToken)
								{
								SYMERRORTOK("Index values need to increase left to right",errInternal,m_pToken);
								}
								else
								{
								SYMERRORLITE("Index values need to increase left to right",errInternal);
								}
							return false;
							}
						// add indicies
					if ((iLast>0)&&(cDelim==g_FullColon[0]))
							for(iX=iLast+1;iX<iThis;iX++)
								m_vecIndicies.push_back(iX);
					m_vecIndicies.push_back(iThis);
					cDelim = str[iCount]; // for next time

					iLast = iThis;
					sNum.erase();
					}
			}
			else
			{
			bDelimNext=true;
			sNum += str[iCount];
			}
	}

	if (iLast>0) // ie there were numbers
		{
			iThis = atoi(sNum.c_str());
			if (iThis<=iLast)
					{
					if (m_pToken)
						{
						SYMERRORTOK("Index values need to increase left to right",errInternal,m_pToken);
						}
						else
						{
						SYMERRORLITE("Index values need to increase left to right",errInternal);
						}

					return false;
					}
					if ((iLast>0)&&(cDelim==g_FullColon[0]))
							for(iX=iLast+1;iX<iThis;iX++)
								m_vecIndicies.push_back(iX);
					m_vecIndicies.push_back(iThis);

		}

	ASSERT2((m_pToken)&&(m_vecIndicies.size()==checkArrayName(*m_pToken))); // just to check

	bIndiciesSet=true;

	return true;

}


///////////////////////////////////////////////////////////
// Function name	: CArray::setIndiciesFromData
// Description	    : Set up indicies based on data only
// Return type		: bool 
// Argument         : long iStart /*=0*/
///////////////////////////////////////////////////////////
bool CArray::setIndiciesFromData(long iStart /*=0*/)
{
	long iX;
	
	if (m_vecValues.size()<1)
		return false;

	for (iX=iStart;iX<m_vecValues.size()+iStart;iX++)
		m_vecIndicies.push_back(iX);

	bIndiciesSet=true;

	return true;
}


///////////////////////////////////////////////////////////
// Function name	: CArray::Ready
// Description	    : Is the array ready to be used ?
// Return type		: bool 
///////////////////////////////////////////////////////////
bool CArray::Ready() const
{
	return bIndiciesSet;
}


/*friend*/ ostream& operator << (ostream& os, const CArray* pA)
{
	pA->out(os);

	return os;
}


///////////////////////////////////////////////////////////
// Function name	: CArray::cleanUpTokenNameAndSetAsArray
// Description	    : Helper function to get rid of array index info and set as array
// Return type		: void 
///////////////////////////////////////////////////////////
bool CArray::cleanUpTokenNameAndSetAsArray()
{
	long iBracketsOpen;
	const string& str = m_pToken->getString();
	string sNew;

	if (!m_pToken)
			return false;

	m_pToken->setAsArray();
	iBracketsOpen =  str.find(g_OpenSquareBracket);
	if (iBracketsOpen<0)
			return true;

	sNew = str.substr(0,iBracketsOpen);
	m_pToken->setString(sNew);

	return true;

}


///////////////////////////////////////////////////////////
// Function name	: CArray::copy
// Description	    : Helper function to copy all values for CArray
// Return type		: void 
// Argument         : const CArray &rca
///////////////////////////////////////////////////////////
void CArray::copy(const CArray &rca)
{

	m_pToken = rca.m_pToken;
	m_eState = rca.m_eState;
	m_sError = rca.m_sError;
	m_vecIndicies = rca.m_vecIndicies;
	m_vecValues = rca.m_vecValues;
	bIndiciesSet = rca.bIndiciesSet;
	m_iInd = rca.m_iInd;

}


///////////////////////////////////////////////////////////
// Function name	: CArray::first
// Description	    : Go to first index count
// Return type		: bool - true if succeeded
///////////////////////////////////////////////////////////
bool CArray::first()
{
	m_iInd=0;

   return (m_vecIndicies.size()>m_iInd);

}


///////////////////////////////////////////////////////////
// Function name	: CArray::next
// Description	    : Set index count forward one
// Return type		: bool - true if succeeded
///////////////////////////////////////////////////////////
bool CArray::next()
{
	m_iInd++;

   return (m_vecIndicies.size()>m_iInd);
}


///////////////////////////////////////////////////////////
// Function name	: CArray::getIndex
// Description	    : return internal index
// Return type		: long 
///////////////////////////////////////////////////////////
long CArray::getIndex() const
{
	ASSERT2(m_iInd>=0);
	if (m_iInd>=m_vecIndicies.size())
		return NOT_DEFINED;

	return m_vecIndicies[m_iInd];
}


///////////////////////////////////////////////////////////
// Function name	: CArray::getValue
// Description	    : return value pointed to by current index
// Return type		: variable 
///////////////////////////////////////////////////////////
variable CArray::getValue() const
{
	ASSERT2(m_iInd>=0);
	if (m_iInd>=m_vecValues.size())
		return NOT_DEFINED;

	return m_vecValues[m_iInd];
}

#define _CARRAYNUMLIMIT 32

///////////////////////////////////////////////////////////
// Function name	: CArray::getString
// Description	    : 
// Return type		: string 
///////////////////////////////////////////////////////////
string CArray::getString() const
{
	#ifndef NDEBUG
	long iSize = 0;
	#endif
	char sNum[_CARRAYNUMLIMIT];
	long iIndex;

	string sResult = getArrayName();
	sResult += "[";
	iIndex = getIndex();
	if (iIndex!=NOT_DEFINED)
		{
		#ifdef NDEBUG
		sprintf(sNum,"%d",getIndex());
		#else
		iSize=sprintf(sNum,"%d",getIndex());
		ASSERT2(iSize<(_CARRAYNUMLIMIT-2));
		#endif
		sResult += sNum;
		}
		else
		{
		sResult += "NOT_DEFINED";
		}
	sResult += "]";

	return sResult;
}


///////////////////////////////////////////////////////////
// Function name	: CArraySetValue_Impl::addTokenPtVec
// Description	    : Common to all arrays that will set values and need
//                    to accept list of Token pointers.
// Return type		: bool 
// Argument         : const vector< CToken* >& rvecpt
///////////////////////////////////////////////////////////
bool CArraySetValue_Impl::addTokenPtVec(const vector< CToken* >& rvecpt)
{

	ASSERT2(rvecpt.size()==m_vecIndicies.size());
	// only do this if the index sizes match !
	if (rvecpt.size()!=m_vecIndicies.size())
			return false;

	m_vecToks = rvecpt;
	return true;
}

///////////////////////////////////////////////////////////
// Function name	: CArraySetValue_Impl::setupIndexesFromLHSToken
// Description	    : Helper function that set up indicies from LHS Token
// Return type		: bool 
///////////////////////////////////////////////////////////
bool CArraySetValue_Impl::setupIndexesFromLHSToken()
{

	long iOpen = NOT_DEFINED;
	long iClose = NOT_DEFINED;
	long iCount;
	long iX;
	string sNum;
	long iLast = -1;
	long iThis;

	if (!m_pToken) // need to check
			{
			m_sError="LHS value not held in array when internal checks started.";
			m_eState = carError;
			SYMERRORLITE(m_sError.c_str(),errInternal);
			return false;
			}

	const string& str = m_pToken->getString();
	bool bDelimNext=false;

	string sTemp; // for debug
	char cDelim=' ';
	iOpen = str.find(g_OpenSquareBracket);
	iClose = str.find(g_CloseSquareBracket);

	if ((iOpen==std::string::npos)||(iClose==std::string::npos))
			{
			m_sError="LHS array lacked square brackets.";
			m_eState = carError;
			SYMERRORTOK(m_sError.c_str(),errSyntax,m_pToken);
			return false;
			}

	if (iOpen>iClose)
			{
			m_sError="Square brackets the wrong way round.";
			m_eState = carError;
			SYMERRORTOK(m_sError.c_str(),errSyntax,m_pToken);
			return false;
			}
		

	for(iCount=iOpen+1;iCount<iClose;iCount++)
				{
				
				
					if ((str[iCount]>57)||(str[iCount]<48)) // then its not number
						{
						if ((!bDelimNext)||((str[iCount]!=g_Comma[0])&&(str[iCount]!=g_FullColon[0]))) // and it noty a delim
								{
								// well this won't work will it
								SYMERRORTOK2(str.substr(iOpen,iClose).c_str()," unrecognised character used in array declaration and not caught in checks",errInternal,m_pToken);
								ASSERT2(false);
								m_eState = carError;
								}
								else
								{
								bDelimNext=false; // can't have two in a row

								iThis = atoi(sNum.c_str());
								// add this number
								if ((iLast>0)&&(cDelim==g_FullColon[0]))
									for (iX=iLast+1;iX<iThis;iX++)  // so get all the indicies inbetween
										m_vecIndicies.push_back(iX);
								m_vecIndicies.push_back(iThis);
								

								if (iThis<=iLast)
										{
										SYMERRORTOK("Index values need to increase left to right and should have been checked before this point",errInternal,m_pToken);
										ASSERT2(false);
										m_eState = carError;
										}

								iLast = iThis;
								cDelim = str[iCount]; // so this info available next time
								sNum.erase();
								}
						}
						else
						{
						bDelimNext=true;
						sNum += str[iCount];
						}
				}

	if (iLast>0) // ie there were numbers
			{
				iThis = atoi(sNum.c_str());
				if (iThis<=iLast)
						{
						SYMERRORTOK("Index values need to increase left to right - but should have been caught before this warning",errInternal,m_pToken);
						ASSERT2(false);
						m_eState = carError;
						}
				if (cDelim==g_FullColon[0]) // so get all the indicies inbetween
					for (iX=iLast+1;iX<iThis;iX++)
						m_vecIndicies.push_back(iX);
				m_vecIndicies.push_back(iThis);


			}


	return true;
}

