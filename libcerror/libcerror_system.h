/*
 * System functions
 *
 * Copyright (c) 2008-2012, Joachim Metz <jbmetz@users.sourceforge.net>
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

#if !defined( _LIBCERROR_SYSTEM_H )
#define _LIBCERROR_SYSTEM_H

#include <common.h>
#include <types.h>

#include <stdio.h>

#include "libcerror_extern.h"
#include "libcerror_libcstring.h"
#include "libcerror_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

ssize_t libcerror_system_copy_string_from_error_number(
         libcstring_system_character_t *string,
         size_t string_size,
         uint32_t error_number );

LIBCERROR_EXTERN \
void libcerror_system_set_error(
      libcerror_error_t **error,
      int error_domain,
      int error_code,
      uint32_t system_error_code,
      const char *format_string,
      ... );

#if defined( __cplusplus )
}
#endif

#endif

