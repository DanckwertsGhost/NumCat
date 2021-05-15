// FuncIdentifierSingleton.cpp: implementation of the CFuncIdentifierSingleton class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FuncIdentifierSingleton.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFuncIdentifierSingleton::CFuncIdentifierSingleton()
{
	long iT;
	m_pmapFuncs = newtrack mapFuncs;
	for(iT=0;iT<g_iFuncs;iT++)
		(*m_pmapFuncs)[g_sFuncs[iT]] = g_cFuncs[iT];

	m_pmapArrayFuncs = newtrack mapFuncs;
	for(iT=0;iT<g_iArrayFuncs;iT++)
		(*m_pmapArrayFuncs)[g_sArrayFuncs[iT]] = g_cArrayFuncs[iT];

}

CFuncIdentifierSingleton::~CFuncIdentifierSingleton()
{
	delete m_pmapFuncs;
	delete m_pmapArrayFuncs;
}

CFuncIdentifierSingleton* CFuncIdentifierSingleton::m_instance = NULL;

//mapFuncs* CFuncIdentifierSingleton::m_pmapFuncs = NULL;
	


///////////////////////////////////////////////////////////
// Function name	: CFuncIdentifierSingleton::makeInstance
// Description	    : 
// Return type		: CFuncIdentifierSingleton* 
///////////////////////////////////////////////////////////
CFuncIdentifierSingleton* CFuncIdentifierSingleton::makeInstance()
{
		
	m_instance = newtrack CFuncIdentifierSingleton;
	atexit(&cleanupInstance);

	return m_instance; // to signal we have trouble
}


///////////////////////////////////////////////////////////
// Function name	: CFuncIdentifierSingleton::cleanupInstance
// Description	    : 
// Return type		: void 
///////////////////////////////////////////////////////////
void CFuncIdentifierSingleton::cleanupInstance()
{
   delete m_instance;
   m_instance = 0;
}



///////////////////////////////////////////////////////////
// Function name	: CFuncIdentifierSingleton::identify
// Description	    : 
// Return type		: long 
// Argument         : const char *sFunc
///////////////////////////////////////////////////////////
long CFuncIdentifierSingleton::identify(const char *sFunc)
{
	CStringHolder csh(sFunc);
	return identify(csh);
}


///////////////////////////////////////////////////////////
// Function name	: CFuncIdentifierSingleton::identifyArrayFunc
// Description	    : 
// Return type		: long 
// Argument         : const char *sFunc
///////////////////////////////////////////////////////////
long CFuncIdentifierSingleton::identifyArrayFunc(const char *sFunc)
{
	CStringHolder csh(sFunc);
	return identifyArrayFunc(csh);
}

///////////////////////////////////////////////////////////
// Function name	: CFuncIdentifierSingleton::identify
// Description	    : 
// Return type		: long 
// Argument         : const CStringHolder& cshFunc
///////////////////////////////////////////////////////////
long CFuncIdentifierSingleton::identify( const CStringHolder& cshFunc)
{
	mapFuncs::const_iterator cit;

	if (m_pmapFuncs) // should always be the case
		{		
		cit = m_pmapFuncs->find(cshFunc);

		if (cit==m_pmapFuncs->end())
			return C_NotAFunc;
		return cit->second;
		}
	return C_NotAFunc; // since need to cover this

}

///////////////////////////////////////////////////////////
// Function name	: CFuncIdentifierSingleton::identifyArrayFunc
// Description	    : 
// Return type		: long 
// Argument         : const CStringHolder& cshFunc
///////////////////////////////////////////////////////////
long CFuncIdentifierSingleton::identifyArrayFunc( const CStringHolder& cshFunc)
{
	mapFuncs::const_iterator cit;

	if (m_pmapArrayFuncs) // should always be the case
		{		
		cit = m_pmapArrayFuncs->find(cshFunc);

		if (cit==m_pmapArrayFuncs->end())
			return C_NotAFunc;
		return cit->second;
		}
	return C_NotAFunc; // since need to cover this

}
