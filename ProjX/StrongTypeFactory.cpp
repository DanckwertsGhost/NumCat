// StrongTypeFactory.cpp: implementation of the CStrongTypeFactory class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StrongTypeFactory.h"
#include "Symlix\ErrorFactory.h"
#include <string>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStrongTypeFactory::CStrongTypeFactory()
{
	for(int iT=0;iT<g_iTypeModifier;iT++)
		m_mapTypes[g_sTypeModifiers[iT]]=g_cTypeModifiers[iT];

}

CStrongTypeFactory::~CStrongTypeFactory()
{

}

CStrongTypeFactory* CStrongTypeFactory::m_instance = 0;


///////////////////////////////////////////////////////////
// Function name	: CStrongTypeFactory::makeInstance
// Description	    : returns an instance - not public
// Return type		: CStrongTypeFactory* 
///////////////////////////////////////////////////////////
CStrongTypeFactory* CStrongTypeFactory::makeInstance()
{
    atexit(&cleanupInstance);
    return (newtrack CStrongTypeFactory);
}


///////////////////////////////////////////////////////////
// Function name	: CStrongTypeFactory::cleanupInstance
// Description	    : 
// Return type		: void 
///////////////////////////////////////////////////////////
void CStrongTypeFactory::cleanupInstance()
{ 
   delete m_instance;
   m_instance = 0;
}


///////////////////////////////////////////////////////////
// Function name	: CStrongTypeFactory::checkUserRequestedStrongType
// Description	    : 
// Return type		: bool 
// Argument         : vector<CToken*>& vLine
// Argument         : ostream& oserr
///////////////////////////////////////////////////////////
bool CStrongTypeFactory::checkUserRequestedStrongType(vector<CToken*>& vLine, ostream& oserr )
{
 long iLeft =0;
 long iRight = vLine.size();

 return checkUserRequestedStrongType(iLeft,iRight,vLine,oserr);
}


///////////////////////////////////////////////////////////
// Function name	: CStrongTypeFactory::checkUserRequestedStrongType
// Description	    : 
// Return type		: bool 
// Argument         : long iLeft
// Argument         : long iRight
// Argument         : vector<CToken*>& vLine
// Argument         : ostream& oserr
///////////////////////////////////////////////////////////
bool CStrongTypeFactory::checkUserRequestedStrongType(long iLeft, long iRight, vector<CToken*>& vLine, ostream& oserr )
{

 ASSERT2(iRight>iLeft); // as this should not be here
 if ((iLeft==iRight)||(iLeft<0))
		{
		oserr << "<Warning*> Line could not be processed.\n";
		SYMERRORLITE("A line could not be processed",errInternal);
		return false;
		}

 if (vLine[iLeft]->IsOfType(ctTypeModifier))
	{

	 MapStStringIndex::iterator itMap;

	 itMap = m_mapTypes.find(vLine[iLeft]->getString().c_str());

	 if (itMap==m_mapTypes.end())
				{
				oserr << "<Internal Error*> Unable to check type modifier specified by "<<vLine[0]->getString().c_str() << " keyword on line "<< vLine[0]->getLine()<<".\n";
				SYMERRORTOK("Unable to check type modifier specified",errSyntax,vLine[0]);
				return false;
				}

		switch(itMap->second)
			{
			case C_TM_Dimension:
				return IsWellFormedTypeSpec(iLeft,iRight,vLine,oserr);
				break;
			case C_NotTMDef:
				oserr << "<Internal Error*> A keyword not defined for starting a type defintion is being used ";
				SYMERRORTOK("A keyword not defined for starting a type defintion is being used",errSyntax,vLine[0]);
				ASSERT2(false);
				break;
			default:
				oserr << "<Internal Error*> A keyword not recognised for starting a type defintion is being used ";
				SYMERRORTOK("A keyword not defined for starting a type defintion is being used",errSyntax,vLine[0]);
				ASSERT2(false);
				break;
			break;
			}

	}
	else
	{
	oserr << "<Error*> Unable to find type modifier keyword ";
	SYMERRORTOK("Unable to find type modifier keyword",errSyntax,vLine[0]);
	}

 
 // default
 oserr << " on line " <<vLine[iLeft]->getLine() << ".\n"; 

 return false;
}



