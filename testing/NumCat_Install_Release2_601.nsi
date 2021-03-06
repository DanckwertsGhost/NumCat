; Script generated by the HM NIS Edit Script Wizard.

; HM NIS Edit Wizard helper defines
!define PRODUCT_NAME "Numerical Catalyst"
!define PRODUCT_VERSION "2.602"
!define PRODUCT_PUBLISHER "Aston Read Limited"
!define PRODUCT_WEB_SITE "http://www.numericalcatalyst.com"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\NumCat.dll"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"
!define PRODUCT_STARTMENU_REGVAL "NSIS:StartMenuDir"

!define SYMLIX_WORKDIR "$DOCUMENTS\Numerical Catalyst"

var ACTIVATION_EXE

var FilesRequested
var FilesFound
var RegValue
var vSubKey
var vEntry
var vComObjects
var vExcelVers
;var v2007Plus
var vNumCatAddIn

; MUI 1.67 compatible ------
!include "MUI2.nsh"
!include Library.nsh
!include "ExcelAddIn.nsh"
!include "dotNetInstallAuto.nsh"


CRCCheck on
;XPStyle on
; MUI Settings
!define MUI_ABORTWARNING
!define MUI_ICON "..\..\cpp_new\ProjX\Symlix\res\SimpleEditExample.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"

; Language Selection Dialog Settings
!define MUI_LANGDLL_REGISTRY_ROOT "${PRODUCT_UNINST_ROOT_KEY}"
!define MUI_LANGDLL_REGISTRY_KEY "${PRODUCT_UNINST_KEY}"
!define MUI_LANGDLL_REGISTRY_VALUENAME "NSIS:Language"

!macro DeleteInstallation
  ;Unregister DLL's a service first
  !insertmacro UnInstallLib REGDLL SHARED REBOOT_NOTPROTECTED $INSTDIR\NumCat.dll
  !insertmacro UnInstallLib REGDLL SHARED REBOOT_NOTPROTECTED $INSTDIR\TraceRecorder2.dll
  !insertmacro UnInstallLib REGDLL SHARED REBOOT_NOTPROTECTED $INSTDIR\ARStore.dll

;  ExecWait "$INSTDIR\TraceRecorder /UNREGSERVER"

  !insertmacro MUI_STARTMENU_GETFOLDER "Application" $ICONS_GROUP
  Delete "$INSTDIR\${PRODUCT_NAME}.url"
  ;Delete "$SYSDIR\ASTSRV.EXE" ; leave this as may be used by other applications
  Delete "$INSTDIR\uninst.exe"
  Delete "$INSTDIR\boxsmall.jpg"
  Delete "$INSTDIR\Connection.exe"
  Delete "$INSTDIR\ControlActivation.exe"
  Delete "$INSTDIR\ControlActivation.exe.config"
  Delete "$INSTDIR\filechck.dll"
  Delete "$INSTDIR\SpinningProgress.dll"
  Delete "$INSTDIR\Update.dat"
  Delete "$INSTDIR\update.exe"
  Delete "$INSTDIR\Version.ini"
  Delete "$INSTDIR\Using License Manager.doc"
  Delete "$INSTDIR\help-manager.chm"
  Delete "$INSTDIR\License Manager.exe"

  Delete "$INSTDIR\NumCat.dll"
  Delete "$INSTDIR\TraceRecorder2.dll"
  Delete "$INSTDIR\ARStore.dll"
  Delete "$INSTDIR\NumCat.chm"
  Delete "$INSTDIR\ReadMe.html"
  Delete "$INSTDIR\NumCatalyst.jpg"
  Delete "$INSTDIR\FileChck.lib"
  Delete "$INSTDIR\NumCat.xla"
  Delete "$INSTDIR\NumCat.xlam"
  
  Delete "$INSTDIR\ArmAccess.dll"
  
  Delete "${SYMLIX_WORKDIR}\sample.xls"
  Delete "${SYMLIX_WORKDIR}\lookup1.xls"
  Delete "${SYMLIX_WORKDIR}\limits.xls"
  Delete "${SYMLIX_WORKDIR}\SkyDiver.xls"
  Delete "${SYMLIX_WORKDIR}\CaseStudies.xls"
  Delete "${SYMLIX_WORKDIR}\ArrayExample.xls"
  Delete "${SYMLIX_WORKDIR}\DCFexample1.xls"
  Delete "${SYMLIX_WORKDIR}\Heart.xls"
  Delete "${SYMLIX_WORKDIR}\traceSymlix.txt" ; take the debug file also
  Delete "${SYMLIX_WORKDIR}\ChemEng\CO_CSTR1.xls" ; wonder if should leave these files ?
  Delete "${SYMLIX_WORKDIR}\ChemEng\TankLevelControl.xls" ; wonder if should leave these files ?
  Delete "${SYMLIX_WORKDIR}\ChemEng\Batch_Distillation.xls"
  Delete "${SYMLIX_WORKDIR}\ChemEng\BatchDistill_Index.xls"
  Delete "${SYMLIX_WORKDIR}\Maths\Analytical1.xls" ; wonder if should leave these files ?
  Delete "${SYMLIX_WORKDIR}\Maths\Lorenz1.xls" ; wonder if should leave these files ?
  Delete "${SYMLIX_WORKDIR}\sample.xlsx"
  Delete "${SYMLIX_WORKDIR}\lookup1.xlsx"
  Delete "${SYMLIX_WORKDIR}\limits.xlsx"
  Delete "${SYMLIX_WORKDIR}\SkyDiver.xlsx"
  Delete "${SYMLIX_WORKDIR}\CaseStudies.xlsm"
  Delete "${SYMLIX_WORKDIR}\ChemEng\CO_CSTR1.xlsx" ; wonder if should leave these files ?
  Delete "${SYMLIX_WORKDIR}\ChemEng\TankLevelControl.xlsx" ; wonder if should leave these files ?
  Delete "${SYMLIX_WORKDIR}\ChemEng\Batch_Distillation.xlsx"
  Delete "${SYMLIX_WORKDIR}\Maths\Analytical1.xlsx" ; wonder if should leave these files ?
  Delete "${SYMLIX_WORKDIR}\Maths\Lorenz1.xlsx" ; wonder if should leave these files ?

