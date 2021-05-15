// SymlixComp.cpp : Implementation of CSymlix
#include "stdafx.h"


#ifdef NALPERION // adding copy protection
#include "CopyProtection.h"
#endif

#include "Symlix.h"
#include "SymlixComp.h"
#include "..\CritCheck.h"
#include <process.h>
#include "ErrorFactory.h"
#include "EventFactory.h"

#ifdef SOFTWAREPASSPORT
#include "ARDRM.h"
#endif

class CSymlixRunInfo
  {
  public:
	CSymlixRunInfo( bool* pb, CSimulation* pds, CSymlix* pHost, short is):pbContinue(pb),pDynObj(pds),m_pHostSymlix(pHost), iSig(is){}
	CSymlixRunInfo( const CSymlixRunInfo& cri):pbContinue(cri.pbContinue),pDynObj(cri.pDynObj),m_pHostSymlix(cri.m_pHostSymlix),iSig(cri.iSig){}
	~CSymlixRunInfo(){}
	bool* pbContinue;
	CSimulation* pDynObj;
	short iSig;
	CSymlix* m_pHostSymlix;
  };



void SimRunThread( void* pParams )
  { 
	long iCount;

	CSymlixRunInfo sri((*(static_cast<CSymlixRunInfo*>(pParams))));
	CCritCheck(sri.m_pHostSymlix->m_csSimulationRunning); // safeguard
	iCount = sri.m_pHostSymlix->AddRef();
	ATLTRACE("@@@ Start SimRunThread Ref count = %d\n",iCount);
	
	if (*sri.pbContinue) // then already running - can't run twice
			{
			SetEvent( sri.m_pHostSymlix->m_hEvent1 ); // all data copied
			sri.m_pHostSymlix->Release();
			_endthread();
			}
			
	// change in running status need to be protected
	{
	CCritCheck cc(sri.m_pHostSymlix->m_csModelRunningState);
	(*sri.pbContinue) = true;
	}

	SetEvent( sri.m_pHostSymlix->m_hEvent1 ); // all data copied

	bool bResult = sri.pDynObj->runSimulation(sri.m_pHostSymlix->m_pINumCatDataServicesCB);

	// change in running status need to be protected
	{
	CCritCheck cc(sri.m_pHostSymlix->m_csModelRunningState);
	if (bResult)
				sri.m_pHostSymlix->m_essState=runCompleted;
				else
				sri.m_pHostSymlix->m_essState=modelError;

	(*sri.pbContinue) = false;
	}

	SetEvent(sri.m_pHostSymlix->m_hEventEndSimThread); // its the end
	iCount = sri.m_pHostSymlix->Release();
	ATLTRACE("_endthread() and release\n");
	ATLTRACE("@@@End SimRunThread Ref count = %d\n",iCount);
	_endthread();
  };




///////////////////////////////////////////////////////////
// Function name	: CISymlixDataServicesCallBack::startDataServices
// Description	    : Function passed to the solver to allow it to
//                    indicate when data services start
// Return type		: void 
///////////////////////////////////////////////////////////
void CISymlixDataServicesCallBack::startDataServices()
{
	m_cSymlix.eventDDEStatus(esddeStart);

}


///////////////////////////////////////////////////////////
// Function name	: CISymlixDataServicesCallBack::endDataServices
// Description	    : Function passed to the solver to allow it to
//                    indicate when data services stop
// Return type		: void 
///////////////////////////////////////////////////////////
void CISymlixDataServicesCallBack::endDataServices()
{
	m_cSymlix.eventDDEStatus(esddeStop);

}

/////////////////////////////////////////////////////////////////////////////
// CSymlix



///////////////////////////////////////////////////////////
// Function name	: CSymlix::FinalRelease
// Description	    : Destructor - clear up heap if needed
// Return type		: 
///////////////////////////////////////////////////////////
void CSymlix::FinalRelease()
{
	killThreads();
	{
	ASSERT2(!m_bBkgrndSolverRun); // as killthreads should have delt with this
	CCritCheck cc(m_csSimulationRunning); // the thread must have exited
	if (m_pICallBack)
		m_pICallBack->Release(); // life time management is up to COM

	delete m_pINumCatDataServicesCB;

	if (m_psimulation) // I think delete would handle the NULL case OK, but lets make it clear
		delete m_psimulation;
	}
	CErrorFactory::forceKill(); // or else will try to call release after COM ends
}


