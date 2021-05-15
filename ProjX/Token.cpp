// Token.cpp: implementation of the CToken class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Token.h"
#include <assert.h>
#include "global.h"
#include "Array.h"

#include "TempSetFix.h" // used due to short coming in MVC6 - replace with STL set latter

#ifndef NDEBUG
#include <iostream>
#endif

#include "Symlix/ErrorFactory.h"



CLocation::CLocation():m_iX(NOT_DEFINED),m_iLine(NOT_DEFINED),m_plParent(NULL),m_bHasIt(false),m_iXOrig(NOT_DEFINED)
{

}


CLocation::CLocation( long iLine, long iX, setofwords::iterator& itsw, CLocation* plParent/*=NULL*/):
m_iX(iX),m_iLine(iLine),m_citFile(itsw),m_plParent(plParent),m_bHasIt(false),m_iXOrig(NOT_DEFINED)
{
	
	ASSERT2(iX>=0);
	ASSERT2(iLine>=0);

	ASSERT2((*itsw).len()>0);

}	

CLocation::~CLocation()
{
 delete m_plParent; 
}
	

///////////////////////////////////////////////////////////
// Function name	: CLocation::copy
// Description	    : 
// Return type		: void 
// Argument         : const CLocation& cl
///////////////////////////////////////////////////////////
void CLocation::copy(const CLocation& cl)
{
	m_bHasIt = cl.m_bHasIt;
	if (m_bHasIt)
		m_citFile = cl.m_citFile;
	m_iLine = cl.m_iLine;
	m_iX = cl.m_iX;
	m_iXOrig = cl.m_iXOrig;
	delete m_plParent;
	if (cl.m_plParent)
		m_plParent = newtrack CLocation(*cl.m_plParent);
		else
		m_plParent = NULL;
}

ostream& operator << (ostream& os, const CLocation& cl)
{
	os << "<"<<cl.m_iLine<<","<<cl.m_iX;
	if (cl.m_iXOrig!=NOT_DEFINED)
		os << "," << cl.m_iXOrig;
	os <<":";
	if (cl.m_bHasIt)
		os << cl.m_citFile->c_str();
	if (cl.m_plParent)
		os <<" parent: "<< *cl.m_plParent;
	os << ">";


	return os;
}


