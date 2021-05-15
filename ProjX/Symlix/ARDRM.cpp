// ARDRM.cpp: implementation of the CARDRM class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ARDRM.h"
#include "../global.h"
#include "ErrorFactory.h"

// defintion of Armidillo function calls
typedef bool (__stdcall *UpdateEnvironmentFn)(void);
typedef bool (__stdcall *CallBuyNowURLFn)(HWND parentwindow);
typedef bool (__stdcall *InstallKeyFn)(const char *name, const char *code);
typedef bool (__stdcall *ShowEnterKeyDialogFn)(HWND parent);
typedef bool (__stdcall *VerifyKeyFn)(const char *name, const char *code);








//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CARDRM::CARDRM():m_bState(true),m_iDaysLeft(NOT_DEFINED),m_iTotalUses(NOT_DEFINED),m_bExpired(true),m_bVerified(false)
{

#ifdef DEBUGDRM
	m_os.open("c:\\temp\\traceDRM.txt");
#endif

	m_sUser = "Undefined";
	m_sKey = "Undefined";
	m_sFingerPrint = "";
	m_sEnhancedFingerPrint = "";

	DRMTRACE("About to call setArmadillPath()");
	if (setArmadilloPath())
		if (updateEnvironment())
		  {		   
			ATLTRACE("CARDRM constructed OK\n");
			m_bVerified = verifyStoredKey(); // also updates
			DRMTRACE(m_sUser.c_str());
			DRMTRACE(m_sKey.c_str());
			if (m_bVerified)
				{
				DRMTRACE("Key verified OK");
				}
				else
				{
				DRMTRACE("Key fails");
				m_bExpired = true;
				}
		  } // end if updateEnvironment

}




CARDRM::~CARDRM()
{

DRMTRACE1("CARDRM::~CARDRM() called",m_bState);
#ifdef DEBUGDRM
	m_os.close();
#endif

}

CARDRM* CARDRM::m_instance = 0;



CARDRM* CARDRM::instance() 
{ 

     if (!m_instance) m_instance = makeInstance();
                 return m_instance;
}    



