dnl Functions for libcerror
dnl
dnl Version: 20120325

dnl Function to detect if libcerror is available
dnl ac_libcerror_dummy is used to prevent AC_CHECK_LIB adding unnecessary -l<library> arguments
AC_DEFUN([AX_LIBCERROR_CHECK_LIB],
 [dnl Check if parameters were provided
 AS_IF(
  [test "x$ac_cv_with_libcerror" != x && test "x$ac_cv_with_libcerror" != xno && test "x$ac_cv_with_libcerror" != xauto-detect],
  [AS_IF(
   [test -d "$ac_cv_with_libcerror"],
   [CFLAGS="$CFLAGS -I${ac_cv_with_libcerror}/include"
   LDFLAGS="$LDFLAGS -L${ac_cv_with_libcerror}/lib"],
   [AC_MSG_WARN([no such directory: $ac_cv_with_libcerror])
   ])
  ])

 AS_IF(
  [test "x$ac_cv_with_libcerror" != xno],
  [dnl Check for headers
  AC_CHECK_HEADERS([libcerror.h])
 
  AS_IF(
   [test "x$ac_cv_header_libcerror_h" = xno],
   [ac_cv_libcerror=no],
   [ac_cv_libcerror=yes
   AC_CHECK_LIB(
    fdatetime,
    libcerror_get_version,
    [ac_cv_libcerror_dummy=yes],
    [ac_cv_libcerror=no])
  
   dnl TODO add functions
   ])
  ])

 AS_IF(
  [test "x$ac_cv_libcerror" = xyes],
  [AC_DEFINE(
   [HAVE_LIBCERROR],
   [1],
   [Define to 1 if you have the `cerror' library (-lcerror).])
  LIBS="-lcerror $LIBS"
  ])

 AS_IF(
  [test "x$ac_cv_libcerror" = xyes],
  [AC_SUBST(
   [HAVE_LIBCERROR],
   [1]) ],
  [AC_SUBST(
   [HAVE_LIBCERROR],
   [0])
  ])
 ])

dnl Function to detect if libcerror dependencies are available
AC_DEFUN([AX_LIBCERROR_CHECK_LOCAL],
 [dnl Headers included in libcerror/libcerror_error.c
 AC_CHECK_HEADERS([stdarg.h varargs.h])

 AS_IF(
  [test "x$ac_cv_header_stdarg_h" != xyes && test "x$ac_cv_header_varargs_h" != xyes],
  [AC_MSG_FAILURE(
   [Missing headers: stdarg.h and varargs.h],
   [1])
  ])

 dnl Wide character string functions used in libcerror/libcerror_error.c
 AS_IF(
  [test "x$ac_cv_enable_wide_character_type" != xno],
  [AC_CHECK_FUNCS([wcstombs])

  AS_IF(
   [test "x$ac_cv_func_wcstombs" != xyes],
   [AC_MSG_FAILURE(
    [Missing function: wcstombs],
    [1])
   ])
  ])

 dnl Check for error string functions used in libcerror/libcerror_system.c
 AC_FUNC_STRERROR_R()
 
 AS_IF(
  [test "x$ac_cv_have_decl_strerror_r" != xyes],
  [AC_CHECK_FUNCS([strerror])

  AS_IF(
   [test "x$ac_cv_func_strerror" != xyes],
   [AC_MSG_FAILURE(
    [Missing functions: strerror_r and strerror],
    [1])
   ])
  ])
 ])

