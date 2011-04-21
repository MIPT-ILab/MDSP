#!/bin/bash

# A script to do the following things:
# 1) Update the main test script to latest SVN version
# 2) Remove old checked out SVN directories 
#
# * ----------------------------------------------------------------------------
# "THE BEER-WARE LICENSE" (Revision 42):
#  Grigory Rechistov wrote this file. As long as you retain this notice you
#  can do whatever you want with this stuff. If we meet some day, and you think
#  this stuff is worth it, you can buy me a beer in return.
#  ----------------------------------------------------------------------------
# 

# If run run this script on Windows, make sure that %HOME% is defined! You can use %HOMEPATH% for it.
ROOTDIR="$HOME"
TESTDIR="$ROOTDIR/mdsp-tests"


# 1) Update the test scripts
cd $ROOTDIR
echo "Updating scripts"

# Files common to all platforms
svn export --force https://mdsp.googlecode.com/svn/trunk/tests/mdsp_test_suite.sh
svn export --force https://mdsp.googlecode.com/svn/trunk/tests/test_self_update.sh
if [ `uname -o` == Cygwin ]
then # Windows specific scripts
  svn export --force https://mdsp.googlecode.com/svn/trunk/tests/run_cygwin_tests.cmd
  svn export --force https://mdsp.googlecode.com/svn/trunk/tests/run_mingw_tests.cmd
  svn export --force https://mdsp.googlecode.com/svn/trunk/tests/run_msvs2008_tests.cmd  
fi

# 2) Remove the old directories
LIFETIME=20 #days old for folders to be removed 
echo "Removing directories older than $LIFETIME days"
mkdir -p $TESTDIR
cd $TESTDIR
# Find all directories in current dir that are older than specified amount of
# days, print their names to pipe, and form a command line for `rm -r`
# XXX make sure that your PATH uses find from Cygwin, not Windows `find.exe` !
find . -maxdepth 1 -type d -mtime +$LIFETIME | xargs rm -r 

####
echo "Maintanance finished"