///////////////////////////////////////////////////////////
// Function name	: CARDRM::updateEnvironment
// Description	    : Make sure all the enviroment values are up to date
// Return type		: bool 
///////////////////////////////////////////////////////////
bool CARDRM::updateEnvironment()
{
	bool bResult = true;
	HINSTANCE libInst=LoadLibrary(m_sDLLLocation.c_str());

	DRMTRACE1("start CARDRM::updateEnvironment()",m_bState);


    if (!libInst)
		 {
			ATLTRACE("<Error> Unable to load ArmAccess.dll %s %d\n",__FILE__,__LINE__);
			#ifdef SOFTWAREPASSPORT
			SYMERRORLITE("Unable to load ArmAccess.dll",errSystem);
			#endif
			m_bState=false;
			DRMTRACE1("end updateEnvironment after ArmAccess.dll failed to load",m_bState);
			return false;
		 }
					   /* Substitute the typedefs above for functions other than InstallKey */

	UpdateEnvironmentFn fUpdateEnvironment=(UpdateEnvironmentFn)GetProcAddress(libInst, "UpdateEnvironment");

	if (fUpdateEnvironment!=0)
					{
					fUpdateEnvironment();


						  { // start get user name data
							 char sName[256]="", sKey[256]="";
						  
							   if (!GetEnvironmentVariable("ALTUSERNAME", sName, 255)) {

										ATLTRACE("<Error> Unable to find username data %s %d\n",__FILE__,__LINE__);
			#ifdef SOFTWAREPASSPORT
										SYMERRORLITE("Unable to identify username data",errSystem);
			#endif
   										m_bState=false;
										m_sUser = "Not found";
										DRMTRACE1("m_bState set to false after ALTUSERNAME call failure",m_bState);

									   }
									   else
									   {
									   m_sUser = sName;
									   if (!GetEnvironmentVariable("USERKEY", sKey, 255)) strcpy(sKey, "No key!");

									   m_sKey = sKey;
									   }

						  }	// end get username data   		

							char sMessage[256]="";
						
						  { // start get expired flag


							if (!GetEnvironmentVariable("EXPIRED", sMessage, 255 ))
									{
										ATLTRACE("<Warning> Unable to find username data %s %d\n",__FILE__,__LINE__);
										//SYMERRORLITE("Unable to identify username data",errSystem);
   										//m_bState=false;
										DRMTRACE1("m_bState set to false after EXPIRED call failure",m_bState);
										m_bExpired = false; // need to check this is right
									}
									else
									{
									if (strcmp(sMessage,"True")==0)
												m_bExpired = false;
												else
												m_bExpired = true;
									}


						  } // end get expired flag
						
						  { // start get days left
							if (!GetEnvironmentVariable("DAYSLEFT", sMessage, 255 ))
									{
										ATLTRACE("<Warning> Unable to find DAYSLEFT data %s %d\n",__FILE__,__LINE__);
										//SYMERRORLITE("Unable to identify DAYSLEFT data",errSystem);
   										//m_bState=false;
										DRMTRACE1("m_bState set to false after DAYSLEFT call failure",m_bState);
										m_bDaysLeft = false;
										m_iDaysLeft = -1;
									}
									else
									{
									if (sMessage[0]==NULL)
										{
										m_bDaysLeft = false;
										m_iDaysLeft = -1;
										}
										else
										{
										m_bDaysLeft = true;
										m_iDaysLeft = atol(sMessage);
										}

									}

						  } // end days left

						  { // start get days left
							if (!GetEnvironmentVariable("TOTALUSES", sMessage, 255 ))
									{
										ATLTRACE("<Error> Unable to find TOTALUSES data %s %d\n",__FILE__,__LINE__);
			#ifdef SOFTWAREPASSPORT
										SYMERRORLITE("Unable to identify TOTALUSES data",errSystem);
			#endif
   										m_bState=false;
										DRMTRACE1("m_bState set to false after TOTALUSES call failure",m_bState);
									}
									else
									{
									if (sMessage[0]==NULL)
										m_iTotalUses = -1;
										else
										m_iTotalUses = atol(sMessage);

									}

						  } // end days left

						  { // start get finger print
							if (!GetEnvironmentVariable("FINGERPRINT", sMessage, 255 ))
									{
										ATLTRACE("<Error> Unable to find FINGERPRINT data %s %d\n",__FILE__,__LINE__);
			#ifdef SOFTWAREPASSPORT
										SYMERRORLITE("Unable to identify FINGERPRINT data",errSystem);
			#endif
   										m_bState=false;
										DRMTRACE1("m_bState set to false after FINGERPRINT call failure",m_bState);
									}
									else
									{
									if (sMessage[0]==NULL)
										m_sFingerPrint = "";
										else
										m_sFingerPrint = sMessage;

									}

						  } // end finger print

						  { // start get finger print
							if (!GetEnvironmentVariable("ENHFINGERPRINT", sMessage, 255 ))
									{
										ATLTRACE("<Error> Unable to find ENHFINGERPRINT data %s %d\n",__FILE__,__LINE__);
			#ifdef SOFTWAREPASSPORT
										SYMERRORLITE("Unable to identify ENHFINGERPRINT data",errSystem);
			#endif
   										m_bState=false;
										DRMTRACE1("m_bState set to false after ENHFINGERPRINT call failure",m_bState);
									}
									else
									{
									if (sMessage[0]==NULL)
										m_sEnhancedFingerPrint = "";
										else
										m_sEnhancedFingerPrint = sMessage;

									}

						  } // end finger print




					}
					else
					{
					ATLTRACE("<Error> Unable to update DRM environment %s %d\n",__FILE__,__LINE__);
			#ifdef SOFTWAREPASSPORT
					SYMERRORLITE("Unable to update DRM environment",errSystem);
			#endif
					bResult = false;
					}
	DRMTRACE1("End of CARDRM::updateEnvironment()",m_bState);

	FreeLibrary(libInst); /* Not needed for the virtual ArmAccess.DLL, but it won't hurt anything. */
	return bResult;
}

///////////////////////////////////////////////////////////
// Function name	: CARDRMgetEnvironmentValue
// Description	    : Find a specified enviromnent variable
// Return type		: string 
// Argument         : const char* sEnvKey
///////////////////////////////////////////////////////////
string CARDRM::getEnvironmentValue(const char* sEnvKey) const
{
	char sMessage[256]=""; 

	if (!GetEnvironmentVariable(sEnvKey, sMessage, 255 ))
					{
						ATLTRACE("<Error> Unable to find %s data %s %d\n",sEnvKey,__FILE__,__LINE__);
			#ifdef SOFTWAREPASSPORT
						SYMERRORLITE2("Unable to identify enviroment data for ",sEnvKey,errSystem);
			#endif
						return "<Not Found>";
					}
					else
					{
					if (sMessage[0]==NULL)
						return "";
					}

	return sMessage;

}