;  Delete "$INSTDIR\Uninstall.exe"

  Delete "$SMPROGRAMS\$ICONS_GROUP\Uninstall.lnk"
  Delete "$SMPROGRAMS\$ICONS_GROUP\Numerical Catalyst Website.lnk"
  Delete "$SMPROGRAMS\$ICONS_GROUP\Manage License.lnk"
  Delete "$SMPROGRAMS\$ICONS_GROUP\Manage License No dotNet.lnk"
  Delete "$SMPROGRAMS\$ICONS_GROUP\Release Notes.lnk"
  Delete "$SMPROGRAMS\$ICONS_GROUP\Sample.lnk"
  Delete "$SMPROGRAMS\$ICONS_GROUP\Help.lnk"
  Delete "$SMPROGRAMS\$ICONS_GROUP\Numerical Catalyst examples.lnk"

  RMDir "$SMPROGRAMS\$ICONS_GROUP"
  RMDir "$INSTDIR"
  RMDir "${SYMLIX_WORKDIR}"

  DeleteRegValue HKCU "$ExcelPath\Add-in Manager" "$INSTDIR\NumCat.xla"
  DeleteRegValue HKCU "$ExcelPath\Add-in Manager" "$INSTDIR\NumCat.xlam"

  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
!macroend

; Welcome page
!insertmacro MUI_PAGE_WELCOME
; License page
;!define MUI_LICENSEPAGE_CHECKBOX
!insertmacro MUI_PAGE_LICENSE "NumCatLicence.txt"
; Components page
!insertmacro MUI_PAGE_COMPONENTS
; Directory page
;!define MUI_DIRECTORYPAGE_TEXT_DESTINATION "C:\Temp"
;!define MUI_DIRECTORYPAGE_VERIFYONLEAVE
!insertmacro MUI_PAGE_DIRECTORY
;!define MUI_DIRECTORYPAGE_VARIABLE $ANOTHERFOLDER
;!insertmacro MUI_PAGE_DIRECTORY

; Start menu page
var ICONS_GROUP
var TRACEINST
!define MUI_STARTMENUPAGE_NODISABLE
!define MUI_STARTMENUPAGE_DEFAULTFOLDER "Numerical Catalyst"
!define MUI_STARTMENUPAGE_REGISTRY_ROOT "${PRODUCT_UNINST_ROOT_KEY}"
!define MUI_STARTMENUPAGE_REGISTRY_KEY "${PRODUCT_UNINST_KEY}"
!define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "${PRODUCT_STARTMENU_REGVAL}"
!insertmacro MUI_PAGE_STARTMENU Application $ICONS_GROUP
; Instfiles page
!insertmacro MUI_PAGE_INSTFILES
; Finish page
!define MUI_FINISHPAGE_NOREBOOTSUPPORT
;!define MUI_FINISHPAGE_RUN_NOTCHECKED
;!define MUI_FINISHPAGE_RUN_TEXT "Activate Numerical Catalyst"
;!define MUI_FINISHPAGE_RUN "$ACTIVATION_EXE"
!define MUI_FINISHPAGE_SHOWREADME_NOTCHECKED
!define MUI_FINISHPAGE_SHOWREADME_TEXT "ReadMe notes" ; defined in header
;!define MUI_FINISHPAGE_SHOWREADME_TEXT "ReadMe notes and link for $(DESC_SHORTDOTNET)" ; defined in header
!define MUI_FINISHPAGE_SHOWREADME "$INSTDIR\ReadMe.html"
;!define MUI_FINISHPAGE_LINK "Link to dot Net 2 runtime."
;!define MUI_FINISHPAGE_LINK_LOCATION "http://www.microsoft.com/downloads"
!insertmacro MUI_PAGE_FINISH

; Uninstaller pages
!insertmacro MUI_UNPAGE_INSTFILES

; Language files
!insertmacro MUI_LANGUAGE "Afrikaans"
!insertmacro MUI_LANGUAGE "Arabic"
!insertmacro MUI_LANGUAGE "Bulgarian"
!insertmacro MUI_LANGUAGE "Czech"
!insertmacro MUI_LANGUAGE "Danish"
!insertmacro MUI_LANGUAGE "Dutch"
!insertmacro MUI_LANGUAGE "English"
!insertmacro MUI_LANGUAGE "Estonian"
!insertmacro MUI_LANGUAGE "Finnish"
!insertmacro MUI_LANGUAGE "French"
!insertmacro MUI_LANGUAGE "German"
!insertmacro MUI_LANGUAGE "Greek"
!insertmacro MUI_LANGUAGE "Hebrew"
!insertmacro MUI_LANGUAGE "Hungarian"
!insertmacro MUI_LANGUAGE "Icelandic"
!insertmacro MUI_LANGUAGE "Indonesian"
!insertmacro MUI_LANGUAGE "Italian"
!insertmacro MUI_LANGUAGE "Japanese"
!insertmacro MUI_LANGUAGE "Korean"
!insertmacro MUI_LANGUAGE "Kurdish"
!insertmacro MUI_LANGUAGE "Latvian"
!insertmacro MUI_LANGUAGE "Lithuanian"
!insertmacro MUI_LANGUAGE "Norwegian"
!insertmacro MUI_LANGUAGE "NorwegianNynorsk"
!insertmacro MUI_LANGUAGE "Polish"
!insertmacro MUI_LANGUAGE "Portuguese"
!insertmacro MUI_LANGUAGE "Russian"
!insertmacro MUI_LANGUAGE "Serbian"
!insertmacro MUI_LANGUAGE "Slovak"
!insertmacro MUI_LANGUAGE "Slovenian"
!insertmacro MUI_LANGUAGE "Spanish"
!insertmacro MUI_LANGUAGE "SpanishInternational"
!insertmacro MUI_LANGUAGE "Swedish"
!insertmacro MUI_LANGUAGE "Ukrainian"
!insertmacro MUI_LANGUAGE "Welsh"

