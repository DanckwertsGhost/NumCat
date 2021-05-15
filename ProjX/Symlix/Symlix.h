/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed May 16 12:24:04 2012
 */
/* Compiler settings for C:\Inetpub\ftproot\cpp_new\ProjX\Symlix\Symlix.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __Symlix_h__
#define __Symlix_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __INumCatHostCallBack_FWD_DEFINED__
#define __INumCatHostCallBack_FWD_DEFINED__
typedef interface INumCatHostCallBack INumCatHostCallBack;
#endif 	/* __INumCatHostCallBack_FWD_DEFINED__ */


#ifndef __INumCatError_FWD_DEFINED__
#define __INumCatError_FWD_DEFINED__
typedef interface INumCatError INumCatError;
#endif 	/* __INumCatError_FWD_DEFINED__ */


#ifndef __INumCatErrorRun_FWD_DEFINED__
#define __INumCatErrorRun_FWD_DEFINED__
typedef interface INumCatErrorRun INumCatErrorRun;
#endif 	/* __INumCatErrorRun_FWD_DEFINED__ */


#ifndef __INumCat_FWD_DEFINED__
#define __INumCat_FWD_DEFINED__
typedef interface INumCat INumCat;
#endif 	/* __INumCat_FWD_DEFINED__ */


#ifndef __INumCatEditor_FWD_DEFINED__
#define __INumCatEditor_FWD_DEFINED__
typedef interface INumCatEditor INumCatEditor;
#endif 	/* __INumCatEditor_FWD_DEFINED__ */


#ifndef __IARDataPost_FWD_DEFINED__
#define __IARDataPost_FWD_DEFINED__
typedef interface IARDataPost IARDataPost;
#endif 	/* __IARDataPost_FWD_DEFINED__ */


#ifndef __IARRunProgress_FWD_DEFINED__
#define __IARRunProgress_FWD_DEFINED__
typedef interface IARRunProgress IARRunProgress;
#endif 	/* __IARRunProgress_FWD_DEFINED__ */


#ifndef __INumCatResource_FWD_DEFINED__
#define __INumCatResource_FWD_DEFINED__
typedef interface INumCatResource INumCatResource;
#endif 	/* __INumCatResource_FWD_DEFINED__ */


#ifndef __INumCatExcelLocalRes_FWD_DEFINED__
#define __INumCatExcelLocalRes_FWD_DEFINED__
typedef interface INumCatExcelLocalRes INumCatExcelLocalRes;
#endif 	/* __INumCatExcelLocalRes_FWD_DEFINED__ */


#ifndef __IARL_DRM_FWD_DEFINED__
#define __IARL_DRM_FWD_DEFINED__
typedef interface IARL_DRM IARL_DRM;
#endif 	/* __IARL_DRM_FWD_DEFINED__ */


#ifndef __NumCat_FWD_DEFINED__
#define __NumCat_FWD_DEFINED__

#ifdef __cplusplus
typedef class NumCat NumCat;
#else
typedef struct NumCat NumCat;
#endif /* __cplusplus */

#endif 	/* __NumCat_FWD_DEFINED__ */


#ifndef __NumCatError_FWD_DEFINED__
#define __NumCatError_FWD_DEFINED__

#ifdef __cplusplus
typedef class NumCatError NumCatError;
#else
typedef struct NumCatError NumCatError;
#endif /* __cplusplus */

#endif 	/* __NumCatError_FWD_DEFINED__ */


#ifndef __NumCatErrorRun_FWD_DEFINED__
#define __NumCatErrorRun_FWD_DEFINED__

#ifdef __cplusplus
typedef class NumCatErrorRun NumCatErrorRun;
#else
typedef struct NumCatErrorRun NumCatErrorRun;
#endif /* __cplusplus */

#endif 	/* __NumCatErrorRun_FWD_DEFINED__ */


#ifndef __NumCatEditor_FWD_DEFINED__
#define __NumCatEditor_FWD_DEFINED__

#ifdef __cplusplus
typedef class NumCatEditor NumCatEditor;
#else
typedef struct NumCatEditor NumCatEditor;
#endif /* __cplusplus */

#endif 	/* __NumCatEditor_FWD_DEFINED__ */


#ifndef __ARDataPost_FWD_DEFINED__
#define __ARDataPost_FWD_DEFINED__

#ifdef __cplusplus
typedef class ARDataPost ARDataPost;
#else
typedef struct ARDataPost ARDataPost;
#endif /* __cplusplus */

#endif 	/* __ARDataPost_FWD_DEFINED__ */


#ifndef __ARRunProgress_FWD_DEFINED__
#define __ARRunProgress_FWD_DEFINED__

#ifdef __cplusplus
typedef class ARRunProgress ARRunProgress;
#else
typedef struct ARRunProgress ARRunProgress;
#endif /* __cplusplus */

#endif 	/* __ARRunProgress_FWD_DEFINED__ */


#ifndef __NumCatResource_FWD_DEFINED__
#define __NumCatResource_FWD_DEFINED__

#ifdef __cplusplus
typedef class NumCatResource NumCatResource;
#else
typedef struct NumCatResource NumCatResource;
#endif /* __cplusplus */

#endif 	/* __NumCatResource_FWD_DEFINED__ */


#ifndef __NumCatExcelLocalRes_FWD_DEFINED__
#define __NumCatExcelLocalRes_FWD_DEFINED__

#ifdef __cplusplus
typedef class NumCatExcelLocalRes NumCatExcelLocalRes;
#else
typedef struct NumCatExcelLocalRes NumCatExcelLocalRes;
#endif /* __cplusplus */

#endif 	/* __NumCatExcelLocalRes_FWD_DEFINED__ */


#ifndef __ARL_DRM_FWD_DEFINED__
#define __ARL_DRM_FWD_DEFINED__

#ifdef __cplusplus
typedef class ARL_DRM ARL_DRM;
#else
typedef struct ARL_DRM ARL_DRM;
#endif /* __cplusplus */

#endif 	/* __ARL_DRM_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "SymlixStore.h"
#include "TraceRecorder.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_Symlix_0000 */
/* [local] */ 

typedef /* [public][public] */ 
enum __MIDL___MIDL_itf_Symlix_0000_0001
    {	blank	= 2,
	modelLoaded	= blank + 1,
	modelError	= modelLoaded + 1,
	runInProgress	= modelError + 1,
	runCompleted	= runInProgress + 1
    }	enumNumCatStatus;

typedef /* [public][public] */ 
enum __MIDL___MIDL_itf_Symlix_0000_0002
    {	errInput	= 2,
	errInternal	= errInput + 1,
	errSystem	= errInternal + 1,
	errSyntax	= errSystem + 1,
	errModel	= errSyntax + 1,
	errWarning	= errModel + 1,
	errDevWarning	= errWarning + 1
    }	enumNumCatErrorCode;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_Symlix_0000_0003
    {	varIndependant	= 2,
	varDependant	= varIndependant + 1,
	varDerivative	= varDependant + 1
    }	enumNumCatTypes;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_Symlix_0000_0004
    {	esddeStart	= 2,
	esddeStop	= esddeStart + 1
    }	enumNumCatDDE;

typedef /* [public][public] */ 
enum __MIDL___MIDL_itf_Symlix_0000_0005
    {	eLicTrial	= 2,
	eLicTimeLimited	= eLicTrial + 1,
	eLicAuthUnlimited	= eLicTimeLimited + 1,
	eLicFail	= eLicAuthUnlimited + 1
    }	enumLicenseState;

typedef /* [public][public] */ 
enum __MIDL___MIDL_itf_Symlix_0000_0006
    {	esecNothing	= 2,
	esecRun	= esecNothing + 1,
	esecRunAndReturn	= esecRun + 1,
	esecSyntaxAndReturn	= esecRunAndReturn + 1
    }	enumNumCatEditorCommand;

typedef /* [public][public] */ 
enum __MIDL___MIDL_itf_Symlix_0000_0007
    {	eventStart	= 0,
	eventStopGreaterEqual	= eventStart + 1,
	eventStopLessEqual	= eventStopGreaterEqual + 1
    }	enumNumCatEvent;