///////////////////////////////////////////////////////////
// Function name	: CARDRM::makeInstance
// Description	    : 
// Return type		: CARDRM* 
///////////////////////////////////////////////////////////
CARDRM* CARDRM::makeInstance()
{
    atexit(&cleanupInstance);
    return (newtrack CARDRM);
}


///////////////////////////////////////////////////////////
// Function name	: CARDRM::cleanupInstance
// Description	    : 
// Return type		: void 
///////////////////////////////////////////////////////////
void CARDRM::cleanupInstance()
{ 

   delete m_instance;
   m_instance = 0;
}


///////////////////////////////////////////////////////////
// Function name	: CARDRM::callBuyNowURL
// Description	    : Call the BuyNow URL ( embedded in the Software Passport wrapper )
// Return type		: void 
// Argument         : HWND parent = NULL
///////////////////////////////////////////////////////////
void CARDRM::callBuyNowURL(HWND parent /*=NULL*/ ) const
{

  HINSTANCE libInst=LoadLibrary(m_sDLLLocation.c_str());

  if (!libInst)
			{
			ATLTRACE("<Error> Unable to load ArmAccess.dll %s line %d\n",__FILE__,__LINE__);
			return;
			}
					   /* Substitute the typedefs above for functions other than InstallKey */

			CallBuyNowURLFn fCallBuyNowURL=(CallBuyNowURLFn)GetProcAddress(libInst, "CallBuyNowURL");

			if (fCallBuyNowURL!=0)
						fCallBuyNowURL(NULL);
						else
						{
						ATLTRACE("<Error> Unable to call CallBuyNowURL %s line %d\n",__FILE__,__LINE__);
						}

  FreeLibrary(libInst); /* Not needed for the virtual ArmAccess.DLL, but it won't hurt anything. */

}


///////////////////////////////////////////////////////////
// Function name	: CARDRM::showEnterKeyDialog
// Description	    : Open the Software Passport key entry dialog
// Return type		: void 
// Argument         : HWND parent
///////////////////////////////////////////////////////////
void CARDRM::showEnterKeyDialog(HWND parent) const
{

  HINSTANCE libInst=LoadLibrary(m_sDLLLocation.c_str());

  if (!libInst)
			{
			ATLTRACE("<Error> Unable to load ArmAccess.dll %s line %d\n",__FILE__,__LINE__);
			return;
			}
					   /* Substitute the typedefs above for functions other than InstallKey */

			ShowEnterKeyDialogFn fShowEnterKeyDialog=(CallBuyNowURLFn)GetProcAddress(libInst, "ShowEnterKeyDialog");

			if (fShowEnterKeyDialog!=0)
						fShowEnterKeyDialog(parent);
						else
						{
						ATLTRACE("<Error> Unable to call ShowEnterKeyDialog %s line %d\n",__FILE__,__LINE__);
						}

  FreeLibrary(libInst); /* Not needed for the virtual ArmAccess.DLL, but it won't hurt anything. */

}

///////////////////////////////////////////////////////////
// Function name	: CARDRM::InstallCode
// Description	    : Install a new user name and code
// Return type		: bool 
// Argument         : const char *sName
// Argument         : const char *sCodestring
///////////////////////////////////////////////////////////
bool CARDRM::installCode(const char *sName, const char *sCodestring)
{

       int returnvalue=0;

       HINSTANCE libInst=LoadLibrary(m_sDLLLocation.c_str());

	  if (!libInst)
				{
				ATLTRACE("<Error> Unable to load ArmAccess.dll %s line %d\n",__FILE__,__LINE__);
				return false;
				}

       /* Substitute the typedefs above for functions other than InstallKey */

       InstallKeyFn InstallKey=(InstallKeyFn)GetProcAddress(libInst, "InstallKey");

       if (InstallKey==0)
				{
				ATLTRACE("<Error> Unable to load InstallKey function %s line %d\n",__FILE__,__LINE__);
				SYMERRORLITE("Unable to load user name and key",errSystem);
				return false;
				}
				else
				returnvalue=InstallKey(sName, sCodestring);

	   if (returnvalue!=0)
				{
				m_sUser = sName;
				m_sKey = sCodestring;
				}

       FreeLibrary(libInst); /* Not needed for the virtual ArmAccess.DLL, but it won't hurt anything. */

	   updateEnvironment();

       return (returnvalue!=0);





}


