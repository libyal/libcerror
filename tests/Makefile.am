AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_DLL_IMPORT@

TESTS = \
	test_api_functions.sh \
	test_api_types.sh

check_SCRIPTS = \
	test_api_functions.sh \
	test_api_types.sh \
	test_runner.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	cerror_test_error \
	cerror_test_get_version

cerror_test_error_SOURCES = \
	cerror_test_error.c \
	cerror_test_libcerror.h \
	cerror_test_libcstring.h \
	cerror_test_macros.h \
	cerror_test_unused.h

cerror_test_error_LDADD = \
	../libcerror/libcerror.la \
	@LIBCSTRING_LIBADD@

cerror_test_get_version_SOURCES = \
	cerror_test_get_version.c \
	cerror_test_libcerror.h \
	cerror_test_libcstring.h \
	cerror_test_macros.h \
	cerror_test_unused.h

cerror_test_get_version_LDADD = \
	../libcerror/libcerror.la \
	@LIBCSTRING_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

