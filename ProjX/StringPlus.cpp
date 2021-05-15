// StringPlus.cpp: implementation of the CStringPlus class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "global.h"
#include "StringPlus.h"
#include <assert.h>
#include <math.h>
#include "Symlix\ErrorFactory.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStringPlus::CStringPlus():m_lMinusCount(NOT_DEFINED),string()
{

}

CStringPlus::CStringPlus(const string& s):string(s),bRequestOnNumber(false)
{

}

CStringPlus::CStringPlus(const CStringPlus& csh):string(csh.c_str()),bRequestOnNumber(false)
{

}


CStringPlus::CStringPlus(const char* sIn ):string(sIn),bRequestOnNumber(false)
{

}

/*
CStringPlus::~CStringPlus()
{

}*/


string CStringPlus::m_sEmpty = _T("");

///////////////////////////////////////////////////////////
// Function name	: CStringPlus::isExponent
// Description	    : Exponents are either XXXE01 or XXXE-01
//                    this routine will reject power higher than +-99
// Return type		: bool 
///////////////////////////////////////////////////////////
bool CStringPlus::isExponent() const
{
	// NYI - and may not be - see if there is a case for it latter
	assert(false);
	return false;
}



///////////////////////////////////////////////////////////
// Function name	: CStringPlus::isIterative
// Description	    : Is this iterative - ie ended in a g_IterationPostfix
// Return type		: bool 
///////////////////////////////////////////////////////////
bool CStringPlus::isIterative() const
{ 
	long iLen = this->length()-1;
	long iPos = this->find_last_of(g_IterationPostfix);

	return (iLen==iPos);

}


///////////////////////////////////////////////////////////
// Function name	: CStringPlus::isNumber
// Description	    : 
// Return type		: bool 
///////////////////////////////////////////////////////////
bool CStringPlus::isNumber()
{

	// lets deal with the minuses first
	m_lMinusCount=countOccurances(g_Minus);

	switch(m_lMinusCount)
	{
		case 0:
			m_lMinus1=m_lMinus2=string::npos;
			break;
		case 1:
			m_lMinus1=find(g_Minus);
			m_lMinus2=string::npos;
			break;
		case 2:
			m_lMinus1=find(g_Minus);
			m_lMinus2=find(g_Minus,m_lMinus1+1);
			break;
		default:
			return false;
	}

	m_lExpCount=countOccurances(g_Expon);

	switch(m_lExpCount)
	{
		case 0:
			m_lExp=string::npos;
			break;
		case 1:
			m_lExp=find(g_Expon);
			break;
		default:
			return false;
	}


	m_lPointCount=countOccurances(g_Point);

	switch(m_lPointCount)
	{
		case 0:
			m_lPoint=string::npos;
			break;
		case 1:
			m_lPoint=find(g_Point);
			break;
		default:
			return false;
	}


	// check for cases which are excluded
	/*
	2minus - but 1st not at front or second not after Exp
	1 minus either not at front or after Exp
	Point after Exp
	*/
	if (m_lMinusCount>0)
		{
		if (m_lMinusCount==1)
			{
			if ((m_lExpCount==0)&&(m_lMinus1!=0))
					return false;
					else
					if ((m_lMinus1!=0)&&(m_lMinus1!=m_lExp+1))
							return false;	

			}
			else
			if (m_lMinusCount==2)
				{
				if(m_lExpCount==0)
						return false;
				if((m_lMinus1!=0)||(m_lMinus2!=m_lExp+1))
						return false;
				}
		}


	if (m_lExpCount==1)
		{
		if ((m_lMinus1==m_lExpCount+1)||(m_lMinus2==m_lExpCount+1))
			if (m_lExp>length()-2) // the expoent too big
				return false;
		}

	if ((m_lPointCount==1)&&(m_lExpCount==1))
		{
		if (m_lPoint>=m_lExp)
			return false;
		}

	// need to check for any prohibitted characters
	long iT=0;
	while( iT<length())
	{
		if (((*this)[iT]<48)||((*this)[iT]>57))
			{
			switch ((*this)[iT])
				{
				case c_Expon: // allows for changes in character code - as if
				case c_Point:
				case c_Minus:
				break;
				default:
					return false;
				}

			}
	
		iT++;
	}	


	return true;
}



///////////////////////////////////////////////////////////
// Function name	: CStringPlus::getLessDerivative
// Description	    : strip out derivate - so dX/dt returns X
// Return type		: string 
///////////////////////////////////////////////////////////
string CStringPlus::getLessDerivative() const
{

	long iBegin = this->find_first_of("d")+1;
	long iEnd = this->find_first_of("/"); 

	return ( ((iBegin>0)&&(iEnd>0))  ? this->substr(iBegin,iEnd-iBegin) : (*this));


}