typedef /* [public][public] */ 
enum __MIDL___MIDL_itf_Symlix_0000_0008
    {	Help_DISPLAY_TOPIC	= 0,
	Help_HELP_FINDER	= 0,
	Help_DISPLAY_TOC	= 0x1,
	Help_DISPLAY_INDEX	= 0x2,
	Help_DISPLAY_SEARCH	= 0x3,
	Help_SET_WIN_TYPE	= 0x4,
	Help_GET_WIN_TYPE	= 0x5,
	Help_GET_WIN_HANDLE	= 0x6,
	Help_ENUM_INFO_TYPE	= 0x7,
	Help_SET_INFO_TYPE	= 0x8,
	Help_SYNC	= 0x9,
	Help_RESERVED1	= 0xa,
	Help_RESERVED2	= 0xb,
	Help_RESERVED3	= 0xc,
	Help_KEYWORD_LOOKUP	= 0xd,
	Help_DISPLAY_TEXT_POPUP	= 0xe,
	Help_HELP_CONTEXT	= 0xf,
	Help_TP_HELP_CONTEXTMENU	= 0x10,
	Help_TP_HELP_WM_HELP	= 0x11,
	Help_CLOSE_ALL	= 0x12,
	Help_ALINK_LOOKUP	= 0x13,
	Help_GET_LAST_ERROR	= 0x14,
	Help_ENUM_CATEGORY	= 0x15,
	Help_ENUM_CATEGORY_IT	= 0x16,
	Help_RESET_IT_FILTER	= 0x17,
	Help_SET_INCLUSIVE_FILTER	= 0x18,
	Help_SET_EXCLUSIVE_FILTER	= 0x19,
	Help_INITIALIZE	= 0x1c,
	Help_UNINITIALIZE	= 0x1d,
	Help_PRETRANSLATEMESSAGE	= 0xfd,
	Help_SET_GLOBAL_PROPERTY	= 0xfc
    }	enumNumCatHelp;



extern RPC_IF_HANDLE __MIDL_itf_Symlix_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_Symlix_0000_v0_0_s_ifspec;

#ifndef __INumCatHostCallBack_INTERFACE_DEFINED__
#define __INumCatHostCallBack_INTERFACE_DEFINED__

/* interface INumCatHostCallBack */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_INumCatHostCallBack;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E8872FE4-948A-4a6b-94BD-5CCC1990D469")
    INumCatHostCallBack : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE TimeSignal( 
            /* [retval][out] */ long __RPC_FAR *piTime) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Update( 
            /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *ppsaVals,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvb) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ToUpdate( 
            /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *ppsaInds,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvb) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ExpectEnd( 
            /* [retval][out] */ double __RPC_FAR *pdEnd) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct INumCatHostCallBackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            INumCatHostCallBack __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            INumCatHostCallBack __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            INumCatHostCallBack __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            INumCatHostCallBack __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            INumCatHostCallBack __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            INumCatHostCallBack __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            INumCatHostCallBack __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TimeSignal )( 
            INumCatHostCallBack __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *piTime);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Update )( 
            INumCatHostCallBack __RPC_FAR * This,
            /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *ppsaVals,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvb);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ToUpdate )( 
            INumCatHostCallBack __RPC_FAR * This,
            /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *ppsaInds,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvb);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ExpectEnd )( 
            INumCatHostCallBack __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pdEnd);
        
        END_INTERFACE
    } INumCatHostCallBackVtbl;

    interface INumCatHostCallBack
    {
        CONST_VTBL struct INumCatHostCallBackVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INumCatHostCallBack_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define INumCatHostCallBack_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define INumCatHostCallBack_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define INumCatHostCallBack_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define INumCatHostCallBack_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define INumCatHostCallBack_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define INumCatHostCallBack_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define INumCatHostCallBack_TimeSignal(This,piTime)	\
    (This)->lpVtbl -> TimeSignal(This,piTime)

#define INumCatHostCallBack_Update(This,ppsaVals,pvb)	\
    (This)->lpVtbl -> Update(This,ppsaVals,pvb)

#define INumCatHostCallBack_ToUpdate(This,ppsaInds,pvb)	\
    (This)->lpVtbl -> ToUpdate(This,ppsaInds,pvb)

#define INumCatHostCallBack_ExpectEnd(This,pdEnd)	\
    (This)->lpVtbl -> ExpectEnd(This,pdEnd)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INumCatHostCallBack_TimeSignal_Proxy( 
    INumCatHostCallBack __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *piTime);


void __RPC_STUB INumCatHostCallBack_TimeSignal_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INumCatHostCallBack_Update_Proxy( 
    INumCatHostCallBack __RPC_FAR * This,
    /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *ppsaVals,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvb);


void __RPC_STUB INumCatHostCallBack_Update_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INumCatHostCallBack_ToUpdate_Proxy( 
    INumCatHostCallBack __RPC_FAR * This,
    /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *ppsaInds,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvb);


void __RPC_STUB INumCatHostCallBack_ToUpdate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INumCatHostCallBack_ExpectEnd_Proxy( 
    INumCatHostCallBack __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pdEnd);


void __RPC_STUB INumCatHostCallBack_ExpectEnd_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __INumCatHostCallBack_INTERFACE_DEFINED__ */


#ifndef __INumCatError_INTERFACE_DEFINED__
#define __INumCatError_INTERFACE_DEFINED__

/* interface INumCatError */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_INumCatError;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("48FB2B27-E7C7-40D3-B3C7-4EA80F351810")
    INumCatError : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StreamName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Line( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ErrCode( 
            /* [retval][out] */ enumNumCatErrorCode __RPC_FAR *pVal) = 0;
        
        virtual /* [hidden][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DevSupportDescription( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_XPosition( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HelpRef( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct INumCatErrorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            INumCatError __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            INumCatError __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            INumCatError __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            INumCatError __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            INumCatError __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            INumCatError __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            INumCatError __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Description )( 
            INumCatError __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StreamName )( 
            INumCatError __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Line )( 
            INumCatError __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ErrCode )( 
            INumCatError __RPC_FAR * This,
            /* [retval][out] */ enumNumCatErrorCode __RPC_FAR *pVal);
        
        /* [hidden][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DevSupportDescription )( 
            INumCatError __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_XPosition )( 
            INumCatError __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HelpRef )( 
            INumCatError __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        END_INTERFACE
    } INumCatErrorVtbl;

    interface INumCatError
    {
        CONST_VTBL struct INumCatErrorVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INumCatError_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define INumCatError_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define INumCatError_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define INumCatError_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define INumCatError_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define INumCatError_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define INumCatError_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define INumCatError_get_Description(This,pVal)	\
    (This)->lpVtbl -> get_Description(This,pVal)

#define INumCatError_get_StreamName(This,pVal)	\
    (This)->lpVtbl -> get_StreamName(This,pVal)

#define INumCatError_get_Line(This,pVal)	\
    (This)->lpVtbl -> get_Line(This,pVal)

#define INumCatError_get_ErrCode(This,pVal)	\
    (This)->lpVtbl -> get_ErrCode(This,pVal)

#define INumCatError_get_DevSupportDescription(This,pVal)	\
    (This)->lpVtbl -> get_DevSupportDescription(This,pVal)

#define INumCatError_get_XPosition(This,pVal)	\
    (This)->lpVtbl -> get_XPosition(This,pVal)

#define INumCatError_get_HelpRef(This,pVal)	\
    (This)->lpVtbl -> get_HelpRef(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INumCatError_get_Description_Proxy( 
    INumCatError __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB INumCatError_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INumCatError_get_StreamName_Proxy( 
    INumCatError __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB INumCatError_get_StreamName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INumCatError_get_Line_Proxy( 
    INumCatError __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB INumCatError_get_Line_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INumCatError_get_ErrCode_Proxy( 
    INumCatError __RPC_FAR * This,
    /* [retval][out] */ enumNumCatErrorCode __RPC_FAR *pVal);


