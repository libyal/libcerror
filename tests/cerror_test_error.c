/*
 * Library error type testing program
 *
 * Copyright (C) 2008-2017, Joachim Metz <joachim.metz@gmail.com>
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
#include <memory.h>
#include <narrow_string.h>
#include <types.h>
#include <system_string.h>
#include <wide_string.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#if defined( HAVE_STDARG_H ) || defined( WINAPI )
#include <stdarg.h>
#elif defined( HAVE_VARARGS_H )
#include <varargs.h>
#else
#error Missing headers stdarg.h and varargs.h
#endif

#if defined( HAVE_GNU_DL_DLSYM )
#define __USE_GNU
#include <dlfcn.h>
#undef __USE_GNU
#endif

#if defined( HAVE_GNU_DL_DLSYM ) && defined( __GNUC__ ) && !defined( __clang__ ) && !defined( __CYGWIN__ )
#define HAVE_CERROR_TEST_FUNCTION_HOOK		1
#endif

#include "cerror_test_libcerror.h"
#include "cerror_test_macros.h"
#include "cerror_test_memory.h"
#include "cerror_test_unused.h"

#include "../libcerror/libcerror_definitions.h"
#include "../libcerror/libcerror_error.h"
#include "../libcerror/libcerror_system.h"

#if defined( HAVE_CERROR_TEST_FUNCTION_HOOK )

static int (*cerror_test_real_vsnprintf)(char *, size_t, const char *, va_list) = NULL;

int cerror_test_vsnprintf_attempts_before_fail                                  = -1;
int cerror_test_vsnprintf_fail_return_value                                     = -1;

#endif /* defined( HAVE_CERROR_TEST_FUNCTION_HOOK ) */

#if defined( HAVE_CERROR_TEST_FUNCTION_HOOK )

/* Custom vsnprintf for testing error cases
 * Returns 0 if successful or an error value otherwise
 */
int vsnprintf(
     char *str,
     size_t size,
     const char *format,
     va_list ap )
{
	int result = 0;

	if( cerror_test_real_vsnprintf == NULL )
	{
		cerror_test_real_vsnprintf = dlsym(
		                              RTLD_NEXT,
		                              "vsnprintf" );
	}
	if( cerror_test_vsnprintf_attempts_before_fail == 0 )
	{
		cerror_test_vsnprintf_attempts_before_fail = -1;

		return( cerror_test_vsnprintf_fail_return_value );
	}
	else if( cerror_test_vsnprintf_attempts_before_fail > 0 )
	{
		cerror_test_vsnprintf_attempts_before_fail--;
	}
	result = cerror_test_real_vsnprintf(
	          str,
	          size,
	          format,
	          ap );

	return( result );
}

#endif /* defined( HAVE_CERROR_TEST_FUNCTION_HOOK ) */

#if defined( __GNUC__ ) && !defined( LIBCERROR_DLL_IMPORT )

/* Tests the libcerror_error_resize function
 * Returns 1 if successful or 0 if not
 */
int cerror_test_error_resize(
     void )
{
	libcerror_error_t *error = NULL;

	/* Test libcerror_error_resize
	 */
	libcerror_error_resize(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC );

	CERROR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	  &error );

	CERROR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test libcerror_error_resize multiple times
	 */
	libcerror_error_resize(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC );

	CERROR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_resize(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC );

	CERROR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_resize(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC );

	CERROR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	  &error );

	CERROR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	libcerror_error_resize(
	 NULL,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC );

