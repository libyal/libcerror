#!/bin/bash
#
# Library error type testing script
#
# Copyright (C) 2008-2016, Joachim Metz <joachim.metz@gmail.com>
#
# Refer to AUTHORS for acknowledgements.
#
# This software is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this software.  If not, see <http://www.gnu.org/licenses/>.
#

EXIT_SUCCESS=0;
EXIT_FAILURE=1;
EXIT_IGNORE=77;

test_error()
{ 
	echo "Testing error type";

	./${CERROR_TEST_ERROR};

	RESULT=$?;

	echo "";

	return ${RESULT};
}

CERROR_TEST_ERROR="cerror_test_error";

if ! test -x ${CERROR_TEST_ERROR};
then
	CERROR_TEST_ERROR="cerror_test_error.exe";
fi

if ! test -x ${CERROR_TEST_ERROR};
then
	echo "Missing executable: ${CERROR_TEST_ERROR}";

	exit ${EXIT_FAILURE};
fi

if ! test_error;
then
	exit ${EXIT_FAILURE};
fi

exit ${EXIT_SUCCESS};

