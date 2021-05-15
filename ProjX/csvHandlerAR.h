// Common header macros for CSV Handler classes


//#define _USE_NAMESPACE

#ifdef _USE_NAMESPACE
	#define _CSV_HANDLER_BEGIN namespace CSV_Handler_AR {
	#define _CSV_HANDLER_END };
	#define _CSV_HANDLER
	#define _CSV_HANDLER_USING using namespace CSV_Handler_AR;
#else
	#define _CSV_HANDLER_BEGIN
	#define _CSV_HANDLER_END
	#define _CSV_HANDLER
	#define _CSV_HANDLER_USING
#endif