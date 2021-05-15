// EvProgFeedback.cpp: implementation of the CEvProgFeedback class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EvProgFeedback.h"
#include "symlix/ErrorFactory.h"
#include "global.h"
#include <process.h>




//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEvProgFeedback::CEvProgFeedback(vector<long>& vecInds,INumCatHostCallBack* pINumCatHostCallBack):m_pINumCatHostCallBack(NULL),m_bFireInds(true),m_vb(VB_FALSE),m_bReleased(false)
{	
	UINT i;
	m_eState = cevInitiated; // since its either ready to go or has an error
	m_vecInds = vecInds;

	if (pINumCatHostCallBack)
		{
		m_pINumCatHostCallBack = pINumCatHostCallBack;
		m_pINumCatHostCallBack->AddRef();
		}

	_ftime(&m_tLast);


// setup variable safe array
	m_iStart=0;
	m_iEnd=vecInds.size();

	m_iElems = m_iEnd - m_iStart;

	m_psaVals= SafeArrayCreateVector(VT_R8,m_iStart,m_iElems);

	double* prgn =0;
	HRESULT hr = SafeArrayAccessData(m_psaVals,(void**)&prgn);

	if (SUCCEEDED(hr))
		{
		for(i=0;i<m_iElems;i++)
			{
			prgn[i] = NOT_DEFINED;
			}
		SafeArrayUnaccessData(m_psaVals);
		}
		else
		{
		SYMERRORLITE("Unable to allocate memory for a key array.",errSystem);
		m_eState = cevError;
		}

// send signal of indexes
	if (m_eState!=cevError)
	{

	m_psaInds = SafeArrayCreateVector(VT_I4,m_iStart,m_iElems);
	long* prgnl =0;
	hr = SafeArrayAccessData(m_psaInds,(void**)&prgnl);

	if (SUCCEEDED(hr))
		{
		for(i=0;i<m_iElems;i++)
			{
			prgnl[i] = vecInds[i];
			}
		SafeArrayUnaccessData(m_psaInds);
		}
		else
		{
		SYMERRORLITE("Unable to allocate memory for a key array.",errSystem);
		m_eState = cevError;
		}

	}

}

CEvProgFeedback::~CEvProgFeedback()
{
	if (!m_bReleased) // as life of this event could end earlier than the component
		finalRelease();
	
	ATLASSERT(m_psaVals==NULL);
	ATLASSERT(m_psaInds==NULL);
	ATLASSERT(m_pINumCatHostCallBack==NULL);
}


///////////////////////////////////////////////////////////
// Function name	: CEvProgFeedback::reset
// Description	    : 
// Return type		: void 
///////////////////////////////////////////////////////////
void CEvProgFeedback::reset()
{
	_ftime(&m_tLast);
	m_bFireInds = true; // so only happens once a run

}


///////////////////////////////////////////////////////////
// Function name	: CEvProgFeedback::finalRelease
// Description	    : Clear up all COM objects and the end of
//                    COM services is about to happen.
// Return type		: void 
///////////////////////////////////////////////////////////
void CEvProgFeedback::finalRelease()
{

	if (!m_bReleased)
	{
		
		HRESULT hr = SafeArrayDestroy(m_psaVals);

		if (FAILED(hr))
				{
				if (hr==DISP_E_ARRAYISLOCKED)
						{
						Sleep(1500); // may as well try again, perhaps its been released
						hr = SafeArrayDestroy(m_psaVals);
						if (hr==DISP_E_ARRAYISLOCKED)
							{
							SYMERRORLITE("Some data was locked when the program tried to end. Report this error.",errInternal);
							}
							else
							if (FAILED(hr))
							{
							SYMERRORLITE("Some data was locked then undefined when the program tried to tidy it up. Report this error.",errInternal);
							}
						}
						else
						{
						SYMERRORLITE("Some data was undefined when the program tried to tidy it up. Report this error.",errInternal);
						}
				}
		m_psaVals = NULL;


		hr = SafeArrayDestroy(m_psaInds);

		if (FAILED(hr))
				{
				if (hr==DISP_E_ARRAYISLOCKED)
						{
						Sleep(1500); // may as well try again, perhaps its been released
						hr = SafeArrayDestroy(m_psaInds);
						if (hr==DISP_E_ARRAYISLOCKED)
							{
							SYMERRORLITE("Some data was locked when the program tried to end. Report this error.",errInternal);
							}
							else
							if (FAILED(hr))
							{
							SYMERRORLITE("Some data was locked then undefined when the program tried to tidy it up. Report this error.",errInternal);
							}
						}
						else
						{
						SYMERRORLITE("Some data was undefined when the program tried to tidy it up. Report this error.",errInternal);
						}
				}
		m_psaInds = NULL;



		if (m_pINumCatHostCallBack)
			{
			m_pINumCatHostCallBack->Release();
			m_pINumCatHostCallBack = NULL;
			}
	}
	m_bReleased=true;
	m_eState = cevUninitiated;
}


