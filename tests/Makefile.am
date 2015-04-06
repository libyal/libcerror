AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_DLL_IMPORT@

TESTS = \
	test_error.sh

check_SCRIPTS = \
	test_error.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	cerror_test_error

cerror_test_error_SOURCES = \
	cerror_test_error.c \
	cerror_test_libcerror.h \
	cerror_test_libcstring.h \
	cerror_test_unused.h

cerror_test_error_LDADD = \
	../libcerror/libcerror.la \
	@LIBCSTRING_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