///////////////////////////////////////////////////////////
// Function name	: CLocation::operator > 
// Description	    : Greater than
// Return type		: bool
// Argument         : const CLocation& cl
///////////////////////////////////////////////////////////
bool CLocation::operator > (const CLocation& cl ) const
{
	const CLocation* cpLHS = this;
	const CLocation* cpRHS = &cl;

	setofwords::const_iterator citStopBefore;

	if ((!cpLHS->hasFileRef())&&(cpRHS->hasFileRef()))
				return false;

	if ((!cpRHS->hasFileRef())&&(cpLHS->hasFileRef()))
				return true;

	// if both !cpLHS->hasFileRef() and cpRHS->hasFileRef() are false then given lines above can just do test on one
	if ((!cpLHS->hasFileRef())||(this->getRefFile()==cl.getRefFile())) // then in same file -skip deeper checks
		{
		if (this->m_iLine>cl.m_iLine)
			return true;
			else
			if (this->m_iLine<cl.m_iLine)
				return false;
				else // they are equal
				if (this->m_iX>cl.m_iX)
					return true;
					if (this->m_iX<cl.m_iX)
						return false;
						else // they are equal
						return (this->m_iXOrig>cl.m_iXOrig);
		}

	CTempSetFix setFiles;
//	cerr << "cpLHS "<<(*cpLHS)<<endl;

	setFiles.insert(cpLHS->getRefFile());
	while (cpLHS->getParent())
		{
		cpLHS=cpLHS->getParent();
		setFiles.insert(cpLHS->getRefFile());
		}

	bool bFindRHS = false;

//	cerr << "cpRHS "<<(*cpRHS)<<endl;

	while((!bFindRHS)&&(cpRHS))
	{
		if (setFiles.find(cpRHS->getRefFile()))
				bFindRHS=true;
				else
				cpRHS=cpRHS->getParent();
	}

	// if !bFindRHS still then either the LHS is inferred or the RHS is.
	// inferred tokens go to the end.

	if (!bFindRHS)
		{
		// note it is asserted here that heirachy for inferred tokens is never deep
//		cerr << setFiles<<endl;
		string sTemp;
		this->getRefFile()->getString(sTemp);
//		cerr << sTemp.c_str()<<endl;
		if (sTemp.compare(g_TokenNoFile)==0)
			 return false;

		cl.getRefFile()->getString(sTemp);
//		cerr << sTemp.c_str()<<endl;
		if (sTemp.compare(g_TokenNoFile)==0)
			 return true;
		
		// This is an unhandled situation
		ASSERT2(bFindRHS);
		throw 1;
		}

	cpLHS=this; //(again)
	while((cpLHS)&&(cpLHS->getRefFile()!=cpRHS->getRefFile()))
			cpLHS=cpLHS->getParent();

	ASSERT2(cpLHS);
	if (!cpLHS)
			throw 1;

	if (cpLHS->m_iLine>cpRHS->m_iLine)
		return true;
		else
		if (cpLHS->m_iLine<cpRHS->m_iLine)
			return false;
			else // they are equal
			if (cpLHS->m_iX>cpRHS->m_iX)
				return true;
				else
				if (cpLHS->m_iX<cpRHS->m_iX)
					return false;
					else
					return (cpLHS->m_iXOrig>cpRHS->m_iXOrig);
	ASSERT2(false);// should never get here
	throw 1;

/*	
	setofwords::const_iterator citStopBefore;

	if (this->getRefFile()==cl.getRefFile()) // then in same file -skip deeper checks
		{
		if (this->m_iLine>cl.m_iLine)
			return true;
			else
			if (this->m_iLine<cl.m_iLine)
				return false;
				else // they are equal
				return (this->m_iX>cl.m_iX);
		}

	set< setofwords::const_iterator > setFiles;

	while (!cpLHS->getParent())
		{
		setFiles.insert(cpLHS->getRefFile());
		cpLHS=cpLHS->getParent();
		}

	bool bFindRHS = false;

	do
	{
		if (setFiles.find(cpRHS->getRefFile())!=setFiles.end())
				bFindRHS=true;
				else
				cpRHS=cpRHS->getParent();
	}
	while((!bFindRHS)&&(!cpRHS->getParent()));

	// if there are no coincidences then something is wrong as it is
	// a requirement that the model is routed in one file. Need to
	// raise this as an fault.
	ASSERT2(bFindRHS);
	if (!bFindRHS) // then its time to crash in the build version - bye bye world
			throw 1;

	cpLHS=this; //(again)
	while((cpLHS)&&(cpLHS->getRefFile()!=cpRHS->getRefFile()))
			cpLHS=cpLHS->getParent();

	ASSERT2(cpLHS);
	if (!cpLHS)
			throw 1;

	if (cpLHS->m_iLine>cpRHS->m_iLine)
		return true;
		else
		if (cpLHS->m_iLine<cpRHS->m_iLine)
			return false;
			else // they are equal
			return (cpLHS->m_iX>cpRHS->m_iX);
	ASSERT2(false);// should never get here
	throw 1;*/
	return false;

}


///////////////////////////////////////////////////////////
// Function name	: CLocation::operator == 
// Description	    : 
// Return type		: bool
// Argument         : const CLocation& cl
///////////////////////////////////////////////////////////
bool CLocation::operator == (const CLocation& cl ) const
{
	bool bResult = (m_iX==cl.m_iX);

	bResult &= (m_iXOrig==cl.m_iXOrig);
	bResult &= (m_iLine==cl.m_iLine);
	bResult &= (m_bHasIt==cl.m_bHasIt);

	if (m_bHasIt)
		bResult &= (m_citFile==cl.m_citFile);

	if (!m_plParent)
		bResult &= (m_plParent==cl.m_plParent);
		else
		if (!cl.m_plParent)
			bResult=false;
			else
			bResult &= ((*m_plParent)==(*cl.m_plParent));


	return bResult;
}


///////////////////////////////////////////////////////////
// Function name	: CLocation::setParent
// Description	    : Make a dynamic copy of parent location
// Return type		: void 
// Argument         : CLocation* pcl
///////////////////////////////////////////////////////////
void CLocation::setParent(const CLocation* pcl)
{
	delete m_plParent;
	if (!pcl)
		{
		m_plParent=NULL;
		return;
		}

	m_plParent= newtrack CLocation(*pcl);

}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////
// Function name	: CToken::CToken
// Description	    : Default constructor
// Return type		: 
///////////////////////////////////////////////////////////
CToken::CToken():
m_eToken(ctNotDefined),m_sToken(""),m_Location(),m_ptCTtoSame(NULL),m_iIndex(NOT_DEFINED),m_pcvr(NULL),m_etatArrayState(atNormal),m_pArray(NULL),m_pvecChildren(NULL),m_iReserveType(NOT_DEFINED),m_ptCTtoIterativeValue(NULL)
{

}