///////////////////////////////////////////////////////////
// Function name	: CStringPlus::getLessIterative
// Description	    : Remove last single quote
// Return type		: CStringPlus 
///////////////////////////////////////////////////////////
string CStringPlus::getLessIterative() const
{
	long iBegin = 0;
	long iEnd = this->find_last_of(g_IterationPostfix);

	return ( (iEnd>0) ? this->substr(iBegin,iEnd) : (*this));
}



///////////////////////////////////////////////////////////
// Function name	: CStringPlus::withDerivBracketedIndex
// Description	    : for dx/dt give dx[i]/dt
// Return type		: string 
// Argument         : const long iIndex
///////////////////////////////////////////////////////////
string CStringPlus::withDerivBracketedIndex(const long iIndex) const
{
	CStringPlus str("d");
	str += this->getLessDerivative();
	str = str.withBracketedIndex(iIndex);
	str += "/dt";

	return str;
}


string CStringPlus::withBracketedIndex(const long iIndex) const
{
	char sBuf[50]; // more than enough
	long len = this->length();
	bool bInterative = false;

	if ((iIndex>2147483647)||(iIndex<0))
		{
		SYMERRORLITE("Index value out of range",errSyntax);
		return "Out of range";
		}

	string str = *this;

	ASSERT2(strlen(g_IterationPostfix)==1);

	// do we have a interative variable ?
	if ((len>0)&&(str[len-1]==g_IterationPostfix[0]))
		{
		 bInterative = true;
		 str = this->substr(0,(len-1));
		}
	str.append(g_OpenSquareBracket);
	str.append(itoa(iIndex,sBuf,10));
	str.append(g_CloseSquareBracket);

	if (bInterative)
			str.append(g_IterationPostfix);

	return str;
}



#ifdef UNITTESTS

