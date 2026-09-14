#!/bin/sh
# Script to run tests
#
# Version: 20260714

if [ -f "${PWD}/libcerror/.libs/libcerror.1.dylib" ] && [ -f ./pycerror/.libs/pycerror.so ]
then
    install_name_tool -change /usr/local/lib/libcerror.1.dylib "${PWD}/libcerror/.libs/libcerror.1.dylib" ./pycerror/.libs/pycerror.so
fi

make check-build > /dev/null

# shellcheck disable=SC2068
make check $@
RESULT=$?

if [ ${RESULT} -ne 0 ]
then
    find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}

