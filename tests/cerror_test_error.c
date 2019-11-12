/*
 * Library error type testing program
 *
 * Copyright (C) 2008-2019, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <file_stream.h>
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

#if defined( HAVE_CERROR_TEST_FUNCTION_HOOK )

#if defined( OPTIMIZATION_DISABLED )
static int (*cerror_test_real_fprintf)(FILE *, const char *, ...)               = NULL;

int cerror_test_fprintf_attempts_before_fail                                    = -1;
#endif

static int (*cerror_test_real_vsnprintf)(char *, size_t, const char *, va_list) = NULL;

int cerror_test_vsnprintf_attempts_before_fail                                  = -1;
int cerror_test_vsnprintf_fail_return_value                                     = -1;

#endif /* defined( HAVE_CERROR_TEST_FUNCTION_HOOK ) */

#if defined( HAVE_CERROR_TEST_FUNCTION_HOOK )

#if defined( OPTIMIZATION_DISABLED )

/* Custom fprintf for testing error cases
 * Returns the number of characters printed if successful or an error value otherwise
 */
int fprintf(
     FILE *stream,
     const char *format,
     ... )
{
	va_list arguments;

	int result = 0;

	if( cerror_test_real_fprintf == NULL )
	{
		cerror_test_real_fprintf = dlsym(
		                            RTLD_NEXT,
		                            "fprintf" );
	}
	if( cerror_test_fprintf_attempts_before_fail == 0 )
	{
		cerror_test_fprintf_attempts_before_fail = -1;

		return( -1 );
	}
	else if( cerror_test_fprintf_attempts_before_fail > 0 )
	{
		cerror_test_fprintf_attempts_before_fail--;
	}
	va_start(
	 arguments,
	 format );

	result = vfprintf(
	          stream,
	          format,
	          arguments );

	va_end(
	 arguments );

	return( result );
}

#endif /* defined( OPTIMIZATION_DISABLED ) */

/* Custom vsnprintf for testing error cases
 * Returns the number of characters printed if successful or an error value otherwise
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

/* Tests the libcerror_error_initialize function
 * Returns 1 if successful or 0 if not
 */
