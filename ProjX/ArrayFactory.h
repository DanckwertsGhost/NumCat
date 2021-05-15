// ArrayFactory.h: interface for the CArrayFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARRAYFACTORY_H__1AD1928B_67E4_4710_9FBB_AB3D21D8E8EA__INCLUDED_)
#define AFX_ARRAYFACTORY_H__1AD1928B_67E4_4710_9FBB_AB3D21D8E8EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <vector>
#include <map>
#include <string>
#include <ostream>
#include "Array.h"
#include "Token.h"
#include <set>
#include "SymlixStore.h"


// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

struct SStringCompareAR
{
  bool operator()(const char* s1, const char* s2) const
  {
    return strcmp(s1, s2) < 0;
  }
};

struct SStringCompareAFStrings
{
  bool operator()(const string& s1, const string& s2) const
  {
    return s1.compare(s2) < 0;
  }
};

#define MapStringIndexAR map<const char*,long,SStringCompareAR>
#define SetStringAR set< string, SStringCompareAFStrings >

class CArrayFactory  
{
public:
    static CArrayFactory* instance() { 
                 if (!m_instance) m_instance = makeInstance();
                 return m_instance;
             }
	bool checkArray( vector<CToken*>& vLine, IARDataStore* pIStore, ostream& osErr );
	CArray* createArray( vector<CToken*>& vLine, IARDataStore* pIStore, ostream& osErr );
	ostream& writeArrays( ostream& os );
	bool anyArraysHere( const vector< CToken* > cvecT );
	bool anyArraysHere( const CToken& rT, bool bNoDervivedCheck =false, bool bIgnoreReserved = true );
	bool createImpliedArray( vector<CToken*>& vRHS, CToken* pLHS, bool& rbHasArray  );
	SetStringAR setOfArraysHere( vector<CToken*>& vLine ); 
	bool first(){ m_itvec = m_vecArrays.begin(); return (m_vecArrays.size()>0);}
	bool next(){ m_itvec++; return (m_itvec!=m_vecArrays.end()); }
	CArray* getCurrentArray(){ return *m_itvec; }
	bool findArrayHere( const CToken& rT );
	bool findUnderlyingArray( const CToken& rT );
	bool manageArray( CArray* pAr );


#ifndef NDEBUG
	bool unitTests(IARDataStore* pIStore);
#endif

	static void reset(){ cleanupInstance(); }
	

private:
	bool addUnderlyingToNamesofArrays(CToken& rT, CArray& rA);
	CArrayFactory();
	virtual ~CArrayFactory();
    static CArrayFactory* makeInstance();

    static CArrayFactory* m_instance;
	vector<CArray*> m_vecArrays;
	vector<CArray*>::iterator m_itvec;
	MapStringIndexAR m_mapArrayTypes;
	SetStringAR m_setArrayNames;
	bool m_bArrayNames; // flag if need to recreate ArrayNames
	void createArrayNamesSet();

    static void cleanupInstance();

};

#endif // !defined(AFX_ARRAYFACTORY_H__1AD1928B_67E4_4710_9FBB_AB3D21D8E8EA__INCLUDED_)
