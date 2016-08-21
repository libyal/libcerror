dnl Functions for testing
dnl
dnl Version: 20160821

dnl Function to detect if tests dependencies are available
AC_DEFUN([AX_TESTS_CHECK_LOCAL],
 [AC_CHECK_HEADERS([malloc.h])

 AC_CHECK_FUNCS([fmemopen])
 ])

