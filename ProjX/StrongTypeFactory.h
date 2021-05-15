// StrongTypeFactory.h: interface for the CStrongTypeFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRONGTYPEFACTORY_H__3C8F06AB_6B7C_431C_9C23_87A4EC9C4129__INCLUDED_)
#define AFX_STRONGTYPEFACTORY_H__3C8F06AB_6B7C_431C_9C23_87A4EC9C4129__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StrongType.h"
#include "Token.h"
#include "Equation.h" // for CNavTokens
#include <vector>
#include <map>

using namespace std;

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

#define mapStrongTypes map< CStringPlus, varStrongType >

struct SStringCompareSt
{
  bool operator()(const char* s1, const char* s2) const
  {
    return strcmp(s1, s2) < 0;
  }
};

//declare rather than include
//class CSolver;

#define MapStStringIndex map<const char*,long,SStringCompareSt>

class CStrongTypeFactory: public CNavTokens   
{
public:

    static CStrongTypeFactory* instance() { 
                 if (!m_instance) m_instance = makeInstance();
                 return m_instance;
             }

	static void clear() { cleanupInstance(); }
	static void reset() { cleanupInstance(); } // as reset has been used in other factories 

	bool addTypeDeclaration(long iLeft, long iRight, vector<CToken*>& vLine, ostream& osErrReport );
	bool checkUserRequestedStrongType(long iLeft, long iRight, vector<CToken*>& vLine, ostream& oserr );
	bool checkUserRequestedStrongType(vector<CToken*>& vLine, ostream& oserr );

	bool assignTypeFor( const CStringPlus& csp, varStrongType& vst );

protected:

	bool IsWellFormedTypeSpec(long iLeft,long iRight, vector<CToken*>& vLine, ostream& oserr);
    static CStrongTypeFactory* makeInstance();
	CStrongTypeFactory();
	virtual ~CStrongTypeFactory();
private: 
    static void cleanupInstance();
    static CStrongTypeFactory* m_instance;
	MapStStringIndex m_mapTypes;
	mapStrongTypes m_mapStrongTypes;
};

#endif // !defined(AFX_STRONGTYPEFACTORY_H__3C8F06AB_6B7C_431C_9C23_87A4EC9C4129__INCLUDED_)