; MUI end ------

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "SetupNumCat2_602.exe"
InstallDir "$PROGRAMFILES\Numerical Catalyst"
InstallDirRegKey HKLM "${PRODUCT_DIR_REGKEY}" ""
ShowInstDetails show
ShowUnInstDetails show

VIAddVersionKey /LANG=${LANG_ENGLISH} "ProductName" $PRODUCT_NAME
;VIAddVersionKey /LANG=${LANG_ENGLISH} "Comments" "A test comment"
VIAddVersionKey /LANG=${LANG_ENGLISH} "CompanyName" "Aston Read Limited"
VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalTrademarks" "Numerical Catalyst is a trademark of Aston Read Limited"
VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalCopyright" "? Aston Read Limited"
VIAddVersionKey /LANG=${LANG_ENGLISH} "FileDescription" "Installation Numerical Catalyst"
VIAddVersionKey /LANG=${LANG_ENGLISH} "FileVersion" $PRODUCT_VERSION
VIProductVersion 2.6.0.0

;Request application privileges for Windows Vista
; this will stop attempts to check compatibility level by Vista
RequestExecutionLevel admin


Function .onInit

  !insertmacro MUI_LANGDLL_DISPLAY

  call InstallDotNetIfNotFound
FunctionEnd

Section "Numerical Catalyst" SEC01

  !insertmacro mcrRemoveSymlixAddInRegistry $ExcelPath $ExcelVersion ; clear Symlix out if already there and report version

  !insertmacro DeleteInstallation

  strcpy $vExcelVers $ExcelVersion
  ; MessageBox MB_OK "ExcelPath = $ExcelPath \n vExcel Vers = $vExcelVers"

  ;MessageBox MB_OK "$$ANOTHERFOLDER = $ANOTHERFOLDER"
  
  StrCpy $FilesRequested 0
  StrCpy $FilesFound 0
  StrCpy $vComObjects 3 ; remove one for each copied
  ClearErrors

  SetOutPath "$SYSDIR"
  SetOverwrite off
;  IntOp $FilesRequested $FilesRequested + 1
;  file "Nalpeiron\ASTSRV.EXE"
;  file /a "Nalpeiron\nlssrv32.exe"
  SetOutPath "$INSTDIR"
  SetOverwrite on
  
  FileOpen $9 $INSTDIR\Install_Error_Log.txt w
  SetOverwrite ifnewer
  FileWrite $9 'Numerical Catalyst installation log ( Cut and Paste this into an email to support@astonread.com or attach the file )'
  FileWriteByte $9 "13" ; CR
  FileWriteByte $9 "10" ; LF
  FileWrite $9 '===================================================================================================================='
  FileWriteByte $9 "13" ; CR
  FileWriteByte $9 "10" ; LF
  FileWrite $9 'Confirmed installed files'
  FileWriteByte $9 "13" ; CR
  FileWriteByte $9 "10" ; LF
  ;IfFileExists $SYSDIR\nlssrv32.exe 0 +5
  ;            FileWrite $9 '$SYSDIR\nlssrv32.exe'
  ;            FileWriteByte $9 "13" ; CR
  ;            FileWriteByte $9 "10" ; LF
  ;            IntOp $FilesFound $FilesFound + 1


  ;IfErrors ErrorsDetected 0

  ;delete "installastsrv.bat"
  ;FileOpen $9 $INSTDIR\installastsrv.bat w
  ;FileWrite $9 'sc create astcc DisplayName= "AST Service" binPath= "$SYSDIR\ASTSRV.exe" start= auto'
  ;FileWriteByte $9 "13" ; CR
  ;FileWriteByte $9 "10" ; LF
  ;FileWrite $9 'sc start astcc'
  ;FileClose $9

  ;file "installastsrv.bat.MANIFEST"
  
;  SetOutPath "$SYSDIR"
;  ExecWait '"$INSTDIR\installastsrv.bat"'

;  ExecWait 'sc create astcc DisplayName= "AST Service" binPath= "$SYSDIR\ASTSRV.exe" start= auto'
;  Exec 'sc start astcc'

;  ExecWait 'sc create nlsX86cc DisplayName= "Nalpeiron Licensing Service" binPath= "$SYSDIR\nlssrv32.exe" start= auto'
;  Exec 'sc start nlsX86cc'

;  IfErrors ErrorsDetected 0

  SetOutPath "$INSTDIR"
;  ExecShell "open" '"$INSTDIR\installastsrv.bat"' SW_HIDE
;  DetailPrint "Nalpeiron service started"
;  FileWrite $9 'Nalpeiron service started'
;  FileWriteByte $9 "13" ; CR
;  FileWriteByte $9 "10" ; LF

