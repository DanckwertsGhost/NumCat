// DispParam.h: interface for the CDispWrap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DISPPARAM_H__6A79A873_B2A1_403D_9808_0745F2526773__INCLUDED_)
#define AFX_DISPPARAM_H__6A79A873_B2A1_403D_9808_0745F2526773__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>

#define MAX_DISP_ARGS 10
#define DISPARG_NOFREEVARIANT 0x01
#define DISP_FREEARGS 0x02
#define DISP_NOSHOWEXCEPTIONS 0x03

#ifndef VB_FALSE // in case used in other code
#define VB_FALSE 0
#define VB_TRUE -1
#endif

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

using namespace std;

class CDispWrap  
{
public:
	CDispWrap();
	virtual ~CDispWrap();

	bool AddArgStr( string& sArg );
	bool AddArgStr( const char* sArg )
	{ string str = sArg;
	  return AddArgStr(str);}
	bool AddArgStr( BSTR* pbstr );
	bool AddArgStr( const CComBSTR& cb );
	bool AddArgDbl( double d );
	bool AddArgBOOL( BOOL b );
	bool AddArgLong( long i );
	bool AddArgStrLong( string sArg, long iNum );
	DISPPARAMS& getDispParams();
	void reset(){ ClearAllArgs(); }
	int countArgs(){ return m_iArgCount; }
	void ClearAllArgs();
	int countNamedArgs(){ return m_iNamedArgCount; }
	HRESULT CallGet( VARIANT *pvResult, IDispatch *pDisp, LPOLESTR ptName)
	{
		 return WrapCall(DISPATCH_PROPERTYGET, pvResult, pDisp, ptName);
	}
	HRESULT CallPut( VARIANT *pvInput, IDispatch *pDisp, LPOLESTR ptName)
	{
		 return WrapCall(DISPATCH_PROPERTYPUT, pvInput, pDisp, ptName);
	}
	HRESULT CallPut( double d, IDispatch *pDisp, LPOLESTR ptName)
	{
		AddArgDbl(d);
		return CallPut(pDisp, ptName);
	}
	HRESULT CallPut( IDispatch *pDisp, LPOLESTR ptName)
	{
		 VARIANTARG vta;
		 return WrapCall(DISPATCH_PROPERTYPUT, &vta, pDisp, ptName);
	}
	HRESULT CallPut( long i, IDispatch *pDisp, LPOLESTR ptName)
	{
		AddArgLong(i);
		return CallPut(pDisp, ptName);
	}
	HRESULT CallPut( char* s, IDispatch *pDisp, LPOLESTR ptName)
	{
		AddArgStr(s);
		return CallPut(pDisp, ptName);
	}
	HRESULT CallPut( string& str, IDispatch *pDisp, LPOLESTR ptName)
	{
		AddArgStr(str);
		return CallPut(pDisp, ptName);
	}
	HRESULT Call( VARIANT *pvResult, IDispatch *pDisp, LPOLESTR ptName)
	{
		 return WrapCall(DISPATCH_METHOD, pvResult, pDisp, ptName);
	}
	HRESULT CallPutRef( VARIANT *pvResult, IDispatch *pDisp, LPOLESTR ptName)
	{
		 return WrapCall(DISPATCH_PROPERTYPUTREF, pvResult, pDisp, ptName);
	}
	
	static void ClearVariant(VARIANTARG *pvarg);
	static void ReleaseVariant(VARIANTARG *pvarg);

protected:
	HRESULT WrapCall(int autoType, VARIANT *pvResult, IDispatch *pDisp, LPOLESTR ptName, bool bClearArrays = true );




	DISPPARAMS m_params;
	int		   m_iArgCount;
	int		   m_iNamedArgCount;
	VARIANTARG m_aVargs[MAX_DISP_ARGS];
//	LPOLESTR	m_alpszArgNames[MAX_DISP_ARGS + 1];	// used to hold the argnames for GetIDs
	WORD		m_awFlags[MAX_DISP_ARGS];
	DISPID		m_aDispIds[MAX_DISP_ARGS + 1];		// one extra for the member name


};

#endif // !defined(AFX_DISPPARAM_H__6A79A873_B2A1_403D_9808_0745F2526773__INCLUDED_)
