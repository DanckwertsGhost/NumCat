/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Nov 30 10:40:26 2009
 */
/* Compiler settings for C:\Inetpub\ftproot\cpp_new\SymlixStore\SymlixStore.idl:
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

#ifndef __SymlixStore_h__
#define __SymlixStore_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IARStream_FWD_DEFINED__
#define __IARStream_FWD_DEFINED__
typedef interface IARStream IARStream;
#endif 	/* __IARStream_FWD_DEFINED__ */


#ifndef __IARWriteStream_FWD_DEFINED__
#define __IARWriteStream_FWD_DEFINED__
typedef interface IARWriteStream IARWriteStream;
#endif 	/* __IARWriteStream_FWD_DEFINED__ */


#ifndef __IARDataStore_FWD_DEFINED__
#define __IARDataStore_FWD_DEFINED__
typedef interface IARDataStore IARDataStore;
#endif 	/* __IARDataStore_FWD_DEFINED__ */


#ifndef __ARFileStream_FWD_DEFINED__
#define __ARFileStream_FWD_DEFINED__

#ifdef __cplusplus
typedef class ARFileStream ARFileStream;
#else
typedef struct ARFileStream ARFileStream;
#endif /* __cplusplus */

#endif 	/* __ARFileStream_FWD_DEFINED__ */


#ifndef __ARFileDataStore_FWD_DEFINED__
#define __ARFileDataStore_FWD_DEFINED__

#ifdef __cplusplus
typedef class ARFileDataStore ARFileDataStore;
#else
typedef struct ARFileDataStore ARFileDataStore;
#endif /* __cplusplus */

#endif 	/* __ARFileDataStore_FWD_DEFINED__ */


#ifndef __ARFileWriteStream_FWD_DEFINED__
#define __ARFileWriteStream_FWD_DEFINED__

#ifdef __cplusplus
typedef class ARFileWriteStream ARFileWriteStream;
#else
typedef struct ARFileWriteStream ARFileWriteStream;
#endif /* __cplusplus */

#endif 	/* __ARFileWriteStream_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_SymlixStore_0000 */
/* [local] */ 

typedef /* [public][public][public][public][public][public][public][public] */ 
enum __MIDL___MIDL_itf_SymlixStore_0000_0001
    {	streamEmpty	= 2,
	hasStreamInfo	= streamEmpty + 1,
	streamLoaded	= hasStreamInfo + 1,
	streamReadline	= streamLoaded + 1,
	streamWriteLine	= streamReadline + 1,
	streamEnd	= streamWriteLine + 1,
	streamFail	= streamEnd + 1
    }	enumARStream;

typedef /* [public][public][public] */ 
enum __MIDL___MIDL_itf_SymlixStore_0000_0002
    {	formatCSV	= 2,
	formatFreeText	= formatCSV + 1
    }	enumARWriteHint;

typedef /* [public][public][public] */ 
enum __MIDL___MIDL_itf_SymlixStore_0000_0003
    {	readFormatCSV	= 2,
	readFormatFreeText	= readFormatCSV + 1
    }	enumARReadHint;

typedef /* [public][public][public] */ 
enum __MIDL___MIDL_itf_SymlixStore_0000_0004
    {	esioFormula	= 2,
	esioNotes	= esioFormula + 1,
	esioAuthor	= esioNotes + 1,
	esioLastRev	= esioAuthor + 1,
	esioRWED	= esioLastRev + 1
    }	enumARIODataType;



extern RPC_IF_HANDLE __MIDL_itf_SymlixStore_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_SymlixStore_0000_v0_0_s_ifspec;

#ifndef __IARStream_INTERFACE_DEFINED__
#define __IARStream_INTERFACE_DEFINED__

