/*
 * Library error system functions testing program
 *
 * Copyright (C) 2008-2020, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( WINAPI )
#if defined( HAVE_STRERROR_R )

#if defined( STRERROR_R_CHAR_P )
static char *(*cerror_test_real_strerror_r)(int, char *, size_t)                = NULL;
#else
static int (*cerror_test_real_strerror_r)(int, char *, size_t)                  = NULL;
#endif

int cerror_test_strerror_r_attempts_before_fail                                 = -1;

#elif defined( HAVE_STRERROR )

static char *(*cerror_test_real_strerror)(int)                                  = NULL;

int cerror_test_strerror_attempts_before_fail                                   = -1;

#endif
#endif /* !defined( WINAPI ) */

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

#if !defined( WINAPI )
#if defined( HAVE_STRERROR_R )

#if defined( STRERROR_R_CHAR_P )
/* Custom strerror_r for testing error cases
 * Returns a pointer to the error string if successfull or NULL on error
 */
char *strerror_r(
       int errnum,
       char *buf,
       size_t buflen )
#else
/* Custom strerror_r for testing error cases
 * Returns 0 if successfull, or -1 or a positive integer on error
 */
int strerror_r(
     int errnum,
     char *buf,
     size_t buflen )
#endif
{
#if defined( STRERROR_R_CHAR_P )
	char *result = NULL;
#else
	int result   = 0;
#endif

	if( cerror_test_real_strerror_r == NULL )
	{
		cerror_test_real_strerror_r = dlsym(
		                               RTLD_NEXT,
		                               "strerror_r" );
	}
	if( cerror_test_strerror_r_attempts_before_fail == 0 )
	{
		cerror_test_strerror_r_attempts_before_fail = -1;

#if defined( STRERROR_R_CHAR_P )
		return( NULL );
#else
		return( -1 );
#endif
	}
	else if( cerror_test_strerror_r_attempts_before_fail > 0 )
	{
		cerror_test_strerror_r_attempts_before_fail--;
	}
	result = cerror_test_real_strerror_r(
	          errnum,
	          buf,
	          buflen );

	return( result );
}

#elif defined( HAVE_STRERROR )

/* Custom strerror for testing error cases
 * Returns a pointer to the error string if successfull or NULL on error
 */
char *strerror(
       int errnum )
{
	char *result = NULL;

	if( cerror_test_real_strerror == NULL )
	{
		cerror_test_real_strerror = dlsym(
		                             RTLD_NEXT,
		                             "strerror" );
	}
	if( cerror_test_strerror_attempts_before_fail == 0 )
	{
		cerror_test_strerrorttempts_before_fail = -1;

		return( NULL );
	}
	else if( cerror_test_strerror_attempts_before_fail > 0 )
	{
		cerror_test_strerror_attempts_before_fail--;
	}
	result = cerror_test_real_strerror(
	          errnum );

	return( result );
}

#endif /* defined( HAVE_STRERROR_R ) */
#endif /* !defined( WINAPI ) */

#endif /* defined( HAVE_CERROR_TEST_FUNCTION_HOOK ) */

#if defined( WINAPI ) && ( WINVER <= 0x0500 ) && !defined( LIBCERROR_DLL_IMPORT )

/* Tests the libcerror_FormatMessageA function
 * Returns 1 if successful or 0 if not
 */
int cerror_test_FormatMessageA(
     void )
{
	char string[ 128 ];

	DWORD print_count = 0;

	/* Test regular cases
	 */
	print_count = libcerror_FormatMessageA(
	               FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
	               NULL,
	               0,
	               MAKELANGID(
	                LANG_NEUTRAL,
	                SUBLANG_DEFAULT ),
	               string,
	               128,
	               NULL );

	CERROR_TEST_ASSERT_NOT_EQUAL_INT(
	 "print_count",
	 (int) print_count,
	 (int) 0 );

	/* Test error cases
	 */
	print_count = libcerror_FormatMessageA(
	               FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
	               NULL,
	               0,
	               MAKELANGID(
	                LANG_NEUTRAL,
	                SUBLANG_DEFAULT ),
	               NULL,
	               128,
	               NULL );

	CERROR_TEST_ASSERT_EQUAL_INT(
	 "print_count",
	 (int) print_count,
	 (int) 0 );

	return( 1 );

on_error:
	return( 0 );
}

/* Tests the libcerror_FormatMessageW function
 * Returns 1 if successful or 0 if not
 */
