# Microsoft Developer Studio Project File - Name="Symlix" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Symlix - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Symlix.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Symlix.mak" CFG="Symlix - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Symlix - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Symlix - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Symlix - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Symlix - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Symlix - Win32 Unicode Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Symlix - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Symlix - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GR /GX /ZI /Od /I ".." /I "C:\Inetpub\ftproot\cpp_new\ProjX" /I "C:\Inetpub\ftproot\cpp_new\ProjX\Symlix" /I "C:\Program Files\HTML Help Workshop\include" /D "_DEBUG" /D "_MBCS" /D "_xDEBUGMEM" /D "xEXTRADEBUG" /D "_xNOSTATUS_BAR" /D "xDEBUGVARS" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "_SYMLIX" /D "_NUMCAT_PRO" /FR /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 htmlhelp.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"Debug/NumCat.dll" /pdbtype:sept /libpath:"C:\Program Files\HTML Help Workshop\lib"
# Begin Custom Build - Performing registration
OutDir=.\Debug
TargetPath=.\Debug\NumCat.dll
InputPath=.\Debug\NumCat.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Symlix - Win32 Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugU"
# PROP BASE Intermediate_Dir "DebugU"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugU"
# PROP Intermediate_Dir "DebugU"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GR /GX /ZI /Od /I ".." /I "C:\Inetpub\ftproot\cpp_new\ProjX" /I "C:\Inetpub\ftproot\cpp_new\ProjX\Symlix" /I "C:\Program Files\HTML Help Workshop\include" /D "_DEBUG" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "_SYMLIX" /D "_xNUMCAT_PRO" /D "NUMCAT_DDE" /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib htmlhelp.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept /libpath:"C:\Program Files\HTML Help Workshop\lib"
# Begin Custom Build - Performing registration
OutDir=.\DebugU
TargetPath=.\DebugU\Symlix.dll
InputPath=.\DebugU\Symlix.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
	:end 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Symlix - Win32 Release MinSize"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMinSize"
# PROP BASE Intermediate_Dir "ReleaseMinSize"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMinSize"
# PROP Intermediate_Dir "ReleaseMinSize"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GR /GX /O1 /I ".." /I "C:\Inetpub\ftproot\cpp_new\ProjX" /I "C:\Inetpub\ftproot\cpp_new\ProjX\Symlix" /I "C:\Program Files\HTML Help Workshop\include" /D "NDEBUG" /D "_MBCS" /D "_ATL_DLL" /D "x_ATL_MIN_CRT" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "_SYMLIX" /D "_xNUMCAT_PRO" /D "NUMCAT_DDE" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib htmlhelp.lib /nologo /subsystem:windows /dll /machine:I386 /out:"ReleaseMinSize/NumCat.dll" /libpath:"C:\Program Files\HTML Help Workshop\lib"
# Begin Custom Build - Performing registration
OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\NumCat.dll
InputPath=.\ReleaseMinSize\NumCat.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Symlix - Win32 Release MinDependency"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMinDependency"
# PROP BASE Intermediate_Dir "ReleaseMinDependency"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMinDependency"
# PROP Intermediate_Dir "ReleaseMinDependency"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GR /GX /O1 /I ".." /I "C:\Inetpub\ftproot\cpp_new\ProjX" /I "C:\Inetpub\ftproot\cpp_new\ProjX\Symlix" /I "C:\Program Files\HTML Help Workshop\include" /D "NDEBUG" /D "_MBCS" /D "_ATL_STATIC_REGISTRY" /D "x_ATL_MIN_CRT" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "_SYMLIX" /D "_xNUMCAT_PRO" /D "NUMCAT_DDE" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib htmlhelp.lib /nologo /subsystem:windows /dll /machine:I386 /out:"ReleaseMinDependency/NumCat.dll" /libpath:"C:\Program Files\HTML Help Workshop\lib"
# Begin Custom Build - Performing registration
OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\NumCat.dll
InputPath=.\ReleaseMinDependency\NumCat.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Symlix - Win32 Unicode Release MinSize"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseUMinSize"
# PROP BASE Intermediate_Dir "ReleaseUMinSize"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseUMinSize"
# PROP Intermediate_Dir "ReleaseUMinSize"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GR /GX /O1 /I ".." /I "C:\Inetpub\ftproot\cpp_new\ProjX" /I "C:\Inetpub\ftproot\cpp_new\ProjX\Symlix" /I "C:\Program Files\HTML Help Workshop\include" /D "NDEBUG" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "_SYMLIX" /D "_xNUMCAT_PRO" /D "NUMCAT_DDE" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib htmlhelp.lib /nologo /subsystem:windows /dll /machine:I386 /libpath:"C:\Program Files\HTML Help Workshop\lib"
# Begin Custom Build - Performing registration
OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\Symlix.dll
InputPath=.\ReleaseUMinSize\Symlix.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
	:end 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Symlix - Win32 Unicode Release MinDependency"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseUMinDependency"