///////////////////////////////////////////////////////////
// Function name	: CToken::CToken
// Description	    : Copy constructor
// Return type		: 
// Argument         : const CToken& cT
///////////////////////////////////////////////////////////
CToken::CToken(const CToken& cT ):
m_eToken(ctNotDefined),m_sToken(""),m_Location(),m_ptCTtoSame(NULL),m_ptCTtoDerivValue(NULL),m_iIndex(NOT_DEFINED),m_pcvr(NULL),m_etatArrayState(atNormal),m_pArray(NULL),m_pvecChildren(NULL),m_iReserveType(NOT_DEFINED),m_ptCTtoIterativeValue(NULL)
{

	Copy(cT);
}


///////////////////////////////////////////////////////////
// Function name	: CToken::CToken
// Description	    : 
// Return type		: 
// Argument         : const long& iL
// Argument         : const long& iX
// Argument         : const char* sToken
///////////////////////////////////////////////////////////
/*CToken::CToken(const long& iL, const long& iX, const char* sToken, eTokenType eType ):
m_eToken(eType),m_sToken(sToken),m_iLine(iL),m_iX(iX),m_ptCTtoSame(NULL),m_ptCTtoDerivValue(NULL),m_iIndex(NOT_DEFINED),m_pcvr(NULL)
{
#ifndef NDEBUG
assert(m_iLine>=0);
assert(m_iX>=0);
assert(m_sToken.length()>0);
#endif
}*/


///////////////////////////////////////////////////////////
// Function name	: CToken::CToken
// Description	    : For creating tokens with no iX or iLine - must be of type ctVariable
// Return type		: 
// Argument         : const string& sToken
// Argument         : eTokenType eType
// Argument         : setofwords::iterator& it
///////////////////////////////////////////////////////////
CToken::CToken(const string& sToken, eTokenType eType, setofwords::const_iterator& cit ):
m_eToken(eType),m_sToken(sToken),m_Location(),m_ptCTtoSame(NULL),m_ptCTtoDerivValue(NULL),m_iIndex(NOT_DEFINED),m_pcvr(NULL),m_etatArrayState(atNormal),m_pArray(NULL),m_pvecChildren(NULL),m_iReserveType(NOT_DEFINED),m_ptCTtoIterativeValue(NULL)
{
	m_Location.setRefFile(cit);

	ASSERT2(m_sToken.length()>0);
	ASSERT2(eType==ctVariable);
}

///////////////////////////////////////////////////////////
// Function name	: CToken::CToken
// Description	    : States need to be either ctDelim, ctNotDefined, ctMacroKeyWord or ctNumber
// Return type		: 
// Argument         : const long& iL
// Argument         : const long& iX
// Argument         : const string& sToken
///////////////////////////////////////////////////////////
CToken::CToken(const long& iL, const long& iX, const string& sToken, setofwords::const_iterator& cit, eTokenType eType, bool bPartArrayFlag /*= false*/  ):
m_eToken(eType),m_sToken(sToken),m_Location()/*,m_iLine(iL),m_iX(iX)*/,m_ptCTtoSame(NULL),m_ptCTtoDerivValue(NULL),m_iIndex(NOT_DEFINED),m_pcvr(NULL),m_etatArrayState(atNormal),m_pArray(NULL),m_pvecChildren(NULL),m_iReserveType(NOT_DEFINED),m_ptCTtoIterativeValue(NULL)
{

	if (bPartArrayFlag)
		m_etatArrayState = atPartOfArray;


	ASSERT2(!(bPartArrayFlag&&(eType==ctNumber))); // indicating trouble to come

	m_Location.setLocation(iL,iX);
	m_Location.setRefFile(cit);
#ifndef NDEBUG

// This switch code is to check states are only of a defined type
switch(eType)
{
	case ctDelim:
	case ctMacroKeyWord:
	case ctNotDefined:
	case ctNumber:
	case ctName:
	// finde nothing to worry about
		break;
	default:
		assert(false);
	break;
}

assert(m_Location.getiLine()>=0);
assert(m_Location.getiX()>=0);
assert(m_sToken.length()>0);
#endif
}

