// ArrayFactory.cpp: implementation of the CArrayFactory class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "global.h"
#include "ArrayFactory.h"
#include "ArraySeries.h"
#include "ArrayImplied.h"
#include "ArrayLookup.h"
#include "Symlix\ErrorFactory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////
// Function name	: CArrayFactory::CArrayFactory
// Description	    : 
// Return type		: 
///////////////////////////////////////////////////////////
CArrayFactory::CArrayFactory():m_bArrayNames(false)
{
	// get ready to look up keywords
	for(long i=0;i<g_iArrays;i++)
		m_mapArrayTypes[g_sArrays[i]]=g_cArrays[i];
	m_itvec = m_vecArrays.begin();
}


///////////////////////////////////////////////////////////
// Function name	: CArrayFactory::~CArrayFactory
// Description	    : 
// Return type		: 
///////////////////////////////////////////////////////////
CArrayFactory::~CArrayFactory()
{
	vector<CArray*>::reverse_iterator it;

	for(it=m_vecArrays.rbegin();it!=m_vecArrays.rend();it++)
		delete *it;

}

CArrayFactory* CArrayFactory::m_instance = 0;


///////////////////////////////////////////////////////////
// Function name	: CArrayFactory::makeInstance
// Description	    : called once
// Return type		: CArrayFactory* 
///////////////////////////////////////////////////////////
CArrayFactory* CArrayFactory::makeInstance()
{
    atexit(&cleanupInstance);
    return (newtrack CArrayFactory);
}


///////////////////////////////////////////////////////////
// Function name	: CArrayFactory::cleanupInstance
// Description	    : this function sent to atexit
// Return type		: void 
///////////////////////////////////////////////////////////
void CArrayFactory::cleanupInstance()
{ 
   delete m_instance;
   m_instance = 0;
}



#ifndef NDEBUG

///////////////////////////////////////////////////////////
// Function name	: CArrayFactory::unitTests
// Description	    : unitTests only function in Debug builds
// Return type		: bool 
// Argument         : IARDataStore* pIStore
///////////////////////////////////////////////////////////
bool CArrayFactory::unitTests(IARDataStore* pIStore)
{
	bool bResults = true;

	ASSERT2(pIStore);
	if (!pIStore)
			return false; // just to cover

	bResults &= CArraySeries::unitTests();
	bResults &= CArrayLookup::unitTests(pIStore);

	return bResults;
}

#endif



bool CArrayFactory::checkArray( vector<CToken*>& vLine, IARDataStore* pIStore, ostream& osErr )
{

	MapStringIndexAR::iterator itMap;
	// first up test the basics
	if (vLine.size()<1)
		{
		osErr << "<*Internal Error*> Attempt to check an empty line.\n";
		SYMERRORLITE("Attempt to carry on checks on an empty line",errInternal);
		return false;
		}

	if (!vLine[0]->IsOfType(ctArrayKeyWord)) // then this should never happen !
		{
		ASSERT2(vLine[0]->IsOfType(ctArrayKeyWord)); // lets get the developer's attention
		//failing that let the user know we've screwed up
		osErr << "<*Internal Error*> A line has been incorrectly indetified as an array.\n";
		SYMERRORTOK("Line incorrectly indetified as an Array",errInternal,vLine[0]);
		return false;
		}

	if (vLine.size()<6)
		{
		osErr << "<*Error*> Array declartion too short.\n";
		SYMERRORTOK("Array declaration too short",errSyntax,vLine[0]);
		return false;
		}

	// look up the Array keyword
	itMap = m_mapArrayTypes.find(vLine[0]->getString().c_str());
	
	if (itMap==m_mapArrayTypes.end()) // this should never have got this far
		{
		ASSERT2(vLine[0]->IsOfType(ctArrayKeyWord)); // lets get the developer's attention
		//failing that let the user know we've screwed up
		osErr << "<*Internal Error*> A line has been incorrectly indetified as an array.\n";
		SYMERRORTOK("Line incorrectly indetified as an Array",errInternal,vLine[0]);
		return false;
		}

	switch(itMap->second)
	{
		case C_Array:
			return CArraySeries::check(1,vLine.size(),vLine,osErr);
		break;
		case C_LookupArray:
			return CArrayLookup::check(1,vLine.size(),vLine,pIStore,osErr);
		default:
			osErr << "<*Internal Error*> Unable to identify array type.\n";
			SYMERRORTOK("Unable to identify array type",errInternal,vLine[0]);
		break;
	}

	return false;
}


