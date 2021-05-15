// csvHolderFactory.h: interface for the CcsvHolderFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CSVHOLDERFACTORY_H__BE107FB2_3934_4951_8765_B8B5687A18AC__INCLUDED_)
#define AFX_CSVHOLDERFACTORY_H__BE107FB2_3934_4951_8765_B8B5687A18AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CCFHEMPTY "empty"
#define CCFHLOOKUP "lookup"

#include <map>
#include <fstream>
#include "csvHolder.h"
#ifndef _AREXCELFUNC
#include "SymlixStore.h" // otherwise via import
#endif

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)


/*
#ifndef NOT_FOUND
	#define CSV_NOT_FOUND -2147483648
	#define CSV_NOT_DEFINED CSV_NOT_FOUND+1
	#define CSV_CANNOT_EVALUATE NOT_DEFINED+1
#else
	#define CSV_NOT_FOUND NOT_FOUND
	#define CSV_NOT_DEFINED NOT_DEFINED
	#define CSV_CANNOT_EVALUATE CANNOT_EVALUATE
#endif
*/

using namespace std;
_CSV_HANDLER_BEGIN

enum ccfHolderType{ ccfHEmpty,ccfHLookup, ccfHNotFound };

struct SStringCompareHolderCCF
{
  bool operator()(const char* s1, const char* s2) const
  {
    return strcmp(s1, s2) < 0;
  }
};

#define MapStringIndexHolderCCF map<const char*,ccfHolderType,SStringCompareHolderCCF>



class CcsvHolderFactory  
{
public:
 
  static CcsvHolderFactory* instance();
  CcsvHolder* create( const char* sType, IARStream* pIStream=NULL);

//  friend ostream& operator << (ostream& os, CcsvHolderFactory* pchf);

  #ifndef NDEBUG
  bool testAllHolders( ostream& osErr );
  #else           // don't want to burdun release versions with test code
  inline bool testAllHolders( ostream& ){ return true; }
  #endif

// Protected stuff
protected:
  // Fields
  static  CcsvHolderFactory* m_instance;
//  vector<CCell*> m_vCells;
//  CEmptyCell m_EmptyCell;
    
  
  // Operations
  static CcsvHolderFactory*  makeInstance ();
  static void cleanUpInstance ();
    
  
private:
  CcsvHolderFactory ();
  ~CcsvHolderFactory ();
  MapStringIndexHolderCCF m_mapTypes;
  vector<CcsvHolder*> m_pvcsvHolders;

};
_CSV_HANDLER_END
#endif // !defined(AFX_CSVHOLDERFACTORY_H__BE107FB2_3934_4951_8765_B8B5687A18AC__INCLUDED_)
