// CNumCatLocalValues.cpp : Implementation of CCNumCatLocalValues
#include "stdafx.h"
#include "Symlix.h"
#include "CNumCatLocalValues.h"

/////////////////////////////////////////////////////////////////////////////
// CCNumCatLocalValues

STDMETHODIMP CCNumCatLocalValues::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_INumCatLocalValues
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}
