/*

	Common additions to StdAfx.h added here to keep two projects in sync

*/

#ifndef COMMON_DEFS_MADE
#define COMMON_DEFS_MADE

	#ifdef NDEBUG
	#define NCSVDEBUG
	#else
	#define NCSVDEBUG
	#endif

	#include <stdio.h>

	// TODO: reference additional headers your program requires here
//	#define _DEBUGMEM

	#ifdef _DEBUGMEM
	#ifndef _SYMLIX // need to work out where this should be added latter on.
		#include <vld.h>
	#endif
	#endif

	#include "global.h"


	#include "MemLeakRecord.h"

	#define xt_value variable
	#define xt_constrained_value varStrongType

	// to ensure correct responses to VB over COM with Variant_Bools
	#define VB_FALSE 0
	#define VB_TRUE -1
// START SYMLIX STUFF
	//stuff for SYMLIX - but may now be needed for all projects
	#ifndef STRICT
	#define STRICT
	#endif
	#ifndef _WIN32_WINNT
	#define _WIN32_WINNT 0x0400
	#endif
	#define _ATL_APARTMENT_THREADED

	#include <atlbase.h>


	//You may derive a class from CComModule and use it if you want to override
	//something, but do not change the name of _Module

	
#ifdef _SYMLIX // need to work out where this should be added latter on.
	#include <atlapp.h>

 	// this is needed for ATL and WTL windows operation
	extern CAppModule _Module;
	#include <atlcom.h>
#else
	// this is the only requirement for console app
	extern CComModule _Module;
	#include <atlcom.h>
#endif // _SYMLIX

//END SYMLIX STUFF
#endif // COMMON_DEFS_MADE