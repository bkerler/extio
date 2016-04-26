/*
	- In all text settings, the doublequote character (") should be escaped in the following form: $\"
*//*
http://nsis.sourceforge.net/Creating_language_files_and_integrating_with_MUI

GetDLLVersion "MyApp.exe" $R0 $R1
IntOp $R2 $R0 >> 16
IntOp $R2 $R2 & 0x0000FFFF ; $R2 now contains major version
IntOp $R3 $R0 & 0x0000FFFF ; $R3 now contains minor version
IntOp $R4 $R1 >> 16
IntOp $R4 $R4 & 0x0000FFFF ; $R4 now contains release
IntOp $R5 $R1 & 0x0000FFFF ; $R5 now contains build
StrCpy $0 "$R2.$R3.$R4.$R5" ; $0 now contains string like "1.2.0.192"
*/
!include "MUI2.nsh"

!define /date TIMESTAMP "%Y-%m-%d-%H-%M-%S"

SetCompressor lzma
RequestExecutionLevel admin

!define MUI_ABORTWARNING
!define MUI_ABORTWARNING_CANCEL_DEFAULT

!define MUI_UNABORTWARNING
!define MUI_UNABORTWARNING_CANCEL_DEFAULT

!define MUI_ICON						"spench-arrow.ico"	#"${NSISDIR}\Contrib\Graphics\Icons\modern-install-colorful.ico"
!define MUI_WELCOMEFINISHPAGE_BITMAP	"Wizard.bmp"
!define MUI_UNWELCOMEFINISHPAGE_BITMAP	"${MUI_WELCOMEFINISHPAGE_BITMAP}"
!define MUI_HEADERIMAGE
!define MUI_HEADERIMAGE_BITMAP			"Header.bmp"

!define MUI_UNICON "spench-uninstall-arrow.ico"	#"${NSISDIR}\Contrib\Graphics\Icons\orange-uninstall-nsis.ico"

#######################################

!define PRODUCT_NAME		"ExtIO_USRP+FCD+RTL2832U + BorIP"
!define PRODUCT_VERSION		"1.7 BETA 2"
!define PRODUCT_PUBLISHER	"balint@spench.net"
!define MAIN_COMMENT		"ExtIO_USRP+FCD plugin for Winrad-compatible SDR receivers && BorIP USRP+FCD Server"

!define UNINSTALLER			"Uninstall ${PRODUCT_NAME}.exe"

!define BORIP				"BorIP"
!define EXTIO_USRP			"ExtIO_USRP"	# Used for DLL file title

!define MAIN_WWW			"http://spench.net/r/USRP_Interfaces"
!define MAIN_RUN_KEY_NAME	"${BORIP}"
!define MAIN_REG			"Software\Baz's Appz\Installations\${PRODUCT_NAME}"
!define MAIN_REG_UNINSTALL	"Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define MAIN_DLL			"${EXTIO_USRP}.dll"
!define MAIN_EXE			"${BORIP}.exe"

#######################################

BrandingText "${PRODUCT_NAME} ${PRODUCT_VERSION} by ${PRODUCT_PUBLISHER}"
Name "${PRODUCT_NAME}"
OutFile "${PRODUCT_NAME}-${PRODUCT_VERSION}_Setup.exe"

InstallDir "<Read the above info>"	# "$PROGRAMFILES\<Read the above info>"
InstallDirRegKey HKCU "${MAIN_REG}" "InstallationDir"
!define DOWNLOAD_LOCATION	"$INSTDIR\Downloaded"

ShowInstDetails show
ShowUninstDetails show

#DirText ""
# If string was continued on new line using '\' then it would overwrite "Destination Folder" group control text

Var StartMenuFolder
#Var MainFolder

#Page Directory
#Page InstFiles

#######################################

	!define MUI_WELCOMEPAGE_TITLE "Installer for ${PRODUCT_NAME} ${PRODUCT_VERSION}"
	!define MUI_WELCOMEPAGE_TITLE_3LINES # Extra space for the title area
	!define MUI_WELCOMEPAGE_TEXT "The ExtIO_USRP+FCD+RTL2832U plugin will allow you to use your USRP/FCD hardware with the Winrad-series of SDR applications.$\n$\nBorIP will allow you to do this remotely over a network.$\n$\nData from both can be sent to other applications, such as the UDP Source block in GNU Radio/GRC.$\n$\nPress Next to continue."