# PROP BASE Intermediate_Dir "ReleaseUMinDependency"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseUMinDependency"
# PROP Intermediate_Dir "ReleaseUMinDependency"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GR /GX /O1 /I ".." /I "C:\Inetpub\ftproot\cpp_new\ProjX" /I "C:\Inetpub\ftproot\cpp_new\ProjX\Symlix" /I "C:\Program Files\HTML Help Workshop\include" /D "NDEBUG" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "_SYMLIX" /D "_xNUMCAT_PRO" /D "NUMCAT_DDE" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib htmlhelp.lib /nologo /subsystem:windows /dll /machine:I386 /libpath:"C:\Program Files\HTML Help Workshop\lib"
# Begin Custom Build - Performing registration
OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\Symlix.dll
InputPath=.\ReleaseUMinDependency\Symlix.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
	:end 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "Symlix - Win32 Debug"
# Name "Symlix - Win32 Unicode Debug"
# Name "Symlix - Win32 Release MinSize"
# Name "Symlix - Win32 Release MinDependency"
# Name "Symlix - Win32 Unicode Release MinSize"
# Name "Symlix - Win32 Unicode Release MinDependency"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ARDataPost.cpp
# End Source File
# Begin Source File

SOURCE=.\ARDataPostOffice.cpp
# End Source File
# Begin Source File

SOURCE=.\ARDPKey.cpp
# End Source File
# Begin Source File

SOURCE=.\ARDRM.cpp
# End Source File
# Begin Source File

SOURCE=..\ARFileReader.cpp
# End Source File
# Begin Source File

SOURCE=.\ARL_DRM.cpp
# End Source File
# Begin Source File

SOURCE=.\ARLatlBasicHoldWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\ARLatlDividerWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\ARLatlSplitWndsHoriz.cpp
# End Source File
# Begin Source File

SOURCE=.\ARLatlSplitWndsVert.cpp
# End Source File
# Begin Source File

SOURCE=..\Array.cpp
# End Source File
# Begin Source File

SOURCE=..\ArrayFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\ArrayImplied.cpp
# End Source File
# Begin Source File

SOURCE=..\ArrayLookup.cpp
# End Source File
# Begin Source File

SOURCE=..\ArraySeries.cpp
# End Source File
# Begin Source File

SOURCE=.\ARRunProgress.cpp
# End Source File
# Begin Source File

SOURCE=..\Cell.cpp
# End Source File
# Begin Source File

SOURCE=..\CellFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\CritCheck.cpp
# End Source File
# Begin Source File

SOURCE=..\csvHolder.cpp
# End Source File
# Begin Source File

SOURCE=..\csvHolderFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\csvLookup.cpp
# End Source File
# Begin Source File

SOURCE=..\csvNumArray.cpp
# End Source File
# Begin Source File

SOURCE=..\DateCell.cpp
# End Source File
# Begin Source File

SOURCE=..\DDESymlix.cpp
# End Source File
# Begin Source File

SOURCE=.\DispParam.cpp
# End Source File
# Begin Source File

SOURCE=.\dlldatax.c
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\EmptyCell.cpp
# End Source File
# Begin Source File

SOURCE=..\EqLookup.cpp
# End Source File
# Begin Source File