///////////////////////////////////////////////////////////
// Function name	: CArrayFactory::createArray
// Description	    : 
// Return type		: CArray* 
// Argument         : vector<CToken*>& vLine
// Argument         : ostream& osErr
///////////////////////////////////////////////////////////
CArray* CArrayFactory::createArray( vector<CToken*>& vLine, IARDataStore* pIStore, ostream& osErr )
{
	MapStringIndexAR::iterator itMap;
	CArray* pArray = NULL;
	m_bArrayNames = false;

	if (!checkArray(vLine,pIStore,osErr))
				return NULL;

	itMap = m_mapArrayTypes.find(vLine[0]->getString().c_str());
	

	ASSERT2(itMap!=m_mapArrayTypes.end()); // this should never happen if checkArray called and true

	switch(itMap->second)
		{
		case C_Array:
			pArray = newtrack CArraySeries(1,vLine.size(),vLine,osErr);
		break;
		case C_LookupArray:
			pArray = newtrack CArrayLookup(1,vLine.size(),vLine,pIStore,osErr);
		break;
		default:
			osErr << "<*Internal Error*> Unable to identify array type.\n";
			SYMERRORTOK("Unable to identify array type to create",errInternal,vLine[0]);
			return NULL;
		break;
		}

	if (pArray)
		{
		m_vecArrays.push_back(pArray);
		return pArray;
		}

	return NULL;

}



///////////////////////////////////////////////////////////
// Function name	: CArrayFactory::manageArray
// Description	    : Add an array to be managed - false if the factory rejects the array
//                    note will return true for a NULL submission.
// Return type		: bool  
// Argument         : CArray* pAr
///////////////////////////////////////////////////////////
bool  CArrayFactory::manageArray( CArray* pAr )
{
	SetStringAR::const_iterator cit;
	
	// if its a duplicate return false
	if (!pAr)
		return true; // since nothing to do

	cit = m_setArrayNames.find(pAr->getString());

	if (cit!=m_setArrayNames.end())
		return false; // will not manage this

	m_vecArrays.push_back(pAr);
	m_setArrayNames.insert(pAr->getArrayName());

	return true;

}


#define _ImpliedArrayDebug