!insertmacro MUI_PAGE_WELCOME

!insertmacro MUI_PAGE_LICENSE "License.rtf"

	!define MUI_COMPONENTSPAGE_SMALLDESC
!insertmacro MUI_PAGE_COMPONENTS

	!define MUI_DIRECTORYPAGE_TEXT_TOP	"- If you want to use the ExtIO plugin (and optionally BorIP), select your EXISTING ExtIO-compatible SDR receiver's installation folder (where you installed HDSDR/etc).$\n$\n- If you are performing a FRESH install of the receiver app (i.e. it is not yet installed), create the receiver directory below and select the same one during installation of the receiver itself.$\n$\n- If you ONLY want to use BorIP, create a new folder of your choice."
	!define MUI_DIRECTORYPAGE_VARIABLE	$INSTDIR	# $MainFolder
!insertmacro MUI_PAGE_DIRECTORY

	!define MUI_STARTMENUPAGE_DEFAULTFOLDER			"${PRODUCT_NAME}"
	!define MUI_STARTMENUPAGE_REGISTRY_ROOT			"HKCU"
	!define MUI_STARTMENUPAGE_REGISTRY_KEY			"${MAIN_REG}"
	!define MUI_STARTMENUPAGE_REGISTRY_VALUENAME	"ShortcutDir"
!insertmacro MUI_PAGE_STARTMENU MainShortcuts $StartMenuFolder

	!define MUI_INSTFILESPAGE_COLORS	"00FF00 000000"
!insertmacro MUI_PAGE_INSTFILES

	!define MUI_FINISHPAGE_NOAUTOCLOSE	# ShowInstDetails
!ifdef MAIN_EXE	
	!define MUI_FINISHPAGE_RUN
#	!define MUI_FINISHPAGE_RUN_NOTCHECKED
    !define MUI_FINISHPAGE_RUN_TEXT			"Start ${BORIP}"
    !define MUI_FINISHPAGE_RUN_FUNCTION		"Launch_Main"
!endif
	!define MUI_FINISHPAGE_SHOWREADME				"${MAIN_WWW}"
#	!define MUI_FINISHPAGE_SHOWREADME_NOTCHECKED
	!define MUI_FINISHPAGE_SHOWREADME_TEXT			"Open instructions (recommended)"
#	!define MUI_FINISHPAGE_SHOWREADME_FUNCTION		"Launch_WWW"

	!define MUI_FINISHPAGE_LINK					"${PRODUCT_NAME} Homepage"
	!define MUI_FINISHPAGE_LINK_LOCATION		"${MAIN_WWW}"
	
	!define MUI_FINISHPAGE_NOREBOOTSUPPORT	# Saves some space
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_UNPAGE_WELCOME
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

	!define MUI_UNFINISHPAGE_NOAUTOCLOSE	# ShowUninstDetails
!insertmacro MUI_UNPAGE_FINISH

!insertmacro MUI_LANGUAGE "English"

ReserveFile "${NSISDIR}\Plugins\InstallOptions.dll"

#######################################

VIProductVersion "1.0.0.0"

VIAddVersionKey /LANG=${LANG_ENGLISH} "ProductName" "${PRODUCT_NAME}"
VIAddVersionKey /LANG=${LANG_ENGLISH} "ProductVersion" "1.0.0.0"
VIAddVersionKey /LANG=${LANG_ENGLISH} "Comments" "${MAIN_COMMENT}"
VIAddVersionKey /LANG=${LANG_ENGLISH} "CompanyName" "spench.net"
#VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalTrademarks" "Test Application is a trademark of Fake company"
VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalCopyright" "© Balint Seeber 2011. All rights reserved."
VIAddVersionKey /LANG=${LANG_ENGLISH} "FileDescription" "${PRODUCT_NAME} (${TIMESTAMP})"
VIAddVersionKey /LANG=${LANG_ENGLISH} "FileVersion" "${PRODUCT_VERSION}"
VIAddVersionKey /LANG=${LANG_ENGLISH} "InternalName" "${TIMESTAMP}"
#VIAddVersionKey /LANG=${LANG_ENGLISH} "OriginalFilename" ""
#VIAddVersionKey /LANG=${LANG_ENGLISH} "PrivateBuild" ""
VIAddVersionKey /LANG=${LANG_ENGLISH} "SpecialBuild" "Beta"

