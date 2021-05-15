/************************************************************************
  			cemptycell.h - Copyright tim

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

#ifndef CEMPTYCELL_H
#define CEMPTYCELL_H 
#include <string>
#include "Cell.h"

using namespace std;
_CSV_HANDLER_BEGIN
// Class CEmptyCell
// Empty cell to represent gaps and allow request to be responded to.
class CEmptyCell : public CCell {
// Public stuff
public:
  // Fields
  // Constructors
  // Empty Constructor
  CEmptyCell():CCell(), sEmpty("") {m_ectType=ectEmpty; }
  virtual ~CEmptyCell(){}

  virtual const char*  getString () const { return sEmpty.c_str();}
  virtual bool find ( const char* sExp){ return sEmpty.compare(sExp)==0; }
  virtual bool greaterThan(CCell* pCell) const { return greaterType(pCell->getType());}

  // Accessor Methods
// Protected stuff
protected:
  // Fields
  // Constructors
  // Accessor Methods
// Private stuff
private:
  string sEmpty;
  // Fields
  // Constructors
  // Accessor Methods
};
_CSV_HANDLER_END
#endif //CEMPTYCELL_H