#if defined( HAVE_CERROR_TEST_MEMORY )

	/* Test libcerror_error_resize with malloc failing
	 */
	cerror_test_malloc_attempts_before_fail = 0;

	libcerror_error_resize(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC );

	if( cerror_test_malloc_attempts_before_fail != -1 )
	{
		cerror_test_malloc_attempts_before_fail = -1;

		libcerror_error_free(
		  &error );
	}
	else
	{
		CERROR_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test libcerror_error_resize with realloc failing
	 */
	libcerror_error_resize(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC );

	CERROR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	cerror_test_realloc_attempts_before_fail = 0;

	libcerror_error_resize(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC );

	if( cerror_test_realloc_attempts_before_fail != -1 )
	{
		cerror_test_realloc_attempts_before_fail = -1;

		libcerror_error_free(
		  &error );
	}
	else
	{
		CERROR_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );
	}
	cerror_test_realloc_attempts_before_fail = 1;

	libcerror_error_resize(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC );

	if( cerror_test_realloc_attempts_before_fail != -1 )
	{
		cerror_test_realloc_attempts_before_fail = -1;

		libcerror_error_free(
		  &error );
	}
	else
	{
		CERROR_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );
	}
#endif /* defined( HAVE_CERROR_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		  &error );
	}
	return( 0 );
}

/* Tests the libcerror_error_vsnprintf function
 * Returns 1 if successful or 0 if not
 */
int cerror_test_error_vsnprintf(
     void )
{
	va_list argument_list;

	system_character_t *error_string = NULL;
	size_t error_string_size         = 0;

	/* Test cerror_test_error_vsnprintf
	 */
	libcerror_error_vsnprintf(
	 &error_string,
	 &error_string_size,
	 "Test error.",
	 12,
	 argument_list );

	CERROR_TEST_ASSERT_IS_NOT_NULL(
	 "error_string",
	 error_string );

	CERROR_TEST_ASSERT_EQUAL_SIZE(
	 "error_string_size",
	 error_string_size,
	 (size_t) 12 );

	memory_free(
	 error_string );

	error_string = NULL;

	/* Test cerror_test_error_vsnprintf with format string larger than LIBCERROR_MESSAGE_INCREMENT_SIZE
	 */
	libcerror_error_vsnprintf(
	 &error_string,
	 &error_string_size,
	 "The aim of science is not to open the door to infinite wisdom, but to set a limit to infinite error.",
	 101,
	 argument_list );

	CERROR_TEST_ASSERT_IS_NOT_NULL(
	 "error_string",
	 error_string );

	CERROR_TEST_ASSERT_EQUAL_SIZE(
	 "error_string_size",
	 error_string_size,
	 (size_t) 101 );

	memory_free(
	 error_string );

	error_string = NULL;

	/* Test error cases
	 */
	libcerror_error_vsnprintf(
	 NULL,
	 &error_string_size,
	 "Test error.",
	 12,
	 argument_list );

	CERROR_TEST_ASSERT_IS_NULL(
	 "error_string",
	 error_string );

	libcerror_error_vsnprintf(
	 &error_string,
	 NULL,
	 "Test error.",
	 12,
	 argument_list );

	CERROR_TEST_ASSERT_IS_NULL(
	 "error_string",
	 error_string );

	libcerror_error_vsnprintf(
	 &error_string,
	 &error_string_size,
	 NULL,
	 12,
	 argument_list );

	CERROR_TEST_ASSERT_IS_NULL(
	 "error_string",
	 error_string );

#if defined( HAVE_CERROR_TEST_MEMORY )

	/* Test libcerror_error_vsnprintf with realloc failing
	 */
	cerror_test_realloc_attempts_before_fail = 0;

	libcerror_error_vsnprintf(
	 &error_string,
	 &error_string_size,
	 "Test error 1.",
	 14,
	 argument_list );

	if( cerror_test_realloc_attempts_before_fail != -1 )
	{
		cerror_test_realloc_attempts_before_fail = -1;
	}
	else
	{
		CERROR_TEST_ASSERT_IS_NULL(
		 "error_string",
		 error_string );
	}
#endif /* defined( HAVE_CERROR_TEST_MEMORY ) */

#if defined( HAVE_CERROR_TEST_FUNCTION_HOOK )

	/* Test libcerror_error_vsnprintf with vsnprintf returning -1
	 */
	cerror_test_vsnprintf_attempts_before_fail = 0;
	cerror_test_vsnprintf_fail_return_value    = -1;

	libcerror_error_vsnprintf(
	 &error_string,
	 &error_string_size,
	 "Test error 2.",
	 14,
	 argument_list );

	if( cerror_test_vsnprintf_attempts_before_fail != -1 )
	{
		cerror_test_vsnprintf_attempts_before_fail = -1;
	}
	else
	{
		CERROR_TEST_ASSERT_IS_NOT_NULL(
		 "error_string",
		 error_string );

		CERROR_TEST_ASSERT_EQUAL_SIZE(
		 "error_string_size",
		 error_string_size,
		 (size_t) 14 );
	}
	memory_free(
	 error_string );

	error_string = NULL;

	/* Test libcerror_error_vsnprintf with vsnprintf returning
	 * a value larger than LIBCERROR_MESSAGE_MAXIMUM_SIZE
	 */
	cerror_test_vsnprintf_attempts_before_fail = 0;
	cerror_test_vsnprintf_fail_return_value    = 2 * LIBCERROR_MESSAGE_MAXIMUM_SIZE;

	libcerror_error_vsnprintf(
	 &error_string,
	 &error_string_size,
	 "Test error 6.",
	 14,
	 argument_list );

	if( cerror_test_vsnprintf_attempts_before_fail != -1 )
	{
		cerror_test_vsnprintf_attempts_before_fail = -1;
	}
	else
	{
		CERROR_TEST_ASSERT_IS_NOT_NULL(
		 "error_string",
		 error_string );

		CERROR_TEST_ASSERT_EQUAL_SIZE(
		 "error_string_size",
		 error_string_size,
		 (size_t) LIBCERROR_MESSAGE_MAXIMUM_SIZE );
	}
	memory_free(
	 error_string );

	error_string = NULL;

#endif /* defined( HAVE_CERROR_TEST_FUNCTION_HOOK ) */

	return( 1 );

on_error:
	if( error_string != NULL )
	{
		memory_free(
		  error_string );
	}
	return( 0 );
}