;  delete "installastsrv.bat"
;  delete "installastsrv.bat.MANIFEST"

;  file /a "Nalpeiron\filechck.dll"
;  IntOp $FilesRequested $FilesRequested + 1
;  IfFileExists $INSTDIR\filechck.dll 0 +5
;              FileWrite $9 '$INSTDIR\filechck.dll'
;              FileWriteByte $9 "13" ; CR
;              FileWriteByte $9 "10" ; LF
;              IntOp $FilesFound $FilesFound + 1

;  IfErrors ErrorsDetected 0

;  StrCmp $vISDOTNETINSTALLED 0 NapNoNet

;  file /a "Nalpeiron\boxsmall.jpg"
;  file /a "Nalpeiron\Connection.exe"
;  file /a "Nalpeiron\ControlActivation.exe"
;  file /a "Nalpeiron\ControlActivation.exe.config"
;  file /a "Nalpeiron\SpinningProgress.dll"
;  file /a "Nalpeiron\Update.dat"
;  file /a "Nalpeiron\update.exe"
;  file /a "Nalpeiron\Version.ini"
;  IntOp $FilesRequested $FilesRequested + 8
;  strcpy $ACTIVATION_EXE "$INSTDIR\ControlActivation.exe"
  
;  IfFileExists $INSTDIR\boxsmall.jpg 0 +5
;              FileWrite $9 '$INSTDIR\boxsmall.jpg'
;              FileWriteByte $9 "13" ; CR
;              FileWriteByte $9 "10" ; LF
;              IntOp $FilesFound $FilesFound + 1
;  IfFileExists $INSTDIR\Connection.exe 0 +5
;              FileWrite $9 '$INSTDIR\Connection.exe'
;              FileWriteByte $9 "13" ; CR
;              FileWriteByte $9 "10" ; LF
;              IntOp $FilesFound $FilesFound + 1
;  IfFileExists $INSTDIR\ControlActivation.exe 0 +5
;              FileWrite $9 '$INSTDIR\ControlActivation.exe'
;              FileWriteByte $9 "13" ; CR
;              FileWriteByte $9 "10" ; LF
;              IntOp $FilesFound $FilesFound + 1
;  IfFileExists $INSTDIR\ControlActivation.exe.config 0 +5
;              FileWrite $9 '$INSTDIR\ControlActivation.exe.config'
;              FileWriteByte $9 "13" ; CR
;              FileWriteByte $9 "10" ; LF
;              IntOp $FilesFound $FilesFound + 1
;  IfFileExists $INSTDIR\SpinningProgress.dll 0 +5
;              FileWrite $9 '$INSTDIR\SpinningProgress.dll'
;              FileWriteByte $9 "13" ; CR
;              FileWriteByte $9 "10" ; LF
;              IntOp $FilesFound $FilesFound + 1
;  IfFileExists $INSTDIR\Update.dat 0 +5
;              FileWrite $9 '$INSTDIR\Update.dat'
;              FileWriteByte $9 "13" ; CR
;              FileWriteByte $9 "10" ; LF
;              IntOp $FilesFound $FilesFound + 1
;  IfFileExists $INSTDIR\update.exe 0 +5
;              FileWrite $9 '$INSTDIR\update.exe'
;              FileWriteByte $9 "13" ; CR
;              FileWriteByte $9 "10" ; LF
;              IntOp $FilesFound $FilesFound + 1
;  IfFileExists $INSTDIR\Version.ini 0 +5
;              FileWrite $9 '$INSTDIR\Version.ini'
;              FileWriteByte $9 "13" ; CR
;              FileWriteByte $9 "10" ; LF
;              IntOp $FilesFound $FilesFound + 1

;  IfErrors ErrorsDetected 0

  goto InstallMainProduct
  NapNoNet:
  file /a "Nalpeiron\Using License Manager.doc"
  file /a "Nalpeiron\help-manager.chm"
  file /a "Nalpeiron\License Manager.exe"
  IntOp $FilesRequested $FilesRequested + 3
  strcpy $ACTIVATION_EXE "$INSTDIR\License Manager.exe"
  
  IfFileExists "$INSTDIR\Using License Manager.doc" 0 +5
              FileWrite $9 '$INSTDIR\Using License Manager.doc'
              FileWriteByte $9 "13" ; CR
              FileWriteByte $9 "10" ; LF
              IntOp $FilesFound $FilesFound + 1
  IfFileExists $INSTDIR\help-manager.chm 0 +5
              FileWrite $9 '$INSTDIR\help-manager.chm'
              FileWriteByte $9 "13" ; CR
              FileWriteByte $9 "10" ; LF
              IntOp $FilesFound $FilesFound + 1
  IfFileExists "$INSTDIR\License Manager.exe" 0 +5
              FileWrite $9 '$INSTDIR\License Manager.exe'
              FileWriteByte $9 "13" ; CR
              FileWriteByte $9 "10" ; LF
              IntOp $FilesFound $FilesFound + 1