///////////////////////////////////////////////////////////
// Function name	: CStringPlus::runUnitTests
// Description	    : Unit tests for this class
// Return type		: bool 
///////////////////////////////////////////////////////////
bool CStringPlus::runUnitTests()
{
	bool bResult = true;

	try
	{

	CStringPlus cspExp1("-100.0345E-99");
	CStringPlus cspExp2("-100.0345E01");
	CStringPlus cspExp3("-100.0345E+01");
	CStringPlus cspExp4("-100.0345E101");
	CStringPlus cspExp5("100.0345E-01");

/*	assert(cspExp1.isExponent()); // true
	assert(cspExp2.isExponent()); // true
	assert(!cspExp3.isExponent());//		false
	assert(!cspExp4.isExponent());//		false
	assert(cspExp5.isExponent());//  true
*/
	CStringPlus cspExp6("-100.0345-E99");
	CStringPlus cspExp7("-100.0345");
	CStringPlus cspExp8("999");
	CStringPlus cspExp9("-999");
	CStringPlus cspExp10("-9/9");
	CStringPlus cspExp11("-100.03-45E99");
	CStringPlus cspExp12("0");

	CStringPlus cspDeriv1("dr/dt");
	CStringPlus cspDeriv2("dr[1]/dt");
	CStringPlus cspDeriv3("d/dt");
	CStringPlus cspDeriv4("ddt");
	CStringPlus cspDeriv5("dword/dt");
	CStringPlus cspDeriv6("dword/dr");

	assert(cspExp1.isNumber()); // true
	assert(cspExp2.isNumber()); // true
	assert(!cspExp3.isNumber()); //		false
	assert(cspExp4.isNumber()); // true
	assert(cspExp5.isNumber()); // true
	assert(!cspExp6.isNumber()); //		false
	assert(cspExp7.isNumber()); // true
	assert(cspExp8.isNumber()); // true
	assert(cspExp9.isNumber()); // true
	assert(!cspExp10.isNumber()); //	false
	assert(!cspExp11.isNumber());// true
	assert(cspExp12.isNumber()); // true


	assert(cspExp1.getNumber()==-100.0345E-99); // this may fail perhaps over double limit - check
	assert(cspExp12.getNumber()==0); // stops problems with length of number leading to -48

	ATLTRACE("cspDeriv1.getLessDerivative() %s to %s\n",cspDeriv1.c_str(),cspDeriv1.getLessDerivative().c_str());
	ATLTRACE("cspDeriv2.getLessDerivative() %s to %s\n",cspDeriv2.c_str(),cspDeriv2.getLessDerivative().c_str());
	ATLTRACE("cspDeriv3.getLessDerivative() %s to %s\n",cspDeriv3.c_str(),cspDeriv3.getLessDerivative().c_str());
	ATLTRACE("cspDeriv4.getLessDerivative() %s to %s\n",cspDeriv4.c_str(),cspDeriv4.getLessDerivative().c_str());
	ATLTRACE("cspDeriv5.getLessDerivative() %s to %s\n",cspDeriv5.c_str(),cspDeriv5.getLessDerivative().c_str());
	ATLTRACE("cspDeriv6.getLessDerivative() %s to %s\n",cspDeriv6.c_str(),cspDeriv6.getLessDerivative().c_str());

	assert(cspDeriv1.getLessDerivative().compare("r")==0);
	assert(cspDeriv2.getLessDerivative().compare("r[1]")==0);
	assert(cspDeriv3.getLessDerivative().compare("")==0);
	assert(cspDeriv4.getLessDerivative().compare("ddt")==0);
	assert(cspDeriv5.getLessDerivative().compare("word")==0);
	assert(cspDeriv6.getLessDerivative().compare("word")==0);

	CStringPlus cspBracks1("asd[12+n*r]]");
	ATLTRACE("cspBracks1.getBetweenSqrBrackets().compare('12+n*r]') = %s\n",cspBracks1.getBetweenSqrBrackets().c_str());
	assert(cspBracks1.getBetweenSqrBrackets().compare("12+n*r]")==0);
	CStringPlus cspBracks2("asd[1]");
	ATLTRACE("cspBracks2.getBetweenSqrBrackets().compare('asd[1]') = %s\n",cspBracks2.getBetweenSqrBrackets().c_str());
	assert(cspBracks2.getBetweenSqrBrackets().compare("1")==0);
	CStringPlus cspBracks3("asd[]][]");
	ATLTRACE("cspBracks3.getBetweenSqrBrackets().compare('asd[]][]') = %s\n",cspBracks3.getBetweenSqrBrackets().c_str());
	assert(cspBracks3.getBetweenSqrBrackets().compare("]][")==0);
	CStringPlus cspBracks4("asd[12+n*r]");
	ATLTRACE("cspBracks4.getBetweenSqrBrackets().compare('asd[12+n*r]') = %s\n",cspBracks4.getBetweenSqrBrackets().c_str());
	assert(cspBracks4.getBetweenSqrBrackets().compare("12+n*r")==0);
	CStringPlus cspBracks5("asd");
	ATLTRACE("cspBracks5.getBetweenSqrBrackets().compare('asd') = %s\n",cspBracks5.getBetweenSqrBrackets().c_str());
	assert(cspBracks5.getBetweenSqrBrackets().compare("")==0);
	CStringPlus cspBracks6("");
	ATLTRACE("cspBracks6.getBetweenSqrBrackets().compare('') = %s\n",cspBracks6.getBetweenSqrBrackets().c_str());
	assert(cspBracks6.getBetweenSqrBrackets().compare("")==0);

	CStringPlus cspBracks7("asd");
	ATLTRACE("cspBracks7 = '%s'\n",cspBracks7.c_str());
	ATLTRACE("cspBracks7.getSubsIntoSqrBrackets('n') %s\n",cspBracks7.getSubsIntoSqrBrackets("n").c_str());
	assert(cspBracks7.getSubsIntoSqrBrackets("n").compare("")==0);

	CStringPlus cspBracks8("asd[meow]");
	ATLTRACE("cspBracks8 = '%s'\n",cspBracks8.c_str());
	ATLTRACE("cspBracks8.getSubsIntoSqrBrackets('n') %s\n",cspBracks8.getSubsIntoSqrBrackets("n").c_str());
	assert(cspBracks8.getSubsIntoSqrBrackets("n").compare("asd[n]")==0);

	CStringPlus cspBracks9("asd[]");
	ATLTRACE("cspBracks9 = '%s'\n",cspBracks9.c_str());
	ATLTRACE("cspBracks9.getSubsIntoSqrBrackets('n') %s\n",cspBracks9.getSubsIntoSqrBrackets("n").c_str());
	assert(cspBracks9.getSubsIntoSqrBrackets("n").compare("asd[n]")==0);

	CStringPlus cspIterate1("x'");
	ATLTRACE("cspIterate1 = '%s'\n",cspIterate1.c_str());
	if (cspIterate1.isIterative())
			ATLTRACE("Iterative found\n");
			else
			ATLTRACE("FAILED to find Iterative\n");
	assert(cspIterate1.isIterative());
	ATLTRACE("cspIterate1.getLessIterative().c_str() = %s\n",cspIterate1.getLessIterative().c_str());


	CStringPlus cspIterate2("x@");
	ATLTRACE("cspIterate2 = '%s'\n",cspIterate2.c_str());
	if (cspIterate2.isIterative())
			ATLTRACE("Iterative found\n");
			else
			ATLTRACE("FAILED to find Iterative\n");
	assert(!cspIterate2.isIterative());
	ATLTRACE("cspIterate2.getLessIterative().c_str() = %s\n",cspIterate2.getLessIterative().c_str());

	}
	catch(...)
	{
	bResult = false;
	cerr << "Unit tests on CStringPlus failed\n";
	}

	return bResult;

}

