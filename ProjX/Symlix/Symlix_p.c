/* this ALWAYS GENERATED file contains the proxy stub code */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed May 16 12:24:04 2012
 */
/* Compiler settings for C:\Inetpub\ftproot\cpp_new\ProjX\Symlix\Symlix.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 440
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif // __RPCPROXY_H_VERSION__


#include "Symlix.h"

#define TYPE_FORMAT_STRING_SIZE   1121                              
#define PROC_FORMAT_STRING_SIZE   879                               

typedef struct _MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } MIDL_TYPE_FORMAT_STRING;

typedef struct _MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } MIDL_PROC_FORMAT_STRING;


extern const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString;
extern const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString;


/* Standard interface: __MIDL_itf_Symlix_0000, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IDispatch, ver. 0.0,
   GUID={0x00020400,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: INumCatHostCallBack, ver. 0.0,
   GUID={0xE8872FE4,0x948A,0x4a6b,{0x94,0xBD,0x5C,0xCC,0x19,0x90,0xD4,0x69}} */


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO INumCatHostCallBack_ServerInfo;

#pragma code_seg(".orpc")
static const unsigned short INumCatHostCallBack_FormatStringOffsetTable[] = 
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0,
    28,
    62,
    96
    };

static const MIDL_SERVER_INFO INumCatHostCallBack_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &INumCatHostCallBack_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO INumCatHostCallBack_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &INumCatHostCallBack_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };

CINTERFACE_PROXY_VTABLE(11) _INumCatHostCallBackProxyVtbl = 
{
    &INumCatHostCallBack_ProxyInfo,
    &IID_INumCatHostCallBack,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *)-1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *)-1 /* INumCatHostCallBack::TimeSignal */ ,
    (void *)-1 /* INumCatHostCallBack::Update */ ,
    (void *)-1 /* INumCatHostCallBack::ToUpdate */ ,
    (void *)-1 /* INumCatHostCallBack::ExpectEnd */
};


static const PRPC_STUB_FUNCTION INumCatHostCallBack_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _INumCatHostCallBackStubVtbl =
{
    &IID_INumCatHostCallBack,
    &INumCatHostCallBack_ServerInfo,
    11,
    &INumCatHostCallBack_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: INumCatError, ver. 0.0,
   GUID={0x48FB2B27,0xE7C7,0x40D3,{0xB3,0xC7,0x4E,0xA8,0x0F,0x35,0x18,0x10}} */


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO INumCatError_ServerInfo;

#pragma code_seg(".orpc")
static const unsigned short INumCatError_FormatStringOffsetTable[] = 
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    124,
    152,
    180,
    208,
    236,
    264,
    292
    };

static const MIDL_SERVER_INFO INumCatError_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &INumCatError_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO INumCatError_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &INumCatError_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };

CINTERFACE_PROXY_VTABLE(14) _INumCatErrorProxyVtbl = 
{
    &INumCatError_ProxyInfo,
    &IID_INumCatError,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *)-1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *)-1 /* INumCatError::get_Description */ ,
    (void *)-1 /* INumCatError::get_StreamName */ ,
    (void *)-1 /* INumCatError::get_Line */ ,
    (void *)-1 /* INumCatError::get_ErrCode */ ,
    (void *)-1 /* INumCatError::get_DevSupportDescription */ ,
    (void *)-1 /* INumCatError::get_XPosition */ ,
    (void *)-1 /* INumCatError::get_HelpRef */
};


static const PRPC_STUB_FUNCTION INumCatError_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _INumCatErrorStubVtbl =
{
    &IID_INumCatError,
    &INumCatError_ServerInfo,
    14,
    &INumCatError_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: INumCatErrorRun, ver. 0.0,
   GUID={0x6B56A92A,0xA885,0x4083,{0xAB,0xAF,0x4E,0x8D,0xF2,0xF9,0x02,0x2B}} */


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO INumCatErrorRun_ServerInfo;

#pragma code_seg(".orpc")
static const unsigned short INumCatErrorRun_FormatStringOffsetTable[] = 
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    320,
    348
    };

static const MIDL_SERVER_INFO INumCatErrorRun_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &INumCatErrorRun_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO INumCatErrorRun_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &INumCatErrorRun_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };

CINTERFACE_PROXY_VTABLE(9) _INumCatErrorRunProxyVtbl = 
{
    &INumCatErrorRun_ProxyInfo,
    &IID_INumCatErrorRun,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *)-1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *)-1 /* INumCatErrorRun::GetAllErrors */ ,
    (void *)-1 /* INumCatErrorRun::get_CountErrors */
};


static const PRPC_STUB_FUNCTION INumCatErrorRun_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _INumCatErrorRunStubVtbl =
{
    &IID_INumCatErrorRun,
    &INumCatErrorRun_ServerInfo,
    9,
    &INumCatErrorRun_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: INumCat, ver. 0.0,
   GUID={0x2F146DBD,0x50AF,0x4A26,{0x99,0xD7,0x2C,0x44,0x65,0x83,0x55,0xE0}} */


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO INumCat_ServerInfo;

#pragma code_seg(".orpc")
extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[2];

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    __MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x20000, /* Ndr library version */
    0,
    0x50100a4, /* MIDL Version 5.1.164 */
    0,
    UserMarshalRoutines,
    0,  /* notify & notify_flag routine table */
    1,  /* Flags */
    0,  /* Reserved3 */
    0,  /* Reserved4 */
    0   /* Reserved5 */
    };

static const unsigned short INumCat_FormatStringOffsetTable[] = 
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    376,
    416,
    456,
    484,
    518,
    552,
    580,
    608,
    642,
    664,
    692,
    720,
    766,
    794,
    822,
    850
    };

static const MIDL_SERVER_INFO INumCat_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &INumCat_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO INumCat_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &INumCat_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };

CINTERFACE_PROXY_VTABLE(23) _INumCatProxyVtbl = 
{
    &INumCat_ProxyInfo,
    &IID_INumCat,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *)-1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *)-1 /* INumCat::LoadModel */ ,
    (void *)-1 /* INumCat::RunModel */ ,
    (void *)-1 /* INumCat::get_ModelStatus */ ,
    (void *)-1 /* INumCat::ClearModel */ ,
    (void *)-1 /* INumCat::ResetModel */ ,
    (void *)-1 /* INumCat::get_VariableNames */ ,
    (void *)-1 /* INumCat::get_CurrentModelValues */ ,
    (void *)-1 /* INumCat::GiveVariableIndex */ ,
    (void *)-1 /* INumCat::StopModel */ ,
    (void *)-1 /* INumCat::GiveErrors */ ,
    (void *)-1 /* INumCat::get_LicenseState */ ,
    (void *)-1 /* INumCat::AddUserEvents */ ,
    (void *)-1 /* INumCat::get_RunTag */ ,
    (void *)-1 /* INumCat::put_RunTag */ ,
    (void *)-1 /* INumCat::get_Version */ ,
    (void *)-1 /* INumCat::get_VersionDescription */
};


