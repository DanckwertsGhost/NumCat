// SubExpression.cpp: implementation of the CSubExpression class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SubExpression.h"
#include "Equation.h"
#include "VarClassFactory.h"
#ifndef NDEBUG
#include <assert.h>
#endif

//#define EXTRADEBUG
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////
// Function name	: CSubExpression::CSubExpression
// Description	    : 
// Return type		: 
// Argument         : CToken* pct):m_pcvr(NULL)
// Argument         : m_pct(pct
///////////////////////////////////////////////////////////
CSubExpression::CSubExpression(CToken* pct,list<CEquation*>* pvecpEquations, CVarClassFactory* pvcf):m_pcvr(NULL),m_pct(pct),m_bNegValue(false)
{


	#ifndef NDEBUG
	assert(pvcf!=NULL); // make sure this is being set up correctly
	assert(pct!=NULL);
	assert(pvecpEquations!=NULL);

	#ifdef EXTRADEBUG
	cerr << "CSubExpression::CSubExpression(CToken* pct,vector<CEquation>* pvecEquations, CVarClassFactory* pvcf)\n";
	cerr << "CToken :: " << *m_pct<<endl;cerr.flush();
	cerr << "Parent, if any :: " << *(m_pct->getRootTokenPt())<<endl;cerr.flush();
	#endif

	#endif

	switch(m_pct->getRootTokenPt()->getType())
 	{
	case ctSubsVariable:
			{
			bool bFind =false;
			list<CEquation*>::iterator itpEq = pvecpEquations->begin();
			list<CEquation*>::iterator itpFound = pvecpEquations->end();

			while(itpEq!=pvecpEquations->end())
				{
	#ifdef EXTRADEBUG
					cerr << *((*itpEq)->getLHS()->getRootTokenPt()) <<endl<<*pct<<endl;cerr.flush();
	#endif
					if (*((*itpEq)->getLHS()->getRootTokenPt())==pct->getRootToken())
						{
						itpFound=itpEq;
						itpEq=pvecpEquations->end();
						}
						else
						itpEq++;
				}

			if (itpFound==pvecpEquations->end())
					throw newtrack CSubExpException("Failed to create CSubExpression object","Unable to locate equation for a substitable variable");


			#ifndef NDEBUG
			#ifdef EXTRADEBUG
			cerr << "LHS = "<<(*((*itpFound)->getLHS()))<<endl;
			cerr << "LHS Root = "<<(*((*itpFound)->getLHS()->getRootTokenPt()))<<endl;
			#endif
			assert((*itpFound)->getLHS()->getRootTokenPt()->getpVarRoot());// Undefined Subs Variable
			#endif
			m_pcvr = (*itpFound)->getLHS()->getRootTokenPt()->getpVarRoot();

			if (m_pcvr==NULL)
					throw newtrack CSubExpException("Failed to create CSubExpression object","Looking for subsitution variable with no VarRoot");

			m_pct = NULL; // won't be using that information any more
			} 
			break;
	case ctNumber:
			m_pcvr = pvcf->createValue(pct->getRootTokenPt()->getNumber());
			if (pct->getNumber()<0) // as we need to indetify negative numbers for evaluating expressions sucessfully as they may really indicate -ve operator number 
					m_bNegValue=true;
			break;
	case ctDepVariable:
	case ctIndVariable:
	case ctDerivative:
			#ifdef EXTRADEBUG
			cerr << "EDG Index for "<<pct->getStringRef().c_str() << " = "<<pct->getRootTokenPt()->getIndex()<<endl;
			#endif
			m_pcvr = pvcf->createVariable(pct->getRootTokenPt()->getIndex());
		break;
	case ctArrayKeyWord:
	case ctDelim:
			m_pct = pct;
		break;
	default:
		#ifndef NDEBUG
		cerr << *m_pct<<endl;cerr.flush();
		cerr << m_pct->getRootToken()<<endl;cerr.flush();
		assert(false); // bring attention directly to this
		#endif
		throw newtrack CSubExpException("Failed to create CSubExpression object","Looking for subsitution variable with no VarRoot");
		break;
	}



}


///////////////////////////////////////////////////////////
// Function name	: CSubExpression::CSubExpression
// Description	    : 
// Return type		: 
// Argument         : CVarRoot* pcvr):m_pcvr(pcvr)
// Argument         : m_pct(NULL
///////////////////////////////////////////////////////////
/*CSubExpression::CSubExpression(CVarRoot* pcvr):m_pcvr(pcvr),m_pct(NULL)
{
}*/