///////////////////////////////////////////////////////////
// Function name	: CSymlix::InterfaceSupportsErrorInfo
// Description	    : Implement Error interface
// Return type		: STDMETHODIMP 
// Argument         : REFIID riid
///////////////////////////////////////////////////////////
STDMETHODIMP CSymlix::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_INumCat
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

/*
///////////////////////////////////////////////////////////
// Function name	: CSymlix::CheckFile
// Description	    : Check file - without actually loading it.
//                    Report errors via Report Error Event
// Return type		: STDMETHODIMP 
// Argument         : BSTR *sFileName
// Argument         : VARIANT_BOOL *pvbResult
///////////////////////////////////////////////////////////
STDMETHODIMP CSymlix::CheckFile(BSTR *sFileName, VARIANT_BOOL *pvbResult)
{
	
	CSimulation* pSim=NULL;

	try
	{
	USES_CONVERSION;
	
	string sTest = OLE2A(sFileName[0]); 

	pSim = newtrack CSimulation;

	(*pvbResult) = CheckSimulationFile(sTest,pSim);	

	delete pSim;

	}
	catch(...) // last line of defence - no C++ exceptions can be allowed to propagate
	{
	delete pSim;
	ATLTRACE("CSymlix::CheckFile(BSTR *sFileName, VARIANT_BOOL *pvbResult) Fail on unhandled exception");
	(*pvbResult) = false;	
	return E_FAIL;
	}
	
	return S_OK;
}
*/


///////////////////////////////////////////////////////////
// Function name	: CSymlix::LoadModel
// Description	    : Create and check stream and if OK pass on DataStore and Load file
//                    to create model ready to run.
// Return type		: STDMETHODIMP 
// Argument         : /*[in]*/ BSTR* sFileName
// Argument         : /*[in]*/ IARDataStore* pIStore
// Argument         : /*[out,retval]*/ VARIANT_BOOL* pvbResult
///////////////////////////////////////////////////////////
STDMETHODIMP CSymlix::LoadModel(/*[in]*/ BSTR* sFileName,/*[in]*/ IARDataStore* pIStore, /*[out,retval]*/ VARIANT_BOOL* pvbResult)
{

	if (m_bBkgrndSolverRun) // thread with solver already running - can't do this
		{
		(*pvbResult)=VB_FALSE;
		return S_FALSE;
		}

	if (!pIStore) // then we can't do much and its an error
		{
		(*pvbResult)=VB_FALSE;
		return E_INVALIDARG;
		}


	//check Stream name is available
	HRESULT hr = pIStore->isAvailable(sFileName,pvbResult);

	if ((FAILED(hr))||(*pvbResult==0))
		{
		USES_CONVERSION;
		SYMERROR("Unable to open stream",errSystem,OLE2A(*sFileName),NOT_DEFINED,NOT_DEFINED);
		return S_FALSE;
		}

	try
	{

		CCritCheck cc(m_csSimulationRunning);

		if (m_psimulation)
			delete m_psimulation;

		{
		USES_CONVERSION;

		m_psimulation = newtrack CSimulation(pIStore,OLE2CA(*sFileName));
		if (m_psimulation)
			m_psimulation->setTag(OLE2A(m_cbRunTag));
		}
			
		if (!m_psimulation)
			{
			(*pvbResult)=false;
			SYMERROR("E_OUTOFMEMORY",errSystem,"",NOT_DEFINED,NOT_DEFINED);
			return E_OUTOFMEMORY;
			}


		if ((m_psimulation->getSimulationState()==cessHasFile)&&
			(m_psimulation->setUpSimulation()))
			{
			m_essState = modelLoaded;
			}
			else
			m_essState = modelError;

	}
	catch(...) // last line of defence - no C++ exceptions can be allowed to propagate
	{
		ATLTRACE("CSymlix::LoadModel Fail on unhandled exception");
		SYMERROR("CSymlix::LoadModel Fail on unhandled exception",errInternal,"",NOT_DEFINED,NOT_DEFINED);
		(*pvbResult) = false;	
		m_essState = modelError;
		return E_FAIL;
	}

	if (m_essState== modelLoaded)
					(*pvbResult)=VB_TRUE;
					else
					(*pvbResult)=VB_FALSE;
	return S_OK;
}