static const PRPC_STUB_FUNCTION INumCat_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _INumCatStubVtbl =
{
    &IID_INumCat,
    &INumCat_ServerInfo,
    23,
    &INumCat_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};

#pragma data_seg(".rdata")

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[2] = 
        {
            
            {
            LPSAFEARRAY_UserSize
            ,LPSAFEARRAY_UserMarshal
            ,LPSAFEARRAY_UserUnmarshal
            ,LPSAFEARRAY_UserFree
            },
            {
            BSTR_UserSize
            ,BSTR_UserMarshal
            ,BSTR_UserUnmarshal
            ,BSTR_UserFree
            }

        };


#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT40_OR_LATER)
#error You need a Windows NT 4.0 or later to run this stub because it uses these features:
#error   -Oif or -Oicf, [wire_marshal] or [user_marshal] attribute, more than 32 methods in the interface.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will die there with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure TimeSignal */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x7 ),	/* 7 */
#ifndef _ALPHA_
/*  8 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 10 */	NdrFcShort( 0x0 ),	/* 0 */
/* 12 */	NdrFcShort( 0x10 ),	/* 16 */
/* 14 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter piTime */

/* 16 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 18 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 20 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 22 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 24 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 26 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Update */

/* 28 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 30 */	NdrFcLong( 0x0 ),	/* 0 */
/* 34 */	NdrFcShort( 0x8 ),	/* 8 */
#ifndef _ALPHA_
/* 36 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 38 */	NdrFcShort( 0x0 ),	/* 0 */
/* 40 */	NdrFcShort( 0xe ),	/* 14 */
/* 42 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter ppsaVals */

/* 44 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
#ifndef _ALPHA_
/* 46 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 48 */	NdrFcShort( 0x3c4 ),	/* Type Offset=964 */

	/* Parameter pvb */

/* 50 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 52 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 54 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 56 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 58 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 60 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ToUpdate */

/* 62 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 64 */	NdrFcLong( 0x0 ),	/* 0 */
/* 68 */	NdrFcShort( 0x9 ),	/* 9 */
#ifndef _ALPHA_
/* 70 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 72 */	NdrFcShort( 0x0 ),	/* 0 */
/* 74 */	NdrFcShort( 0xe ),	/* 14 */
/* 76 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter ppsaInds */

/* 78 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
#ifndef _ALPHA_
/* 80 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 82 */	NdrFcShort( 0x3c4 ),	/* Type Offset=964 */

	/* Parameter pvb */

/* 84 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 86 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 88 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 90 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 92 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 94 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ExpectEnd */

/* 96 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 98 */	NdrFcLong( 0x0 ),	/* 0 */
/* 102 */	NdrFcShort( 0xa ),	/* 10 */
#ifndef _ALPHA_
/* 104 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 106 */	NdrFcShort( 0x0 ),	/* 0 */
/* 108 */	NdrFcShort( 0x18 ),	/* 24 */
/* 110 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pdEnd */

/* 112 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 114 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 116 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 118 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 120 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 122 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Description */

/* 124 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 126 */	NdrFcLong( 0x0 ),	/* 0 */
/* 130 */	NdrFcShort( 0x7 ),	/* 7 */
#ifndef _ALPHA_
/* 132 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 134 */	NdrFcShort( 0x0 ),	/* 0 */
/* 136 */	NdrFcShort( 0x8 ),	/* 8 */
/* 138 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 140 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 142 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 144 */	NdrFcShort( 0x3de ),	/* Type Offset=990 */

	/* Return value */

/* 146 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 148 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 150 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_StreamName */

/* 152 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 154 */	NdrFcLong( 0x0 ),	/* 0 */
/* 158 */	NdrFcShort( 0x8 ),	/* 8 */
#ifndef _ALPHA_
/* 160 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 162 */	NdrFcShort( 0x0 ),	/* 0 */
/* 164 */	NdrFcShort( 0x8 ),	/* 8 */
/* 166 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 168 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 170 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 172 */	NdrFcShort( 0x3de ),	/* Type Offset=990 */

	/* Return value */

/* 174 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 176 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 178 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Line */

/* 180 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 182 */	NdrFcLong( 0x0 ),	/* 0 */
/* 186 */	NdrFcShort( 0x9 ),	/* 9 */
#ifndef _ALPHA_
/* 188 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 190 */	NdrFcShort( 0x0 ),	/* 0 */
/* 192 */	NdrFcShort( 0x10 ),	/* 16 */
/* 194 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 196 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 198 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 200 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 202 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 204 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 206 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_ErrCode */

/* 208 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 210 */	NdrFcLong( 0x0 ),	/* 0 */
/* 214 */	NdrFcShort( 0xa ),	/* 10 */
#ifndef _ALPHA_
/* 216 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 218 */	NdrFcShort( 0x0 ),	/* 0 */
/* 220 */	NdrFcShort( 0xe ),	/* 14 */
/* 222 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 224 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
#ifndef _ALPHA_
/* 226 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 228 */	NdrFcShort( 0x3e8 ),	/* Type Offset=1000 */

	/* Return value */

/* 230 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 232 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 234 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_DevSupportDescription */

/* 236 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 238 */	NdrFcLong( 0x0 ),	/* 0 */
/* 242 */	NdrFcShort( 0xb ),	/* 11 */
#ifndef _ALPHA_
/* 244 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 246 */	NdrFcShort( 0x0 ),	/* 0 */
/* 248 */	NdrFcShort( 0x8 ),	/* 8 */
/* 250 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 252 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 254 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 256 */	NdrFcShort( 0x3de ),	/* Type Offset=990 */

	/* Return value */

/* 258 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 260 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 262 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_XPosition */

/* 264 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 266 */	NdrFcLong( 0x0 ),	/* 0 */
/* 270 */	NdrFcShort( 0xc ),	/* 12 */
#ifndef _ALPHA_
/* 272 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 274 */	NdrFcShort( 0x0 ),	/* 0 */
/* 276 */	NdrFcShort( 0x10 ),	/* 16 */
/* 278 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 280 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 282 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 284 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 286 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 288 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 290 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_HelpRef */

/* 292 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 294 */	NdrFcLong( 0x0 ),	/* 0 */
/* 298 */	NdrFcShort( 0xd ),	/* 13 */
#ifndef _ALPHA_
/* 300 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 302 */	NdrFcShort( 0x0 ),	/* 0 */
/* 304 */	NdrFcShort( 0x10 ),	/* 16 */
/* 306 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 308 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 310 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 312 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 314 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 316 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 318 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetAllErrors */

/* 320 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 322 */	NdrFcLong( 0x0 ),	/* 0 */
/* 326 */	NdrFcShort( 0x7 ),	/* 7 */
#ifndef _ALPHA_
/* 328 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 330 */	NdrFcShort( 0x0 ),	/* 0 */
/* 332 */	NdrFcShort( 0x8 ),	/* 8 */
/* 334 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter ppErrors */

/* 336 */	NdrFcShort( 0x113 ),	/* Flags:  must size, must free, out, simple ref, */
#ifndef _ALPHA_
/* 338 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 340 */	NdrFcShort( 0x3f8 ),	/* Type Offset=1016 */

	/* Return value */

/* 342 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 344 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 346 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_CountErrors */

/* 348 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 350 */	NdrFcLong( 0x0 ),	/* 0 */
/* 354 */	NdrFcShort( 0x8 ),	/* 8 */
#ifndef _ALPHA_
/* 356 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 358 */	NdrFcShort( 0x0 ),	/* 0 */
/* 360 */	NdrFcShort( 0x10 ),	/* 16 */
/* 362 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 364 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 366 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 368 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 370 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 372 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 374 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure LoadModel */

/* 376 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 378 */	NdrFcLong( 0x0 ),	/* 0 */
/* 382 */	NdrFcShort( 0x7 ),	/* 7 */
#ifndef _ALPHA_
/* 384 */	NdrFcShort( 0x14 ),	/* x86, MIPS, PPC Stack size/offset = 20 */
#else
			NdrFcShort( 0x28 ),	/* Alpha Stack size/offset = 40 */
#endif
/* 386 */	NdrFcShort( 0x0 ),	/* 0 */
/* 388 */	NdrFcShort( 0xe ),	/* 14 */
/* 390 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x4,		/* 4 */

	/* Parameter sFileName */

/* 392 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
#ifndef _ALPHA_
/* 394 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 396 */	NdrFcShort( 0x40a ),	/* Type Offset=1034 */

	/* Parameter pIStore */

/* 398 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
#ifndef _ALPHA_
/* 400 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 402 */	NdrFcShort( 0x414 ),	/* Type Offset=1044 */

	/* Parameter pvbResult */

/* 404 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 406 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 408 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 410 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 412 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 414 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure RunModel */

/* 416 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 418 */	NdrFcLong( 0x0 ),	/* 0 */
/* 422 */	NdrFcShort( 0x8 ),	/* 8 */
#ifndef _ALPHA_
/* 424 */	NdrFcShort( 0x14 ),	/* x86, MIPS, PPC Stack size/offset = 20 */
#else
			NdrFcShort( 0x28 ),	/* Alpha Stack size/offset = 40 */
#endif
/* 426 */	NdrFcShort( 0x8 ),	/* 8 */
/* 428 */	NdrFcShort( 0xe ),	/* 14 */
/* 430 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x4,		/* 4 */

	/* Parameter hInstance */

/* 432 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 434 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 436 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pINumCatHostCallBack */

/* 438 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
#ifndef _ALPHA_
/* 440 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 442 */	NdrFcShort( 0x426 ),	/* Type Offset=1062 */

	/* Parameter pvbResult */

/* 444 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 446 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 448 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 450 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 452 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 454 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_ModelStatus */

/* 456 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 458 */	NdrFcLong( 0x0 ),	/* 0 */
/* 462 */	NdrFcShort( 0x9 ),	/* 9 */
#ifndef _ALPHA_
/* 464 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 466 */	NdrFcShort( 0x0 ),	/* 0 */
/* 468 */	NdrFcShort( 0xe ),	/* 14 */
/* 470 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 472 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
#ifndef _ALPHA_
/* 474 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 476 */	NdrFcShort( 0x3e8 ),	/* Type Offset=1000 */

	/* Return value */

/* 478 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 480 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 482 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ClearModel */

/* 484 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 486 */	NdrFcLong( 0x0 ),	/* 0 */
/* 490 */	NdrFcShort( 0xa ),	/* 10 */
#ifndef _ALPHA_
/* 492 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 494 */	NdrFcShort( 0x6 ),	/* 6 */
/* 496 */	NdrFcShort( 0xe ),	/* 14 */
/* 498 */	0x4,		/* Oi2 Flags:  has return, */
			0x3,		/* 3 */

	/* Parameter bEvenIfRunning */

/* 500 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 502 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 504 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter pvbResult */

/* 506 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 508 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 510 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 512 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 514 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 516 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ResetModel */

/* 518 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 520 */	NdrFcLong( 0x0 ),	/* 0 */
/* 524 */	NdrFcShort( 0xb ),	/* 11 */
#ifndef _ALPHA_
/* 526 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 528 */	NdrFcShort( 0x6 ),	/* 6 */
/* 530 */	NdrFcShort( 0xe ),	/* 14 */
/* 532 */	0x4,		/* Oi2 Flags:  has return, */
			0x3,		/* 3 */

	/* Parameter bEvenIfRunning */

/* 534 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 536 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 538 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter pvbResult */

/* 540 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 542 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 544 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 546 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 548 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 550 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_VariableNames */

/* 552 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 554 */	NdrFcLong( 0x0 ),	/* 0 */
/* 558 */	NdrFcShort( 0xc ),	/* 12 */
#ifndef _ALPHA_
/* 560 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 562 */	NdrFcShort( 0x0 ),	/* 0 */
/* 564 */	NdrFcShort( 0x8 ),	/* 8 */
/* 566 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter ppsaVars */

/* 568 */	NdrFcShort( 0x113 ),	/* Flags:  must size, must free, out, simple ref, */
#ifndef _ALPHA_
/* 570 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 572 */	NdrFcShort( 0x3f8 ),	/* Type Offset=1016 */

	/* Return value */

/* 574 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 576 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 578 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_CurrentModelValues */

/* 580 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 582 */	NdrFcLong( 0x0 ),	/* 0 */
/* 586 */	NdrFcShort( 0xd ),	/* 13 */
#ifndef _ALPHA_
/* 588 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 590 */	NdrFcShort( 0x0 ),	/* 0 */
/* 592 */	NdrFcShort( 0x8 ),	/* 8 */
/* 594 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter ppsaVals */

/* 596 */	NdrFcShort( 0x113 ),	/* Flags:  must size, must free, out, simple ref, */
#ifndef _ALPHA_
/* 598 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 600 */	NdrFcShort( 0x3f8 ),	/* Type Offset=1016 */

	/* Return value */

/* 602 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 604 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 606 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GiveVariableIndex */

/* 608 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 610 */	NdrFcLong( 0x0 ),	/* 0 */
/* 614 */	NdrFcShort( 0xe ),	/* 14 */
#ifndef _ALPHA_
/* 616 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 618 */	NdrFcShort( 0x0 ),	/* 0 */
/* 620 */	NdrFcShort( 0x10 ),	/* 16 */
/* 622 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter sVariable */