///////////////////////////////////////////////////////////
// Function name	: CToken::~CToken
// Description	    : Destructor
// Return type		: 
///////////////////////////////////////////////////////////
CToken::~CToken()
{
	delete m_pvecChildren;
}


///////////////////////////////////////////////////////////
// Function name	: CToken::Copy
// Description	    : 
// Return type		: void 
// Argument         : const CToken &cT
///////////////////////////////////////////////////////////
void CToken::Copy(const CToken &cT)
{
	m_Location = cT.m_Location;
	m_eToken = cT.m_eToken;
	m_sToken = cT.m_sToken;
	m_ptCTtoSame = cT.m_ptCTtoSame;
	m_ptCTtoDerivValue = cT.m_ptCTtoDerivValue;
	m_ptCTtoIterativeValue = cT.m_ptCTtoIterativeValue;
	m_iIndex = cT.m_iIndex;
	m_pcvr = cT.m_pcvr;
	m_etatArrayState = cT.m_etatArrayState;
	m_pArray = cT.m_pArray;
	if (m_pvecChildren)
			delete m_pvecChildren;

	if (cT.m_pvecChildren)
		{
		m_pvecChildren = newtrack vector< CToken* >;
		if (!m_pvecChildren)
			{
			SYMERRORLITE("Out of memory",errSystem);
			return;
			}
		(*m_pvecChildren) = (*(cT.m_pvecChildren));
		}
		else
		m_pvecChildren = NULL;
	m_iReserveType = cT.m_iReserveType;


}


///////////////////////////////////////////////////////////
// Function name	: = 
// Description	    : 
// Return type		: CToken&
// Argument         : const CToken& cT
///////////////////////////////////////////////////////////
CToken& CToken::operator = (const CToken& cT)
{
	Copy(cT);
	return *this;
}


///////////////////////////////////////////////////////////
// Function name	: == 
// Description	    : 
// Return type		: bool
// Argument         : const CToken& cT
///////////////////////////////////////////////////////////
bool CToken::operator == (const CToken& cT) const
{
	bool bResult;

	bResult = cT.m_Location==m_Location;
	bResult = bResult && ( cT.m_eToken==m_eToken);
	if (bResult) // only worth doing if all same so far
		bResult = cT.m_sToken.compare(m_sToken)==0;


	return bResult;
}


///////////////////////////////////////////////////////////
// Function name	: CToken::greaterThan
// Description	    : 
// Return type		: bool 
// Argument         : const CToken& cT
///////////////////////////////////////////////////////////
bool CToken::greaterThan(const CToken& cT) const
{

	if (m_Location.getiLine()==NOT_DEFINED)
		if (cT.m_Location.getiLine()==NOT_DEFINED)
			return m_sToken.compare(cT.m_sToken)>0;
			else
			return true; // place it at the end
	
	if (m_Location > cT.m_Location)
			return true;

	return false;

}


///////////////////////////////////////////////////////////
// Function name	: CToken::operator > 
// Description	    : 
// Return type		: bool
// Argument         : const CToken& cT
///////////////////////////////////////////////////////////
bool CToken::operator > (const CToken& cT) const
{
	return greaterThan(cT);
}




///////////////////////////////////////////////////////////
// Function name	: < 
// Description	    : 
// Return type		: bool CToken::operator 
// Argument         : const CToken& cT
///////////////////////////////////////////////////////////
bool CToken::operator < (const CToken& cT) const
{
	if (*this==cT) /// need to catch the case where they are the same
		return false;

	return !greaterThan(cT);

}


/*friend*/ /*ostream& operator << (ostream& os, const CToken* cT)
{
	os << *cT;
	return os;
}*/