///////////////////////////////////////////////////////////
// Function name	: CArrayFactory::createImpliedArray
// Description	    : Create an implied array (and) add it to the search terms list
// Return type		: bool 
// Argument         : vector<CToken*>& vRHS
// Argument         : CToken* pLHS
// Argument         : bool& rbHasArray 
///////////////////////////////////////////////////////////
bool CArrayFactory::createImpliedArray( vector<CToken*>& vRHS, CToken* pLHS, bool& rbHasArray )
{
	vector<CToken*>::const_iterator ciTok; 
	SetStringAR::iterator ciTokFind; 
	vector<CArray*>::const_iterator it;
	bool bNewArray = false;

	ASSERT2(pLHS);
	if (!pLHS) // handle and warn
			{
			SYMERRORLITE("Problem indentified with setting up arrays",errInternal);
			return false;
			}

	CArray* pAr=NULL; // so no messing if delete called on it when not allocated
	
	if (pLHS->getArrayType()==atArray)
		{
		pAr = pLHS->getArray();
		ASSERT2(pAr);
		if (!pAr)
				{
				SYMERRORTOK("Unexpected error whilst resolving implied arrays on LHS",errInternal,pLHS);
				return false;
				}
		bNewArray = false; // important for memory management
		}
		else
		{
		pAr = newtrack CArrayImplied(pLHS);
		ATLTRACE("Create implied array - %s\n",pAr->getString().c_str());
		bNewArray = true;
		}

	if (!pAr)
		{
		SYMERRORTOK("Unable to allocate memory needed in simulation",errSystem,pLHS);
		return false;
		}

	if (!m_bArrayNames) // will implement later to speed up
		createArrayNamesSet();
#ifdef _ImpliedArrayDebug
ATLTRACE("Start array search:-\n");
ATLTRACE("\tLHS = %s\n\tRHS = \t",pLHS->getString().c_str());
for(ciTok=vRHS.begin();ciTok!=vRHS.end();ciTok++)
	{
	ATLTRACE("%s\t",(*ciTok)->getString().c_str());
	}
ATLTRACE("\n");
#endif

	for(ciTok=vRHS.begin();ciTok!=vRHS.end();ciTok++)
		if (((*ciTok)->IsOfTypeVariable())&&(!(*ciTok)->isReserved()))
			{
#ifdef _ImpliedArrayDebug
ATLTRACE("Check - %s\n",(*ciTok)->getString().c_str());
#endif
			ciTokFind = m_setArrayNames.find((*ciTok)->getString());
			if (ciTokFind!=m_setArrayNames.end())
					{
					bool bNotFound=true;
					it = m_vecArrays.begin();
					while((bNotFound)&&(it!=m_vecArrays.end()))
						{
						bNotFound = ((*it)->getArrayName().compare((*ciTok)->getString())!=0);
						if (bNotFound)
							it++;
						}

					ASSERT2(!bNotFound);
					if (bNotFound) // then there is a problem - need to clean up
						{
						SYMERRORLITE("Problem found in the way arrays are identified. Please report.",errInternal);
						delete pAr;
						return false;
						}

					ASSERT2(it!=m_vecArrays.end());
					if (it==m_vecArrays.end()) // being very defensive here
						{
						SYMERRORLITE("Problem found in the way arrays are identified. Please report.",errInternal);
						delete pAr;
						return false;
						}

					pAr->CatArray(*it);
					(*ciTok)->setAsArray(); // so it gets spotted later and this search doesn't have to be repeated
					}
			}

	// the LHS may be an array or be an implied array
///	ciTokFind = m_setArrayNames.find(pLHS->getString());

	if (pLHS->IsOfType(ctDerivative)) // then any underlying array will need to be considered here
		{
			bool bNotFound=true;
			it = m_vecArrays.begin();
			while((bNotFound)&&(it!=m_vecArrays.end()))
						{
						bNotFound = ((*it)->getArrayName().compare(pLHS->getStringWithoutDeriv())!=0);
						if (bNotFound)
							it++;
						}
			
			if (!bNotFound)
					{

					ASSERT2(it!=m_vecArrays.end());
					if (it==m_vecArrays.end()) // being very defensive here
						{
						SYMERRORLITE("Problem found in the way arrays are identified. Please report.",errInternal);
						delete pAr;
						return false;
						}

					pAr->CatArray(*it);
					pLHS->setAsArray(); // so it gets spotted later and this search doesn't have to be repeated
					}		


		}
		if (pLHS->IsIterative())
			{
			bool bNotFound=true;
			it = m_vecArrays.begin();
			while((bNotFound)&&(it!=m_vecArrays.end()))
						{
						bNotFound = ((*it)->getArrayName().compare(pLHS->getString().getLessIterative())!=0);
						if (bNotFound)
							it++;
						}
			
			if (!bNotFound)
					{

					ASSERT2(it!=m_vecArrays.end());
					if (it==m_vecArrays.end()) // being very defensive here
						{
						SYMERRORLITE("Problem found in the way arrays are identified. Please report.",errInternal);
						delete pAr;
						return false;
						}

					pAr->CatArray(*it);
					pLHS->setAsArray(); // so it gets spotted later and this search doesn't have to be repeated
					}		

			}

	if (!pAr->IsReady())
		{
		delete pAr;
		return false;
		}

	rbHasArray = true; // the calling function is signalled that there is an array here - for equations

	if (bNewArray)
			{
				m_vecArrays.push_back(pAr); // life time will be handled now by the class
				pLHS->linkToArray(pAr); // note only the LHS value needs a link array to be used later for expansion

				m_setArrayNames.insert(pAr->getArrayName()); // so this won't have to be recreated later - faster this was
			}

	// now if its a derivative then the underlying variable is also an array but should be picked up later
	// update: will Cat Array at this point if it exists already

#ifndef NDEBUG
	bool bResult = addUnderlyingToNamesofArrays(*pLHS,*pAr);
	return bResult;
#else

	return addUnderlyingToNamesofArrays(*pLHS,*pAr);
#endif
}



