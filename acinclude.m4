dnl Checks for required headers and functions
dnl
dnl Version: 20240513

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

dnl Function to check if DLL support is needed
AC_DEFUN([AX_LIBCERROR_CHECK_DLL_SUPPORT],
  [AS_IF(
    [test "x$enable_shared" = xyes],
    [AS_CASE(
      [$host],
      [*cygwin* | *mingw* | *msys*],
      [AC_DEFINE(
        [HAVE_DLLMAIN],
        [1],
        [Define to 1 to enable the DllMain function.])
      AC_SUBST(
        [HAVE_DLLMAIN],
        [1])

      AC_SUBST(
        [LIBCERROR_DLL_EXPORT],
        ["-DLIBCERROR_DLL_EXPORT"])

      AC_SUBST(
        [LIBCERROR_DLL_IMPORT],
        ["-DLIBCERROR_DLL_IMPORT"])
      ])
    ])
  ])

