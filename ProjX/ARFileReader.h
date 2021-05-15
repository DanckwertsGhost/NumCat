

#if !defined(ARFILEREADER_1737)

#define ARFILEREADER

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <istream>
#include <ostream>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "csvHandlerAR.h"
#ifndef _AREXCELFUNC
#include "SymlixStore.h" // otherwise via import
#endif

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

using namespace std;
_CSV_HANDLER_BEGIN

#define CR 15
#define LF 10

bool readLine( istream& is, const vector< char >& vDelim, vector< string >& vLine );
bool readLine( IARStream* pIStream, const vector< char >& vDelim, vector< string >& vLine );
_CSV_HANDLER_END

#endif // #if !defined(ARFILEREADER_1737)