/* 624 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
#ifndef _ALPHA_
/* 626 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 628 */	NdrFcShort( 0x40a ),	/* Type Offset=1034 */

	/* Parameter piIndex */

/* 630 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 632 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 634 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 636 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 638 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 640 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure StopModel */

/* 642 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 644 */	NdrFcLong( 0x0 ),	/* 0 */
/* 648 */	NdrFcShort( 0xf ),	/* 15 */
#ifndef _ALPHA_
/* 650 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 652 */	NdrFcShort( 0x0 ),	/* 0 */
/* 654 */	NdrFcShort( 0x8 ),	/* 8 */
/* 656 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 658 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 660 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 662 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GiveErrors */

/* 664 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 666 */	NdrFcLong( 0x0 ),	/* 0 */
/* 670 */	NdrFcShort( 0x10 ),	/* 16 */
#ifndef _ALPHA_
/* 672 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 674 */	NdrFcShort( 0x0 ),	/* 0 */
/* 676 */	NdrFcShort( 0x8 ),	/* 8 */
/* 678 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pINumCatErrorRun */

/* 680 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
#ifndef _ALPHA_
/* 682 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 684 */	NdrFcShort( 0x438 ),	/* Type Offset=1080 */

	/* Return value */

/* 686 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 688 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 690 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_LicenseState */

/* 692 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 694 */	NdrFcLong( 0x0 ),	/* 0 */
/* 698 */	NdrFcShort( 0x11 ),	/* 17 */
#ifndef _ALPHA_
/* 700 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 702 */	NdrFcShort( 0x0 ),	/* 0 */
/* 704 */	NdrFcShort( 0xe ),	/* 14 */
/* 706 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 708 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
#ifndef _ALPHA_
/* 710 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 712 */	NdrFcShort( 0x3e8 ),	/* Type Offset=1000 */

	/* Return value */

/* 714 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 716 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 718 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AddUserEvents */

/* 720 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 722 */	NdrFcLong( 0x0 ),	/* 0 */
/* 726 */	NdrFcShort( 0x12 ),	/* 18 */
#ifndef _ALPHA_
/* 728 */	NdrFcShort( 0x18 ),	/* x86, MIPS, PPC Stack size/offset = 24 */
#else
			NdrFcShort( 0x30 ),	/* Alpha Stack size/offset = 48 */
#endif
/* 730 */	NdrFcShort( 0x0 ),	/* 0 */
/* 732 */	NdrFcShort( 0xe ),	/* 14 */
/* 734 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x5,		/* 5 */

	/* Parameter ppsaVars */

/* 736 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
#ifndef _ALPHA_
/* 738 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 740 */	NdrFcShort( 0x452 ),	/* Type Offset=1106 */

	/* Parameter ppsaVals */

/* 742 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
#ifndef _ALPHA_
/* 744 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 746 */	NdrFcShort( 0x452 ),	/* Type Offset=1106 */

	/* Parameter ppsaEvTypes */

/* 748 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
#ifndef _ALPHA_
/* 750 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 752 */	NdrFcShort( 0x452 ),	/* Type Offset=1106 */

	/* Parameter pvbResult */

/* 754 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 756 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 758 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 760 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 762 */	NdrFcShort( 0x14 ),	/* x86, MIPS, PPC Stack size/offset = 20 */
#else
			NdrFcShort( 0x28 ),	/* Alpha Stack size/offset = 40 */
#endif
/* 764 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_RunTag */

/* 766 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 768 */	NdrFcLong( 0x0 ),	/* 0 */
/* 772 */	NdrFcShort( 0x13 ),	/* 19 */
#ifndef _ALPHA_
/* 774 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 776 */	NdrFcShort( 0x0 ),	/* 0 */
/* 778 */	NdrFcShort( 0x8 ),	/* 8 */
/* 780 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 782 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 784 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 786 */	NdrFcShort( 0x3de ),	/* Type Offset=990 */

	/* Return value */

/* 788 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 790 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 792 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_RunTag */

/* 794 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 796 */	NdrFcLong( 0x0 ),	/* 0 */
/* 800 */	NdrFcShort( 0x14 ),	/* 20 */
#ifndef _ALPHA_
/* 802 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 804 */	NdrFcShort( 0x0 ),	/* 0 */
/* 806 */	NdrFcShort( 0x8 ),	/* 8 */
/* 808 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 810 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 812 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 814 */	NdrFcShort( 0x40a ),	/* Type Offset=1034 */

	/* Return value */

/* 816 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 818 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 820 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Version */

/* 822 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 824 */	NdrFcLong( 0x0 ),	/* 0 */
/* 828 */	NdrFcShort( 0x15 ),	/* 21 */
#ifndef _ALPHA_
/* 830 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 832 */	NdrFcShort( 0x0 ),	/* 0 */
/* 834 */	NdrFcShort( 0x10 ),	/* 16 */
/* 836 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 838 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 840 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 842 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Return value */

/* 844 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 846 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 848 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_VersionDescription */

/* 850 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 852 */	NdrFcLong( 0x0 ),	/* 0 */
/* 856 */	NdrFcShort( 0x16 ),	/* 22 */
#ifndef _ALPHA_
/* 858 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 860 */	NdrFcShort( 0x0 ),	/* 0 */
/* 862 */	NdrFcShort( 0x8 ),	/* 8 */
/* 864 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 866 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 868 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 870 */	NdrFcShort( 0x3de ),	/* Type Offset=990 */

	/* Return value */

/* 872 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 874 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 876 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/*  4 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/*  6 */	
			0x11, 0x0,	/* FC_RP */
/*  8 */	NdrFcShort( 0x3bc ),	/* Offset= 956 (964) */
/* 10 */	
			0x12, 0x10,	/* FC_UP */
/* 12 */	NdrFcShort( 0x2 ),	/* Offset= 2 (14) */
/* 14 */	
			0x12, 0x0,	/* FC_UP */
/* 16 */	NdrFcShort( 0x3a2 ),	/* Offset= 930 (946) */
/* 18 */	
			0x2a,		/* FC_ENCAPSULATED_UNION */
			0x49,		/* 73 */