#endif

///////////////////////////////////////////////////////////
// Function name	: CStringPlus::countOccurances
// Description	    : Find the number of times a character string occurs
// Return type		: long 
// Argument         : const char* sItem
///////////////////////////////////////////////////////////
long CStringPlus::countOccurances(const char* sItem) const
{
	long iCount=0;
	long iT=0;

	while((iT!=string::npos)&&(iT<length()))
	{
	iT=find(sItem,iT);
	if (iT!=npos)
		{
		iCount++;
		iT++;
		}
	}
	
	return iCount;

}


///////////////////////////////////////////////////////////
// Function name	: CStringPlus::getNumber
// Description	    : return number for string as a double - 
//					  if this is not possible then returns NOT_DEFINED
// Return type		: double 
///////////////////////////////////////////////////////////
double CStringPlus::getNumber()
{
// Start critical section - if go to multithread
	double dResult = 0;

	bRequestOnNumber=true;

	
	#ifndef NDEBUG // isNumber must be run now to get internal state correct
	assert(isNumber());
	#else
	
	if (!isNumber())
			{
			bRequestOnNumber=false;
			return NOT_DEFINED;
			}
	#endif

	try
	{

	if (m_lExp!=string::npos)
		{
		dResult = substringNumber(0,m_lExp-1);
		dResult *= pow(10,substringNumber(m_lExp+1,length()-1));
		}
		else
		{
		dResult = substringNumber(0,length()-1);
		}
	
	}
	catch(...)
		{
		// lets make sure bRequestOnNumber = false
		dResult = NOT_DEFINED;

		}


// endif critical section
	bRequestOnNumber=false; // must happen at end
	return dResult;
}


///////////////////////////////////////////////////////////
// Function name	: CStringPlus::substringNumber
// Description	    : Helper function to return a number represented by a section
//                    of the string
// Return type		: double 
// Argument         : long lFrom
// Argument         : long lTo
///////////////////////////////////////////////////////////
double CStringPlus::substringNumber(long lFrom, long lTo)
{
	double dResult=0;
	long iT,iCount,lPower;
	iCount=0;

	#ifndef NDEBUG
	assert(bRequestOnNumber);
	#endif
	if (!bRequestOnNumber) // this must be called from within an approved function
			return NOT_DEFINED;

	for(iT=lTo;iT>=lFrom;iT--)
		{
		if ((iT!=m_lPoint)&&(iT!=m_lMinus1)&&(iT!=m_lMinus2))
			{
			dResult+=((*this)[iT]-48)*pow(10,iCount);
			iCount++;
			}
		}


	// make adjustment if minus at front
	if (m_lMinus1==lFrom)
			dResult*=-1;
	if (m_lMinus2==lFrom)
			dResult*=-1;
	// make adjustment for decimal point
	if ((m_lPoint>=lFrom)&&(m_lPoint<=lTo))
		{
		lPower=lTo-m_lPoint;
		dResult /= pow(10,lPower);
		}

	return dResult;

}


///////////////////////////////////////////////////////////
// Function name	: CStringPlus::getBetweenSqrBrackets
// Description	    : If "a[n+1]" then return string "n+1"
// Return type		: string 
///////////////////////////////////////////////////////////
string CStringPlus::getBetweenSqrBrackets() const
{
	long iFrom = this->find_first_of(g_OpenSquareBracket)+1;
	long iTo = this->find_last_of(g_CloseSquareBracket);
	
	if ((iFrom==this->npos)||(iTo==this->npos))
		return m_sEmpty;

	if (iFrom>iTo)
		return m_sEmpty;

	return this->substr(iFrom,iTo-iFrom);

}

string CStringPlus::getSubsIntoSqrBrackets(const char* sInsert) const
{
	string sResult;
	long iFrom = this->find_first_of(g_OpenSquareBracket);
	long iTo = this->find_last_of(g_CloseSquareBracket); // as perhaps both miss!ing 
	
	if ((iFrom==this->npos)||(iTo==this->npos))
		return m_sEmpty;

	sResult = this->substr(0,iFrom);
	sResult.append(g_OpenSquareBracket);
	sResult.append(sInsert);
	sResult.append(g_CloseSquareBracket);
	return sResult;
}

