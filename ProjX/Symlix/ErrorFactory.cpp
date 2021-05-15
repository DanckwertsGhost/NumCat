// ErrorFactory.cpp: implementation of the CErrorFactory class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <objbase.h>


#include "ErrorFactory.h"
#include "SymlixError.h"



CErrorFactory* CErrorFactory::m_instance = NULL;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////
// Function name	: CErrorFactory::CErrorFactory
// Description	    : Private constructor - other code supports singleton
///////////////////////////////////////////////////////////
CErrorFactory::CErrorFactory():m_bIsOK(true),m_pIErrorRun(NULL),m_pErrorRun(NULL)
{
	InitializeCriticalSection(&m_csErrorUpdates);
	createErrorRun();
}


///////////////////////////////////////////////////////////
// Function name	: CErrorFactory::~CErrorFactory
// Description	    : Private - should be called by cleanUpInstance
///////////////////////////////////////////////////////////
CErrorFactory::~CErrorFactory()
{
	CCritCheck cc(m_csErrorUpdates); // lets die in a state of grace
	deleteErrorRun();
}


///////////////////////////////////////////////////////////
// Function name	: static CErrorFactory::instance
// Description	    : If instance exits return that - otherwise construct
//                    ensures only one singleton object.
// Return type		: CErrorFactory* 
///////////////////////////////////////////////////////////
CErrorFactory* CErrorFactory::instance() 
{
  if (!m_instance)
		m_instance = makeInstance();

  return m_instance;
}


///////////////////////////////////////////////////////////
// Function name	: static CErrorFactory::makeInstance
// Description	    : Private function
// Return type		: CErrorFactory* 
///////////////////////////////////////////////////////////
CErrorFactory* CErrorFactory::makeInstance() 
{
    atexit(&cleanUpInstance);
    return (newtrack CErrorFactory());
}


///////////////////////////////////////////////////////////
// Function name	: CErrorFactory::cleanUpInstance
// Description	    : Lets tidy up before we leave this world
//                    called by atexit.
// Return type		: void 
///////////////////////////////////////////////////////////
void CErrorFactory::cleanUpInstance() 
{
  delete m_instance;
  m_instance = NULL; // just to be sure
}



///////////////////////////////////////////////////////////
// Function name	: CErrorFactory::createErrorRun
// Description	    : Private helper function
// Return type		: bool 
///////////////////////////////////////////////////////////
bool CErrorFactory::createErrorRun()
{
	HRESULT hr;

	deleteErrorRun(); // will clear any exiting records - but allow for COM object to continue if held elsewhere

	hr = CoCreateInstance(CLSID_NumCatErrorRun,NULL,CLSCTX_INPROC_SERVER,IID_INumCatErrorRun,(void**)&m_pIErrorRun);
		
		if ((FAILED(hr))||(!m_pIErrorRun))
			{
			m_bIsOK = false;
			deleteErrorRun();
			return m_bIsOK;
			}
	
	m_pErrorRun = dynamic_cast<CSymlixErrorRun*>(m_pIErrorRun);

	if (!m_pErrorRun) // will be NULL if cats fails
			{
			m_bIsOK = false;
			deleteErrorRun();
			return m_bIsOK;
			}

	if ((m_pErrorRun)&&(m_pIErrorRun))
			m_bIsOK = true;
			else
			m_bIsOK = false;

	return m_bIsOK;
}


///////////////////////////////////////////////////////////
// Function name	: CErrorFactory::deleteErrorRun
// Description	    : Its important to keep m_pErrorRun and m_pIErrorRun
//                    in step - hence this helper function.
// Return type		: void 
///////////////////////////////////////////////////////////
void CErrorFactory::deleteErrorRun()
{

ATLTRACE("CErrorFactory::deleteErrorRun()  m_pErrorRun %d, m_pIErrorRun %d\n",m_pErrorRun,m_pIErrorRun);
	
	if (m_pErrorRun)
			{
			ASSERT2(m_pIErrorRun); // this should never have happened
			m_pErrorRun = NULL; // now you might think that makes a memory leak - but will release COM object at same object
			}

	if (m_pIErrorRun)
			{
#ifndef NDEBUG
			int iRefCount;
			iRefCount = m_pIErrorRun->Release();
			ATLTRACE(" ref count = %d after m_pIErrorRun->Release()\n",iRefCount);
#else
			m_pIErrorRun->Release();
#endif
			m_pIErrorRun = NULL;
			}

}


///////////////////////////////////////////////////////////
// Function name	: CErrorFactory::newErrorRun
// Description	    : Create a new Error run obejct
//                    to agregate errors in.
// Return type		: void 
///////////////////////////////////////////////////////////
void CErrorFactory::newErrorRun()
{
	CCritCheck cc(m_csErrorUpdates);
	createErrorRun();
}



