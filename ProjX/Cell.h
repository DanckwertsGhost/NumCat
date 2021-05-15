/************************************************************************
  			ccell.h - Copyright tim

Here you can write a license for your code, some comments or any other
information you want to have in your generated code. To to this simply
configure the "headings" directory in uml to point to a directory
where you have your heading files.

or you can just replace the contents of this file with your own.
If you want to do this, this file is located at

/usr/share/apps/umbrello/headings/heading.h

-->Code Generators searches for heading files based on the file extension
   i.e. it will look for a file name ending in ".h" to include in C++ header
   files, and for a file name ending in ".java" to include in all generated
   java code.
   If you name the file "heading.<extension>", Code Generator will always
   choose this file even if there are other files with the same extension in the
   directory. If you name the file something else, it must be the only one with that
   extension in the directory to guarantee that Code Generator will choose it.

you can use variables in your heading files which are replaced at generation
time. possible variables are : author, date, time, filename and filepath.
just write %variable_name%

This file was generated on Fri Oct 7 2005 at 11:24:06
The original location of this file is 
**************************************************************************/

#ifndef CCELL_H
#define CCELL_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "csvHandlerAR.h"
#include <string>
//#include "ccsvholder.h"
//#include "ccsvrange.h"

#ifndef NOT_FOUND
	#define CSV_NOT_FOUND -2147483648
	#define CSV_NOT_DEFINED CSV_NOT_FOUND+1
	#define CSV_CANNOT_EVALUATE CSV_NOT_DEFINED+1
#else
	#define CSV_NOT_FOUND NOT_FOUND
	#define CSV_NOT_DEFINED NOT_DEFINED
	#define CSV_CANNOT_EVALUATE CANNOT_EVALUATE
#endif

#define csvVariable double
#define CSV_DEFAULT_NUMBER 0

#define CCFEMPTY "empty"
#define CCFNUMBER "number"
#define CCFSTRING "string"

#define vectorcsvVariableRow vector<csvVariable> 

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

using namespace std;

_CSV_HANDLER_BEGIN

enum eCellType{ ectNum, ectString, ectDate, ectEmpty, ectNotDefined };

// Class CCell
//Abstract class for cells
class CCell {
// Public stuff
public:
  // Fields
  // Constructors
  // Empty Constructor
  CCell ( ):m_iLocks(1),m_ectType(ectNotDefined){ }
  virtual ~CCell();
  // Accessor Methods
  // Operations
  virtual csvVariable  getNumber () const {return CSV_DEFAULT_NUMBER;} // needs to be overridden
  virtual const char*  getString () const = 0;
  virtual bool  isEmpty (){ return (m_iLocks<1);}
  virtual bool  isLocked(){ return (m_iLocks>0);}
  virtual long  addLock ();
  virtual long  removeLock ();
  virtual long  getLock (){ return m_iLocks; };
  virtual bool  isOfType(eCellType ect){ return ect==m_ectType; }
  inline eCellType getType() const { return m_ectType; }
  ostream& writeType(ostream& os) const;  
  // 
  // @param const char* sExp 
  virtual bool find ( const char* sExp)=0;
  virtual bool find ( const long iFind){ return false; } // unless its a number cell value always false
    
  
  // 
  // @param const char* sExp 
  virtual bool match ( const char* sExp){ return find(sExp);};

  inline bool operator > (CCell* pCell){ return greaterThan(pCell);};
  inline bool operator < (CCell* pCell){ return pCell->greaterThan(this);};
  inline bool operator == (CCell* pCell){ return (!this->greaterThan(pCell))&&(!pCell->greaterThan(this));}
    
  friend ostream& operator << (ostream& os, const CCell& cell){ os << cell.getString(); return os; } 
// Protected stuff
protected:

   virtual bool greaterThan(CCell* pCell) const =0;
   bool greaterType(eCellType ect) const;

  // Fields
   long m_iLocks;
   eCellType m_ectType;
// Private stuff
private:
  // Fields
  // Constructors
  // Accessor Methods
  // Operations
};
_CSV_HANDLER_END
#endif //CCELL_H