###############################################################################

SectionGroup /e "Support files" secSupport

#Section "libusb (libwdi Zadig v1.1.1.139)" secLibUSB
Section "libusb (libwdi Zadig v2.0.1)" secLibUSB
	SetOutPath $INSTDIR
!define ZADIG_EXE	"zadig.exe"
	File ${ZADIG_EXE}
	MessageBox MB_YESNO|MB_ICONQUESTION "If you haven't installed libusb drivers before for your USRP using Zadig,$\nit is recommended you read a quick guide on how to do it properly.$\n$\nOpen the guide before launching Zadig?" IDYES open_guide IDNO continue
open_guide:
	ExecShell "open" "http://spench.net/r/USRP_Zadig"
continue:
	!insertmacro MUI_STARTMENU_WRITE_BEGIN MainShortcuts
		CreateDirectory	"$SMPROGRAMS\$StartMenuFolder"
		CreateShortCut	"$SMPROGRAMS\$StartMenuFolder\Zadig.lnk" "$\"$INSTDIR\${ZADIG_EXE}$\"" "" "" "" "" "" "Configure libusb drivers"
	!insertmacro MUI_STARTMENU_WRITE_END
	ExecWait "$INSTDIR\${ZADIG_EXE}"
SectionEnd

LangString desc_secLibUSB ${LANG_ENGLISH} "Install drivers required to access USB-based USRPs (i.e. USRP 1)"

!define RUNTIME_FILE		"${DOWNLOAD_LOCATION}\vcredist_x86_2008_sp1.exe"

Section /o "VC++ Runtime (2008 SP1)" secRuntime
	AddSize 4119
	SetOutPath ${DOWNLOAD_LOCATION}	# Download is placed in installation directory
	NSISdl::download "http://download.microsoft.com/download/d/d/9/dd9a82d0-52ef-40db-8dab-795376989c03/vcredist_x86.exe" "${RUNTIME_FILE}"
		Pop $R0 ;Get the return value
		StrCmp $R0 "success" install
			MessageBox MB_YESNO|MB_ICONEXCLAMATION "Download failed: $R0$\n$\n${PRODUCT_NAME} may not run until this component is correctly installed.$\n$\nDo you wish to continue?" IDYES true IDNO false
			true:
				Goto finish
			false:
				Abort "Download failed: $R0"
install:
	ExecWait "${RUNTIME_FILE}"	# FIXME: Silent install?
finish:
	#ExecShell "open" "http://www.microsoft.com/DOWNLOADS/details.aspx?familyid=A5C84275-3B97-4AB7-A40D-3802B2AF5FC2&displaylang=en"
	#MessageBox MB_OK|MB_ICONINFORMATION "The Microsoft download site has been opened.$\n$\nPlease click OK once you have installed the runtime."
SectionEnd

LangString desc_secRuntime ${LANG_ENGLISH} "Runtime for C++ and MFC 9.0 SP1 (will be downloaded from Microsoft)"

SectionGroupEnd

LangString desc_secSupport ${LANG_ENGLISH} "Support files - if you unsure you already have a component, you should install it anyway (it is safe)"

###############################################################################

Section "!${PRODUCT_NAME}" secMain
	#SetShellVarContext all

	# call userInfo plugin to get user info.  The plugin puts the result in the stack
    #userInfo::getAccountType
    # pop the result from the stack into $0
    #pop $0
    # compare the result with the string "Admin" to see if the user is admin.
    # If match, jump 3 lines down.
    #strCmp $0 "Admin" +3

	SetOutPath $INSTDIR

	#Rename "$INSTDIR" "$INSTDIR.${PRODUCT_VERSION}.${TIMESTAMP}"	# Create backup if already exists
	
	File "C:\Program Files\Sound\HDSDR\Release\${MAIN_DLL}"
	File "Release\${MAIN_EXE}"
	
	File "Release\libusb-1.0.dll"
	File "Release\libusrp.dll"
	File "Release\librtl2832++.dll"
	File "Release\uhd.dll"
	File "Release\liborc-0.4-0.dll"
	#File "Release\usrp1_fw.ihx"
	#File "Release\usrp1_fpga.rbf"
	#File "Release\usrp1_fpga_4rx.rbf"
	File /r "D:\Dev\usrp-images-distrib\*.*"
	File /r "Release\rev4"
	
	FindFirst $0 $1 "$SYSDIR\libusb0.dll"
	FindClose $0
	StrCmp $1 "" install_libusb0
	Goto skip_libusb0