/* 20 */	NdrFcShort( 0x18 ),	/* 24 */
/* 22 */	NdrFcShort( 0xa ),	/* 10 */
/* 24 */	NdrFcLong( 0x8 ),	/* 8 */
/* 28 */	NdrFcShort( 0x6c ),	/* Offset= 108 (136) */
/* 30 */	NdrFcLong( 0xd ),	/* 13 */
/* 34 */	NdrFcShort( 0x9e ),	/* Offset= 158 (192) */
/* 36 */	NdrFcLong( 0x9 ),	/* 9 */
/* 40 */	NdrFcShort( 0xcc ),	/* Offset= 204 (244) */
/* 42 */	NdrFcLong( 0xc ),	/* 12 */
/* 46 */	NdrFcShort( 0x292 ),	/* Offset= 658 (704) */
/* 48 */	NdrFcLong( 0x24 ),	/* 36 */
/* 52 */	NdrFcShort( 0x2ba ),	/* Offset= 698 (750) */
/* 54 */	NdrFcLong( 0x800d ),	/* 32781 */
/* 58 */	NdrFcShort( 0x2d6 ),	/* Offset= 726 (784) */
/* 60 */	NdrFcLong( 0x10 ),	/* 16 */
/* 64 */	NdrFcShort( 0x2ee ),	/* Offset= 750 (814) */
/* 66 */	NdrFcLong( 0x2 ),	/* 2 */
/* 70 */	NdrFcShort( 0x306 ),	/* Offset= 774 (844) */
/* 72 */	NdrFcLong( 0x3 ),	/* 3 */
/* 76 */	NdrFcShort( 0x31e ),	/* Offset= 798 (874) */
/* 78 */	NdrFcLong( 0x14 ),	/* 20 */
/* 82 */	NdrFcShort( 0x336 ),	/* Offset= 822 (904) */
/* 84 */	NdrFcShort( 0xffffffff ),	/* Offset= -1 (83) */
/* 86 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 88 */	NdrFcShort( 0x2 ),	/* 2 */
/* 90 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 92 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 94 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 96 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 98 */	NdrFcShort( 0x8 ),	/* 8 */
/* 100 */	NdrFcShort( 0xfffffff2 ),	/* Offset= -14 (86) */
/* 102 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 104 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 106 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 108 */	NdrFcShort( 0x4 ),	/* 4 */
/* 110 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 112 */	NdrFcShort( 0x0 ),	/* 0 */
/* 114 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 116 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 118 */	NdrFcShort( 0x4 ),	/* 4 */
/* 120 */	NdrFcShort( 0x0 ),	/* 0 */
/* 122 */	NdrFcShort( 0x1 ),	/* 1 */
/* 124 */	NdrFcShort( 0x0 ),	/* 0 */
/* 126 */	NdrFcShort( 0x0 ),	/* 0 */
/* 128 */	0x12, 0x0,	/* FC_UP */
/* 130 */	NdrFcShort( 0xffffffde ),	/* Offset= -34 (96) */
/* 132 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 134 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 136 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 138 */	NdrFcShort( 0x8 ),	/* 8 */
/* 140 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 142 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 144 */	NdrFcShort( 0x4 ),	/* 4 */
/* 146 */	NdrFcShort( 0x4 ),	/* 4 */
/* 148 */	0x11, 0x0,	/* FC_RP */
/* 150 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (106) */
/* 152 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 154 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 156 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 158 */	NdrFcLong( 0x0 ),	/* 0 */
/* 162 */	NdrFcShort( 0x0 ),	/* 0 */
/* 164 */	NdrFcShort( 0x0 ),	/* 0 */
/* 166 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 168 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 170 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 172 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 174 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 176 */	NdrFcShort( 0x0 ),	/* 0 */
/* 178 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 180 */	NdrFcShort( 0x0 ),	/* 0 */
/* 182 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 186 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 188 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (156) */
/* 190 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 192 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 194 */	NdrFcShort( 0x8 ),	/* 8 */
/* 196 */	NdrFcShort( 0x0 ),	/* 0 */
/* 198 */	NdrFcShort( 0x6 ),	/* Offset= 6 (204) */
/* 200 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 202 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 204 */	
			0x11, 0x0,	/* FC_RP */
/* 206 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (174) */
/* 208 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 210 */	NdrFcLong( 0x20400 ),	/* 132096 */
/* 214 */	NdrFcShort( 0x0 ),	/* 0 */
/* 216 */	NdrFcShort( 0x0 ),	/* 0 */
/* 218 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 220 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 222 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 224 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 226 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 228 */	NdrFcShort( 0x0 ),	/* 0 */
/* 230 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 232 */	NdrFcShort( 0x0 ),	/* 0 */
/* 234 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 238 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 240 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (208) */
/* 242 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 244 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 246 */	NdrFcShort( 0x8 ),	/* 8 */
/* 248 */	NdrFcShort( 0x0 ),	/* 0 */
/* 250 */	NdrFcShort( 0x6 ),	/* Offset= 6 (256) */
/* 252 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 254 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 256 */	
			0x11, 0x0,	/* FC_RP */