int cerror_test_FormatMessageW(
     void )
{
	wchar_t string[ 128 ];

	DWORD print_count = 0;

	/* Test regular cases
	 */
	print_count = libcerror_FormatMessageW(
	               FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
	               NULL,
	               0,
	               MAKELANGID(
	                LANG_NEUTRAL,
	                SUBLANG_DEFAULT ),
	               string,
	               128,
	               NULL );

	CERROR_TEST_ASSERT_NOT_EQUAL_INT(
	 "print_count",
	 (int) print_count,
	 (int) 0 );

	/* Test error cases
	 */
	print_count = libcerror_FormatMessageW(
	               FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
	               NULL,
	               0,
	               MAKELANGID(
	                LANG_NEUTRAL,
	                SUBLANG_DEFAULT ),
	               NULL,
	               128,
	               NULL );

	CERROR_TEST_ASSERT_EQUAL_INT(
	 "print_count",
	 (int) print_count,
	 (int) 0 );

	return( 1 );

on_error:
	return( 0 );
}

#endif /* defined( WINAPI ) && ( WINVER <= 0x0500 ) && !defined( LIBCERROR_DLL_IMPORT ) */

#if defined( __GNUC__ ) && !defined( LIBCERROR_DLL_IMPORT )

/* Tests the libcerror_system_copy_string_from_error_number function
 * Returns 1 if successful or 0 if not
 */
int cerror_test_system_copy_string_from_error_number(
     void )
{
	system_character_t string[ 128 ];

	int result = 0;

	/* Test error cases
	 */
	result = libcerror_system_copy_string_from_error_number(
	          NULL,
	          128,
	          0 );

	CERROR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	result = libcerror_system_copy_string_from_error_number(
	          string,
	          (size_t) INT_MAX + 1,
	          0 );

	CERROR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

#if defined( WINAPI )

/* TODO test FormatMessage failing */

#elif defined( HAVE_STRERROR_R )

#if defined( HAVE_CERROR_TEST_FUNCTION_HOOK )

	/* Test libcerror_system_copy_string_from_error_number with strerror_r failing
	 */
	cerror_test_strerror_r_attempts_before_fail = 0;

	result = libcerror_system_copy_string_from_error_number(
	          string,
	          128,
	          0 );

	if( cerror_test_strerror_r_attempts_before_fail != -1 )
	{
		cerror_test_strerror_r_attempts_before_fail = -1;
	}
	else
	{
		CERROR_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );
	}

#endif /* defined( HAVE_CERROR_TEST_FUNCTION_HOOK ) */

#elif defined( HAVE_STRERROR )

#if defined( HAVE_CERROR_TEST_FUNCTION_HOOK )

	/* Test libcerror_system_copy_string_from_error_number with strerror failing
	 */
	cerror_test_strerror_attempts_before_fail = 0;

	result = libcerror_system_copy_string_from_error_number(
	          string,
	          128,
	          0 );

	if( cerror_test_strerror_attempts_before_fail != -1 )
	{
		cerror_test_strerror_attempts_before_fail = -1;
	}
	else
	{
		CERROR_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );
	}

#endif /* defined( HAVE_CERROR_TEST_FUNCTION_HOOK ) */

#endif /* defined( WINAPI ) */

	return( 1 );

on_error:
	return( 0 );
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

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )

	/* TODO test libcerror_error_get_system_format_string failing */

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	/* TODO test libcerror_error_get_system_format_string with libcerror_error_initialize failing */

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

#if defined( WINAPI )

	/* TODO test libcerror_error_set with FormatMessage failing in libcerror_system_copy_string_from_error_number */

#elif defined( HAVE_STRERROR_R )

#if defined( HAVE_CERROR_TEST_FUNCTION_HOOK )

	/* Test libcerror_error_set with strerror_r failing in libcerror_system_copy_string_from_error_number
	 */
	cerror_test_strerror_r_attempts_before_fail = 0;

	libcerror_system_set_error(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 error_code,
	 "Test error 7." );

	if( cerror_test_strerror_r_attempts_before_fail != -1 )
	{
		cerror_test_strerror_r_attempts_before_fail = -1;
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

#elif defined( HAVE_STRERROR )

#if defined( HAVE_CERROR_TEST_FUNCTION_HOOK )

	/* Test libcerror_error_set with strerror failing in libcerror_system_copy_string_from_error_number
	 */
	cerror_test_strerror_attempts_before_fail = 0;

	libcerror_system_set_error(
	 &error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 error_code,
	 "Test error 7." );

	if( cerror_test_strerror_attempts_before_fail != -1 )
	{
		cerror_test_strerror_attempts_before_fail = -1;
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

#endif /* defined( WINAPI ) */

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

#if defined( WINAPI ) && ( WINVER <= 0x0500 ) && !defined( LIBCERROR_DLL_IMPORT )

	CERROR_TEST_RUN(
	 "libcerror_FormatMessageA",
	 cerror_test_FormatMessageA );

	CERROR_TEST_RUN(
	 "libcerror_FormatMessageW",
	 cerror_test_FormatMessageW );

#endif /* defined( WINAPI ) && ( WINVER <= 0x0500 ) && !defined( LIBCERROR_DLL_IMPORT ) */

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

