# Microsoft Developer Studio Project File - Name="Parser1" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=Parser1 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Parser1.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Parser1.mak" CFG="Parser1 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Parser1 - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "Parser1 - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Parser1 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GR /GX /O2 /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "WIN32_LEAN_AND_MEAN" /D "_NUMCAT_PRO" /FR /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /i "Symlix .." /i ".." /d "NDEBUG"
# SUBTRACT RSC /x
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /machine:I386

!ELSEIF  "$(CFG)" == "Parser1 - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GR /GX /ZI /Od /D "_DEBUG" /D "_CONSOLE" /D "DEBUGVARS" /D "_CRTDBG_MAP_ALLOC" /D "xEXTRADEBUG" /D "x_DEBUGMEM" /D "xCRASHHARD" /D "xNALPERION" /D "_xDEBUGSTRONGTYPE" /D "WIN32" /D "_MBCS" /D "WIN32_LEAN_AND_MEAN" /D "_NUMCAT_PRO" /D "UNITTESTS" /Fr /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /i ".." /d "_DEBUG"
# SUBTRACT RSC /x
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Parser1 - Win32 Release"
# Name "Parser1 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ARFileReader.cpp
# End Source File
# Begin Source File

SOURCE=.\Array.cpp
# End Source File
# Begin Source File

SOURCE=.\ArrayFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\ArrayImplied.cpp
# End Source File
# Begin Source File

SOURCE=.\ArrayLookup.cpp
# End Source File
# Begin Source File

SOURCE=.\ArraySeries.cpp
# End Source File
# Begin Source File

SOURCE=.\Cell.cpp
# End Source File
# Begin Source File

SOURCE=.\CellFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\CritCheck.cpp
# End Source File
# Begin Source File

SOURCE=.\csvHolder.cpp
# End Source File
# Begin Source File

SOURCE=.\csvHolderFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\csvLookup.cpp
# End Source File
# Begin Source File

SOURCE=.\csvNumArray.cpp
# End Source File
# Begin Source File

SOURCE=.\DateCell.cpp
# End Source File
# Begin Source File

SOURCE=.\DDESymlix.cpp
# End Source File
# Begin Source File

SOURCE=.\EmptyCell.cpp
# End Source File
# Begin Source File

SOURCE=.\EqIterative.cpp
# End Source File
# Begin Source File

SOURCE=.\EqLookup.cpp
# End Source File
# Begin Source File

SOURCE=.\EqSwitch.cpp
# End Source File
# Begin Source File

SOURCE=.\Equation.cpp
# End Source File
# Begin Source File

SOURCE=.\EquationFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\Symlix\ErrorFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\EvDDEServer.cpp
# End Source File
# Begin Source File

SOURCE=.\EvDump.cpp
# End Source File
# Begin Source File

SOURCE=.\EvDumpEquations.cpp
# End Source File
# Begin Source File

SOURCE=.\Event.cpp
# End Source File
# Begin Source File

SOURCE=.\EventFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\EvIteration.cpp
# End Source File
# Begin Source File

SOURCE=.\EvItValueStep.cpp
# End Source File
# Begin Source File

SOURCE=.\EvOnce.cpp
# End Source File
# Begin Source File

SOURCE=.\EvOutsideGetData.cpp
# End Source File
# Begin Source File

SOURCE=.\EvOutsideSetData.cpp
# End Source File
# Begin Source File

SOURCE=.\EvOutsideStop.cpp
# End Source File
# Begin Source File

SOURCE=.\EvPace.cpp
# End Source File
# Begin Source File

SOURCE=.\EvProgFeedback.cpp
# End Source File
# Begin Source File

SOURCE=.\EvRealTime.cpp
# End Source File
# Begin Source File

SOURCE=.\EvRecorder.cpp
# End Source File
# Begin Source File

SOURCE=.\EvRegressionTest.cpp
# End Source File
# Begin Source File

SOURCE=.\EvStart.cpp
# End Source File
# Begin Source File

SOURCE=.\EvStop.cpp
# End Source File
# Begin Source File

SOURCE=.\EvSync.cpp
# End Source File
# Begin Source File

SOURCE=.\EvValue.cpp
# End Source File
# Begin Source File

SOURCE=.\FuncIdentifierSingleton.cpp
# End Source File
# Begin Source File

SOURCE=.\Index.cpp
# End Source File
# Begin Source File

SOURCE=.\IndexExpandPoint.cpp
# End Source File
# Begin Source File

SOURCE=.\IndexFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\IndexForTo.cpp
# End Source File
# Begin Source File

SOURCE=.\IndexSeries.cpp
# End Source File
# Begin Source File

SOURCE=.\Model.cpp
# End Source File
# Begin Source File

SOURCE=.\NumCell.cpp
# End Source File
# Begin Source File

SOURCE=.\Parser1.cpp
# End Source File
# Begin Source File

