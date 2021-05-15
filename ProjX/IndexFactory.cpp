// IndexFactory.cpp: implementation of the CIndexFactory class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IndexFactory.h"
#include "global.h"
#include "Symlix\ErrorFactory.h"
#include "indexForTo.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIndexFactory::CIndexFactory():m_bNewExpandPoints(false)
{
	// get ready to look up keywords
	for(long i=0;i<g_iMacros;i++)
		m_mapIndexTypes[g_sMacros[i]]=g_cMacros[i];
	m_itset = m_setIndicies.begin();
}

CIndexFactory::~CIndexFactory()
{
	clear();
/*
	vector<CIndex*>::reverse_iterator it;

	for(it=m_vecIndicies.rbegin();it!=m_vecIndicies.rend();it++)
		delete *it;*/
}

CIndexFactory* CIndexFactory::m_instance = 0;



///////////////////////////////////////////////////////////
// Function name	: CIndexFactory::makeInstance
// Description	    : create instance and register it to be cleaned up 
//                    when program closes.
// Return type		: CIndexFactory* 
///////////////////////////////////////////////////////////
CIndexFactory* CIndexFactory::makeInstance()
{
    atexit(&cleanupInstance);
    return (newtrack CIndexFactory);
}


///////////////////////////////////////////////////////////
// Function name	: CIndexFactory::cleanupInstance
// Description	    : 
// Return type		: void 
///////////////////////////////////////////////////////////
void CIndexFactory::cleanupInstance()
{ 
   delete m_instance;
   m_instance = 0;
}

#ifndef NDEBUG


///////////////////////////////////////////////////////////
// Function name	: CIndexFactory::unitTests
// Description	    : Unit tests for all index types used
// Return type		: bool 
// Argument         : IARDataStore* pIStore
///////////////////////////////////////////////////////////
bool CIndexFactory::unitTests(IARDataStore* pIStore)
{
	bool bResult = true;

	bResult &= CIndexForTo::unitTests();


	return bResult;

}

#endif


///////////////////////////////////////////////////////////
// Function name	: CIndexFactory::clear
// Description	    : clear out varianbles and free memory
// Return type		: void 
///////////////////////////////////////////////////////////
void CIndexFactory::clear()
{

	vector<CIndex*>::reverse_iterator it;
	vector<CIndexExpandPoint*>::reverse_iterator it2;
	m_setIndicies.clear();
	m_setIndexNames.clear();
	m_itset=m_setIndicies.begin();

	for(it=m_vecIndicies.rbegin();it!=m_vecIndicies.rend();it++)
		delete *it;

	for(it2=m_vecExpandPoints.rbegin();it2!=m_vecExpandPoints.rend();it2++)
		delete *it2;

	m_vecIndicies.clear();
	m_vecExpandPoints.clear();
	m_bNewExpandPoints=false;
}



///////////////////////////////////////////////////////////
// Function name	: CIndexFactory::checkIndex
// Description	    : IS this index going to be OK to create ?
// Return type		: bool 
// Argument         : vector<CToken*>& vLine
// Argument         : IARDataStore* pIStore
// Argument         : ostream& osErr
///////////////////////////////////////////////////////////
bool CIndexFactory::checkIndex(vector<CToken*>& vLine,IARDataStore* pIStore, ostream& osErr)
{
	MapStringIndex2::iterator itMap;
	// first up test the basics
	if (vLine.size()<1)
		{
		osErr << "<*Internal Error*> Attempt to check an empty line.\n";
		SYMERRORLITE("Attempt to carry on checks on an empty line",errInternal);
		return false;
		}

	if (!vLine[0]->IsOfType(ctMacroKeyWord)) // then this should never happen !
		{
		ASSERT2(vLine[0]->IsOfType(ctMacroKeyWord)); // lets get the developer's attention
		//failing that let the user know we've screwed up
		osErr << "<*Internal Error*> A line has been incorrectly indetified as an index macro.\n";
		SYMERRORTOK("Line incorrectly indetified as an Index macro",errInternal,vLine[0]);
		return false;
		}

/*	if (vLine.size()<6)
		{
		osErr << "<*Error*> Index declartion too short.\n";
		SYMERRORTOK("Index declaration too short",errSyntax,vLine[0]);
		return false;
		}*/

	// look up the Index keyword
	itMap = m_mapIndexTypes.find(vLine[0]->getString().c_str());
	
	if (itMap==m_mapIndexTypes.end()) // this should never have got this far
		{
		ASSERT2(vLine[0]->IsOfType(ctMacroKeyWord)); // lets get the developer's attention
		//failing that let the user know we've screwed up
		osErr << "<*Internal Error*> A line has been incorrectly indetified as an index macro.\n";
		SYMERRORTOK("Line incorrectly indetified as an Index macro",errInternal,vLine[0]);
		return false;
		}

	switch(itMap->second)
	{
		case C_MacIndex:
			if (vLine[4]->getString().compare(g_Eq)==0)
				return CIndexForTo::check(1,vLine.size(),vLine,osErr);
				else
				return CIndexForTo::check(1,vLine.size(),vLine,osErr); // to be replaced by CIndexSeries later
		break;
		case C_MacExpand:
			return CIndexExpandPoint::check(1,vLine.size(),vLine,osErr);
		default:
			osErr << "<*Internal Error*> Unable to identify index macro type.\n";
			SYMERRORTOK("Unable to identify index macro type",errInternal,vLine[0]);
		break;
	}

	return false;
}


