// TestObject3.cpp : Implementation of CTestObject3
#include "stdafx.h"
#include "SymlixStore.h"
#include "TestObject3.h"

/////////////////////////////////////////////////////////////////////////////
// CTestObject3


STDMETHODIMP CTestObject3::twoPlusTwo(long *pVal)
{
	// TODO: Add your implementation code here
	(*pVal) = 42;
	return S_OK;
}

