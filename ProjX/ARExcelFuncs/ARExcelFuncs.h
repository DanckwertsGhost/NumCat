/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Jun 06 18:10:40 2012
 */
/* Compiler settings for C:\Inetpub\ftproot\cpp_new\ProjX\ARExcelFuncs\ARExcelFuncs.idl:
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

#ifndef __ARExcelFuncs_h__
#define __ARExcelFuncs_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IARFuncs_FWD_DEFINED__
#define __IARFuncs_FWD_DEFINED__
typedef interface IARFuncs IARFuncs;
#endif 	/* __IARFuncs_FWD_DEFINED__ */


#ifndef __ARFuncs_FWD_DEFINED__
#define __ARFuncs_FWD_DEFINED__

#ifdef __cplusplus
typedef class ARFuncs ARFuncs;
#else
typedef struct ARFuncs ARFuncs;
#endif /* __cplusplus */

#endif 	/* __ARFuncs_FWD_DEFINED__ */


#ifndef __ARExcelStream_FWD_DEFINED__
#define __ARExcelStream_FWD_DEFINED__

#ifdef __cplusplus
typedef class ARExcelStream ARExcelStream;
#else
typedef struct ARExcelStream ARExcelStream;
#endif /* __cplusplus */

#endif 	/* __ARExcelStream_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IARFuncs_INTERFACE_DEFINED__
#define __IARFuncs_INTERFACE_DEFINED__

/* interface IARFuncs */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IARFuncs;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ED20BD27-82D1-4D80-BA33-01DE6E5E107C")
    IARFuncs : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Interpolate( 
            /* [in] */ BSTR __RPC_FAR *Key,
            /* [in] */ VARIANT __RPC_FAR *KeyValue,
            /* [in] */ BSTR __RPC_FAR *LookupKey,
            /* [in] */ BSTR __RPC_FAR *Sheet,
            /* [retval][out] */ VARIANT __RPC_FAR *vReturn) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IARFuncsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IARFuncs __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IARFuncs __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IARFuncs __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IARFuncs __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IARFuncs __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IARFuncs __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IARFuncs __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Version )( 
            IARFuncs __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Interpolate )( 
            IARFuncs __RPC_FAR * This,
            /* [in] */ BSTR __RPC_FAR *Key,
            /* [in] */ VARIANT __RPC_FAR *KeyValue,
            /* [in] */ BSTR __RPC_FAR *LookupKey,
            /* [in] */ BSTR __RPC_FAR *Sheet,
            /* [retval][out] */ VARIANT __RPC_FAR *vReturn);
        
        END_INTERFACE
    } IARFuncsVtbl;

    interface IARFuncs
    {
        CONST_VTBL struct IARFuncsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IARFuncs_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IARFuncs_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IARFuncs_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IARFuncs_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IARFuncs_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IARFuncs_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IARFuncs_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IARFuncs_get_Version(This,pVal)	\
    (This)->lpVtbl -> get_Version(This,pVal)

#define IARFuncs_Interpolate(This,Key,KeyValue,LookupKey,Sheet,vReturn)	\
    (This)->lpVtbl -> Interpolate(This,Key,KeyValue,LookupKey,Sheet,vReturn)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IARFuncs_get_Version_Proxy( 
    IARFuncs __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IARFuncs_get_Version_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IARFuncs_Interpolate_Proxy( 
    IARFuncs __RPC_FAR * This,
    /* [in] */ BSTR __RPC_FAR *Key,
    /* [in] */ VARIANT __RPC_FAR *KeyValue,
    /* [in] */ BSTR __RPC_FAR *LookupKey,
    /* [in] */ BSTR __RPC_FAR *Sheet,
    /* [retval][out] */ VARIANT __RPC_FAR *vReturn);


void __RPC_STUB IARFuncs_Interpolate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IARFuncs_INTERFACE_DEFINED__ */



#ifndef __AREXCELFUNCSLib_LIBRARY_DEFINED__
#define __AREXCELFUNCSLib_LIBRARY_DEFINED__

/* library AREXCELFUNCSLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_AREXCELFUNCSLib;

EXTERN_C const CLSID CLSID_ARFuncs;

#ifdef __cplusplus

class DECLSPEC_UUID("A0FC5F62-9BB3-4430-87FF-20DBC812BB29")
ARFuncs;
#endif

EXTERN_C const CLSID CLSID_ARExcelStream;

#ifdef __cplusplus

class DECLSPEC_UUID("C18BB11A-5500-4B46-8B44-AA2D8FF281E4")
ARExcelStream;
#endif
#endif /* __AREXCELFUNCSLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long __RPC_FAR *, unsigned long            , VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long __RPC_FAR *, VARIANT __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