/* Tests the libcerror_error_get_system_format_string function
 * Returns 1 if successful or 0 if not
 */
int cerror_test_error_get_system_format_string(
     void )
{
	system_character_t *format_string = NULL;

	/* Test cerror_test_error_get_system_format_string
	 */
	libcerror_error_get_system_format_string(
	 "Test error.",
	 12,
	 &format_string );

	CERROR_TEST_ASSERT_IS_NOT_NULL(
	 "format_string",
	 format_string );

	format_string = NULL;

	/* Test error cases
	 */
	libcerror_error_get_system_format_string(
	 NULL,
	 12,
	 &format_string );

	CERROR_TEST_ASSERT_IS_NULL(
	 "format_string",
	 format_string );

	libcerror_error_get_system_format_string(
	 "Test error.",
	 (size_t) SSIZE_MAX + 1,
	 &format_string );

	CERROR_TEST_ASSERT_IS_NULL(
	 "format_string",
	 format_string );

	libcerror_error_get_system_format_string(
	 "Test error.",
	 12,
	 NULL );

	CERROR_TEST_ASSERT_IS_NULL(
	 "format_string",
	 format_string );

	return( 1 );

on_error:
	return( 0 );
}

#endif /* #if defined( __GNUC__ ) && !defined( LIBCERROR_DLL_IMPORT ) */

/* Tests the libcerror_error_set function
 * Returns 1 if successful or 0 if not
 */