SOURCE=..\EqSwitch.cpp
# End Source File
# Begin Source File

SOURCE=..\Equation.cpp
# End Source File
# Begin Source File

SOURCE=..\EquationFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\ErrorFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\EvDDEServer.cpp
# End Source File
# Begin Source File

SOURCE=..\EvDump.cpp
# End Source File
# Begin Source File

SOURCE=..\EvDumpEquations.cpp
# End Source File
# Begin Source File

SOURCE=..\Event.cpp
# End Source File
# Begin Source File

SOURCE=..\EventFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\EvIteration.cpp
# End Source File
# Begin Source File

SOURCE=..\EvItValueStep.cpp
# End Source File
# Begin Source File

SOURCE=..\EvOnce.cpp
# End Source File
# Begin Source File

SOURCE=..\EvOutsideGetData.cpp
# End Source File
# Begin Source File

SOURCE=..\EvOutsideSetData.cpp
# End Source File
# Begin Source File

SOURCE=..\EvOutsideStop.cpp
# End Source File
# Begin Source File

SOURCE=..\EvPace.cpp
# End Source File
# Begin Source File

SOURCE=..\EvProgFeedback.cpp
# End Source File
# Begin Source File

SOURCE=..\EvRealTime.cpp
# End Source File
# Begin Source File

SOURCE=..\EvRecorder.cpp
# End Source File
# Begin Source File

SOURCE=..\EvRegressionTest.cpp
# End Source File
# Begin Source File

SOURCE=..\EvStart.cpp
# End Source File
# Begin Source File

SOURCE=..\EvStop.cpp
# End Source File
# Begin Source File

SOURCE=..\EvSync.cpp
# End Source File
# Begin Source File

SOURCE=..\EvValue.cpp
# End Source File
# Begin Source File

SOURCE=..\FuncIdentifierSingleton.cpp
# End Source File
# Begin Source File

SOURCE=..\Index.cpp
# End Source File
# Begin Source File

SOURCE=..\IndexExpandPoint.cpp
# End Source File
# Begin Source File

SOURCE=..\IndexFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\IndexForTo.cpp
# End Source File
# Begin Source File

SOURCE=..\IndexSeries.cpp
# End Source File
# Begin Source File

SOURCE=..\Model.cpp
# End Source File
# Begin Source File

SOURCE=.\NumCatExcelLocalRes.cpp
# End Source File
# Begin Source File

SOURCE=.\NumCatResource.cpp
# End Source File
# Begin Source File

SOURCE=..\NumCell.cpp
# End Source File
# Begin Source File

SOURCE=..\Relation.cpp
# End Source File
# Begin Source File

SOURCE=..\SimRun.cpp
# End Source File
# Begin Source File

SOURCE=..\Simulation.cpp
# End Source File
# Begin Source File

SOURCE=..\SolClassFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\SolOneStep.cpp
# End Source File
# Begin Source File

SOURCE=..\SolRK3.cpp
# End Source File
# Begin Source File

SOURCE=..\SolRK3VS.cpp
# End Source File
# Begin Source File

SOURCE=..\SolRK4.cpp
# End Source File
# Begin Source File

SOURCE=..\SolRK4VS.cpp
# End Source File
# Begin Source File

SOURCE=..\SolRK4VSMT.cpp
# End Source File
# Begin Source File

SOURCE=..\SolRK5.cpp
# End Source File
# Begin Source File

SOURCE=..\SolRK5VS.cpp
# End Source File
# Begin Source File

SOURCE=..\SolVarStep.cpp
# End Source File
# Begin Source File

SOURCE=..\Solver.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\StringCell.cpp
# End Source File
# Begin Source File

SOURCE=..\StringHolder.cpp
# End Source File
# Begin Source File

SOURCE=..\StringPlus.cpp
# End Source File
# Begin Source File

SOURCE=..\StrongTypeFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\SubExpression.cpp
# End Source File
# Begin Source File

SOURCE=.\SymEdErrList.cpp
# End Source File
# Begin Source File

