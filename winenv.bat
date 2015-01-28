@echo off

if defined COMMON_ACTIVE (
   goto END
)

if "%1" == "--help" (
   echo common.bat [ARCHSUFFIX]
   echo "ARCHSUFFIX: win32, win32opt, amdwin64, amdwin64opt, ia64win, vista (default), vistaopt, zackel, zackelopt, angus, angusopt, yoroo, yorooopt, berrenda, berrendaopt, tamarau, tamarauopt, mingw, mingwopt"
   pause
   goto END
)

if "%1" == "" (
  if not defined ARCHSUFFIX% set ARCHSUFFIX=vista
) else (
  set ARCHSUFFIX=%1
)

if not defined COVISE_BRANCH (
   set COVISE_BRANCH=HLRS
)

if not defined EXTERNLIBS (
   if not defined EXTERNLIBSROOT (
      echo EXTERNLIBS and EXTERNLIBSROOT are not set
      pause
      goto END
   ) else (
      set EXTERNLIBS=%EXTERNLIBSROOT%\%ARCHSUFFIX%
   )
)


if defined COVISEDIR goto COVISEDIR_IS_OK
REM to avoid problems with closing rounded bracket in IF-clause
REM work with GOTOs to set missing COVISEDIR

REM current working path looks like COVISEDIR
if exist "%CD%"\common.bat echo setting COVISEDIR to %CD%
if exist "%CD%"\common.bat set COVISEDIR=%CD%
if exist "%CD%"\common.bat goto COVISEDIR_IS_OK

REM see, if path where this script is called looks like COVISEDIR
REM accept path if common-base.bat seems to be at the right place
if exist "%~dp0"\bin\common-base.bat echo setting COVISEDIR to %~dp0
if exist "%~dp0"\bin\common-base.bat set COVISEDIR=%~dp0
if exist "%~dp0"\bin\common-base.bat goto COVISEDIR_IS_OK

REM else no suitable COVISEDIR found; abort
echo COVISEDIR is not set
pause
goto END

:COVISEDIR_IS_OK

if defined CADCV_DIR (
   cd /d %CADCV_DIR%/qmakehelp
   call qmakehelp.bat
   cd /d %COVISEDIR%
)

if not defined COFRAMEWORKDIR (
   set COFRAMEWORKDIR=%COVISEDIR%
)

if /I "%ARCHSUFFIX%" EQU "amdwin64opt" goto LABEL_SETENVIRONMENT
if /I "%ARCHSUFFIX%" EQU "amdwin64" goto LABEL_SETENVIRONMENT
if /I "%ARCHSUFFIX%" EQU "ia64win"  goto LABEL_SETENVIRONMENT
if /I "%ARCHSUFFIX%" EQU "win32opt" goto LABEL_SETENVIRONMENT
if /I "%ARCHSUFFIX%" EQU "win32"    goto LABEL_SETENVIRONMENT
if /I "%ARCHSUFFIX%" EQU "vistaopt" goto LABEL_SETENVIRONMENT
if /I "%ARCHSUFFIX%" EQU "vista"    goto LABEL_SETENVIRONMENT
if /I "%ARCHSUFFIX%" EQU "zackelopt" goto LABEL_SETENVIRONMENT
if /I "%ARCHSUFFIX%" EQU "zackel"    goto LABEL_SETENVIRONMENT
if /I "%ARCHSUFFIX%" EQU "angusopt" goto LABEL_SETENVIRONMENT
if /I "%ARCHSUFFIX%" EQU "angus"    goto LABEL_SETENVIRONMENT
if /I "%ARCHSUFFIX%" EQU "yorooopt" goto LABEL_SETENVIRONMENT
if /I "%ARCHSUFFIX%" EQU "yoroo"    goto LABEL_SETENVIRONMENT
if /I "%ARCHSUFFIX%" EQU "berrendaopt" goto LABEL_SETENVIRONMENT
if /I "%ARCHSUFFIX%" EQU "berrenda"    goto LABEL_SETENVIRONMENT
if /I "%ARCHSUFFIX%" EQU "tamarauopt" goto LABEL_SETENVIRONMENT
if /I "%ARCHSUFFIX%" EQU "tamarau"    goto LABEL_SETENVIRONMENT
if /I "%ARCHSUFFIX%" EQU "mingwopt" goto LABEL_SETENVIRONMENT
if /I "%ARCHSUFFIX%" EQU "mingw"    goto LABEL_SETENVIRONMENT
echo ARCHSUFFIX %ARCHSUFFIX% is not supported!
echo common.bat [ARCHSUFFIX]
echo "ARCHSUFFIX: win32, win32opt, amdwin64, amdwin64opt, ia64win, vista (default), vistaopt, zackel, zackelopt, angus, angusopt, yoroo, yorooopt, berrenda, berrendaopt, tamarau, tamarauopt, mingw, mingwopt"
pause
goto END



:LABEL_SETENVIRONMENT
echo Environment settings for ARCHSUFFIX %ARCHSUFFIX%

set BASEARCHSUFFIX=%ARCHSUFFIX:opt=%

cd /d %COVISEDIR%
         
if exist "%COVISEDIR%"\mysetenv.bat (
   call "%COVISEDIR%"\mysetenv.bat
   echo mysetenv.bat was included
)


rem   start microsoft development environment
rem   =======================================
rem
rem If VS2003 or VS2005 was installed in a non-standard location you have to set VCVARS32 !
rem 

set PROGFILES=%ProgramFiles%
if defined ProgramFiles(x86)  set PROGFILES=%ProgramFiles(x86)%
rem echo  %VS100COMNTOOLS%
cd

