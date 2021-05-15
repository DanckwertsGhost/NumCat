// EquationFactory.h: interface for the CEquationFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EQUATIONFACTORY_H__EAEBF4A4_07B3_4535_9E89_BF23CF8E2C15__INCLUDED_)
#define AFX_EQUATIONFACTORY_H__EAEBF4A4_07B3_4535_9E89_BF23CF8E2C15__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include <map>
#include <string>
#include <list>
#include "Solver.h"
#include "Token.h"
#include "Equation.h"
#include "EqLookup.h"
#include "EqSwitch.h"
#include "SymlixStore.h"

using namespace std;

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)


struct SStringCompareEq
{
  bool operator()(const char* s1, const char* s2) const
  {
    return strcmp(s1, s2) < 0;
  }
};

//declare rather than include
//class CSolver;

#define MapEqStringIndex map<const char*,long,SStringCompareEq>

class CEquationFactory: public CNavTokens  
{
public:

    static CEquationFactory* instance() { 
                 if (!m_instance) m_instance = makeInstance();
                 return m_instance;
             }

//	CEquation* createEquation(const char* sType, bool bManageLife=true ){return NULL;};
	CEquation* createEquation(long iLeft, long iRight, vector<CToken*>& vLine, IARDataStore* pIStore, ostream& osErrReport, bool bManageLife=true );
	bool checkUserRequestedEquation(long iLeft, long iRight, vector<CToken*>& vLine, IARDataStore* pIStore, ostream& oserr );
	bool checkUserRequestedEquation(vector<CToken*>& vLine, IARDataStore* pIStore, ostream& oserr );
	long expandArrayEquations( CEquation* pEqMaster, list<CToken>& ltToks, vector<CEquation*>& rvecNewEqs, SetPtCTokenStringSearch& rsetPtToksUnique );
	bool lookAfterLifeCycle(CEquation* pe);

	static void reset(){ cleanupInstance(); }

protected:

    static CEquationFactory* makeInstance();
	CEquationFactory();
	virtual ~CEquationFactory();
	vector<CEquation*> m_vecCEquation;

private: 
    static void cleanupInstance();
    static CEquationFactory* m_instance;
	MapEqStringIndex m_mapTypes;

};


#endif // !defined(AFX_EQUATIONFACTORY_H__EAEBF4A4_07B3_4535_9E89_BF23CF8E2C15__INCLUDED_)