SOURCE=.\SymEditor.cpp
# End Source File
# Begin Source File

SOURCE=.\SymEdLine.cpp
# End Source File
# Begin Source File

SOURCE=.\Symlix.cpp
# End Source File
# Begin Source File

SOURCE=.\Symlix.def
# End Source File
# Begin Source File

SOURCE=.\Symlix.idl
# ADD MTL /tlb ".\Symlix.tlb" /h "Symlix.h" /iid "Symlix_i.c" /Oicf
# End Source File
# Begin Source File

SOURCE=.\Symlix.rc
# End Source File
# Begin Source File

SOURCE=.\SymlixComp.cpp
# End Source File
# Begin Source File

SOURCE=.\SymlixEditor.cpp
# End Source File
# Begin Source File

SOURCE=.\SymlixError.cpp
# End Source File
# Begin Source File

SOURCE=.\SymlixErrorRun.cpp
# End Source File
# Begin Source File

SOURCE=.\SymlixHiddenDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\SymlixStore_i.c
# End Source File
# Begin Source File

SOURCE=.\SymRunProgressDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\TempSetFix.cpp
# End Source File
# Begin Source File

SOURCE=..\Token.cpp
# End Source File
# Begin Source File

SOURCE=..\Tokeniser.cpp
# End Source File
# Begin Source File

SOURCE=.\TraceRecorder_i.c
# End Source File
# Begin Source File

SOURCE=..\VarClassFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\VarExp.cpp
# End Source File
# Begin Source File

SOURCE=..\VarExpression.cpp
# End Source File
# Begin Source File

SOURCE=..\VarMultiVarExpression.cpp
# End Source File
# Begin Source File

SOURCE=..\VarRoot.cpp
# End Source File
# Begin Source File

SOURCE=..\VarUnitTests.cpp
# End Source File
# Begin Source File

SOURCE=..\VarValue.cpp
# End Source File
# Begin Source File

SOURCE=..\VarVariable.cpp
# End Source File
# Begin Source File

SOURCE=.\WndProcSafeSwapper.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\aboutdlg.h
# End Source File
# Begin Source File

SOURCE=.\ARDataPost.h
# End Source File
# Begin Source File

SOURCE=.\ARDataPostOffice.h
# End Source File
# Begin Source File

SOURCE=.\ARDPKey.h
# End Source File
# Begin Source File

SOURCE=.\ARDRM.h
# End Source File
# Begin Source File

SOURCE=..\ARFileReader.h
# End Source File
# Begin Source File

SOURCE=.\ARL_DRM.h
# End Source File
# Begin Source File

SOURCE=.\ARLatlBasicHoldWnd.h
# End Source File
# Begin Source File

SOURCE=.\ARLatlDividerWnd.h
# End Source File
# Begin Source File

SOURCE=.\ARLatlSplitWndsHoriz.h
# End Source File
# Begin Source File

SOURCE=.\ARLatlSplitWndsVert.h
# End Source File
# Begin Source File

SOURCE=..\Array.h
# End Source File
# Begin Source File

SOURCE=..\ArrayFactory.h
# End Source File
# Begin Source File

SOURCE=..\ArrayImplied.h
# End Source File
# Begin Source File

SOURCE=..\ArrayLookup.h
# End Source File
# Begin Source File

SOURCE=..\ArraySeries.h
# End Source File
# Begin Source File

SOURCE=.\ARRunProgress.h
# End Source File
# Begin Source File

SOURCE=..\Cell.h
# End Source File
# Begin Source File

SOURCE=..\CellFactory.h
# End Source File
# Begin Source File

SOURCE=.\CopyProtection.h
# End Source File
# Begin Source File

SOURCE=..\CritCheck.h
# End Source File
# Begin Source File

SOURCE=..\csvException.h
# End Source File
# Begin Source File

SOURCE=..\csvHandlerAR.h
# End Source File
# Begin Source File

SOURCE=..\csvHolder.h
# End Source File
# Begin Source File

SOURCE=..\csvHolderFactory.h
# End Source File
# Begin Source File

SOURCE=..\csvLookup.h
# End Source File
# Begin Source File

