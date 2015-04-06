/*
 * Library error type testing program
 *
 * Copyright (C) 2008-2015, Joachim Metz <joachim.metz@gmail.com>
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
	 "Testing set\t" );

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
	 "Testing set multiple times\t" );

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
	 "Testing matches\t" );

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
	 "Testing not matches\t" );

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

	if( result != 0 )
	{
		return( 0 );
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
		 "Unable to test set.\n" );

		return( EXIT_FAILURE );
	}
	if( cerror_test_error_matches() != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test matches.\n" );

		return( EXIT_FAILURE );
	}
	/* TODO: add tests for:
	 * libcerror_error_fprint
	 * libcerror_error_sprint
	 * libcerror_error_backtrace_fprint
	 * libcerror_error_backtrace_sprint
	 */
	return( EXIT_SUCCESS );
}