;  IfErrors ErrorsDetected 0
  
  InstallMainProduct:
  ; MessageBox MB_OK $vExcelVers
  strcmp $vExcelVers "12.0" AddXlam
  strcmp $vExcelVers "14.0" AddXlam
  strcmp $vExcelVers "15.0" AddXlam
  strcmp $vExcelVers "16.0" AddXlam
  strcpy $vNumCatAddIn "NumCat.xla"
  file /a "NumCat.xla"
  goto InstallMainFiles
  AddXlam:
  strcpy $vNumCatAddIn "NumCat.xlam"
  file /a "NumCat.xlam"
  InstallMainFiles:


  file /a "ArmAccess.dll"
  file /a "NumCat.dll"
  file /a "TraceRecorder2.dll"
  file /a "ARStore.dll"
  file /a "NumCatalyst.jpg"
  file /a "ReadMe.html"
  file /a "NumCat.chm"
  IntOp $FilesRequested $FilesRequested + 8

  IfFileExists $INSTDIR\NumCat.dll 0 +6
              FileWrite $9 '$INSTDIR\NumCat.dll'
              FileWriteByte $9 "13" ; CR
              FileWriteByte $9 "10" ; LF
              IntOp $FilesFound $FilesFound + 1
              IntOp $vComObjects $vComObjects - 1
  IfFileExists $INSTDIR\$vNumCatAddIn 0 +5
              FileWrite $9 '$INSTDIR\$vNumCatAddIn'
              FileWriteByte $9 "13" ; CR
              FileWriteByte $9 "10" ; LF
              IntOp $FilesFound $FilesFound + 1
  IfFileExists $INSTDIR\TraceRecorder2.dll 0 +6
              FileWrite $9 '$INSTDIR\TraceRecorder2.dll'
              FileWriteByte $9 "13" ; CR
              FileWriteByte $9 "10" ; LF
              IntOp $FilesFound $FilesFound + 1
              IntOp $vComObjects $vComObjects - 1
  IfFileExists $INSTDIR\ARStore.dll 0 +6
              FileWrite $9 '$INSTDIR\ARStore.dll'
              FileWriteByte $9 "13" ; CR
              FileWriteByte $9 "10" ; LF
              IntOp $FilesFound $FilesFound + 1
              IntOp $vComObjects $vComObjects - 1
  IfFileExists $INSTDIR\NumCatalyst.jpg 0 +5
              FileWrite $9 '$INSTDIR\NumCatalyst.jpg'
              FileWriteByte $9 "13" ; CR
              FileWriteByte $9 "10" ; LF
              IntOp $FilesFound $FilesFound + 1
  IfFileExists $INSTDIR\ArmAccess.dll 0 +5
              FileWrite $9 '$INSTDIR\ArmAccess.dll'
              FileWriteByte $9 "13" ; CR
              FileWriteByte $9 "10" ; LF
              IntOp $FilesFound $FilesFound + 1
  IfFileExists $INSTDIR\ReadMe.html 0 +5
              FileWrite $9 '$INSTDIR\ReadMe.html'
              FileWriteByte $9 "13" ; CR
              FileWriteByte $9 "10" ; LF
              IntOp $FilesFound $FilesFound + 1
  IfFileExists $INSTDIR\NumCat.chm 0 +5
              FileWrite $9 '$INSTDIR\NumCat.chm'
              FileWriteByte $9 "13" ; CR
              FileWriteByte $9 "10" ; LF
              IntOp $FilesFound $FilesFound + 1

  FileWriteByte $9 "13" ; CR
  FileWriteByte $9 "10" ; LF
  FileWrite $9 'Number of files requested to be copied = $FilesRequested and number confirmed copied = $FilesFound of which COM dlls missing = $vComObjects'
  FileWriteByte $9 "13" ; CR
  FileWriteByte $9 "10" ; LF
  FileWriteByte $9 "13" ; CR
  FileWriteByte $9 "10" ; LF

;  IfErrors ErrorsDetected 0
  
  StrCmp $FilesRequested $FilesFound carryonCOMdll ; skip if all files confirmed
         IntOp $8 $FilesFound + $vComObjects
         StrCmp $vComObjects 3 0 ErrorsDetected ; ensure its 3 COM objects
         StrCmp $FilesRequested $8 ComFilesError ErrorsDetected ; detect if only the COM dlls have been left out
  carryonCOMdll:

  delete "SymlixHelp.chm" ; clean up from previous versions
  
  