int cerror_test_error_initialize(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test libcerror_error_initialize
	 */
	result = libcerror_error_initialize(
	          &error,
	          LIBCERROR_ERROR_DOMAIN_RUNTIME,
	          LIBCERROR_RUNTIME_ERROR_GENERIC );

	CERROR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

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
	result = libcerror_error_initialize(
	          NULL,
	          LIBCERROR_ERROR_DOMAIN_RUNTIME,
	          LIBCERROR_RUNTIME_ERROR_GENERIC );

	CERROR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	error = (libcerror_error_t *) 0x12345678;

	result = libcerror_error_initialize(
	          &error,
	          LIBCERROR_ERROR_DOMAIN_RUNTIME,
	          LIBCERROR_RUNTIME_ERROR_GENERIC );

	CERROR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	error = NULL;

#if defined( HAVE_CERROR_TEST_MEMORY )

	/* Test libcerror_error_initialize with malloc failing
	 */
	cerror_test_malloc_attempts_before_fail = 0;

	result = libcerror_error_initialize(
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
		CERROR_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		CERROR_TEST_ASSERT_IS_NULL(
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

#endif /* defined( __GNUC__ ) && !defined( LIBCERROR_DLL_IMPORT ) */

/* Tests the libcerror_error_free function
 * Returns 1 if successful or 0 if not
 */
int cerror_test_error_free(
     void )
{
	/* Test error cases
	 */
	libcerror_error_free(
	 NULL );

	return( 1 );
}

#if defined( __GNUC__ ) && !defined( LIBCERROR_DLL_IMPORT )

/* Tests the libcerror_error_resize function
 * Returns 1 if successful or 0 if not
 */
int cerror_test_error_resize(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Initialize test
	 */
	libcerror_error_set(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 "Test error." );

	CERROR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	/* Test libcerror_error_resize
	 */
	result = libcerror_error_resize(
	          (libcerror_internal_error_t *) error );

	CERROR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CERROR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libcerror_error_resize(
	          NULL );

	CERROR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

#if defined( HAVE_CERROR_TEST_MEMORY )

	/* Test libcerror_error_resize with libcerror_error_initialize failing
	 */
	cerror_test_malloc_attempts_before_fail = 0;

	result = libcerror_error_resize(
	          (libcerror_internal_error_t *) error );

	if( cerror_test_malloc_attempts_before_fail != -1 )
	{
		cerror_test_malloc_attempts_before_fail = -1;
	}
	else
	{
		CERROR_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		CERROR_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test libcerror_error_resize with realloc failing
	 */
	result = libcerror_error_resize(
	          (libcerror_internal_error_t *) error );

	CERROR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	cerror_test_realloc_attempts_before_fail = 0;

	result = libcerror_error_resize(
	          (libcerror_internal_error_t *) error );

	if( cerror_test_realloc_attempts_before_fail != -1 )
	{
		cerror_test_realloc_attempts_before_fail = -1;
	}
	else
	{
		CERROR_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		CERROR_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );
	}
	cerror_test_realloc_attempts_before_fail = 1;

	result = libcerror_error_resize(
	          (libcerror_internal_error_t *) error );

	if( cerror_test_realloc_attempts_before_fail != -1 )
	{
		cerror_test_realloc_attempts_before_fail = -1;
	}
	else
	{
		CERROR_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		CERROR_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );
	}
#endif /* defined( HAVE_CERROR_TEST_MEMORY ) */

	/* Clean up
	 */
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

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )

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

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

#endif /* defined( __GNUC__ ) && !defined( LIBCERROR_DLL_IMPORT ) */

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

	/* Test libcerror_error_set with format string larger than LIBCERROR_MESSAGE_INCREMENT_SIZE
	 */
	libcerror_error_set(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 "The aim of science is not to open the door to infinite wisdom, but to set a limit to infinite error." );

	CERROR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	  &error );

	CERROR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test libcerror_error_set with parameters
	 */
	libcerror_error_set(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 "Test error with parameter: %s = %d.",
	 "MYPARAMETER",
	 5 );

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

	/* Test libcerror_error_set with libcerror_error_initialize failing
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
	}
	else
	{
		CERROR_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	libcerror_error_free(
	  &error );

	/* Test libcerror_error_set with libcerror_error_resize failing
	 */
	cerror_test_realloc_attempts_before_fail = 0;

	libcerror_error_set(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 "Test error." );

	if( cerror_test_realloc_attempts_before_fail != -1 )
	{
		cerror_test_realloc_attempts_before_fail = -1;
	}
	else
	{
		CERROR_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );
	}
	libcerror_error_free(
	  &error );

	/* Test libcerror_error_set with memory_reallocate before system_string_vsnprintf failing
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
	}
	else
	{
		CERROR_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );
	}
	libcerror_error_free(
	  &error );

#endif /* defined( HAVE_CERROR_TEST_MEMORY ) */

	/* TODO test libcerror_error_get_system_format_string failing */

#if defined( HAVE_CERROR_TEST_FUNCTION_HOOK )

	/* Test libcerror_error_set with vsnprintf returning -1
	 */
	cerror_test_vsnprintf_attempts_before_fail = 0;
	cerror_test_vsnprintf_fail_return_value    = -1;

	libcerror_error_set(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 "Test error 2." );

	if( cerror_test_vsnprintf_attempts_before_fail != -1 )
	{
		cerror_test_vsnprintf_attempts_before_fail = -1;
	}
	else
	{
		CERROR_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );
	}
	libcerror_error_free(
	  &error );

	/* Test libcerror_error_set with vsnprintf returning
	 * a value larger than LIBCERROR_MESSAGE_MAXIMUM_SIZE
	 */
	cerror_test_vsnprintf_attempts_before_fail = 0;
	cerror_test_vsnprintf_fail_return_value    = 2 * LIBCERROR_MESSAGE_MAXIMUM_SIZE;

	libcerror_error_set(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 "Test error 6." );

	if( cerror_test_vsnprintf_attempts_before_fail != -1 )
	{
		cerror_test_vsnprintf_attempts_before_fail = -1;
	}
	else
	{
		CERROR_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );
	}
	libcerror_error_free(
	  &error );

