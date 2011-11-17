#!/bin/bash
 
# This script simply compile and test working copy of the project.
#
# * ----------------------------------------------------------------------------
# "THE BEER-WARE LICENSE" (Revision 42):
#  Grigory Rechistov wrote this file. As long as you retain this notice you
#  can do whatever you want with this stuff. If we meet some day, and you think
#  this stuff is worth it, you can buy me a beer in return.
#  
#  I may buy a beer to Grigory. I've wrote this script basing on Grigori's.
#  Mikhail Churikov
#  ----------------------------------------------------------------------------
# 

if [ $# = 1 ]
then
    INPUT=$1
else 
    INPUT=0
fi

echo Cleaning...
make -C .. clean
if [ $? != 0 ]
then
    echo 'Warning: clean failed'
fi

echo 'Building test...'
MAKEOUTPUT=`make -C .. test`
MAKEERRORCODE=$?
if [ $MAKEERRORCODE != 0 ] # Failure
then
    echo Failed with code $MAKEERRORCODE.The output is:
    echo 'No more actions were done'
    exit 1
else # Success
    echo OK.  
    # Check if there were any warnings
    if [[ $MAKEOUTPUT  == *warning\:* ]]
    then
      echo There were warnings during build
      echo $MAKEOUTPUT
    fi
fi
echo 'Running test'

if [ $INPUT = "print_output" ];
then
    ./../Release/test
else
    TESTOUTPUT=`./../Release/test`
fi
TESTERRORCODE=$?
if [ $TESTERRORCODE != 0 ] # Failure
then
    echo Failed with code $TESTERRORCODE. The output is:
    echo $TESTOUTPUT  
    echo 'No more actions were done ' 
    exit 1
else # Success
    echo OK.  
fi