///////////////////////////////////////////////////////////
// Function name	: CStrongTypeFactory::IsWellFormedTypeSpec
// Description	    : helper function to check over format for a type
// Return type		: bool 
// Argument         : long iLeft
// Argument         : long iRight
// Argument         : vector<CToken*>& vLine
// Argument         : ostream& oserr
///////////////////////////////////////////////////////////
bool CStrongTypeFactory::IsWellFormedTypeSpec(long iLeft,long iRight, vector<CToken*>& vLine, ostream& oserr)
{

 MapStStringIndex::iterator itMap;
 long iTemp;

 long iRightNC = getPosRightWithoutComments(iLeft,vLine.size(),vLine);
 long iCount=iLeft;

// for debug
#ifndef NDEBUG
 for (iTemp=0;iTemp<vLine.size();iTemp++)
	 oserr << (*vLine[iTemp]) << endl;	
#endif

 if (iLeft>=iRight)
	return false;

 // first check g_Declare is first
 if (vLine[iCount]->getString().compare(g_Dimension)!=0)
	{
	oserr << "<Error*> First term for a declaration should be '"<<g_Dimension<<"', not '"<<vLine[iCount]->getString().c_str() <<"' in line "<<vLine[iCount]->getLine()<<".\n";
	SYMERRORTOK2("First term for a declaration should be ",g_Dimension,errSyntax,vLine[iCount]);
	return false;
	}

 iCount++;
 // no checks on declartion as will use wild cards
 iCount++;
 if (iCount>=iRightNC)
	{
	oserr <<"<Error*> Declartion term is incomplete in line "<<vLine[iLeft]->getLine()<<".\n";
	SYMERRORTOK("Declartion term is incomplete",errSyntax,vLine[iCount-1]);
	return false;
	}

 if (vLine[iCount]->getString().compare(g_As)!=0)
	{
	oserr <<"<Error*> Syntax error in line "<<vLine[iLeft]->getLine()<<", missing 'as'.\n";
	SYMERRORTOK("Syntax error in line",errSyntax,vLine[iCount]);
	return false;
	}

 iCount++;

 if (iCount>=iRightNC)
	{
	oserr <<"<Error*> Declartion term is incomplete in line "<<vLine[iLeft]->getLine()<<".\n";
	SYMERRORTOK("Declartion term is incomplete",errSyntax,vLine[iCount-1]);
	return false;
	}

 if (vLine[iCount]->getString().compare(g_OpenCurlyBracket)!=0)
	{
	oserr <<"<Error*> Syntax error in line "<<vLine[iLeft]->getLine()<<", missing '"<<g_OpenCurlyBracket<<"'.\n";
	SYMERRORTOK("Syntax error in line",errSyntax,vLine[iCount]);
	return false;
	}
 iCount++;

 long iType;
 bool bCheckNext=true;
 // need to look through terms here ...
 iTemp=-1;
 while((bCheckNext)&&(iCount<(iRightNC-2))&&(vLine[iCount]->IsOfType(ctTypeModifier)))
 {

	itMap = m_mapTypes.find(vLine[iCount]->getString().c_str());

	if (itMap==m_mapTypes.end())
			{
			oserr << "<Error*> '"<<vLine[iCount]->getString().c_str()<<"' not expected as a modifier in line "<<vLine[iCount]->getLine()<<".\n";
			SYMERRORTOK("Unexpected symbol found",errSyntax,vLine[iCount]);
			return false;
			}

	switch(itMap->second)
		{
		case C_TM_Min:
			iType = C_TM_Min;
			break;
		case C_TM_Max:
			iType = C_TM_Max;
			break;
		case C_NotTMDef:
			iType = C_NotTMDef;
			break;
		default:
			oserr << "<Internal Error*> Type modifier not correctly modified in line "<<vLine[iCount]->getString().c_str()<<"\n";	
			SYMERRORTOK("Type modifier not correctly modified identified",errInternal,vLine[iCount]);
			ASSERT2(false);
			return false;
		}
	iCount++;
	// must be equals
	if (vLine[iCount]->getString().compare(g_Eq)!=0)
		{
		oserr << "<Error*> '"<<vLine[iCount]->getString().c_str() << "' present where '"<<g_Eq<<"' was expected in line "<<vLine[iCount]->getLine()<<".\n";
		SYMERRORTOK2("Unexpected symbol found, wanted ",g_Eq,errSyntax,vLine[iCount]);
		return false;
		}

	iCount++;
	// check what is equates to
	switch(iType)
		{
		case C_TM_Min:
		case C_TM_Max:
			if (!vLine[iCount]->IsOfType(ctNumber))
				{
				oserr << "<Error*> Expected a number, but found '"<<vLine[iCount]->getString().c_str()<<"' at line "<<vLine[iCount]->getLine()<<".\n";
				SYMERRORTOK2("Expected a number, but found ",vLine[iCount]->getString().c_str(),errSyntax,vLine[iCount]);
				return false;
				}
			iCount++; // note other types might require more than one step
			break;
		default:
			oserr << "<Warning*> Type modifier not recognised in line "<<vLine[iCount]->getLine()<<" and ignored.\n";
			SYMERRORTOK("Type modifier not recognised",errSyntax,vLine[iCount]);
			break;
		}
	
//	iCount = find(g_Comma,vLine,iCount,iRightNC);
	iTemp=iCount-1;
	if (iCount>=iRightNC) // as will need to look at next phrase
		bCheckNext=false;
		else
		if (vLine[iCount]->getString().compare(g_Comma)!=0)
			if (vLine[iCount]->getString().compare(g_CloseCurlyBracket)!=0)
				{
				oserr << "<Error*> Missing either '"<<g_Comma<<"' or '"<<g_CloseCurlyBracket;
				oserr <<" found '"<<vLine[iCount]->getString().c_str()<<"' instead";
				oserr <<" in line "<<vLine[iCount]->getLine()<<".\n";
				if (vLine[iCount]->getString().compare(g_Comma)!=0)
					SYMERRORTOK2("Missing ",g_Comma,errSyntax,vLine[iCount])//; - normally not an issue
					else
					SYMERRORTOK2("Missing ",g_CloseCurlyBracket,errSyntax,vLine[iCount]);
				return false;
				}
				else
				bCheckNext=false;
			else
				iCount++; // step beyond comma
 }

 if (iTemp<0)
		{
		oserr <<"<Error*> Type dimension statment error in line "<<vLine[iLeft]->getLine()<<".\n";
		SYMERRORTOK("Error in dimension statement",errSyntax,vLine[iLeft]);
		return false;
		}		

 if (iTemp>=iRightNC)
	{
	ASSERT2(iTemp<iRightNC); // internal error deal with now
	oserr <<"<Internal Error*> Unable to check end of declare statement on line "<<vLine[iLeft]->getLine()<<".\n";
	SYMERRORTOK("Unable to check end of declare statement",errInternal,vLine[iLeft]);
	return false;
	}

 if (vLine[iCount]->getString().compare(g_CloseCurlyBracket)!=0)
	{
	if (iCount==(iRightNC-1))
		{
		oserr <<"<Error*> Type dimension statement needs to end with '"<<g_CloseCurlyBracket<<" on line "<<vLine[iLeft]->getLine()<<".\n";
		SYMERRORTOK2("Type dimension statement needs to end with ",g_CloseCurlyBracket,errSyntax,vLine[iCount]);
		}
		else
		{
		oserr <<"<Error*> Found '"<<vLine[iCount]->getString().c_str()<<"' when expecting '"<< g_CloseCurlyBracket<<"' in line "<<vLine[iLeft]->getLine()<<".\n";
		SYMERRORTOK2("Was expecting ",g_CloseCurlyBracket,errSyntax,vLine[iCount]);
		}
	return false;
	}

 return true; 
}