SOURCE=.\SimRun.cpp
# End Source File
# Begin Source File

SOURCE=.\Simulation.cpp
# End Source File
# Begin Source File

SOURCE=.\SolClassFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\SolOneStep.cpp
# End Source File
# Begin Source File

SOURCE=.\SolRK3.cpp
# End Source File
# Begin Source File

SOURCE=.\SolRK3VS.cpp
# End Source File
# Begin Source File

SOURCE=.\SolRK4.cpp
# End Source File
# Begin Source File

SOURCE=.\SolRK4VS.cpp
# End Source File
# Begin Source File

SOURCE=.\SolRK4VSMT.cpp
# End Source File
# Begin Source File

SOURCE=.\SolRK5.cpp
# End Source File
# Begin Source File

SOURCE=.\SolRK5VS.cpp
# End Source File
# Begin Source File

SOURCE=.\SolVarStep.cpp
# End Source File
# Begin Source File

SOURCE=.\Solver.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StringCell.cpp
# End Source File
# Begin Source File

SOURCE=.\StringHolder.cpp
# End Source File
# Begin Source File

SOURCE=.\StringPlus.cpp
# End Source File
# Begin Source File

SOURCE=.\StrongTypeFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\SubExpression.cpp
# End Source File
# Begin Source File

SOURCE=.\Symlix\Symlix_i.c
# End Source File
# Begin Source File

SOURCE=.\Symlix\SymlixError.cpp
# End Source File
# Begin Source File

SOURCE=.\Symlix\SymlixErrorRun.cpp
# End Source File
# Begin Source File

SOURCE=.\SymlixStore_i.c
# End Source File
# Begin Source File

SOURCE=.\TempSetFix.cpp
# End Source File
# Begin Source File

SOURCE=.\Token.cpp
# End Source File
# Begin Source File

SOURCE=.\Tokeniser.cpp
# End Source File
# Begin Source File

SOURCE=.\VarClassFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\VarExp.cpp
# End Source File
# Begin Source File

SOURCE=.\VarExpression.cpp
# End Source File
# Begin Source File

SOURCE=.\VarMultiVarExpression.cpp
# End Source File
# Begin Source File

SOURCE=.\VarRoot.cpp
# End Source File
# Begin Source File

SOURCE=.\VarUnitTests.cpp
# End Source File
# Begin Source File

SOURCE=.\VarValue.cpp
# End Source File
# Begin Source File

SOURCE=.\VarVariable.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ARFileReader.h
# End Source File
# Begin Source File

SOURCE=.\Array.h
# End Source File
# Begin Source File

SOURCE=.\ArrayFactory.h
# End Source File
# Begin Source File

SOURCE=.\ArrayImplied.h
# End Source File
# Begin Source File

SOURCE=.\ArrayLookup.h
# End Source File
# Begin Source File

SOURCE=.\ArraySeries.h
# End Source File
# Begin Source File

SOURCE=.\Cell.h
# End Source File
# Begin Source File

SOURCE=.\CellFactory.h
# End Source File
# Begin Source File

SOURCE=.\CritCheck.h
# End Source File
# Begin Source File

SOURCE=.\csvException.h
# End Source File
# Begin Source File

SOURCE=.\csvHandlerAR.h
# End Source File
# Begin Source File

SOURCE=.\csvHolder.h
# End Source File
# Begin Source File

SOURCE=.\csvHolderFactory.h
# End Source File
# Begin Source File

SOURCE=.\csvLookup.h
# End Source File
# Begin Source File

SOURCE=.\csvNumArray.h
# End Source File
# Begin Source File

SOURCE=.\DateCell.h
# End Source File
# Begin Source File

SOURCE=.\DDESymlix.h
# End Source File
# Begin Source File

SOURCE=.\EmptyCell.h
# End Source File
# Begin Source File

SOURCE=.\EqLookup.h
# End Source File
# Begin Source File

SOURCE=.\EqSwitch.h
# End Source File
# Begin Source File

SOURCE=.\Equation.h
# End Source File
# Begin Source File

SOURCE=.\EquationFactory.h
# End Source File
# Begin Source File

SOURCE=.\Symlix\ErrorFactory.h
# End Source File
# Begin Source File

SOURCE=.\EvDDEServer.h
# End Source File
# Begin Source File

SOURCE=.\EvDump.h
# End Source File
# Begin Source File

SOURCE=.\EvDumpEquations.h
# End Source File
# Begin Source File

SOURCE=.\Event.h
# End Source File
# Begin Source File

SOURCE=.\EventFactory.h
# End Source File
# Begin Source File

SOURCE=.\EvIteration.h
# End Source File
# Begin Source File

SOURCE=.\EvItValueStep.h
# End Source File
# Begin Source File

SOURCE=.\EvOnce.h
# End Source File
# Begin Source File

SOURCE=.\EvOutsideGetData.h
# End Source File
# Begin Source File