int cerror_test_error_set(
     void )
{
	libcerror_error_t *error = NULL;

	/* Test libcerror_error_set
	 */
	libcerror_error_set(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 "Test error." );

	CERROR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	  &error );

	CERROR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test libcerror_error_set multiple times
	 */
	libcerror_error_set(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 "Test error 1." );

	CERROR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_set(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 "Test error 2." );

	CERROR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_set(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 "Test error 3." );

	CERROR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	  &error );

	CERROR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	libcerror_error_set(
	 NULL,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 "Test error." );

	libcerror_error_set(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 NULL );

	CERROR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#if defined( HAVE_CERROR_TEST_MEMORY )

	/* Test libcerror_error_set with libcerror_error_resize failing
	 */
	cerror_test_malloc_attempts_before_fail = 0;

	libcerror_error_set(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 "Test error." );

	if( cerror_test_malloc_attempts_before_fail != -1 )
	{
		cerror_test_malloc_attempts_before_fail = -1;

		libcerror_error_free(
		  &error );
	}
	else
	{
		CERROR_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test libcerror_error_set with libcerror_error_vsnprintf failing
	 */
	libcerror_error_set(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 "Test error 1." );

	CERROR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	cerror_test_realloc_attempts_before_fail = 2;

	libcerror_error_set(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 "Test error 2." );

	if( cerror_test_realloc_attempts_before_fail != -1 )
	{
		cerror_test_realloc_attempts_before_fail = -1;

		libcerror_error_free(
		  &error );
	}
	else
	{
		CERROR_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );
	}
#endif /* defined( HAVE_CERROR_TEST_MEMORY ) */

	/* TODO test libcerror_error_get_system_format_string failing */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		  &error );
	}
	return( 0 );
}

/* Tests the libcerror_error_matches function
 * Returns 1 if successful or 0 if not
 */
int cerror_test_error_matches(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	libcerror_error_set(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 "Test error." );

	CERROR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	result = libcerror_error_matches(
	          error,
	          LIBCERROR_ERROR_DOMAIN_RUNTIME,
	          LIBCERROR_RUNTIME_ERROR_GENERIC );

	CERROR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	result = libcerror_error_matches(
	          error,
	          LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
	          LIBCERROR_ARGUMENT_ERROR_GENERIC );

	CERROR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	libcerror_error_free(
	  &error );

	CERROR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcerror_error_matches(
	          NULL,
	          LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
	          LIBCERROR_ARGUMENT_ERROR_GENERIC );

	CERROR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		  &error );
	}
	return( 0 );
}

/* TODO: if fmemopen is missing use a temporary file instead? */

#if defined( HAVE_FMEMOPEN ) && ! defined( WINAPI )

/* Tests the libcerror_error_fprint function
 * Returns 1 if successful or 0 if not
 */
int cerror_test_error_fprint(
     void )
{
	char string[ 128 ];

	libcerror_error_t *error = NULL;
	FILE *stream             = NULL;
	int print_count          = 0;
	int result               = 0;

	libcerror_error_set(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 "Test error." );

	CERROR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	stream = fmemopen(
	          string,
	          128,
	          "w+");

	print_count = libcerror_error_fprint(
	               error,
	               stream );

	fclose(
	 stream );

	CERROR_TEST_ASSERT_EQUAL_INT(
	 "print_count",
	 print_count,
	 12 )

	result = narrow_string_compare(
	          string,
	          "Test error.",
	          11 );

	CERROR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	print_count = libcerror_error_fprint(
	               NULL,
	               stream );

	CERROR_TEST_ASSERT_EQUAL_INT(
	 "print_count",
	 print_count,
	 -1 )

	print_count = libcerror_error_fprint(
	               error,
	               NULL );

	CERROR_TEST_ASSERT_EQUAL_INT(
	 "print_count",
	 print_count,
	 -1 )

	libcerror_error_free(
	  &error );

	CERROR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		  &error );
	}
	return( 0 );
}

/* Tests the libcerror_error_backtrace_fprint function
 * Returns 1 if successful or 0 if not
 */
