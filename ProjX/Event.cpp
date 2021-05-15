// EvValue.cpp: implementation of the CEvValue class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Event.h"
#include <assert.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////
// Function name	: CEventImpl::prepareForSimulation
// Description	    : returns true if event can be ignored after call
//                    ( if life time not managed by factory then delete event )
// Return type		: bool 
// Argument         : vector< variable >* pvecVars
// Argument         : ostream& oserr - where the error messages go
///////////////////////////////////////////////////////////
bool CEventImpl::prepareForSimulation( vector< variable >* /*pvecVars*/, ostream& /*oserr*/  )
{

 return false; // default - events override if necessary
}