SOURCE=..\csvNumArray.h
# End Source File
# Begin Source File

SOURCE=.\ctxNumCatHelp.h
# End Source File
# Begin Source File

SOURCE=..\DateCell.h
# End Source File
# Begin Source File

SOURCE=..\DDESymlix.h
# End Source File
# Begin Source File

SOURCE=.\DispParam.h
# End Source File
# Begin Source File

SOURCE=.\dlldatax.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\EmptyCell.h
# End Source File
# Begin Source File

SOURCE=..\EqLookup.h
# End Source File
# Begin Source File

SOURCE=..\EqSwitch.h
# End Source File
# Begin Source File

SOURCE=..\Equation.h
# End Source File
# Begin Source File

SOURCE=..\EquationFactory.h
# End Source File
# Begin Source File

SOURCE=.\ErrorFactory.h
# End Source File
# Begin Source File

SOURCE=..\EvDDEServer.h
# End Source File
# Begin Source File

SOURCE=..\EvDump.h
# End Source File
# Begin Source File

SOURCE=..\EvDumpEquations.h
# End Source File
# Begin Source File

SOURCE=..\Event.h
# End Source File
# Begin Source File

SOURCE=..\EventFactory.h
# End Source File
# Begin Source File

SOURCE=..\EvIteration.h
# End Source File
# Begin Source File

SOURCE=..\EvItValueStep.h
# End Source File
# Begin Source File

SOURCE=..\EvOnce.h
# End Source File
# Begin Source File

SOURCE=..\EvOutsideGetData.h
# End Source File
# Begin Source File

SOURCE=..\EvOutsideSetData.h
# End Source File
# Begin Source File

SOURCE=..\EvOutsideStop.h
# End Source File
# Begin Source File

SOURCE=..\EvPace.h
# End Source File
# Begin Source File

SOURCE=..\EvProgFeedback.h
# End Source File
# Begin Source File

SOURCE=..\EvRealTime.h
# End Source File
# Begin Source File

SOURCE=..\EvRecorder.h
# End Source File
# Begin Source File

SOURCE=..\EvRegressionTest.h
# End Source File
# Begin Source File

SOURCE=..\EvStart.h
# End Source File
# Begin Source File

SOURCE=..\EvStop.h
# End Source File
# Begin Source File

SOURCE=..\EvSync.h
# End Source File
# Begin Source File

SOURCE=..\EvValue.h
# End Source File
# Begin Source File

SOURCE=..\FuncIdentifierSingleton.h
# End Source File
# Begin Source File

SOURCE=..\global.h
# End Source File
# Begin Source File

SOURCE=..\IModelSim.h
# End Source File
# Begin Source File

SOURCE=..\Index.h
# End Source File
# Begin Source File

SOURCE=..\IndexExpandPoint.h
# End Source File
# Begin Source File

SOURCE=..\IndexFactory.h
# End Source File
# Begin Source File

SOURCE=..\IndexForTo.h
# End Source File
# Begin Source File

SOURCE=..\IndexSeries.h
# End Source File
# Begin Source File

SOURCE=..\MemLeakRecord.h
# End Source File
# Begin Source File

SOURCE=..\Model.h
# End Source File
# Begin Source File

SOURCE=.\NumCatExcelLocalRes.h
# End Source File
# Begin Source File

SOURCE=.\NumCatResource.h
# End Source File
# Begin Source File

SOURCE=..\NumCell.h
# End Source File
# Begin Source File

SOURCE=..\Relation.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=..\SimRun.h
# End Source File
# Begin Source File

SOURCE=..\Simulation.h
# End Source File
# Begin Source File

SOURCE=..\SolClassFactory.h
# End Source File
# Begin Source File

SOURCE=..\SolOneStep.h
# End Source File
# Begin Source File

SOURCE=..\SolRK3.h
# End Source File
# Begin Source File

SOURCE=..\SolRK3VS.h
# End Source File
# Begin Source File

SOURCE=..\SolRK4.h
# End Source File
# Begin Source File

SOURCE=..\SolRK4VS.h
# End Source File
# Begin Source File

