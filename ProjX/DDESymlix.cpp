/*-----------------------------------------------
   Symlix DDE server
                
  -----------------------------------------------*/
#include "stdafx.h"
#include <windows.h>
#include <ddeml.h>
#include <string.h>
#include <process.h>
#include "DDESymlix.h"
#include "EvDDEServer.h"

#define WM_USER_INITIATE (WM_USER + 1)
#define ID_TIMER         1


long     FAR PASCAL _export WndProc2     (HWND, UINT, UINT, LONG) ;
HDDEDATA FAR PASCAL _export DdeCallback (UINT, UINT, HCONV, HSZ, HSZ,
                                         HDDEDATA, DWORD, DWORD) ;

//char   szAppName [] = "Symlix_DDE_Server" ;
char* szAppName;
//char   szTopic   [] = "US_Population" ;
char   szTopic   [] = "LiveData" ;
DWORD  idInst ;
HANDLE hInst ;
HWND   hwnd ;
CDDEServerData* pDDEServerData;
MapStringDDE mapResults;
vector< variable > vecResults;

void DDEThread1(void* pParams)
//int PASCAL WinMain (HANDLE hInstance, HANDLE hPrevInstance,
//                    LPSTR lpszCmdLine, int nCmdShow)
     {
//	 HINSTANCE hInstance = *(HINSTANCE*)(pParams);
	 pDDEServerData = static_cast<CDDEServerData*>(pParams);

	 if (!pDDEServerData) // this should not happen as static cast shouldn't set to null
		_endthread(); // or else its going to get really ugly - this shoudl never happen


	 if (!pDDEServerData->getEvDDEServer()->copyIndexMap(mapResults))
		_endthread();	

	 vecResults.resize(pDDEServerData->getEvDDEServer()->getSizeResults(),NOT_DEFINED);
	 
	 ATLTRACE("Size of mapResults = %d\n",mapResults.size());
	 
	 HINSTANCE hInstance = NULL;
     FARPROC  pfnDdeCallback ;
     MSG      msg ;
     WNDCLASS wndclass ;

//     if (hPrevInstance) 
//          return FALSE ;
	 szAppName = pDDEServerData->getAppName();

     wndclass.style         = 0 ;
     wndclass.lpfnWndProc   = WndProc2 ;
     wndclass.cbClsExtra    = 0 ;
     wndclass.cbWndExtra    = 0 ;
     wndclass.hInstance     = hInstance ;
     wndclass.hIcon         = LoadIcon (hInstance, szAppName) ;
     wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
     wndclass.hbrBackground = (HBRUSH)GetStockObject (WHITE_BRUSH) ;
     wndclass.lpszMenuName  = NULL ;
     wndclass.lpszClassName = szAppName ;
//     wndclass.lpszClassName = pDDEServerData->getAppName();

     RegisterClass (&wndclass) ;

     hwnd = CreateWindow (szAppName, "TIDynSim Population Server",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT, CW_USEDEFAULT,
                          CW_USEDEFAULT, CW_USEDEFAULT,
                          NULL, NULL, hInstance, NULL) ;

	 if (!hwnd)
			ATLTRACE("Unable to create window\n");

     ShowWindow (hwnd, SW_HIDE);//SW_SHOWMINNOACTIVE) ;
     UpdateWindow (hwnd) ;

	 pDDEServerData->setTimerDDEHandle(hwnd);
               // Initialize for using DDEML

/*     pfnDdeCallback = MakeProcInstance ((FARPROC) DdeCallback, hInstance) ;

     if (DdeInitialize (&idInst, (PFNCALLBACK) pfnDdeCallback,
                        CBF_FAIL_EXECUTES | CBF_FAIL_POKES |
                        CBF_SKIP_REGISTRATIONS | CBF_SKIP_UNREGISTRATIONS, 0L))*/
 //    pfnDdeCallback = MakeProcInstance ((FARPROC) DdeCallback, hInstance) ;

     idInst = 0;
	 if (DdeInitialize (&idInst, (PFNCALLBACK) &DdeCallback,
                        CBF_FAIL_EXECUTES | CBF_FAIL_POKES |
                        CBF_SKIP_REGISTRATIONS | CBF_SKIP_UNREGISTRATIONS, 0L))
          {
          /*MessageBox (hwnd, "Could not initialize server!",
                      szAppName, MB_ICONEXCLAMATION | MB_OK) ;*/
		  ATLTRACE("Could not initialize DDE server - thread exit called and end DDE Window just created.\n");
          DestroyWindow (hwnd) ;
		  _endthread();
          }

                // Set the timer

//     if (!SetTimer (hwnd, ID_TIMER, 5000, NULL))
     if (!SetTimer (hwnd, ID_TIMER, pDDEServerData->getEvDDEServer()->getTimeStep(), NULL))
          {
          MessageBox (hwnd, "Too many clocks or timers!", szAppName,
                      MB_ICONEXCLAMATION | MB_OK) ;

          DestroyWindow (hwnd) ;
		  _endthread();
          }

               // Start things going

     SendMessage (hwnd, WM_USER_INITIATE, 0, 0L) ;

     while (GetMessage (&msg, NULL, 0, 0))
          {
          TranslateMessage (&msg) ;
          DispatchMessage (&msg) ;
          }

               // Clean up

     DdeUninitialize (idInst) ;
     KillTimer (hwnd, ID_TIMER) ;
//	 pDDEServerData->signalCloseTimerWindow(); // so that call from event releases
	 _endthread();
     }