;  delete "install_error_log.txt" ; clean up from previous
  ; register the COM components
  !insertmacro InstallLib REGDLL NOTSHARED NOREBOOT_PROTECTED NumCat.dll $INSTDIR\NumCat.dll $INSTDIR
  !insertmacro InstallLib REGDLL NOTSHARED NOREBOOT_PROTECTED TraceRecorder2.dll $INSTDIR\TraceRecorder2.dll $INSTDIR
  !insertmacro InstallLib REGDLL NOTSHARED NOREBOOT_PROTECTED ARStore.dll $INSTDIR\ARStore.dll $INSTDIR
  ;ExecWait "$INSTDIR\TraceRecorder /REGSERVER"
  ; Add symlix to this users options so add in can be found
  
  ; will also check registry keys and write to log file

 ; WriteRegStr HKCU "$ExcelPath\Add-in Manager" "$INSTDIR\NumCat.xla" ""
  ;WriteRegStr HKCU "Software\VB and VBA Program Settings\NumCatAddIn\Help" "Location" "$INSTDIR\NumCat.chm"
  ;WriteRegStr HKCU "Software\VB and VBA Program Settings\NumCatAddIn\Docs" "Trace" "$TEMP"
  ;WriteRegStr HKCU "Software\VB and VBA Program Settings\NumCatAddIn\Display" "TempToolbar" "true" ; this is needed to cover reinstallation issues as it forces a new toolbar on installation

  clearErrors
  strcpy $vSubKey "$ExcelPath\Add-in Manager"
  strcpy $vEntry "$INSTDIR\$vNumCatAddIn"
  WriteRegStr HKCU $vSubKey $vEntry ""
  ReadRegStr $RegValue HKCU $vSubKey $vEntry
  FileWrite $9 'HKCU $vSubKey $vEntry $RegValue'
  FileWriteByte $9 "13" ; CR
  FileWriteByte $9 "10" ; LF

   ; Add reference to help file to registry
  strcpy $vSubKey "Software\VB and VBA Program Settings\NumCatAddIn\Help"
  strcpy $vEntry "Location"
  WriteRegStr HKCU $vSubKey $vEntry "$INSTDIR\NumCat.chm"
  ReadRegStr $RegValue HKCU $vSubKey $vEntry
  FileWrite $9 'HKCU $vSubKey $vEntry $RegValue'
  FileWriteByte $9 "13" ; CR
  FileWriteByte $9 "10" ; LF

  strcpy $vSubKey "Software\VB and VBA Program Settings\NumCatAddIn\Docs"
  strcpy $vEntry "Trace"
  WriteRegStr HKCU $vSubKey $vEntry "$TEMP"
  ReadRegStr $RegValue HKCU $vSubKey $vEntry
  FileWrite $9 'HKCU $vSubKey $vEntry $RegValue'
  FileWriteByte $9 "13" ; CR
  FileWriteByte $9 "10" ; LF

  strcpy $vSubKey "Software\VB and VBA Program Settings\NumCatAddIn\Display"
  strcpy $vEntry "TempToolbar"
  WriteRegStr HKCU $vSubKey $vEntry "true" ; this is needed to cover reinstallation issues as it forces a new toolbar on installation
  ReadRegStr $RegValue HKCU $vSubKey $vEntry
  FileWrite $9 'HKCU $vSubKey $vEntry $RegValue'
  FileWriteByte $9 "13" ; CR
  FileWriteByte $9 "10" ; LF

  SetOutPath "$SYSDIR" ; must be somewhere I can run it from
  file "ARAddInHelper.exe"
  ExecWait "ARAddInHelper NumCat"
  delete "ARAddInHelper.exe"
  ClearErrors
  ;IfErrors ErrorsDetected 0
  FileWrite $9 'ARAddInHelper NumCat appears to have executed successfully'
  FileWriteByte $9 "13" ; CR
  FileWriteByte $9 "10" ; LF


; Shortcuts
  !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
  CreateDirectory "$SMPROGRAMS\$ICONS_GROUP"
  ;StrCmp $vISDOTNETINSTALLED 0 LinkNoNet
  ;CreateShortCut "$SMPROGRAMS\$ICONS_GROUP\Manage License.lnk" "$INSTDIR\ControlActivation.exe"
  ;goto OtherLinks
  ;LinkNoNet:
  ;CreateShortCut "$SMPROGRAMS\$ICONS_GROUP\Manage License No dotNet.lnk" "$INSTDIR\License Manager.exe"
  ;OtherLinks:
  CreateShortCut "$SMPROGRAMS\$ICONS_GROUP\Help.lnk" "$INSTDIR\NumCat.chm"
  CreateShortCut "$SMPROGRAMS\$ICONS_GROUP\Release Notes.lnk" "$INSTDIR\Readme.html"

  IfErrors ErrorsDetected 0
  
  strcmp $FilesRequested $FilesFound AllOK ErrorsDetected
  
  ComFilesError: ; The absence of the COM dll files has been detected
  strcpy $0 '<Warning> All the COM dll files failed to copy to the install drive'
  DetailPrint $0
  FileWrite $9 $0
  FileWriteByte $9 "13" ; CR
  FileWriteByte $9 "10" ; LF
  MessageBox MB_OK "Three files that contain COM objects couldn't be copied to your hard drive. Even though you are using admin rights for the installer it may be that security setting prevent COM objects being copied to your machine. Ask for help from your IT support."
  MessageBox MB_YESNO 'Would you like to open the support FAQ which has more up to date information about this issue ?' IDYES 0 IDNO ErrorsDetected
  ExecShell "open" "http://www.astonread.com/support/numcat/installation"
  MessageBox MB_OK "The installer will now run through its abort process and clear up the installation."

  ErrorsDetected:
  
  FileWrite $9 "Excel installation $ExcelPath"
  FileWriteByte $9 "13" ; CR
  FileWriteByte $9 "10" ; LF

  FileWrite $9 "Language chosen for installer $LANGUAGE"
  FileWriteByte $9 "13" ; CR
  FileWriteByte $9 "10" ; LF
  FileWrite $9 "Product ${PRODUCT_NAME} ${PRODUCT_VERSION}"
  FileWriteByte $9 "13" ; CR
  FileWriteByte $9 "10" ; LF

  DetailPrint 'Problems identified in the installation'
  strcpy $0 'Problems detected during installation. Please email $INSTDIR\Install_Error_Log.txt file to support@astonread.com'
  FileWrite $9 $0
  DetailPrint $0
  FileWriteByte $9 "13" ; CR
  FileWriteByte $9 "10" ; LF
  FileClose $9
  
  MessageBox MB_OK $0
  
  MessageBox MB_YESNO "Would you like to open the log file and send an email now ?" IDYES 0 IDNO abortinstall
  ExecShell "open" "$INSTDIR\Install_Error_Log.txt"
  ExecShell "open" "mailto:support@astonread.com?subject=Problem with installation of ${PRODUCT_NAME} ${PRODUCT_VERSION}&body=Cut and paste error log here:&attachment=$INSTDIR\Install_Error_Log.txt"
  
  abortinstall:
 !insertmacro DeleteInstallation
  DetailPrint "Press Cancel"
  Abort
  
  AllOK:

  FileClose $9
  delete "$INSTDIR\install_error_log.txt" ; clean up as all has gone well !

