// SymlixErrorRun.cpp : Implementation of CSymlixErrorRun
#include "stdafx.h"
#include "Symlix.h"
#include "SymlixErrorRun.h"

/////////////////////////////////////////////////////////////////////////////
// CSymlixErrorRun

void CSymlixErrorRun::FinalRelease()
{
	vector< INumCatError* >::iterator it;

	ATLTRACE(_T("CSymlixErrorRun::FinalRelease() %d\n"),this);

	for (it=m_vecpISymErr.begin();it!=m_vecpISymErr.end();it++)
#ifndef NDEBUG
		{
		long iC;
		iC = (*it)->Release(); // release interest in these objects
		ATLTRACE(_T("SymlixError ref count after release = %d \n"),iC);
		}
#else
		(*it)->Release(); // release interest in these objects
#endif

	m_vecpISymErr.clear();

}


///////////////////////////////////////////////////////////
// Function name	: CSymlixErrorRun::addError
// Description	    : Take an intrest int he Error object
//                    this is the only route for errors to
//                    be recorded.
// Return type		: bool 
// Argument         : INumCatError *pIErr
///////////////////////////////////////////////////////////
bool CSymlixErrorRun::addError(INumCatError *pIErr)
{
	if (pIErr)
		{
		pIErr->AddRef();
		m_vecpISymErr.push_back(pIErr);
		}
		else
		return false;
	return true;
}

STDMETHODIMP CSymlixErrorRun::GetAllErrors(SAFEARRAY **ppErrors)
{
	// TODO: Add your implementation code here

	UINT iElems = m_vecpISymErr.size();//iEnd-iStart+1;
	*ppErrors= SafeArrayCreateVector(VT_DISPATCH,0,iElems);

	INumCatError** prgn =0;
	HRESULT hr = SafeArrayAccessData(*ppErrors,(void**)&prgn);

	vector< INumCatError* >::iterator it = m_vecpISymErr.begin();

	for(UINT i=0;i<iElems;i++)
		{
		ASSERT2(it!=m_vecpISymErr.end());// should be guarenteed by defn of iElems
		prgn[i] = (*it);
#ifndef NDEBUG
		{
		int iRefCount;
		iRefCount = prgn[i]->AddRef(); // make a claim
		ATLTRACE("Ref count for item %d is %d\n",i,iRefCount);
		}
#else
		prgn[i]->AddRef(); // make a claim
#endif
		it++;
		}
	SafeArrayUnaccessData(*ppErrors);

	return S_OK;
}

STDMETHODIMP CSymlixErrorRun::get_CountErrors(long *pVal)
{
	(*pVal) = m_vecpISymErr.size();

	return S_OK;
}
