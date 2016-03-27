/*
 * Library error type testing program
 *
 * Copyright (C) 2008-2016, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <common.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include <stdio.h>

#include "cerror_test_libcerror.h"
#include "cerror_test_libcstring.h"
#include "cerror_test_unused.h"

/* Tests the libcerror_error_set function
 * Returns 1 if successful, 0 if not or -1 on error
 */
int cerror_test_error_set(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 1;

	/* Test libcerror_error_set once
	 */
	libcerror_error_set(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 "Test error." );

	if( error == NULL )
	{
		fprintf(
		 stderr,
		 "Unable to set error.\n" );

		result = 0;
	}
	fprintf(
	 stdout,
	 "Testing: libcerror_error_set\t\t\t" );

	if( result == 0 )
	{
		fprintf(
		 stdout,
		 "(FAIL)" );

	}
	else
	{
		fprintf(
		 stdout,
		 "(PASS)" );
	}
	fprintf(
	 stdout,
	 "\n" );

	if( error != NULL )
	{
		libcerror_error_free(
		  &error );

		if( error != NULL )
		{
			fprintf(
			 stderr,
			 "Unable to free error.\n" );

			result = -1;
		}
	}
	if( result != 1 )
	{
		return( result );
	}
	/* Test libcerror_error_set multiple times
	 */
	libcerror_error_set(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 "Test error 1." );

	if( error != NULL )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GENERIC,
		 "Test error 2." );
	}
	if( error != NULL )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GENERIC,
		 "Test error 3." );
	}
	if( error == NULL )
	{
		fprintf(
		 stderr,
		 "Unable to set error.\n" );

		result = 0;
	}
	fprintf(
	 stdout,
	 "Testing: libcerror_error_set\t\t\t" );

	if( result == 0 )
	{
		fprintf(
		 stdout,
		 "(FAIL)" );
	}
	else
	{
		fprintf(
		 stdout,
		 "(PASS)" );
	}
	fprintf(
	 stdout,
	 "\n" );

	if( error != NULL )
	{
		libcerror_error_free(
		  &error );

		if( error != NULL )
		{
			fprintf(
			 stderr,
			 "Unable to free error.\n" );

			result = -1;
		}
	}
	if( result != 1 )
	{
		return( result );
	}
	return( 1 );
}

/* Tests the libcerror_error_matches function
 * Returns 1 if successful, 0 if not or -1 on error
 */
int cerror_test_error_matches(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 1;

	libcerror_error_set(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 "Test error." );

	if( error == NULL )
	{
		fprintf(
		 stderr,
		 "Unable to set error.\n" );

		return( -1 );
	}
	result = libcerror_error_matches(
	          error,
	          LIBCERROR_ERROR_DOMAIN_RUNTIME,
	          LIBCERROR_RUNTIME_ERROR_GENERIC );

	fprintf(
	 stdout,
	 "Testing: libcerror_error_matches\t\t" );

	if( result == 0 )
	{
		fprintf(
		 stdout,
		 "(FAIL)" );
	}
	else
	{
		fprintf(
		 stdout,
		 "(PASS)" );
	}
	fprintf(
	 stdout,
	 "\n" );

	if( result != 1 )
	{
		return( 0 );
	}
	result = libcerror_error_matches(
	          error,
	          LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
	          LIBCERROR_ARGUMENT_ERROR_GENERIC );

	fprintf(
	 stdout,
	 "Testing: libcerror_error_matches\t\t" );

	if( result != 0 )
	{
		fprintf(
		 stdout,
		 "(FAIL)" );
	}
	else
	{
		fprintf(
		 stdout,
		 "(PASS)" );
	}
	fprintf(
	 stdout,
	 "\n" );

	if( error != NULL )
	{
		libcerror_error_free(
		  &error );

		if( error != NULL )
		{
			fprintf(
			 stderr,
			 "Unable to free error.\n" );

			result = -1;
		}
	}
	if( result != 0 )
	{
		return( 0 );
	}
	return( 1 );
}

/* TODO: if fmemopen is missing use a temporary file instead? */

#if defined( HAVE_FMEMOPEN ) && ! defined( WINAPI )

/* Tests the libcerror_error_fprint function
 * Returns 1 if successful, 0 if not or -1 on error
 */