///////////////////////////////////////////////////////////
// Function name	: CARDRM::setArmadilloPath
// Description	    : Helper function to locate NumCat.dll and therefore ArmAccess.dll
// Return type		: bool 
///////////////////////////////////////////////////////////
bool CARDRM::setArmadilloPath()
{

	#define STR_LENGTH 250 
    #define SYMNAME 10 // then length of "Symlix.dll"

//	char szMessage[STR_LENGTH+2];
	char szRegValue[STR_LENGTH];
	DWORD dwLen = STR_LENGTH-2;
	long iLen;

	CRegKey crLicenseDLL;
	long iR = crLicenseDLL.Open(HKEY_CLASSES_ROOT,TEXT("CLSID\\{8F086AA2-30F8-4480-A04A-9623134E4EB2}\\InprocServer32"),KEY_READ);

	if (iR != ERROR_SUCCESS)
		{
		#ifdef SOFTWAREPASSPORT
         SYMERRORLITE("Unable to find registration information in registry.",errSystem);
		 SYMERRORLITE("Ensure installed files have not been moved, if necessary rerun installation.",errWarning);
		 #endif
		 return false;
		}

	iR = crLicenseDLL.QueryValue(szRegValue,"",&dwLen);

	if (iR != ERROR_SUCCESS)
		{
		 #ifdef SOFTWAREPASSPORT
         SYMERRORLITE("Unable to find a DRM related registry key.",errSystem);
		 SYMERRORLITE("Re-running the installation program may help.",errWarning);
		 #endif
		 crLicenseDLL.Close();
		 return false;
		}
	ATLTRACE(szRegValue);
	ATLTRACE("\n");

	iLen = strlen(szRegValue);
	// test for iLen being less than SYMNAME long
	if (iLen<=SYMNAME)
		{
         SYMERRORLITE("Unable to find registration information in registry.",errSystem);
		 SYMERRORLITE2("A registry key has an unexpected value:",szRegValue,errWarning);
		 crLicenseDLL.Close();
		 return false;
		}

	m_sDLLLocation = szRegValue;
	m_sDLLLocation = m_sDLLLocation.substr(0,iLen-SYMNAME);
	//ATLTRACE(sDLLLocation.c_str());
	m_sDLLLocation.append("ArmAccess.dll");

	crLicenseDLL.Close();

	return true;
}


///////////////////////////////////////////////////////////
// Function name	: CARDRM::verifyStoredKey
// Description	    : Verify the key stored internally
// Return type		: bool 
///////////////////////////////////////////////////////////
bool CARDRM::verifyStoredKey()
{
	return verifyKey(m_sUser.c_str(),m_sKey.c_str());
}

bool CARDRM::verifyKey(const char *sUser, const char *sKey)
{
       int returnvalue=0;

	   DRMTRACE("Passed values below:");
	   DRMTRACE3("sUser",sUser);
	   DRMTRACE3("sKey",sKey);

       HINSTANCE libInst=LoadLibrary(m_sDLLLocation.c_str());

	  if (!libInst)
				{
				ATLTRACE("<Error> Unable to load ArmAccess.dll %s line %d\n",__FILE__,__LINE__);
				DRMTRACE("<Error> Unable to load ArmAccess.dll in VerifyKey()");
				return false;
				}


       VerifyKeyFn fVerifyKey=(VerifyKeyFn)GetProcAddress(libInst, "VerifyKey");

       if (fVerifyKey==0)
				{
				ATLTRACE("<Error> Unable to load VerifyKey function %s line %d\n",__FILE__,__LINE__);
				DRMTRACE("<Error> Unable to load VerifyKey function in VerifyKey()");
				SYMERRORLITE("Unable to check user name and key",errSystem);
				return false;
				}
				else
				returnvalue=fVerifyKey(sUser, sKey);

       FreeLibrary(libInst); /* Not needed for the virtual ArmAccess.DLL, but it won't hurt anything. */

	   updateEnvironment();

	   DRMTRACE2("Key process has worked OK - returned value ",returnvalue );

	 return (returnvalue!=0);
}
