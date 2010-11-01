#!/bin/bash
 
# This script fetches the latest sources from MDSP SVN, builds them and run several tests.
# It also collects output from these stages and stores it for further analysis.
# After the procedure is over it sends a brief report to MDSP mailing list.
#
# * ----------------------------------------------------------------------------
# "THE BEER-WARE LICENSE" (Revision 42):
#  Grigory Rechistov wrote this file. As long as you retain this notice you
#  can do whatever you want with this stuff. If we meet some day, and you think
#  this stuff is worth it, you can buy me a beer in return.
#  ----------------------------------------------------------------------------
# 

# The buildbot script version
VERSION=2

function mail_results {
    #MAILADDRESS="multimedia-dsp-2010@googlegroups.com"
    MAILADDRESS="ggg_mail@inbox.ru"
    MAILNAME="mdsp.buildbot@inbox.ru"
    MAILPASS=`cat .mdsp_bot_passwd`
    if [ $? != 0 ] 
	then
		echo "No password for mail bot was found!"
	    exit 1
	fi
    MFILE=$1
    MDATE=`date "+%d.%m.%Y %H:%M.%S"`
    SUBJ="MDSP testing results $MDATE"

    sendEmail -f $MAILNAME -t $MAILADDRESS  -xu $MAILNAME  -xp $MAILPASS -u $SUBJ -s smtp.inbox.ru:25 -o message-file=$MFILE -o message-charset=utf-8
    echo " The mail is sent at $MDATE"
}
 
function logprint {
echo $1
echo $1 >> "$LOGFILE"
}
 
DATETIME=`date "+%Y-%m-%d-%H-%M-%S"`
HOST=`uname -a`
DATE=`date`
 
MAKEFLAGS=""
 
LOGFILE="output.txt"
 
logprint "Creating the working directory"
WRK="/home/grigory.rechistov/mdsp-tests/$DATETIME"
mkdir -p "$WRK" || echo "Failed to create the dir!" 1>&2
 
cd "$WRK"
touch "$LOGFILE"
 
logprint "MDSP test suite version $VERSION, started at $DATE"   
logprint "The machine: $HOST" 
 
# DEBUG
#mail_results "$LOGFILE"
#exit 0
 
# Getting the sources
logprint "Fetching sources from SVN..." 
SVNOUTPUT=`svn checkout https://mdsp.googlecode.com/svn/trunk/ mdsp 2>&1`
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
MAKEDIR="mdsp/sources"
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
TESTOUTPUT=`mdsp/sources/bin/test 2>&1`
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
logprint "All tests are OK."  
mail_results "$LOGFILE"
 
#cd "$HOME"
logprint "Bye!"
exit 0
 
 