;  CreateShortCut "$SMPROGRAMS\$ICONS_GROUP\Symlix.lnk" "$INSTDIR\Symlix.dll"
  !insertmacro MUI_STARTMENU_WRITE_END
SectionEnd

Section "Basic examples" SEC02
  SetOutPath "${SYMLIX_WORKDIR}"
  SetOverwrite off
  
  !insertmacro mcrIsExcel2007Plus $Excel2007Plus
  
  strcmp $Excel2007Plus 1 AddSec022007

  File /a "NumCatSamples\sample.xls"
  File /a "NumCatSamples\lookup1.xls"
  File /a "NumCatSamples\limits.xls"
  File /a "NumCatSamples\SkyDiver.xls"
  File /a "NumCatSamples\CaseStudies.xls"
  File /a "NumCatSamples\Heart.xls"
  File /a "NumCatSamples\ArrayExample.xls"
  File /a "NumCatSamples\DCFexample1.xls"

  goto Sec02CarryOn

AddSec022007:
  File /a "NumCatSamples\sample.xlsx"
  File /a "NumCatSamples\lookup1.xlsx"
  File /a "NumCatSamples\limits.xlsx"
  File /a "NumCatSamples\SkyDiver.xlsx"
  File /a "NumCatSamples\CaseStudies.xlsm"
  File /a "NumCatSamples\Heart.xlsx"
  File /a "NumCatSamples\ArrayExample.xlsx"
  File /a "NumCatSamples\DCFexample1.xlsx"

  Sec02CarryOn:
  ; Add reference to help file to registry
  WriteRegStr HKCU "Software\VB and VBA Program Settings\NumCatAddIn\Docs" "Examples" "${SYMLIX_WORKDIR}"
  WriteRegStr HKCU "Software\VB and VBA Program Settings\NumCatAddIn\Docs" "Trace" "${SYMLIX_WORKDIR}"


; Shortcuts
  !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
  CreateDirectory "$SMPROGRAMS\$ICONS_GROUP"
  strcmp $Excel2007Plus 1 Sample2007
  CreateShortCut "$SMPROGRAMS\$ICONS_GROUP\Sample.lnk" "${SYMLIX_WORKDIR}\sample.xls"
  goto CarryOnExplorer
 Sample2007:
  CreateShortCut "$SMPROGRAMS\$ICONS_GROUP\Sample.lnk" "${SYMLIX_WORKDIR}\sample.xlsx"
 CarryOnExplorer:
  CreateShortCut "$SMPROGRAMS\$ICONS_GROUP\Numerical Catalyst examples.lnk" "$WINDIR\explorer.exe" "/e,${SYMLIX_WORKDIR}"
  !insertmacro MUI_STARTMENU_WRITE_END
SectionEnd

Section "Chem Eng examples" SEC03
  SetOutPath "${SYMLIX_WORKDIR}\ChemEng"
  SetOverwrite off

  !insertmacro mcrIsExcel2007Plus $Excel2007Plus

  strcmp $Excel2007Plus 1 AddSec032007

  File /a "NumCatSamples\CO_CSTR1.xls"
  File /a "NumCatSamples\TankLevelControl.xls"
  File /a "NumCatSamples\Batch_Distillation.xls"
  File /a "NumCatSamples\BatchDistill_Index.xls"

  goto Sec03CarryOn
  AddSec032007:

  File /a "NumCatSamples\CO_CSTR1.xlsx"
  File /a "NumCatSamples\TankLevelControl.xlsx"
  File /a "NumCatSamples\Batch_Distillation.xlsx"
  File /a "NumCatSamples\BatchDistill_Index.xlsx"

  Sec03CarryOn:
; Shortcuts
  !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
  !insertmacro MUI_STARTMENU_WRITE_END
SectionEnd

Section "Maths examples" SEC04
  SetOutPath "${SYMLIX_WORKDIR}\Maths"
  SetOverwrite off

  !insertmacro mcrIsExcel2007Plus $Excel2007Plus

  strcmp $Excel2007Plus 1 AddSec042007

  File /a "NumCatSamples\Analytical1.xls"
  File /a "NumCatSamples\Lorenz1.xls"
  
  goto Sec04CarryOn
  AddSec042007:

  File /a "NumCatSamples\Analytical1.xlsx"
  File /a "NumCatSamples\Lorenz1.xlsx"

  Sec04CarryOn:
; Shortcuts
  !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
  !insertmacro MUI_STARTMENU_WRITE_END
SectionEnd

Section -AdditionalIcons
  !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
;  FileOpen $TRACEINST $INSTDIR\install_error_log.txt w
;  FileWrite $TRACEINST 'Prod web site ="${PRODUCT_WEB_SITE}"'
;  FileWriteByte $TRACEINST "13" ; CR
;  FileWriteByte $TRACEINST "10" ; LF
;  FileClose $TRACEINST
  WriteIniStr "$INSTDIR\${PRODUCT_NAME}.url" "InternetShortcut" "URL" "${PRODUCT_WEB_SITE}"
  CreateShortCut "$SMPROGRAMS\$ICONS_GROUP\Numerical Catalyst Website.lnk" "$INSTDIR\${PRODUCT_NAME}.url" "" "$INSTDIR\${PRODUCT_NAME}.dll"
  CreateShortCut "$SMPROGRAMS\$ICONS_GROUP\Uninstall.lnk" "$INSTDIR\uninst.exe"
  !insertmacro MUI_STARTMENU_WRITE_END
SectionEnd

Section -Post
  WriteUninstaller "$INSTDIR\uninst.exe"
  WriteRegStr HKLM "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR\NumCat.dll"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\NumCat.dll"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
