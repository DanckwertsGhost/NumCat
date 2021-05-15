// VarExpression.cpp: implementation of the CVarExpression class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VarExpression.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////
// Function name	: CVarExpression::CVarExpression
// Description	    : Constructor which should be called by all derived classes
// Return type		: 
// Argument         : bool bDestroyPVRs - do these pointer need to have their life time
//                                        managed inside this object ? ( default = false )
// intialises       : m_bDestroyPVRs(bDestroyPVRs)
// intialises       : m_pvrLeft(NULL)
// intialises       : m_pvrRight(NULL
///////////////////////////////////////////////////////////
CVarExpression::CVarExpression(bool bDestroyPVRs/*=false*/):m_bDestroyPVRs(bDestroyPVRs),m_pvrLeft(NULL),m_pvrRight(NULL),m_iLocalCacheState(-1)
{

}


///////////////////////////////////////////////////////////
// Function name	: CVarExpression::~CVarExpression
// Description	    : Will delete pvr objects if m_bDestroyPVRs is true
// Return type		: 
///////////////////////////////////////////////////////////
CVarExpression::~CVarExpression()
{
	if (m_bDestroyPVRs)
		{
		delete m_pvrLeft;
		delete m_pvrRight; // note if NULL then has no effect
		}
}