/*friend*/ ostream& operator << (ostream& os, const CToken& cT)
//ostream& CToken::operator << (ostream& os)
{
	os << cT.m_Location <<" ";
	os << "(";
	os << cT.m_Location.getiLine();
	os << ",";
	os << cT.m_Location.getiX();
	if (cT.m_Location.hasFileRef())
			{
			os << ",";
			os << (*(cT.m_Location.getRefFile()));
			}
	os << "): '";
	os << cT.m_sToken.c_str();
	os << "' [";
	switch (cT.getType())
		{
		case ctDefinedNotAssigned:
			os <<"ctDefinedNotAssigned";
			break;
		case ctComment:
			os <<"ctComment";
			break;
		case ctVariable:
			os <<"ctVariable";
			break;
		case ctDepVariable:
			os <<"ctDepVariable";
			break;
		case ctSubsVariable:
			os <<"ctSubsVariable";
			break;
		case ctIndVariable:
			os <<"ctIndVariable";
			break;
		case ctDelim:
			os <<"ctDelim";
			break;
		case ctNotDefined:
			os <<"ctNotDefined";
			break;
		case ctNumber:
			os <<"ctNumber";
			break;
		case ctDerivative:
			os <<"ctDerivative";
			break;
		case ctEventKeyWord:
			os <<"ctEventKeyWord";
			break;
		case ctSolverKeyWord:
			os <<"ctSolverKeyWord";
			break;
		case ctEquationKeyWord:
			os <<"ctEquationKeyWord";
			break;
		case ctArrayKeyWord:
			os <<"ctArrayKeyWord";
			break;
		case ctMacroKeyWord:
			os <<"ctMacroKeyWord";
			break;
		case ctName:
			os <<"ctName";
			break;
		case ctTypeModifier:
			os <<"ctTypeModifier";
			break;
		case ctUserDefined:
			os <<"ctUserDefined";
			break;
		default:
			os << "**Not Recognised**";
			break;

		}
	os <<" , ";
	switch (cT.getArrayType())
		{
		case atNormal:
			os <<"atNormal";
			break;
		case atArray:
			os <<"atArray";
			break;
		case atPartOfArray:
			os <<"atPartOfArray";
			break;
		default:
			os <<"**Array Not Recognised**";
			break;
		}
	if (cT.isReserved())
		os << ", Reserved " << cT.getReserveType();
	os << " ] ";

	if (cT.getArray())
		os << "<#Link array#> '"<< cT.getArray()->getArrayName().c_str() <<"', ";

	if (cT.HasAParent())
		os << " <#has parent#> " << cT.getRootToken();

	if (cT.m_iIndex!=NOT_DEFINED)
		os << " index ="<<cT.m_iIndex;

	if (cT.m_pcvr)
		os << " CVarRoot assigned";

	return os;

}


///////////////////////////////////////////////////////////
// Function name	: CToken::TrimForChar
// Description	    : Remove any characters c at the start and end of the m_sToken
// Return type		: void 
// Argument         : const char c
///////////////////////////////////////////////////////////
void CToken::TrimForChar(const char c)
{
	long lleft=0;
	long lright=m_sToken.length()-1;
	bool bStop = false;

	while((!bStop)&&(lleft<lright))
		{
		long lTok = m_sToken[lleft];
		if (m_sToken[lleft]==c)
					lleft++;
				else
					bStop=true;
		}
	bStop=false;
	while((!bStop)&&(lright>=lleft))
		{
		long lTok = m_sToken[lright];
		if (m_sToken[lright]==c)
					lright--;
				else
					bStop=true;
		}
	m_sToken = m_sToken.substr(lleft,lright-lleft+1);

}


///////////////////////////////////////////////////////////
// Function name	: CToken::ReplaceAllChar
// Description	    : To allow some characters to be swapped - eg tabs for spaces
// Return type		: void 
// Argument         : const char c
// Argument         : const char cNew
///////////////////////////////////////////////////////////
void CToken::ReplaceAllChar(const char c, const char cNew)
{
	long iCount=0;
	long iLen=m_sToken.length();

	while(iCount<iLen)
		{
		if (m_sToken[iCount]==c)
			m_sToken[iCount]=cNew;
		iCount++;
		}


}

///////////////////////////////////////////////////////////
// Function name	: CToken::AssignParent
// Description	    : All variables should have only one parent
// Return type		: bool 
// Argument         : CToken *pCTParent
///////////////////////////////////////////////////////////
bool CToken::AssignParent(CToken *pCTParent)
{
	ASSERT2(pCTParent!=NULL);
	if ((pCTParent==NULL)||(!IsOfType(ctVariable)))
		return false; // as it is not possible to assign to a Token that is not a variable

	ASSERT2(this!=pCTParent); // this is going to cause infinate loops !
	#ifndef NDEBUG
	if (pCTParent->IsOfType(ctComment))
		ATLTRACE("Attempting to make %s a parent but is of type ctComment\n",pCTParent->getString().c_str());
	#endif

	ASSERT2(pCTParent->IsOfType(ctVariable)); // this is more serious as should never have occured

	if (!pCTParent->IsOfType(ctVariable))
		return false; // need to cover this happening in build version

	m_ptCTtoSame = pCTParent;
	// and the parent gains a child
	pCTParent->addChild(this);

	return (m_ptCTtoSame==pCTParent);
}


