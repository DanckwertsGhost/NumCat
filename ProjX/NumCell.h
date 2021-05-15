/************************************************************************
  			cnumcell.h - Copyright tim

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

#ifndef CNUMCELL_H
#define CNUMCELL_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



#include <string>
#include <vector>
#include "Cell.h"

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

#define CSV_NUMCELL_ALLOWED_CHARS "-0.123456789E"


using namespace std;
_CSV_HANDLER_BEGIN
// Class CNumCell

class CNumCell : public CCell {
// Public stuff
public:
  // Constructors
  // Operations
  // 
  // @param const char* sData 
  CNumCell ( const char* sData);
  virtual ~CNumCell(){}
    
  // 
  // @param const char* sExp 
  virtual csvVariable  getNumber() const;
  virtual bool find ( const char* sExp);
  virtual bool find ( const long iFind){ return (long(m_vValue)==iFind); }
  virtual const char*  getString () const;
    
  virtual csvVariable getNumber( const char* sNum ) const;
  
// Protected stuff
protected:

// Private stuff
private:
    virtual bool greaterThan(CCell* pCell) const;

	csvVariable m_vValue;
    string m_sValue;
	vector< char > m_vNumChars;

};
_CSV_HANDLER_END
#endif //CNUMCELL_H
