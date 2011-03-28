rem This script use MinGW to build the MDSP.
rem But still we use certain CygWin utilities: SVN

rem Currently MingGW version is disabled - we don't have validated Boost libs version for it.
exit

PATH=C:\mingw\bin\;c:\mingw\mingw32\bin\;c:\mingw\msys\1.0\bin;C:\MinGW\libexec\gcc\mingw32\4.5.0\;C:\cygwin\bin\;c:\buildbot\bin;%PATH%

set HOME=/c/buildbot/

bash mdsp_test_suite.sh mail