/* 258 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (226) */
/* 260 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 262 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 264 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 266 */	NdrFcShort( 0x2 ),	/* Offset= 2 (268) */
/* 268 */	NdrFcShort( 0x10 ),	/* 16 */
/* 270 */	NdrFcShort( 0x2b ),	/* 43 */
/* 272 */	NdrFcLong( 0x3 ),	/* 3 */
/* 276 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 278 */	NdrFcLong( 0x11 ),	/* 17 */
/* 282 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 284 */	NdrFcLong( 0x2 ),	/* 2 */
/* 288 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 290 */	NdrFcLong( 0x4 ),	/* 4 */
/* 294 */	NdrFcShort( 0x800a ),	/* Simple arm type: FC_FLOAT */
/* 296 */	NdrFcLong( 0x5 ),	/* 5 */
/* 300 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 302 */	NdrFcLong( 0xb ),	/* 11 */
/* 306 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 308 */	NdrFcLong( 0xa ),	/* 10 */
/* 312 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 314 */	NdrFcLong( 0x6 ),	/* 6 */
/* 318 */	NdrFcShort( 0xd6 ),	/* Offset= 214 (532) */
/* 320 */	NdrFcLong( 0x7 ),	/* 7 */
/* 324 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 326 */	NdrFcLong( 0x8 ),	/* 8 */
/* 330 */	NdrFcShort( 0xd0 ),	/* Offset= 208 (538) */
/* 332 */	NdrFcLong( 0xd ),	/* 13 */
/* 336 */	NdrFcShort( 0xffffff4c ),	/* Offset= -180 (156) */
/* 338 */	NdrFcLong( 0x9 ),	/* 9 */
/* 342 */	NdrFcShort( 0xffffff7a ),	/* Offset= -134 (208) */
/* 344 */	NdrFcLong( 0x2000 ),	/* 8192 */
/* 348 */	NdrFcShort( 0xc2 ),	/* Offset= 194 (542) */
/* 350 */	NdrFcLong( 0x24 ),	/* 36 */
/* 354 */	NdrFcShort( 0xc0 ),	/* Offset= 192 (546) */
/* 356 */	NdrFcLong( 0x4024 ),	/* 16420 */
/* 360 */	NdrFcShort( 0xba ),	/* Offset= 186 (546) */
/* 362 */	NdrFcLong( 0x4011 ),	/* 16401 */
/* 366 */	NdrFcShort( 0xe8 ),	/* Offset= 232 (598) */
/* 368 */	NdrFcLong( 0x4002 ),	/* 16386 */
/* 372 */	NdrFcShort( 0xe6 ),	/* Offset= 230 (602) */
/* 374 */	NdrFcLong( 0x4003 ),	/* 16387 */
/* 378 */	NdrFcShort( 0xe4 ),	/* Offset= 228 (606) */
/* 380 */	NdrFcLong( 0x4004 ),	/* 16388 */
/* 384 */	NdrFcShort( 0xe2 ),	/* Offset= 226 (610) */
/* 386 */	NdrFcLong( 0x4005 ),	/* 16389 */
/* 390 */	NdrFcShort( 0xe0 ),	/* Offset= 224 (614) */
/* 392 */	NdrFcLong( 0x400b ),	/* 16395 */
/* 396 */	NdrFcShort( 0xce ),	/* Offset= 206 (602) */
/* 398 */	NdrFcLong( 0x400a ),	/* 16394 */
/* 402 */	NdrFcShort( 0xcc ),	/* Offset= 204 (606) */
/* 404 */	NdrFcLong( 0x4006 ),	/* 16390 */
/* 408 */	NdrFcShort( 0xd2 ),	/* Offset= 210 (618) */
/* 410 */	NdrFcLong( 0x4007 ),	/* 16391 */
/* 414 */	NdrFcShort( 0xc8 ),	/* Offset= 200 (614) */
/* 416 */	NdrFcLong( 0x4008 ),	/* 16392 */
/* 420 */	NdrFcShort( 0xca ),	/* Offset= 202 (622) */
/* 422 */	NdrFcLong( 0x400d ),	/* 16397 */
/* 426 */	NdrFcShort( 0xc8 ),	/* Offset= 200 (626) */
/* 428 */	NdrFcLong( 0x4009 ),	/* 16393 */
/* 432 */	NdrFcShort( 0xc6 ),	/* Offset= 198 (630) */
/* 434 */	NdrFcLong( 0x6000 ),	/* 24576 */
/* 438 */	NdrFcShort( 0xc4 ),	/* Offset= 196 (634) */
/* 440 */	NdrFcLong( 0x400c ),	/* 16396 */
/* 444 */	NdrFcShort( 0xbe ),	/* Offset= 190 (634) */
/* 446 */	NdrFcLong( 0x10 ),	/* 16 */
/* 450 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 452 */	NdrFcLong( 0x12 ),	/* 18 */
/* 456 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 458 */	NdrFcLong( 0x13 ),	/* 19 */
/* 462 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 464 */	NdrFcLong( 0x16 ),	/* 22 */
/* 468 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 470 */	NdrFcLong( 0x17 ),	/* 23 */
/* 474 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 476 */	NdrFcLong( 0xe ),	/* 14 */
/* 480 */	NdrFcShort( 0x9e ),	/* Offset= 158 (638) */
/* 482 */	NdrFcLong( 0x400e ),	/* 16398 */
/* 486 */	NdrFcShort( 0xa4 ),	/* Offset= 164 (650) */
/* 488 */	NdrFcLong( 0x4010 ),	/* 16400 */
/* 492 */	NdrFcShort( 0x6a ),	/* Offset= 106 (598) */
/* 494 */	NdrFcLong( 0x4012 ),	/* 16402 */
/* 498 */	NdrFcShort( 0x68 ),	/* Offset= 104 (602) */
/* 500 */	NdrFcLong( 0x4013 ),	/* 16403 */
/* 504 */	NdrFcShort( 0x66 ),	/* Offset= 102 (606) */
/* 506 */	NdrFcLong( 0x4016 ),	/* 16406 */
/* 510 */	NdrFcShort( 0x60 ),	/* Offset= 96 (606) */
/* 512 */	NdrFcLong( 0x4017 ),	/* 16407 */
/* 516 */	NdrFcShort( 0x5a ),	/* Offset= 90 (606) */
/* 518 */	NdrFcLong( 0x0 ),	/* 0 */
/* 522 */	NdrFcShort( 0x0 ),	/* Offset= 0 (522) */
/* 524 */	NdrFcLong( 0x1 ),	/* 1 */
/* 528 */	NdrFcShort( 0x0 ),	/* Offset= 0 (528) */
/* 530 */	NdrFcShort( 0xffffffff ),	/* Offset= -1 (529) */
/* 532 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 534 */	NdrFcShort( 0x8 ),	/* 8 */
/* 536 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 538 */	
			0x12, 0x0,	/* FC_UP */
/* 540 */	NdrFcShort( 0xfffffe44 ),	/* Offset= -444 (96) */
/* 542 */	
			0x12, 0x0,	/* FC_UP */
/* 544 */	NdrFcShort( 0x192 ),	/* Offset= 402 (946) */
/* 546 */	
			0x12, 0x0,	/* FC_UP */
/* 548 */	NdrFcShort( 0x1e ),	/* Offset= 30 (578) */
/* 550 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 552 */	NdrFcLong( 0x2f ),	/* 47 */
/* 556 */	NdrFcShort( 0x0 ),	/* 0 */
/* 558 */	NdrFcShort( 0x0 ),	/* 0 */
/* 560 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 562 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 564 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 566 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 568 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 570 */	NdrFcShort( 0x1 ),	/* 1 */
/* 572 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 574 */	NdrFcShort( 0x4 ),	/* 4 */
/* 576 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 578 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 580 */	NdrFcShort( 0x10 ),	/* 16 */
/* 582 */	NdrFcShort( 0x0 ),	/* 0 */
/* 584 */	NdrFcShort( 0xa ),	/* Offset= 10 (594) */
/* 586 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 588 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 590 */	NdrFcShort( 0xffffffd8 ),	/* Offset= -40 (550) */
/* 592 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 594 */	
			0x12, 0x0,	/* FC_UP */
/* 596 */	NdrFcShort( 0xffffffe4 ),	/* Offset= -28 (568) */
/* 598 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 600 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 602 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 604 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 606 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 608 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 610 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 612 */	0xa,		/* FC_FLOAT */
			0x5c,		/* FC_PAD */
/* 614 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 616 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 618 */	
			0x12, 0x0,	/* FC_UP */
/* 620 */	NdrFcShort( 0xffffffa8 ),	/* Offset= -88 (532) */
/* 622 */	
			0x12, 0x10,	/* FC_UP */
/* 624 */	NdrFcShort( 0xffffffaa ),	/* Offset= -86 (538) */
/* 626 */	
			0x12, 0x10,	/* FC_UP */
