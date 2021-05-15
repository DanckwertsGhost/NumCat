// SolClassFactory.h: interface for the CSolClassFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOLCLASSFACTORY_H__4B438B29_1E6E_41D9_A510_C11C425F5CA1__INCLUDED_)
#define AFX_SOLCLASSFACTORY_H__4B438B29_1E6E_41D9_A510_C11C425F5CA1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include <map>
#include <string>
#include "Solver.h"
#include "Token.h"

using namespace std;

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)


struct SStringCompare
{
  bool operator()(const char* s1, const char* s2) const
  {
    return strcmp(s1, s2) < 0;
  }
};

//declare rather than include
//class CSolver;

#define MapStringIndex map<const char*,long,SStringCompare>

class CSolClassFactory  
{
public:

    static CSolClassFactory* instance() { 
                 if (!m_instance) m_instance = makeInstance();
                 return m_instance;
             }

	CSolver* createSolver(const char* sType, bool bManageLife=true );
	CSolver* createSolver(const char* sType, long iLeft, long iRight, vector<CToken*>* pvExpLine, ostream& osErrReport, bool bManageLife=true );
	bool checkUserRequestedSolver(vector<CToken*>& vLine, ostream& oserr );

	static void reset(){ cleanupInstance(); }

protected:

    static CSolClassFactory* makeInstance();
	CSolClassFactory();
	virtual ~CSolClassFactory();
	vector<CSolver*> m_vecCSolver;

private: 
    static void cleanupInstance();
    static CSolClassFactory* m_instance;
	MapStringIndex m_mapTypes;

};



#endif // !defined(AFX_SOLCLASSFACTORY_H__4B438B29_1E6E_41D9_A510_C11C425F5CA1__INCLUDED_)