#endif /* defined( HAVE_CERROR_TEST_FUNCTION_HOOK ) */

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

#if defined( HAVE_FMEMOPEN ) && !defined( WINAPI )

/* Tests the libcerror_error_fprint function
 * Returns 1 if successful or 0 if not
 */
int cerror_test_error_fprint(
     void )
{
	char string[ 128 ];

	libcerror_error_t *error      = NULL;
	system_character_t *message   = NULL;
	system_character_t **messages = NULL;
	FILE *stream                  = NULL;
	int print_count               = 0;
	int result                    = 0;

	/* Initialize test
	 */
	libcerror_error_set(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 "Test error." );

	CERROR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	/* Test libcerror_error_fprint
	 */
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

	message = ( (libcerror_internal_error_t *) error )->messages[ 0 ];

	( (libcerror_internal_error_t *) error )->messages[ 0 ] = NULL;

	stream = fmemopen(
	          string,
	          128,
	          "w+");

	print_count = libcerror_error_fprint(
	               error,
	               stream );

	fclose(
	 stream );

	( (libcerror_internal_error_t *) error )->messages[ 0 ] = message;

	CERROR_TEST_ASSERT_EQUAL_INT(
	 "print_count",
	 print_count,
	 0 )

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

	messages = ( (libcerror_internal_error_t *) error )->messages;

	( (libcerror_internal_error_t *) error )->messages = NULL;

	print_count = libcerror_error_fprint(
	               error,
	               stream );

	( (libcerror_internal_error_t *) error )->messages = messages;

	CERROR_TEST_ASSERT_EQUAL_INT(
	 "print_count",
	 print_count,
	 -1 )

#if defined( HAVE_CERROR_TEST_FUNCTION_HOOK ) && defined( OPTIMIZATION_DISABLED )

	/* Test libcerror_error_fprint with fprintf returning -1
	 */
	cerror_test_fprintf_attempts_before_fail = 0;

	stream = fmemopen(
	          string,
	          128,
	          "w+");

	print_count = libcerror_error_fprint(
	               error,
	               stream );

	fclose(
	 stream );

	if( cerror_test_fprintf_attempts_before_fail != -1 )
	{
		cerror_test_fprintf_attempts_before_fail = -1;
	}
	else
	{
		CERROR_TEST_ASSERT_EQUAL_INT(
		 "print_count",
		 print_count,
		 -1 )
	}
#endif /* defined( HAVE_CERROR_TEST_FUNCTION_HOOK ) && defined( OPTIMIZATION_DISABLED ) */

	/* Clean up
	 */
	libcerror_error_free(
	  &error );

	CERROR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#if defined( __GNUC__ ) && !defined( LIBCERROR_DLL_IMPORT )

	/* Test internal_error->messages == NULL
	 */
	libcerror_error_initialize(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC );

	CERROR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	( (libcerror_internal_error_t *) error )->number_of_messages = 0;
	( (libcerror_internal_error_t *) error )->messages           = NULL;
	( (libcerror_internal_error_t *) error )->sizes              = NULL;

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
	 -1 )

	memory_free(
	 error );

	error = NULL;

