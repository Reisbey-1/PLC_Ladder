

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 06:14:07 2038
 */
/* Compiler settings for Ladder.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.01.0622 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __Ladder_i_h__
#define __Ladder_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __Ildr_FWD_DEFINED__
#define __Ildr_FWD_DEFINED__
typedef interface Ildr Ildr;

#endif 	/* __Ildr_FWD_DEFINED__ */


#ifndef __ldr_FWD_DEFINED__
#define __ldr_FWD_DEFINED__

#ifdef __cplusplus
typedef class ldr ldr;
#else
typedef struct ldr ldr;
#endif /* __cplusplus */

#endif 	/* __ldr_FWD_DEFINED__ */


/* header files for imported files */
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __Ildr_INTERFACE_DEFINED__
#define __Ildr_INTERFACE_DEFINED__

/* interface Ildr */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_Ildr;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2B946F2C-FB4A-415F-B395-FF173735FACA")
    Ildr : public IDispatch
    {
    public:
    };
    
    
#else 	/* C style interface */

    typedef struct IldrVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            Ildr * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            Ildr * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            Ildr * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            Ildr * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            Ildr * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            Ildr * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            Ildr * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } IldrVtbl;

    interface Ildr
    {
        CONST_VTBL struct IldrVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define Ildr_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define Ildr_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define Ildr_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define Ildr_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define Ildr_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define Ildr_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define Ildr_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __Ildr_INTERFACE_DEFINED__ */



#ifndef __LadderLib_LIBRARY_DEFINED__
#define __LadderLib_LIBRARY_DEFINED__

/* library LadderLib */
/* [helpstring][version][uuid] */ 

typedef /* [uuid] */  DECLSPEC_UUID("3A47444F-91FF-4602-A403-4F9311669A18") 
enum tagDS
    {
        LINE	= 1,
        HORVER	= ( LINE + 1 ) ,
        VERHOR	= ( HORVER + 1 ) 
    } 	DS;

typedef /* [uuid] */  DECLSPEC_UUID("0B064B6B-C58B-44f5-9837-4A77A30C8243") 
enum tagDC
    {
        CONTEX_NONE	= 0,
        CONTEX_TIMER	= ( CONTEX_NONE + 1 ) ,
        CONTEX_COUNTER	= ( CONTEX_TIMER + 1 ) ,
        CONTEX_MEMORY	= ( CONTEX_COUNTER + 1 ) ,
        CONTEX_AND	= ( CONTEX_MEMORY + 1 ) ,
        CONTEX_AND2	= ( CONTEX_AND + 1 ) ,
        CONTEX_OR2	= ( CONTEX_AND2 + 1 ) 
    } 	DC;

typedef /* [uuid] */  DECLSPEC_UUID("494B2223-146E-4898-AB05-434790FC9123") 
enum tagDM
    {
        DRAW	= 0,
        REFRESH	= ( DRAW + 1 ) ,
        HIGHLIGTH	= ( REFRESH + 1 ) 
    } 	DM;

typedef /* [uuid] */  DECLSPEC_UUID("FC5502CC-BC18-4cae-B591-BBDD3A1C0D90") 
enum tagSNT
    {
        NET_0	= 0,
        NET_1	= 1,
        NET_2	= 2,
        NET_3	= 3,
        NET_4	= 4,
        NET_5	= 5,
        NET_6	= 6,
        NET_7	= 7,
        NET_8	= 8,
        NET_9	= 9,
        NET_10	= 10,
        NET_11	= 11,
        NET_12	= 12,
        NET_13	= 13,
        NET_14	= 14,
        NET_15	= 15,
        SUB_NET_CONTACTOR	= NET_15,
        NET_30	= 30,
        SUB_NET_BLOCK	= NET_30,
        NET_45	= 45,
        SUB_NET_BLOCK_	= NET_45,
        NET_60	= 15,
        SUB_NET_FUNCTION	= NET_60,
        NET_85	= 85,
        SUB_NET_FUNCTION_	= NET_85,
        NET_90	= 90,
        SUB_NET_LIST	= NET_90,
        NET_105	= 105,
        SUB_NET_LIST_	= NET_105,
        NET_120	= 120,
        NET_BLOCK_SHALT	= NET_120
    } 	SNT;

typedef /* [uuid] */  DECLSPEC_UUID("EC037F5B-EA90-4e34-AB1B-366D258B9C20") 
enum tagERT
    {
        OUTPUT	= 0,
        BIT	= ( OUTPUT + 1 ) ,
        MEMORY	= ( BIT + 1 ) ,
        TIMER	= ( MEMORY + 1 ) ,
        COUNTER	= ( TIMER + 1 ) ,
        INPUt	= ( COUNTER + 1 ) ,
        BLOCK	= ( INPUt + 1 ) ,
        FUNCTION	= ( BLOCK + 1 ) ,
        LIST	= ( FUNCTION + 1 ) ,
        ANALOGINPUT	= ( LIST + 1 ) ,
        ANALOGOUTPUT	= ( ANALOGINPUT + 1 ) ,
        nill	= ( ANALOGOUTPUT + 1 ) ,
        SUBROUTINE	= ( nill + 1 ) ,
        ALL	= ( SUBROUTINE + 1 ) ,
        COUNT_ERT	= ( ALL + 1 ) ,
        START	= ( COUNT_ERT + 1 ) 
    } 	ERT;

typedef /* [uuid] */  DECLSPEC_UUID("99BEEFAF-CF5F-40c7-B9A2-92A6DDB5A32E") 
enum tagET
    {
        TYPE_LINE	= 0,
        TYPE_POINT	= ( TYPE_LINE + 1 ) ,
        TYPE_ELEMENT	= ( TYPE_POINT + 1 ) ,
        TYPE_CONTACTOR	= ( TYPE_ELEMENT + 1 ) ,
        TYPE_OUTPUT	= ( TYPE_CONTACTOR + 1 ) ,
        TYPE_START	= ( TYPE_OUTPUT + 1 ) ,
        TYPE_END	= ( TYPE_START + 1 ) ,
        TYPE_INVCONTACTOR	= ( TYPE_END + 1 ) ,
        TYPE_TIMER	= ( TYPE_INVCONTACTOR + 1 ) ,
        TYPE_COUNTER	= ( TYPE_TIMER + 1 ) ,
        TYPE_BLOCK	= ( TYPE_COUNTER + 1 ) ,
        TYPE_FUNCTION	= ( TYPE_BLOCK + 1 ) ,
        TYPE_LIST	= ( TYPE_FUNCTION + 1 ) ,
        TYPE_MEMORY	= ( TYPE_LIST + 1 ) ,
        TYPE_ON	= ( TYPE_MEMORY + 1 ) ,
        TYPE_OFF	= ( TYPE_ON + 1 ) ,
        TYPE_INVERT	= ( TYPE_OFF + 1 ) ,
        TYPE_AND	= ( TYPE_INVERT + 1 ) ,
        TYPE_OR	= ( TYPE_AND + 1 ) ,
        TYPE_IN	= ( TYPE_OR + 1 ) ,
        TYPE_OUT	= ( TYPE_IN + 1 ) ,
        TYPE_POINT2	= ( TYPE_OUT + 1 ) ,
        TYPE_BUFFER	= ( TYPE_POINT2 + 1 ) ,
        TYPE_TEXT	= ( TYPE_BUFFER + 1 ) ,
        TYPE_SUBROUTINE	= ( TYPE_TEXT + 1 ) ,
        TYPE_REGISTER	= ( TYPE_SUBROUTINE + 1 ) ,
        TYPE_LIST2	= ( TYPE_REGISTER + 1 ) ,
        TYPE_AND2	= ( TYPE_LIST2 + 1 ) ,
        TYPE_OR2	= ( TYPE_AND2 + 1 ) 
    } 	ET;

typedef /* [uuid] */  DECLSPEC_UUID("83003D89-1499-497d-A104-9F2E11CEB8FA") 
enum tagCT
    {
        CNTtoCNT	= 0,
        CNTtoPRE	= ( CNTtoCNT + 1 ) ,
        CNTtoPAS	= ( CNTtoPRE + 1 ) ,
        PREtoCNT	= ( CNTtoPAS + 1 ) ,
        PREtoPRE	= ( PREtoCNT + 1 ) ,
        PREtoPAS	= ( PREtoPRE + 1 ) ,
        PAStoCNT	= ( PREtoPAS + 1 ) ,
        PAStoPRE	= ( PAStoCNT + 1 ) ,
        PAStoPAS	= ( PAStoPRE + 1 ) ,
        UNKNOWN	= ( PAStoPAS + 1 ) 
    } 	CT;

typedef /* [uuid] */  DECLSPEC_UUID("D768AAF0-3D74-4eb2-999E-16EC4A0AD045") 
enum tagMT
    {
        CNT	= 1,
        PRE	= ( CNT + 1 ) ,
        PAS	= ( PRE + 1 ) ,
        SET	= ( PAS + 1 ) ,
        RST	= ( SET + 1 ) ,
        QPT	= ( RST + 1 ) ,
        P01	= ( QPT + 1 ) ,
        P02	= ( P01 + 1 ) ,
        P03	= ( P02 + 1 ) ,
        P04	= ( P03 + 1 ) ,
        P05	= ( P04 + 1 ) ,
        P06	= ( P05 + 1 ) ,
        PBASE	= ( P06 + 1 ) ,
        OHP	= 30,
        MAX_AND_SIZE	= 17
    } 	MT;

typedef /* [uuid] */  DECLSPEC_UUID("6F9DC39F-65E8-4186-B3AE-9A44BBD5FF45") 
enum tagTIMERMODES
    {
        TIMER_MODE_0	= 0,
        TIMER_MODE_1	= ( TIMER_MODE_0 + 1 ) ,
        TIMER_MODE_2	= ( TIMER_MODE_1 + 1 ) ,
        TIMER_MODE_3	= ( TIMER_MODE_2 + 1 ) ,
        TIMER_MODE_4	= ( TIMER_MODE_3 + 1 ) ,
        TIMER_MODE_5	= ( TIMER_MODE_4 + 1 ) ,
        TIMER_MODE_6	= ( TIMER_MODE_5 + 1 ) ,
        TIMER_MODE_7	= ( TIMER_MODE_6 + 1 ) 
    } 	TIMERMODES;

typedef /* [uuid] */  DECLSPEC_UUID("1F28A899-1B57-41d4-AB6A-3ABBA2D8A8B6") 
enum tagMEMORYMODES
    {
        MEMORY_MODE_0	= 0,
        MEMORY_MODE_1	= ( MEMORY_MODE_0 + 1 ) ,
        MEMORY_MODE_2	= ( MEMORY_MODE_1 + 1 ) ,
        MEMORY_MODE_3	= ( MEMORY_MODE_2 + 1 ) ,
        MEMORY_MODE_4	= ( MEMORY_MODE_3 + 1 ) ,
        MEMORY_MODE_5	= ( MEMORY_MODE_4 + 1 ) 
    } 	MEMORYMODES;

typedef /* [uuid] */  DECLSPEC_UUID("7C172763-4CFD-4bd9-9C97-A1EBA3D2F17D") 
enum tagCOUNTERMODES
    {
        COUNTER_MODE_UP	= 0,
        COUNTER_MODE_DOWN	= ( COUNTER_MODE_UP + 1 ) 
    } 	COUNTERMODES;


EXTERN_C const IID LIBID_LadderLib;

EXTERN_C const CLSID CLSID_ldr;

#ifdef __cplusplus

class DECLSPEC_UUID("35FEF323-EADA-4003-82A3-E803EE985DEE")
ldr;
#endif
#endif /* __LadderLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


