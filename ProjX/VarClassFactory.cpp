// VarClassFactory.cpp: implementation of the CVarClassFactory class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VarClassFactory.h"
#include "global.h"
#include "VarExp.h"
#include "VarVariable.h"
#include "VarValue.h"
#include "VarMultiVarExpression.h"
#ifndef NDEBUG
#include <assert.h>
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////
// Function name	: CVarClassFactory::CVarClassFactory
// Description	    : protected constructor
// Return type		: 
///////////////////////////////////////////////////////////
CVarClassFactory::CVarClassFactory()
{
	m_vecCVarRoot.reserve(20);
}


///////////////////////////////////////////////////////////
// Function name	: CVarClassFactory::~CVarClassFactory
// Description	    : protected destructor
// Return type		: 
///////////////////////////////////////////////////////////
CVarClassFactory::~CVarClassFactory()
{
	vector< CVarRoot* >::reverse_iterator it;

	// 
	for( it=m_vecCVarRoot.rbegin();it!=m_vecCVarRoot.rend();it++)
			delete *it;
}

CVarClassFactory* CVarClassFactory::m_instance = 0;


///////////////////////////////////////////////////////////
// Function name	: CVarClassFactory::cleanupInstance
// Description	    : delete singleton instance
// Return type		: void 
///////////////////////////////////////////////////////////
void CVarClassFactory::cleanupInstance()
{ 
   delete m_instance;
   m_instance = 0;
}
         



///////////////////////////////////////////////////////////
// Function name	: CVarClassFactory::makeInstance
// Description	    : create singleton and add function to delete object to atexit()
// Return type		: CVarClassFactory* 
///////////////////////////////////////////////////////////
CVarClassFactory* CVarClassFactory::makeInstance()
{
	atexit(&cleanupInstance);
    return (newtrack CVarClassFactory);
}


///////////////////////////////////////////////////////////
// Function name	: CVarClassFactory::createExpression
// Description	    : Class factory method for expressions.
//                    Life cycle of object is 
//                    controlled from within the class.
// Return type		: CVarRoot* - either pointer to object or null
// Argument         : const char* sType
// Argument         : CVarRoot* cvrL
// Argument         : CVarRoot* cvrR
///////////////////////////////////////////////////////////
CVarRoot* CVarClassFactory::createExpression(const char* sType, CVarRoot* cvrL, CVarRoot* cvrR)
{
	long lType = strlen(sType);
	CVarRoot* pcvrReturn = NULL;
	#ifndef NDEBUG
	assert(lType>0);
	#endif
	if (lType<1)
			return NULL;
				
	if (cvrR) // look at types that have a LHS and RHS
		{
		
		if (lType==1) // then can use case switch - hurray
			{
			
			switch( sType[0] )
			{
				case c_Plus:
				pcvrReturn = newtrack CVarExpAdd(cvrL,cvrR);
				break;
				case c_Minus:
				pcvrReturn = newtrack CVarExpMinus(cvrL,cvrR);
				break;
				case c_Div:
				pcvrReturn = newtrack CVarExpDiv(cvrL,cvrR);
				break;
				case c_Mult:
				pcvrReturn = newtrack CVarExpMulti(cvrL,cvrR);
				break;
				case c_Pow:
				pcvrReturn = newtrack CVarExpPow(cvrL,cvrR);
				break;
				case c_GT:
				pcvrReturn = newtrack CVarExpGT(cvrL,cvrR);
				break;
				case c_LT:
				pcvrReturn = newtrack CVarExpLT(cvrL,cvrR);
				break;
				default:
				pcvrReturn = NULL; // yes its assigned there initally also, but lets play safe
			} // END switch( sType[0] )
			} // END if (lType==1)
			else
			{	
			
/*				if (strcmp(sType,g_Power)==0)
					pcvrReturn = newtrack CVarExpPow(cvrL,cvrR);*/
				
			} // END else (lType==1)
		} // END if (cvrR) 


	if (!pcvrReturn) // ie hasn't been assigned yet 
		{ // look at types with only LHS
			if ((strcmp(sType,g_Neg)==0)||(strcmp(sType,g_Minus)==0))
				pcvrReturn = newtrack CVarExpNeg(cvrL);
					else
					{
						CFuncIdentifierSingleton* fis = CFuncIdentifierSingleton::instance();
							switch(fis->identify(sType))
							{
							case C_LnFunc:
								pcvrReturn = newtrack CVarExpLn(cvrL);
								break;
							case C_ExpFunc:
								pcvrReturn = newtrack CVarExpExp(cvrL);
								break;
							case C_SinFunc:
								pcvrReturn = newtrack CVarExpSin(cvrL);
								break;
							case C_CosFunc:
								pcvrReturn = newtrack CVarExpCos(cvrL);
								break;
							case C_TanFunc:
								pcvrReturn = newtrack CVarExpTan(cvrL);
								break;
							case C_ASinFunc:
								pcvrReturn = newtrack CVarExpASin(cvrL);
								break;
							case C_ACosFunc:
								pcvrReturn = newtrack CVarExpACos(cvrL);
								break;
							case C_ATanFunc:
								pcvrReturn = newtrack CVarExpATan(cvrL);
								break;
							case C_PowFunc:
								ATLTRACE("Unexpected function identified on line %d %s\n",__LINE__,__FILE__);
								ATLASSERT(false);
								break;
							case C_Log10Func:
								pcvrReturn = newtrack CVarExpLog(cvrL);
								break;
							case C_AbsFunc:
								pcvrReturn = newtrack CVarExpAbs(cvrL);
								break;
							case C_IntFunc:
								pcvrReturn = newtrack CVarExpInteger(cvrL);
								break;
							case C_IntRoundUpFunc:
								pcvrReturn = newtrack CVarExpIntegerUp(cvrL);
								break;
							case C_NotAFunc:
							default:
								ATLTRACE("Unexpected function identified on line %d %s\n",__LINE__,__FILE__);
								ATLASSERT(false);
								break;
							}

					}
		}

	if (pcvrReturn!=NULL)
			m_vecCVarRoot.push_back(pcvrReturn); // store copy of pointer to object for clean up later

	return pcvrReturn;
}


