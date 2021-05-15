/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Jun 06 18:10:40 2012
 */
/* Compiler settings for C:\Inetpub\ftproot\cpp_new\ProjX\ARExcelFuncs\ARExcelFuncs.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID IID_IARFuncs = {0xED20BD27,0x82D1,0x4D80,{0xBA,0x33,0x01,0xDE,0x6E,0x5E,0x10,0x7C}};


const IID LIBID_AREXCELFUNCSLib = {0xDC44711E,0xB32A,0x4FA5,{0xAE,0xB3,0x9C,0xF2,0x99,0x87,0xE8,0xED}};


const CLSID CLSID_ARFuncs = {0xA0FC5F62,0x9BB3,0x4430,{0x87,0xFF,0x20,0xDB,0xC8,0x12,0xBB,0x29}};


const CLSID CLSID_ARExcelStream = {0xC18BB11A,0x5500,0x4B46,{0x8B,0x44,0xAA,0x2D,0x8F,0xF2,0x81,0xE4}};


#ifdef __cplusplus
}
#endif