/* interface IARStream */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IARStream;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2CEB4397-105D-42F4-B84A-016E2E5155AF")
    IARStream : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StreamState( 
            /* [retval][out] */ enumARStream __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE loadStream( 
            /* [in] */ BSTR __RPC_FAR *pbstrKey,
            /* [in] */ enumARReadHint esrh,
            /* [retval][out] */ enumARStream __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE readLine( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrLine) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE gotoFirstLine( 
            /* [retval][out] */ enumARStream __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE lastLineExtra( 
            /* [in] */ enumARIODataType esType,
            /* [retval][out] */ BSTR __RPC_FAR *pbstr) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddWatchObject( 
            /* [in] */ IDispatch __RPC_FAR *pIDisp,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pOK) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDataSystem( 
            /* [in] */ IDispatch __RPC_FAR *pIDisp,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pOK) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IARStreamVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IARStream __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IARStream __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IARStream __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IARStream __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IARStream __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IARStream __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IARStream __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StreamState )( 
            IARStream __RPC_FAR * This,
            /* [retval][out] */ enumARStream __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *loadStream )( 
            IARStream __RPC_FAR * This,
            /* [in] */ BSTR __RPC_FAR *pbstrKey,
            /* [in] */ enumARReadHint esrh,
            /* [retval][out] */ enumARStream __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *readLine )( 
            IARStream __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrLine);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *gotoFirstLine )( 
            IARStream __RPC_FAR * This,
            /* [retval][out] */ enumARStream __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *lastLineExtra )( 
            IARStream __RPC_FAR * This,
            /* [in] */ enumARIODataType esType,
            /* [retval][out] */ BSTR __RPC_FAR *pbstr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddWatchObject )( 
            IARStream __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *pIDisp,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pOK);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetDataSystem )( 
            IARStream __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *pIDisp,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pOK);
        
        END_INTERFACE
    } IARStreamVtbl;

    interface IARStream
    {
        CONST_VTBL struct IARStreamVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IARStream_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IARStream_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IARStream_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IARStream_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IARStream_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IARStream_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IARStream_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IARStream_get_StreamState(This,pVal)	\
    (This)->lpVtbl -> get_StreamState(This,pVal)

#define IARStream_loadStream(This,pbstrKey,esrh,pVal)	\
    (This)->lpVtbl -> loadStream(This,pbstrKey,esrh,pVal)

#define IARStream_readLine(This,pbstrLine)	\
    (This)->lpVtbl -> readLine(This,pbstrLine)

#define IARStream_gotoFirstLine(This,pVal)	\
    (This)->lpVtbl -> gotoFirstLine(This,pVal)

#define IARStream_lastLineExtra(This,esType,pbstr)	\
    (This)->lpVtbl -> lastLineExtra(This,esType,pbstr)

#define IARStream_AddWatchObject(This,pIDisp,pOK)	\
    (This)->lpVtbl -> AddWatchObject(This,pIDisp,pOK)

#define IARStream_SetDataSystem(This,pIDisp,pOK)	\
    (This)->lpVtbl -> SetDataSystem(This,pIDisp,pOK)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IARStream_get_StreamState_Proxy( 
    IARStream __RPC_FAR * This,
    /* [retval][out] */ enumARStream __RPC_FAR *pVal);


void __RPC_STUB IARStream_get_StreamState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IARStream_loadStream_Proxy( 
    IARStream __RPC_FAR * This,
    /* [in] */ BSTR __RPC_FAR *pbstrKey,
    /* [in] */ enumARReadHint esrh,
    /* [retval][out] */ enumARStream __RPC_FAR *pVal);


void __RPC_STUB IARStream_loadStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IARStream_readLine_Proxy( 
    IARStream __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrLine);


void __RPC_STUB IARStream_readLine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IARStream_gotoFirstLine_Proxy( 
    IARStream __RPC_FAR * This,
    /* [retval][out] */ enumARStream __RPC_FAR *pVal);


void __RPC_STUB IARStream_gotoFirstLine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IARStream_lastLineExtra_Proxy( 
    IARStream __RPC_FAR * This,
    /* [in] */ enumARIODataType esType,
    /* [retval][out] */ BSTR __RPC_FAR *pbstr);


void __RPC_STUB IARStream_lastLineExtra_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IARStream_AddWatchObject_Proxy( 
    IARStream __RPC_FAR * This,
    /* [in] */ IDispatch __RPC_FAR *pIDisp,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pOK);


void __RPC_STUB IARStream_AddWatchObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IARStream_SetDataSystem_Proxy( 
    IARStream __RPC_FAR * This,
    /* [in] */ IDispatch __RPC_FAR *pIDisp,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pOK);


void __RPC_STUB IARStream_SetDataSystem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IARStream_INTERFACE_DEFINED__ */


#ifndef __IARWriteStream_INTERFACE_DEFINED__
#define __IARWriteStream_INTERFACE_DEFINED__

/* interface IARWriteStream */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IARWriteStream;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9AB3CC26-6A0A-4EDF-9AC5-B37F5CC8B894")
    IARWriteStream : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE loadStream( 
            /* [in] */ BSTR __RPC_FAR *pbstrKey,
            /* [in] */ enumARWriteHint hint,
            /* [retval][out] */ enumARStream __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE writeLine( 
            /* [in] */ BSTR __RPC_FAR *pbstrKey,
            /* [retval][out] */ enumARStream __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StreamState( 
            /* [retval][out] */ enumARStream __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE closeStream( 
            /* [retval][out] */ enumARStream __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE prepareLineWriteExtra( 
            /* [in] */ enumARIODataType esType,
            /* [in] */ BSTR __RPC_FAR *pbstr,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddWatchObject( 
            /* [in] */ IDispatch __RPC_FAR *pIDisp,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pOK) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDataSystem( 
            /* [in] */ IDispatch __RPC_FAR *pIDisp,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pOK) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IARWriteStreamVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IARWriteStream __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IARWriteStream __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IARWriteStream __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IARWriteStream __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IARWriteStream __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IARWriteStream __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IARWriteStream __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *loadStream )( 
            IARWriteStream __RPC_FAR * This,
            /* [in] */ BSTR __RPC_FAR *pbstrKey,
            /* [in] */ enumARWriteHint hint,
            /* [retval][out] */ enumARStream __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *writeLine )( 
            IARWriteStream __RPC_FAR * This,
            /* [in] */ BSTR __RPC_FAR *pbstrKey,
            /* [retval][out] */ enumARStream __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StreamState )( 
            IARWriteStream __RPC_FAR * This,
            /* [retval][out] */ enumARStream __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *closeStream )( 
            IARWriteStream __RPC_FAR * This,
            /* [retval][out] */ enumARStream __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *prepareLineWriteExtra )( 
            IARWriteStream __RPC_FAR * This,
            /* [in] */ enumARIODataType esType,
            /* [in] */ BSTR __RPC_FAR *pbstr,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddWatchObject )( 
            IARWriteStream __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *pIDisp,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pOK);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetDataSystem )( 
            IARWriteStream __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *pIDisp,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pOK);
        
        END_INTERFACE
    } IARWriteStreamVtbl;

    interface IARWriteStream
    {
        CONST_VTBL struct IARWriteStreamVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IARWriteStream_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IARWriteStream_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IARWriteStream_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IARWriteStream_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IARWriteStream_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IARWriteStream_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IARWriteStream_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IARWriteStream_loadStream(This,pbstrKey,hint,pVal)	\
    (This)->lpVtbl -> loadStream(This,pbstrKey,hint,pVal)

#define IARWriteStream_writeLine(This,pbstrKey,pVal)	\
    (This)->lpVtbl -> writeLine(This,pbstrKey,pVal)

#define IARWriteStream_get_StreamState(This,pVal)	\
    (This)->lpVtbl -> get_StreamState(This,pVal)

#define IARWriteStream_closeStream(This,pVal)	\
    (This)->lpVtbl -> closeStream(This,pVal)

#define IARWriteStream_prepareLineWriteExtra(This,esType,pbstr,pVal)	\
    (This)->lpVtbl -> prepareLineWriteExtra(This,esType,pbstr,pVal)

#define IARWriteStream_AddWatchObject(This,pIDisp,pOK)	\
    (This)->lpVtbl -> AddWatchObject(This,pIDisp,pOK)

#define IARWriteStream_SetDataSystem(This,pIDisp,pOK)	\
    (This)->lpVtbl -> SetDataSystem(This,pIDisp,pOK)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IARWriteStream_loadStream_Proxy( 
    IARWriteStream __RPC_FAR * This,
    /* [in] */ BSTR __RPC_FAR *pbstrKey,
    /* [in] */ enumARWriteHint hint,
    /* [retval][out] */ enumARStream __RPC_FAR *pVal);


void __RPC_STUB IARWriteStream_loadStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IARWriteStream_writeLine_Proxy( 
    IARWriteStream __RPC_FAR * This,
    /* [in] */ BSTR __RPC_FAR *pbstrKey,
    /* [retval][out] */ enumARStream __RPC_FAR *pVal);


void __RPC_STUB IARWriteStream_writeLine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IARWriteStream_get_StreamState_Proxy( 
    IARWriteStream __RPC_FAR * This,
    /* [retval][out] */ enumARStream __RPC_FAR *pVal);


void __RPC_STUB IARWriteStream_get_StreamState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IARWriteStream_closeStream_Proxy( 
    IARWriteStream __RPC_FAR * This,
    /* [retval][out] */ enumARStream __RPC_FAR *pVal);


void __RPC_STUB IARWriteStream_closeStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IARWriteStream_prepareLineWriteExtra_Proxy( 
    IARWriteStream __RPC_FAR * This,
    /* [in] */ enumARIODataType esType,
    /* [in] */ BSTR __RPC_FAR *pbstr,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IARWriteStream_prepareLineWriteExtra_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IARWriteStream_AddWatchObject_Proxy( 
    IARWriteStream __RPC_FAR * This,
    /* [in] */ IDispatch __RPC_FAR *pIDisp,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pOK);


void __RPC_STUB IARWriteStream_AddWatchObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IARWriteStream_SetDataSystem_Proxy( 
    IARWriteStream __RPC_FAR * This,
    /* [in] */ IDispatch __RPC_FAR *pIDisp,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pOK);


void __RPC_STUB IARWriteStream_SetDataSystem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IARWriteStream_INTERFACE_DEFINED__ */


#ifndef __IARDataStore_INTERFACE_DEFINED__
#define __IARDataStore_INTERFACE_DEFINED__

/* interface IARDataStore */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IARDataStore;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("511B72BC-0641-4BD9-ADB0-F0EFFA0EFD26")
    IARDataStore : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE tryToGetARStream( 
            /* [in] */ BSTR __RPC_FAR *pbstrKey,
            /* [in] */ enumARReadHint esrh,
            /* [retval][out] */ IARStream __RPC_FAR *__RPC_FAR *ppSymlixStream) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE doChecks( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pOK) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE isAvailable( 
            /* [in] */ BSTR __RPC_FAR *pbstrKey,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pOK) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE tryToGetARWriteStream( 
            /* [in] */ BSTR __RPC_FAR *pbstrKey,
            /* [in] */ enumARWriteHint eswh,
            /* [retval][out] */ IARWriteStream __RPC_FAR *__RPC_FAR *ppSymlixWriteStream) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE isAvailableForWrite( 
            /* [in] */ BSTR __RPC_FAR *pbstrKey,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pOK) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VersionDescription( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddWatchObject( 
            /* [in] */ IDispatch __RPC_FAR *pIDisp,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pOK) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDataSystem( 
            /* [in] */ IDispatch __RPC_FAR *pIDisp,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pOK) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IARDataStoreVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IARDataStore __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IARDataStore __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IARDataStore __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IARDataStore __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IARDataStore __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IARDataStore __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IARDataStore __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *tryToGetARStream )( 
            IARDataStore __RPC_FAR * This,
            /* [in] */ BSTR __RPC_FAR *pbstrKey,
            /* [in] */ enumARReadHint esrh,
            /* [retval][out] */ IARStream __RPC_FAR *__RPC_FAR *ppSymlixStream);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *doChecks )( 
            IARDataStore __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pOK);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *isAvailable )( 
            IARDataStore __RPC_FAR * This,
            /* [in] */ BSTR __RPC_FAR *pbstrKey,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pOK);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *tryToGetARWriteStream )( 
            IARDataStore __RPC_FAR * This,
            /* [in] */ BSTR __RPC_FAR *pbstrKey,
            /* [in] */ enumARWriteHint eswh,
            /* [retval][out] */ IARWriteStream __RPC_FAR *__RPC_FAR *ppSymlixWriteStream);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *isAvailableForWrite )( 
            IARDataStore __RPC_FAR * This,
            /* [in] */ BSTR __RPC_FAR *pbstrKey,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pOK);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Version )( 
            IARDataStore __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VersionDescription )( 
            IARDataStore __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddWatchObject )( 
            IARDataStore __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *pIDisp,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pOK);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetDataSystem )( 
            IARDataStore __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *pIDisp,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pOK);
        
        END_INTERFACE
    } IARDataStoreVtbl;

    interface IARDataStore
    {
        CONST_VTBL struct IARDataStoreVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IARDataStore_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IARDataStore_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IARDataStore_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IARDataStore_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IARDataStore_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IARDataStore_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IARDataStore_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IARDataStore_tryToGetARStream(This,pbstrKey,esrh,ppSymlixStream)	\
    (This)->lpVtbl -> tryToGetARStream(This,pbstrKey,esrh,ppSymlixStream)

#define IARDataStore_doChecks(This,pOK)	\
    (This)->lpVtbl -> doChecks(This,pOK)

#define IARDataStore_isAvailable(This,pbstrKey,pOK)	\
    (This)->lpVtbl -> isAvailable(This,pbstrKey,pOK)

#define IARDataStore_tryToGetARWriteStream(This,pbstrKey,eswh,ppSymlixWriteStream)	\
    (This)->lpVtbl -> tryToGetARWriteStream(This,pbstrKey,eswh,ppSymlixWriteStream)

#define IARDataStore_isAvailableForWrite(This,pbstrKey,pOK)	\
    (This)->lpVtbl -> isAvailableForWrite(This,pbstrKey,pOK)

#define IARDataStore_get_Version(This,pVal)	\
    (This)->lpVtbl -> get_Version(This,pVal)

#define IARDataStore_get_VersionDescription(This,pVal)	\
    (This)->lpVtbl -> get_VersionDescription(This,pVal)

#define IARDataStore_AddWatchObject(This,pIDisp,pOK)	\
    (This)->lpVtbl -> AddWatchObject(This,pIDisp,pOK)

#define IARDataStore_SetDataSystem(This,pIDisp,pOK)	\
    (This)->lpVtbl -> SetDataSystem(This,pIDisp,pOK)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IARDataStore_tryToGetARStream_Proxy( 
    IARDataStore __RPC_FAR * This,
    /* [in] */ BSTR __RPC_FAR *pbstrKey,
    /* [in] */ enumARReadHint esrh,
    /* [retval][out] */ IARStream __RPC_FAR *__RPC_FAR *ppSymlixStream);


void __RPC_STUB IARDataStore_tryToGetARStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IARDataStore_doChecks_Proxy( 
    IARDataStore __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pOK);


void __RPC_STUB IARDataStore_doChecks_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IARDataStore_isAvailable_Proxy( 
    IARDataStore __RPC_FAR * This,
    /* [in] */ BSTR __RPC_FAR *pbstrKey,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pOK);


void __RPC_STUB IARDataStore_isAvailable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IARDataStore_tryToGetARWriteStream_Proxy( 
    IARDataStore __RPC_FAR * This,
    /* [in] */ BSTR __RPC_FAR *pbstrKey,
    /* [in] */ enumARWriteHint eswh,
    /* [retval][out] */ IARWriteStream __RPC_FAR *__RPC_FAR *ppSymlixWriteStream);


void __RPC_STUB IARDataStore_tryToGetARWriteStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IARDataStore_isAvailableForWrite_Proxy( 
    IARDataStore __RPC_FAR * This,
    /* [in] */ BSTR __RPC_FAR *pbstrKey,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pOK);


void __RPC_STUB IARDataStore_isAvailableForWrite_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IARDataStore_get_Version_Proxy( 
    IARDataStore __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IARDataStore_get_Version_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IARDataStore_get_VersionDescription_Proxy( 
    IARDataStore __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IARDataStore_get_VersionDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IARDataStore_AddWatchObject_Proxy( 
    IARDataStore __RPC_FAR * This,
    /* [in] */ IDispatch __RPC_FAR *pIDisp,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pOK);


void __RPC_STUB IARDataStore_AddWatchObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IARDataStore_SetDataSystem_Proxy( 
    IARDataStore __RPC_FAR * This,
    /* [in] */ IDispatch __RPC_FAR *pIDisp,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pOK);


void __RPC_STUB IARDataStore_SetDataSystem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IARDataStore_INTERFACE_DEFINED__ */



#ifndef __ARSTORELib_LIBRARY_DEFINED__
#define __ARSTORELib_LIBRARY_DEFINED__

/* library ARSTORELib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_ARSTORELib;

EXTERN_C const CLSID CLSID_ARFileStream;

#ifdef __cplusplus

class DECLSPEC_UUID("75CC38D9-4877-41D3-B2D5-E7189446D593")
ARFileStream;
#endif

EXTERN_C const CLSID CLSID_ARFileDataStore;

#ifdef __cplusplus

class DECLSPEC_UUID("06BB7B0F-5B83-41DD-A6F9-13D787B79FA1")
ARFileDataStore;
#endif

EXTERN_C const CLSID CLSID_ARFileWriteStream;

#ifdef __cplusplus

class DECLSPEC_UUID("6A96EB6A-101A-4CE3-AA93-946D53AE76DC")
ARFileWriteStream;
#endif
#endif /* __ARSTORELib_LIBRARY_DEFINED__ */

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
