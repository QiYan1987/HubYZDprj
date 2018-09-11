# Microsoft Developer Studio Project File - Name="Wilson6" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Wilson6 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Wilson6.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Wilson6.mak" CFG="Wilson6 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Wilson6 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Wilson6 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Wilson6 - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Wilson6 - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 MPC08.lib 8112PG.lib IPHLPAPI.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Wilson6 - Win32 Release"
# Name "Wilson6 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\3dPoint.cpp
# End Source File
# Begin Source File

SOURCE=.\AmpScale.cpp
# End Source File
# Begin Source File

SOURCE=.\biaoding.cpp
# End Source File
# Begin Source File

SOURCE=.\Body.cpp
# End Source File
# Begin Source File

SOURCE=.\Canshuchushi.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorMap.cpp
# End Source File
# Begin Source File

SOURCE=.\ComboToolBar1.cpp
# End Source File
# Begin Source File

SOURCE=.\DesktopView.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_CZD.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_PMD.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_pmPXD.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_PXD.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_QKxs.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_SavePath.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_TZD.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_YD.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_YZD.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_ZXD.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAjustCenter.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAjustCenterAndPose.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAjustPingjing.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCHGQBiaoDing.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgextendCircle.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlgfrequency1.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgGongYiSetting.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgHands.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMachineInf.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOneAxisPara.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOneAxisPara1.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgUserManagement.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgZuobiao.cpp
# End Source File
# Begin Source File

SOURCE=.\DoAdjustOritation.cpp
# End Source File
# Begin Source File

SOURCE=.\DoAdjustPosition.cpp
# End Source File
# Begin Source File

SOURCE=.\DoCircle.cpp
# End Source File
# Begin Source File

SOURCE=.\DoCircleRunOut.cpp
# End Source File
# Begin Source File

SOURCE=.\DoCoaxiality.cpp
# End Source File
# Begin Source File

SOURCE=.\DoCylinder.cpp
# End Source File
# Begin Source File

SOURCE=.\DoDynamicDisplay.cpp
# End Source File
# Begin Source File

SOURCE=.\DoParallelism.cpp
# End Source File
# Begin Source File

SOURCE=.\DoPlaneness.cpp
# End Source File
# Begin Source File

SOURCE=.\DoStraightness.cpp
# End Source File
# Begin Source File

SOURCE=.\DoVerticality.cpp
# End Source File
# Begin Source File

SOURCE=.\HeaderCtrlCl.cpp
# End Source File
# Begin Source File

SOURCE=.\JMAnalyse.cpp
# End Source File
# Begin Source File

SOURCE=.\Line.cpp
# End Source File
# Begin Source File

SOURCE=.\ListCtrlCl.cpp
# End Source File
# Begin Source File

SOURCE=.\LOGIN.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MotorCorrection.cpp
# End Source File
# Begin Source File

SOURCE=.\MotorState.cpp
# End Source File
# Begin Source File

SOURCE=.\PageEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\PageFilter.cpp
# End Source File
# Begin Source File

SOURCE=.\PageInorOut.cpp
# End Source File
# Begin Source File

SOURCE=.\PageParaG.cpp
# End Source File
# Begin Source File

SOURCE=.\PageProAlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PageSelect.cpp
# End Source File
# Begin Source File

SOURCE=.\PageTargetEccentricity.cpp
# End Source File
# Begin Source File

SOURCE=.\PageTimes.cpp
# End Source File
# Begin Source File

SOURCE=.\PropertyDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\scbarg.cpp
# End Source File
# Begin Source File

SOURCE=.\sizecbar.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Wilson6.cpp
# End Source File
# Begin Source File

SOURCE=.\Wilson6.rc
# End Source File
# Begin Source File

SOURCE=.\WilsonFrame.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\3dPoint.h
# End Source File
# Begin Source File

SOURCE=.\AmpScale.h
# End Source File
# Begin Source File

SOURCE=..\11\BCMenu.h
# End Source File
# Begin Source File

SOURCE=.\biaoding.h
# End Source File
# Begin Source File

SOURCE=.\Body.h
# End Source File
# Begin Source File

SOURCE=.\Canshuchushi.h
# End Source File
# Begin Source File

SOURCE=.\ColorMap.h
# End Source File
# Begin Source File

SOURCE=.\ComboToolBar1.h
# End Source File
# Begin Source File

SOURCE=.\const.h
# End Source File
# Begin Source File