///////////////////////////////////////////////////////////
// Function name	: CVarClassFactory::createMultiVarExpression
// Description	    : 
// Return type		: CVarRoot* 
// Argument         : const char* sType
// Argument         : vector< CVarRoot* >& rveccvrR
///////////////////////////////////////////////////////////
CVarRoot* CVarClassFactory::createMultiVarExpression(const char* sType, vector< CVarRoot* >& rveccvrR)
{
	CVarRoot* pcvrReturn = NULL;
	CFuncIdentifierSingleton* fis = CFuncIdentifierSingleton::instance();

	switch(fis->identifyArrayFunc(sType))
	{
	case C_AF_Sum: 
			pcvrReturn = newtrack CVarArraySum(rveccvrR);
		break;
	case C_AF_Count:
			pcvrReturn = newtrack CVarArrayCount(rveccvrR);
		break;
	case C_AF_Avrg:
			pcvrReturn = newtrack CVarArrayAvrg(rveccvrR);
		break;
	default:
		break;
	}

	if (pcvrReturn!=NULL)
			m_vecCVarRoot.push_back(pcvrReturn); // store copy of pointer to object for clean up later

	return pcvrReturn;
}


///////////////////////////////////////////////////////////
// Function name	: CVarClassFactory::createVariable
// Description	    : Class Factory for Variables
// Return type		: CVarRoot* 
// Argument         : const long lIndex
///////////////////////////////////////////////////////////
CVarRoot* CVarClassFactory::createVariable(const long lIndex)
{
	CVarRoot* pcvrReturn=NULL;
#ifndef NDEBUG
	assert(lIndex>=0);
#endif
	if (lIndex<0)
		return pcvrReturn;

	pcvrReturn = newtrack CVarVariable(lIndex);

	if (pcvrReturn!=NULL)
			m_vecCVarRoot.push_back(pcvrReturn); // store copy of pointer to object for clean up later

	return pcvrReturn;

}


///////////////////////////////////////////////////////////
// Function name	: CVarClassFactory::createValue
// Description	    : Class factory for values
// Return type		: CVarRoot* 
// Argument         : const xt_value xtv
///////////////////////////////////////////////////////////
CVarRoot* CVarClassFactory::createValue(const xt_value xtv)
{
	CVarRoot* pcvrReturn=NULL;

	pcvrReturn = newtrack CVarValue(xtv);

	if (pcvrReturn!=NULL)
			m_vecCVarRoot.push_back(pcvrReturn); // store copy of pointer to object for clean up later

	return pcvrReturn;

}