///////////////////////////////////////////////////////////
// Function name	: CArrayFactory::writeArrays
// Description	    : write a description of all the arrays
//                    to a stream
// Return type		: ostream& 
// Argument         : ostream& os
///////////////////////////////////////////////////////////
ostream& CArrayFactory::writeArrays( ostream& os )
{
//	ostream_iterator<CArray*> out(os,"\n"); // see p53 STL book
	vector<CArray*>::iterator it;

	try
	{
	os <<"Arrays held in CArrayFactory\n";
	os <<"----------------------------\n";
	os << "Total = " << m_vecArrays.size()<<"\n";
	ATLTRACE("Arrays size = %d \n",m_vecArrays.size());
	os << "*start arrays*\n";
//	copy(m_vecArrays.begin(),m_vecArrays.end(),out);
	for (it=m_vecArrays.begin();it!=m_vecArrays.end();it++)
		os << (*it);
	}
	catch(...)
	{
	os << "<Error> unhandled exception caught in CArrayFactory::writeArrays."<<endl;
	os << "This error has been ignored at this stage, but represents a serious failure"<<endl;
	}

	os << "*end arrays*" << endl;

	return os;

}



///////////////////////////////////////////////////////////
// Function name	: CArrayFactory::anyArraysHere
// Description	    : check if any of the Token's match array defintions - unless its been a reserved Token ( used in Array fuction )
// Return type		: bool 
// Argument         : const vector<CToken*> cvecT
///////////////////////////////////////////////////////////
bool CArrayFactory::anyArraysHere(const vector<CToken*> cvecT)
{
	bool bNoArrays = true;
	vector<CToken*>::const_iterator ciTok; 
	
	if (!m_bArrayNames) // will implement later to speed up
		createArrayNamesSet();

	for(ciTok=cvecT.begin();ciTok!=cvecT.end();ciTok++)
		if (((*ciTok)->IsOfTypeVariable())&&(!(*ciTok)->isReserved())) // note reserved is there to allow for arrays sent to Array functions
			bNoArrays &= (m_setArrayNames.find((*ciTok)->getString())==m_setArrayNames.end());

	return !bNoArrays;
}


///////////////////////////////////////////////////////////
// Function name	: CArrayFactory::findArrayHere
// Description	    : Find and point to array - if exists
// Return type		: bool - true if array exists and factory now pointing to it
// Argument         : const CToken& rT
///////////////////////////////////////////////////////////
bool CArrayFactory::findArrayHere( const CToken& rT )
{
	bool bFound = false;
	vector<CArray*>::iterator itvec;
	
	if (!anyArraysHere(rT,true,false))
		return false;	

	for(itvec=m_vecArrays.begin();(!bFound)&&(itvec!=m_vecArrays.end());itvec++)
		{
//		ATLTRACE("'%s' vs '%s'\n",(*itvec)->getArrayName().c_str(),rT.getString().c_str());
		if ((*itvec)->getArrayName().compare(rT.getString())==0)
				{
				bFound=true;
				m_itvec=itvec;
				}
		}

	return bFound;

}



