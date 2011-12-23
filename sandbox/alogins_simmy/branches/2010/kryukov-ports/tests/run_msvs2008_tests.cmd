@echo off
rem This script use MS VS 2008 to build and test the MDSP project.

REM ----------------------------------------------------------------------------
REM "THE BEER-WARE LICENSE" (Revision 42):
REM Grigory Rechistov wrote this file. As long as you retain this notice you
REM can do whatever you want with this stuff. If we meet some day, and you think
REM this stuff is worth it, you can buy me a beer in return.
REM ----------------------------------------------------------------------------

set VERSION=W7

rem We still need CygWin for Unix utils, also sendEmail.exe
PATH=c:\cygwin\bin;c:\buildbot\bin;%PATH%

rem get current date and time
for /f %%x in ('C:\cygwin\bin\date.exe +%%Y-%%m-%%d-%%H-%%M-%%S') do set DATE=%%x

rem set host name and type
set HOST=%COMPUTERNAME% %OS% %PROCESSOR_ARCHITECTURE% 

rem make CygWin happy with paths
set CYGWIN=nodosfilewarning %CYGWIN%

rem Set up the MS VS environment. 
if exist "%VS90COMNTOOLS%\vsvars32.bat" (
    rem for user machines
    call "%VS90COMNTOOLS%\vsvars32.bat"
) else (
    rem for buildbot, it does not have the variable defined in batch mode
    call "C:\Program Files\Microsoft Visual Studio 9.0\Common7\Tools\vsvars32.bat"
)

rem Set up buildbot home dir. If not set, take user's home dir 
if "%HOME%" == "" (
	set HOME=%HOMEPATH% 
)

set NOMAIL=0
set BRANCHBUILD=0
set WCTEST=0

rem check command line parameters
if "%1" == "branch" ( 
  set BRANCHBUILD=1
  set BRANCHNAME=%2
  if "%BRANCHNAME%" == "" (
    echo Empty branch name!
    goto :end
  )    
) else if "%1" == "test" (
  echo Test run, the mail won't be sent
  set NOMAIL=1
) else if "%1" == "this" (
	echo Testing working copy
	set NOMAIL=1
	set WCTEST=1
) else if "%1" == "" (
	rem Empty option is the default mode: test HEAD, send mail.
) else (
  echo Unexpected option is given. Valid options: test this branch
  goto :end
)
echo ===============================================================
echo MDSP test suite version %VERSION%, started at %DATE%
echo The machine: %HOST% 
if %BRANCHBUILD% == 1 echo Testing branch %BRANCHNAME%
if %WCTEST% == 1 echo Testing current working directory
echo ===============================================================
set PASS=0 
 
if %WCTEST% == 1 (
  cd ..
  goto :skipfetch
)

echo Creating the working directory
set WRK=%HOME%\mdsp-tests\%DATE%
echo %WRK%
rem change disk to the home, then change directory
%HOMEDRIVE% 
mkdir "%WRK%" 
cd "%WRK%"

rem Getting the sources
echo  Fetching sources from SVN... 

if %BRANCHBUILD% == 1 (
    set URL=https://mdsp.googlecode.com/svn/branches/%BRANCHNAME%
) else (
    set URL=https://mdsp.googlecode.com/svn/trunk/
)
svn checkout %URL% mdsp > nul
if errorlevel 1 goto :svnretry
cd mdsp
goto :skipfetch
:svnretry
svn update mdsp > nul
if errorlevel 1 goto :svnerror
cd mdsp
:skipfetch
rem Build funcsim
devenv sources/funcsim/funcsim.vcproj /useenv /build "Release|Win32" 
if errorlevel 1 (
    goto :blderr 
)

rem Run unit tests
echo Unit tests are not implemented yet
REM mdsp\sources\funcsim\Release\test.exe
REM if errorlevel 1 goto :unittesterror

rem Run funcsim
echo Running funcsim
sources\funcsim\Release\funcsim.exe tests\simple_test.bin
if errorlevel 1 goto :fsimerr

rem Success
set PASS=1
echo ======================================
echo Tests passed!
goto :mailresults
   

:svnerror
echo ======================================
echo SVN error
goto :mailresults
   
:blderr 
echo ======================================
echo Build error
goto :mailresults

:unittesterror
echo ======================================
echo Unit test error
goto :mailresults

:fsimerr:
echo ======================================
echo Funcsim error
goto :mailresults

rem Exit point -------------------------------------------
:mailresults

cd "%HOME%"

if %NOMAIL% == 1 goto :end
if %BRANCHBUILD% == 1 goto :end

set MAILADDRESS="multimedia-dsp-2010@googlegroups.com"
rem set MAILADDRESS="ggg_mail@inbox.ru"
set MAILNAME="mdsp.buildbot@inbox.ru"

rem Read password for mail from file
for /f %%x in (C:\cygwin\bin\cat.exe .mdsp_bot_passwd ) do set MAILPASS=%%x

rem See crontab to understand how testlog.txt is created
set MFILE=testlog.txt

set MDATE=%DATE%

set SUBJ=[FAIL]
if %PASS%==1 set SUBJ=[PASS]   

set SUBJ=%SUBJ% MDSP testing results (%MDATE%)

sendemail.exe -f %MAILNAME% -t %MAILADDRESS%  -xu %MAILNAME%  -xp %MAILPASS% -u %SUBJ% -s smtp.inbox.ru:25 -o message-file=%MFILE% -o message-charset=cp866
echo The mail is sent at %MDATE% to %MAILADDRESS% 1>&2
:end
