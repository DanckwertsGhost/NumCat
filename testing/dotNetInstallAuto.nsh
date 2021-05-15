; Header file to determine if dot Net installed
; and if not offer automatic download
!define DOT_MAJOR 2
!define DOT_MINOR 0


;==========================================================================
!define DOT_NET_BASE_URL http://download.microsoft.com/download
; .NET Framework
; English
!define URL_DOTNET_1033 "${DOT_NET_BASE_URL}/a/a/c/aac39226-8825-44ce-90e3-bf8203e74006/dotnetfx.exe"
;German
!define URL_DOTNET_1031 "${DOT_NET_BASE_URL}/4/f/3/4f3ac857-e063-45d0-9835-83894f20e808/dotnetfx.exe"
;Spanish
!define URL_DOTNET_1034 "${DOT_NET_BASE_URL}/8/f/0/8f023ff4-2dc1-4f10-9618-333f5b9f8040/dotnetfx.exe"
;French
!define URL_DOTNET_1036 "${DOT_NET_BASE_URL}/e/d/a/eda9d4ea-8ec9-4431-8efa-75391fb91421/dotnetfx.exe"
;Portuguese (Brazil)
!define URL_DOTNET_1046 "${DOT_NET_BASE_URL}/8/c/f/8cf55d0c-235e-4062-933c-64ffdf7e7043/dotnetfx.exe"
;Chinese (Simplified)
!define URL_DOTNET_2052 "${DOT_NET_BASE_URL}/7/b/9/7b90644d-1af0-42b9-b76d-a2770319a568/dotnetfx.exe"
!define URL_DOTNET_4100 "${DOT_NET_BASE_URL}/7/b/9/7b90644d-1af0-42b9-b76d-a2770319a568/dotnetfx.exe"
;Chinese (Traditional)
!define URL_DOTNET_1028 "${DOT_NET_BASE_URL}/8/2/7/827bb1ef-f5e1-4464-9788-40ef682930fd/dotnetfx.exe"
!define URL_DOTNET_3076 "${DOT_NET_BASE_URL}/8/2/7/827bb1ef-f5e1-4464-9788-40ef682930fd/dotnetfx.exe"
!define URL_DOTNET_5124 "${DOT_NET_BASE_URL}/8/2/7/827bb1ef-f5e1-4464-9788-40ef682930fd/dotnetfx.exe"
;Czech
!define URL_DOTNET_1029 "${DOT_NET_BASE_URL}/2/a/2/2a224db0-2e6d-4961-99ed-6f377555b1ef/dotnetfx.exe"
;Danish
!define URL_DOTNET_1030 "${DOT_NET_BASE_URL}/e/7/5/e755a559-025d-4282-95ae-d14a8d0b1929/dotnetfx.exe"
;Dutch
!define URL_DOTNET_1043 "${DOT_NET_BASE_URL}/4/6/b/46b519cb-bdd2-4701-b962-9ffaa323f40b/dotnetfx.exe"
!define URL_DOTNET_2067 "${DOT_NET_BASE_URL}/4/6/b/46b519cb-bdd2-4701-b962-9ffaa323f40b/dotnetfx.exe"
;Finnish
!define URL_DOTNET_1035 "${DOT_NET_BASE_URL}/d/a/6/da6b472c-157c-429a-98f6-6eb87fa36fd3/dotnetfx.exe"
;Greek
!define URL_DOTNET_1032 "${DOT_NET_BASE_URL}/5/9/8/598fb686-cd09-45cd-8b13-2a0fd814e4cc/dotnetfx.exe"
;Hungarian
!define URL_DOTNET_1038 "${DOT_NET_BASE_URL}/8/2/0/82093ba7-c9a4-457d-864d-bbeb1cd884d4/dotnetfx.exe"
;Italian
!define URL_DOTNET_1040 "${DOT_NET_BASE_URL}/1/f/a/1fa816d7-a8d6-4f15-b682-b96239e68ab7/dotnetfx.exe"
!define URL_DOTNET_2064 "${DOT_NET_BASE_URL}/1/f/a/1fa816d7-a8d6-4f15-b682-b96239e68ab7/dotnetfx.exe"
;Japanese
!define URL_DOTNET_1041 "${DOT_NET_BASE_URL}/5/b/5/5b510096-5b68-4e3f-8f9e-56fb7a80ca81/dotnetfx.exe"
;Korean
!define URL_DOTNET_1042 "${DOT_NET_BASE_URL}/d/2/d/d2db6a60-6fb1-4015-ae45-2fb84ec30faa/dotnetfx.exe"
;Norwegian
!define URL_DOTNET_1044 "${DOT_NET_BASE_URL}/b/6/6/b663aaf1-ef27-4119-8cf1-fa23888cf6a7/dotnetfx.exe"
!define URL_DOTNET_2068 "${DOT_NET_BASE_URL}/b/6/6/b663aaf1-ef27-4119-8cf1-fa23888cf6a7/dotnetfx.exe"
;Polish
!define URL_DOTNET_1045 "${DOT_NET_BASE_URL}/c/9/f/c9f672f3-c14b-4cff-9671-d419842d792d/dotnetfx.exe"
;Portuguese (Portugal)
!define URL_DOTNET_2070 "${DOT_NET_BASE_URL}/1/2/0/1206b231-b961-40ca-9ac2-e4ab7e92ca9b/dotnetfx.exe"
;Russian
!define URL_DOTNET_1049 "${DOT_NET_BASE_URL}/0/8/6/086e7824-ddad-45c0-b765-721e5e28e4c5/dotnetfx.exe"
;Swedish
!define URL_DOTNET_1053 "${DOT_NET_BASE_URL}/3/0/0/300b9c1c-9a26-4334-b273-8c0064ba5f2b/dotnetfx.exe"
;Turkish
!define URL_DOTNET_1055 "${DOT_NET_BASE_URL}/a/f/7/af738ebf-dc15-4c61-a20d-1c29306cd9bc/dotnetfx.exe"
; ... If you need one not listed above you will have to visit the Microsoft Download site,
; select the language you are after and scan the page source to obtain the link.