///////////////////////////////////////////////////////////
// Function name	: CToken::getPointer
// Description	    : return pointer to this or root variable, if it exists
// Return type		: CToken* 
///////////////////////////////////////////////////////////
CToken* CToken::getPointer()
{
	if ((IsOfType(ctVariable))&&(m_ptCTtoSame!=NULL))
			return m_ptCTtoSame;
	
	return this; // by default
}



///////////////////////////////////////////////////////////
// Function name	: CToken::getRootToken
// Description	    : 
// Return type		: const CToken& 
///////////////////////////////////////////////////////////
const CToken& CToken::getRootToken() const
{
	if (HasAParent())
		return m_ptCTtoSame->getRootToken();
	return *this;


}

#ifndef NDEBUG // otherwise defined in header
bool CToken::IsOfType(const eTokenType eTest) const
{
 return eTest==m_eToken;
}
#endif

bool CToken::IsOfTypeVariable() const
{
	bool bResult;
	switch(m_eToken)
		{
		case ctVariable:
		case ctDepVariable:
		case ctIndVariable:
		case ctSubsVariable:
			bResult = true;
			break;
		default:
			bResult = false;
		}


	return bResult;
}


void CToken::setToParentType()
{
	if (HasAParent())
			setType(getRootToken().getType());
}

bool CToken::setToDepVariable()
{
	if (m_eToken!=ctVariable) // can only be assigned from variable state
		return false;

	m_eToken = ctDepVariable;
	return true;	
}

bool CToken::setToIndVariable()
{
	if (m_eToken!=ctVariable) // can only be assigned from variable state
		return false;

	m_eToken = ctIndVariable;
	return true;
}

bool CToken::setToSubsVariable()
{
	if (m_eToken!=ctVariable) // can only be assigned from variable state
		return false;

	m_eToken = ctSubsVariable;
	return true;
}

string CToken::getVariableFromDerivative(const string& sDerv)
{
	int iDiv,iD;
	iD = sDerv.find_first_of("d")+1;
	iDiv = sDerv.find_first_of("/");

#ifndef NDEBUG
	assert((iD!=string::npos)&&(iDiv!=string::npos));
#endif

	if ((iD==string::npos)||(iDiv==string::npos))
		{
		SYMERRORLITE2("Trying to get a variable from a derivative but an error has occured: ",sDerv.c_str(),errInternal);
		return string("<Error#>");
		}

	return sDerv.substr(iD,(iDiv-iD));

}

bool CToken::setDervivativeVariable( CToken& ct) 
{
	// first check this is a derviavte
	if (!IsOfType(ctDerivative))
					return false;
	// check Token is of type variable
	if (!ct.IsOfTypeVariable())
					return false;
	#ifndef NDEBUG // just to check
	assert(CToken::getVariableFromDerivative(this->m_sToken).compare(ct.getString())==0);
	#endif

	m_ptCTtoDerivValue = &ct;

	return true;
}

bool CToken::setIterativeVariable( CToken& ct) 
{
	// first check this is a derviavte
	if (!this->IsIterative())
					return false;
	// check Token is of type variable
	if (!ct.IsOfTypeVariable())
					return false;
	#ifndef NDEBUG // just to check
	assert(this->getString().getLessIterative().compare(ct.getString())==0);
	#endif

	m_ptCTtoIterativeValue = &ct;

	return true;
}

CToken* CToken::getRootTokenPt()
{
	if (HasAParent())
		return m_ptCTtoSame->getRootTokenPt();
	return this;
}


bool CToken::getUnderlyingVariable(CToken** ppct) // was CToken**
{
//	CToken* pt;
	(*ppct) = NULL;

	if (IsOfType(ctDerivative))
		{
		if (m_ptCTtoDerivValue==NULL)
				return false;

		(*ppct) = /*&*/m_ptCTtoDerivValue;

		return true; // covers case where 
		}
		else
		if (IsIterative())
			{
			if (m_ptCTtoIterativeValue==NULL)
					return false;

			(*ppct) = /*&*/m_ptCTtoIterativeValue;

			return true; // covers case where 
			}
	
/*	pt = getRootTokenPt();
	pct = &pt;*/
	(*ppct) = getRootTokenPt();

	return true;
}


///////////////////////////////////////////////////////////
// Function name	: CToken::getNumber
// Description	    : Return value if a number, otherwise return
//                    NOT_FOUND
// Return type		: variable 
///////////////////////////////////////////////////////////
variable CToken::getNumber() // for type number tokens
{
	if ((this->IsOfType(ctNumber))&&(m_sToken.isNumber()))
			return m_sToken.getNumber();

	return NOT_FOUND;
}