int cerror_test_error_backtrace_fprint(
     void )
{
	char string[ 128 ];

	libcerror_error_t *error = NULL;
	FILE *stream             = NULL;
	int print_count          = 0;
	int result               = 0;

	libcerror_error_set(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 "Test error 1." );

	CERROR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_set(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 "Test error 2." );

	CERROR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	stream = fmemopen(
	          string,
	          128,
	          "w+");

	print_count = libcerror_error_backtrace_fprint(
	               error,
	               stream );

	fclose(
	 stream );

#if defined( WINAPI )
	CERROR_TEST_ASSERT_EQUAL_INT(
	 "print_count",
	 print_count,
	 29 )

	result = narrow_string_compare(
	          string,
	          "Test error 1.\r\nTest error 2.",
	          28 );

#else
	CERROR_TEST_ASSERT_EQUAL_INT(
	 "print_count",
	 print_count,
	 28 )

	result = narrow_string_compare(
	          string,
	          "Test error 1.\nTest error 2.",
	          27 );
#endif

	CERROR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	print_count = libcerror_error_backtrace_fprint(
	               NULL,
	               stream );

	CERROR_TEST_ASSERT_EQUAL_INT(
	 "print_count",
	 print_count,
	 -1 )

	print_count = libcerror_error_backtrace_fprint(
	               error,
	               NULL );

	CERROR_TEST_ASSERT_EQUAL_INT(
	 "print_count",
	 print_count,
	 -1 )

	libcerror_error_free(
	  &error );

	CERROR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		  &error );
	}
	return( 0 );
}

#endif /* defined( HAVE_FMEMOPEN ) && ! defined( WINAPI ) */

/* Tests the libcerror_error_sprint function
 * Returns 1 if successful or 0 if not
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

	CERROR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	print_count = libcerror_error_sprint(
	               error,
	               string,
	               128 );

	CERROR_TEST_ASSERT_EQUAL_INT(
	 "print_count",
	 print_count,
	 12 )

	result = narrow_string_compare(
	          string,
	          "Test error.",
	          11 );

	CERROR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	print_count = libcerror_error_sprint(
	               NULL,
	               string,
	               128 );

	CERROR_TEST_ASSERT_EQUAL_INT(
	 "print_count",
	 print_count,
	 -1 )

	print_count = libcerror_error_sprint(
	               error,
	               NULL,
	               128 );

	CERROR_TEST_ASSERT_EQUAL_INT(
	 "print_count",
	 print_count,
	 -1 )

	print_count = libcerror_error_sprint(
	               error,
	               string,
	               (size_t) SSIZE_MAX + 1 );

	CERROR_TEST_ASSERT_EQUAL_INT(
	 "print_count",
	 print_count,
	 -1 )

	libcerror_error_free(
	  &error );

	CERROR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		  &error );
	}
	return( 0 );
}

/* Tests the libcerror_error_backtrace_sprint function
 * Returns 1 if successful or 0 if not
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

	CERROR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_set(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 "Test error 2." );

	CERROR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	print_count = libcerror_error_backtrace_sprint(
	               error,
	               string,
	               128 );

#if defined( WINAPI )
	CERROR_TEST_ASSERT_EQUAL_INT(
	 "print_count",
	 print_count,
	 29 )

	result = narrow_string_compare(
	          string,
	          "Test error 1.\r\nTest error 2.",
	          28 );

#else
	CERROR_TEST_ASSERT_EQUAL_INT(
	 "print_count",
	 print_count,
	 28 )

	result = narrow_string_compare(
	          string,
	          "Test error 1.\nTest error 2.",
	          27 );
#endif

	CERROR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	print_count = libcerror_error_backtrace_sprint(
	               NULL,
	               string,
	               128 );

	CERROR_TEST_ASSERT_EQUAL_INT(
	 "print_count",
	 print_count,
	 -1 )

	print_count = libcerror_error_backtrace_sprint(
	               error,
	               NULL,
	               128 );

	CERROR_TEST_ASSERT_EQUAL_INT(
	 "print_count",
	 print_count,
	 -1 )

	print_count = libcerror_error_backtrace_sprint(
	               error,
	               string,
	               (size_t) SSIZE_MAX + 1 );

	CERROR_TEST_ASSERT_EQUAL_INT(
	 "print_count",
	 print_count,
	 -1 )

	libcerror_error_free(
	  &error );

	CERROR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		  &error );
	}
	return( 0 );
}

/* Tests the libcerror_system_set_error function
 * Returns 1 if successful or 0 if not
 */