SOURCE=.\EvOutsideSetData.h
# End Source File
# Begin Source File

SOURCE=.\EvOutsideStop.h
# End Source File
# Begin Source File

SOURCE=.\EvPace.h
# End Source File
# Begin Source File

SOURCE=.\EvProgFeedback.h
# End Source File
# Begin Source File

SOURCE=.\EvRealTime.h
# End Source File
# Begin Source File

SOURCE=.\EvRecorder.h
# End Source File
# Begin Source File

SOURCE=.\EvRegressionTest.h
# End Source File
# Begin Source File

SOURCE=.\EvStart.h
# End Source File
# Begin Source File

SOURCE=.\EvStop.h
# End Source File
# Begin Source File

SOURCE=.\EvSync.h
# End Source File
# Begin Source File

SOURCE=.\EvValue.h
# End Source File
# Begin Source File

SOURCE=.\FuncIdentifierSingleton.h
# End Source File
# Begin Source File

SOURCE=.\global.h
# End Source File
# Begin Source File

SOURCE=.\IModelSim.h
# End Source File
# Begin Source File

SOURCE=.\Index.h
# End Source File
# Begin Source File

SOURCE=.\IndexExpandPoint.h
# End Source File
# Begin Source File

SOURCE=.\IndexFactory.h
# End Source File
# Begin Source File

SOURCE=.\IndexForTo.h
# End Source File
# Begin Source File

SOURCE=.\IndexSeries.h
# End Source File
# Begin Source File

SOURCE=.\MemLeakRecord.h
# End Source File
# Begin Source File

SOURCE=.\Model.h
# End Source File
# Begin Source File

SOURCE=.\NumCell.h
# End Source File
# Begin Source File

SOURCE=.\SimRun.h
# End Source File
# Begin Source File

SOURCE=.\Simulation.h
# End Source File
# Begin Source File

SOURCE=.\SolClassFactory.h
# End Source File
# Begin Source File

SOURCE=.\SolOneStep.h
# End Source File
# Begin Source File

SOURCE=.\SolRK3.h
# End Source File
# Begin Source File

SOURCE=.\SolRK3VS.h
# End Source File
# Begin Source File

SOURCE=.\SolRK4.h
# End Source File
# Begin Source File

SOURCE=.\SolRK4VS.h
# End Source File
# Begin Source File

SOURCE=.\SolRK4VSMT.h
# End Source File
# Begin Source File

SOURCE=.\SolRK5.h
# End Source File
# Begin Source File

SOURCE=.\SolRK5VS.h
# End Source File
# Begin Source File

SOURCE=.\SolVarStep.h
# End Source File
# Begin Source File

SOURCE=.\Solver.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\StdAfxCommon.h
# End Source File
# Begin Source File

SOURCE=.\StringCell.h
# End Source File
# Begin Source File

SOURCE=.\StringHolder.h
# End Source File
# Begin Source File

SOURCE=.\StringPlus.h
# End Source File
# Begin Source File

SOURCE=.\StrongType.h
# End Source File
# Begin Source File

SOURCE=.\StrongTypeFactory.h
# End Source File
# Begin Source File

SOURCE=.\SubExpression.h
# End Source File
# Begin Source File

SOURCE=.\Symlix\Symlix.h
# End Source File
# Begin Source File

SOURCE=.\Symlix\SymlixError.h
# End Source File
# Begin Source File

SOURCE=.\Symlix\SymlixErrorRun.h
# End Source File
# Begin Source File

SOURCE=.\SymlixStore.h
# End Source File
# Begin Source File

SOURCE=.\TempSetFix.h
# End Source File
# Begin Source File

SOURCE=.\Token.h
# End Source File
# Begin Source File

SOURCE=.\Tokeniser.h
# End Source File
# Begin Source File

SOURCE=.\VarClassFactory.h
# End Source File
# Begin Source File

SOURCE=.\VarExp.h
# End Source File
# Begin Source File

SOURCE=.\VarExpression.h
# End Source File
# Begin Source File

SOURCE=.\VarMultiVarExpression.h
# End Source File
# Begin Source File

SOURCE=.\VarRoot.h
# End Source File
# Begin Source File

SOURCE=.\VarUnitTests.h
# End Source File
# Begin Source File

SOURCE=.\VarValue.h
# End Source File
# Begin Source File

SOURCE=.\VarVariable.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Delim.txt
# End Source File
# Begin Source File

SOURCE=.\InputDeck.txt
# End Source File
# Begin Source File

SOURCE=.\InputDeck_Fail.txt
# End Source File
# Begin Source File

SOURCE=.\InputDeck_old1.txt
# End Source File
# Begin Source File

SOURCE=.\InputDeck_Pass.txt
# End Source File
# Begin Source File

SOURCE=.\InputDeck_t1.txt
# End Source File
# Begin Source File

SOURCE=.\Results.txt
# End Source File
# Begin Source File

SOURCE=.\ToDo.txt
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