///////////////////////////////////////////////////////////
// Function name	: CIndexFactory::createIndex
// Description	    : Create a new index - return false is fails
// Return type		: bool 
// Argument         : vector<CToken*>& vLine
// Argument         : IARDataStore* pIStore
// Argument         : ostream& osErr
///////////////////////////////////////////////////////////
bool CIndexFactory::createIndex( vector<CToken*>& vLine, IARDataStore* pIStore, ostream& osErr )
{
	MapStringIndex2::iterator itMap;

	if (!checkIndex(vLine,pIStore,osErr))
				return NULL;

	itMap = m_mapIndexTypes.find(vLine[0]->getString().c_str());
	

	ASSERT2(itMap!=m_mapIndexTypes.end()); // this should never happen if checkArray called and true

	switch(itMap->second)
		{
		case C_MacIndex:
			{
			CIndex* pIndex = NULL;
		
			ATLTRACE("vLine[2]->getString() = '%s'\n",vLine[2]->getString().c_str());
			if (vLine[2]->getString().compare(g_Eq)==0)
				pIndex = newtrack CIndexForTo(1,vLine.size(),vLine,osErr);
		
			if (pIndex)
				{
				m_vecIndicies.push_back(pIndex);
				m_setIndicies.insert(pIndex);
				m_setIndexNames.insert(pIndex->getIndexName());
				return true;
				}
		
			}
		break;
		case C_MacExpand:
			{
			CIndexExpandPoint* pExpand = NULL;

			pExpand = newtrack CIndexExpandPoint(1,vLine.size(),vLine,osErr);

			if (pExpand)
				{
				m_vecExpandPoints.push_back(pExpand);
				m_bNewExpandPoints=true;
				return true;
				}
			}
		break;
		default:
			osErr << "<*Internal Error*> Unable to identify index macro type.\n";
			SYMERRORTOK("Unable to identify index macro type to create",errInternal,vLine[0]);
			return NULL;
		break;
		}


	return NULL;

}


///////////////////////////////////////////////////////////
// Function name	: CIndexFactory::exists
// Description	    : Returns true if exists, but internal set
//                    pointer remains where it was.
// Return type		: bool 
// Argument         : const char* sTest
///////////////////////////////////////////////////////////
bool CIndexFactory::exists(const char* sTest ) const
{

	if (m_setIndexNames.find(sTest)!=m_setIndexNames.end())
		return true;

	return false;;

}


///////////////////////////////////////////////////////////
// Function name	: CIndexFactory::find
// Description	    : Returns true if find sTest and move internal pointer to that Index
// Return type		: bool 
// Argument         : const char* sTest
///////////////////////////////////////////////////////////
bool CIndexFactory::find(const char* sTest )
{
	bool bResult=false;
	SetIndiciesPts::iterator it;

	it = m_setIndicies.begin();
		
	while((!bResult)&&(it!=m_setIndicies.end()))
	{
		if ((*it)->getIndexName().compare(sTest)==0)
			bResult = true;
			else
			it++;
	}

	if (bResult)
		m_itset = it;

	return bResult;
}


///////////////////////////////////////////////////////////
// Function name	: CIndexFactory::assignExpansionPoints
// Description	    : Helper function to locate expansion points
// Return type		: void 
///////////////////////////////////////////////////////////
void CIndexFactory::assignExpansionPoints()
{
	vector<CIndexExpandPoint*>::iterator it;
	SetIndiciesPts::iterator itSetBegin = m_itset;

	#ifndef CRASHHARD
	try
	{
	#endif
	
/*
	for(it=m_vecExpandPoints.begin();it!=m_vecExpandPoints.end();it++)
		if (((*it)->isReady())&&(find((*it)->getLocationTokenPt()->getString().c_str())))
			(*m_itset)->setExpansionPoint(*it);
*/
	for(it=m_vecExpandPoints.begin();it!=m_vecExpandPoints.end();it++)
		{
		bool bIsReady = (*it)->isReady();
		ATLTRACE("find %s\n",(*it)->getLocationTokenPt()->getString().c_str());
		bool bFindString = find((*it)->getLocationTokenPt()->getString().c_str());
		if (((*it)->isReady())&&(find((*it)->getLocationTokenPt()->getString().c_str())))
			{
			ATLTRACE("Set point %s for Index %s\n",(*it)->getLocationTokenPt()->getString().c_str(),(*m_itset)->getIndexName().c_str());
			(*m_itset)->setExpansionPoint(*it);
			}
		}
#ifndef CRASHHARD
	}
	catch(...)
	{
		SYMERRORLITE("Unexpected error when handling index locations",errInternal);

	}
#endif
	m_itset = itSetBegin; // so no change in state
	m_bNewExpandPoints=false;
}
