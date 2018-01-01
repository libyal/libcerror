/*
 * Library error system functions testing program
 *
 * Copyright (C) 2008-2018, Joachim Metz <joachim.metz@gmail.com>
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

/* Tests the libcerror_system_copy_string_from_error_number function
 * Returns 1 if successful or 0 if not
 */
int cerror_test_system_copy_string_from_error_number(
     void )
{
	system_character_t string[ 128 ];

	/* Test error cases
	 */
	libcerror_system_copy_string_from_error_number(
	 NULL,
	 128,
	 0 );

	libcerror_system_copy_string_from_error_number(
	 string,
	 (size_t) INT_MAX + 1,
	 0 );

/* TODO test FormatMessage failing */
/* TODO test strerror_r failing */
/* TODO test strerror failing */

	return( 1 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBCERROR_DLL_IMPORT ) */

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

	/* Test libcerror_system_set_error with format string larger than LIBCERROR_MESSAGE_INCREMENT_SIZE
	 */
	libcerror_system_set_error(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 error_code,
	 "The aim of science is not to open the door to infinite wisdom, but to set a limit to infinite error." );

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
	cerror_test_realloc_attempts_before_fail = 0;

	libcerror_system_set_error(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 error_code,
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

	/* Test libcerror_system_set_error with memory_reallocate before system_string_vsnprintf failing
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
	}
	else
	{
		CERROR_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );
	}
	libcerror_error_free(
	  &error );

	/* Test libcerror_system_set_error with memory_reallocate before system_string_copy failing
	 */
	cerror_test_realloc_attempts_before_fail = 3;

	libcerror_system_set_error(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 error_code,
	 "Test error 3." );

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

	libcerror_system_set_error(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 error_code,
	 "Test error 4." );

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

	libcerror_system_set_error(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 error_code,
	 "Test error 5." );

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

	/* TODO test system_string_copy failing */

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
	 "libcerror_system_copy_string_from_error_number",
	 cerror_test_system_copy_string_from_error_number );

#endif /* defined( __GNUC__ ) && !defined( LIBCERROR_DLL_IMPORT ) */

	CERROR_TEST_RUN(
	 "libcerror_system_set_error",
	 cerror_test_system_set_error );

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

