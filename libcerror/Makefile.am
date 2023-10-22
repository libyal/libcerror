AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_DLL_EXPORT@

lib_LTLIBRARIES = libcerror.la

libcerror_la_SOURCES = \
	libcerror.c \
	libcerror_definitions.h \
	libcerror_extern.h \
	libcerror_error.c libcerror_error.h \
	libcerror_support.c libcerror_support.h \
	libcerror_system.c libcerror_system.h \
	libcerror_types.h \
	libcerror_unused.h

libcerror_la_LDFLAGS = -no-undefined -version-info 1:0:0

EXTRA_DIST = \
	libcerror_definitions.h.in \
	libcerror.rc \
	libcerror.rc.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	-rm -f libcerror_definitions.h
	-rm -f libcerror.rc
	-rm -f Makefile

sources-local: $(BUILT_SOURCES)

splint-local:
	@echo "Running splint on libcerror ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libcerror_la_SOURCES)