///////////////////////////////////////////////////////////
// Function name	: CToken::getValue
// Description	    : Return value if CVarRoot defined already, otherwise
//                    returns NOT_DEFINED
// Return type		: variable 
// Argument         : vector<variable>* pvecV
///////////////////////////////////////////////////////////
variable CToken::getValue(vector<variable>* pvecV)
{

	if (!m_pcvr)
			return NOT_DEFINED;

	return m_pcvr->getValue(*pvecV);
}

///////////////////////////////////////////////////////////
// Function name	: CToken::setIndex
// Description	    : Used to assign the index number for a variable
//                    to locate it in the array used for the numerical
//                    simulation.
// Return type		: bool 
// Argument         : const long iIndex
///////////////////////////////////////////////////////////
bool CToken::setIndex(const long iIndex)
{
	if (!((IsOfTypeVariable())||(IsOfType(ctDerivative))))
			{
			m_iIndex=NOT_DEFINED;
			ASSERT2(((IsOfTypeVariable())||(IsOfType(ctDerivative)))); // CToken::setIndex
			return false;
			}

	m_iIndex = iIndex;

	return true;
}


///////////////////////////////////////////////////////////
// Function name	: CToken::setType
// Description	    : 
// Return type		: void 
// Argument         : eTokenType eType
// Argument         : bool bLC /*= false*/
///////////////////////////////////////////////////////////
void CToken::setType(eTokenType eType, bool bLC /*= false*/ )
{
	// if new type is ctComment and old type was variable then must consider the chidlren
	if ((eType==ctComment)&&(m_pvecChildren))
		{
		ATLTRACE("Depreciated code being run\n");
		ASSERT2(false);
		// try to find a child that is a variable
		vector< CToken* >::iterator it = m_pvecChildren->begin();
		bool bNext = true;

		while((bNext)&&(it!=m_pvecChildren->end())) // bNext must be first as m_pvecChidlren will be deleted
			{
			if (((*it)->IsOfTypeVariable())&&((*it)->adoptChildren(*m_pvecChildren)))
			   {
				bNext = false;
				delete m_pvecChildren;
				m_pvecChildren=NULL;
			   }
			   else
			   it++;
			}
#ifndef NDEBUG
		if (bNext)
			{
			ATLTRACE("Failed on at %s with %d children\n",__FILE__,m_pvecChildren->size());
			cout <<"[this] " << (*this) <<endl;
			for (it=m_pvecChildren->begin();it!=m_pvecChildren->end();it++)
				{
				ATLTRACE("%s %d\t",(*it)->getString().c_str(),(*it)->getType());
				cout << (**it) <<endl;
				}
			ATLTRACE("\n");
/*			bool bAdopt = (*(m_pvecChildren->begin()))->adoptChildren(*m_pvecChildren);
			if (!bAdopt)
				ATLTRACE("Failed to adopt\n");*/
			}
#endif

	if (m_pvecChildren) // need to break these links
		{
		for (it=m_pvecChildren->begin();it!=m_pvecChildren->end();it++)
			(*it)->ClearParent();
		delete m_pvecChildren;
		m_pvecChildren = NULL;
		}

/*		ASSERT2(!bNext);
		if (bNext)
			{
			// Unable to reassign chidlren - this is a serious issue
			SYMERRORLITE("An internal problem has arisen in understanding the model",errInternal);
			}*/

		} // end if making comment

	m_eToken=eType;
	if (bLC)
		 setStringLowerCase(m_sToken);
}


///////////////////////////////////////////////////////////
// Function name	: CToken::setpVarRoot
// Description	    : Assign root vraible - if it can hold one,
//                    ie is a 
// Return type		: bool 
// Argument         : CVarRoot* pcvr
///////////////////////////////////////////////////////////
bool CToken::setpVarRoot(CVarRoot* pcvr)
{
	if (!((IsOfTypeVariable())||(IsOfType(ctDerivative))))
			return false;

	#ifndef NDEBUG
	assert(pcvr!=NULL);
	#endif
	if (pcvr==NULL)
			return false;
	

	m_pcvr = pcvr;
	
	return true;


}