install_libusb0:
		MessageBox MB_YESNO|MB_ICONINFORMATION "libusb0.dll was not found in your Windows System directory.$\nThis is likely due to you either choosing a libusb1 driver, or not installing any driver at all.$\n$\nlibusb0.dll must be found by this software for it to work.$\n$\nIf you are going to install a libusb0 (NOT libusb1) driver, and therefore libusb0.dll, using the included libusb installer, or manually, select 'No'.$\n$\nIf you don't know what this means (or are using libusb1 drivers only), select 'Yes'. This will install a local copy." IDYES install_libusb0_file IDNO skip_libusb0
install_libusb0_file:		
		File "/oname=libusb0.dll" "C:\Dev\SDK\libusb0\bin\x86\libusb0_x86.dll"
skip_libusb0:
	
	WriteRegStr HKCU "${MAIN_REG}" "InstallationDir" "$INSTDIR"

	writeUninstaller "$INSTDIR\${UNINSTALLER}"
	
	!insertmacro MUI_STARTMENU_WRITE_BEGIN MainShortcuts
		CreateDirectory	"$SMPROGRAMS\$StartMenuFolder"
		CreateShortCut	"$SMPROGRAMS\$StartMenuFolder\${BORIP}.lnk" "$\"$INSTDIR\${MAIN_EXE}$\"" "" "" "" "" "" "Start ${BORIP} server"
		#CreateShortCut	"$SMPROGRAMS\$StartMenuFolder\Stop iTunes plugin.lnk" "rundll32.exe" "$\"$INSTDIR\${MAIN_DLL}$\",Quit iTunes" "" "" "" "" "Stop the NISRP plugin for iTunes (it will no longer appear when running iTunes)"
		CreateShortCut	"$SMPROGRAMS\$StartMenuFolder\Uninstall.lnk" "$INSTDIR\${UNINSTALLER}"
	!insertmacro MUI_STARTMENU_WRITE_END

	WriteRegStr		HKLM "${MAIN_REG_UNINSTALL}" "DisplayName" "${PRODUCT_NAME}"
	WriteRegStr		HKLM "${MAIN_REG_UNINSTALL}" "UninstallString" "$\"$INSTDIR\${UNINSTALLER}$\""
	WriteRegStr		HKLM "${MAIN_REG_UNINSTALL}" "Publisher" "spench.net"
	WriteRegStr		HKLM "${MAIN_REG_UNINSTALL}" "URLInfoAbout" "${MAIN_WWW}"
	WriteRegDWORD	HKLM "${MAIN_REG_UNINSTALL}" "NoModify" 1
	WriteRegDWORD	HKLM "${MAIN_REG_UNINSTALL}" "NoRepair" 1
	WriteRegStr		HKLM "${MAIN_REG_UNINSTALL}" "DisplayIcon" "$\"$INSTDIR\${UNINSTALLER}$\""
SectionEnd

LangString desc_secMain ${LANG_ENGLISH} "${MAIN_COMMENT}"

SectionGroup /e "Settings" secSettings

!ifdef MAIN_RUN_KEY_NAME
Section /o "Autorun BorIP" secAutorun_Main
	WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Run" "${MAIN_RUN_KEY_NAME}" "$\"$INSTDIR\${MAIN_EXE}$\" /autorun"
SectionEnd

LangString desc_secAutorun_Main ${LANG_ENGLISH} "Automatically start BorIP when you log on"
!endif # MAIN_RUN_KEY_NAME

SectionGroupEnd

LangString desc_secSettings ${LANG_ENGLISH} "Settings you can configure at installation time"

###############################################################################

