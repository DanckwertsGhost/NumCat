// FuncIdentifierSingleton.h: interface for the CFuncIdentifierSingleton class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FUNCIDENTIFIERSINGLETON_H__22A8322E_EAA3_4AEC_913B_EA21D170EC68__INCLUDED_)
#define AFX_FUNCIDENTIFIERSINGLETON_H__22A8322E_EAA3_4AEC_913B_EA21D170EC68__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include <map>
#include "StringHolder.h"

using namespace std;

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

#define mapFuncs map< CStringHolder, long >

class CFuncIdentifierSingleton  
{
public:
	long identify( const char* sFunc);
	long identify( const CStringHolder& cshFunc);
	long identifyArrayFunc( const char* sFunc);
	long identifyArrayFunc( const CStringHolder& cshFunc);
	static CFuncIdentifierSingleton* instance() { 
                 if (!m_instance) m_instance = makeInstance();
                 return m_instance;
             }

private:
    static CFuncIdentifierSingleton* makeInstance();

	
	
	CFuncIdentifierSingleton();
	virtual ~CFuncIdentifierSingleton();
	mapFuncs* m_pmapFuncs; // map of all functions that the programme can generate
	mapFuncs* m_pmapArrayFuncs; // map of all functions that the programme can generate
    static void cleanupInstance();
    static CFuncIdentifierSingleton* m_instance;

};

#endif // !defined(AFX_FUNCIDENTIFIERSINGLETON_H__22A8322E_EAA3_4AEC_913B_EA21D170EC68__INCLUDED_)
