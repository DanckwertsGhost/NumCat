/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Oct 06 16:53:51 2008
 */
/* Compiler settings for C:\Inetpub\ftproot\cpp_new\TraceRecorder\TraceRecorder.idl:
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

#ifndef __TraceRecorder_h__
#define __TraceRecorder_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IARTrace_FWD_DEFINED__
#define __IARTrace_FWD_DEFINED__
typedef interface IARTrace IARTrace;
#endif 	/* __IARTrace_FWD_DEFINED__ */


#ifndef __ARTrace_FWD_DEFINED__
#define __ARTrace_FWD_DEFINED__

#ifdef __cplusplus
typedef class ARTrace ARTrace;
#else
typedef struct ARTrace ARTrace;
#endif /* __cplusplus */

#endif 	/* __ARTrace_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IARTrace_INTERFACE_DEFINED__
#define __IARTrace_INTERFACE_DEFINED__

/* interface IARTrace */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IARTrace;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("482B95D2-2025-4807-87BF-CF8D0EE2A9B9")
    IARTrace : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetFilename( 
            /* [in] */ BSTR __RPC_FAR *pbstrName,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Assert( 
            /* [in] */ VARIANT_BOOL vbAssert,
            /* [in] */ BSTR __RPC_FAR *pbstrNote,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Trace( 
            /* [in] */ BSTR __RPC_FAR *pbstrNote,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE TraceS( 
            /* [in] */ BSTR __RPC_FAR *pbstrCodeName,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE TraceE( 
            /* [in] */ BSTR __RPC_FAR *pbstrCodeName,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbResult) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IARTraceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IARTrace __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IARTrace __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IARTrace __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IARTrace __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IARTrace __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IARTrace __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IARTrace __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetFilename )( 
            IARTrace __RPC_FAR * This,
            /* [in] */ BSTR __RPC_FAR *pbstrName,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Assert )( 
            IARTrace __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL vbAssert,
            /* [in] */ BSTR __RPC_FAR *pbstrNote,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Trace )( 
            IARTrace __RPC_FAR * This,
            /* [in] */ BSTR __RPC_FAR *pbstrNote,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TraceS )( 
            IARTrace __RPC_FAR * This,
            /* [in] */ BSTR __RPC_FAR *pbstrCodeName,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TraceE )( 
            IARTrace __RPC_FAR * This,
            /* [in] */ BSTR __RPC_FAR *pbstrCodeName,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbResult);
        
        END_INTERFACE
    } IARTraceVtbl;

    interface IARTrace
    {
        CONST_VTBL struct IARTraceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IARTrace_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IARTrace_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IARTrace_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IARTrace_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IARTrace_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IARTrace_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IARTrace_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IARTrace_SetFilename(This,pbstrName,pvbResult)	\
    (This)->lpVtbl -> SetFilename(This,pbstrName,pvbResult)

#define IARTrace_Assert(This,vbAssert,pbstrNote,pvbResult)	\
    (This)->lpVtbl -> Assert(This,vbAssert,pbstrNote,pvbResult)

#define IARTrace_Trace(This,pbstrNote,pvbResult)	\
    (This)->lpVtbl -> Trace(This,pbstrNote,pvbResult)

#define IARTrace_TraceS(This,pbstrCodeName,pvbResult)	\
    (This)->lpVtbl -> TraceS(This,pbstrCodeName,pvbResult)

#define IARTrace_TraceE(This,pbstrCodeName,pvbResult)	\
    (This)->lpVtbl -> TraceE(This,pbstrCodeName,pvbResult)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IARTrace_SetFilename_Proxy( 
    IARTrace __RPC_FAR * This,
    /* [in] */ BSTR __RPC_FAR *pbstrName,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbResult);


void __RPC_STUB IARTrace_SetFilename_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IARTrace_Assert_Proxy( 
    IARTrace __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL vbAssert,
    /* [in] */ BSTR __RPC_FAR *pbstrNote,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbResult);


void __RPC_STUB IARTrace_Assert_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IARTrace_Trace_Proxy( 
    IARTrace __RPC_FAR * This,
    /* [in] */ BSTR __RPC_FAR *pbstrNote,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbResult);


void __RPC_STUB IARTrace_Trace_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IARTrace_TraceS_Proxy( 
    IARTrace __RPC_FAR * This,
    /* [in] */ BSTR __RPC_FAR *pbstrCodeName,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbResult);


void __RPC_STUB IARTrace_TraceS_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IARTrace_TraceE_Proxy( 
    IARTrace __RPC_FAR * This,
    /* [in] */ BSTR __RPC_FAR *pbstrCodeName,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvbResult);


void __RPC_STUB IARTrace_TraceE_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IARTrace_INTERFACE_DEFINED__ */



#ifndef __TRACERECORDERLib_LIBRARY_DEFINED__
#define __TRACERECORDERLib_LIBRARY_DEFINED__

/* library TRACERECORDERLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_TRACERECORDERLib;

EXTERN_C const CLSID CLSID_ARTrace;

#ifdef __cplusplus

class DECLSPEC_UUID("C5F62AAA-494E-4786-B642-1D85CEF68F1C")
ARTrace;
#endif
#endif /* __TRACERECORDERLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