;==========================================================================
;Variables
Var "LANGUAGE_DLL_TITLE"
Var "LANGUAGE_DLL_INFO"
Var "URL_DOTNET"
Var "OSLANGUAGE"
Var "DOTNET_RETURN_CODE"

;==========================================================================
;Language Strings
LangString DESC_REMAINING ${LANG_ENGLISH} " (%d %s%s remaining)"
LangString DESC_PROGRESS ${LANG_ENGLISH} "%d.%01dkB/s" ;"%dkB (%d%%) of %dkB @ %d.%01dkB/s"
LangString DESC_PLURAL ${LANG_ENGLISH} "s"
LangString DESC_HOUR ${LANG_ENGLISH} "hour"
LangString DESC_MINUTE ${LANG_ENGLISH} "minute"
LangString DESC_SECOND ${LANG_ENGLISH} "second"
LangString DESC_CONNECTING ${LANG_ENGLISH} "Connecting..."
LangString DESC_DOWNLOADING ${LANG_ENGLISH} "Downloading %s"
LangString DESC_SHORTDOTNET ${LANG_ENGLISH} "Microsoft .Net Framework 2.1"
LangString DESC_LONGDOTNET ${LANG_ENGLISH} "Microsoft .Net Framework 2.1"
LangString DESC_DOTNET_DECISION ${LANG_ENGLISH} "$(DESC_SHORTDOTNET) is required.$\nIt is strongly \
  advised that you install$\n$(DESC_SHORTDOTNET) before continuing.$\nIf you choose to continue, \
  you will need to connect$\nto the internet before proceeding.$\nWould you like to continue with \
  the installation?"
LangString SEC_DOTNET ${LANG_ENGLISH} "$(DESC_SHORTDOTNET) "
LangString DESC_INSTALLING ${LANG_ENGLISH} "Installing"
LangString DESC_DOWNLOADING1 ${LANG_ENGLISH} "Downloading"
LangString DESC_DOWNLOADFAILED ${LANG_ENGLISH} "Download Failed:"
LangString ERROR_DOTNET_DUPLICATE_INSTANCE ${LANG_ENGLISH} "The $(DESC_SHORTDOTNET) Installer is \
  already running."
