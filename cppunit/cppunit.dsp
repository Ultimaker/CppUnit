# Microsoft Developer Studio Project File - Name="cppunit" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=cppunit - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "cppunit.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "cppunit.mak" CFG="cppunit - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "cppunit - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "cppunit - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "cppunit - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GR /GX /O2 /I "..\include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\cppunit.lib"

!ELSEIF  "$(CFG)" == "cppunit - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "..\include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\cppunitd.lib"

!ENDIF 

# Begin Target

# Name "cppunit - Win32 Release"
# Name "cppunit - Win32 Debug"
# Begin Source File

SOURCE=.\Exception.cpp
# End Source File
# Begin Source File

SOURCE=..\include\cppunit\Exception.h
# End Source File
# Begin Source File

SOURCE=..\include\cppunit\Test.h
# End Source File
# Begin Source File

SOURCE=..\include\cppunit\TestCaller.h
# End Source File
# Begin Source File

SOURCE=.\TestCase.cpp
# End Source File
# Begin Source File

SOURCE=..\include\cppunit\TestCase.h
# End Source File
# Begin Source File

SOURCE=.\TestFailure.cpp
# End Source File
# Begin Source File

SOURCE=..\include\cppunit\TestFailure.h
# End Source File
# Begin Source File

SOURCE=.\TestRegistry.cpp
# End Source File
# Begin Source File

SOURCE=..\include\cppunit\TestRegistry.h
# End Source File
# Begin Source File

SOURCE=.\TestResult.cpp
# End Source File
# Begin Source File

SOURCE=..\include\cppunit\TestResult.h
# End Source File
# Begin Source File

SOURCE=.\TestSuite.cpp
# End Source File
# Begin Source File

SOURCE=..\include\cppunit\TestSuite.h
# End Source File
# Begin Source File

SOURCE=.\TextTestResult.cpp
# End Source File
# Begin Source File

SOURCE=..\include\cppunit\TextTestResult.h
# End Source File
# End Target
# End Project
