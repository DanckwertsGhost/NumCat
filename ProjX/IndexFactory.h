// IndexFactory.h: interface for the CIndexFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INDEXFACTORY_H__0ED45F78_986D_4177_B5E2_1C935D4FAB48__INCLUDED_)
#define AFX_INDEXFACTORY_H__0ED45F78_986D_4177_B5E2_1C935D4FAB48__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include <map>
#include <string>
#include <ostream>
#include "index.h"
#include <set>
#include "SymlixStore.h"
#include "IndexExpandPoint.h"

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

struct SStringCompareIndex
{
  bool operator()(const char* s1, const char* s2) const
  {
    return strcmp(s1, s2) < 0;
  }
};

#define MapStringIndex2 map<const char*,long,SStringCompareIndex>
#define SetIndiciesPts set<CIndex*,ltIndecies>

struct ltIndecies
{
  bool operator()(const CIndex* pi1, const CIndex* pi2) const
  {
	if (pi1==pi2)
		return true;
	if (!pi1)
		return false;
    return (*pi1)<pi2;
  }
};

struct SStringCompareIndStrings
{
  bool operator()(const string& s1, const string& s2) const
  {
    return s1.compare(s2) < 0;
  }
};

#define SetStringInd set< string, SStringCompareIndStrings >


class CIndexFactory  
{
public:
	void clear();
    static CIndexFactory* instance() { 
                 if (!m_instance) m_instance = makeInstance();
                 return m_instance;
             }
	bool checkIndex( vector<CToken*>& vLine, IARDataStore* pIStore, ostream& osErr );
	bool createIndex( vector<CToken*>& vLine, IARDataStore* pIStore, ostream& osErr );
	ostream& writeIndicies( ostream& os );
//	bool anyArraysHere( const vector< CToken* > cvecT );
//	bool anyArraysHere( const CToken& rT, bool bNoDervativeCheck =false );
	bool first(){ m_itset = m_setIndicies.begin(); return (m_setIndicies.size()>0);}
	bool next(){ m_itset++; return (m_itset!=m_setIndicies.end()); }
	bool find(const char* sTest );
	bool exists(const char* sTest ) const;
	CIndex* getCurrentIndex(){ checkExpand(); return *m_itset; }

#ifndef NDEBUG
	bool unitTests(IARDataStore* pIStore);
#endif
	
	static void reset(){ cleanupInstance(); }

private:
	CIndexFactory();
	virtual ~CIndexFactory();
    static CIndexFactory* makeInstance();
    static void cleanupInstance();
	inline void checkExpand(){ if (m_bNewExpandPoints) 
									assignExpansionPoints();
							 } 

    static CIndexFactory* m_instance;
	vector<CIndex*> m_vecIndicies;
	vector<CIndexExpandPoint*> m_vecExpandPoints;
	SetIndiciesPts m_setIndicies;
	SetIndiciesPts::iterator m_itset;
	MapStringIndex2 m_mapIndexTypes;
//	SetStringAR m_setArrayNames;
//	bool m_bArrayNames; // flag if need to recreate ArrayNames
//	void createArrayNamesSet();
	SetStringInd m_setIndexNames;
	void assignExpansionPoints();
	bool m_bNewExpandPoints;


};

#endif // !defined(AFX_INDEXFACTORY_H__0ED45F78_986D_4177_B5E2_1C935D4FAB48__INCLUDED_)