int cerror_test_error_fprint(
     void )
{
	char string[ 128 ];

	libcerror_error_t *error = NULL;
	FILE *stream             = NULL;
	int print_count          = 0;
	int result               = 1;

	libcerror_error_set(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 "Test error." );

	if( error == NULL )
	{
		fprintf(
		 stderr,
		 "Unable to set error.\n" );

		return( -1 );
	}
	stream = fmemopen(
	          string,
	          128,
	          "w+");

	print_count = libcerror_error_fprint(
	               error,
	               stream );

	fclose(
	 stream );

	if( print_count != 12 )
	{
		result = 0;
	}
	else if( libcstring_narrow_string_compare(
	          string,
	          "Test error.",
	          11 ) != 0 )
	{
		result = 0;
	}
	fprintf(
	 stdout,
	 "Testing: libcerror_error_fprint\t\t\t" );

	if( result == 0 )
	{
		fprintf(
		 stdout,
		 "(FAIL)" );
	}
	else
	{
		fprintf(
		 stdout,
		 "(PASS)" );
	}
	fprintf(
	 stdout,
	 "\n" );

	if( error != NULL )
	{
		libcerror_error_free(
		  &error );

		if( error != NULL )
		{
			fprintf(
			 stderr,
			 "Unable to free error.\n" );

			result = -1;
		}
	}
	if( result != 1 )
	{
		return( 0 );
	}
	return( 1 );
}

/* Tests the libcerror_error_backtrace_fprint function
 * Returns 1 if successful, 0 if not or -1 on error
 */
int cerror_test_error_backtrace_fprint(
     void )
{
	char string[ 128 ];

	libcerror_error_t *error = NULL;
	FILE *stream             = NULL;
	int print_count          = 0;
	int result               = 1;

	libcerror_error_set(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 "Test error 1." );

	if( error == NULL )
	{
		fprintf(
		 stderr,
		 "Unable to set error.\n" );

		return( -1 );
	}
	libcerror_error_set(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 "Test error 2." );

	if( error == NULL )
	{
		fprintf(
		 stderr,
		 "Unable to set error.\n" );

		return( -1 );
	}
	stream = fmemopen(
	          string,
	          128,
	          "w+");

	print_count = libcerror_error_backtrace_fprint(
	               error,
	               stream );

	fclose(
	 stream );

	if( print_count != 28 )
	{
		result = 0;
	}
	else if( libcstring_narrow_string_compare(
	          string,
	          "Test error 1.\nTest error 2.",
	          27 ) != 0 )
	{
		result = 0;
	}
	fprintf(
	 stdout,
	 "Testing: libcerror_error_backtrace_fprint\t" );

	if( result == 0 )
	{
		fprintf(
		 stdout,
		 "(FAIL)" );
	}
	else
	{
		fprintf(
		 stdout,
		 "(PASS)" );
	}
	fprintf(
	 stdout,
	 "\n" );

	if( error != NULL )
	{
		libcerror_error_free(
		  &error );

		if( error != NULL )
		{
			fprintf(
			 stderr,
			 "Unable to free error.\n" );

			result = -1;
		}
	}
	if( result != 1 )
	{
		return( 0 );
	}
	return( 1 );
}

#endif /* defined( HAVE_FMEMOPEN ) && ! defined( WINAPI ) */

/* Tests the libcerror_error_sprint function
 * Returns 1 if successful, 0 if not or -1 on error
 */
int cerror_test_error_sprint(
     void )
{
	char string[ 128 ];

	libcerror_error_t *error = NULL;
	int print_count          = 0;
	int result               = 1;

	libcerror_error_set(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 "Test error." );

	if( error == NULL )
	{
		fprintf(
		 stderr,
		 "Unable to set error.\n" );

		return( -1 );
	}
	print_count = libcerror_error_sprint(
	               error,
	               string,
	               128 );

	if( print_count != 12 )
	{
		result = 0;
	}
	else if( libcstring_narrow_string_compare(
	          string,
	          "Test error.",
	          11 ) != 0 )
	{
		result = 0;
	}
	fprintf(
	 stdout,
	 "Testing: libcerror_error_sprint\t\t\t" );

	if( result == 0 )
	{
		fprintf(
		 stdout,
		 "(FAIL)" );
	}
	else
	{
		fprintf(
		 stdout,
		 "(PASS)" );
	}
	fprintf(
	 stdout,
	 "\n" );

	if( error != NULL )
	{
		libcerror_error_free(
		  &error );

		if( error != NULL )
		{
			fprintf(
			 stderr,
			 "Unable to free error.\n" );

			result = -1;
		}
	}
	if( result != 1 )
	{
		return( 0 );
	}
	return( 1 );
}

