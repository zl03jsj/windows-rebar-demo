# Microsoft Developer Studio Project File - Name="MyWinFrameWork" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=MyWinFrameWork - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MyWinFrameWork.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MyWinFrameWork.mak" CFG="MyWinFrameWork - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MyWinFrameWork - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MyWinFrameWork - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MyWinFrameWork - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /D "NDEBUG" /D "WIN32" /D "_MBCS" /YX /FD /c
# SUBTRACT CPP /O<none>
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib comctl32.lib /nologo /entry:"" /machine:I386
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "MyWinFrameWork - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib comctl32.lib /nologo /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "MyWinFrameWork - Win32 Release"
# Name "MyWinFrameWork - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\mywindow.cpp
# End Source File
# Begin Source File

SOURCE=.\rebar.cpp
# End Source File
# Begin Source File

SOURCE=.\resource.rc
# End Source File
# Begin Source File

SOURCE=.\toolbar.cpp
# End Source File
# Begin Source File

SOURCE=.\winmain.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\mywindow.h
# End Source File
# Begin Source File

SOURCE=.\rebar.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\toolbar.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\myicons\About.ico
# End Source File
# Begin Source File

SOURCE=.\myicons\Check.ico
# End Source File
# Begin Source File

SOURCE=".\myicons\Close 2.ico"
# End Source File
# Begin Source File

SOURCE=.\myicons\Close.ico
# End Source File
# Begin Source File

SOURCE=.\myicons\Copy.ico
# End Source File
# Begin Source File

SOURCE=.\myicons\Cut.ico
# End Source File
# Begin Source File

SOURCE=".\myicons\Delete 2.ico"
# End Source File
# Begin Source File

SOURCE=.\myicons\Delete.ico
# End Source File
# Begin Source File

SOURCE=.\myicons\Document.ico
# End Source File
# Begin Source File

SOURCE=.\myicons\Exit.ico
# End Source File
# Begin Source File

SOURCE=.\myicons\Help.ico
# End Source File
# Begin Source File

SOURCE=.\myicons\New.ico
# End Source File
# Begin Source File

SOURCE=.\myicons\Open.ico
# End Source File
# Begin Source File

SOURCE=.\myicons\Paste.ico
# End Source File
# Begin Source File

SOURCE=.\myicons\Picture.ico
# End Source File
# Begin Source File

SOURCE=.\myicons\Preview.ico
# End Source File
# Begin Source File

SOURCE=.\myicons\Printer.ico
# End Source File
# Begin Source File

SOURCE=.\myicons\Redo.ico
# End Source File
# Begin Source File

SOURCE=.\myicons\Refresh.ico
# End Source File
# Begin Source File

SOURCE=".\myicons\Save and Close.ico"
# End Source File
# Begin Source File

SOURCE=.\myicons\View.ico
# End Source File
# End Group
# End Target
# End Project