///////////////////////////////////////////////////////////
// Function name	: CArrayFactory::findUnderlyingArray
// Description	    : point factory marker to any underlying arrays
// Return type		: bool 
// Argument         : const CToken& rT
///////////////////////////////////////////////////////////
bool CArrayFactory::findUnderlyingArray( const CToken& rT )
{
	bool bFound = false;
	vector<CArray*>::iterator itvec;
	string sUnderlying;
	
	if (rT.getArrayType()==atArray)
			return false; // already done

	if (rT.getType()==ctDerivative)
		sUnderlying = rT.getStringWithoutDeriv();
		else
		if (rT.IsIterative())
			sUnderlying = rT.getString().getLessDerivative();
			else
			return false; // nothing to do

	for(itvec=m_vecArrays.begin();(!bFound)&&(itvec!=m_vecArrays.end());itvec++)
		{
//		ATLTRACE("'%s' vs '%s'\n",(*itvec)->getArrayName().c_str(),rT.getString().c_str());
		if ((*itvec)->getArrayName().compare(sUnderlying)==0)
				{
				bFound=true;
				m_itvec=itvec;
				}
		}

	return bFound;

}


///////////////////////////////////////////////////////////
// Function name	: CArrayFactory::anyArraysHere
// Description	    : Check if an individual Token may be an array - unless its been a reserved Token ( used in Array fuction )
// Return type		: bool 
// Argument         : const CToken& rT
// Argument         : bool bNoDervivedCheck /*=false*/ if true then iterative and derviative forms ignored in search
///////////////////////////////////////////////////////////
bool CArrayFactory::anyArraysHere( const CToken& rT, bool bNoDervivedCheck /*=false*/, bool bIgnoreReserved /*= true*/  )
{
	
	bool bResult;

	if ((bIgnoreReserved)&&(rT.isReserved())) // Token's that are used in Array Functions are not ifdentified as Arrays here
		return false;

	if (!m_bArrayNames) // will implement later to speed up
		createArrayNamesSet();

	bResult = m_setArrayNames.find(rT.getString())!=m_setArrayNames.end();

	if (!bNoDervivedCheck)
		{

		#ifndef NDEBUG
			if ((!bResult)&&(rT.IsOfType(ctDerivative))) // as this is more computationally expensive
					{
					ATLTRACE("Checking for derivate or iterative on '%s' for underlying variable '%s'\n",rT.getString().c_str(),rT.getStringWithoutDeriv().c_str());
					}
		#endif

			if ((!bResult)&&(rT.IsOfType(ctDerivative))) 
					return m_setArrayNames.find(rT.getStringWithoutDeriv())!=m_setArrayNames.end();

			if ((!bResult)&&(rT.getString().isIterative())) 
					return m_setArrayNames.find(rT.getString().getLessIterative())!=m_setArrayNames.end();

		}

	return bResult;

}



///////////////////////////////////////////////////////////
// Function name	: CArrayFactory::createArrayNamesSet
// Description	    : Generate a set of current array names
// Return type		: void 
///////////////////////////////////////////////////////////
void CArrayFactory::createArrayNamesSet()
{
	vector<CArray*>::const_iterator cit;

	m_setArrayNames.clear();

	for(cit=m_vecArrays.begin();cit!=m_vecArrays.end();cit++)
		m_setArrayNames.insert((*cit)->getArrayName());

	m_bArrayNames=true;

}