/* Tests the libcerror_error_backtrace_sprint function
 * Returns 1 if successful, 0 if not or -1 on error
 */
int cerror_test_error_backtrace_sprint(
     void )
{
	char string[ 128 ];

	libcerror_error_t *error = NULL;
	int print_count          = 0;
	int result               = 1;

	libcerror_error_set(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 "Test error 1." );

	if( error == NULL )
	{
		fprintf(
		 stderr,
		 "Unable to set error.\n" );

		return( -1 );
	}
	libcerror_error_set(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 "Test error 2." );

	if( error == NULL )
	{
		fprintf(
		 stderr,
		 "Unable to set error.\n" );

		return( -1 );
	}
	print_count = libcerror_error_backtrace_sprint(
	               error,
	               string,
	               128 );

	if( print_count != 28 )
	{
		result = 0;
	}
	else if( libcstring_narrow_string_compare(
	          string,
	          "Test error 1.\nTest error 2.",
	          27 ) != 0 )
	{
		result = 0;
	}
	fprintf(
	 stdout,
	 "Testing: libcerror_error_backtrace_sprint\t" );

	if( result == 0 )
	{
		fprintf(
		 stdout,
		 "(FAIL)" );
	}
	else
	{
		fprintf(
		 stdout,
		 "(PASS)" );
	}
	fprintf(
	 stdout,
	 "\n" );

	if( error != NULL )
	{
		libcerror_error_free(
		  &error );

		if( error != NULL )
		{
			fprintf(
			 stderr,
			 "Unable to free error.\n" );

			result = -1;
		}
	}
	if( result != 1 )
	{
		return( 0 );
	}
	return( 1 );
}

/* Tests the libcerror_system_set_error function
 * Returns 1 if successful, 0 if not or -1 on error
 */
int cerror_test_system_set_error(
     void )
{
	libcerror_error_t *error = NULL;
	uint32_t error_code      = 0;
	int result               = 1;

	libcerror_system_set_error(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 error_code,
	 "Test system error." );

	if( error == NULL )
	{
		fprintf(
		 stderr,
		 "Unable to set system error.\n" );

		result = 0;
	}
	fprintf(
	 stdout,
	 "Testing: libcerror_system_set_error\t\t" );

	if( result == 0 )
	{
		fprintf(
		 stdout,
		 "(FAIL)" );

	}
	else
	{
		fprintf(
		 stdout,
		 "(PASS)" );
	}
	fprintf(
	 stdout,
	 "\n" );

	if( error != NULL )
	{
		libcerror_error_free(
		  &error );

		if( error != NULL )
		{
			fprintf(
			 stderr,
			 "Unable to free error.\n" );

			result = -1;
		}
	}
	if( result != 1 )
	{
		return( result );
	}
	return( 1 );
}

/* The main program
 */
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
int wmain( int argc, wchar_t * const argv[] CERROR_TEST_ATTRIBUTE_UNUSED )
#else
int main( int argc, char * const argv[] CERROR_TEST_ATTRIBUTE_UNUSED )
#endif
{
	CERROR_TEST_UNREFERENCED_PARAMETER( argv )

	if( argc != 1 )
	{
		fprintf(
		 stderr,
		 "Unsupported number of arguments.\n" );

		return( EXIT_FAILURE );
	}
	if( cerror_test_error_set() != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test error set.\n" );

		return( EXIT_FAILURE );
	}
	if( cerror_test_error_matches() != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test error matches.\n" );

		return( EXIT_FAILURE );
	}
#if defined( HAVE_FMEMOPEN ) && ! defined( WINAPI )
	if( cerror_test_error_fprint() != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test error fprint.\n" );

		return( EXIT_FAILURE );
	}
	if( cerror_test_error_backtrace_fprint() != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test error backtrace fprint.\n" );

		return( EXIT_FAILURE );
	}
#endif /* defined( HAVE_FMEMOPEN ) && ! defined( WINAPI ) */

	if( cerror_test_error_sprint() != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test error sprint.\n" );

		return( EXIT_FAILURE );
	}
	if( cerror_test_error_backtrace_sprint() != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test error backtrace sprint.\n" );

		return( EXIT_FAILURE );
	}
	if( cerror_test_system_set_error() != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test system set error.\n" );

		return( EXIT_FAILURE );
	}
	return( EXIT_SUCCESS );
}