/*int GetStateNumber (UINT iFmt, HSZ hszItem)
     {
     char szItem [32] ;
     int  i ;

     if (iFmt != CF_TEXT)
          return -1 ;

     DdeQueryString (idInst, hszItem, szItem, sizeof (szItem), 0) ;

     for (i = 0 ; i < NUM_STATES ; i++)
          if (strcmp (szItem, pop[i].szState) == 0)
               break ;

     if (i >= NUM_STATES)
          return -1 ;

     return i ;
     }*/

HDDEDATA FAR PASCAL _export DdeCallback (UINT iType, UINT iFmt, HCONV hConv,
                                         HSZ hsz1, HSZ hsz2, HDDEDATA hData,
                                         DWORD dwData1, DWORD dwData2)
     {
     char szBuffer [32] ;
     int  i ;

     switch (iType)
          {
          case XTYP_CONNECT:            // hsz1 = topic
                                        // hsz2 = service

               DdeQueryString (idInst, hsz2, szBuffer, sizeof (szBuffer), 0) ;

               if (0 != strcmp (szBuffer, szAppName))
                    return FALSE ;

               DdeQueryString (idInst, hsz1, szBuffer, sizeof (szBuffer), 0) ;

               if (0 != strcmp (szBuffer, szTopic))
                    return FALSE ;

               return (HDDEDATA)TRUE ;

          case XTYP_ADVSTART:           // hsz1 = topic
                                        // hsz2 = item

                    // Check for matching format and data item

			   if (iFmt!=CF_TEXT)
					return FALSE;

				 {
				 char szItem [32] ;
 
				 DdeQueryString (idInst, hsz2, szItem, sizeof (szItem), 0) ;

				 if (!pDDEServerData->getEvDDEServer()->findVariable(szItem))
						return false;


				 }

// BACK HERE              pop[i].lPopLast = 0 ;
               PostMessage (hwnd, WM_TIMER, 0, 0L) ;

               return (HDDEDATA)TRUE ;

          case XTYP_REQUEST:
          case XTYP_ADVREQ:             // hsz1 = topic
                                        // hsz2 = item

                    // Check for matching format and data item
				 try
				 {
				 MapStringDDE::const_iterator cit;
				 char szItem [32] ;
 
				 DdeQueryString (idInst, hsz2, szItem, sizeof (szItem), 0) ;


				 cit = mapResults.find(szItem);	
				 if (cit==mapResults.end()) // as we can't find it
						return NULL;

				 variable vTemp = cit->second;
				 ATLTRACE(cit->first.c_str());
				 ATLTRACE("\n");
				 ATLTRACE(" second = %d\n",cit->second);
				 ATLTRACE("\n");

			     _gcvt(vecResults[cit->second],20,szBuffer); // was 28 - reduced to avoid overwrite _gcvt bug
				 strcat(szBuffer,"\r\n");
				 ATLTRACE(szItem,szBuffer);
				 ATLTRACE("\n");
				 // maybe _gcvt _ecvt etc
//				 wsprintf (szBuffer, "%ed\r\n", pDDEServerData->getEvDDEServer()->getValue(szItem)) ;
				 }
				 catch(...) // since its possible to address unallocated memeory if we screw up
				 {
					ATLTRACE("Unhandled exception in XTYP_ADVREQ routine.\n");
					ASSERT2(false);
					return FALSE;

				 }

               return (HDDEDATA)DdeCreateDataHandle (idInst, (LPBYTE)szBuffer,
                                           strlen (szBuffer) + 1,
                                           0, hsz2, CF_TEXT, 0) ;

          case XTYP_ADVSTOP:            // hsz1 = topic
                                        // hsz2 = item

                    // Check for matching format and data item

				 try
				 {
				 MapStringDDE::const_iterator cit;
				 char szItem [32] ;
 
				 DdeQueryString (idInst, hsz2, szItem, sizeof (szItem), 0) ;


				 cit = mapResults.find(szItem);	
				 if (cit==mapResults.end()) // as we can't find it
						return FALSE;

				 ATLTRACE("XTYP_ADVSTOP for ",cit->first.c_str(),"\n");
				 }
				 catch(...) // since its possible to address unallocated memeory if we screw up
				 {
					ATLTRACE("Unhandled exception in XTYP_ADVSTOP routine.\n");
					ASSERT2(false);
					return FALSE;
				 }

//               if (-1 == (i = GetStateNumber (iFmt, hsz2)))
//                    return FALSE ;

               return (HDDEDATA)TRUE ;
          }

     return NULL ;
     }