///////////////////////////////////////////////////////////
// Function name	: CSubExpression::CSubExpression
// Description	    : 
// Return type		: 
// Argument         : CSubExpression* pcseLHS
// Argument         : CSubExpression* pcseMid
// Argument         : CSubExpression* pcseRHS):m_pcvr(NULL)
// Argument         : m_pct(NULL
///////////////////////////////////////////////////////////
CSubExpression::CSubExpression(CSubExpression* pcseLHS, CSubExpression* pcseMid, CSubExpression* pcseRHS, CVarClassFactory* pvcf):m_pcvr(NULL),m_pct(NULL),m_bNegValue(false)
{
	
	if (!pcseMid->isTokenDelim())
			throw newtrack CSubExpException("Failed to create CSubExpression object","Mid token is not a deliminator");

	if (!pcseLHS->isRootToken())
			throw newtrack CSubExpException("Failed to create CSubExpression object","Left expression is not a CVarRoot");
			
	if (!pcseRHS->isRootToken())
			throw newtrack CSubExpException("Failed to create CSubExpression object","Right expression is not a CVarRoot");


	m_pcvr = pvcf->createExpression(pcseMid->getToken()->getStringRef().c_str(),pcseLHS->m_pcvr,pcseRHS->m_pcvr);

	if (!m_pcvr) // then expression was not recognised to be created - must report this
		throw  newtrack CSubExpException("Failed to create CSubExpression object","Right expression is not a c");
}


///////////////////////////////////////////////////////////
// Function name	: CSubExpression::CSubExpression
// Description	    : constructor for forcing operation (plus only )
// Return type		: 
// Argument         : CSubExpression* pcseLHS
// Argument         : CSubExpression* pcseRHS
// Argument         : const char* pOp
// Argument         : CVarClassFactory* pcvf )
///////////////////////////////////////////////////////////
CSubExpression::CSubExpression(CSubExpression* pcseLHS, CSubExpression* pcseRHS, const char* pOp, CVarClassFactory* pcvf ):m_pcvr(NULL),m_pct(NULL),m_bNegValue(false)
{
	ASSERT2(pOp);
	if (!pOp)
		throw newtrack CSubExpException("Failed to create CSubExpression object","Internal information had difficulty.");

	if (strlen(pOp)!=1)
		throw newtrack CSubExpException("Failed to create CSubExpression object","Internal information had difficulty.");
		 
	switch(pOp[0])
		{
		case '+':
			m_pcvr = pcvf->createExpression(g_Plus,pcseLHS->m_pcvr,pcseRHS->m_pcvr);			


			break;
		default:
			throw newtrack CSubExpException("Failed to create CSubExpression object","Unhandled operator found or operator in wrong location.");
			break;


		}

	if (!m_pcvr) // then expression was not recognised to be created - must report this
		throw  newtrack CSubExpException("Failed to create CSubExpression object","Right expression is not a c");

}

///////////////////////////////////////////////////////////
// Function name	: CSubExpression::CSubExpression
// Description	    : 
// Return type		: 
// Argument         : CSubExpression* pcseLHS - should be a function
// Argument         : CSubExpression* pcseRHS - should hold value to go into function
///////////////////////////////////////////////////////////
CSubExpression::CSubExpression(CSubExpression* pcseLHS, CSubExpression* pcseRHS, CVarClassFactory* pvcf):m_pcvr(NULL),m_pct(NULL),m_bNegValue(false)
{

	// the only exception here is when the LHS is negative and RHS is not a delim
	if ((pcseLHS->isTokenDelim())&&(pcseLHS->getToken()->getStringRef().compare(g_Neg)==0))
		{
		if (!pcseRHS->isTokenDelim())
				#ifndef NDEBUG
				assert(false);
				#else
				throw newtrack CSubExpException("Failed to create CSubExpression object","Attempting to take negative of a delim token");
				#endif
		
		m_pcvr = pvcf->createExpression(g_Neg,pcseRHS->m_pcvr);

		if (!m_pcvr) // then expression was not recognised to be created - must report this
			throw  newtrack CSubExpException("Failed to create CSubExpression object","Right expression is not a c");
		
		return;
		}

	if (!pcseLHS->isTokenDelim())
			#ifndef NDEBUG
			assert(false);
			#else
			throw newtrack CSubExpException("Failed to create CSubExpression object","Left expression is not a delim function");
			#endif

	if (!pcseRHS->isRootToken())
			#ifndef NDEBUG
			assert(false);
			#else
			throw newtrack CSubExpException("Failed to create CSubExpression object","Right expression is not a CVarRoot");
			#endif

	m_pcvr = pvcf->createExpression(pcseLHS->getToken()->getStringRef().c_str(),pcseRHS->m_pcvr);

	if (!m_pcvr) // then expression was not recognised to be created - must report this
		throw  newtrack CSubExpException("Failed to create CSubExpression object","Right expression is not a c");

}