SectionGroup /e "Download an SDR receiver application" secSDR

Section /o "!HDSDR (download latest)" secSDR_HDSDR
	AddSize 911	# v2.0	# Download is placed in installation directory
	SetOutPath ${DOWNLOAD_LOCATION}
	NSISdl::download "http://www.hdsdr.de/download/HDSDR_install.exe" "${DOWNLOAD_LOCATION}\HDSDR_install.exe"
		Pop $R0 ;Get the return value
		StrCmp $R0 "success" install
			MessageBox MB_YESNO|MB_ICONEXCLAMATION "Download failed: $R0$\n$\nDo you wish to continue?" IDYES true IDNO false
			true:
				Goto finish
			false:
				Abort "Download failed: $R0"
install:
	ExecWait "${DOWNLOAD_LOCATION}\HDSDR_install.exe"
finish:
SectionEnd

LangString desc_secSDR_HDSDR ${LANG_ENGLISH} "Download && install HDSDR"

Section /o "Winrad (download v1.6.1)" secSDR_Winrad
	AddSize 850
	SetOutPath ${DOWNLOAD_LOCATION}	# Download is placed in installation directory
	NSISdl::download "http://www.winrad.org/bin/Winrad161.msi" "${DOWNLOAD_LOCATION}\Winrad161.msi"
		Pop $R0 ;Get the return value
		StrCmp $R0 "success" install
			MessageBox MB_YESNO|MB_ICONEXCLAMATION "Download failed: $R0$\n$\nDo you wish to continue?" IDYES true IDNO false
			true:
				Goto finish
			false:
				Abort "Download failed: $R0"
install:
	ExecWait "msiexec.exe /i $\"${DOWNLOAD_LOCATION}\Winrad161.msi$\""
finish:
SectionEnd

LangString desc_secSDR_Winrad ${LANG_ENGLISH} "Download && install Winrad"

SectionGroupEnd

LangString desc_secSDR ${LANG_ENGLISH} "If you don't already have an SDR receiver application, download && install one to use ExtIO_USRP"

###############################################################################

Function .onSelChange
	#MessageBox MB_OK "Changed"
FunctionEnd

###############################################################################

!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
  !insertmacro MUI_DESCRIPTION_TEXT ${secMain} $(desc_secMain)
  !insertmacro MUI_DESCRIPTION_TEXT ${secRuntime} $(desc_secRuntime)
!ifdef MAIN_RUN_KEY_NAME
  !insertmacro MUI_DESCRIPTION_TEXT ${secAutorun_Main} $(desc_secAutorun_Main)
!endif # MAIN_RUN_KEY_NAME
  !insertmacro MUI_DESCRIPTION_TEXT ${secSettings} $(desc_secSettings)
  !insertmacro MUI_DESCRIPTION_TEXT ${secLibUSB} $(desc_secLibUSB)
  !insertmacro MUI_DESCRIPTION_TEXT ${secSupport} $(desc_secSupport)
  !insertmacro MUI_DESCRIPTION_TEXT ${secSDR} $(desc_secSDR)
  !insertmacro MUI_DESCRIPTION_TEXT ${secSDR_Winrad} $(desc_secSDR_Winrad)
  !insertmacro MUI_DESCRIPTION_TEXT ${secSDR_HDSDR} $(desc_secSDR_HDSDR)
!insertmacro MUI_FUNCTION_DESCRIPTION_END

!ifdef MAIN_EXE
Function Launch_Main
	# Single quote ' not used since args are not passed properly (however won't work on Win98?)
	Exec "$\"$INSTDIR\${MAIN_EXE}$\""
FunctionEnd
!endif # MAIN_EXE

Function .onInit
	#Banner::show #"Starting installer..."
	
#	!insertmacro MUI_LANGDLL_DISPLAY

	#StrCpy $MainFolder $INSTDIR

	ClearErrors
	#StrCpy $0 0
	EnumRegValue $1 HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\SideBySide\Winners\x86_microsoft.vc90.crt_1fc8b3b9a1e18e3b_none_ea33c8f0b247cd77\9.0" 0 #$0
	IfErrors no_runtime_check_xp
	#IntOp $0 $0 + 1
	#ReadRegStr $2 HKLM Software\Microsoft\Windows\CurrentVersion $1
	Goto skip_runtime	# Runtime is present