///////////////////////////////////////////////////////////
// Function name	: CEvProgFeedback::trigger
// Description	    : 
// Return type		: eEventSignal 
// Argument         : vector<variable>* pvecVars
// Argument         : vector<variable>* pvecVarsLast
///////////////////////////////////////////////////////////
eEventSignal CEvProgFeedback::trigger(vector<variable>* pvecVars, vector<variable>* pvecVarsLast)
{
	HRESULT hr;


//	return ceesNoTrig; // temporary to track down error


	_ftime(&m_tNow);

	if (m_bFireInds)
		{
		m_bFireInds = false; // so only happens once a run
		if ((m_pINumCatHostCallBack)&&(m_psaInds))
			{
			SAFEARRAY* pSAInds=NULL;

			hr = SafeArrayCopy(m_psaInds,&pSAInds);
#ifndef NDEBUG
			if (hr==E_INVALIDARG)
				ATLTRACE("hr = E_INVALIDARG\n");
#endif
			if (SUCCEEDED(hr))
				hr = m_pINumCatHostCallBack->ToUpdate(&pSAInds,&m_vb); // ppSAInds gets destroyed in function

			if ((FAILED(hr))||(m_vb==VB_FALSE))
					{
					m_sError = "Call to update simulation data failed."; // if use SYMERROR here could over load error handling
					m_eState= cevError;
					return ceesNoTrig;
					}	
			}
		}
		


	if ((!m_pINumCatHostCallBack)||(m_eState!=cevInitiated))
		return ceesNoTrig;

	if ((m_tNow.time - m_tLast.time)>1)
		{
		double* prgn =0;
		hr = SafeArrayAccessData(m_psaVals,(void**)&prgn);

		if (SUCCEEDED(hr))
			{
			ATLASSERT(m_iElems==m_vecInds.size());
			SAFEARRAY* pSAVals=NULL;

			m_cit=m_vecInds.begin();
			for(UINT i=0;(i<m_iElems)&&(m_cit!=m_vecInds.end());i++,m_cit++)
				{
				ATLASSERT(*m_cit<pvecVars->size()); // or else things are going to get unpleasant. This should be ensured in the prog, but to catch dev mistakes
				prgn[i] = (*pvecVars)[*m_cit];
				}
			SafeArrayUnaccessData(m_psaVals);

			hr = SafeArrayCopy(m_psaVals,&pSAVals);

			if (SUCCEEDED(hr))
					hr = m_pINumCatHostCallBack->Update(&pSAVals,&m_vb); // ppSAVals gets destroyed by call

			if ((FAILED(hr))||(m_vb==VB_FALSE))
					{
					m_sError = "Call to update simulation data failed."; // if use SYMERROR here could over load error handling
					m_eState= cevError;
					}
			}
			
		}
		else
		return ceesNoTrig;

	return ceesTrig;
}


///////////////////////////////////////////////////////////
// Function name	: CEvProgFeedback::simulationEnd
// Description	    : 
// Return type		: void 
///////////////////////////////////////////////////////////
void CEvProgFeedback::simulationEnd()
{

// nothing yet

}