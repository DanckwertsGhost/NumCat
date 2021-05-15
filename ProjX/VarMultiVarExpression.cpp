// VarMultiVarExpression.cpp: implementation of the CVarMultiVarExpression class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VarMultiVarExpression.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVarMultiVarExpression::CVarMultiVarExpression(bool bDestroyPVRs ):CVarExpression(bDestroyPVRs)
{

}

CVarMultiVarExpression::~CVarMultiVarExpression()
{
	if (m_bDestroyPVRs)
		{
		for (m_itVP=m_vecPVR.begin();m_itVP!=m_vecPVR.end();m_itVP++)
				delete (*m_itVP);
		m_vecPVR.clear();
		}

}