///////////////////////////////////////////////////////////
// Function name	: CStrongTypeFactory::addTypeDeclaration
// Description	    : Will add declartion to map of types
// Return type		: bool 
// Argument         : long iLeft
// Argument         : long iRight
// Argument         : vector<CToken*>& vLine
// Argument         : ostream& osErrReport
///////////////////////////////////////////////////////////
bool CStrongTypeFactory::addTypeDeclaration(long iLeft, long iRight, vector<CToken*>& vLine, ostream& osErrReport )
{
 string sKey;
 varStrongType vType;
 MapStStringIndex::iterator itMap;
 long iType;
 long iCount;
 #ifndef NDEBUG
 if (!this->checkUserRequestedStrongType(iLeft,iRight,vLine,osErrReport))
	return false;
 #endif
 long iRightNC = getPosRightWithoutComments(iLeft,vLine.size(),vLine);

  ASSERT2((iLeft+8)<=iRightNC);

 if ((iLeft+8)>iRightNC)
		{
		osErrReport << "<Internal Error*> There has been a failure of internal checks in CStrongTypeFactory::addTypeDeclaration.\n";
		SYMERRORTOK("There is not enough information for the type declartion",errInternal,vLine[iLeft]);
		return false;
		}

// ASSERT2(vLine[iLeft+1]->IsOfTypeVariable()); // should have been check else where - but to be sure
 sKey = vLine[iLeft+1]->getString();
 
 ASSERT2(sKey.length()>0);
 
 iCount = iLeft+4;
 ASSERT2(iCount<iRightNC);
 // declaration should start at offset 5 ie 'dim' 'x' 'as' '{'
 do
 {

	if (!vLine[iCount]->IsOfType(ctTypeModifier))
			{
//			ASSERT2(false); // should never get this far
			osErrReport <<"<Error*> The term '"<<vLine[iCount]->getString().c_str()<<"' is not recognised in line "<<vLine[iCount]->getLine()<<".\n";
			SYMERRORTOK2("Term not recognised - ",vLine[iCount]->getString().c_str(),errSyntax,vLine[iCount]);
			return false;
			}

	itMap = m_mapTypes.find(vLine[iCount]->getString().c_str());

	if (itMap==m_mapTypes.end())
			{
			ASSERT2(false); // should never get this far
			osErrReport << "<Error*> '"<<vLine[iCount]->getString().c_str()<<"' not expected as a modifier in line "<<vLine[iCount]->getLine()<<".\n";
			SYMERRORTOK2("The following was not expected - ",vLine[iCount]->getString().c_str(),errSyntax,vLine[iCount]);
			return false;
			}

	switch(itMap->second)
		{
		case C_TM_Min:
			iType = C_TM_Min;
			break;
		case C_TM_Max:
			iType = C_TM_Max;
			break;
		case C_NotTMDef:
			iType = C_NotTMDef;
			break;
		default:
			osErrReport << "<Internal Error*> Type modifier not correctly modified in line "<<vLine[iCount]->getString().c_str()<<"\n";	
			SYMERRORTOK("Type modifier not correctly identified",errSyntax,vLine[iCount]);
			ASSERT2(false);
			return false;
		} 
	iCount++;iCount++; // since don't need to check the '=' thats done elsewhere
	if (iCount>=iRightNC)
			{
			osErrReport << "<Warning*> Type definition statement in line "<<vLine[iLeft]->getLine()<<".\n";
			SYMERRORTOK("Type definition statement has a problem",errSyntax,vLine[iCount-1]);
			return false;
			}
	 
	 switch(iType)
		{
		case C_TM_Min:
			vType.setLow(vLine[iCount]->getNumber());
			break;
		case C_TM_Max:
			vType.setHigh(vLine[iCount]->getNumber());
			break;
		case C_NotTMDef:
			osErrReport << "<Warning*> Type modfier "<<vLine[iCount-2]->getString().c_str()<<" not yet supported and has not been implemented.\n";
			SYMERRORTOK("Type modifier not yet supported and has not been implemented",errSyntax,vLine[iCount]);
			break;
		default: // really shoudl never happen
			osErrReport << "<Internal Error*> Type modifier not correctly modified in line "<<vLine[iCount]->getString().c_str()<<"\n";	
			SYMERRORTOK("Type modifier not correctly modified in line",errInternal,vLine[iCount]);
			ASSERT2(false);
			return false;
		}	
	iCount = find(g_Comma,vLine,iCount,iRightNC)+1;
 
 }
 while(iCount<(iRightNC-3)); // at least	 

 m_mapStrongTypes[sKey].copy(vType);

 ASSERT2(m_mapStrongTypes[sKey]==vType);
 vType = m_mapStrongTypes[sKey];

 mapStrongTypes::iterator itMap2;
 for (itMap2=m_mapStrongTypes.begin();itMap2!=m_mapStrongTypes.end();itMap2++)
	{
	itMap2->second.writeAll(cout);
	cout <<endl;

	}
 return true; 
}