#endif /* defined( __GNUC__ ) && !defined( LIBCERROR_DLL_IMPORT ) */

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

	libcerror_error_t *error      = NULL;
	system_character_t *message   = NULL;
	system_character_t **messages = NULL;
	FILE *stream                  = NULL;
	const char *expected_string   = NULL;
	int expected_print_count      = 0;
	int print_count               = 0;
	int result                    = 0;

	/* Initialize test
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
	expected_string      = "Test error 1.\r\nTest error 2.";
	expected_print_count = 29;
#else
	expected_string      = "Test error 1.\nTest error 2.";
	expected_print_count = 28;
#endif

	CERROR_TEST_ASSERT_EQUAL_INT(
	 "print_count",
	 print_count,
	 expected_print_count )

	result = narrow_string_compare(
	          string,
	          expected_string,
	          expected_print_count - 1 );

	CERROR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	message = ( (libcerror_internal_error_t *) error )->messages[ 0 ];

	( (libcerror_internal_error_t *) error )->messages[ 0 ] = NULL;

	stream = fmemopen(
	          string,
	          128,
	          "w+");

	print_count = libcerror_error_backtrace_fprint(
	               error,
	               stream );

	fclose(
	 stream );

	( (libcerror_internal_error_t *) error )->messages[ 0 ] = message;

	CERROR_TEST_ASSERT_EQUAL_INT(
	 "print_count",
	 print_count,
	 14 )

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

	messages = ( (libcerror_internal_error_t *) error )->messages;

	( (libcerror_internal_error_t *) error )->messages = NULL;

	print_count = libcerror_error_backtrace_fprint(
	               error,
	               stream );

	( (libcerror_internal_error_t *) error )->messages = messages;

	CERROR_TEST_ASSERT_EQUAL_INT(
	 "print_count",
	 print_count,
	 -1 )

#if defined( HAVE_CERROR_TEST_FUNCTION_HOOK ) && defined( OPTIMIZATION_DISABLED )

	/* Test libcerror_error_backtrace_fprint with fprintf returning -1
	 */
	cerror_test_fprintf_attempts_before_fail = 0;

	stream = fmemopen(
	          string,
	          128,
	          "w+");

	print_count = libcerror_error_backtrace_fprint(
	               error,
	               stream );

	fclose(
	 stream );

	if( cerror_test_fprintf_attempts_before_fail != -1 )
	{
		cerror_test_fprintf_attempts_before_fail = -1;
	}
	else
	{
		CERROR_TEST_ASSERT_EQUAL_INT(
		 "print_count",
		 print_count,
		 -1 )
	}
#endif /* defined( HAVE_CERROR_TEST_FUNCTION_HOOK ) && defined( OPTIMIZATION_DISABLED ) */

	/* Clean up
	 */
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

#endif /* defined( HAVE_FMEMOPEN ) && !defined( WINAPI ) */

/* Tests the libcerror_error_sprint function
 * Returns 1 if successful or 0 if not
 */