///////////////////////////////////////////////////////////
// Function name	: CArrayFactory::setOfArraysHere
// Description	    : Return a set of the valid arrays submitted - excluding those in array functions
// Return type		: SetStringAR
// Argument         : vector<CToken*>& vLine
///////////////////////////////////////////////////////////
SetStringAR CArrayFactory::setOfArraysHere( vector<CToken*>& vLine )
{
	SetStringAR::iterator itSetAR;
	SetStringAR setArrays;
	vector<CToken*>::iterator it;

	if (!m_bArrayNames) // if for some reason this has happened
			createArrayNamesSet();

	for (it=vLine.begin();it!=vLine.end();it++)
		{
		if (((*it)->IsOfTypeVariable())&&(!(*it)->isReserved()))
			{
			itSetAR = m_setArrayNames.find((*it)->getString().c_str());

			if (itSetAR!=m_setArrayNames.end())
				setArrays.insert(*itSetAR);
			}
		}

	return setArrays;
}



///////////////////////////////////////////////////////////
// Function name	: CArrayFactory::addUnderlyingToNamesofArrays
// Description	    : Helper function
// Return type		: bool - true if new implied array to an underlying Token created 
//
// Argument         : CToken &rT
// Argument         : CArray& rA
///////////////////////////////////////////////////////////
bool CArrayFactory::addUnderlyingToNamesofArrays(CToken &rT, CArray& rA)
{
	CToken* p2 = NULL;
	string sUnderlying;
	bool bNewArray = false;

	if ((!rT.IsOfType(ctDerivative))&&(!rT.IsIterative()))
			return false;

	if (rT.IsOfType(ctDerivative))
		sUnderlying = rT.getString().getLessDerivative();
		else
		{
		ASSERT2(rT.IsIterative());
		if (!rT.IsIterative()) // need to handle with grace
				return false;
		sUnderlying = rT.getString().getLessIterative();
		}

	SetStringAR::iterator itSSA = m_setArrayNames.find(sUnderlying);

	if (itSSA==m_setArrayNames.end())
		{
		CToken* p2 = NULL;

		if ((rT.getUnderlyingVariable(&p2))&&(p2)) // note CSimulation::unifyEquationTokens - the &&(p2) is perhaps unnecssary, just being defensive.
				{
				CArray* pAr2=NULL;
//				SetStringAR::iterator itSSA = m_setArrayNames.find(sUnderlying);
				bNewArray = false;

				ASSERT2(sUnderlying.compare(p2->getString())==0); // of interest

				if (itSSA!=m_setArrayNames.end())
						{
						vector<CArray*>::iterator it = m_vecArrays.begin();
						ASSERT2(false); // this code should never execute

						while((pAr2==NULL)&&(it!=m_vecArrays.end()))
							{
							 if ((*it)->getArrayName().compare(sUnderlying)==0)
								{
								pAr2 = (*it);
								//bNewArray = true;
								}
							 it++;
							}

						}

				if (!pAr2)
					{
					if (p2->getArrayType()==atArray)
						{
						pAr2 = p2->getArray();
						ASSERT2(pAr2);
						if (!pAr2)
							{
							SYMERRORTOK("Unexpected error whilst resolving implied arrays",errInternal,p2);
							return false;
							}
						bNewArray = false;
						}
						else
						{
						pAr2 = newtrack CArrayImplied(p2);
						ATLTRACE("Create implied array - %s\n",pAr2->getString().c_str());

						bNewArray = true;
						}
					}

				pAr2->CatArray(&rA);

				if (bNewArray) // then a little memory management is going to be required
						{
						m_vecArrays.push_back(pAr2); // life time will be handled now by the class

						m_setArrayNames.insert(pAr2->getArrayName()); // so this won't have to be recreated later - faster this way
					//	bNewAssignment = true;
						}

				ATLTRACE("Successfully found variable %s from %s\n",p2->getString().c_str(),rT.getString().c_str());
				cout << (*p2) <<"\n"<<rT<<endl;


				} 
				else
				{
				ATLTRACE("Failed to find underlying variable from %s\n",rT.getString().c_str());
				cout <<"FAILED: "<<rT<<endl;
				}
		}

	return 	bNewArray;

}