///////////////////////////////////////////////////////////
// Function name	: CSymlix::RunModel
// Description	    : Run a loaded model - return false if problem
// Return type		: STDMETHODIMP 
// Argument         : VARIANT_BOOL *pvbResult
///////////////////////////////////////////////////////////
STDMETHODIMP CSymlix::RunModel(long hInstance, /*[defaultvalue(NULL)]*/ INumCatHostCallBack* pINumCatHostCallBack, VARIANT_BOOL *pvbResult)
{

#ifdef SOFTWAREPASSPORT
	
	try
	{

	CARDRM* pdrm = CARDRM::instance();

	if (!pdrm)
		{
		SYMERRORLITE("A problem was found checking for the licence.",errInternal);
		return S_FALSE;
		}

	if (pdrm->hasErrors())
		{
		SYMERRORLITE("A problem was found checking for the licence.",errInternal);
		return S_FALSE;
		}

	if (pdrm->getExpired())
		{
		SYMERRORLITE("It appears the license has expired, hence the run has been cancelled.",errWarning);
		return S_FALSE;
		}
	
	if ((pdrm->getUser().compare("DEFAULT")!=0)&&(!pdrm->getVerified()))
		{
		SYMERRORLITE("It appears the license cannot be verified, hence the run has been cancelled.",errWarning);
		return S_FALSE;
		}

	}
	catch(...)
	{
		SYMERRORLITE("There was a problem with the DRM solution - run aborted",errInternal);

		return S_FALSE;
	}

#endif


#ifdef NALPERION

	#define STR_LENGTH ARCA_STRLENGTH 
    #define SYMNAME 10 // then length of "Symlix.dll"

	char szMessage[ARCA_STRLENGTH+2];
	char szRegValue[STR_LENGTH];
	DWORD dwLen = STR_LENGTH-2;
	long iLen;
	string sDLLLocation;

	enumNumCatErrorCode esErrCode = errWarning; // so has default value
	CRegKey crLicenseDLL;
	long iR = crLicenseDLL.Open(HKEY_LOCAL_MACHINE,TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\NumCat.dll"),KEY_READ);

	if (iR != ERROR_SUCCESS)
		{
         SYMERRORLITE("Unable to find registration information in registry.",errSystem);
		 SYMERRORLITE("Ensure installed files have not been moved, if necessary rerun installation.",errWarning);
		 return S_FALSE;
		}

	iR = crLicenseDLL.QueryValue(szRegValue,"",&dwLen);

	if (iR != ERROR_SUCCESS)
		{
         SYMERRORLITE("Unable to find a Symlix registry key.",errSystem);
		 SYMERRORLITE("Re-running the installation program may help.",errWarning);
		 crLicenseDLL.Close();
		 return S_FALSE;
		}
	//ATLTRACE(szRegValue);

	iLen = strlen(szRegValue);
	// test for iLen being less than SYMNAME long
	if (iLen<=SYMNAME)
		{
         SYMERRORLITE("Unable to find registration information in registry.",errSystem);
		 SYMERRORLITE2("A registry key has an unexpected value:",szRegValue,errWarning);
		 crLicenseDLL.Close();
		 return S_FALSE;
		}

	sDLLLocation = szRegValue;
	sDLLLocation = sDLLLocation.substr(0,iLen-10);
	//ATLTRACE(sDLLLocation.c_str());
	sDLLLocation.append("filechck.dll");

	crLicenseDLL.Close();

	strcpy(szMessage,"");

	int iCA = ARCheckAuthorization(sDLLLocation.c_str(),szMessage,esErrCode);


	if (iCA == ARCA_ERROR) // then an error needs to be reported
		{
		SYMERRORLITE(szMessage,esErrCode);
		return S_FALSE;
		}

	if ((iCA == 0)&&(strlen(szMessage)>0))
		SYMERRORLITE(szMessage,esErrCode);

	if (iCA!=0)
		{
		SYMERRORLITE("Unknown error with license system",errInternal);
		return E_FAIL;
		}

#endif

	if (m_essState!=modelLoaded)
		{
		(*pvbResult)=VB_FALSE; 
		return S_FALSE;
		}

	ASSERT2(m_psimulation); // should never get past m_essState test

	if (!m_psimulation) // its a serrious error
		{
		(*pvbResult)=VB_FALSE; 
		return E_FAIL;
		}

	try
	{
		m_essState=runInProgress;

		if (hInstance)
				{
				CSymlixRunInfo sri(&m_bBkgrndSolverRun,m_psimulation,this,0);
				unsigned long ithrd = _beginthread(SimRunThread,0,&sri);
				if (ithrd==-1) // then thread has failed
						{
						ResetEvent(m_hEvent1);
						(*pvbResult)=VB_FALSE; 
						SYMERRORLITE("Unable to create Symlix solver thread",errSystem);
						ATLTRACE("<Error#> Could not create thread in CSymlix::RunModel");
						return E_FAIL;
						}

				WaitForSingleObject( m_hEvent1, INFINITE );
				ResetEvent(m_hEvent1);
				(*pvbResult)=VB_TRUE; 
				}
				else
				{
				// add a feedback event
				vector<long> vecInds;
				vecInds.push_back(m_psimulation->findIndexOfVar(g_Time));
				CEventFactory* pev = CEventFactory::instance();
				if (!m_psimulation->addRunTimeEvent(pev->createCallbackEvent(pINumCatHostCallBack,vecInds)))
					{
					SYMERRORLITE("Unable to create run time feedback on progress",errWarning);
					}

				// run
				if (m_psimulation->runSimulation(m_pINumCatDataServicesCB))
							{
							m_essState=runCompleted;
							(*pvbResult)=VB_TRUE;
							}
							else
							{
							m_essState=modelError;
							(*pvbResult)=VB_FALSE;
							}
				}


	}
	catch(...) // last line of defence - C++ exceptions no further
	{
		(*pvbResult)=VB_FALSE; 
		m_essState=modelError;
		SYMERRORLITE("Unexpected exception fielded in Numerical Catalyst",errInternal);
		ATLTRACE("<Error#> unexpected exception fielded in CSymlix::RunModel");
		return E_FAIL;
	}


	return S_OK;
}


///////////////////////////////////////////////////////////
// Function name	: CSymlix::get_ModelStatus
// Description	    : Return model state
// Return type		: STDMETHODIMP 
// Argument         : enumNumCatStatus *pVal
///////////////////////////////////////////////////////////
STDMETHODIMP CSymlix::get_ModelStatus(enumNumCatStatus *pVal)
{
	CCritCheck cc(m_csModelRunningState); // so doesn't change

	(*pVal)=m_essState; 
	return S_OK;
}


///////////////////////////////////////////////////////////
// Function name	: CSymlix::get_VariableNames
// Description	    : Get array of variables - in order
// Return type		: STDMETHODIMP 
// Argument         : /*[out,retval]*/ SAFEARRAY **ppsaVars
///////////////////////////////////////////////////////////
STDMETHODIMP CSymlix::get_VariableNames(/*[out,retval]*/ SAFEARRAY **ppsaVars)
{

	try
	{
		vector<string> vecVars;

		long iStart=0;
		long iEnd;

		switch(m_essState) // only certain states can do this
		{
		case modelLoaded:
		case runInProgress:
		case runCompleted:
			// carry on
			break;
		default:
			*ppsaVars= SafeArrayCreateVector(VT_BSTR,0,0);
			return S_FALSE;
		}

		if (!m_psimulation)
				{
				*ppsaVars= SafeArrayCreateVector(VT_BSTR,0,0);
				return S_FALSE;
				}

		if (!m_psimulation->getCopyVariableList(vecVars))
				{
				*ppsaVars= SafeArrayCreateVector(VT_BSTR,0,0);
				return S_FALSE;
				}

		if (vecVars.size()==0)
				{
				*ppsaVars= SafeArrayCreateVector(VT_BSTR,0,0);
				return S_OK;
				}

		iEnd = vecVars.size();


		UINT iElems = iEnd-iStart;


		*ppsaVars= SafeArrayCreateVector(VT_BSTR,iStart,iElems);

		BSTR* prgn =0;

		HRESULT hr = SafeArrayAccessData(*ppsaVars,(void**)&prgn);

		if (FAILED(hr))
			return hr;

		USES_CONVERSION;


		for(UINT i=0;i<iElems;i++)
			{
			prgn[i] = SysAllocString( A2OLE( (vecVars[i].c_str())));
			}
	
	
	}
	catch(...) // to stop any leaking C++ exceptions
	{
		SafeArrayUnaccessData(*ppsaVars);
		return E_FAIL;
	}
	
	SafeArrayUnaccessData(*ppsaVars);


	return S_OK;
}


///////////////////////////////////////////////////////////
// Function name	: CSymlix::get_CurrentModelValues
// Description	    : 
// Return type		: STDMETHODIMP 
// Argument         : /*[out,retval]*/ SAFEARRAY **ppsaVals
///////////////////////////////////////////////////////////
STDMETHODIMP CSymlix::get_CurrentModelValues(/*[out,retval]*/ SAFEARRAY **ppsaVals)
{
	long iStart=0;
	long iEnd=5;
	UINT iElems = iEnd-iStart+1;

	vector< variable > vecValues;

	if (m_psimulation)
		m_psimulation->getCurrentValues(vecValues);

	iEnd = vecValues.size();
	iElems = iEnd - iStart;

	*ppsaVals= SafeArrayCreateVector(VT_R8,iStart,iElems);

	double* prgn =0;
	HRESULT hr = SafeArrayAccessData(*ppsaVals,(void**)&prgn);

	for(UINT i=0;i<iElems;i++)
		{
//		prgn[i].vt = VT_BSTR;
		prgn[i]/*.bstrVal*/ = vecValues[i];
		}
	SafeArrayUnaccessData(*ppsaVals);


	return S_OK;
}


///////////////////////////////////////////////////////////
// Function name	: CSymlix::AddUserEvents
// Description	    : Method to allow the user to add events at the last minute
// Return type		: STDMETHODIMP 
// Argument         : /*[in]*/ SAFEARRAY **ppsaVars
// Argument         : /*[in]*/ SAFEARRAY **ppsaVals
// Argument         : /*[in]*/ SAFEARRAY **ppsaEvTypes
// Argument         : /*[out,retval]*/ VARIANT_BOOL* pvbResult
///////////////////////////////////////////////////////////
STDMETHODIMP CSymlix::AddUserEvents(/*[in]*/ SAFEARRAY **ppsaVars, /*[in]*/ SAFEARRAY **ppsaVals, /*[in]*/ SAFEARRAY **ppsaEvTypes, /*[out,retval]*/ VARIANT_BOOL* pvbResult)
{

	vector<long> vecInd;
	vector<variable> vecValue;
	vector<eUserEvents> vecEvType;
	long iLboundVars, iLboundVals, iLboundEvTypes;
	long iHboundVars, iHboundVals, iHboundEvTypes;
	long iCount;

	(*pvbResult)=VB_FALSE; 

//	bool addUserEvents( const vector<long>& vecInd, const vector<variable>& vecValue, const vector<eUserEvents>& vecEvType );
	BSTR* prgnInd =0;
	double* prgnVar =0;
	enumNumCatEvent* prgnEvType =0;

	if (m_essState!=modelLoaded)
		return S_FALSE;

	ASSERT2(m_psimulation); // should never get past m_essState test

	if (!m_psimulation) // its a serrious error
		return E_FAIL;



	HRESULT hr = SafeArrayAccessData(*ppsaVars,(void**)&prgnInd);
	
	if (FAILED(hr))
		return hr;

	if(SafeArrayGetDim(*ppsaVars) != 1)
		return E_INVALIDARG;

	hr = SafeArrayAccessData(*ppsaVals,(void**)&prgnVar);
	
	if (FAILED(hr))
		{
		SafeArrayUnaccessData(*ppsaVars);
		return hr;
		}

	if(SafeArrayGetDim(*ppsaVals) != 1)
		{
		SafeArrayUnaccessData(*ppsaVars);
		SafeArrayUnaccessData(*ppsaVals);
 		return E_INVALIDARG;
		}

	hr = SafeArrayAccessData(*ppsaEvTypes,(void**)&prgnEvType);

	if (FAILED(hr))
		{
		SafeArrayUnaccessData(*ppsaVars);
		SafeArrayUnaccessData(*ppsaVals);
 		return hr;
		}
    
	if(SafeArrayGetDim(*ppsaEvTypes) != 1)
		{
		SafeArrayUnaccessData(*ppsaVars);
		SafeArrayUnaccessData(*ppsaVals);
		SafeArrayUnaccessData(*ppsaEvTypes);
 		return E_INVALIDARG;
		}
	
	
	hr = SafeArrayGetLBound(*ppsaVars, 1, &iLboundVars);
    if(FAILED(hr))
		{
		SafeArrayUnaccessData(*ppsaVars);
		SafeArrayUnaccessData(*ppsaVals);
 		SafeArrayUnaccessData(*ppsaEvTypes);
        return hr;
		}

    hr = SafeArrayGetUBound(*ppsaVars, 1, &iHboundVars);
    if(FAILED(hr))
		{
		SafeArrayUnaccessData(*ppsaVars);
		SafeArrayUnaccessData(*ppsaVals);
 		SafeArrayUnaccessData(*ppsaEvTypes);
        return hr;
		}

	hr = SafeArrayGetLBound(*ppsaVals, 1, &iLboundVals);
	if(FAILED(hr))
		{
		SafeArrayUnaccessData(*ppsaVars);
		SafeArrayUnaccessData(*ppsaVals);
		SafeArrayUnaccessData(*ppsaEvTypes);
        return hr;
		}

    hr = SafeArrayGetUBound(*ppsaVals, 1, &iHboundVals);
 
	if(FAILED(hr))
		{
		SafeArrayUnaccessData(*ppsaVars);
		SafeArrayUnaccessData(*ppsaVals);
		SafeArrayUnaccessData(*ppsaEvTypes);
        return hr;
		}

	hr = SafeArrayGetLBound(*ppsaEvTypes, 1, &iLboundEvTypes);
	if(FAILED(hr))
		{
		SafeArrayUnaccessData(*ppsaVars);
		SafeArrayUnaccessData(*ppsaVals);
		SafeArrayUnaccessData(*ppsaEvTypes);
        return hr;
		}

    hr = SafeArrayGetUBound(*ppsaEvTypes, 1, &iHboundEvTypes);
 
	if(FAILED(hr))
		{
		SafeArrayUnaccessData(*ppsaVars);
		SafeArrayUnaccessData(*ppsaVals);
		SafeArrayUnaccessData(*ppsaEvTypes);
        return hr;
		}

	
	if ((iLboundVars==iLboundVals)&&(iLboundVals==iLboundEvTypes)&&(iHboundVars==iHboundVals)&&(iHboundVals==iHboundEvTypes)&&(iHboundVals!=-1))
		{

		for(iCount=0;iCount<=(iHboundVars-iLboundVars);iCount++)
			{
			long iFound;
			
			switch(prgnEvType[iCount])
			{
			case eventStart:
				iFound = findVariableIndex(&prgnInd[iCount]);
				if (iFound!=NOT_FOUND)
					{
					vecInd.push_back(iFound);
					vecValue.push_back(prgnVar[iCount]);
					vecEvType.push_back(eueStart);
					}
			break;
			case eventStopGreaterEqual:
				ATLTRACE("eventStopGreaterEqual called but not implemented yet.\n");
				SYMERRORLITE("eventStopGreaterEqual is not implemented in this version.",errWarning);
			break;
			case eventStopLessEqual:
				ATLTRACE("eventStopLessEqual called but not implemented yet.\n");
				SYMERRORLITE("eventStopLessEqual is not implemented in this version.",errWarning);
			break;
			default:
				ATLTRACE("Unknown event called but not implemented yet.\n");
				SYMERRORLITE("Unknown event called but not implemented yet.",errWarning);
				break;
			}
			
			}
		
		if (m_psimulation->addUserEvents(vecInd,vecValue,vecEvType))
					(*pvbResult)=VB_TRUE;
					else
					(*pvbResult)=VB_FALSE;

		}
		else
		(*pvbResult)=VB_FALSE; 


	SafeArrayUnaccessData(*ppsaVars);
	SafeArrayUnaccessData(*ppsaVals);
	SafeArrayUnaccessData(*ppsaEvTypes);

		
	return S_OK;

}

///////////////////////////////////////////////////////////
// Function name	: CSymlix::ClearModel
// Description	    : Empty the model. If overide selected then stop
//                    an model activity then clear.
// Return type		: STDMETHODIMP 
// Argument         : VARIANT_BOOL bEvenIfRunning
// Argument         : VARIANT_BOOL *pvbResult
///////////////////////////////////////////////////////////
STDMETHODIMP CSymlix::ClearModel(VARIANT_BOOL bEvenIfRunning, VARIANT_BOOL *pvbResult)
{
	{
	CCritCheck cc(m_csModelRunningState); // must be in local scope or potential lock on thread exit

	if ((!bEvenIfRunning)&&(m_bBkgrndSolverRun))
			{
			(*pvbResult)=VB_FALSE;
			return S_FALSE; // as can't override ongoing solver
			}
	}
	
	killThreads(); // hence state should no longer be 'runInProgress'
	
	switch(m_essState)
	{
	case runCompleted:
	case modelError:
		(*pvbResult) = VB_TRUE;
		ASSERT2(m_psimulation); // must exist if in these states
		delete m_psimulation;
		m_psimulation = NULL;
		m_essState = blank;
		break;
	case blank:
		(*pvbResult) = VB_TRUE; // as model hasn't been loaded
		break;
	default:
		(*pvbResult) = VB_FALSE;
		ATLTRACE("CSymlix::ClearModel called when Symlix in unexpected state");
		return E_FAIL; // bad error
		break;

	}

	return S_OK;
}


///////////////////////////////////////////////////////////
// Function name	: CSymlix::ResetModel
// Description	    : Reset model to start state - but don't reload or
//                    repeat checks.
// Return type		: STDMETHODIMP 
// Argument         : VARIANT_BOOL bEvenIfRunning
// Argument         : VARIANT_BOOL *pvbResult
///////////////////////////////////////////////////////////
STDMETHODIMP CSymlix::ResetModel(VARIANT_BOOL bEvenIfRunning, VARIANT_BOOL *pvbResult)
{

	{
	CCritCheck cc(m_csModelRunningState); // must be in local scope or potential lock on thread exit

	if ((!bEvenIfRunning)&&(m_bBkgrndSolverRun))
			{
			(*pvbResult)=VB_FALSE;
			return S_FALSE; // as can't override ongoing solver
			}
	}
	
	killThreads();
	
	switch(m_essState)
	{
	case runCompleted:
		(*pvbResult) = VB_TRUE;
		m_essState = modelLoaded;
		break;
	case modelLoaded:
		(*pvbResult) = VB_TRUE;
		break;
	case modelError:
		(*pvbResult) = VB_FALSE; // this need to be cleared or reloaded
		return S_FALSE;
		break;
	case blank:
		(*pvbResult) = VB_FALSE; // as model hasn't been loaded
		ASSERT2(!m_psimulation); // this should never happen - catch it if it does
		return S_FALSE;
	default:
		(*pvbResult) = VB_FALSE;
		ATLTRACE("CSymlix::ResetModel called when Symlix in unexpected state");
		return E_FAIL; // bad error

	}
#ifndef NDEBUG
	this->AddRef();
	ATLTRACE("Ref count at Reset model = %d\n",this->Release());
#endif
 
	return S_OK;
}


///////////////////////////////////////////////////////////
// Function name	: CSymlix::GiveVariableIndex
// Description	    : 
// Return type		: STDMETHODIMP 
// Argument         : BSTR *sVariable
// Argument         : long *piIndex
///////////////////////////////////////////////////////////
STDMETHODIMP CSymlix::GiveVariableIndex(BSTR *sVariable, long *piIndex)
{
	// TODO: Add your implementation code here

	*piIndex=-1; // Default return value
	
	switch(m_essState) // only certain states can do this
		{
		case modelLoaded:
		case runInProgress:
		case runCompleted:
			// carry on
			break;
		default:
			return S_FALSE;
		}

	try
	{

		(*piIndex) = findVariableIndex(sVariable);

		if ((*piIndex)==NOT_FOUND)
				{
				(*piIndex) = -1;
				return S_FALSE;
				}

/*		string sTerm;

		USES_CONVERSION;

		sTerm = OLE2A(*sVariable);

		if (m_psimulation)
				{
				long iRef = m_psimulation->findIndexOfVar(sTerm);
				if (iRef==NOT_FOUND)
					*piIndex=-1;
					else
					*piIndex=iRef;
				}
				else
				return S_FALSE;
*/
	}
	catch(...) // C++ exceptions must stop here
	{
		ATLTRACE("Unhandled exception sweeped before COM interface CSymlix::GiveVariableIndex");
		m_essState=modelError;
		return E_FAIL;
	}

	return S_OK;
}


/*
///////////////////////////////////////////////////////////
// Function name	: CSymlix::CheckSimulationFile
// Description	    : Static function to check for filename
//                    if pSim in right state.
// Return type		: bool 
// Argument         : string &sFileName
// Argument         : CSimulation *pSim
///////////////////////////////////////////////////////////
bool CSymlix::CheckSimulationFile(string &sFileName, CSimulation *pSim)
{
	bool bResult;

	if (!pSim)
		return false;

	bResult = pSim->setFile(sFileName);
	if (bResult)
		bResult=pSim->setUpSimulation();

	return bResult;
}
*/



///////////////////////////////////////////////////////////
// Function name	: CSymlix::killThreads
// Description	    : code here to kill of any outstanding threads
// Return type		: void 
///////////////////////////////////////////////////////////
void CSymlix::killThreads()
{
	StopModel();
		
}


///////////////////////////////////////////////////////////
// Function name	: CSymlix::StopModel
// Description	    : 
// Return type		: STDMETHODIMP 
///////////////////////////////////////////////////////////
STDMETHODIMP CSymlix::StopModel()
{

	if (m_essState!=runInProgress)
			return S_FALSE;

	try
	{
		//m_essState=runInProgress;
		if (m_psimulation->requestEndOfSimulation())
			{
			// lets wait for the simulation to end
			if (WaitForSingleObject(m_hEventEndSimThread,4000)!=WAIT_OBJECT_0)
					{
					ATLTRACE("CSymlix::StopModel Waited for end of simulation, but it took more than 4 secs");
					return E_FAIL;
					}
			ResetEvent(m_hEventEndSimThread);
			return S_OK;
			}
	}
	catch(...)
	{
		ATLTRACE("Unhandled exception sweeped before COM interface CSymlix::StopModel");
		m_essState=modelError;
		return E_FAIL;
	}


	return S_FALSE;
}


///////////////////////////////////////////////////////////
// Function name	: CSymlix::GiveErrors
// Description	    : Hands control of the Error run over to the caller
//                    releasing the copy in the singleton ErrorFactory
//                    which starts another Error run.
//                    This call must be thread safe since additions to 
//                    the error run cannot be allowed as its in progress.
// Return type		: STDMETHODIMP 
// Argument         : INumCatErrorRun *pINumCatErrorRun
///////////////////////////////////////////////////////////
STDMETHODIMP CSymlix::GiveErrors(/*[out,retval]*/INumCatErrorRun** ppINumCatErrorRun)
{

	CErrorFactory* pcef = CErrorFactory::instance();

	ASSERT2(pcef);
	if (!pcef)
		return E_FAIL;

	(*ppINumCatErrorRun) = pcef->getErrorRun();

	if (!(*ppINumCatErrorRun))
		return E_FAIL;

	return S_OK;
}


///////////////////////////////////////////////////////////
// Function name	: CSymlix::get_LicenseState
// Description	    : Return the state of the license
// Return type		: STDMETHODIMP 
// Argument         : enumLicenseState *pVal
///////////////////////////////////////////////////////////
STDMETHODIMP CSymlix::get_LicenseState(/*[out,retval]*/enumLicenseState *pVal)
{
	CCritCheck cc(m_csModelRunningState); // so doesn't change

	(*pVal)=eLicAuthUnlimited;  // for the moment - will change soon
	return S_OK;
}


///////////////////////////////////////////////////////////
// Function name	: CSymlix::findVariableIndex
// Description	    : Helper function to locate index variable for string
//                    or else return NOT_FOUND
// Return type		: long 
// Argument         : BSTR *pbstr
///////////////////////////////////////////////////////////
long CSymlix::findVariableIndex(BSTR *pbstr)
{

	long iResult=-1; // default value

	switch(m_essState) // only certain states can do this
		{
		case modelLoaded:
		case runInProgress:
		case runCompleted:
			// carry on
			break;
		default:
			return NOT_FOUND;
		}

	try
	{

		string sTerm;

		if (!(*pbstr)) // handle the BSTR = NULL case
			return NOT_FOUND;

		USES_CONVERSION;

		sTerm = OLE2A(*pbstr);

		if (m_psimulation)
				iResult = m_psimulation->findIndexOfVar(sTerm);
				else
				return NOT_FOUND;

	}
	catch(...) // C++ exceptions must stop here
	{
		ATLTRACE("Unhandled exception here %s \n",__FILE__);
		SYMERRORLITE("Unhandled exception whilst trying to find a variable",errInternal);
		m_essState=modelError;
		return NOT_FOUND;
	}

	return iResult;

}

STDMETHODIMP CSymlix::get_RunTag(BSTR *pVal)
{

	m_cbRunTag.CopyTo(pVal);

	return S_OK;
}

STDMETHODIMP CSymlix::put_RunTag(BSTR newVal)
{

	m_cbRunTag = newVal;

	try
	{
	USES_CONVERSION;
	if (m_psimulation)
		m_psimulation->setTag(OLE2A(m_cbRunTag));
	}
	catch(...)
	{
	ATLTRACE("Unhandled error %s reported by line %d",__FILE__,__LINE__);
	return E_FAIL;
	}

	return S_OK;
}

STDMETHODIMP CSymlix::get_Version(float *pVal)
{

	if (pVal == NULL)
		return E_POINTER;

	(*pVal) = 2.700F;

	return S_OK;
}

STDMETHODIMP CSymlix::get_VersionDescription(BSTR *pVal)
{
	CComBSTR cbDescription;

	cbDescription.LoadString(IDS_VERSIONDESCRIPTION);
	cbDescription.Append("\ncompiled ");
	cbDescription.Append(__DATE__);
	cbDescription.Append(" at ");
	cbDescription.Append(__TIME__);
	
	cbDescription.CopyTo(pVal);


	return S_OK;
}

