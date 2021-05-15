// ManageExcelAddIn.cpp: implementation of the ManageExcelAddIn class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ManageExcelAddIn.h"
#include "../DispParam.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CManageExcelAddIn::CManageExcelAddIn(const char* sCmdLine)
{

	ATLTRACE("CmdLine = [%s]\n",sCmdLine);
	try
	{
	CLSID clsExcelApp;
	IDispatch* pdispExcelApp;
	HRESULT hr;

	if ((SUCCEEDED(CLSIDFromProgID(L"Excel.Application", &clsExcelApp)))&&
	   (SUCCEEDED(CoCreateInstance(clsExcelApp, NULL, CLSCTX_LOCAL_SERVER, IID_IDispatch, (void**)&pdispExcelApp)))) 
		{
			CDispWrap dw;
			CComVariant ccv;
			dw.AddArgBOOL(VB_FALSE);
			if (SUCCEEDED(dw.CallPut(pdispExcelApp,L"Visible")))
			{
				dw.AddArgStr(sCmdLine);
				if (SUCCEEDED(dw.CallGet(&ccv,pdispExcelApp,L"AddIns")))
					{
					dw.AddArgBOOL(VB_TRUE);
					hr = dw.CallPut(ccv.pdispVal,L"Installed");

					}


			}
			dw.countNamedArgs(); // just in case
			dw.Call(&ccv,pdispExcelApp,L"Quit");


		}
		else
		{
		ATLTRACE("Failed to find Excel");
		}


	}
	catch(...)
	{
		ATLTRACE("Unkown error in %s line %d\n",__FILE__,__LINE__);
	}


}

CManageExcelAddIn::~CManageExcelAddIn()
{

}