/* 628 */	NdrFcShort( 0xfffffe28 ),	/* Offset= -472 (156) */
/* 630 */	
			0x12, 0x10,	/* FC_UP */
/* 632 */	NdrFcShort( 0xfffffe58 ),	/* Offset= -424 (208) */
/* 634 */	
			0x12, 0x10,	/* FC_UP */
/* 636 */	NdrFcShort( 0xffffffa2 ),	/* Offset= -94 (542) */
/* 638 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 640 */	NdrFcShort( 0x10 ),	/* 16 */
/* 642 */	0x6,		/* FC_SHORT */
			0x2,		/* FC_CHAR */
/* 644 */	0x2,		/* FC_CHAR */
			0x38,		/* FC_ALIGNM4 */
/* 646 */	0x8,		/* FC_LONG */
			0x39,		/* FC_ALIGNM8 */
/* 648 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 650 */	
			0x12, 0x0,	/* FC_UP */
/* 652 */	NdrFcShort( 0xfffffff2 ),	/* Offset= -14 (638) */
/* 654 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 656 */	NdrFcShort( 0x20 ),	/* 32 */
/* 658 */	NdrFcShort( 0x0 ),	/* 0 */
/* 660 */	NdrFcShort( 0x0 ),	/* Offset= 0 (660) */
/* 662 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 664 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 666 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 668 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 670 */	NdrFcShort( 0xfffffe66 ),	/* Offset= -410 (260) */
/* 672 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 674 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 676 */	NdrFcShort( 0x4 ),	/* 4 */
/* 678 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 680 */	NdrFcShort( 0x0 ),	/* 0 */
/* 682 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 684 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 686 */	NdrFcShort( 0x4 ),	/* 4 */
/* 688 */	NdrFcShort( 0x0 ),	/* 0 */
/* 690 */	NdrFcShort( 0x1 ),	/* 1 */
/* 692 */	NdrFcShort( 0x0 ),	/* 0 */
/* 694 */	NdrFcShort( 0x0 ),	/* 0 */
/* 696 */	0x12, 0x0,	/* FC_UP */
/* 698 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (654) */
/* 700 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 702 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 704 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 706 */	NdrFcShort( 0x8 ),	/* 8 */
/* 708 */	NdrFcShort( 0x0 ),	/* 0 */
/* 710 */	NdrFcShort( 0x6 ),	/* Offset= 6 (716) */
/* 712 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 714 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 716 */	
			0x11, 0x0,	/* FC_RP */
/* 718 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (674) */
/* 720 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 722 */	NdrFcShort( 0x4 ),	/* 4 */
/* 724 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 726 */	NdrFcShort( 0x0 ),	/* 0 */
/* 728 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 730 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 732 */	NdrFcShort( 0x4 ),	/* 4 */
/* 734 */	NdrFcShort( 0x0 ),	/* 0 */
/* 736 */	NdrFcShort( 0x1 ),	/* 1 */
/* 738 */	NdrFcShort( 0x0 ),	/* 0 */
/* 740 */	NdrFcShort( 0x0 ),	/* 0 */
/* 742 */	0x12, 0x0,	/* FC_UP */
/* 744 */	NdrFcShort( 0xffffff5a ),	/* Offset= -166 (578) */
/* 746 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 748 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 750 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 752 */	NdrFcShort( 0x8 ),	/* 8 */
/* 754 */	NdrFcShort( 0x0 ),	/* 0 */
/* 756 */	NdrFcShort( 0x6 ),	/* Offset= 6 (762) */
/* 758 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 760 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 762 */	
			0x11, 0x0,	/* FC_RP */
/* 764 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (720) */
/* 766 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 768 */	NdrFcShort( 0x8 ),	/* 8 */
/* 770 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 772 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 774 */	NdrFcShort( 0x10 ),	/* 16 */
/* 776 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 778 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 780 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffff1 ),	/* Offset= -15 (766) */
			0x5b,		/* FC_END */
/* 784 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 786 */	NdrFcShort( 0x18 ),	/* 24 */
/* 788 */	NdrFcShort( 0x0 ),	/* 0 */
/* 790 */	NdrFcShort( 0xa ),	/* Offset= 10 (800) */
/* 792 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 794 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 796 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (772) */
/* 798 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 800 */	
			0x11, 0x0,	/* FC_RP */
/* 802 */	NdrFcShort( 0xfffffd8c ),	/* Offset= -628 (174) */
/* 804 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 806 */	NdrFcShort( 0x1 ),	/* 1 */
/* 808 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 810 */	NdrFcShort( 0x0 ),	/* 0 */
/* 812 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 814 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 816 */	NdrFcShort( 0x8 ),	/* 8 */
/* 818 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 820 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 822 */	NdrFcShort( 0x4 ),	/* 4 */
/* 824 */	NdrFcShort( 0x4 ),	/* 4 */
/* 826 */	0x12, 0x0,	/* FC_UP */
/* 828 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (804) */
/* 830 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 832 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 834 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 836 */	NdrFcShort( 0x2 ),	/* 2 */
/* 838 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 840 */	NdrFcShort( 0x0 ),	/* 0 */
/* 842 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 844 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 846 */	NdrFcShort( 0x8 ),	/* 8 */
/* 848 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 850 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 852 */	NdrFcShort( 0x4 ),	/* 4 */
/* 854 */	NdrFcShort( 0x4 ),	/* 4 */
/* 856 */	0x12, 0x0,	/* FC_UP */
/* 858 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (834) */
/* 860 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 862 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 864 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 866 */	NdrFcShort( 0x4 ),	/* 4 */
/* 868 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 870 */	NdrFcShort( 0x0 ),	/* 0 */
/* 872 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 874 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 876 */	NdrFcShort( 0x8 ),	/* 8 */
/* 878 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 880 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 882 */	NdrFcShort( 0x4 ),	/* 4 */
/* 884 */	NdrFcShort( 0x4 ),	/* 4 */
/* 886 */	0x12, 0x0,	/* FC_UP */
/* 888 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (864) */
/* 890 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 892 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 894 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 896 */	NdrFcShort( 0x8 ),	/* 8 */
/* 898 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 900 */	NdrFcShort( 0x0 ),	/* 0 */
/* 902 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 904 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 906 */	NdrFcShort( 0x8 ),	/* 8 */
/* 908 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 910 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 912 */	NdrFcShort( 0x4 ),	/* 4 */
/* 914 */	NdrFcShort( 0x4 ),	/* 4 */
/* 916 */	0x12, 0x0,	/* FC_UP */
/* 918 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (894) */
/* 920 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 922 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 924 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 926 */	NdrFcShort( 0x8 ),	/* 8 */
/* 928 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 930 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 932 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 934 */	NdrFcShort( 0x8 ),	/* 8 */
/* 936 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 938 */	NdrFcShort( 0xffd8 ),	/* -40 */
/* 940 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 942 */	NdrFcShort( 0xffffffee ),	/* Offset= -18 (924) */
/* 944 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 946 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 948 */	NdrFcShort( 0x28 ),	/* 40 */
/* 950 */	NdrFcShort( 0xffffffee ),	/* Offset= -18 (932) */
/* 952 */	NdrFcShort( 0x0 ),	/* Offset= 0 (952) */
/* 954 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 956 */	0x38,		/* FC_ALIGNM4 */
			0x8,		/* FC_LONG */
