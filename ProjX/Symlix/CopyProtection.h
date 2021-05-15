
//#ifndef NDEBUG
//#define LOADDLL LoadLibrary("C:\\Program Files\\Symlix\\filechck.dll")
//#else
#define LOADDLL LoadLibrary("filechck.dll")
//#endif

#include <stdlib.h>
#include <time.h>


//*******************************************************************//
//*																	*//
//*			Required header file with library functions named		*//
//*			and return code definitions.							*//
//*																	*//
//*			Versions 5-6 Header (C) Nalpeiron Ltd/Inc. 2009			*//
//*					Version 6.0		June 11th 2009					*//
//*																	*//
//*			File modified for Numerical catalysts                   *//
//*																	*//
//*******************************************************************//


#ifndef __CPROTUTIL_H
#define __CPROTUTIL_H

#include <windows.h>

#ifndef __CPROTUTIL__
	#define __CPROTUTILLIB__  // __declspec(dllimport)
#else
	#define __CPROTUTILLIB__  __declspec(dllexport)
#endif

#ifdef __cplusplus
extern "C" {
#endif


//*******************************************************************//
//*																	*//
//*			The following list of functions are the API				*//
//*			functions stored in the custom DLL.						*//
//*																	*//
//*******************************************************************//




__CPROTUTILLIB__ int WINAPI CheckFlags(long *ModuleNumber);
   // returns the contents of the flag table entry

__CPROTUTILLIB__ int WINAPI ViewExpirationDate(long *Month, long *Day, long *Year);
	// returns the expiration date

__CPROTUTILLIB__ int WINAPI CheckLicense(long *RandomNumber);
	//multipurpose - most important routine for publisher

__CPROTUTILLIB__ int WINAPI AuditLicense(long *RandomNumber);
	//Gets the license status WIHOUT having to deal with X, Y, and Z values

__CPROTUTILLIB__ int WINAPI DisplayInstallationID(char *szCodeInfo);
   // returns 10-character string

__CPROTUTILLIB__ int WINAPI GetComputerID(char *szpComputerID);
   // returns a unique ID for this computer

__CPROTUTILLIB__ void WINAPI DisplayVersion();
   // returns copyright notice and version number

__CPROTUTILLIB__ int WINAPI ReturnVersion();
	// returns the version number as a 3 digit number i.e. 2.7.0 returns 270

__CPROTUTILLIB__ int WINAPI ValidateDLL(long *CustomerNumber, long *ProductNumber, long *ParmValue);

   // returns true if DLL matches customer number and last 5 digits of product ID

__CPROTUTILLIB__ int WINAPI InstallLicense(char *szUnlockCode);
   // updates the table with new program entry if legitimate

__CPROTUTILLIB__ int WINAPI InitializeMedia(char *szDriveLetter);
   // writes out the site code to a drive

__CPROTUTILLIB__ int WINAPI RemoveToMedia(char *szDriveLetter);
   // writes the proof of removal code to a drive as well as the corresponding site code

__CPROTUTILLIB__ int WINAPI InstallFromMedia(char *szDriveLetter);
   // looks for a valid proof of removal code/site code then provides

__CPROTUTILLIB__ int WINAPI InternetActivate(char *szLicenseCode, char *szpProxyPort, int PortNumber);
   // updates the table with new program entry if legitimate

__CPROTUTILLIB__ int WINAPI ReturnLicense(char *szLicenseCode, char *szpProxyPort, int PortNumber);
   //  returns license to web server, and removes authorization

__CPROTUTILLIB__ int WINAPI RemoveLicense(char *szpRemovalCode);
   // sets status code to 0 in the program's table entry

__CPROTUTILLIB__ int WINAPI ViewUses(long *UsesNum);
   // returns the number of uses available

__CPROTUTILLIB__ int WINAPI SubtractUses(long *Uses, long *UsesNum);
   // checks to see if authorized and has any remaining uses.
   // if so, decrements remaining uses and returns that to caller

__CPROTUTILLIB__ int WINAPI GetGeneralPurpose(long *Value);
	//Gets the General Purpose Value

__CPROTUTILLIB__ int WINAPI PutGeneralPurpose(long *Value,long *RandomNumber,long *Checksum);
	//Stores the General Purpose Value

// Demo Minutes Start - Messsage and caption variables are UNICODE
__CPROTUTILLIB__ int WINAPI StartDemo(wchar_t *szMessage, wchar_t *szCaption);

__CPROTUTILLIB__ int WINAPI StartDemoAdvanced(char *szProcess);

__CPROTUTILLIB__ int WINAPI EndDemo();		// Demo Minutes Stop using up demo minutes

__CPROTUTILLIB__ int WINAPI UpdateTime();	// Demo Minutes Update to the hard drive the number of minutes used.

__CPROTUTILLIB__ int WINAPI ViewTime();

__CPROTUTILLIB__ int WINAPI ExportLicense(char *szpLicenseNumber, char *szpReturnCode);
   //  This allows manually returning the license to the server

__CPROTUTILLIB__ int WINAPI GetHostName(char *szHostName);
   //	Return the domain name of the activation server.

__CPROTUTILLIB__ void WINAPI WaitForFinish();
   //	Waits for open threads to finish

__CPROTUTILLIB__ int WINAPI GetActivationMethod();
   //	Returns an integer indicating the method last used to activate the product
   //	See the list of Activation Method constants below

__CPROTUTILLIB__ int WINAPI UsesLicenseCertificate();
   //	Returns 1 if the flag for using license certificates is set; 0 otherwise

__CPROTUTILLIB__ int WINAPI EnterAuthenticationInformation(
								const char *szpProxyUsername,
								const char *szpProxyPassword);
   //	Sets proxy authentication information for proxy servers that require such


__CPROTUTILLIB__ int WINAPI StartTheService();
	// Starts the Nalpeiron Service associated with custom DLL

__CPROTUTILLIB__ int WINAPI StopTheService();
	// Stops the Nalpeiron Service associated with custom DLL





//*******************************************************************//
//*																	*//
//*			CheckAuthorization() is a Nalpeiron-provided			*//
//*			function that calls ValidateDLL and CheckLicense		*//
//*			and handles all return values.							*//
//*																	*//
//*******************************************************************//



int	CheckAuthorization();

 

/***** return codes  *****/

#define CPROT_OK										0
#define	CPROT_PRODUCT_AUTHORIZED						10000
#define CPROT_MISSING_PARM								-1
#define CPROT_BAD_PARM									-2
#define CPROT_BAD_UNLOCK_CODE							-3
#define CPROT_PRODUCT_NOT_AUTHORIZED					-4
#define CPROT_DEMO_EXPIRED								-5
#define CPROT_EVAL_USES_EXPIRED							-6
#define CPROT_LEASE_EXPIRED								-7
#define CPROT_USES_EXHAUSTED							-8
#define	CPROT_OPEN_DRIVE_FAILURE						-9
#define	CPROT_CANNOT_FIND_HARD_DRIVE					-10
#define CPROT_SERVICE_INSTALL_FAILED					-11
#define CPROT_SERVICE_FAILURE							-12
#define	CPROT_HARDDRIVE_READ_FAILURE					-13
#define	CPROT_HARDDRIVE_WRITE_FAILURE					-14
#define	CPROT_NO_ROOM_FOR_ENTRY							-15
#define CPROT_FIND_ENTRY_FAILURE						-16
#define	CPROT_ERROR_GETTING_UNLOCKING_CODE				-19
#define	CPROT_INVALID_LICENSE_NUMBER					-20
#define CPROT_INVALID_INSTALLATION_ID					-21
#define CPROT_WRONG_LICENSE_NUMBER						-22
#define	CPROT_LICENSE_NUMBER_ALREADY_USED				-23
#define	CPROT_CANNOT_ACCESS_WEB_SITE					-24
#define CPROT_CONCURRENT_USERS_EXCEEDED					-25
#define CPROT_UNABLE_TO_READ_FROM_MEDIA					-26
#define CPROT_UNABLE_TO_WRITE_TO_MEDIA					-27
#define CPROT_INVALID_MEDIA_DATA						-28
#define CPROT_LICENSE_ALREADY_INSTALLED					-29
#define	CPROT_UNKNOWN_ERROR								-30
#define CPROT_INAPPROPRIATE_FUNCTION_CALL				-31
#define CPROT_LICENSE_ALREADY_RETURNED					-32
#define CPROT_DLL_NOT_CUSTOMIZED						-33
#define CPROT_UNDEFINED_LICENSE_CONDITION				-34
#define CPROT_SUBTRACTION_AMOUNT_GREATER_THAN_USES		-35
#define CPROT_USER_IS_CHANGING_DATE						-36
#define CPROT_NO_DRIVE_PRESENT							-37
#define CPROT_NOT_INITIALIZED							-38
#define CPROT_WRITE_DOES_NOT_VERIFY						-55
#define CPROT_UNABLE_VERIFY_WRITE						-56
#define CPROT_FUNCTION_NOT_ALLOWED						-59
#define CPROT_SERVICE_MISSING							-63
#define CPROT_ERROR_GETTING_DISK_SPECIFICATIONS			-64
#define	CPROT_SERVICE_VERSION_NOT_CURRENT				-65
#define CPROT_CANNOT_CONNECT_TO_INTERNET				-68
#define CPROT_LICENSE_NUMBER_NOT_AUTHORIZED				-69
#define CPROT_ERROR_GETTING_REMOVAL_CODE				-70
#define CPROT_VMWARE_ENVIRONMENT						-71
#define CPROT_VPC_ENVIRONMENT							-72
#define CPROT_CUSTOMER_REGISTRATION_REQUIRED			-73
#define CPROT_PROBLEM_WITH_INTERNET_CONNECTION			-74
#define CPROT_CANNOT_CONNECT_TO_WEB_SITE				-75
#define CPROT_SOCKET_ERROR_1							-76
#define CPROT_SOCKET_ERROR_2							-77
#define CPROT_CANNOT_SEND_DATA							-78
#define CPROT_CANNOT_RECEIVE_DATA						-79
#define	CPROT_LICENSE_READ_FAILURE						-80
#define	CPROT_LICENSE_WRITE_FAILURE						-81
#define CPROT_MEDIA_INITIALIZED_ON_DRIVE_A				-82
#define CPROT_NO_INTERNAL_HARD_DRIVES_FOUND				-83
#define CPROT_WRONG_COMPUTER							-84
#define CPROT_TABLE_ERROR								-86
#define CPROT_WIN98_OR_ME								-87
#define CPROT_DEMO_TIME_EXPIRED							-88
#define CPROT_USER_IS_CHANGING_TIME						-89
#define CPROT_RETURNED_DATA_ERROR						-98
#define CPROT_COMPUTER_IS_BACKDATED						-99
#define CPROT_INTERNET_CONNECTION_REQUIRED				-100
#define CPROT_LICENSE_ACTIVATED_ON_DIFFERENT_COMPUTER	-101
#define CPROT_UNLOCKING_KEYS_NOT_ALLOWED				-102
#define CPROT_MOVING_LICENSE_NOT_PERMITTED				-103
#define CPROT_DRIVE_DOES_NOT_READ_RELIABLY				-107
#define CPROT_INSUFFICIENT_PRIVILEGES					-108
#define CPROT_RAM_FAILURE								-109
#define	CPROT_REGISTER_TRIAL_ERROR						-110
#define CPROT_TM_ERROR									-111
#define CPROT_CHECK_REGISTRATION_ERROR					-112
#define CPROT_TRANSMISSION_ERROR						-113
#define CPROT_LICENSE_TABLE_ALTERED1					-114
#define CPROT_LICENSE_TABLE_ALTERED2					-115
#define CPROT_LICENSE_TABLE_ALTERED3					-116
#define CPROT_LICENSE_MUST_BE_REACTIVATED				-117




//*****  Table Status Variables  *****//

#define CPROT_NEVER_AUTHORIZED							0
#define CPROT_NOT_AUTHORIZED							1
#define CPROT_UNLIMITED_USAGE							2
#define CPROT_LEASE_PERIOD_LIMITED						3
#define CPROT_AUTHORIZED_USES_LIMITED					4
#define CPROT_DEMO_DAYS_LIMITED							5
#define CPROT_DEMO_USES_LIMITED							6
#define CPROT_DEMO_USES_DAYS_LIMITED					7
#define CPROT_LIMITED_NETWORK_LICENSES					8
#define CPROT_DEMO_DAYS_EXPIRED							9
#define CPROT_DEMO_USES_EXPIRED							10
#define CPROT_LEASE_PERIOD_EXPIRED						11
#define CPROT_AUTHORIZED_USES_EXPIRED					12
#define CPROT_LEASE_USES_LIMITED						13
#define	CPROT_LICENSE_RETURNED_TO_SERVER				14
#define CPROT_DEMO_MINUTES_LIMITED						15
#define CPROT_DEMO_MINUTES_IN_USE						16
#define CPROT_DEMO_MINUTES_EXPIRED						17
#define CPROT_LICENSE_REMOVED							20
#define CPROT_USER_CHANGING_DATES						21
#define CPROT_INDETERMINATE_LICENSE_STATUS				22


//	Activation Method constants

#define CPROT_METHOD_NOT_ACTIVATED						0
#define CPROT_METHOD_INTERNET_ACTIVATE					1
#define CPROT_METHOD_UNLOCKING_KEY						2
#define CPROT_METHOD_LICENSE_CERTIFICATE				3


#endif

//*******************************************************************//
//*																	*//
//*			Required header file with library functions named		*//
//*			and return code definitions.							*//
//*																	*//
//*			Version 5 Header (C) Nalpeiron Ltd/Inc. 2009			*//
//*			    Version 5.4		March 5th 2009						*//
//*																	*//
//*******************************************************************//


//#include "CopyProtection.h"
//#include <stdlib.h>
//#include <time.h>



//////////////////////////////////////////////////////////////////////////////////////
//																					//
// Functions        :    CheckAuthorization	& Random number generator				//
//                                                                                  //
// Originated      :    11/07/2003 har                                              //
//                                                                                  //
// Revisions:			08/10/2004  har												//
//																					//
//		Revised to work with Pro-Tector and handle Pro-Tector return error codes.	//	
//																					//
//																					//                                                                                   //
//  Abstract:	This function reads the cpresult file, and places the value in		//
//		the variable szpReturnedValue.   If it cannot read the cpresult.inf			//
//		file, it szpszpReturnedValue = "255"										//
//																					//
//      It attempts to read the file 2000 times, or until successful.				//
//		By doing this, it waits until the file is actually made available by		//
//		Windows, and control may be returned before the file can be read.			//
//																					//
//																					//
//                                                                                  //
//	Outputs:	NONE																//
//																					//
//              If it returns to caller, the program is authorized to run.			//
//                                                                                  //
//                                                                                  //
//////////////////////////////////////////////////////////////////////////////////////


char Int2Char(int num)
{
	char text_number;

	if (num == 0)
	{text_number = '0';}

	if (num == 1)
	{text_number = '1';}

	if (num == 2)
	{text_number = '2';}

	if (num == 3)
	{text_number = '3';}

	if (num == 4)
	{text_number = '4';}

	if (num == 5)
	{text_number = '5';}

	if (num == 6)
	{text_number = '6';}

	if (num == 7)
	{text_number = '7';}

	if (num == 8)
	{text_number = '8';}

	if (num == 9)
	{text_number = '9';}

	return text_number;
}





void myitoa(int nNumber, char *szNumber)
{
	int i;
	
	int ones;
	int tens;
	int hundreds;
	int thousands;
	int tenthousands;

	BOOL	NegativeFlag;

	char localNumber[10];

	if (nNumber < 0)
	{
		NegativeFlag = TRUE;
		nNumber = nNumber * -1;
	}
	else
	{
		NegativeFlag = FALSE;
	}

	ones = 0;
	tens = 0;
	hundreds = 0;
	thousands = 0;
	tenthousands = 0;

//*  Handle the special case where the number to convert = 0

	if (nNumber == 0)
	{
		szNumber[0] = '0';
		szNumber[1] = '\n';
		return;
	}

//*  Break the number down into the number of 10,000s, 1,000s 100s 10s and ones

	if (nNumber >= 10000)
	{
		while (nNumber >= 10000)
		{
			nNumber = nNumber - 10000;
			tenthousands ++;
		}
	}

	if (nNumber >= 1000)
	{
		while (nNumber >= 1000)
		{
			nNumber = nNumber - 1000;
			thousands ++;
		}
	}

	if (nNumber >= 100)
	{
		while (nNumber >= 100)
		{
			nNumber = nNumber - 100;
			hundreds ++;
		}
	}

	
	if (nNumber >= 10)
	{
		while (nNumber >= 10)
		{
			nNumber = nNumber - 10;
			tens ++;
		}
	}

//*  Convert each one of those into digits, placing it in the correct position 

	ones = nNumber;

	localNumber[0] = Int2Char(tenthousands);
	localNumber[1] = Int2Char(thousands);
	localNumber[2] = Int2Char(hundreds);
	localNumber[3] = Int2Char(tens);
	localNumber[4] = Int2Char(ones);
	localNumber[5] = '\0';

//*  Stip out the zeros, so that we do not return a character string with leading zeros
	
	i = 0;

	while ((localNumber[i] == '0') && (i < 5))
	{
		i++;
	}

	if (NegativeFlag == TRUE)
	{
		strcpy(szNumber,"-");

		if (i > 0)
		{
			strcat (szNumber,localNumber + i);
		}

		if (i == 0)
		{
			strcat (szNumber,localNumber);
		}
	}
	else
	{

		if (i > 0)
		{
			strcpy (szNumber,localNumber + i);
		}

		if (i == 0)
		{
			strcpy (szNumber,localNumber);
		}
	}
	
	return;
}


long GenerateRandomNumber(int nMin, int nMax)
{

	unsigned int nSeed;

	SYSTEMTIME	sysTime;

	GetSystemTime(&sysTime);

	nSeed = sysTime.wMilliseconds + sysTime.wMinute + sysTime.wSecond;

	if( nMax < nMin )
	{
		return -1;					// invalid value  Max value is less than minimum value
	}
	
	else if( nMin == nMax )
	{
		return -2;					// invalid value  Max and min are the same
	}
	else
	{
		srand(nSeed);
		return (rand() % (nMax - nMin + 1)) + nMin;
	}
}

DWORD WINAPI UnloadDLL(LPVOID Param)
{
	typedef void (WINAPI *WaitForFinish)();

	//	Param should be the address of the dllhandle, passed in from CheckAuthorization()
	HINSTANCE *dllhandle = (HINSTANCE*)Param;
	WaitForFinish WaitForFinish_ptr = 0;

	//	Attempt to load the function WaitForFinish().  If we cannot get this function,
	//	then this is a version of the DLL without any threads to wait on, so there's
	//	no need to return an error if it's missing.  We can just proceed to unload the
	//	DLL
	if ( (WaitForFinish_ptr = (WaitForFinish)GetProcAddress(*dllhandle, "WaitForFinish")) )
	{
		//	If it is there, then call WaitForFinish() to let all threads from
		//	CheckLicense() finish before we unload the DLL
		WaitForFinish_ptr();
	}

	//	Finally, unload the DLL
	FreeLibrary(*dllhandle);
	*dllhandle = 0;
	return 0;
}


struct dllInfo
{
public:
	HINSTANCE* pdllHandle;
	HANDLE* pEvent;
};

void UnloadDLL2(void* pParams)
{
	typedef void (WINAPI *WaitForFinish)();

	//	Param should be the address of the dllhandle, passed in from CheckAuthorization()
	dllInfo* pdllInfo = static_cast<dllInfo*>(pParams);
	WaitForFinish WaitForFinish_ptr = 0;
	//	Attempt to load the function WaitForFinish().  If we cannot get this function,
	//	then this is a version of the DLL without any threads to wait on, so there's
	//	no need to return an error if it's missing.  We can just proceed to unload the
	//	DLL
	if ( (WaitForFinish_ptr = (WaitForFinish)GetProcAddress(*(pdllInfo->pdllHandle), "WaitForFinish")) )
	{
		//	If it is there, then call WaitForFinish() to let all threads from
		//	CheckLicense() finish before we unload the DLL
		WaitForFinish_ptr();
	}

	//	Finally, unload the DLL
	FreeLibrary(*(pdllInfo->pdllHandle));
	*(pdllInfo->pdllHandle) = 0;
	SetEvent(*(pdllInfo->pEvent));
	ATLTRACE("UnloadDLL2 exit\n");
	_endthread();
}


class CRunDllInThread
{
public:
	CRunDllInThread(HINSTANCE* pdllHandle )
	{
		m_hEventRun = CreateEvent(NULL,FALSE,FALSE,NULL);
		m_dllInfo.pEvent = &m_hEventRun;
		m_dllInfo.pdllHandle = pdllHandle;
		_beginthread(UnloadDLL2,0,&m_dllInfo);
	}
	~CRunDllInThread()
	{
		if (WaitForSingleObject( m_hEventRun, 5000 )==WAIT_TIMEOUT)
			{
				WaitForSingleObject( m_hEventRun, 500 );
			}
	}

	
private:
	HANDLE m_hEventRun;
	dllInfo m_dllInfo;


};



int CheckAuthorization()
{
	
	typedef	int (WINAPI *CheckLicense)(long *ParmValue);
	typedef int (WINAPI *ValidateDLL) (long *CustomerNumber, long *ProductNumber, long *ParmValue);

	int  CopyProtectionResult;
	int	 Offset;
	int  ValidDLL;

	long CustomerNumber;
	long ProductNumber;
	long ParmValue;
	long ConstantX;
	long ConstantY;
	long ConstantZ;

	char szWhatsLeft[20];
	char szMessage [250];

	unsigned long  UnloadDLLThreadID;
	HINSTANCE dllhandle;

	CheckLicense CheckLicense_ptr = 0;
	ValidateDLL  ValidateDLL_ptr = 0;

//============================================================
//		DO NOT MODIFY THE SOURCE CODE ABOVE THIS LINE



//***************************************************//
//*													*//
//*		To use the ValidateDLL function and	the		*//
//*		Dynamic Random Authentication option,		*//
//*		you MUST enter the appropriate values		*//
//*		beside the variables below.					*//
//*													*//
//*		To use the Dynamic Random Authentication,	*//
//*		you must fill in values for the X,Y,& Z		*//
//*		valiables, below.  Those numbers must		*//
//*		match the same values that you entered		*//
//*		when you created the custom DLL.			*//
//*													*//
//***************************************************//


	ConstantX = 0;
	ConstantY = 0;
	ConstantZ = 0;


//***************************************************//
//*													*//
//*		To use the ValidateDLL function, you must	*//
//*		enter your customer number to the right		*//
//*		of the equal sign besides CustomerNumber.	*//
//*		On the line below that:						*//
//*		enter the LAST 5 DIGITS of your ProductID.	*//
//*		WITHOUT LEADING ZEROS						*//
//*													*//
//***************************************************//

	CustomerNumber = 0;
	ProductNumber = 0;


//	 	DO NOT MODIFY THE SOURCE CODE BELOW THIS LINE.
//============================================================


	if (ConstantX != 0)
	{
		srand( (unsigned)time( NULL ) );
		ParmValue = GenerateRandomNumber(1,500);
		Offset = ConstantX + ((ParmValue * ConstantY) % (ConstantZ));
	}
	else
	{
		ParmValue = 50;
		Offset = 0;
	}



//***************************************************************//
//*																*//
//*		Call the DLL function to verify it is the right DLL.	*//
//*																*//
//***************************************************************//

	if (!(dllhandle = LoadLibrary("filechck.dll")))
	{
		MessageBox(0,"\n\n\n\n     Filechck.dll is missing.               \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
		ExitProcess(1);
	}
    
    if (!(ValidateDLL_ptr = (ValidateDLL)GetProcAddress(dllhandle, "ValidateDLL")))
	{
        FreeLibrary(dllhandle);
        dllhandle = 0;
        MessageBox(0,"\n\n\n\n     Filechck.dll is not current version               \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
		ExitProcess(1);
    }
	
	ValidDLL = ValidateDLL_ptr(&CustomerNumber, &ProductNumber, &ParmValue);
	ValidDLL -= Offset;

	FreeLibrary(dllhandle);
	dllhandle = 0;

	if (ValidDLL != 1)
	{
        MessageBox(0,"\n\n\n\n     Filechck.dll is for a different product               \n     Run setup again.          \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
		ExitProcess(1);
	}

		
	if (ConstantX != 0)
	{
		ParmValue = GenerateRandomNumber(1,500);
		Offset = ConstantX + ((ParmValue * ConstantY) % (ConstantZ));
	}
	else
	{
		ParmValue = 50;
		Offset = 0;
	}


					
//***************************************************************//
//*																*//
//*			Call the DLL function to check the license			*//
//*																*//
//***************************************************************//

	if (!(dllhandle = LoadLibrary("filechck.dll")))
	{
		MessageBox(0,"\n\n\n\n     Filechck.dll is missing.               \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
		ExitProcess(1);
	}
    
    if (!(CheckLicense_ptr = (CheckLicense)GetProcAddress(dllhandle, "CheckLicense")))
	{
        FreeLibrary(dllhandle);
        dllhandle = 0;
       	MessageBox(0,"\n\n\n\n      Filechck.dll is missing or the wrong version.             \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
		ExitProcess(1);
	}

	CopyProtectionResult = CheckLicense_ptr(&ParmValue);
	CopyProtectionResult -= Offset;

/*
	Create a separate thread to call the function UnloadDLL, above.
	CheckLicense can spawn threads of its own, so we have to wait
	on those to finish before we can unload the DLL--otherwise the
	threads won't finish, and in worst case the entire program can
	hang.  To allow the rest of the program to run while we wait,
	we handle unloading the DLL in a separate thread.
*/
	CreateThread(NULL, 0, UnloadDLL, &dllhandle, 0, &UnloadDLLThreadID);

	//	The product is fully authorized, or may have a number of authorized uses
	if ((CopyProtectionResult == CPROT_PRODUCT_AUTHORIZED ) &&
			((ParmValue == CPROT_UNLIMITED_USAGE) || (ParmValue == CPROT_AUTHORIZED_USES_LIMITED)))
	{
		return 0;
	}

	//	The product is authorized but has a lease period, and may have a number of authorized uses
	if ((CopyProtectionResult == CPROT_PRODUCT_AUTHORIZED ) &&
			((ParmValue == CPROT_LEASE_PERIOD_LIMITED) || (ParmValue == CPROT_LEASE_USES_LIMITED)))
	{
		return 0;
	}

	//	This product is authorized
	if ((CopyProtectionResult == CPROT_PRODUCT_AUTHORIZED ) &&
			(ParmValue == CPROT_LIMITED_NETWORK_LICENSES))
	{
		return 0;
	}

	//	This product is in demo minutes evaluation mode.  For all cases, even if the minutes
	//	have been depleted, let the product continue.  Demo Minutes is different from other
	//	demos in that developers have control over how it starts and when it ends, and they
	//	may choose to let portions of the product run even after the demo has terminated
	if (((CopyProtectionResult == CPROT_DEMO_MINUTES_LIMITED)
			&& (ParmValue == CPROT_DEMO_MINUTES_LIMITED)) ||
		((CopyProtectionResult == CPROT_DEMO_MINUTES_IN_USE)
			&& (ParmValue == CPROT_DEMO_MINUTES_IN_USE)) ||
		((CopyProtectionResult == CPROT_DEMO_MINUTES_EXPIRED)
			&& (ParmValue == CPROT_DEMO_MINUTES_EXPIRED)))
	{
		return 0;
	}

	//	This product is in evaluation mode and is nearing, or has reached, its expiration date
	//	Since the number of days in an evaluation may be up to 365, developers may wish to
	//	change the upper bound of this statement to reflect their settings
	if ((ParmValue == CPROT_DEMO_DAYS_LIMITED) &&
		(CopyProtectionResult >= 0) &&
		(CopyProtectionResult <= 100))
	{
		//	Display a message informing the user of how many days are left in the evaluation period
		if (CopyProtectionResult == 0)
		{
			strcpy (szMessage,"\n\n\n     This Program is running in Evaluation mode.                  \n           This is ");
			strcat (szMessage," your last day of evaluation.              \n\n\n");
		}
		else
		{
			myitoa (CopyProtectionResult, szWhatsLeft);
			strcpy (szMessage,"\n\n\n     This Program is running in Evaluation mode.                   \n            You have ");
			strcat (szMessage, szWhatsLeft);
			strcat (szMessage," evaluation days left.                     \n\n\n");
		}

		MessageBox(0,szMessage,"INFORMATION",MB_OK|MB_ICONINFORMATION);
		return 0;
	}

	//	This product is in evaluation mode and has a limited number of uses left
	if ((ParmValue == CPROT_DEMO_USES_LIMITED) &&
		(CopyProtectionResult >= 0) &&
		(CopyProtectionResult <= 100))
	{
		//	Display a message informing the user of how many uses are left in the evaluation
		if (CopyProtectionResult == 0)
		{
			strcpy (szMessage,"\n\n\n     This Program is running in Evaluation mode.                  \n           This is ");
			strcat (szMessage," your last evaluation trial.              \n\n\n");
		}
		else
		{
			myitoa (CopyProtectionResult, szWhatsLeft);
			strcpy (szMessage,"\n\n\n     This Program is running in Evaluation mode.                   \n           You have ");
			strcat (szMessage, szWhatsLeft);
			strcat (szMessage," evaluation trials left.                     \n\n\n");
		}

		MessageBox(0,szMessage,"INFORMATION",MB_OK|MB_ICONINFORMATION);
		return 0;
	}

	//	This product is in evaluation mode, limited by both days and uses, and the demo
	//	is approaching its expiration date
	if ((ParmValue == CPROT_DEMO_USES_DAYS_LIMITED) &&
		(CopyProtectionResult >= 0) &&
		(CopyProtectionResult <= 100))
	{
		//	Display a message informing the user of how many days are left in the evaluation period
		if (CopyProtectionResult == 0)
		{
			strcpy (szMessage,"\n\n\n     This Program is running in Evaluation mode.                  \n           This is ");
			strcat (szMessage," your last day of evaluation.              \n\n\n");
		}
		else
		{
			myitoa (CopyProtectionResult, szWhatsLeft);
			strcpy (szMessage,"\n\n\n     This Program is running in Evaluation mode.                   \n            You have ");
			strcat (szMessage, szWhatsLeft);
			strcat (szMessage," evaluation days left.                     \n\n\n");
		}

		MessageBox(0,szMessage,"INFORMATION",MB_OK|MB_ICONINFORMATION);
		return 0;
	}

	//	This product was in evaluation mode, limited by both days and uses, but
	//	the demo has expired.
	if ((ParmValue == CPROT_DEMO_USES_DAYS_LIMITED) &&
		(CopyProtectionResult < 0))
	{
		if (CopyProtectionResult == CPROT_LEASE_PERIOD_EXPIRED)
		{
			MessageBox(0,"\n\n\n     Your EvaluationUses are over                  \n\n\n","INFORMATION",MB_OK|MB_ICONINFORMATION);
			ExitProcess(1);
		}
		else
		{
			MessageBox(0,"\n\n\n     The evaluation period has expired.              \n\n\n","INFORMATION",MB_OK|MB_ICONSTOP);
			ExitProcess(1);
		}
	}

	//	This product is in lease mode and is nearing, or has reached, the
	//	end of its lease
	if ((CopyProtectionResult >= 0) &&
		(CopyProtectionResult <= 48) &&
		(
			(ParmValue == CPROT_LEASE_PERIOD_LIMITED) ||
			(ParmValue == CPROT_LEASE_USES_LIMITED)
		))
	{
		//	Display a message informing the user of how many days are left in the lease period
		if (CopyProtectionResult == 0)
		{
			strcpy (szMessage,"\n\n\n         This is the last day of your license period                             .\n\n\n");
		}
		else
		{
			if (CopyProtectionResult != CPROT_PRODUCT_AUTHORIZED)
			{
				myitoa (CopyProtectionResult, szWhatsLeft);
				strcpy (szMessage,"\n\n\n     This Program's license period is about to expire.                   \n");
				strcat (szMessage,"     You have ");
				strcat (szMessage, szWhatsLeft);
				strcat (szMessage," days left in this license period.\n\n\n");
			}
		}

		if (CopyProtectionResult != CPROT_PRODUCT_AUTHORIZED)
		{
			MessageBox(0,szMessage,"INFORMATION",MB_OK|MB_ICONINFORMATION);
		}
		return 0;
	}

	//	This product is not authorized to run
	if ((CopyProtectionResult == CPROT_PRODUCT_NOT_AUTHORIZED) &&
		(ParmValue == CPROT_NOT_AUTHORIZED))
	{
		//	Display a message informing the user that they need to activate the product
		MessageBox (0,"\n\n\n     This product needs to be activated.              \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
		ExitProcess(1);
	}

	//	This product was in evaluation mode, but the the demo has expired
	if ((CopyProtectionResult == CPROT_DEMO_EXPIRED) &&
		(ParmValue == CPROT_DEMO_DAYS_EXPIRED))
	{
		MessageBox(0,"\n\n\n     The evaluation period has expired.              \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
		ExitProcess(1);
	}

	//	This product was in evaluation mode, limited by uses, but the uses
	//	have all been used
	if ((CopyProtectionResult == CPROT_EVAL_USES_EXPIRED) &&
		(ParmValue == CPROT_DEMO_USES_EXPIRED))
	{
		MessageBox(0,"\n\n\n     There are no more evaluation uses.              \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
		ExitProcess(1);
	}

	//	This product was in lease mode, but the lease has expired
	if ((CopyProtectionResult == CPROT_LEASE_EXPIRED) &&
		(ParmValue == CPROT_LEASE_PERIOD_EXPIRED))
	{
		MessageBox(0,"\n\n\n     The Lease Period has expired.              \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
		ExitProcess(1);
	}

	if ((CopyProtectionResult == CPROT_USES_EXHAUSTED) &&
		(ParmValue == CPROT_AUTHORIZED_USES_EXPIRED))
	{
		MessageBox(0,"\n\n\n    All uses have been exhausted.              \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
		ExitProcess(1);
	}

	if (CopyProtectionResult == CPROT_SERVICE_INSTALL_FAILED)
	{
		MessageBox(0,"\n\n\n    Unable to install Windows Service.              \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
		ExitProcess(1);
	}

	if (CopyProtectionResult == CPROT_SERVICE_FAILURE)
	{
		MessageBox(0,"\n\n\n    Windows service failure.              \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
		ExitProcess(1);
	}

	if (CopyProtectionResult == CPROT_HARDDRIVE_READ_FAILURE)
	{
		MessageBox(0,"\n\n\n    Unable to read from hard drive.              \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
		ExitProcess(1);
	}

	if (CopyProtectionResult == CPROT_HARDDRIVE_WRITE_FAILURE)
	{
		MessageBox(0,"\n\n\n    Unable to write to hard drive.              \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
		ExitProcess(1);
	}

	if (CopyProtectionResult == CPROT_NO_ROOM_FOR_ENTRY)
	{
		MessageBox(0,"\n\n\n    License access failure 1.              \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
		ExitProcess(1);
	}

	if (CopyProtectionResult == CPROT_FIND_ENTRY_FAILURE)
	{
		MessageBox(0,"\n\n\n    There is no product license present.              \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
		ExitProcess(1);
	}

	if (CopyProtectionResult == CPROT_CONCURRENT_USERS_EXCEEDED)
	{
		MessageBox(0,"\n\n\n     No more users allowed at this time.              \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
		ExitProcess(1);
	}
	
	if (CopyProtectionResult == CPROT_UNABLE_TO_READ_FROM_MEDIA)
	{
		MessageBox(0,"\n\n\n    Unable to read USB Key.              \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
		ExitProcess(1);
	}

	if (CopyProtectionResult == CPROT_UNABLE_TO_WRITE_TO_MEDIA)
	{
		MessageBox(0,"\n\n\n    Unable to write to USB Key.              \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
		ExitProcess(1);
	}

	if (CopyProtectionResult == CPROT_DLL_NOT_CUSTOMIZED)
	{
		MessageBox(0,"\n\n\n\n     Publisher supplied non-customized DLL.              \n\n\n\n","ERROR",MB_OK|MB_ICONSTOP);
		ExitProcess(1);
	}

	if (CopyProtectionResult == CPROT_UNDEFINED_LICENSE_CONDITION)
	{
		MessageBox(0,"\n\n\n\n     License state undefined - reinstall authorization.              \n\n\n\n","ERROR",MB_OK|MB_ICONSTOP);
		ExitProcess(1);
	}

	if (CopyProtectionResult == CPROT_USER_IS_CHANGING_DATE)
	{
		MessageBox(0,"\n\n\n\n     Security bypass attempted - product must be reauthorized.              \n\n\n\n","ERROR",MB_OK|MB_ICONSTOP);
		ExitProcess(1);
	}

	if (CopyProtectionResult == CPROT_WRITE_DOES_NOT_VERIFY)
	{
		MessageBox(0,"\n\n\n\n     Media is bad or computer is not writing correctly.              \n\n\n\n","ERROR",MB_OK|MB_ICONSTOP);
		ExitProcess(1);
	}
	
	if (CopyProtectionResult == CPROT_UNABLE_VERIFY_WRITE)
	{
		MessageBox(0,"\n\n\n\n     Media defective or computer not reading correctly.              \n\n\n\n","ERROR",MB_OK|MB_ICONSTOP);
		ExitProcess(1);
	}

	if (CopyProtectionResult == CPROT_SERVICE_MISSING)
	{
		MessageBox(0,"\n\n\n\n     File astsrv.exe is missing.              \n\n\n\n","ERROR",MB_OK|MB_ICONSTOP);
		ExitProcess(1);
	}
	
	if (CopyProtectionResult == CPROT_ERROR_GETTING_DISK_SPECIFICATIONS)
	{
		MessageBox(0,"\n\n\n\n     File dllnt.dll is not current version.              \n\n\n\n","ERROR",MB_OK|MB_ICONSTOP);
		ExitProcess(1);
	}

	if (CopyProtectionResult == CPROT_SERVICE_VERSION_NOT_CURRENT)
	{
		MessageBox(0,"\n\n\n\n     File astsrv.exe is not current version.              \n\n\n\n","ERROR",MB_OK|MB_ICONSTOP);
		ExitProcess(1);
	}

	if (CopyProtectionResult == CPROT_CANNOT_CONNECT_TO_INTERNET)
	{
		MessageBox(0,"\n\n\n    Cannot connect to the internet.               \n    You may be behind a fire wall.              \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
		ExitProcess(1);
	}

	if (CopyProtectionResult == CPROT_VMWARE_ENVIRONMENT)
	{
		MessageBox(0,"\n\n\n     This will not run under VMWare.                  \n\n\n\n","INFORMATION",MB_OK|MB_ICONINFORMATION);
		ExitProcess(1);
	}

	if (CopyProtectionResult == CPROT_VPC_ENVIRONMENT)
	{
		MessageBox(0,"\n\n\n     This will not run under Virtual PC.                  \n\n\n\n","INFORMATION",MB_OK|MB_ICONINFORMATION);
		ExitProcess(1);
	}

	if (CopyProtectionResult == CPROT_PROBLEM_WITH_INTERNET_CONNECTION)
	{
		MessageBox(0,"\n\n\n    There is a problem with your internet connection.              \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
		ExitProcess(1); 
	}

	if (CopyProtectionResult == CPROT_CANNOT_CONNECT_TO_WEB_SITE)
	{
		MessageBox(0,"\n\n\n    Cannot connect to activation web site.              \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
		ExitProcess(1); 
	}

	if (CopyProtectionResult == CPROT_SOCKET_ERROR_1)
	{
		MessageBox(0,"\n\n\n    There is not a connection to the license server              \n    You may have firewall or proxy server issues.              \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
		ExitProcess(1);
	}

	if (CopyProtectionResult == CPROT_SOCKET_ERROR_2)
	{
		MessageBox(0,"\n\n\n    There is not a connection to the license server              \n    You may have firewall or proxy server issues.              \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
		ExitProcess(1);
	}

	if (CopyProtectionResult == CPROT_CANNOT_SEND_DATA)
	{
		MessageBox(0,"\n\n\n    Cannot send activation data.              \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
		ExitProcess(1);
	}

	if (CopyProtectionResult == CPROT_CANNOT_RECEIVE_DATA)
	{
		MessageBox(0,"\n\n\n    Cannot receive activation data.              \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
		ExitProcess(1); 
	}

	if (CopyProtectionResult == CPROT_NO_INTERNAL_HARD_DRIVES_FOUND)
	{
		MessageBox(0,"\n\n\n\n     Unable to locate any internal hard drives.              \n\n\n\n","ERROR",MB_OK|MB_ICONSTOP);
		ExitProcess(1);
	}

	if (CopyProtectionResult == CPROT_WRONG_COMPUTER)
	{
		MessageBox(0,"\n\n\n\n     Originally licensed on a different computer.              \n\n\n\n","ERROR",MB_OK|MB_ICONSTOP);
		ExitProcess(1);
	}

	if (CopyProtectionResult == CPROT_TABLE_ERROR)
	{
		MessageBox(0,"\n\n\n     Internal technical error #86.                  \n\n\n\n","INFORMATION",MB_OK|MB_ICONINFORMATION);
		ExitProcess(1);
	}

	if (CopyProtectionResult == CPROT_WIN98_OR_ME)
	{
		MessageBox(0,"\n\n\n\n     This will not run under Windows 95/98/Me.              \n\n\n\n","ERROR",MB_OK|MB_ICONSTOP);
		ExitProcess(1);
	}

	if (CopyProtectionResult == CPROT_RETURNED_DATA_ERROR)
	{
		MessageBox(0,"\n\n\n\n     The returned data was corrupted.       \n\n\n\n","ERROR",MB_OK|MB_ICONSTOP);
		ExitProcess(1);
	}

	if (CopyProtectionResult == CPROT_COMPUTER_IS_BACKDATED)
	{
		MessageBox(0,"\n\n\n\n     This computer has been backdated.              \n\n\n\n","ERROR",MB_OK|MB_ICONSTOP);
		ExitProcess(1);
	}

	if (CopyProtectionResult == CPROT_INTERNET_CONNECTION_REQUIRED)
	{
		MessageBox(0,"\n\n\n\n     Running this requires an internet connection.              \n\n\n\n","ERROR",MB_OK|MB_ICONSTOP);
		ExitProcess(1);
	}

	if (CopyProtectionResult == CPROT_DRIVE_DOES_NOT_READ_RELIABLY)
	{
		MessageBox(0,"\n\n\n\n     The hard drive does not read reliably.        \n\n\n\n","ERROR",MB_OK|MB_ICONSTOP);
		ExitProcess(1);
	}

	if (CopyProtectionResult == CPROT_INSUFFICIENT_PRIVILEGES)
	{
		MessageBox(0,"\n\n\n\n     The service does not have sufficient privileges.  Please reinstall.        \n\n\n\n","ERROR",MB_OK|MB_ICONSTOP);
		ExitProcess(1);
	}

	if (CopyProtectionResult == CPROT_REGISTER_TRIAL_ERROR)
	{
		MessageBox(0,"\n\n\n\n     There was an error when registering the trial.        \n\n\n\n","ERROR",MB_OK|MB_ICONSTOP);
		ExitProcess(1);
	}

	if (CopyProtectionResult == CPROT_TM_ERROR)
	{
		MessageBox(0,"\n\n\n\n     There was an error during the trial.        \n\n\n\n","ERROR",MB_OK|MB_ICONSTOP);
		ExitProcess(1);
	}

	if (CopyProtectionResult == CPROT_TRANSMISSION_ERROR)
	{
		MessageBox(0,"\n\n\n\n     The transmitted data was corrupted.        \n\n\n\n","ERROR",MB_OK|MB_ICONSTOP);
		ExitProcess(1);
	}

	if (CopyProtectionResult == CPROT_LICENSE_TABLE_ALTERED1)
	{
		MessageBox(0,"\n\n\n\n     Mutiple Restore Hard drive operations damaged the            \n     license and the product must be re-registered. #1       \n\n\n\n","ERROR",MB_OK|MB_ICONSTOP);
		ExitProcess(1);
	}

	if (CopyProtectionResult == CPROT_LICENSE_TABLE_ALTERED2)
	{
		MessageBox(0,"\n\n\n\n     Mutiple Restore Hard drive operations damaged the            \n     license and the product must be re-registered. #2       \n\n\n\n","ERROR",MB_OK|MB_ICONSTOP);
		ExitProcess(1);
	}

	if (CopyProtectionResult == CPROT_LICENSE_TABLE_ALTERED3)
	{
		MessageBox(0,"\n\n\n\n     Mutiple Restore Hard drive operations damaged the            \n     license and the product must be re-registered. #3       \n\n\n\n","ERROR",MB_OK|MB_ICONSTOP);
		ExitProcess(1);
	}

	if (CopyProtectionResult == CPROT_LICENSE_MUST_BE_REACTIVATED)
	{
		MessageBox(0,"\n\n\n\n     Mutiple Restore Hard drive operations damaged the            \n     license and the product must be re-registered. #4       \n\n\n\n","ERROR",MB_OK|MB_ICONSTOP);
		ExitProcess(1);
	}



	if (CopyProtectionResult != 10000)
	{
		myitoa (CopyProtectionResult,szWhatsLeft);
		strcpy (szMessage,"\n\n\n     Unknown Error # : ");
		strcat (szMessage,szWhatsLeft);
		strcat (szMessage,"               \n\n\n");
			
		MessageBox(0,szMessage,"INFORMATION",MB_OK|MB_ICONINFORMATION);	
		ExitProcess(1);
	}


	return 0;
}





//#include "ErrorFactory.h"
#include "Symlix.h"
#define ARCA_ERROR -1
#define ARCA_STRLENGTH 250


#define _WARNMESSAGE(sMessage,errorState) { \
esErrCode = errorState; \
strcpy( szMessage, sMessage ); \
/*MessageBox(0,szMessage,"License information",MB_OK|MB_ICONINFORMATION);*/ }

#define _WARNMESSAGE2( sMessage, errorState ) { \
esErrCode = errorState; \
/*MessageBox(0,sMessage,"License information",MB_OK|MB_ICONINFORMATION);*/ }

#define _WARNNOMESSAGE( sMessage, errorState ) { \
esErrCode = errorState; \
strcpy( szMessage, sMessage ); \
}

#define _WARNNOMESSAGE2( sMessage, errorState ) { \
esErrCode = errorState; \
}

///////////////////////////////////////////////////////////
// Function name	: ARCheckAuthorization
// Description	    : Aston Read customised version that
//                    does not abort
// Return type		: int 
///////////////////////////////////////////////////////////
int ARCheckAuthorization(const char* sDllFullPath, char* szMessage, enumNumCatErrorCode& esErrCode)

{
	
	
	typedef	int (WINAPI *CheckLicense)(long *ParmValue);
	typedef int (WINAPI *ValidateDLL) (long *CustomerNumber, long *ProductNumber, long *ParmValue);
	typedef int (WINAPI *FindVirtualMachines)();

	int  CopyProtectionResult;
	int	 Offset;
	int  ValidDLL;
//	int	 Status;

	long CustomerNumber;
	long ProductNumber;
	long ParmValue;
	long ConstantX;
	long ConstantY;
	long ConstantZ;

	char szWhatsLeft[20];
//	char szMessage [ARCA_STRLENGTH];

	unsigned long UnloadDLLThreadID;
	HINSTANCE dllhandle;

	CheckLicense CheckLicense_ptr = 0;
	ValidateDLL  ValidateDLL_ptr = 0;

	strcpy(szMessage,"");

//============================================================
//		DO NOT MODIFY THE SOURCE CODE ABOVE THIS LINE



//***************************************************//
//*													*//
//*		To use the ValidateDLL function and	the		*//
//*		Dynamic Random Authentication option,		*//
//*		you MUST enter the appropriate values		*//
//*		beside the variables below.					*//
//*													*//
//*		To use the Dynamic Random Authentication,	*//
//*		you must fill in values for the X,Y,& Z		*//
//*		valiables, below.  Those numbers must		*//
//*		match the same values that you entered		*//
//*		when you created the custom DLL.			*//
//*													*//
//***************************************************//


	ConstantX = 236;
	ConstantY = 836;
	ConstantZ = 269;


//***************************************************//
//*													*//
//*		To use the ValidateDLL function, you must	*//
//*		enter your customer number to the right		*//
//*		of the equal sign besides CustomerNumber.	*//
//*		On the line below that:						*//
//*		enter the LAST 5 DIGITS of your ProductID.	*//
//*		WITHOUT LEADING ZEROS						*//
//*													*//
//***************************************************//

	CustomerNumber = 2443;
#ifdef _OLDLICENSE
	ProductNumber = 100; // new number 1907634006 ie 34006
#else
	ProductNumber = 34006; // new number 1907634006 ie 34006
#endif

//	 	DO NOT MODIFY THE SOURCE CODE BELOW THIS LINE.
//============================================================



	if (ConstantX != 0)
	{
		srand( (unsigned)time( NULL ) );
		ParmValue = GenerateRandomNumber(1,500);
		Offset = ConstantX + ((ParmValue * ConstantY) % (ConstantZ));
	}
	else
	{
		ParmValue = 50;
		Offset = 0;
	}



//***************************************************************//
//*																*//
//*		Call the DLL function to verify it is the right DLL.	*//
//*																*//
//***************************************************************//

	if (!(dllhandle = LoadLibrary(sDllFullPath)))
	{
//		MessageBox(0,"\n\n\n\n     Filechck.dll is missing.               \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
//		ExitProcess(1);
		strcpy(szMessage,"File ");
		strcat(szMessage,sDllFullPath);
		strcat(szMessage," is missing.");
		_WARNMESSAGE2( szMessage, errSystem );
		return ARCA_ERROR;
	}
    
    if (!(ValidateDLL_ptr = (ValidateDLL)GetProcAddress(dllhandle, "ValidateDLL")))
	{
        FreeLibrary(dllhandle);
        dllhandle = 0;
		_WARNMESSAGE( "Filechck.dll is not current version", errSystem );
		return ARCA_ERROR;
//        MessageBox(0,"\n\n\n\n     Filechck.dll is not current version               \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
//		ExitProcess(1);
    }
	
	ValidDLL = ValidateDLL_ptr(&CustomerNumber, &ProductNumber, &ParmValue);
	ValidDLL -= Offset;

	FreeLibrary(dllhandle);
	dllhandle = 0;

	if (ValidDLL != 1)
	{
//        MessageBox(0,"\n\n\n\n     Filechck.dll is for a different product               \n     Run setup again.          \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
//		ExitProcess(1);
		_WARNMESSAGE( "Filechck.dll is for a different product", errSystem );
		return ARCA_ERROR;
	}

		
	if (ConstantX != 0)
	{
		ParmValue = GenerateRandomNumber(1,500);
		Offset = ConstantX + ((ParmValue * ConstantY) % (ConstantZ));
	}
	else
	{
		ParmValue = 50;
		Offset = 0;
	}


					
//***************************************************************//
//*																*//
//*			Call the DLL function to check the license			*//
//*																*//
//***************************************************************//

	if (!(dllhandle = LoadLibrary(sDllFullPath)))
	{
//		MessageBox(0,"\n\n\n\n     Filechck.dll is missing.               \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
//		ExitProcess(1);
		_WARNMESSAGE("Filechck.dll is missing",errSystem);
		return ARCA_ERROR;
	}
    
    if (!(CheckLicense_ptr = (CheckLicense)GetProcAddress(dllhandle, "CheckLicense")))
	{
        FreeLibrary(dllhandle);
        dllhandle = 0;
  		_WARNMESSAGE("Filechck.dll is missing or the wrong version",errSystem);
		return ARCA_ERROR;
//     	MessageBox(0,"\n\n\n\n      Filechck.dll is missing or the wrong version.             \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
//		ExitProcess(1);
	}

	CopyProtectionResult = CheckLicense_ptr(&ParmValue);
	CopyProtectionResult -= Offset;

/*
	Create a separate thread to call the function UnloadDLL, above.
	CheckLicense can spawn threads of its own, so we have to wait
	on those to finish before we can unload the DLL--otherwise the
	threads won't finish, and in worst case the entire program can
	hang.  To allow the rest of the program to run while we wait,
	we handle unloading the DLL in a separate thread.
*/

//	CreateThread(NULL, 0, UnloadDLL, &dllhandle, 0, &UnloadDLLThreadID);
//	_beginthread(UnloadDLL2,0,&dllhandle);
	CRunDllInThread rundll(&dllhandle);
	
	//	The product is fully authorized, or may have a number of authorized uses
	if ((CopyProtectionResult == CPROT_PRODUCT_AUTHORIZED ) &&
			((ParmValue == CPROT_UNLIMITED_USAGE) || (ParmValue == CPROT_AUTHORIZED_USES_LIMITED)))
	{
		return 0;
	}

	//	The product is authorized but has a lease period, and may have a number of authorized uses
	if ((CopyProtectionResult == CPROT_PRODUCT_AUTHORIZED ) &&
			((ParmValue == CPROT_LEASE_PERIOD_LIMITED) || (ParmValue == CPROT_LEASE_USES_LIMITED)))
	{
		return 0;
	}

	//	This product is authorized
	if ((CopyProtectionResult == CPROT_PRODUCT_AUTHORIZED ) &&
			(ParmValue == CPROT_LIMITED_NETWORK_LICENSES))
	{
		return 0;
	}

	//	This product is in demo minutes evaluation mode.  For all cases, even if the minutes
	//	have been depleted, let the product continue.  Demo Minutes is different from other
	//	demos in that developers have control over how it starts and when it ends, and they
	//	may choose to let portions of the product run even after the demo has terminated
	if (((CopyProtectionResult == CPROT_DEMO_MINUTES_LIMITED)
			&& (ParmValue == CPROT_DEMO_MINUTES_LIMITED)) ||
		((CopyProtectionResult == CPROT_DEMO_MINUTES_IN_USE)
			&& (ParmValue == CPROT_DEMO_MINUTES_IN_USE)) ||
		((CopyProtectionResult == CPROT_DEMO_MINUTES_EXPIRED)
			&& (ParmValue == CPROT_DEMO_MINUTES_EXPIRED)))
	{
		return 0;
	}

	//	This product is in evaluation mode and is nearing, or has reached, its expiration date
	//	Since the number of days in an evaluation may be up to 365, developers may wish to
	//	change the upper bound of this statement to reflect their settings
	if ((ParmValue == CPROT_DEMO_DAYS_LIMITED) &&
		(CopyProtectionResult >= 0) &&
		(CopyProtectionResult <= 100))
	{
		//	Display a message informing the user of how many days are left in the evaluation period
		if (CopyProtectionResult == 0)
		{
			strcpy (szMessage,"\n\n\n     This Program is running in Evaluation mode.                  \n           This is ");
			strcat (szMessage," your last day of evaluation.              \n\n\n");
			_WARNMESSAGE2(szMessage,errWarning);
		}
		else
		{
			myitoa (CopyProtectionResult, szWhatsLeft);
			strcpy (szMessage,"\n\n\n     This Program is running in Evaluation mode.                   \n            You have ");
			strcat (szMessage, szWhatsLeft);
			strcat (szMessage," evaluation days left.                     \n\n\n");
			_WARNNOMESSAGE2(szMessage,errWarning);
		}

	//	MessageBox(0,szMessage,"INFORMATION",MB_OK|MB_ICONINFORMATION);
		return 0;
	}

	//	This product is in evaluation mode and has a limited number of uses left
	if ((ParmValue == CPROT_DEMO_USES_LIMITED) &&
		(CopyProtectionResult >= 0) &&
		(CopyProtectionResult <= 100))
	{
		//	Display a message informing the user of how many uses are left in the evaluation
		if (CopyProtectionResult == 0)
		{
			strcpy (szMessage,"\n\n\n     This Program is running in Evaluation mode.                  \n           This is ");
			strcat (szMessage," your last evaluation trial.              \n\n\n");
			_WARNMESSAGE2(szMessage,errWarning);
		}
		else
		{
			myitoa (CopyProtectionResult, szWhatsLeft);
			strcpy (szMessage,"\n\n\n     This Program is running in Evaluation mode.                   \n           You have ");
			strcat (szMessage, szWhatsLeft);
			strcat (szMessage," evaluation trials left.                     \n\n\n");
			_WARNNOMESSAGE2(szMessage,errWarning);
		}

		//MessageBox(0,szMessage,"INFORMATION",MB_OK|MB_ICONINFORMATION);
		return 0;
	}

	//	This product is in evaluation mode, limited by both days and uses, and the demo
	//	is approaching its expiration date
	if ((ParmValue == CPROT_DEMO_USES_DAYS_LIMITED) &&
		(CopyProtectionResult >= 0) &&
		(CopyProtectionResult <= 100))
	{
		//	Display a message informing the user of how many days are left in the evaluation period
		if (CopyProtectionResult == 0)
		{
			strcpy (szMessage,"\n\n\n     This Program is running in Evaluation mode.                  \n           This is ");
			strcat (szMessage," your last day of evaluation.              \n\n\n");
			_WARNMESSAGE2(szMessage,errWarning);
		}
		else
		{
			myitoa (CopyProtectionResult, szWhatsLeft);
			strcpy (szMessage,"\n\n\n     This Program is running in Evaluation mode.                   \n            You have ");
			strcat (szMessage, szWhatsLeft);
			strcat (szMessage," evaluation days left.                     \n\n\n");
			_WARNNOMESSAGE2(szMessage,errWarning);
		}

//		MessageBox(0,szMessage,"INFORMATION",MB_OK|MB_ICONINFORMATION);
		return 0;
	}

	//	This product was in evaluation mode, limited by both days and uses, but
	//	the demo has expired.
	if ((ParmValue == CPROT_DEMO_USES_DAYS_LIMITED) &&
		(CopyProtectionResult < 0))
	{
		if (CopyProtectionResult == CPROT_LEASE_PERIOD_EXPIRED)
		{
			_WARNMESSAGE("Your Evaluation Uses are over",errSystem);
			return ARCA_ERROR;
//			MessageBox(0,"\n\n\n     Your EvaluationUses are over                  \n\n\n","INFORMATION",MB_OK|MB_ICONINFORMATION);
//			ExitProcess(1);
		}
		else
		{
			_WARNMESSAGE("The evaluation period has expired",errSystem);
			return ARCA_ERROR;
//			MessageBox(0,"\n\n\n     The evaluation period has expired.              \n\n\n","INFORMATION",MB_OK|MB_ICONSTOP);
//			ExitProcess(1);
		}
	}

	//	This product is in lease mode and is nearing, or has reached, the
	//	end of its lease
	if ((CopyProtectionResult >= 0) &&
		(CopyProtectionResult <= 48) &&
		(
			(ParmValue == CPROT_LEASE_PERIOD_LIMITED) ||
			(ParmValue == CPROT_LEASE_USES_LIMITED)
		))
	{
		//	Display a message informing the user of how many days are left in the lease period
		if (CopyProtectionResult == 0)
		{
			strcpy (szMessage,"\n\n\n         This is the last day of your license period                             .\n\n\n");
		}
		else
		{
			if (CopyProtectionResult != CPROT_PRODUCT_AUTHORIZED)
			{
				myitoa (CopyProtectionResult, szWhatsLeft);
				strcpy (szMessage,"\n\n\n     This Program's license period is about to expire.                   \n");
				strcat (szMessage,"     You have ");
				strcat (szMessage, szWhatsLeft);
				strcat (szMessage," days left in this license period.\n\n\n");
			}
		}

		if (CopyProtectionResult != CPROT_PRODUCT_AUTHORIZED)
		{
			_WARNNOMESSAGE2(szMessage,errWarning);
//			MessageBox(0,szMessage,"INFORMATION",MB_OK|MB_ICONINFORMATION);
		}
		return 0;
	}

	//	This product is not authorized to run
	if ((CopyProtectionResult == CPROT_PRODUCT_NOT_AUTHORIZED) &&
		(ParmValue == CPROT_NOT_AUTHORIZED))
	{
		//	Display a message informing the user that they need to activate the product
//		MessageBox (0,"\n\n\n     This product needs to be activated.              \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
//		ExitProcess(1);
		_WARNMESSAGE("This product needs to be activated",errSystem);
		return ARCA_ERROR;
	}

	//	This product was in evaluation mode, but the the demo has expired
	if ((CopyProtectionResult == CPROT_DEMO_EXPIRED) &&
		(ParmValue == CPROT_DEMO_DAYS_EXPIRED))
	{
//		MessageBox(0,"\n\n\n     The evaluation period has expired.              \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
//		ExitProcess(1);
		_WARNMESSAGE("The evaluation period has expired",errSystem);
		return ARCA_ERROR;
	}

	//	This product was in evaluation mode, limited by uses, but the uses
	//	have all been used
	if ((CopyProtectionResult == CPROT_EVAL_USES_EXPIRED) &&
		(ParmValue == CPROT_DEMO_USES_EXPIRED))
	{
//		MessageBox(0,"\n\n\n     There are no more evaluation uses.              \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
//		ExitProcess(1);
		_WARNMESSAGE("There are no more evaluation uses",errSystem);
		return ARCA_ERROR;
	}

	//	This product was in lease mode, but the lease has expired
	if ((CopyProtectionResult == CPROT_LEASE_EXPIRED) &&
		(ParmValue == CPROT_LEASE_PERIOD_EXPIRED))
	{
//		MessageBox(0,"\n\n\n     The Lease Period has expired.              \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
//		ExitProcess(1);
		_WARNMESSAGE("The Lease Period has expired",errSystem);
		return ARCA_ERROR;
	}

	if ((CopyProtectionResult == CPROT_USES_EXHAUSTED) &&
		(ParmValue == CPROT_AUTHORIZED_USES_EXPIRED))
	{
//		MessageBox(0,"\n\n\n    All uses have been exhausted.              \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
//		ExitProcess(1);
		_WARNMESSAGE("All uses have been exhausted",errSystem);
		return ARCA_ERROR;
	}

	if (CopyProtectionResult == CPROT_SERVICE_INSTALL_FAILED)
	{
//		MessageBox(0,"\n\n\n    Unable to install Windows Service.              \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
//		ExitProcess(1);
		_WARNMESSAGE(" Unable to install Windows Service",errSystem);
		return ARCA_ERROR;
	}

	if (CopyProtectionResult == CPROT_SERVICE_FAILURE)
	{
//		MessageBox(0,"\n\n\n    Windows service failure.              \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
//		ExitProcess(1);
		_WARNMESSAGE("Windows service failure",errSystem);
		return ARCA_ERROR;
	}

	if (CopyProtectionResult == CPROT_HARDDRIVE_READ_FAILURE)
	{
//		MessageBox(0,"\n\n\n    Unable to read from hard drive.              \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
//		ExitProcess(1);
		_WARNMESSAGE("Unable to read from hard drive",errSystem);
		return ARCA_ERROR;
	}

	if (CopyProtectionResult == CPROT_HARDDRIVE_WRITE_FAILURE)
	{
//		MessageBox(0,"\n\n\n    Unable to write to hard drive.              \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
//		ExitProcess(1);
		_WARNMESSAGE("Unable to write to hard drive",errSystem);
		return ARCA_ERROR;
	}

	if (CopyProtectionResult == CPROT_NO_ROOM_FOR_ENTRY)
	{
//		MessageBox(0,"\n\n\n    License access failure 1.              \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
//		ExitProcess(1);
		_WARNMESSAGE("License access failure 1",errSystem);
		return ARCA_ERROR;
	}

	if (CopyProtectionResult == CPROT_FIND_ENTRY_FAILURE)
	{
//		MessageBox(0,"\n\n\n    There is no product license present.              \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
//		ExitProcess(1);
		_WARNMESSAGE("There is no product license present",errSystem);
		return ARCA_ERROR;
	}

	if (CopyProtectionResult == CPROT_CONCURRENT_USERS_EXCEEDED)
	{
//		MessageBox(0,"\n\n\n     No more users allowed at this time.              \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
//		ExitProcess(1);
		_WARNMESSAGE("No more users allowed at this time",errSystem);
		return ARCA_ERROR;
	}
	
	if (CopyProtectionResult == CPROT_UNABLE_TO_READ_FROM_MEDIA)
	{
//		MessageBox(0,"\n\n\n    Unable to read USB Key.              \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
//		ExitProcess(1);
		_WARNMESSAGE("Unable to read USB Key",errSystem);
		return ARCA_ERROR;
	}

	if (CopyProtectionResult == CPROT_UNABLE_TO_WRITE_TO_MEDIA)
	{
//		MessageBox(0,"\n\n\n    Unable to write to USB Key.              \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
//		ExitProcess(1);
		_WARNMESSAGE("Unable to write to USB Key",errSystem);
		return ARCA_ERROR;
	}

	if (CopyProtectionResult == CPROT_DLL_NOT_CUSTOMIZED)
	{
//		MessageBox(0,"\n\n\n\n     Publisher supplied non-customized DLL.              \n\n\n\n","ERROR",MB_OK|MB_ICONSTOP);
//		ExitProcess(1);
		_WARNMESSAGE("Publisher supplied non-customized DLL",errSystem);
		return ARCA_ERROR;
	}

	if (CopyProtectionResult == CPROT_UNDEFINED_LICENSE_CONDITION)
	{
//		MessageBox(0,"\n\n\n\n     License state undefined - reinstall authorization.              \n\n\n\n","ERROR",MB_OK|MB_ICONSTOP);
//		ExitProcess(1);
		_WARNMESSAGE("License state undefined - reinstall authorization",errSystem);
		return ARCA_ERROR;
	}

	if (CopyProtectionResult == CPROT_USER_IS_CHANGING_DATE)
	{
//		MessageBox(0,"\n\n\n\n     Security bypass attempted - product must be reauthorized.              \n\n\n\n","ERROR",MB_OK|MB_ICONSTOP);
//		ExitProcess(1);
		_WARNMESSAGE("Security bypass attempted - product must be reauthorized",errSystem);
		return ARCA_ERROR;
	}

	if (CopyProtectionResult == CPROT_WRITE_DOES_NOT_VERIFY)
	{
//		MessageBox(0,"\n\n\n\n     Media is bad or computer is not writing correctly.              \n\n\n\n","ERROR",MB_OK|MB_ICONSTOP);
//		ExitProcess(1);
		_WARNMESSAGE("Media is bad or computer is not writing correctly",errSystem);
		return ARCA_ERROR;
	}
	
	if (CopyProtectionResult == CPROT_UNABLE_VERIFY_WRITE)
	{
//		MessageBox(0,"\n\n\n\n     Media defective or computer not reading correctly.              \n\n\n\n","ERROR",MB_OK|MB_ICONSTOP);
//		ExitProcess(1);
		_WARNMESSAGE("Media defective or computer not reading correctly",errSystem);
		return ARCA_ERROR;
	}

	if (CopyProtectionResult == CPROT_SERVICE_MISSING)
	{
//		MessageBox(0,"\n\n\n\n     File astsrv.exe is missing.              \n\n\n\n","ERROR",MB_OK|MB_ICONSTOP);
//		ExitProcess(1);
		_WARNMESSAGE("File nlssrv32.exe is missing",errSystem);
		return ARCA_ERROR;
	}
	
	if (CopyProtectionResult == CPROT_ERROR_GETTING_DISK_SPECIFICATIONS)
	{
//		MessageBox(0,"\n\n\n\n     File dllnt.dll is not current version.              \n\n\n\n","ERROR",MB_OK|MB_ICONSTOP);
//		ExitProcess(1);
		_WARNMESSAGE("File dllnt.dll is not current version",errSystem);
		return ARCA_ERROR;
	}

	if (CopyProtectionResult == CPROT_SERVICE_VERSION_NOT_CURRENT)
	{
//		MessageBox(0,"\n\n\n\n     File astsrv.exe is not current version.              \n\n\n\n","ERROR",MB_OK|MB_ICONSTOP);
//		ExitProcess(1);
		_WARNMESSAGE("File nlssrv32.exe is not current version",errSystem);
		return ARCA_ERROR;
	}

	if (CopyProtectionResult == CPROT_CANNOT_CONNECT_TO_INTERNET)
	{
//		MessageBox(0,"\n\n\n    Cannot connect to the internet.               \n    You may be behind a fire wall.              \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
//		ExitProcess(1);
		_WARNMESSAGE("Cannot connect to the internet\nYou may be behind a fire wall",errSystem);
		return ARCA_ERROR;
	}

	if (CopyProtectionResult == CPROT_VMWARE_ENVIRONMENT)
	{
//		MessageBox(0,"\n\n\n     This will not run under VMWare.                  \n\n\n\n","INFORMATION",MB_OK|MB_ICONINFORMATION);
//		ExitProcess(1);
		_WARNMESSAGE("This will not run under VMWare",errSystem);
		return ARCA_ERROR;
	}

	if (CopyProtectionResult == CPROT_VPC_ENVIRONMENT)
	{
//		MessageBox(0,"\n\n\n     This will not run under Virtual PC.                  \n\n\n\n","INFORMATION",MB_OK|MB_ICONINFORMATION);
//		ExitProcess(1);
		_WARNMESSAGE("This will not run under Virtual PC",errSystem);
		return ARCA_ERROR;
	}

	if (CopyProtectionResult == CPROT_PROBLEM_WITH_INTERNET_CONNECTION)
	{
//		MessageBox(0,"\n\n\n    There is a problem with your internet connection.              \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
//		ExitProcess(1); 
		_WARNMESSAGE("There is a problem with your internet connection",errSystem);
		return ARCA_ERROR;
	}

	if (CopyProtectionResult == CPROT_CANNOT_CONNECT_TO_WEB_SITE)
	{
//		MessageBox(0,"\n\n\n    Cannot connect to activation web site.              \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
//		ExitProcess(1); 
		_WARNMESSAGE("Cannot connect to activation web site",errSystem);
		return ARCA_ERROR;
	}

	if (CopyProtectionResult == CPROT_SOCKET_ERROR_1)
	{
//		MessageBox(0,"\n\n\n    There is not a connection to the license server              \n    You may have firewall or proxy server issues.              \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
//		ExitProcess(1);
		_WARNMESSAGE("There is not a connection to the license server\nYou may have firewall or proxy server issues",errSystem);
		return ARCA_ERROR;
	}

	if (CopyProtectionResult == CPROT_SOCKET_ERROR_2)
	{
//		MessageBox(0,"\n\n\n    There is not a connection to the license server              \n    You may have firewall or proxy server issues.              \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
//		ExitProcess(1);
		_WARNMESSAGE("There is not a connection to the license server\nYou may have firewall or proxy server issues",errSystem);
		return ARCA_ERROR;
	}

	if (CopyProtectionResult == CPROT_CANNOT_SEND_DATA)
	{
//		MessageBox(0,"\n\n\n    Cannot send activation data.              \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
//		ExitProcess(1);
		_WARNMESSAGE("Cannot send activation data",errSystem);
		return ARCA_ERROR;
	}

	if (CopyProtectionResult == CPROT_CANNOT_RECEIVE_DATA)
	{
//		MessageBox(0,"\n\n\n    Cannot receive activation data.              \n\n\n","ERROR",MB_OK|MB_ICONSTOP);
//		ExitProcess(1); 
		_WARNMESSAGE("Cannot send activation data",errSystem);
		return ARCA_ERROR;
	}

	if (CopyProtectionResult == CPROT_NO_INTERNAL_HARD_DRIVES_FOUND)
	{
//		MessageBox(0,"\n\n\n\n     Unable to locate any internal hard drives.              \n\n\n\n","ERROR",MB_OK|MB_ICONSTOP);
//		ExitProcess(1);
		_WARNMESSAGE("Unable to locate any internal hard drives",errSystem);
		return ARCA_ERROR;
	}

	if (CopyProtectionResult == CPROT_WRONG_COMPUTER)
	{
//		MessageBox(0,"\n\n\n\n     Originally licensed on a different computer.              \n\n\n\n","ERROR",MB_OK|MB_ICONSTOP);
//		ExitProcess(1);
		_WARNMESSAGE("Originally licensed on a different computer",errSystem);
		return ARCA_ERROR;
	}

	if (CopyProtectionResult == CPROT_TABLE_ERROR)
	{
//		MessageBox(0,"\n\n\n     Internal technical error #86.                  \n\n\n\n","INFORMATION",MB_OK|MB_ICONINFORMATION);
//		ExitProcess(1);
		_WARNMESSAGE("Internal technical error #86",errSystem);
		return ARCA_ERROR;
	}

	if (CopyProtectionResult == CPROT_WIN98_OR_ME)
	{
//		MessageBox(0,"\n\n\n\n     This will not run under Windows 95/98/Me.              \n\n\n\n","ERROR",MB_OK|MB_ICONSTOP);
//		ExitProcess(1);
		_WARNMESSAGE("This will not run under Windows 95/98 or if your insane enought to run it Windows Me",errSystem);
		return ARCA_ERROR;
	}

	if (CopyProtectionResult == CPROT_RETURNED_DATA_ERROR)
	{
//		MessageBox(0,"\n\n\n\n     The returned data was corrupted.       \n\n\n\n","ERROR",MB_OK|MB_ICONSTOP);
//		ExitProcess(1);
		_WARNMESSAGE("The returned data was corrupted",errSystem);
		return ARCA_ERROR;
	}

	if (CopyProtectionResult == CPROT_COMPUTER_IS_BACKDATED)
	{
//		MessageBox(0,"\n\n\n\n     This computer has been backdated.              \n\n\n\n","ERROR",MB_OK|MB_ICONSTOP);
//		ExitProcess(1);
		_WARNMESSAGE("This computer has been backdated",errSystem);
		return ARCA_ERROR;
	}

	if (CopyProtectionResult == CPROT_INTERNET_CONNECTION_REQUIRED)
	{
//		MessageBox(0,"\n\n\n\n     Running this requires an internet connection.              \n\n\n\n","ERROR",MB_OK|MB_ICONSTOP);
//		ExitProcess(1);
		_WARNMESSAGE("Running this requires an internet connection",errSystem);
		return ARCA_ERROR;
	}

	if (CopyProtectionResult == CPROT_DRIVE_DOES_NOT_READ_RELIABLY)
	{
//		MessageBox(0,"\n\n\n\n     The hard drive does not read reliably.        \n\n\n\n","ERROR",MB_OK|MB_ICONSTOP);
//		ExitProcess(1);
		_WARNMESSAGE("The hard drive does not read reliably",errSystem);
		return ARCA_ERROR;
	}

	if (CopyProtectionResult == CPROT_INSUFFICIENT_PRIVILEGES)
	{
//		MessageBox(0,"\n\n\n\n     The service does not have sufficient privileges.  Please reinstall.        \n\n\n\n","ERROR",MB_OK|MB_ICONSTOP);
//		ExitProcess(1);
		_WARNMESSAGE("\n\nThe service does not have sufficient privileges.  Please reinstall.\n\n",errSystem);
		return ARCA_ERROR;
	}

	if (CopyProtectionResult == CPROT_REGISTER_TRIAL_ERROR)
	{
//		MessageBox(0,"\n\n\n\n     There was an error when registering the trial.        \n\n\n\n","ERROR",MB_OK|MB_ICONSTOP);
//		ExitProcess(1);
		_WARNMESSAGE("\n\nThere was an error when registering the trial\n\n",errSystem);
		return ARCA_ERROR;
	}

	if (CopyProtectionResult == CPROT_TM_ERROR)
	{
//		MessageBox(0,"\n\n\n\n     There was an error during the trial.        \n\n\n\n","ERROR",MB_OK|MB_ICONSTOP);
//		ExitProcess(1);
		_WARNMESSAGE("\n\nThere was an error when registering the trial\n\n",errSystem);
		return ARCA_ERROR;
	}

	if (CopyProtectionResult == CPROT_TRANSMISSION_ERROR)
	{
//		MessageBox(0,"\n\n\n\n     The transmitted data was corrupted.        \n\n\n\n","ERROR",MB_OK|MB_ICONSTOP);
//		ExitProcess(1);
		_WARNMESSAGE("The transmitted data was corrupted",errSystem);
		return ARCA_ERROR;
	}

	if (CopyProtectionResult == CPROT_LICENSE_TABLE_ALTERED1)
	{
//		MessageBox(0,"\n\n\n\n     Mutiple Restore Hard drive operations damaged the            \n     license and the product must be re-registered. #1       \n\n\n\n","ERROR",MB_OK|MB_ICONSTOP);
//		ExitProcess(1);
		_WARNMESSAGE("Mutiple Restore Hard drive operations damaged the\nlicense and the product must be re-registered. #1",errSystem);
		return ARCA_ERROR;
	}

	if (CopyProtectionResult == CPROT_LICENSE_TABLE_ALTERED2)
	{
//		MessageBox(0,"\n\n\n\n     Mutiple Restore Hard drive operations damaged the            \n     license and the product must be re-registered. #2       \n\n\n\n","ERROR",MB_OK|MB_ICONSTOP);
//		ExitProcess(1);
		_WARNMESSAGE("Mutiple Restore Hard drive operations damaged the\nlicense and the product must be re-registered. #2",errSystem);
		return ARCA_ERROR;
	}

	if (CopyProtectionResult == CPROT_LICENSE_TABLE_ALTERED3)
	{
//		MessageBox(0,"\n\n\n\n     Mutiple Restore Hard drive operations damaged the            \n     license and the product must be re-registered. #3       \n\n\n\n","ERROR",MB_OK|MB_ICONSTOP);
//		ExitProcess(1);
		_WARNMESSAGE("Mutiple Restore Hard drive operations damaged the\nlicense and the product must be re-registered. #3",errSystem);
		return ARCA_ERROR;
	}

	if (CopyProtectionResult == CPROT_LICENSE_MUST_BE_REACTIVATED)
	{
//		MessageBox(0,"\n\n\n\n     Mutiple Restore Hard drive operations damaged the            \n     license and the product must be re-registered. #4       \n\n\n\n","ERROR",MB_OK|MB_ICONSTOP);
//		ExitProcess(1);
		_WARNMESSAGE("Mutiple Restore Hard drive operations damaged the\nlicense and the product must be re-registered. #4",errSystem);
		return ARCA_ERROR;
	}



	if (CopyProtectionResult != 10000)
	{
		myitoa (CopyProtectionResult,szWhatsLeft);
		strcpy (szMessage,"\n\n\n     Unknown Error # : ");
		strcat (szMessage,szWhatsLeft);
		strcat (szMessage,"               \n\n\n");
			
//		MessageBox(0,szMessage,"INFORMATION",MB_OK|MB_ICONINFORMATION);	
//		ExitProcess(1);
		_WARNMESSAGE2(szMessage,errSystem);
		return ARCA_ERROR;
	}


	return 0;
}




#ifdef __cplusplus
}
#endif

