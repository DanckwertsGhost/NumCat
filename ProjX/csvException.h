#if !defined(CCSVEXCEPTION__INCLUDED_)
#define CCSVEXCEPTION__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CellFactory.h"
#include <vector>
#include <fstream>

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

using namespace std;
_CSV_HANDLER_BEGIN

class CcsvException
{
private:
	string m_sMessage;
	string m_sDetails;
public:
	CcsvException( const char* sMessage, const char* sDetails )
	{m_sMessage=sMessage; m_sDetails=sDetails;}
	CcsvException( const char* sMessage )
	{m_sMessage=sMessage; m_sDetails="";}
	
	const char* getMessage(){ return m_sMessage.c_str(); }
	const char* getDetails(){ return m_sDetails.c_str(); }

};
_CSV_HANDLER_END
#endif