///////////////////////////////////////////////////////////
// Function name	: CStrongTypeFactory::assignTypeFor
// Description	    : Set type limitations to those in the internal map for the csp key
// Return type		: bool 
// Argument         : const CStringPlus& csp
// Argument         : varStrongType& vst
///////////////////////////////////////////////////////////
bool CStrongTypeFactory::assignTypeFor( const CStringPlus& csp, varStrongType& vst )
{

 long iMatch; // but may be modified if find wildcard
 mapStrongTypes::iterator itMap;

 // first try for outright match
 itMap = m_mapStrongTypes.find(csp);

 if (itMap!=m_mapStrongTypes.end())
		{
		vst.copy(itMap->second);
		return true;
		}

 // OK check wild cards not involved. - some optimisation here will be possible later
 // but currently total matches out rank wild cards
 for (itMap=m_mapStrongTypes.begin();itMap!=m_mapStrongTypes.end();itMap++)
		{
		iMatch = itMap->first.find_first_of(g_WildCard);
		if (iMatch!=CStringPlus::npos) // ie this type has a wildcard
				{
				string sSubLeft = itMap->first.substr(0,iMatch);
				string sSubRight = csp.substr(0,iMatch);
				if (sSubLeft.compare(sSubRight)==0)
						{
						vst.copy(itMap->second);
						return true;
						}
				}
		}


 return false;
} 