SOURCE=..\SolRK4VSMT.h
# End Source File
# Begin Source File

SOURCE=..\SolRK5.h
# End Source File
# Begin Source File

SOURCE=..\SolRK5VS.h
# End Source File
# Begin Source File

SOURCE=..\SolVarStep.h
# End Source File
# Begin Source File

SOURCE=..\Solver.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\StdAfxCommon.h
# End Source File
# Begin Source File

SOURCE=..\StringCell.h
# End Source File
# Begin Source File

SOURCE=..\StringHolder.h
# End Source File
# Begin Source File

SOURCE=..\StringPlus.h
# End Source File
# Begin Source File

SOURCE=..\StrongType.h
# End Source File
# Begin Source File

SOURCE=..\StrongTypeFactory.h
# End Source File
# Begin Source File

SOURCE=..\SubExpression.h
# End Source File
# Begin Source File

SOURCE=.\SymEdErrList.h
# End Source File
# Begin Source File

SOURCE=.\SymEditMainFrm.h
# End Source File
# Begin Source File

SOURCE=.\SymEditor.h
# End Source File
# Begin Source File

SOURCE=.\SymEdLine.h
# End Source File
# Begin Source File

SOURCE=.\SymlixComp.h
# End Source File
# Begin Source File

SOURCE=.\SymlixCP.h
# End Source File
# Begin Source File

SOURCE=.\SymlixEditor.h
# End Source File
# Begin Source File

SOURCE=.\SymlixError.h
# End Source File
# Begin Source File

SOURCE=.\SymlixErrorRun.h
# End Source File
# Begin Source File

SOURCE=.\SymlixHiddenDlg.h
# End Source File
# Begin Source File

SOURCE=..\SymlixStore.h
# End Source File
# Begin Source File

SOURCE=.\SymRunProgressDlg.h
# End Source File
# Begin Source File

SOURCE=..\TempSetFix.h
# End Source File
# Begin Source File

SOURCE=..\Token.h
# End Source File
# Begin Source File

SOURCE=..\Tokeniser.h
# End Source File
# Begin Source File

SOURCE=.\TraceRecorder.h
# End Source File
# Begin Source File

SOURCE=..\VarClassFactory.h
# End Source File
# Begin Source File

SOURCE=..\VarExp.h
# End Source File
# Begin Source File

SOURCE=..\VarExpression.h
# End Source File
# Begin Source File

SOURCE=..\VarMultiVarExpression.h
# End Source File
# Begin Source File

SOURCE=..\VarRoot.h
# End Source File
# Begin Source File

SOURCE=..\VarUnitTests.h
# End Source File
# Begin Source File

SOURCE=..\VarValue.h
# End Source File
# Begin Source File

SOURCE=..\VarVariable.h
# End Source File
# Begin Source File

SOURCE=.\WndProcSafeSwapper.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\ARDataPost.rgs
# End Source File
# Begin Source File

SOURCE=.\ARL_DRM.rgs
# End Source File
# Begin Source File

SOURCE=.\ARRunProgress.rgs
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmaphe.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmapnu.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmapru.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00004.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CommandBut1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CommandBut2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CommandMask1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\logo1.bmp
# End Source File
# Begin Source File

SOURCE=.\NumCatDRM.rgs
# End Source File
# Begin Source File

SOURCE=.\NumCatExcelLocalRes.rgs
# End Source File
# Begin Source File

SOURCE=.\NumCatResource.rgs
# End Source File
# Begin Source File

SOURCE=.\res\numcattr.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SimpleEditExample.ico
# End Source File
# Begin Source File

SOURCE=.\Symlix.rgs
# End Source File
# Begin Source File

SOURCE=.\SymlixEditor.rgs
# End Source File
# Begin Source File

SOURCE=.\SymlixError.rgs
# End Source File
# Begin Source File

SOURCE=.\SymlixErrorRun.rgs
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# End Group
# End Target
# End Project
# Section Symlix : {00000000-0000-0000-0000-800000800000}
# 	1:21:IDD_SYMRUNPROGRESSDLG:108
# End Section
