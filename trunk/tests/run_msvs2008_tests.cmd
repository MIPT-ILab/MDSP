@echo off
rem This script use MS VS 2008 to build and test the MDSP project.

REM ----------------------------------------------------------------------------
REM "THE BEER-WARE LICENSE" (Revision 42):
REM Grigory Rechistov wrote this file. As long as you retain this notice you
REM can do whatever you want with this stuff. If we meet some day, and you think
REM this stuff is worth it, you can buy me a beer in return.
REM ----------------------------------------------------------------------------


set VERSION=W2
rem We still need CygWin for Unix utils, also sendEmail.exe
PATH=c:\cygwin\bin;c:\buildbot\bin;%PATH%

rem current date and time
for /f %%x in ('C:\cygwin\bin\date.exe +%%Y-%%m-%%d-%%H-%%M-%%S') do set DATE=%%x

rem set host name and type
REM for /f %%x in ('c:\cygwin\bin\hostname.exe') do set HOST=%%x
set HOST=%COMPUTERNAME% %OS% %PROCESSOR_ARCHITECTURE% 

rem make CygWin happy with paths
set CYGWIN=nodosfilewarning %CYGWIN%

rem Set up the MS VS environment. 
rem call twice in case some users have different setup
call "C:\Program Files\Microsoft Visual Studio 9.0\Common7\Tools\vsvars32.bat"
call "%VS90COMNTOOLS%\vsvars32.bat"

set HOMEPATH="c:\buildbot\mdsp-tests\%DATE%"

echo Creating the working directory
set WRK="%HOMEPATH%%

REM rm -rf %WRK%
mkdir %WRK% 
 
cd %WRK%

REM set LOGFILE=output.txt
REM touch %LOGFILE%

echo ===============================================================
echo MDSP test suite version %VERSION%, started at %DATE%
echo The machine: %HOST% 
echo ===============================================================
set PASS=0 
 
rem Getting the sources
echo  Fetching sources from SVN... 

set URL=https://mdsp.googlecode.com/svn/trunk/
svn checkout %URL% mdsp 2>&1

rem Build funcsim
devenv mdsp/sources/funcsim/funcsim.vcproj /useenv /build "Release|Win32" 
if errorlevel 1 goto :builderror

rem Run unit tests
echo Unit tests are not implemented yet
REM mdsp\sources\funcsim\Release\test.exe
REM if errorlevel 1 goto :unittesterror

rem Run funcsim
echo Running funcsim
mdsp\sources\funcsim\Release\test.exe mdsp\tests\simple_test.bin
if errorlevel 1 goto :funcsimerror

rem Success
set PASS=1
echo =====================================================
echo Tests passed!
goto :mailresults
   
 
:builderror
echo =====================================================
echo Build error
goto :mailresults

:unittesterror
echo =====================================================
echo Unit test error
goto :mailresults

:funcsimerror:
echo =====================================================
echo Funcsim error
goto :mailresults

rem Exit point -------------------------------------------
:mailresults

cd C:\buildbot
set MAILADDRESS="multimedia-dsp-2010@googlegroups.com"
rem set MAILADDRESS="ggg_mail@inbox.ru"
set MAILNAME="mdsp.buildbot@inbox.ru"

rem Read password for mail
for /f %%x in (C:\cygwin\bin\cat.exe .mdsp_bot_passwd ) do set MAILPASS=%%x

rem See crontab to understand how testlog.txt is created
set MFILE=testlog.txt

set MDATE=%DATE%

set SUBJ=[FAIL]
if %PASS%==1 set SUBJ=[PASS]   

set SUBJ=%SUBJ% MDSP testing results (%MDATE%)

sendemail.exe -f %MAILNAME% -t %MAILADDRESS%  -xu %MAILNAME%  -xp %MAILPASS% -u %SUBJ% -s smtp.inbox.ru:25 -o message-file=%MFILE% -o message-charset=cp866
echo The mail is sent at %MDATE% to %MAILADDRESS% 1>&2