///////////////////////////////////////////////////////////
// Function name	: CToken::getpVarRoot
// Description	    : 
// Return type		: CVarRoot* 
///////////////////////////////////////////////////////////
CVarRoot* CToken::getpVarRoot() const
{
	#ifndef NDEBUG
	assert(m_pcvr!=NULL);
	#endif
	return m_pcvr; // will be NULL if not intialised.

}


///////////////////////////////////////////////////////////
// Function name	: CToken::setConstrainedType
// Description	    : Set the strong type for the calculation variable
//                    this find the root variable of the root object
//                    so *no* need to do this when calling.
// Return type		: bool 
// Argument         : const varStrongType& vst
///////////////////////////////////////////////////////////
/*bool CToken::setConstrainedType( const varStrongType& vst )
{
	CVarRoot* pRoot = this->getRootTokenPt()->getpVarRoot();
	if (!pRoot)
		return false;

	pRoot->setType(vst);

	return true;
}*/


///////////////////////////////////////////////////////////
// Function name	: CToken::setRootLocation
// Description	    : 
// Return type		: void 
// Argument         : const CLocation& cl
///////////////////////////////////////////////////////////
void CToken::setRootLocation( const CLocation& cl )
{

	m_Location.setParent(&cl);

	ASSERT2(cl==(*m_Location.getParent()));
}



///////////////////////////////////////////////////////////
// Function name	: CToken::setRelativeLocation
// Description	    : 
// Return type		: void 
// Argument         :  const CLocation& clatpoint
// Argument         : const CLocation& clLinePos
// Argument         : const long iOffset
///////////////////////////////////////////////////////////
void CToken::setRelativeLocation( const CLocation& clatpoint, const CLocation& clLinePos, const long iOffset )
{

	long iNewX = clLinePos.getiX();
	m_Location = clatpoint;
	m_Location.setLocation(clatpoint.getiLine(),clatpoint.getiX(),iNewX);

}


///////////////////////////////////////////////////////////
// Function name	: CToken::sameLine
// Description	    : See if two CTokens are on the same line
// Return type		: bool 
// Argument         : const CToken& ct
///////////////////////////////////////////////////////////
bool CToken::sameLine(const CToken& ct ) const
{
	if (getLine()!=ct.getLine())
		return false;

	// need to check case of nested files with same line number
	if (getLocation().getRefFile()!=ct.getLocation().getRefFile())
		return false;

	return true;
}

string  CToken::getStringWithoutDeriv() const
{

	if (m_eToken!=ctDerivative)
			return m_sToken;

	return m_sToken.getLessDerivative();

}




///////////////////////////////////////////////////////////
// Function name	: CToken::addChild
// Description	    : This token is the parent of its chidlren
// Return type		: void 
// Argument         : CToken *pT
///////////////////////////////////////////////////////////
void CToken::addChild(CToken *pT)
{
	if (!m_pvecChildren)
		m_pvecChildren = newtrack vector< CToken* >;

	if (!m_pvecChildren)
		{
		SYMERRORLITE("Out of memory",errSystem);
		return;
		}

	ASSERT2(m_pvecChildren);

	if (pT)
		(*m_pvecChildren).push_back(pT);

}


///////////////////////////////////////////////////////////
// Function name	: CToken::adoptChildren
// Description	    : Helper function
// Return type		: bool - true if new chidlren vector created
// Argument         : const vector< CToken* > &rChildren
///////////////////////////////////////////////////////////
bool CToken::adoptChildren(const vector< CToken* > &rChildren)
{
	vector< CToken* >::const_iterator cit;

	if (rChildren.size()<1)
		return true;

	ASSERT2(!m_pvecChildren); // bring to developer attention
	if (m_pvecChildren)
		{
		SYMERRORLITE("Internally tried to make invalid model connections.",errInternal);
		return false;
		}
/*
	m_pvecChildren = newtrack vector< CToken* >;

	ASSERT2(m_pvecChildren);
	if (!m_pvecChildren)
		{
		SYMERRORLITE("Out of memory.",errSystem);
		return false;
		}
*/
	for (cit= rChildren.begin(); cit!=rChildren.end();cit++)
		{
		if ((*cit)!=this) // don't adopt self - bad things will happen
			(*cit)->AssignParent(this);
//			m_pvecChildren->push_back(*cit);
		}

	m_ptCTtoSame = NULL; // since this is now the parent

	if (!m_pvecChildren) // ie wasn't created above - maybe this was the only child before
		return false;

	if (m_pvecChildren->size()==0) // then I was an only child
		{
		delete m_pvecChildren;
		m_pvecChildren = NULL;
		return false;
		}
	return true;
}
