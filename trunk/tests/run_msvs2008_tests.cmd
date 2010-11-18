@echo off
rem This script use MS VS 2008 to build the MDSP.
echo ===========================================
echo This is experimental script!
echo 
echo ===========================================

rem We still need CygWin for Unix utils
PATH=c:\cygwin\bin;c:\buildbot\bin;%PATH%

rem make CygWin happy with paths
set CYGWIN=nodosfilewarning %CYGWIN%

rem Set up the VS environment. 
call "C:\Program Files\Microsoft Visual Studio 9.0\VC\vcvarsall.bat" x86

set HOMEPATH=c:\buildbot\mdsp-tests\vc2008
set LOGFILE=output.txt

rem TODO set DATETIME properly
rem set DATETIME=date-time

echo Creating the working directory
set WRK="%HOMEPATH%%

rm -rf %WRK%
mkdir %WRK% 
 
cd %WRK%
touch %LOGFILE%
 
rem logprint "MDSP test suite version $VERSION, started at $DATE"   
rem logprint "The machine: $HOST" 
 
rem Getting the sources
echo  "Fetching sources from SVN..." 

set URL=https://mdsp.googlecode.com/svn/trunk/
svn checkout %URL% mdsp 2>&1

rem Build funcsim
devenv mdsp/sources/funcsim/funcsim.vcproj /build "Release|Win32" /out %LOGFILE% 

echo That's all for now

goto :endbuild

rem the stuff below is not implemented yet
rem --------------------------------------------------------------------------------
if [ -n "$BRANCHNAME" ]
then
    URL="https://mdsp.googlecode.com/svn/branches/$BRANCHNAME"
else
    URL="https://mdsp.googlecode.com/svn/trunk/"
fi
SVNOUTPUT=`svn checkout $URL mdsp 2>&1`
SVNERRORCODE=$?
if [ $SVNERRORCODE != 0 ] # Failure
then
    logprint "Failed with code "$SVNERRORCODE". The output is:"  
    logprint "$SVNOUTPUT"  
    logprint "No more actions were done"  
    mail_results "$LOGFILE"
    # TODO bail out
    exit 1
else # Success
    logprint "OK."  
  # Get svn revision
    REVISION=`svnversion mdsp`
    logprint "SVN Revision is $REVISION"
fi
 
# Let' build the code
MAKEDIR="mdsp"
logprint "Building..."  
MAKEOUTPUT=`make -C $MAKEDIR $MAKEFLAGS 2>&1`
MAKEERRORCODE=$?
if [ $MAKEERRORCODE != 0 ] # Failure
then
    logprint "Failed with code $MAKEERRORCODE.The output is:"  
    logprint "$MAKEOUTPUT"  
    logprint "No more actions were done"   
    mail_results "$LOGFILE"
 
    # TODO bail out
    exit 1
else # Success
    logprint "OK."  
    # Check if there were any warnings
    if [[ $MAKEOUTPUT  == *warning\:* ]]
    then
      logprint "There were warnings during build"
      logprint "$MAKEOUTPUT"
    fi
fi
 
# Let' run the test suite included in MDSP
logprint "Running unit tests..."   
TESTOUTPUT=`mdsp/Release/test 2>&1`
TESTERRORCODE=$?
if [ $TESTERRORCODE != 0 ] # Failure
then
    logprint "Failed with code $TESTERRORCODE. The output is:"  
    logprint "$TESTOUTPUT"  
    logprint "No more actions were done"  
    mail_results "$LOGFILE"
    # TODO bail out
    exit 1
else # Success
    logprint "OK."  
fi
 
# Let' run the additional tests
logprint "Running product tests..."  
 
# TODO 
# For each of lines specified
# run the line, get its output
# check error code 
# add output to report
 
logprint "Not implemented yet"  
 
# Happily finish
PASS=1
logprint "All tests are OK."  
ENDDATE=`date "+%Y-%m-%d-%H-%M-%S"`
logprint "Finished at $ENDDATE"
mail_results "$LOGFILE"
 
#cd "$HOME"
logprint "Bye!"
exit 0
 
 


rem Exit point
:endbuild