/* 958 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 960 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffc51 ),	/* Offset= -943 (18) */
			0x5b,		/* FC_END */
/* 964 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 966 */	NdrFcShort( 0x0 ),	/* 0 */
/* 968 */	NdrFcShort( 0x4 ),	/* 4 */
/* 970 */	NdrFcShort( 0x0 ),	/* 0 */
/* 972 */	NdrFcShort( 0xfffffc3e ),	/* Offset= -962 (10) */
/* 974 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 976 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 978 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 980 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 982 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 984 */	NdrFcShort( 0x6 ),	/* Offset= 6 (990) */
/* 986 */	
			0x13, 0x0,	/* FC_OP */
/* 988 */	NdrFcShort( 0xfffffc84 ),	/* Offset= -892 (96) */
/* 990 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 992 */	NdrFcShort( 0x1 ),	/* 1 */
/* 994 */	NdrFcShort( 0x4 ),	/* 4 */
/* 996 */	NdrFcShort( 0x0 ),	/* 0 */
/* 998 */	NdrFcShort( 0xfffffff4 ),	/* Offset= -12 (986) */
/* 1000 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 1002 */	0xd,		/* FC_ENUM16 */
			0x5c,		/* FC_PAD */
/* 1004 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 1006 */	NdrFcShort( 0xa ),	/* Offset= 10 (1016) */
/* 1008 */	
			0x13, 0x10,	/* FC_OP */
/* 1010 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1012) */
/* 1012 */	
			0x13, 0x0,	/* FC_OP */
/* 1014 */	NdrFcShort( 0xffffffbc ),	/* Offset= -68 (946) */
/* 1016 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1018 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1020 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1022 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1024 */	NdrFcShort( 0xfffffff0 ),	/* Offset= -16 (1008) */
/* 1026 */	
			0x11, 0x0,	/* FC_RP */
/* 1028 */	NdrFcShort( 0x6 ),	/* Offset= 6 (1034) */
/* 1030 */	
			0x12, 0x0,	/* FC_UP */
/* 1032 */	NdrFcShort( 0xfffffc58 ),	/* Offset= -936 (96) */
/* 1034 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1036 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1038 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1040 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1042 */	NdrFcShort( 0xfffffff4 ),	/* Offset= -12 (1030) */
/* 1044 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1046 */	NdrFcLong( 0x511b72bc ),	/* 1360753340 */
/* 1050 */	NdrFcShort( 0x641 ),	/* 1601 */
/* 1052 */	NdrFcShort( 0x4bd9 ),	/* 19417 */
/* 1054 */	0xad,		/* 173 */
			0xb0,		/* 176 */
/* 1056 */	0xf0,		/* 240 */
			0xef,		/* 239 */
/* 1058 */	0xfa,		/* 250 */
			0xe,		/* 14 */
/* 1060 */	0xfd,		/* 253 */
			0x26,		/* 38 */
/* 1062 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1064 */	NdrFcLong( 0xe8872fe4 ),	/* -393793564 */
/* 1068 */	NdrFcShort( 0x948a ),	/* -27510 */
/* 1070 */	NdrFcShort( 0x4a6b ),	/* 19051 */
/* 1072 */	0x94,		/* 148 */
			0xbd,		/* 189 */
/* 1074 */	0x5c,		/* 92 */
			0xcc,		/* 204 */
/* 1076 */	0x19,		/* 25 */
			0x90,		/* 144 */
/* 1078 */	0xd4,		/* 212 */
			0x69,		/* 105 */
/* 1080 */	
			0x11, 0x10,	/* FC_RP */
/* 1082 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1084) */
/* 1084 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1086 */	NdrFcLong( 0x6b56a92a ),	/* 1800841514 */
/* 1090 */	NdrFcShort( 0xa885 ),	/* -22395 */
/* 1092 */	NdrFcShort( 0x4083 ),	/* 16515 */
/* 1094 */	0xab,		/* 171 */
			0xaf,		/* 175 */
/* 1096 */	0x4e,		/* 78 */
			0x8d,		/* 141 */
/* 1098 */	0xf2,		/* 242 */
			0xf9,		/* 249 */
/* 1100 */	0x2,		/* 2 */
			0x2b,		/* 43 */
/* 1102 */	
			0x11, 0x0,	/* FC_RP */
/* 1104 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1106) */
/* 1106 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1108 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1110 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1112 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1114 */	NdrFcShort( 0xfffffe20 ),	/* Offset= -480 (634) */
/* 1116 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 1118 */	0xa,		/* FC_FLOAT */
			0x5c,		/* FC_PAD */

			0x0
        }
    };

const CInterfaceProxyVtbl * _Symlix_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_INumCatErrorProxyVtbl,
    ( CInterfaceProxyVtbl *) &_INumCatErrorRunProxyVtbl,
    ( CInterfaceProxyVtbl *) &_INumCatProxyVtbl,
    ( CInterfaceProxyVtbl *) &_INumCatHostCallBackProxyVtbl,
    0
};

const CInterfaceStubVtbl * _Symlix_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_INumCatErrorStubVtbl,
    ( CInterfaceStubVtbl *) &_INumCatErrorRunStubVtbl,
    ( CInterfaceStubVtbl *) &_INumCatStubVtbl,
    ( CInterfaceStubVtbl *) &_INumCatHostCallBackStubVtbl,
    0
};

PCInterfaceName const _Symlix_InterfaceNamesList[] = 
{
    "INumCatError",
    "INumCatErrorRun",
    "INumCat",
    "INumCatHostCallBack",
    0
};

const IID *  _Symlix_BaseIIDList[] = 
{
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    0
};


#define _Symlix_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _Symlix, pIID, n)

int __stdcall _Symlix_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _Symlix, 4, 2 )
    IID_BS_LOOKUP_NEXT_TEST( _Symlix, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _Symlix, 4, *pIndex )
    
}

const ExtendedProxyFileInfo Symlix_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _Symlix_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _Symlix_StubVtblList,
    (const PCInterfaceName * ) & _Symlix_InterfaceNamesList,
    (const IID ** ) & _Symlix_BaseIIDList,
    & _Symlix_IID_Lookup, 
    4,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
