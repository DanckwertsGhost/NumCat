/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Oct 06 16:53:51 2008
 */
/* Compiler settings for C:\Inetpub\ftproot\cpp_new\TraceRecorder\TraceRecorder.idl:
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

const IID IID_IARTrace = {0x482B95D2,0x2025,0x4807,{0x87,0xBF,0xCF,0x8D,0x0E,0xE2,0xA9,0xB9}};


const IID LIBID_TRACERECORDERLib = {0x282F06FA,0xB067,0x4304,{0xB9,0xDD,0x23,0x54,0xF4,0x7D,0x59,0x4E}};


const CLSID CLSID_ARTrace = {0xC5F62AAA,0x494E,0x4786,{0xB6,0x42,0x1D,0x85,0xCE,0xF6,0x8F,0x1C}};


#ifdef __cplusplus
}
#endif

