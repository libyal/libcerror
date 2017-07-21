#!/bin/bash
# Script that runs the tests on Windows
#
# Version: 20170721

EXIT_SUCCESS=0;
EXIT_FAILURE=1;

make check

RESULT=$?

if test -f tests/test-suite.log;
then
	cat tests/test-suite.log;
fi

exit ${RESULT};

