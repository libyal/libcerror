#!/bin/sh
# Script to run tests on GitHub actions
#
# Version: 20201121

if test -f ./pycerror/.libs/pycerror.so;
then
	install_name_tool -change /usr/local/lib/libcerror.1.dylib ${PWD}/libcerror/.libs/libcerror.1.dylib ./pycerror/.libs/pycerror.so;
fi

make check CHECK_WITH_STDERR=1;
RESULT=$?;

if test ${RESULT} -ne 0 && test -f tests/test-suite.log;
then
	cat tests/test-suite.log;
fi
exit ${RESULT};

