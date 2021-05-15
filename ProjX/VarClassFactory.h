// VarClassFactory.h: interface for the CVarClassFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VARCLASSFACTORY_H__9B9C246D_92AB_4BDA_9AF8_C90E30FE38E1__INCLUDED_)
#define AFX_VARCLASSFACTORY_H__9B9C246D_92AB_4BDA_9AF8_C90E30FE38E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include <map>
#include "VarRoot.h"
#include "StringHolder.h"
#include "FuncIdentifierSingleton.h"

using namespace std;

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

//#define mapFuncs map< CStringHolder, long >

class CVarClassFactory  
{
public:

    static CVarClassFactory* instance() { 
                 if (!m_instance) m_instance = makeInstance();
                 return m_instance;
             }

	CVarRoot* createExpression(const char* sType, CVarRoot* cvrL, CVarRoot* cvrR=NULL);
	CVarRoot* createMultiVarExpression(const char* sType, vector< CVarRoot* >& rveccvrR);
	CVarRoot* createVariable(const long lIndex);
	CVarRoot* createValue(const xt_value xtv);

	static void reset(){ cleanupInstance(); }

protected:

    static CVarClassFactory* makeInstance();
	CVarClassFactory();
	virtual ~CVarClassFactory();
	vector<CVarRoot*> m_vecCVarRoot;
//	static mapFuncs* m_pmapFuncs; // map of all functions that the programme can generate

private: 
    static void cleanupInstance();
    static CVarClassFactory* m_instance;

};

#endif // !defined(AFX_VARCLASSFACTORY_H__9B9C246D_92AB_4BDA_9AF8_C90E30FE38E1__INCLUDED_)
