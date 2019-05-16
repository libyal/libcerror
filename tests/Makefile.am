AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_DLL_IMPORT@

TESTS = \
	test_library.sh

check_SCRIPTS = \
	test_library.sh \
	test_manpage.sh \
	test_runner.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	cerror_test_error \
	cerror_test_support \
	cerror_test_system

cerror_test_error_SOURCES = \
	cerror_test_error.c \
	cerror_test_libcerror.h \
	cerror_test_macros.h \
	cerror_test_memory.c cerror_test_memory.h \
	cerror_test_unused.h

cerror_test_error_LDADD = \
	../libcerror/libcerror.la

cerror_test_support_SOURCES = \
	cerror_test_libcerror.h \
	cerror_test_macros.h \
	cerror_test_support.c \
	cerror_test_unused.h

cerror_test_support_LDADD = \
	../libcerror/libcerror.la

cerror_test_system_SOURCES = \
	cerror_test_libcerror.h \
	cerror_test_macros.h \
	cerror_test_memory.c cerror_test_memory.h \
	cerror_test_system.c \
	cerror_test_unused.h

cerror_test_system_LDADD = \
	../libcerror/libcerror.la

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

