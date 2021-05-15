; ExcelAddIn.nsh
;
; Provides the macro mcrRemoveSymlixAddInRegistry


  var ExcelPath
  var ExcelVersion
  var Excel2007Plus
;--------------------------------
;Macros
!macro mcrIsExcel2007Plus Excel2007Plus
    DetailPrint "Start Numerical Catalyst integration with Excel in add-in registry"

    StrCpy $0 0
    StrCpy $4 0
    StrCpy $5 0
    StrCpy $Excel2007Plus -1 ; default value

  loopExDt:
    EnumRegKey $1 HKCU "Software\Microsoft\Office" $0
    ; lets see if we have a number
    StrCmp $1 "16.0" confirmExcelDt ; reverse order to get actual installed version
    StrCmp $1 "15.0" confirmExcelDt ; reverse order to get actual installed version
    StrCmp $1 "14.0" confirmExcelDt ; reverse order to get actual installed version
    StrCmp $1 "12.0" confirmExcelDt ; reverse order to get actual installed version
    StrCmp $1 "11.0" confirmExcelDt
    StrCmp $1 "10.0" confirmExcelDt
    StrCmp $1 "9.0" confirmExcelDt
    StrCmp $1 "8.0" confirmExcelDt

    Goto doneDtErrors

  confirmExcelDt:

    ClearErrors
    EnumRegValue $5 HKCU "Software\Microsoft\Office\$1\Excel" 0
    DetailPrint "Software\Microsoft\Office\$1\Excel = $5"
    IfErrors doneDtErrorsExcelInst

    DetailPrint "Excel $1 confirmed"
    StrCmp $1 "16.0" ExcelPlus ; reverse order to get actual installed version
    StrCmp $1 "15.0" ExcelPlus ; reverse order to get actual installed version
    StrCmp $1 "14.0" ExcelPlus ; reverse order to get actual installed version
    StrCmp $1 "12.0" ExcelPlus ; reverse order to get actual installed version
    StrCmp $1 "11.0" ExcelMinus
    StrCmp $1 "10.0" ExcelMinus
    StrCmp $1 "9.0" ExcelMinus
    StrCmp $1 "8.0" ExcelMinus

    goto endloopcheckDt
  ExcelMinus:
    StrCpy $Excel2007Plus 0
    goto doneDt
  ExcelPlus:
    StrCpy $Excel2007Plus 1
    goto doneDt
  endloopcheckDt:
    
    StrCmp $1 "" doneDtErrors
    IntOp $0 $0 + 1
    Goto loopExDt
  doneDtErrorsExcelInst:
    DetailPrint "Old Excel remnants found - looking for a new installation"
    Goto endloopcheckDt
  doneDtErrors:
    DetailPrint "Errors found whilst trying to detect Excel version"
 doneDt:
  
!macroend