void __RPC_STUB INumCatError_get_ErrCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INumCatError_get_DevSupportDescription_Proxy( 
    INumCatError __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB INumCatError_get_DevSupportDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INumCatError_get_XPosition_Proxy( 
    INumCatError __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB INumCatError_get_XPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INumCatError_get_HelpRef_Proxy( 
    INumCatError __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB INumCatError_get_HelpRef_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __INumCatError_INTERFACE_DEFINED__ */


#ifndef __INumCatErrorRun_INTERFACE_DEFINED__
#define __INumCatErrorRun_INTERFACE_DEFINED__

/* interface INumCatErrorRun */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_INumCatErrorRun;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6B56A92A-A885-4083-ABAF-4E8DF2F9022B")
    INumCatErrorRun : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAllErrors( 
            /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *ppErrors) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CountErrors( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct INumCatErrorRunVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            INumCatErrorRun __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            INumCatErrorRun __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            INumCatErrorRun __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            INumCatErrorRun __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            INumCatErrorRun __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            INumCatErrorRun __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            INumCatErrorRun __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAllErrors )( 
            INumCatErrorRun __RPC_FAR * This,
            /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *ppErrors);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CountErrors )( 
            INumCatErrorRun __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        END_INTERFACE
    } INumCatErrorRunVtbl;

    interface INumCatErrorRun
    {
        CONST_VTBL struct INumCatErrorRunVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INumCatErrorRun_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define INumCatErrorRun_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define INumCatErrorRun_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define INumCatErrorRun_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define INumCatErrorRun_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define INumCatErrorRun_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define INumCatErrorRun_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define INumCatErrorRun_GetAllErrors(This,ppErrors)	\
    (This)->lpVtbl -> GetAllErrors(This,ppErrors)

#define INumCatErrorRun_get_CountErrors(This,pVal)	\
    (This)->lpVtbl -> get_CountErrors(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INumCatErrorRun_GetAllErrors_Proxy( 
    INumCatErrorRun __RPC_FAR * This,
    /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *ppErrors);


void __RPC_STUB INumCatErrorRun_GetAllErrors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INumCatErrorRun_get_CountErrors_Proxy( 
    INumCatErrorRun __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB INumCatErrorRun_get_CountErrors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __INumCatErrorRun_INTERFACE_DEFINED__ */


#ifndef __INumCat_INTERFACE_DEFINED__
#define __INumCat_INTERFACE_DEFINED__

/* interface INumCat */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_INumCat;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2F146DBD-50AF-4A26-99D7-2C44658355E0")
    INumCat : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadModel( 
            /* [in] */ BSTR __RPC_FAR *sFileName,
            /* [in] */ IARDataStore __RPC_FAR *pIStore,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RunModel( 
            /* [in] */ long hInstance,
            /* [defaultvalue] */ INumCatHostCallBack __RPC_FAR *pINumCatHostCallBack,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbResult) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ModelStatus( 
            /* [retval][out] */ enumNumCatStatus __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ClearModel( 
            /* [in] */ VARIANT_BOOL bEvenIfRunning,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ResetModel( 
            /* [in] */ VARIANT_BOOL bEvenIfRunning,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbResult) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VariableNames( 
            /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *ppsaVars) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CurrentModelValues( 
            /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *ppsaVals) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GiveVariableIndex( 
            /* [in] */ BSTR __RPC_FAR *sVariable,
            /* [retval][out] */ long __RPC_FAR *piIndex) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StopModel( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GiveErrors( 
            /* [retval][out] */ INumCatErrorRun __RPC_FAR *__RPC_FAR *pINumCatErrorRun) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LicenseState( 
            /* [retval][out] */ enumLicenseState __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddUserEvents( 
            /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *ppsaVars,
            /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *ppsaVals,
            /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *ppsaEvTypes,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbResult) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RunTag( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RunTag( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VersionDescription( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct INumCatVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            INumCat __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            INumCat __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            INumCat __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            INumCat __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            INumCat __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            INumCat __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            INumCat __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadModel )( 
            INumCat __RPC_FAR * This,
            /* [in] */ BSTR __RPC_FAR *sFileName,
            /* [in] */ IARDataStore __RPC_FAR *pIStore,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RunModel )( 
            INumCat __RPC_FAR * This,
            /* [in] */ long hInstance,
            /* [defaultvalue] */ INumCatHostCallBack __RPC_FAR *pINumCatHostCallBack,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbResult);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ModelStatus )( 
            INumCat __RPC_FAR * This,
            /* [retval][out] */ enumNumCatStatus __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ClearModel )( 
            INumCat __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL bEvenIfRunning,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetModel )( 
            INumCat __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL bEvenIfRunning,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbResult);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VariableNames )( 
            INumCat __RPC_FAR * This,
            /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *ppsaVars);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CurrentModelValues )( 
            INumCat __RPC_FAR * This,
            /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *ppsaVals);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GiveVariableIndex )( 
            INumCat __RPC_FAR * This,
            /* [in] */ BSTR __RPC_FAR *sVariable,
            /* [retval][out] */ long __RPC_FAR *piIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StopModel )( 
            INumCat __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GiveErrors )( 
            INumCat __RPC_FAR * This,
            /* [retval][out] */ INumCatErrorRun __RPC_FAR *__RPC_FAR *pINumCatErrorRun);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LicenseState )( 
            INumCat __RPC_FAR * This,
            /* [retval][out] */ enumLicenseState __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddUserEvents )( 
            INumCat __RPC_FAR * This,
            /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *ppsaVars,
            /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *ppsaVals,
            /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *ppsaEvTypes,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbResult);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RunTag )( 
            INumCat __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RunTag )( 
            INumCat __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Version )( 
            INumCat __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VersionDescription )( 
            INumCat __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        END_INTERFACE
    } INumCatVtbl;

    interface INumCat
    {
        CONST_VTBL struct INumCatVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INumCat_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define INumCat_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define INumCat_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define INumCat_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define INumCat_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define INumCat_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define INumCat_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define INumCat_LoadModel(This,sFileName,pIStore,pvbResult)	\
    (This)->lpVtbl -> LoadModel(This,sFileName,pIStore,pvbResult)

#define INumCat_RunModel(This,hInstance,pINumCatHostCallBack,pvbResult)	\
    (This)->lpVtbl -> RunModel(This,hInstance,pINumCatHostCallBack,pvbResult)

#define INumCat_get_ModelStatus(This,pVal)	\
    (This)->lpVtbl -> get_ModelStatus(This,pVal)

#define INumCat_ClearModel(This,bEvenIfRunning,pvbResult)	\
    (This)->lpVtbl -> ClearModel(This,bEvenIfRunning,pvbResult)

#define INumCat_ResetModel(This,bEvenIfRunning,pvbResult)	\
    (This)->lpVtbl -> ResetModel(This,bEvenIfRunning,pvbResult)

#define INumCat_get_VariableNames(This,ppsaVars)	\
    (This)->lpVtbl -> get_VariableNames(This,ppsaVars)

#define INumCat_get_CurrentModelValues(This,ppsaVals)	\
    (This)->lpVtbl -> get_CurrentModelValues(This,ppsaVals)

#define INumCat_GiveVariableIndex(This,sVariable,piIndex)	\
    (This)->lpVtbl -> GiveVariableIndex(This,sVariable,piIndex)

#define INumCat_StopModel(This)	\
    (This)->lpVtbl -> StopModel(This)

#define INumCat_GiveErrors(This,pINumCatErrorRun)	\
    (This)->lpVtbl -> GiveErrors(This,pINumCatErrorRun)

#define INumCat_get_LicenseState(This,pVal)	\
    (This)->lpVtbl -> get_LicenseState(This,pVal)

#define INumCat_AddUserEvents(This,ppsaVars,ppsaVals,ppsaEvTypes,pvbResult)	\
    (This)->lpVtbl -> AddUserEvents(This,ppsaVars,ppsaVals,ppsaEvTypes,pvbResult)

#define INumCat_get_RunTag(This,pVal)	\
    (This)->lpVtbl -> get_RunTag(This,pVal)

#define INumCat_put_RunTag(This,newVal)	\
    (This)->lpVtbl -> put_RunTag(This,newVal)

#define INumCat_get_Version(This,pVal)	\
    (This)->lpVtbl -> get_Version(This,pVal)

#define INumCat_get_VersionDescription(This,pVal)	\
    (This)->lpVtbl -> get_VersionDescription(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INumCat_LoadModel_Proxy( 
    INumCat __RPC_FAR * This,
    /* [in] */ BSTR __RPC_FAR *sFileName,
    /* [in] */ IARDataStore __RPC_FAR *pIStore,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbResult);


void __RPC_STUB INumCat_LoadModel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INumCat_RunModel_Proxy( 
    INumCat __RPC_FAR * This,
    /* [in] */ long hInstance,
    /* [defaultvalue] */ INumCatHostCallBack __RPC_FAR *pINumCatHostCallBack,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbResult);


void __RPC_STUB INumCat_RunModel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INumCat_get_ModelStatus_Proxy( 
    INumCat __RPC_FAR * This,
    /* [retval][out] */ enumNumCatStatus __RPC_FAR *pVal);


void __RPC_STUB INumCat_get_ModelStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INumCat_ClearModel_Proxy( 
    INumCat __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL bEvenIfRunning,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbResult);


void __RPC_STUB INumCat_ClearModel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INumCat_ResetModel_Proxy( 
    INumCat __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL bEvenIfRunning,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbResult);


void __RPC_STUB INumCat_ResetModel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INumCat_get_VariableNames_Proxy( 
    INumCat __RPC_FAR * This,
    /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *ppsaVars);


void __RPC_STUB INumCat_get_VariableNames_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INumCat_get_CurrentModelValues_Proxy( 
    INumCat __RPC_FAR * This,
    /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *ppsaVals);


void __RPC_STUB INumCat_get_CurrentModelValues_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INumCat_GiveVariableIndex_Proxy( 
    INumCat __RPC_FAR * This,
    /* [in] */ BSTR __RPC_FAR *sVariable,
    /* [retval][out] */ long __RPC_FAR *piIndex);


void __RPC_STUB INumCat_GiveVariableIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INumCat_StopModel_Proxy( 
    INumCat __RPC_FAR * This);


void __RPC_STUB INumCat_StopModel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INumCat_GiveErrors_Proxy( 
    INumCat __RPC_FAR * This,
    /* [retval][out] */ INumCatErrorRun __RPC_FAR *__RPC_FAR *pINumCatErrorRun);


void __RPC_STUB INumCat_GiveErrors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INumCat_get_LicenseState_Proxy( 
    INumCat __RPC_FAR * This,
    /* [retval][out] */ enumLicenseState __RPC_FAR *pVal);


void __RPC_STUB INumCat_get_LicenseState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INumCat_AddUserEvents_Proxy( 
    INumCat __RPC_FAR * This,
    /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *ppsaVars,
    /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *ppsaVals,
    /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *ppsaEvTypes,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbResult);


void __RPC_STUB INumCat_AddUserEvents_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INumCat_get_RunTag_Proxy( 
    INumCat __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB INumCat_get_RunTag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INumCat_put_RunTag_Proxy( 
    INumCat __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB INumCat_put_RunTag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INumCat_get_Version_Proxy( 
    INumCat __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB INumCat_get_Version_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INumCat_get_VersionDescription_Proxy( 
    INumCat __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB INumCat_get_VersionDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __INumCat_INTERFACE_DEFINED__ */



#ifndef __NumCatLib_LIBRARY_DEFINED__
#define __NumCatLib_LIBRARY_DEFINED__

/* library NumCatLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_NumCatLib;

#ifndef __INumCatEditor_INTERFACE_DEFINED__
#define __INumCatEditor_INTERFACE_DEFINED__

/* interface INumCatEditor */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_INumCatEditor;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B80CE381-488E-467A-B537-AC6C9E6A1B3C")
    INumCatEditor : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OpenToEdit( 
            /* [in] */ int ihwnd,
            /* [in] */ BSTR __RPC_FAR *pbstrKey,
            /* [in] */ IARDataStore __RPC_FAR *pIStore,
            /* [in] */ INumCatErrorRun __RPC_FAR *pIErrorRun,
            /* [in] */ IARTrace __RPC_FAR *pIARTrace,
            /* [retval][out] */ enumNumCatEditorCommand __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct INumCatEditorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            INumCatEditor __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            INumCatEditor __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            INumCatEditor __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            INumCatEditor __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            INumCatEditor __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            INumCatEditor __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            INumCatEditor __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OpenToEdit )( 
            INumCatEditor __RPC_FAR * This,
            /* [in] */ int ihwnd,
            /* [in] */ BSTR __RPC_FAR *pbstrKey,
            /* [in] */ IARDataStore __RPC_FAR *pIStore,
            /* [in] */ INumCatErrorRun __RPC_FAR *pIErrorRun,
            /* [in] */ IARTrace __RPC_FAR *pIARTrace,
            /* [retval][out] */ enumNumCatEditorCommand __RPC_FAR *pVal);
        
        END_INTERFACE
    } INumCatEditorVtbl;

    interface INumCatEditor
    {
        CONST_VTBL struct INumCatEditorVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INumCatEditor_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define INumCatEditor_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define INumCatEditor_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define INumCatEditor_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define INumCatEditor_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define INumCatEditor_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define INumCatEditor_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define INumCatEditor_OpenToEdit(This,ihwnd,pbstrKey,pIStore,pIErrorRun,pIARTrace,pVal)	\
    (This)->lpVtbl -> OpenToEdit(This,ihwnd,pbstrKey,pIStore,pIErrorRun,pIARTrace,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INumCatEditor_OpenToEdit_Proxy( 
    INumCatEditor __RPC_FAR * This,
    /* [in] */ int ihwnd,
    /* [in] */ BSTR __RPC_FAR *pbstrKey,
    /* [in] */ IARDataStore __RPC_FAR *pIStore,
    /* [in] */ INumCatErrorRun __RPC_FAR *pIErrorRun,
    /* [in] */ IARTrace __RPC_FAR *pIARTrace,
    /* [retval][out] */ enumNumCatEditorCommand __RPC_FAR *pVal);


void __RPC_STUB INumCatEditor_OpenToEdit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __INumCatEditor_INTERFACE_DEFINED__ */


#ifndef __IARDataPost_INTERFACE_DEFINED__
#define __IARDataPost_INTERFACE_DEFINED__

/* interface IARDataPost */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IARDataPost;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("293CA626-F7A4-46AA-B5D1-4C13C4AE6A28")
    IARDataPost : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddItem( 
            /* [in] */ BSTR __RPC_FAR *pbstrFirstKey,
            /* [in] */ BSTR __RPC_FAR *pbstrSecondKey,
            /* [in] */ double vValue,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RetrieveItem( 
            /* [in] */ BSTR __RPC_FAR *pbstrFirstKey,
            /* [in] */ BSTR __RPC_FAR *pbstrSecondKey,
            /* [retval][out] */ double __RPC_FAR *pvValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FindItem( 
            /* [in] */ BSTR __RPC_FAR *pbstrFirstKey,
            /* [in] */ BSTR __RPC_FAR *pbstrSecondKey,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddTextItem( 
            /* [in] */ BSTR __RPC_FAR *pbstrFirstKey,
            /* [in] */ BSTR __RPC_FAR *pbstrSecondKey,
            /* [in] */ BSTR __RPC_FAR *pbstrItem,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RetrieveTextItem( 
            /* [in] */ BSTR __RPC_FAR *pbstrFirstKey,
            /* [in] */ BSTR __RPC_FAR *pbstrSecondKey,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FindTextItem( 
            /* [in] */ BSTR __RPC_FAR *pbstrFirstKey,
            /* [in] */ BSTR __RPC_FAR *pbstrSecondKey,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbResult) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IARDataPostVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IARDataPost __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IARDataPost __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IARDataPost __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IARDataPost __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IARDataPost __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IARDataPost __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IARDataPost __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddItem )( 
            IARDataPost __RPC_FAR * This,
            /* [in] */ BSTR __RPC_FAR *pbstrFirstKey,
            /* [in] */ BSTR __RPC_FAR *pbstrSecondKey,
            /* [in] */ double vValue,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RetrieveItem )( 
            IARDataPost __RPC_FAR * This,
            /* [in] */ BSTR __RPC_FAR *pbstrFirstKey,
            /* [in] */ BSTR __RPC_FAR *pbstrSecondKey,
            /* [retval][out] */ double __RPC_FAR *pvValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FindItem )( 
            IARDataPost __RPC_FAR * This,
            /* [in] */ BSTR __RPC_FAR *pbstrFirstKey,
            /* [in] */ BSTR __RPC_FAR *pbstrSecondKey,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddTextItem )( 
            IARDataPost __RPC_FAR * This,
            /* [in] */ BSTR __RPC_FAR *pbstrFirstKey,
            /* [in] */ BSTR __RPC_FAR *pbstrSecondKey,
            /* [in] */ BSTR __RPC_FAR *pbstrItem,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RetrieveTextItem )( 
            IARDataPost __RPC_FAR * This,
            /* [in] */ BSTR __RPC_FAR *pbstrFirstKey,
            /* [in] */ BSTR __RPC_FAR *pbstrSecondKey,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FindTextItem )( 
            IARDataPost __RPC_FAR * This,
            /* [in] */ BSTR __RPC_FAR *pbstrFirstKey,
            /* [in] */ BSTR __RPC_FAR *pbstrSecondKey,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbResult);
        
        END_INTERFACE
    } IARDataPostVtbl;

    interface IARDataPost
    {
        CONST_VTBL struct IARDataPostVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IARDataPost_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IARDataPost_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IARDataPost_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IARDataPost_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IARDataPost_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IARDataPost_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IARDataPost_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IARDataPost_AddItem(This,pbstrFirstKey,pbstrSecondKey,vValue,pvbResult)	\
    (This)->lpVtbl -> AddItem(This,pbstrFirstKey,pbstrSecondKey,vValue,pvbResult)

#define IARDataPost_RetrieveItem(This,pbstrFirstKey,pbstrSecondKey,pvValue)	\
    (This)->lpVtbl -> RetrieveItem(This,pbstrFirstKey,pbstrSecondKey,pvValue)

#define IARDataPost_FindItem(This,pbstrFirstKey,pbstrSecondKey,pvbResult)	\
    (This)->lpVtbl -> FindItem(This,pbstrFirstKey,pbstrSecondKey,pvbResult)

#define IARDataPost_AddTextItem(This,pbstrFirstKey,pbstrSecondKey,pbstrItem,pvbResult)	\
    (This)->lpVtbl -> AddTextItem(This,pbstrFirstKey,pbstrSecondKey,pbstrItem,pvbResult)

#define IARDataPost_RetrieveTextItem(This,pbstrFirstKey,pbstrSecondKey,pbstrValue)	\
    (This)->lpVtbl -> RetrieveTextItem(This,pbstrFirstKey,pbstrSecondKey,pbstrValue)

#define IARDataPost_FindTextItem(This,pbstrFirstKey,pbstrSecondKey,pvbResult)	\
    (This)->lpVtbl -> FindTextItem(This,pbstrFirstKey,pbstrSecondKey,pvbResult)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IARDataPost_AddItem_Proxy( 
    IARDataPost __RPC_FAR * This,
    /* [in] */ BSTR __RPC_FAR *pbstrFirstKey,
    /* [in] */ BSTR __RPC_FAR *pbstrSecondKey,
    /* [in] */ double vValue,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbResult);


void __RPC_STUB IARDataPost_AddItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IARDataPost_RetrieveItem_Proxy( 
    IARDataPost __RPC_FAR * This,
    /* [in] */ BSTR __RPC_FAR *pbstrFirstKey,
    /* [in] */ BSTR __RPC_FAR *pbstrSecondKey,
    /* [retval][out] */ double __RPC_FAR *pvValue);


void __RPC_STUB IARDataPost_RetrieveItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IARDataPost_FindItem_Proxy( 
    IARDataPost __RPC_FAR * This,
    /* [in] */ BSTR __RPC_FAR *pbstrFirstKey,
    /* [in] */ BSTR __RPC_FAR *pbstrSecondKey,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbResult);


void __RPC_STUB IARDataPost_FindItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IARDataPost_AddTextItem_Proxy( 
    IARDataPost __RPC_FAR * This,
    /* [in] */ BSTR __RPC_FAR *pbstrFirstKey,
    /* [in] */ BSTR __RPC_FAR *pbstrSecondKey,
    /* [in] */ BSTR __RPC_FAR *pbstrItem,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbResult);


void __RPC_STUB IARDataPost_AddTextItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IARDataPost_RetrieveTextItem_Proxy( 
    IARDataPost __RPC_FAR * This,
    /* [in] */ BSTR __RPC_FAR *pbstrFirstKey,
    /* [in] */ BSTR __RPC_FAR *pbstrSecondKey,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrValue);


void __RPC_STUB IARDataPost_RetrieveTextItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IARDataPost_FindTextItem_Proxy( 
    IARDataPost __RPC_FAR * This,
    /* [in] */ BSTR __RPC_FAR *pbstrFirstKey,
    /* [in] */ BSTR __RPC_FAR *pbstrSecondKey,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbResult);


void __RPC_STUB IARDataPost_FindTextItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IARDataPost_INTERFACE_DEFINED__ */


#ifndef __IARRunProgress_INTERFACE_DEFINED__
#define __IARRunProgress_INTERFACE_DEFINED__

/* interface IARRunProgress */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IARRunProgress;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("54F985BE-62D5-4E33-A96C-66807855A48B")
    IARRunProgress : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RunModel( 
            /* [in] */ int ihwnd,
            /* [in] */ INumCat __RPC_FAR *pINumCat,
            /* [in] */ IARDataStore __RPC_FAR *pIStore,
            /* [in] */ BSTR __RPC_FAR *pbstrRunName,
            /* [in] */ VARIANT_BOOL bShow,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbSuccess) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IARRunProgressVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IARRunProgress __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IARRunProgress __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IARRunProgress __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IARRunProgress __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IARRunProgress __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IARRunProgress __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IARRunProgress __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RunModel )( 
            IARRunProgress __RPC_FAR * This,
            /* [in] */ int ihwnd,
            /* [in] */ INumCat __RPC_FAR *pINumCat,
            /* [in] */ IARDataStore __RPC_FAR *pIStore,
            /* [in] */ BSTR __RPC_FAR *pbstrRunName,
            /* [in] */ VARIANT_BOOL bShow,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbSuccess);
        
        END_INTERFACE
    } IARRunProgressVtbl;

    interface IARRunProgress
    {
        CONST_VTBL struct IARRunProgressVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IARRunProgress_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IARRunProgress_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IARRunProgress_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IARRunProgress_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IARRunProgress_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IARRunProgress_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IARRunProgress_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IARRunProgress_RunModel(This,ihwnd,pINumCat,pIStore,pbstrRunName,bShow,pbSuccess)	\
    (This)->lpVtbl -> RunModel(This,ihwnd,pINumCat,pIStore,pbstrRunName,bShow,pbSuccess)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IARRunProgress_RunModel_Proxy( 
    IARRunProgress __RPC_FAR * This,
    /* [in] */ int ihwnd,
    /* [in] */ INumCat __RPC_FAR *pINumCat,
    /* [in] */ IARDataStore __RPC_FAR *pIStore,
    /* [in] */ BSTR __RPC_FAR *pbstrRunName,
    /* [in] */ VARIANT_BOOL bShow,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbSuccess);


void __RPC_STUB IARRunProgress_RunModel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IARRunProgress_INTERFACE_DEFINED__ */


#ifndef __INumCatResource_INTERFACE_DEFINED__
#define __INumCatResource_INTERFACE_DEFINED__

/* interface INumCatResource */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_INumCatResource;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("49BFFF76-4D2C-4FE8-A18E-0749C9AAAF08")
    INumCatResource : public IDispatch
    {
    public:
        virtual /* [hidden][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Picture( 
            /* [in] */ short iPict,
            /* [retval][out] */ IPictureDisp __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [hidden][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Mask( 
            /* [in] */ short iMask,
            /* [retval][out] */ IPictureDisp __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [hidden][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_String( 
            /* [in] */ short iString,
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VersionDescription( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CallHTMLHelp( 
            /* [in] */ long hWnd,
            /* [in] */ enumNumCatHelp eHelp,
            /* [in] */ long iRef,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct INumCatResourceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            INumCatResource __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            INumCatResource __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            INumCatResource __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            INumCatResource __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            INumCatResource __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            INumCatResource __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            INumCatResource __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [hidden][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Picture )( 
            INumCatResource __RPC_FAR * This,
            /* [in] */ short iPict,
            /* [retval][out] */ IPictureDisp __RPC_FAR *__RPC_FAR *pVal);
        
        /* [hidden][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Mask )( 
            INumCatResource __RPC_FAR * This,
            /* [in] */ short iMask,
            /* [retval][out] */ IPictureDisp __RPC_FAR *__RPC_FAR *pVal);
        
        /* [hidden][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_String )( 
            INumCatResource __RPC_FAR * This,
            /* [in] */ short iString,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Version )( 
            INumCatResource __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VersionDescription )( 
            INumCatResource __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CallHTMLHelp )( 
            INumCatResource __RPC_FAR * This,
            /* [in] */ long hWnd,
            /* [in] */ enumNumCatHelp eHelp,
            /* [in] */ long iRef,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        END_INTERFACE
    } INumCatResourceVtbl;

    interface INumCatResource
    {
        CONST_VTBL struct INumCatResourceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INumCatResource_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define INumCatResource_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define INumCatResource_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define INumCatResource_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define INumCatResource_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define INumCatResource_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define INumCatResource_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define INumCatResource_get_Picture(This,iPict,pVal)	\
    (This)->lpVtbl -> get_Picture(This,iPict,pVal)

#define INumCatResource_get_Mask(This,iMask,pVal)	\
    (This)->lpVtbl -> get_Mask(This,iMask,pVal)

#define INumCatResource_get_String(This,iString,pVal)	\
    (This)->lpVtbl -> get_String(This,iString,pVal)

#define INumCatResource_get_Version(This,pVal)	\
    (This)->lpVtbl -> get_Version(This,pVal)

#define INumCatResource_get_VersionDescription(This,pVal)	\
    (This)->lpVtbl -> get_VersionDescription(This,pVal)

#define INumCatResource_CallHTMLHelp(This,hWnd,eHelp,iRef,pVal)	\
    (This)->lpVtbl -> CallHTMLHelp(This,hWnd,eHelp,iRef,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [hidden][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INumCatResource_get_Picture_Proxy( 
    INumCatResource __RPC_FAR * This,
    /* [in] */ short iPict,
    /* [retval][out] */ IPictureDisp __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB INumCatResource_get_Picture_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INumCatResource_get_Mask_Proxy( 
    INumCatResource __RPC_FAR * This,
    /* [in] */ short iMask,
    /* [retval][out] */ IPictureDisp __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB INumCatResource_get_Mask_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INumCatResource_get_String_Proxy( 
    INumCatResource __RPC_FAR * This,
    /* [in] */ short iString,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB INumCatResource_get_String_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INumCatResource_get_Version_Proxy( 
    INumCatResource __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB INumCatResource_get_Version_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INumCatResource_get_VersionDescription_Proxy( 
    INumCatResource __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB INumCatResource_get_VersionDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INumCatResource_CallHTMLHelp_Proxy( 
    INumCatResource __RPC_FAR * This,
    /* [in] */ long hWnd,
    /* [in] */ enumNumCatHelp eHelp,
    /* [in] */ long iRef,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB INumCatResource_CallHTMLHelp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __INumCatResource_INTERFACE_DEFINED__ */


#ifndef __INumCatExcelLocalRes_INTERFACE_DEFINED__
#define __INumCatExcelLocalRes_INTERFACE_DEFINED__

/* interface INumCatExcelLocalRes */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_INumCatExcelLocalRes;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B4B5D683-B400-4540-A7E2-26C7D3544007")
    INumCatExcelLocalRes : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetPropertyItem( 
            /* [in] */ BSTR __RPC_FAR *sKey,
            /* [in] */ BSTR __RPC_FAR *sItem,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvb) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SheetOrder( 
            /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *ppVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetSheetOrder( 
            /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *sSheetArray,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvb) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPropertyItem( 
            /* [in] */ BSTR __RPC_FAR *sKey,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrItem) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReadProperties( 
            /* [in] */ IDispatch __RPC_FAR *Application,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvb) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveProperties( 
            /* [in] */ IDispatch __RPC_FAR *Application,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvb) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TagCharts( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TagModels( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TagSheets( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TagResults( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VersionDescription( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddResultName( 
            /* [in] */ BSTR __RPC_FAR *sResult,
            /* [retval][out] */ long __RPC_FAR *piCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IsAResultName( 
            /* [in] */ BSTR __RPC_FAR *sResultName,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LocalSheetName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPropertyNumber( 
            /* [in] */ BSTR __RPC_FAR *pbstr,
            /* [retval][out] */ float __RPC_FAR *Value) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetPropertyNumber( 
            /* [in] */ BSTR __RPC_FAR *pbstrKey,
            /* [in] */ float __RPC_FAR *pValue,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvb) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct INumCatExcelLocalResVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            INumCatExcelLocalRes __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            INumCatExcelLocalRes __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            INumCatExcelLocalRes __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            INumCatExcelLocalRes __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            INumCatExcelLocalRes __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            INumCatExcelLocalRes __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            INumCatExcelLocalRes __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPropertyItem )( 
            INumCatExcelLocalRes __RPC_FAR * This,
            /* [in] */ BSTR __RPC_FAR *sKey,
            /* [in] */ BSTR __RPC_FAR *sItem,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvb);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SheetOrder )( 
            INumCatExcelLocalRes __RPC_FAR * This,
            /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *ppVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSheetOrder )( 
            INumCatExcelLocalRes __RPC_FAR * This,
            /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *sSheetArray,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvb);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPropertyItem )( 
            INumCatExcelLocalRes __RPC_FAR * This,
            /* [in] */ BSTR __RPC_FAR *sKey,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrItem);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReadProperties )( 
            INumCatExcelLocalRes __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *Application,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvb);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SaveProperties )( 
            INumCatExcelLocalRes __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *Application,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvb);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TagCharts )( 
            INumCatExcelLocalRes __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TagModels )( 
            INumCatExcelLocalRes __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TagSheets )( 
            INumCatExcelLocalRes __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TagResults )( 
            INumCatExcelLocalRes __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Version )( 
            INumCatExcelLocalRes __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VersionDescription )( 
            INumCatExcelLocalRes __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddResultName )( 
            INumCatExcelLocalRes __RPC_FAR * This,
            /* [in] */ BSTR __RPC_FAR *sResult,
            /* [retval][out] */ long __RPC_FAR *piCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsAResultName )( 
            INumCatExcelLocalRes __RPC_FAR * This,
            /* [in] */ BSTR __RPC_FAR *sResultName,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LocalSheetName )( 
            INumCatExcelLocalRes __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPropertyNumber )( 
            INumCatExcelLocalRes __RPC_FAR * This,
            /* [in] */ BSTR __RPC_FAR *pbstr,
            /* [retval][out] */ float __RPC_FAR *Value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPropertyNumber )( 
            INumCatExcelLocalRes __RPC_FAR * This,
            /* [in] */ BSTR __RPC_FAR *pbstrKey,
            /* [in] */ float __RPC_FAR *pValue,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvb);
        
        END_INTERFACE
    } INumCatExcelLocalResVtbl;

    interface INumCatExcelLocalRes
    {
        CONST_VTBL struct INumCatExcelLocalResVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INumCatExcelLocalRes_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define INumCatExcelLocalRes_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define INumCatExcelLocalRes_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define INumCatExcelLocalRes_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define INumCatExcelLocalRes_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define INumCatExcelLocalRes_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define INumCatExcelLocalRes_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define INumCatExcelLocalRes_SetPropertyItem(This,sKey,sItem,pvb)	\
    (This)->lpVtbl -> SetPropertyItem(This,sKey,sItem,pvb)

#define INumCatExcelLocalRes_get_SheetOrder(This,ppVal)	\
    (This)->lpVtbl -> get_SheetOrder(This,ppVal)

#define INumCatExcelLocalRes_SetSheetOrder(This,sSheetArray,pvb)	\
    (This)->lpVtbl -> SetSheetOrder(This,sSheetArray,pvb)

#define INumCatExcelLocalRes_GetPropertyItem(This,sKey,pbstrItem)	\
    (This)->lpVtbl -> GetPropertyItem(This,sKey,pbstrItem)

#define INumCatExcelLocalRes_ReadProperties(This,Application,pvb)	\
    (This)->lpVtbl -> ReadProperties(This,Application,pvb)

#define INumCatExcelLocalRes_SaveProperties(This,Application,pvb)	\
    (This)->lpVtbl -> SaveProperties(This,Application,pvb)

#define INumCatExcelLocalRes_get_TagCharts(This,pVal)	\
    (This)->lpVtbl -> get_TagCharts(This,pVal)

#define INumCatExcelLocalRes_get_TagModels(This,pVal)	\
    (This)->lpVtbl -> get_TagModels(This,pVal)

#define INumCatExcelLocalRes_get_TagSheets(This,pVal)	\
    (This)->lpVtbl -> get_TagSheets(This,pVal)

#define INumCatExcelLocalRes_get_TagResults(This,pVal)	\
    (This)->lpVtbl -> get_TagResults(This,pVal)

#define INumCatExcelLocalRes_get_Version(This,pVal)	\
    (This)->lpVtbl -> get_Version(This,pVal)

#define INumCatExcelLocalRes_get_VersionDescription(This,pVal)	\
    (This)->lpVtbl -> get_VersionDescription(This,pVal)

#define INumCatExcelLocalRes_AddResultName(This,sResult,piCount)	\
    (This)->lpVtbl -> AddResultName(This,sResult,piCount)

#define INumCatExcelLocalRes_IsAResultName(This,sResultName,pVal)	\
    (This)->lpVtbl -> IsAResultName(This,sResultName,pVal)

#define INumCatExcelLocalRes_get_LocalSheetName(This,pVal)	\
    (This)->lpVtbl -> get_LocalSheetName(This,pVal)

#define INumCatExcelLocalRes_GetPropertyNumber(This,pbstr,Value)	\
    (This)->lpVtbl -> GetPropertyNumber(This,pbstr,Value)

#define INumCatExcelLocalRes_SetPropertyNumber(This,pbstrKey,pValue,pvb)	\
    (This)->lpVtbl -> SetPropertyNumber(This,pbstrKey,pValue,pvb)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INumCatExcelLocalRes_SetPropertyItem_Proxy( 
    INumCatExcelLocalRes __RPC_FAR * This,
    /* [in] */ BSTR __RPC_FAR *sKey,
    /* [in] */ BSTR __RPC_FAR *sItem,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvb);


void __RPC_STUB INumCatExcelLocalRes_SetPropertyItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INumCatExcelLocalRes_get_SheetOrder_Proxy( 
    INumCatExcelLocalRes __RPC_FAR * This,
    /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *ppVal);


void __RPC_STUB INumCatExcelLocalRes_get_SheetOrder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INumCatExcelLocalRes_SetSheetOrder_Proxy( 
    INumCatExcelLocalRes __RPC_FAR * This,
    /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *sSheetArray,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvb);


void __RPC_STUB INumCatExcelLocalRes_SetSheetOrder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INumCatExcelLocalRes_GetPropertyItem_Proxy( 
    INumCatExcelLocalRes __RPC_FAR * This,
    /* [in] */ BSTR __RPC_FAR *sKey,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrItem);


void __RPC_STUB INumCatExcelLocalRes_GetPropertyItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INumCatExcelLocalRes_ReadProperties_Proxy( 
    INumCatExcelLocalRes __RPC_FAR * This,
    /* [in] */ IDispatch __RPC_FAR *Application,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvb);


void __RPC_STUB INumCatExcelLocalRes_ReadProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INumCatExcelLocalRes_SaveProperties_Proxy( 
    INumCatExcelLocalRes __RPC_FAR * This,
    /* [in] */ IDispatch __RPC_FAR *Application,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvb);


void __RPC_STUB INumCatExcelLocalRes_SaveProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INumCatExcelLocalRes_get_TagCharts_Proxy( 
    INumCatExcelLocalRes __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB INumCatExcelLocalRes_get_TagCharts_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INumCatExcelLocalRes_get_TagModels_Proxy( 
    INumCatExcelLocalRes __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB INumCatExcelLocalRes_get_TagModels_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INumCatExcelLocalRes_get_TagSheets_Proxy( 
    INumCatExcelLocalRes __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB INumCatExcelLocalRes_get_TagSheets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INumCatExcelLocalRes_get_TagResults_Proxy( 
    INumCatExcelLocalRes __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB INumCatExcelLocalRes_get_TagResults_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INumCatExcelLocalRes_get_Version_Proxy( 
    INumCatExcelLocalRes __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB INumCatExcelLocalRes_get_Version_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INumCatExcelLocalRes_get_VersionDescription_Proxy( 
    INumCatExcelLocalRes __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB INumCatExcelLocalRes_get_VersionDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INumCatExcelLocalRes_AddResultName_Proxy( 
    INumCatExcelLocalRes __RPC_FAR * This,
    /* [in] */ BSTR __RPC_FAR *sResult,
    /* [retval][out] */ long __RPC_FAR *piCount);


void __RPC_STUB INumCatExcelLocalRes_AddResultName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INumCatExcelLocalRes_IsAResultName_Proxy( 
    INumCatExcelLocalRes __RPC_FAR * This,
    /* [in] */ BSTR __RPC_FAR *sResultName,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB INumCatExcelLocalRes_IsAResultName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INumCatExcelLocalRes_get_LocalSheetName_Proxy( 
    INumCatExcelLocalRes __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB INumCatExcelLocalRes_get_LocalSheetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INumCatExcelLocalRes_GetPropertyNumber_Proxy( 
    INumCatExcelLocalRes __RPC_FAR * This,
    /* [in] */ BSTR __RPC_FAR *pbstr,
    /* [retval][out] */ float __RPC_FAR *Value);


void __RPC_STUB INumCatExcelLocalRes_GetPropertyNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INumCatExcelLocalRes_SetPropertyNumber_Proxy( 
    INumCatExcelLocalRes __RPC_FAR * This,
    /* [in] */ BSTR __RPC_FAR *pbstrKey,
    /* [in] */ float __RPC_FAR *pValue,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvb);


void __RPC_STUB INumCatExcelLocalRes_SetPropertyNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __INumCatExcelLocalRes_INTERFACE_DEFINED__ */


#ifndef __IARL_DRM_INTERFACE_DEFINED__
#define __IARL_DRM_INTERFACE_DEFINED__

/* interface IARL_DRM */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IARL_DRM;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2013EA3D-5AC4-4BBE-A3C9-528E89247BE2")
    IARL_DRM : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Expired( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_User( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Key( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MachineFingerPrint( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MachineEnhancedFingerPrint( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Register( 
            /* [in] */ BSTR __RPC_FAR *sUser,
            /* [in] */ BSTR __RPC_FAR *sKey,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbResult) = 0;
        
        virtual /* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetValue( 
            /* [in] */ BSTR __RPC_FAR *sIndex,
            /* [retval][out] */ BSTR __RPC_FAR *sValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OpenUserRegisterDialog( 
            /* [defaultvalue][in][optional] */ int parent_hwnd,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvb) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OpenBuyNowURL( 
            /* [defaultvalue][in][optional] */ int parent_hwnd,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvb) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DaysLeft( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CountUses( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Verified( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IARL_DRMVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IARL_DRM __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IARL_DRM __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IARL_DRM __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IARL_DRM __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IARL_DRM __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IARL_DRM __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IARL_DRM __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Version )( 
            IARL_DRM __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Expired )( 
            IARL_DRM __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_User )( 
            IARL_DRM __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Key )( 
            IARL_DRM __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MachineFingerPrint )( 
            IARL_DRM __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MachineEnhancedFingerPrint )( 
            IARL_DRM __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Register )( 
            IARL_DRM __RPC_FAR * This,
            /* [in] */ BSTR __RPC_FAR *sUser,
            /* [in] */ BSTR __RPC_FAR *sKey,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbResult);
        
        /* [hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetValue )( 
            IARL_DRM __RPC_FAR * This,
            /* [in] */ BSTR __RPC_FAR *sIndex,
            /* [retval][out] */ BSTR __RPC_FAR *sValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OpenUserRegisterDialog )( 
            IARL_DRM __RPC_FAR * This,
            /* [defaultvalue][in][optional] */ int parent_hwnd,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvb);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OpenBuyNowURL )( 
            IARL_DRM __RPC_FAR * This,
            /* [defaultvalue][in][optional] */ int parent_hwnd,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvb);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DaysLeft )( 
            IARL_DRM __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CountUses )( 
            IARL_DRM __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Verified )( 
            IARL_DRM __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        END_INTERFACE
    } IARL_DRMVtbl;

    interface IARL_DRM
    {
        CONST_VTBL struct IARL_DRMVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IARL_DRM_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IARL_DRM_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IARL_DRM_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IARL_DRM_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IARL_DRM_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IARL_DRM_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IARL_DRM_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IARL_DRM_get_Version(This,pVal)	\
    (This)->lpVtbl -> get_Version(This,pVal)

#define IARL_DRM_get_Expired(This,pVal)	\
    (This)->lpVtbl -> get_Expired(This,pVal)

#define IARL_DRM_get_User(This,pVal)	\
    (This)->lpVtbl -> get_User(This,pVal)

#define IARL_DRM_get_Key(This,pVal)	\
    (This)->lpVtbl -> get_Key(This,pVal)

#define IARL_DRM_get_MachineFingerPrint(This,pVal)	\
    (This)->lpVtbl -> get_MachineFingerPrint(This,pVal)

#define IARL_DRM_get_MachineEnhancedFingerPrint(This,pVal)	\
    (This)->lpVtbl -> get_MachineEnhancedFingerPrint(This,pVal)

#define IARL_DRM_Register(This,sUser,sKey,pvbResult)	\
    (This)->lpVtbl -> Register(This,sUser,sKey,pvbResult)

#define IARL_DRM_GetValue(This,sIndex,sValue)	\
    (This)->lpVtbl -> GetValue(This,sIndex,sValue)

#define IARL_DRM_OpenUserRegisterDialog(This,parent_hwnd,pvb)	\
    (This)->lpVtbl -> OpenUserRegisterDialog(This,parent_hwnd,pvb)

#define IARL_DRM_OpenBuyNowURL(This,parent_hwnd,pvb)	\
    (This)->lpVtbl -> OpenBuyNowURL(This,parent_hwnd,pvb)

#define IARL_DRM_get_DaysLeft(This,pVal)	\
    (This)->lpVtbl -> get_DaysLeft(This,pVal)

#define IARL_DRM_get_CountUses(This,pVal)	\
    (This)->lpVtbl -> get_CountUses(This,pVal)

#define IARL_DRM_get_Verified(This,pVal)	\
    (This)->lpVtbl -> get_Verified(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IARL_DRM_get_Version_Proxy( 
    IARL_DRM __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IARL_DRM_get_Version_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IARL_DRM_get_Expired_Proxy( 
    IARL_DRM __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IARL_DRM_get_Expired_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IARL_DRM_get_User_Proxy( 
    IARL_DRM __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IARL_DRM_get_User_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IARL_DRM_get_Key_Proxy( 
    IARL_DRM __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IARL_DRM_get_Key_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IARL_DRM_get_MachineFingerPrint_Proxy( 
    IARL_DRM __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IARL_DRM_get_MachineFingerPrint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IARL_DRM_get_MachineEnhancedFingerPrint_Proxy( 
    IARL_DRM __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IARL_DRM_get_MachineEnhancedFingerPrint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IARL_DRM_Register_Proxy( 
    IARL_DRM __RPC_FAR * This,
    /* [in] */ BSTR __RPC_FAR *sUser,
    /* [in] */ BSTR __RPC_FAR *sKey,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbResult);


void __RPC_STUB IARL_DRM_Register_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE IARL_DRM_GetValue_Proxy( 
    IARL_DRM __RPC_FAR * This,
    /* [in] */ BSTR __RPC_FAR *sIndex,
    /* [retval][out] */ BSTR __RPC_FAR *sValue);


void __RPC_STUB IARL_DRM_GetValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IARL_DRM_OpenUserRegisterDialog_Proxy( 
    IARL_DRM __RPC_FAR * This,
    /* [defaultvalue][in][optional] */ int parent_hwnd,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvb);


void __RPC_STUB IARL_DRM_OpenUserRegisterDialog_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IARL_DRM_OpenBuyNowURL_Proxy( 
    IARL_DRM __RPC_FAR * This,
    /* [defaultvalue][in][optional] */ int parent_hwnd,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvb);


void __RPC_STUB IARL_DRM_OpenBuyNowURL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IARL_DRM_get_DaysLeft_Proxy( 
    IARL_DRM __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IARL_DRM_get_DaysLeft_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IARL_DRM_get_CountUses_Proxy( 
    IARL_DRM __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IARL_DRM_get_CountUses_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IARL_DRM_get_Verified_Proxy( 
    IARL_DRM __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IARL_DRM_get_Verified_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IARL_DRM_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_NumCat;

#ifdef __cplusplus

class DECLSPEC_UUID("8F086AA2-30F8-4480-A04A-9623134E4EB2")
NumCat;
#endif

EXTERN_C const CLSID CLSID_NumCatError;

#ifdef __cplusplus

class DECLSPEC_UUID("4A5890DE-4E2C-4B2E-A0EE-9C379056661D")
NumCatError;
#endif

EXTERN_C const CLSID CLSID_NumCatErrorRun;

#ifdef __cplusplus

class DECLSPEC_UUID("D73F0863-5428-4818-A201-EECC3D645E4C")
NumCatErrorRun;
#endif

EXTERN_C const CLSID CLSID_NumCatEditor;

#ifdef __cplusplus

class DECLSPEC_UUID("E2CF0192-2445-44EA-A0D3-69804BADB96B")
NumCatEditor;
#endif

EXTERN_C const CLSID CLSID_ARDataPost;

#ifdef __cplusplus

class DECLSPEC_UUID("F37F34AA-4762-4F9E-AD00-F97D7932B30B")
ARDataPost;
#endif

EXTERN_C const CLSID CLSID_ARRunProgress;

#ifdef __cplusplus

class DECLSPEC_UUID("A6210167-B6D4-4C0F-8AE4-5D37F6C1B628")
ARRunProgress;
#endif

EXTERN_C const CLSID CLSID_NumCatResource;

#ifdef __cplusplus

class DECLSPEC_UUID("CDD16F1B-5BA2-444A-90FA-4F2ABFD68DC4")
NumCatResource;
#endif

EXTERN_C const CLSID CLSID_NumCatExcelLocalRes;

#ifdef __cplusplus

class DECLSPEC_UUID("8E04407D-E8B5-45E6-A935-74A54D9C77E5")
NumCatExcelLocalRes;
#endif

EXTERN_C const CLSID CLSID_ARL_DRM;

#ifdef __cplusplus

class DECLSPEC_UUID("30393366-5766-4352-B5A5-6CB2C6FD59DC")
ARL_DRM;
#endif
#endif /* __NumCatLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

unsigned long             __RPC_USER  LPSAFEARRAY_UserSize(     unsigned long __RPC_FAR *, unsigned long            , LPSAFEARRAY __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  LPSAFEARRAY_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, LPSAFEARRAY __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  LPSAFEARRAY_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, LPSAFEARRAY __RPC_FAR * ); 
void                      __RPC_USER  LPSAFEARRAY_UserFree(     unsigned long __RPC_FAR *, LPSAFEARRAY __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