int cerror_test_system_set_error(
     void )
{
	libcerror_error_t *error = NULL;
	uint32_t error_code      = 0;

	/* Test libcerror_system_set_error
	 */
	libcerror_system_set_error(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 error_code,
	 "Test system error." );

	CERROR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	  &error );

	CERROR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test libcerror_system_set_error multiple times
	 */
	libcerror_system_set_error(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 error_code,
	 "Test error 1." );

	CERROR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_system_set_error(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 error_code,
	 "Test error 2." );

	CERROR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_system_set_error(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 error_code,
	 "Test error 3." );

	CERROR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	  &error );

	CERROR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	libcerror_system_set_error(
	 NULL,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 error_code,
	 "Test error." );

	libcerror_system_set_error(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 error_code,
	 NULL );

	CERROR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#if defined( HAVE_CERROR_TEST_MEMORY )

	/* Test libcerror_system_set_error with libcerror_error_resize failing
	 */
	cerror_test_malloc_attempts_before_fail = 0;

	libcerror_system_set_error(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 error_code,
	 "Test error." );

	if( cerror_test_malloc_attempts_before_fail != -1 )
	{
		cerror_test_malloc_attempts_before_fail = -1;

		libcerror_error_free(
		  &error );
	}
	else
	{
		CERROR_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test libcerror_system_set_error with libcerror_error_vsnprintf failing
	 */
	cerror_test_realloc_attempts_before_fail = 2;

	libcerror_system_set_error(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 error_code,
	 "Test error 2." );

	if( cerror_test_realloc_attempts_before_fail != -1 )
	{
		cerror_test_realloc_attempts_before_fail = -1;

		libcerror_error_free(
		  &error );
	}
	else
	{
		CERROR_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );
	}
#endif /* defined( HAVE_CERROR_TEST_MEMORY ) */

	/* TODO test libcerror_error_get_system_format_string failing */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		  &error );
	}
	return( 0 );
}

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc CERROR_TEST_ATTRIBUTE_UNUSED,
     wchar_t * const argv[] CERROR_TEST_ATTRIBUTE_UNUSED )
#else
int main(
     int argc CERROR_TEST_ATTRIBUTE_UNUSED,
     char * const argv[] CERROR_TEST_ATTRIBUTE_UNUSED )
#endif
{
	CERROR_TEST_UNREFERENCED_PARAMETER( argc )
	CERROR_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBCERROR_DLL_IMPORT )

	CERROR_TEST_RUN(
	 "libcerror_error_vsnprintf",
	 cerror_test_error_vsnprintf );

	CERROR_TEST_RUN(
	 "libcerror_error_get_system_format_string",
	 cerror_test_error_get_system_format_string );

#endif /* #if defined( __GNUC__ ) && !defined( LIBCERROR_DLL_IMPORT ) */

	CERROR_TEST_RUN(
	 "libcerror_error_resize",
	 cerror_test_error_resize );

	CERROR_TEST_RUN(
	 "libcerror_error_set",
	 cerror_test_error_set );

	CERROR_TEST_RUN(
	 "libcerror_error_matches",
	 cerror_test_error_matches );

#if defined( HAVE_FMEMOPEN ) && !defined( WINAPI )

	CERROR_TEST_RUN(
	 "libcerror_error_fprint",
	 cerror_test_error_fprint );

	CERROR_TEST_RUN(
	 "libcerror_error_backtrace_fprint",
	 cerror_test_error_backtrace_fprint );

#endif /* defined( HAVE_FMEMOPEN ) && !defined( WINAPI ) */

	CERROR_TEST_RUN(
	 "libcerror_error_sprint",
	 cerror_test_error_sprint );

	CERROR_TEST_RUN(
	 "libcerror_error_backtrace_sprint",
	 cerror_test_error_backtrace_sprint );

#if defined( __GNUC__ ) && !defined( LIBCERROR_DLL_IMPORT )

	/* TODO add tests for libcerror_system_copy_string_from_error_number */

#endif /* #if defined( __GNUC__ ) && !defined( LIBCERROR_DLL_IMPORT ) */

	CERROR_TEST_RUN(
	 "libcerror_system_set_error",
	 cerror_test_system_set_error );

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

