
#ifndef CCELLFACTORY_H
#define CCELLFACTORY_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <string>
#include <vector>
#include <map>
#include "EmptyCell.h"
#include "NumCell.h"
#include "StringCell.h"

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

using namespace std;
_CSV_HANDLER_BEGIN


enum ccfType{ ccfEmpty,ccfNum,ccfString };

struct SStringCompareCCF
{
  bool operator()(const char* s1, const char* s2) const
  {
    return strcmp(s1, s2) < 0;
  }
};

#define MapStringIndexCCF map<const char*,ccfType,SStringCompareCCF>


// Class CCellFactory
// Cell factory to allow different cells to be added latter for little effort
class CCellFactory {
public:
 
  static CCellFactory* instance ();
  CCell* createCell(/*long iRow, long iCol,*/ const char* sContents, const char* sType=NULL);
  bool removeCell(CCell* pCCellRemove);

  friend ostream& operator << (ostream& os, CCellFactory* pcf);

  static void reset(){ cleanUpInstance(); }

// Protected stuff
protected:
  // Fields
  static  CCellFactory* m_instance;
  vector<CCell*> m_vCells;
//  CEmptyCell m_EmptyCell;
    
  
  // Operations
  static CCellFactory*  makeInstance ();
  static void cleanUpInstance ();
    
  
private:
  CCellFactory ();
  ~CCellFactory ();
  MapStringIndexCCF m_mapTypes;
    
  
};
_CSV_HANDLER_END
#endif //CCELLFACTORY_H