int cerror_test_error_sprint(
     void )
{
	char string[ 128 ];

	libcerror_error_t *error      = NULL;
	system_character_t **messages = NULL;
	size_t *sizes                 = NULL;
	int print_count               = 0;
	int result                    = 1;

	/* Initialize test
	 */
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

	messages = ( (libcerror_internal_error_t *) error )->messages;

	( (libcerror_internal_error_t *) error )->messages = NULL;

	print_count = libcerror_error_sprint(
	               error,
	               string,
	               128 );

	( (libcerror_internal_error_t *) error )->messages = messages;

	CERROR_TEST_ASSERT_EQUAL_INT(
	 "print_count",
	 print_count,
	 -1 )

	sizes = ( (libcerror_internal_error_t *) error )->sizes;

	( (libcerror_internal_error_t *) error )->sizes = NULL;

	print_count = libcerror_error_sprint(
	               error,
	               string,
	               128 );

	( (libcerror_internal_error_t *) error )->sizes = sizes;

	CERROR_TEST_ASSERT_EQUAL_INT(
	 "print_count",
	 print_count,
	 -1 )

	print_count = libcerror_error_sprint(
	               error,
	               string,
	               10 );

	CERROR_TEST_ASSERT_EQUAL_INT(
	 "print_count",
	 print_count,
	 -1 )

#if defined( HAVE_CERROR_TEST_MEMORY ) && defined( OPTIMIZATION_DISABLED )

	/* Test libcerror_error_sprint with memcpy returning NULL
	 */
	cerror_test_memcpy_attempts_before_fail = 0;

	print_count = libcerror_error_sprint(
	               error,
	               string,
	               128 );

	if( cerror_test_memcpy_attempts_before_fail != -1 )
	{
		cerror_test_memcpy_attempts_before_fail = -1;
	}
	else
	{
		CERROR_TEST_ASSERT_EQUAL_INT(
		 "print_count",
		 print_count,
		 -1 )
	}
	libcerror_error_free(
	  &error );

#endif /* defined( HAVE_CERROR_TEST_MEMORY ) && defined( OPTIMIZATION_DISABLED ) */

	/* Clean up
	 */
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

	libcerror_error_t *error      = NULL;
	system_character_t **messages = NULL;
	size_t *sizes                 = NULL;
	const char *expected_string   = NULL;
	int expected_print_count      = 0;
	int print_count               = 0;
	int result                    = 1;

	/* Initialize test
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

	print_count = libcerror_error_backtrace_sprint(
	               error,
	               string,
	               128 );

#if defined( WINAPI )
	expected_string      = "Test error 1.\r\nTest error 2.";
	expected_print_count = 29;
#else
	expected_string      = "Test error 1.\nTest error 2.";
	expected_print_count = 28;
#endif

	CERROR_TEST_ASSERT_EQUAL_INT(
	 "print_count",
	 print_count,
	 expected_print_count )

	result = narrow_string_compare(
	          string,
	          expected_string,
	          expected_print_count - 1 );

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

	messages = ( (libcerror_internal_error_t *) error )->messages;

	( (libcerror_internal_error_t *) error )->messages = NULL;

	print_count = libcerror_error_backtrace_sprint(
	               error,
	               string,
	               128 );

	( (libcerror_internal_error_t *) error )->messages = messages;

	CERROR_TEST_ASSERT_EQUAL_INT(
	 "print_count",
	 print_count,
	 -1 )

	sizes = ( (libcerror_internal_error_t *) error )->sizes;

	( (libcerror_internal_error_t *) error )->sizes = NULL;

	print_count = libcerror_error_backtrace_sprint(
	               error,
	               string,
	               128 );

	( (libcerror_internal_error_t *) error )->sizes = sizes;

	CERROR_TEST_ASSERT_EQUAL_INT(
	 "print_count",
	 print_count,
	 -1 )

	print_count = libcerror_error_backtrace_sprint(
	               error,
	               string,
	               10 );

	CERROR_TEST_ASSERT_EQUAL_INT(
	 "print_count",
	 print_count,
	 -1 )

	print_count = libcerror_error_backtrace_sprint(
	               error,
	               string,
	               14 );

	CERROR_TEST_ASSERT_EQUAL_INT(
	 "print_count",
	 print_count,
	 -1 )

#if defined( HAVE_CERROR_TEST_MEMORY ) && defined( OPTIMIZATION_DISABLED )

	/* Test libcerror_error_backtrace_sprint with memcpy returning NULL
	 */
	cerror_test_memcpy_attempts_before_fail = 0;

	print_count = libcerror_error_backtrace_sprint(
	               error,
	               string,
	               128 );

	if( cerror_test_memcpy_attempts_before_fail != -1 )
	{
		cerror_test_memcpy_attempts_before_fail = -1;
	}
	else
	{
		CERROR_TEST_ASSERT_EQUAL_INT(
		 "print_count",
		 print_count,
		 -1 )
	}
	libcerror_error_free(
	  &error );

#endif /* defined( HAVE_CERROR_TEST_MEMORY ) && defined( OPTIMIZATION_DISABLED ) */

	/* Clean up
	 */
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
	 "libcerror_error_initialize",
	 cerror_test_error_initialize );

#endif /* defined( __GNUC__ ) && !defined( LIBCERROR_DLL_IMPORT ) */

	CERROR_TEST_RUN(
	 "libcerror_error_free",
	 cerror_test_error_free );

#if defined( __GNUC__ ) && !defined( LIBCERROR_DLL_IMPORT )

	CERROR_TEST_RUN(
	 "libcerror_error_resize",
	 cerror_test_error_resize );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )

	CERROR_TEST_RUN(
	 "libcerror_error_get_system_format_string",
	 cerror_test_error_get_system_format_string );

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

#endif /* defined( __GNUC__ ) && !defined( LIBCERROR_DLL_IMPORT ) */

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

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