!macro mcrRemoveSymlixAddInRegistry ExcelPath ExcelVersion
  ;Find the excel version
  DetailPrint "Start Numerical Catalyst integration with Excel in add-in registry"

  StrCpy $0 0
  StrCpy $4 0
  StrCpy $5 0
  StrCpy $ExcelVersion ""
  loopEx:
    EnumRegKey $1 HKCU "Software\Microsoft\Office" $0
    ; lets see if we have a number
    StrCpy $ExcelVersion $1
    StrCmp $1 "16.0" confirmExcel ; confirmExcelNoTested ; reverse order to get actual installed version
    StrCmp $1 "15.0" confirmExcel ; confirmExcelNoTested ; reverse order to get actual installed version
    StrCmp $1 "14.0" confirmExcel ; reverse order to get actual installed version
    StrCmp $1 "12.0" confirmExcel ; reverse order to get actual installed version
    StrCmp $1 "11.0" confirmExcel
    StrCmp $1 "10.0" confirmExcel
    StrCmp $1 "9.0" confirmExcel
    StrCmp $1 "8.0" confirmExcel

    Goto endloopcheck
    ;confirm Excel is here
    confirmExcelNoTested:
    DetailPrint "An untested version of Excel found - this has not been tested and is not yet supported"
    MessageBox MB_OK "Sorry but this version of Excel is not yet supported, this may be being worked on." ;IDYES confirmExcel IDNO cancelExcel
    cancelExcel:
    abort "Excel version > 14 found and user abort requested."
    confirmExcel:

    StrCpy $ExcelVersion $1
    DetailPrint "Excel version $ExcelVersion found."
    ClearErrors
    EnumRegValue $5 HKCU "Software\Microsoft\Office\$1\Excel" 0
    DetailPrint "Software\Microsoft\Office\$1\Excel = $5"
    IfErrors endloopcheck

    DetailPrint "Excel $1 confirmed"
    StrCmp $1 "16.0" Excel2016 ; reverse order to get actual installed version
    StrCmp $1 "15.0" Excel2013 ; reverse order to get actual installed version
    StrCmp $1 "14.0" Excel2010 ; reverse order to get actual installed version
    StrCmp $1 "12.0" Excel2007 ; reverse order to get actual installed version
    StrCmp $1 "11.0" Excel2003
    StrCmp $1 "10.0" ExcelXP ; Also Excel 2002 part of Office XP
    StrCmp $1 "9.0" Excel2000
    StrCmp $1 "8.0" Excel97
    endloopcheck:
    StrCmp $1 "" doneEx
    IntOp $0 $0 + 1
    Goto loopEx
  doneEx:

    Goto CannotFindExcelEx
  Excel97:
    StrCpy $4 "Found Excel 97"
    Goto FoundExcelEx

  ExcelXP:
    StrCpy $4 "Found Excel 2002 (Office XP)"
    Goto FoundExcelEx

  Excel2000:
    StrCpy $4 "Found Excel 2000"
    Goto FoundExcelEx

  Excel2003:
    StrCpy $4 "Found Excel 2003"
    Goto FoundExcelEx

  Excel2007:
    StrCpy $4 "Found Excel 2007"
    Goto FoundExcelEx

  Excel2010:
    StrCpy $4 "Found Excel 2010"
    Goto FoundExcelEx
    
  Excel2013:
    StrCpy $4 "Found Excel 2013"
    Goto FoundExcelEx

  Excel2016:
    StrCpy $4 "Found Excel 2016"
    Goto FoundExcelEx
  FoundExcelEx:
    ; Create the registry key for that would expect Excel to be at

    StrCpy $0 0
    StrCpy $3 "Software\Microsoft\Office\$1\Excel"
    DetailPrint "Excel believed to be located here $3"
    EnumRegKey $2 HKCU "$3" $0
    StrCmp $2 "" CannotFindExcelEx

    DetailPrint "Have found $4"

    ;now must check if already installed
    ;if already active then ask user to uninstall

    StrCpy $0 0
    loop2Ex:
      EnumRegValue $1 HKCU "$3\Options" $0
      DetailPrint "$3\Options"
      ;DetailPrint "Dollar1 =$1"
      StrCmp $1 "" done2Ex
      ; now can we find NumCat.xla ?
      StrCpy $7 $1 4
      ;DetailPrint "The first four letters are:$7"

      StrCmp $7 "OPEN" 0 nextkeyEx

      ReadRegStr $6 HKCU "$3\Options" $1

      StrCpy $6 $6 "" -11
      StrCpy $6 $6 10

      StrCmp $6 "NumCat.xla" DelNumCatKey1
      StrCmp $6 "NumCat.xlam" DelNumCatKey1 nextkeyEx

      ;MessageBox MB_OK "Extract is :$6"
      DelNumCatKey1:
      ; right I'm going to delete this key then
      DeleteRegValue HKCU "$3\Options" $1
      ; we're done here now
      Goto done2Ex

      nextkeyEx:
      IntOp $0 $0 + 1
      Goto loop2Ex
    done2Ex:

    ; check if Excel is aware of a NumCat add in - if so delete the reference
    StrCpy $0 0
    loop3Ex:
      EnumRegValue $1 HKCU "$3\Add-in Manager" $0
      ;DetailPrint "$3\Add-in Manager"
      ;DetailPrint "Dollar1 =$1"
      StrCmp $1 "" done3Ex
      ; now can we find NumCat.xla ?

      ;ReadRegStr $6 HKCU "$3\Add-in Manager" $1
      StrCpy $6 $1

      ;DetailPrint "Before shortening:$6"

      StrCpy $6 $6 "" -10
      ;StrCpy $6 $6 10

      ;MessageBox MB_OK "Extract is :$6"

      StrCmp $6 "NumCat.xla" DelNumCatKey2
      StrCmp $6 "NumCat.xlam" DelNumCatKey2 nextkey3Ex

      DelNumCatKey2:
      ;MessageBox MB_OK "Extract is :$6"
      ; right I'm going to delete this key then
      DetailPrint "Removing old Add-in registry settings for NumCat.xla"
      DeleteRegValue HKCU "$3\Add-in Manager" $1
      ; we're done here now
      Goto done3Ex

      nextkey3Ex:
      IntOp $0 $0 + 1
      Goto loop3Ex
    done3Ex:


    Goto EndOfExcelSectionEx

  CannotFindExcelEx:

    DetailPrint "Unable to locate a supported Microsoft Excel installation or errors occured, installation has stopped"
    Abort "Abort and try the installation again - if this fails please report to support@astonread.com"

    EndOfExcelSectionEx:

    Strcpy $ExcelPath $3
  DetailPrint "End tidying NumCat add-in registry"

!macroend