///////////////////////////////////////////////////////////
// Function name	: CSubExpression::CSubExpression
// Description	    : 
// Return type		: 
// Argument         : CSubExpression* pcseLHS - with the function type
// Argument         : vector< CSubExpression* >& rvecRHS -  array of variables to be fed to function
// Argument         : CVarClassFactory* pvcf 
///////////////////////////////////////////////////////////
CSubExpression::CSubExpression(CSubExpression* pcseLHS, vector< CSubExpression* >& rvecRHS, CVarClassFactory* pvcf):m_pcvr(NULL),m_pct(NULL),m_bNegValue(false)
{
	vector< CVarRoot* > vecpCVR;
	vector< CSubExpression* >::iterator it;

	if (!pcseLHS)
		throw newtrack CSubExpException("Failed to create CSubExpression object","Left expression is not a CVarRoot");

	for(it=rvecRHS.begin();it!=rvecRHS.end();it++)
		if (!(*it)->isTokenDelim()) // just for safety
				vecpCVR.push_back((*it)->getVarRoot());			

	if (vecpCVR.size()==0)
		throw newtrack CSubExpException("Failed to create CSubExpression object","Right expression is not a CVarRoot");

	m_pcvr = pvcf->createMultiVarExpression(pcseLHS->getToken()->getStringRef().c_str(),vecpCVR);

	if (!m_pcvr) // then expression was not recognised to be created - must report this
		throw  newtrack CSubExpException("Failed to create CSubExpression object");
	
}


///////////////////////////////////////////////////////////
// Function name	: CSubExpression::CSubExpression
// Description	    : 
// Return type		: 
// Argument         : const CSubExpression& cse
///////////////////////////////////////////////////////////
CSubExpression::CSubExpression(const CSubExpression& cse)
{
	Copy(cse);

}

CSubExpression::~CSubExpression()
{

}


void CSubExpression::Copy(const CSubExpression& cse)
{
	m_pct = cse.m_pct;
	m_pcvr = cse.m_pcvr;
    m_bNegValue = cse.m_bNegValue;

}
/*
CSubExpression& CSubExpression::operator + (const CSubExpression& cse)
{
#ifndef NDEBUG
	assert(false); //NYI
#endif
	return *this;
}

CSubExpression& CSubExpression::operator - (const CSubExpression& cse)
{
#ifndef NDEBUG
	assert(false); //NYI
#endif
	return *this;
}


CSubExpression& CSubExpression::operator * (const CSubExpression& cse)
{
#ifndef NDEBUG
	assert(false); //NYI
#endif
	return *this;
}


CSubExpression& CSubExpression::operator / (const CSubExpression& cse)
{
#ifndef NDEBUG
	assert(false); //NYI
#endif
	return *this;
}


CSubExpression& CSubExpression::operator ^ (const CSubExpression& cse)
{
#ifndef NDEBUG
	assert(false); //NYI
#endif
	return *this;
}*/

bool CSubExpression::isTokenDelim() const
{
	if (!m_pct)
			return false;

	return ((m_pct->IsOfType(ctDelim))||(m_pct->IsOfType(ctArrayKeyWord)));
}

bool CSubExpression::isRootToken() const
{
	if (!m_pcvr)
			return false;

	return true;

}

CToken* CSubExpression::getToken() const
{
	
	return m_pct;
}

CVarRoot* CSubExpression::getVarRoot() const
{


	return m_pcvr;
}

ostream& CSubExpression::out(ostream& os) const
{
	if (m_pct)
		os << m_pct->getStringRef().c_str();
		else
		if (m_pcvr)
			os << "CVR";
			else
			os << "<Error#>";
	return os;
}


CSubExpException::CSubExpException(const char* sHeading, const char* sMessage/*=NULL*/)
{

	strcpy(m_sHeading,sHeading);
	if (sMessage)
		strcpy(m_sMessage,sMessage);

}

ostream& CSubExpException::out(ostream& os)
{

	os << "[CSubExpException] " << m_sHeading;
	if (m_sMessage)
		os << " : " << m_sMessage;
	return os;

}