///////////////////////////////////////////////////////////
// Function name	: CErrorFactory::addError
// Description	    : 
// Return type		: void 
// Argument         : const char *sDescription
// Argument         : enumNumCatErrorCode eLevel
// Argument         : const char *sSource
// Argument         : long iLine
// Argument         : long iX
// Argument         : const char* sCodeSource
// Argument         : long iCodeLine
///////////////////////////////////////////////////////////
void CErrorFactory::addError(const char *sDescription, enumNumCatErrorCode eLevel, const char *sSource, long iLine, long iX, const char* sCodeSource, long iCodeLine )
{
	INumCatError* pINumCatError = NULL;
	CSymlixError* pSymlixError = NULL;
	HRESULT hr;

	CCritCheck cc(m_csErrorUpdates); // spare us from thread based balls ups

	hr = CoCreateInstance(CLSID_NumCatError,NULL,CLSCTX_INPROC_SERVER,IID_INumCatError,(void**)&pINumCatError);
		
		if ((FAILED(hr))||(!pINumCatError))
			{
			m_bIsOK = false;
			ATLTRACE("<Error#> Failed to create Error COM object in line %d ",__LINE__);
			ATLTRACE(__FILE__);ATLTRACE("\n");
			ASSERT2(false); // this is bad - check reasons
			return;
			}
	
	pSymlixError = dynamic_cast<CSymlixError*>(pINumCatError);

	if (!pSymlixError) // will be NULL if cats fails
			{
			m_bIsOK = false;
			ATLTRACE("<Error#> Failed to fully create Error COM object in line %d ",__LINE__);
			ATLTRACE(__FILE__);ATLTRACE("\n");
			pINumCatError->Release();
			ASSERT2(false); // this is bad - check reasons
			return;
			}
	pSymlixError->setError(sDescription,eLevel,sSource,iLine,iX,sCodeSource,iCodeLine);


	ASSERT2(m_pErrorRun); // just shouldn't happen
	if (m_pErrorRun) // to be sure - can't let this screw up in the wild
		m_bIsOK = m_pErrorRun->addError(pINumCatError);
		else
		m_bIsOK = false;


	pINumCatError->Release(); // copy no longer needed here

}



///////////////////////////////////////////////////////////
// Function name	: CErrorFactory::addError
// Description	    : Add error based on the following information
//                    this version used reference to a Token
// Return type		: void 
// Argument         : const char* sDescription
// Argument         : enumNumCatErrorCode eLevel
// Argument         : const CToken& cTok
// Argument         : const char* sCodeSource
// Argument         : long iCodeLine
///////////////////////////////////////////////////////////
void CErrorFactory::addError( const char* sDescription, enumNumCatErrorCode eLevel,  const CToken& cTok, const char* sCodeSource, long iCodeLine )
{

// since this call the other defn of addError a critical section must NOT be defined here
	string sErr = sDescription; //  the error text
	sErr.append(" : [");
	sErr.append(cTok.getString().c_str());
	sErr.append("] ");
	addError(sErr.c_str(),eLevel,cTok.getLocation().getRefFile()->c_str(),cTok.getLine(),cTok.getX(),sCodeSource,iCodeLine);

}



///////////////////////////////////////////////////////////
// Function name	: CErrorFactory::getErrorRun
// Description	    : Returns error run with AddRef
//                    and starts a new error run.
// Return type		: INumCatErrorRun* 
///////////////////////////////////////////////////////////
INumCatErrorRun* CErrorFactory::getErrorRun()
{
#ifndef NDEBUG
	long iCheck;
#endif 

 ASSERT2(m_pIErrorRun);
 if (!m_pIErrorRun)
		return NULL;

 CCritCheck cc(m_csErrorUpdates); // nail things to the floor
 INumCatErrorRun* pIOldErrorRun = m_pIErrorRun; 
#ifndef NDEBUG
 iCheck = pIOldErrorRun->AddRef();
 ASSERT2(iCheck>1); // as there should be two at this point - but don't want this check in the wild
#else
 pIOldErrorRun->AddRef();
#endif
 bool bResult = createErrorRun();
 ASSERT2(bResult);

 ASSERT2(pIOldErrorRun!=m_pIErrorRun); // just to be sure

 return pIOldErrorRun;
}


///////////////////////////////////////////////////////////
// Function name	: CErrorFactory::numberOfCurrentErrors
// Description	    : For the current error collection obejct
//                    how many errors does it have ?
// Return type		: long 
///////////////////////////////////////////////////////////
long CErrorFactory::numberOfCurrentErrors()
{

	long iErr =0;
    CCritCheck cc(m_csErrorUpdates); // nail things to the floor


	if (!m_pIErrorRun)
		return 0;

	HRESULT hr =  m_pIErrorRun->get_CountErrors(&iErr);

	ASSERT2(SUCCEEDED(hr));

	if (SUCCEEDED(hr))
		return iErr;

	return 0;
}



///////////////////////////////////////////////////////////
// Function name	: CErrorFactory::clearErrors
// Description	    : Clear all errors
//                    this is done by creating another object
// Return type		: void 
///////////////////////////////////////////////////////////
void CErrorFactory::clearErrors()
{

	ASSERT2(m_bIsOK);
	if (!m_bIsOK)
			return;

	INumCatErrorRun* pOldRun = this->getErrorRun();	

	if (pOldRun)
		pOldRun->Release();

}