if "%ARCHSUFFIX:~0,5%" EQU "win32" (
    call "%PROGFILES%"\"Microsoft Visual Studio .NET 2003"\Vc7\bin\vcvars32.bat
) else if "%ARCHSUFFIX:~0,5%" EQU "vista" (
    call "%VS80COMNTOOLS%"\..\..\Vc\bin\vcvars32.bat"
) else if "%ARCHSUFFIX:~0,6%" EQU "zackel" (
    cd /d "%VS90COMNTOOLS%"\..\..\vc
	call vcvarsall.bat x86
    cd /d "%COVISEDIR%"\
) else if "%ARCHSUFFIX:~0,5%" EQU "yoroo" (
    cd /d "%VS100COMNTOOLS%"\..\..\vc
	call vcvarsall.bat x86
    cd /d "%COVISEDIR%"\
) else if "%ARCHSUFFIX:~0,7%" EQU "tamarau" (
    cd /d "%VS110COMNTOOLS%"\..\..\vc
	call vcvarsall.bat x64
    cd /d "%COVISEDIR%"\
) else if "%ARCHSUFFIX:~0,8%" EQU "berrenda" (
if defined VS110COMNTOOLS  (
    cd /d "%VS110COMNTOOLS%"\..\..\vc
	call vcvarsall.bat x64
) else (
    cd /d "%VS100COMNTOOLS%"\..\..\vc
	call vcvarsall.bat x64
	)
    cd /d "%COVISEDIR%"\
) else if "%ARCHSUFFIX:~0,5%" EQU "angus" (
    cd /d "%VS90COMNTOOLS%"\..\..\vc
    call vcvarsall.bat x64
    cd /d "%COVISEDIR%"\
) else if "%ARCHSUFFIX:~0,8%" EQU "amdwin64"   (
    cd /d "%VS80COMNTOOLS%"\..\..\vc
    call vcvarsall.bat x64
    cd /d "%COVISEDIR%"\
) else if defined VCVARS32 (
    call "%VCVARS32%"
)

if not defined QT_HOME ( 
   REM QT_HOME is not set... check QTDIR
   IF not defined QTDIR (
     REM QTDIR is not set ! Try in EXTERNLIBS
     set "QT_HOME=%EXTERNLIBS%\qt5"
     set "QT_SHAREDHOME=%EXTERNLIBS%\qt5"
     set "QTDIR=%EXTERNLIBS%\qt5"
     set "QT_INCPATH=%EXTERNLIBS%\qt5\include"
     set "QT_LIBPATH=%EXTERNLIBS%\qt5\lib"
	 set "PATH=%EXTERNLIBS%\qt5\bin;%EXTERNLIBS%\qt5\lib;%PATH%"
	 set "QT_QPA_PLATFORM_PLUGIN_PATH=%EXTERNLIBS%\qt5\plugins\platforms"   rem tested for qt5 on win7, visual studio 2010
   ) ELSE (
     REM QTDIR is set so try to use it !
     REM Do a simple sanity-check...
     IF NOT EXIST "%QTDIR%\.qmake.cache" (
       echo *** WARNING: .qmake.cache NOT found !
       echo ***          Check QTDIR or simply do NOT set QT_HOME and QTDIR to use the version from EXTERNLIBS!
       pause
     )
     REM Set QT_HOME according to QTDIR. If User ignores any warnings before he will find himself in a world of pain! 
     set "QT_HOME=%QTDIR%"
     set "QT_SHAREDHOME=%QTDIR%"
     set "QT_INCPATH=%QTDIR%\include"
     set "QT_LIBPATH=%QTDIR%\lib"
	 set "PATH=%QTDIR%\bin;%QTDIR%\lib;%PATH%"
	 set "QT_QPA_PLATFORM_PLUGIN_PATH=%QTDIR%\plugins\platforms"  
   )
)

set FRAMEWORK=covise
set QMAKECOVISEDIR=%COVISEDIR%
set LOGNAME=covise
set PATH=%PATH%;%COVISEDIR%\%ARCHSUFFIX%\bin;%COVISEDIR%\%ARCHSUFFIX%\lib;%COVISEDIR%\bin;%COVISEDIR%\%ARCHSUFFIX%\bin\Renderer;%COVISEDIR%\%ARCHSUFFIX%\lib\opencover\plugins


if not defined COVISEDESTDIR   set COVISEDESTDIR=%COVISEDIR%
if not defined VV_SHADER_PATH  set VV_SHADER_PATH=%COVISEDIR%\src\3rdparty\deskvox\virvo\shader
if not defined COVISE_PATH     set COVISE_PATH=%COVISEDIR%


set RM=rmdir /S /Q
if "%ARCHSUFFIX%" EQU "vista"  set COVISE_DEVELOPMENT=YES
if "%ARCHSUFFIX%" EQU "zackel"  set COVISE_DEVELOPMENT=YES
if "%ARCHSUFFIX%" EQU "angus"  set COVISE_DEVELOPMENT=YES
if "%ARCHSUFFIX%" EQU "yoroo"  set COVISE_DEVELOPMENT=YES
if "%ARCHSUFFIX%" EQU "berrenda"  set COVISE_DEVELOPMENT=YES
if "%ARCHSUFFIX%" EQU "tamarau"  set COVISE_DEVELOPMENT=YES
if "%ARCHSUFFIX%" EQU "mingw"  set COVISE_DEVELOPMENT=YES

set COMMON_ACTIVE=1
:END