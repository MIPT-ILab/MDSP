#!/bin/bash

# A script to do the following things:
# 1) Remove old checked out SVN directories 
# 2) Update the main test script to latest SVN version
#
# * ----------------------------------------------------------------------------
# "THE BEER-WARE LICENSE" (Revision 42):
#  Grigory Rechistov wrote this file. As long as you retain this notice you
#  can do whatever you want with this stuff. If we meet some day, and you think
#  this stuff is worth it, you can buy me a beer in return.
#  ----------------------------------------------------------------------------
# 

ROOTDIR= "$HOME"
TESTDIR="$ROOTDIR/mdsp-tests"
TOKEEP=7 # how many directories to keep

# 1) Remove the old directories
echo "Removing directories"
cd $TESTDIR



# Update the test script
cd $ROOTDIR
echo "Updating the script"
svn export https://mdsp.googlecode.com/svn/trunk/tests/mdsp_test_suite.sh temp.sh
mv mdsp_test_suite.sh old.sh
mv temp.sh mdsp_test_suite.sh
