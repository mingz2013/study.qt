; �ýű�ʹ�� HM VNISEdit �ű��༭���򵼲���

; ��װ�����ʼ���峣��
!define PRODUCT_NAME "webQQ"
!define PRODUCT_VERSION "1.0"
!define PRODUCT_PUBLISHER "MingZz"
!define PRODUCT_WEB_SITE "http://www.MingZz.com"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\webqq21.exe"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"

SetCompressor lzma

; ------ MUI �ִ����涨�� (1.67 �汾���ϼ���) ------
!include "MUI.nsh"

; MUI Ԥ���峣��
!define MUI_ABORTWARNING
!define MUI_ICON "webQQ.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"

; ��ӭҳ��
!insertmacro MUI_PAGE_WELCOME
; ���Э��ҳ��
!define MUI_LICENSEPAGE_CHECKBOX
!insertmacro MUI_PAGE_LICENSE "Licence.txt"
; ��װĿ¼ѡ��ҳ��
!insertmacro MUI_PAGE_DIRECTORY
; ��װ����ҳ��
!insertmacro MUI_PAGE_INSTFILES
; ��װ���ҳ��
!define MUI_FINISHPAGE_RUN "$INSTDIR\webqq21.exe"
!insertmacro MUI_PAGE_FINISH

; ��װж�ع���ҳ��
!insertmacro MUI_UNPAGE_INSTFILES

; ��װ�����������������
!insertmacro MUI_LANGUAGE "SimpChinese"

; ��װԤ�ͷ��ļ�
!insertmacro MUI_RESERVEFILE_INSTALLOPTIONS
; ------ MUI �ִ����涨����� ------

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "webQQ.exe"
InstallDir "$PROGRAMFILES\webQQ"
InstallDirRegKey HKLM "${PRODUCT_UNINST_KEY}" "UninstallString"
ShowInstDetails show
ShowUnInstDetails show

Section "MainSection" SEC01
  SetOutPath "$INSTDIR"
  SetOverwrite ifnewer
  File "icudt51.dll"
  CreateDirectory "$SMPROGRAMS\webQQ"
  CreateShortCut "$SMPROGRAMS\webQQ\webQQ.lnk" "$INSTDIR\webqq21.exe"
  CreateShortCut "$DESKTOP\webQQ.lnk" "$INSTDIR\webqq21.exe"
  File "icuin51.dll"
  File "icuuc51.dll"
  SetOutPath "$INSTDIR\JS"
  File "JS\hash.js"
  File "JS\QQ.js"
  SetOutPath "$INSTDIR"
  File "libeay32.dll"
  File "libgcc_s_dw2-1.dll"
  File "libstdc++-6.dll"
  File "libwinpthread-1.dll"
  File "Licence.txt"
  File "nsis.nsi"
  SetOutPath "$INSTDIR\platforms"
  File "platforms\qwindows.dll"
  SetOutPath "$INSTDIR"
  File "Qt5Core.dll"
  File "Qt5Gui.dll"
  File "Qt5Network.dll"
  File "Qt5Script.dll"
  File "Qt5Widgets.dll"
  File "SortDefault.nls"
  File "ssleay32.dll"
  File "webQQ.ico"
  File "webqq21.exe"
SectionEnd

Section -AdditionalIcons
  WriteIniStr "$INSTDIR\${PRODUCT_NAME}.url" "InternetShortcut" "URL" "${PRODUCT_WEB_SITE}"
  CreateShortCut "$SMPROGRAMS\webQQ\Website.lnk" "$INSTDIR\${PRODUCT_NAME}.url"
  CreateShortCut "$SMPROGRAMS\webQQ\Uninstall.lnk" "$INSTDIR\uninst.exe"
SectionEnd

Section -Post
  WriteUninstaller "$INSTDIR\uninst.exe"
  WriteRegStr HKLM "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR\webqq21.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\webqq21.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
SectionEnd

/******************************
 *  �����ǰ�װ�����ж�ز���  *
 ******************************/

Section Uninstall
  Delete "$INSTDIR\${PRODUCT_NAME}.url"
  Delete "$INSTDIR\uninst.exe"
  Delete "$INSTDIR\webqq21.exe"
  Delete "$INSTDIR\webQQ.ico"
  Delete "$INSTDIR\ssleay32.dll"
  Delete "$INSTDIR\SortDefault.nls"
  Delete "$INSTDIR\Qt5Widgets.dll"
  Delete "$INSTDIR\Qt5Script.dll"
  Delete "$INSTDIR\Qt5Network.dll"
  Delete "$INSTDIR\Qt5Gui.dll"
  Delete "$INSTDIR\Qt5Core.dll"
  Delete "$INSTDIR\platforms\qwindows.dll"
  Delete "$INSTDIR\nsis.nsi"
  Delete "$INSTDIR\Licence.txt"
  Delete "$INSTDIR\libwinpthread-1.dll"
  Delete "$INSTDIR\libstdc++-6.dll"
  Delete "$INSTDIR\libgcc_s_dw2-1.dll"
  Delete "$INSTDIR\libeay32.dll"
  Delete "$INSTDIR\JS\QQ.js"
  Delete "$INSTDIR\JS\hash.js"
  Delete "$INSTDIR\icuuc51.dll"
  Delete "$INSTDIR\icuin51.dll"
  Delete "$INSTDIR\icudt51.dll"

  Delete "$SMPROGRAMS\webQQ\Uninstall.lnk"
  Delete "$SMPROGRAMS\webQQ\Website.lnk"
  Delete "$DESKTOP\webQQ.lnk"
  Delete "$SMPROGRAMS\webQQ\webQQ.lnk"

  RMDir "$SMPROGRAMS\webQQ"
  RMDir "$INSTDIR\platforms"
  RMDir "$INSTDIR\JS"

  RMDir "$INSTDIR"

  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
  SetAutoClose true
SectionEnd

#-- ���� NSIS �ű��༭�������� Function ���α�������� Section ����֮���д���Ա��ⰲװ�������δ��Ԥ֪�����⡣--#

Function un.onInit
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "��ȷʵҪ��ȫ�Ƴ� $(^Name) ���������е������" IDYES +2
  Abort
FunctionEnd

Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) �ѳɹ��ش����ļ�����Ƴ���"
FunctionEnd