SOURCE=.\DesktopView.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_CZD.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_PMD.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_pmPXD.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_PXD.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_QKxs.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_SavePath.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_TZD.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_YD.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_YZD.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_ZXD.h
# End Source File
# Begin Source File

SOURCE=.\DlgAjustCenter.h
# End Source File
# Begin Source File

SOURCE=.\DlgAjustCenterAndPose.h
# End Source File
# Begin Source File

SOURCE=.\DlgAjustPingjing.h
# End Source File
# Begin Source File

SOURCE=.\DlgCHGQBiaoDing.h
# End Source File
# Begin Source File

SOURCE=.\DlgextendCircle.h
# End Source File
# Begin Source File

SOURCE=.\Dlgfrequency1.h
# End Source File
# Begin Source File

SOURCE=.\DlgGongYiSetting.h
# End Source File
# Begin Source File

SOURCE=.\DlgHands.h
# End Source File
# Begin Source File

SOURCE=.\DlgMachineInf.h
# End Source File
# Begin Source File

SOURCE=.\DlgOneAxisPara.h
# End Source File
# Begin Source File

SOURCE=.\DlgOneAxisPara1.h
# End Source File
# Begin Source File

SOURCE=.\DlgUserManagement.h
# End Source File
# Begin Source File

SOURCE=.\DlgZuobiao.h
# End Source File
# Begin Source File

SOURCE=.\DLL2.H
# End Source File
# Begin Source File

SOURCE=.\DoAdjustOritation.h
# End Source File
# Begin Source File

SOURCE=.\DoAdjustPosition.h
# End Source File
# Begin Source File

SOURCE=.\DoCircle.h
# End Source File
# Begin Source File

SOURCE=.\DoCircleRunOut.h
# End Source File
# Begin Source File

SOURCE=.\DoCoaxiality.h
# End Source File
# Begin Source File

SOURCE=.\DoCylinder.h
# End Source File
# Begin Source File

SOURCE=.\DoDynamicDisplay.h
# End Source File
# Begin Source File

SOURCE=.\DoParallelism.h
# End Source File
# Begin Source File

SOURCE=.\DoPlaneness.h
# End Source File
# Begin Source File

SOURCE=.\DoStraightness.h
# End Source File
# Begin Source File

SOURCE=.\DoVerticality.h
# End Source File
# Begin Source File

SOURCE=.\FilterSelect.h
# End Source File
# Begin Source File

SOURCE=.\HeaderCtrlCl.h
# End Source File
# Begin Source File

SOURCE=.\JMAnalyse.h
# End Source File
# Begin Source File

SOURCE=.\Line.h
# End Source File
# Begin Source File

SOURCE=.\ListCtrlCl.h
# End Source File
# Begin Source File

SOURCE=.\LOGIN.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MotorCorrection.h
# End Source File
# Begin Source File

SOURCE=.\MotorState.h
# End Source File
# Begin Source File

SOURCE=.\Mpc.h
# End Source File
# Begin Source File

SOURCE=.\PageEdit.h
# End Source File
# Begin Source File

SOURCE=.\PageFilter.h
# End Source File
# Begin Source File

SOURCE=.\PageInorOut.h
# End Source File
# Begin Source File

SOURCE=.\PageParaG.h
# End Source File
# Begin Source File

SOURCE=.\PageProAlg.h
# End Source File
# Begin Source File

SOURCE=.\PageSelect.h
# End Source File
# Begin Source File

SOURCE=.\PageTargetEccentricity.h
# End Source File
# Begin Source File

SOURCE=.\PageTimes.h
# End Source File
# Begin Source File

SOURCE=.\Preserve.h
# End Source File
# Begin Source File

SOURCE=.\PropertyDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\scbarg.h
# End Source File
# Begin Source File

SOURCE=.\sizecbar.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\11\SXBtn.h
# End Source File
# Begin Source File

SOURCE=.\type_def.h
# End Source File
# Begin Source File

SOURCE=.\Wilson6.h
# End Source File
# Begin Source File

SOURCE=.\WilsonFrame.h
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\Program Files\Microsoft Visual Studio\VC98\Include\WINUSER.H"
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\0.cur
# End Source File
# Begin Source File

SOURCE=.\res\2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\20111115032357892_easyicon_cn_24.ico
# End Source File
# Begin Source File

SOURCE=.\res\20111115032725945_easyicon_cn_32.ico
# End Source File
# Begin Source File

SOURCE=.\res\3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\6.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BGFX.ico
# End Source File
# Begin Source File