long FAR PASCAL _export WndProc2 (HWND hwnd, UINT message, UINT wParam,
                                                          LONG lParam)
     {
     static HSZ  hszService, hszTopic ;
     HSZ         hszItem ;
//     int         i ;

     switch (message)
          {
          case WM_USER_INITIATE:
//               InitPops () ;

               hszService = DdeCreateStringHandle (idInst, szAppName, 0) ;
               hszTopic   = DdeCreateStringHandle (idInst, szTopic,   0) ;

               DdeNameService (idInst, hszService, NULL, DNS_REGISTER) ;
               return 0 ;

          case WM_TIMER:
          case WM_TIMECHANGE:

                    // Calculate new current populations

 //              CalcPops () ;
			// go and get a current and time conistent sample of results
			ATLTRACE("Size of mapResults WM_TIMECHANGE = %d\n",mapResults.size());

			pDDEServerData->getEvDDEServer()->updateWithResults(vecResults);

			{
			MapStringDDE::const_iterator cit;

			// fire signals for all items being watched
			for (cit=mapResults.begin();cit!=mapResults.end();cit++)
				{
                         hszItem = DdeCreateStringHandle (idInst,
                                                          cit->first.c_str(), 0) ;

                         DdePostAdvise (idInst, hszTopic, hszItem) ;

                         DdeFreeStringHandle (idInst, hszItem) ;
				
				}

 /*              for (i = 0 ; i < NUM_STATES ; i++)
                    if (pop[i].lPop != pop[i].lPopLast)
                         {
                         hszItem = DdeCreateStringHandle (idInst,
                                                          pop[i].szState, 0) ;

                         DdePostAdvise (idInst, hszTopic, hszItem) ;

                         DdeFreeStringHandle (idInst, hszItem) ;

                         pop[i].lPopLast = pop[i].lPop ;
                         }*/
				}
               return 0 ;

          case WM_QUERYOPEN:
               return 0 ;

#ifndef NDEBUG
		  case WM_CLOSE:
			   ATLTRACE("WM_CLOSE message processes %d \n",hwnd);
			   break;

		  case WM_QUIT:
			   ATLTRACE("WM_QUIT message processes %d \n",hwnd);
			   break;
#endif
          case WM_DESTROY:
			   ATLTRACE("WM_DESTROY recieved and being processed %d +++++\n",hwnd);
               DdeNameService (idInst, hszService, NULL, DNS_UNREGISTER) ;
               DdeFreeStringHandle (idInst, hszService) ;
               DdeFreeStringHandle (idInst, hszTopic) ;
				
			   if (!DdeUninitialize(idInst))
					ATLTRACE("DdeUninitialize(%d) failed\n",idInst);

               PostQuitMessage (0) ;
               return 0 ;
          }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
     }