LangString ERROR_NOT_ADMINISTRATOR ${LANG_ENGLISH} "$(DESC_000022)"
LangString ERROR_INVALID_PLATFORM ${LANG_ENGLISH} "$(DESC_000023)"
LangString DESC_DOTNET_TIMEOUT ${LANG_ENGLISH} "The installation of the $(DESC_SHORTDOTNET) \
  has timed out."
LangString ERROR_DOTNET_INVALID_PATH ${LANG_ENGLISH} "The $(DESC_SHORTDOTNET) Installation$\n\
  was not found in the following location:$\n"
LangString ERROR_DOTNET_FATAL ${LANG_ENGLISH} "A fatal error occurred during the installation$\n\
  of the $(DESC_SHORTDOTNET)."
LangString FAILED_DOTNET_INSTALL ${LANG_ENGLISH} "The installation of $(PRODUCT_NAME) will$\n\
  continue. However, it may not function properly$\nuntil $(DESC_SHORTDOTNET)$\nis installed."
LangString DESC_DOTNET_NEEDED ${LANG_ENGLISH} "$(DESC_SHORTDOTNET) is required for the product activation.$\n \
  This .Net Framework version has not been detected by the installer.$\n \
  To proceed with product activation you will need to install$\n$(DESC_SHORTDOTNET).$\n \
  A link and guide for installing $(DESC_SHORTDOTNET) will be provided by the installation."
var vISDOTNETINSTALLED

Function InstallDotNetIfNotFound
  ; Lets go a look at the registry
  StrCpy $0 "0"
  StrCpy $1 "SOFTWARE\Microsoft\.NETFramework" ;registry entry to look in.
  StrCpy $2 0
  StrCpy $vISDOTNETINSTALLED 0 ; default value  = no

  StartEnum:
    ;Enumerate the versions installed.
    EnumRegKey $3 HKLM "$1\policy" $2

    ;If we don't find any versions installed, it's not here.
    StrCmp $3 "" noDotNet notEmpty

    ;We found something.
    notEmpty:
      ;Find out if the RegKey starts with 'v'.
      ;If it doesn't, goto the next key.
      StrCpy $4 $3 1 0
      StrCmp $4 "v" +1 goNext
      StrCpy $4 $3 1 1

      ;MessageBox MB_OK "Found : $4"
      ;It starts with 'v'.  Now check to see how the installed major version
      ;relates to our required major version.
      ;If it's equal check the minor version, if it's greater,
      ;we found a good RegKey.
      IntCmp $4 ${DOT_MAJOR} +1 goNext yesDotNetReg
      ;Check the minor version.  If it's equal or greater to our requested
      ;version then we're good.
      StrCpy $4 $3 1 3
      IntCmp $4 ${DOT_MINOR} yesDotNetReg goNext yesDotNetReg

    goNext:
      ;Go to the next RegKey.
      IntOp $2 $2 + 1
      goto StartEnum

  yesDotNetReg:
    ;Now that we've found a good RegKey, let's make sure it's actually
    ;installed by getting the install path and checking to see if the
    ;mscorlib.dll exists.
    ;MessageBox MB_OK "Checking yesDotNetReg"
    EnumRegValue $2 HKLM "$1\policy\$3" 0
    ;$2 should equal whatever comes after the major and minor versions
    ;(ie, v1.1.4322)
    StrCmp $2 "" noDotNet
    ReadRegStr $4 HKLM $1 "InstallRoot"
    ;Hopefully the install root isn't empty.
    StrCmp $4 "" noDotNet
    ;build the actuall directory path to mscorlib.dll.
    StrCpy $4 "$4$3.$2\mscorlib.dll"
    IfFileExists $4 yesDotNet noDotNet

  noDotNet:
;   MessageBox MB_OK "$(DESC_DOTNET_NEEDED)" ; this message removed as a different license system is installed for Win32

   ; ${SelectSection} ${SECDOTNET}
   return
  yesDotNet:
   strcpy $vISDOTNETINSTALLED 1 ; yes its there TEMP 0
    ;Everything checks out.  Go on with the rest of the installation.
    ;MessageBox MB_OK "Found the correct version of dot Net"
   ; ${UnSelectSection} ${SECDOTNET}
   return
FunctionEnd



