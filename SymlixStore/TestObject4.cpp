// TestObject4.cpp : Implementation of CTestObject4
#include "stdafx.h"
#include "SymlixStore.h"
#include "TestObject4.h"

/////////////////////////////////////////////////////////////////////////////
// CTestObject4

STDMETHODIMP CTestObject4::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITestObject4
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CTestObject4::twoPlusTwo(long *pVal)
{
	// TODO: Add your implementation code here
	(*pVal) = 56;
	return S_OK;
}