SOURCE=.\res\bitmap13.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap14.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap15.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap17.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap18.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap19.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap21.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap22.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap7.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap_d.bmp
# End Source File
# Begin Source File

SOURCE=.\res\chuangan.bmp
# End Source File
# Begin Source File

SOURCE=.\res\chuanganqi.bmp
# End Source File
# Begin Source File

SOURCE=.\res\chuli.ico
# End Source File
# Begin Source File

SOURCE=.\res\Created.ico
# End Source File
# Begin Source File

SOURCE=.\res\created2.ico
# End Source File
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursor2.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursor5.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursor6.cur
# End Source File
# Begin Source File

SOURCE=.\res\czd.ico
# End Source File
# Begin Source File

SOURCE=.\res\denglutubiao1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\desktop.bmp
# End Source File
# Begin Source File

SOURCE=.\res\disenable.ico
# End Source File
# Begin Source File

SOURCE=.\res\Document0000.cur
# End Source File
# Begin Source File

SOURCE=.\res\enable.ico
# End Source File
# Begin Source File

SOURCE=.\res\folder.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00002.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00003.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00004.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00005.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00006.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00007.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00008.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00009.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00010.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00011.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00012.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon10.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon11.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon12.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon13.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon14.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon15.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon16.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon17.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon18.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon19.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon20.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon21.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon24.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon25.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon28.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon29.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon3.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon30.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon32.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon33.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon4.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon5.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon6.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon7.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon8.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon9.ico
# End Source File
# Begin Source File

SOURCE=.\res\IDI_DISABLE.ico
# End Source File
# Begin Source File

SOURCE=.\res\kebiao.ico
# End Source File
# Begin Source File

SOURCE=.\res\lizhu.bmp
# End Source File
# Begin Source File

SOURCE=.\res\lizhu2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\osx10.ico
# End Source File
# Begin Source File

SOURCE=.\res\pingtai.bmp
# End Source File
# Begin Source File

SOURCE=.\res\pingtai2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\pingtaidisplay.bmp
# End Source File
# Begin Source File

SOURCE=.\res\pingtaidisplay12.bmp
# End Source File
# Begin Source File

SOURCE=.\res\pintai.bmp
# End Source File
# Begin Source File

SOURCE=".\2012-3-31\res\pist.ico"
# End Source File
# Begin Source File

SOURCE=.\res\pist.ico
# End Source File
# Begin Source File

SOURCE=.\res\pmd.ico
# End Source File
# Begin Source File

SOURCE=.\res\PPFX.ico
# End Source File
# Begin Source File

SOURCE=.\res\pxd.ico
# End Source File
# Begin Source File

SOURCE=.\res\r.bmp
# End Source File
# Begin Source File

SOURCE=.\res\R2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\reset.bmp
# End Source File
# Begin Source File

SOURCE=.\res\right.ico
# End Source File
# Begin Source File

SOURCE=.\res\rotcyl.ico
# End Source File
# Begin Source File

SOURCE=".\res\自建图标\Rzhouyou.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\setorigi.ico
# End Source File
# Begin Source File

SOURCE=.\res\setother.ico
# End Source File
# Begin Source File

SOURCE=.\res\stop.bmp
# End Source File
# Begin Source File

SOURCE=.\res\stop.ico
# End Source File
# Begin Source File

SOURCE=.\res\taiping.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tiaoping.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tiaoxin.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tiaoxinping.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tleft.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar5.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tree_closed.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tree_opened.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tright.ico
# End Source File
# Begin Source File

SOURCE=.\res\trt.ico
# End Source File
# Begin Source File

SOURCE=.\res\txd.ico
# End Source File
# Begin Source File

SOURCE=.\res\tzd.ico
# End Source File
# Begin Source File

SOURCE=.\res\Wilson6.ico
# End Source File
# Begin Source File

SOURCE=.\res\Wilson6.rc2
# End Source File
# Begin Source File

SOURCE=.\res\zhuzhou.bmp
# End Source File
# Begin Source File

SOURCE=.\res\zhuzhou2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\zhuzhou3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\zxd.ico
# End Source File
# Begin Source File

SOURCE=".\res\登录.ico"
# End Source File
# Begin Source File

SOURCE=".\res\删除(新).ico"
# End Source File
# Begin Source File

SOURCE=".\res\项目3.ico"
# End Source File
# Begin Source File

SOURCE=".\res\注销.ico"
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