SectionEnd

; Section descriptions
!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
  !insertmacro MUI_DESCRIPTION_TEXT ${SEC01} "Excel dynamic simulation add in"
  !insertmacro MUI_DESCRIPTION_TEXT ${SEC02} "To demostrate the use of Numerical Catalyst"
  !insertmacro MUI_DESCRIPTION_TEXT ${SEC03} "Examples from Chemical Engineering"
  !insertmacro MUI_DESCRIPTION_TEXT ${SEC04} "Examples from Maths"
!insertmacro MUI_FUNCTION_DESCRIPTION_END


Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) was successfully removed from your computer."
FunctionEnd

Function un.onInit
!insertmacro MUI_UNGETLANGUAGE
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "Are you sure you want to completely remove $(^Name) and all of its components?" IDYES +2
  Abort
FunctionEnd

Section Uninstall

  !insertmacro mcrRemoveSymlixAddInRegistry $ExcelPath $vNumCatAddIn ; clear NumCat out if already there
  !insertmacro DeleteInstallation
  ;Unregister DLL's a service first
;  !insertmacro UnInstallLib REGDLL SHARED REBOOT_NOTPROTECTED $INSTDIR\NumCat.dll
;  !insertmacro UnInstallLib REGDLL SHARED REBOOT_NOTPROTECTED $INSTDIR\TraceRecorder2.dll
;  !insertmacro UnInstallLib REGDLL SHARED REBOOT_NOTPROTECTED $INSTDIR\ARStore.dll

;  ExecWait "$INSTDIR\TraceRecorder /UNREGSERVER"

;  !insertmacro MUI_STARTMENU_GETFOLDER "Application" $ICONS_GROUP
;  !insertmacro mcrRemoveSymlixAddInRegistry $ExcelPath ; clear NumCat out if already there
 ; Delete "$INSTDIR\${PRODUCT_NAME}.url"
 ; ;Delete "$SYSDIR\ASTSRV.EXE" ; leave this as may be used by other applications
;  Delete "$INSTDIR\uninst.exe"
;  Delete "$INSTDIR\boxsmall.jpg"
;  Delete "$INSTDIR\Connection.exe"
;  Delete "$INSTDIR\ControlActivation.exe"
;  Delete "$INSTDIR\ControlActivation.exe.config"
;  Delete "$INSTDIR\filechck.dll"
;  Delete "$INSTDIR\SpinningProgress.dll"
;  Delete "$INSTDIR\Update.dat"
;  Delete "$INSTDIR\update.exe"
;  Delete "$INSTDIR\Version.ini"
;  Delete "$INSTDIR\Using License Manager.doc"
;  Delete "$INSTDIR\help-manager.chm"
;  Delete "$INSTDIR\License Manager.exe"

;  Delete "$INSTDIR\NumCat.dll"
;  Delete "$INSTDIR\TraceRecorder2.dll"
;  Delete "$INSTDIR\ARStore.dll"
;  Delete "$INSTDIR\NumCat.chm"
  
;  Delete "$INSTDIR\ReadMe.html"
;  Delete "$INSTDIR\NumCatalyst.jpg"
;  Delete "$INSTDIR\FileChck.lib"
;  Delete "$INSTDIR\NumCat.xla"
;  Delete "${SYMLIX_WORKDIR}\sample.xls"
;  Delete "${SYMLIX_WORKDIR}\lookup1.xls"
;  Delete "${SYMLIX_WORKDIR}\limits.xls"
;  Delete "${SYMLIX_WORKDIR}\SkyDiver.xls"
;  Delete "${SYMLIX_WORKDIR}\CaseStudies.xls"
;  Delete "${SYMLIX_WORKDIR}\traceSymlix.txt" ; take the debug file also
;  Delete "${SYMLIX_WORKDIR}\ChemEng\CO_CSTR1.xls" ; wonder if should leave these files ?
;  Delete "${SYMLIX_WORKDIR}\ChemEng\TankLevelControl.xls" ; wonder if should leave these files ?
;  Delete "${SYMLIX_WORKDIR}\ChemEng\Batch_Distillation.xls"
;  Delete "${SYMLIX_WORKDIR}\Maths\Analytical1.xls" ; wonder if should leave these files ?
;  Delete "${SYMLIX_WORKDIR}\Maths\Lorenz1.xls" ; wonder if should leave these files ?

;;  Delete "$INSTDIR\Uninstall.exe"

;  Delete "$SMPROGRAMS\$ICONS_GROUP\Uninstall.lnk"
;  Delete "$SMPROGRAMS\$ICONS_GROUP\Numerical Catalyst Website.lnk"
;  Delete "$SMPROGRAMS\$ICONS_GROUP\Manage License.lnk"
;  Delete "$SMPROGRAMS\$ICONS_GROUP\Manage License No dotNet.lnk"
;  Delete "$SMPROGRAMS\$ICONS_GROUP\Release Notes.lnk"
;  Delete "$SMPROGRAMS\$ICONS_GROUP\Sample.lnk"
;  Delete "$SMPROGRAMS\$ICONS_GROUP\Help.lnk"
;  Delete "$SMPROGRAMS\$ICONS_GROUP\Numerical Catalyst examples.lnk"

;  RMDir "$SMPROGRAMS\$ICONS_GROUP"
;  RMDir "$INSTDIR"
;  RMDir "${SYMLIX_WORKDIR}"
  
;  DeleteRegValue HKCU "$ExcelPath\Add-in Manager" "$INSTDIR\NumCat.xla"

;  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
;  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
  SetAutoClose true
SectionEnd