no_runtime_check_xp:
	ClearErrors
	EnumRegKey $1 HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\SideBySide\Installations\x86_Microsoft.VC90.CRT_1fc8b3b9a1e18e3b_9.0.21022.8_x-ww_d08d0375" 0 #$0
	IfErrors no_runtime
	Goto skip_runtime
no_runtime:
	IntOp $0 ${SF_SELECTED} | ${SF_RO}
	SectionSetFlags ${secRuntime} $0
skip_runtime:

	#Banner::destroy
FunctionEnd

#######################################

#Page uninstConfirm	# Cannot use this as it appears in the installer too

# create a section to define what the uninstaller does.
# the section will always be named "Uninstall"
Section "Uninstall" secUninstall
	#SetShellVarContext all

	#DetailPrint "Exiting SoftMicroswitchFix..."
	#ExecWait "$\"$INSTDIR\${MAIN_EXE}$\" /quit"
 
	Delete "$INSTDIR\${UNINSTALLER}"	# Always delete uninstaller first
	
borip_delete:	
	Delete "$INSTDIR\${MAIN_EXE}"
	IfErrors borip_is_running
	Goto borip_continue
borip_is_running:
	MessageBox MB_YESNO|MB_ICONEXCLAMATION "Failed to delete BorIP.exe$\n$\nThis may be because it is still running.$\n$\nWould you like to try deleting it again?" IDYES borip_delete IDNO borip_continue
borip_continue:
	Delete "$INSTDIR\${MAIN_DLL}"
	
	Delete "$INSTDIR\libusb-1.0.dll"
	Delete "$INSTDIR\libusrp.dll"
	Delete "$INSTDIR\librtl2832++.dll"
	Delete "$INSTDIR\uhd.dll"
	RMDir /r "$INSTDIR\rev4"
	Delete "$INSTDIR\libusb0.dll"
	Delete "$INSTDIR\zadig.exe"
	
	#Delete "$INSTDIR\usrp1_fw.ihx"
	#Delete "$INSTDIR\usrp1_fpga.rbf"
	#Delete "$INSTDIR\usrp1_fpga_4rx.rbf"
	RMDir /r "$INSTDIR\bit"
	Delete "$INSTDIR\*.bin"
	Delete "$INSTDIR\*.ihx"
	Delete "$INSTDIR\*.rbf"
	Delete "$INSTDIR\*.tag"
	
	IfFileExists "${DOWNLOAD_LOCATION}" 0 continue
		MessageBox MB_YESNO|MB_ICONQUESTION "Would you like to delete the files the installer downloaded from:$\n$\n${DOWNLOAD_LOCATION}" IDYES true IDNO continue
true:
		RMDir /r "${DOWNLOAD_LOCATION}"
continue:
	RMDir "$INSTDIR"	# Silent failure (leave files that remain)
	
	!insertmacro MUI_STARTMENU_GETFOLDER MainShortcuts $StartMenuFolder
	Delete	"$SMPROGRAMS\$StartMenuFolder\${BORIP}.lnk"
	Delete	"$SMPROGRAMS\$StartMenuFolder\Zadig.lnk"
	Delete	"$SMPROGRAMS\$StartMenuFolder\Uninstall.lnk"
	RMDir	"$SMPROGRAMS\$StartMenuFolder"	#/r

!ifdef MAIN_RUN_KEY_NAME
	DeleteRegValue HKCU "Software\Microsoft\Windows\CurrentVersion\Run" "${MAIN_RUN_KEY_NAME}"
!endif # MAIN_RUN_KEY_NAME

	DeleteRegKey HKLM "${MAIN_REG_UNINSTALL}"
	
/*	MessageBox MB_YESNO|MB_ICONQUESTION "Would you also like to remove your preferences?" IDYES remove_prefs IDNO finish
remove_prefs:
	DeleteRegKey HKCU "${MAIN_REG}\Settings"
finish:
*/	DeleteRegKey /ifempty HKCU "${MAIN_REG}"
SectionEnd

Function un.onInit
#	!insertmacro MUI_UNGETLANGUAGE
FunctionEnd
