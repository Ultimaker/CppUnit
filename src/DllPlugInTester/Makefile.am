EXTRA_DIST = DllPlugInTester.dsp

INCLUDES = -I$(top_builddir)/include -I$(top_srcdir)/include

bin_PROGRAMS=DllPlugInTester

DllPlugInTester_SOURCES= DllPlugInTester.cpp \
	CommandLineParser.h \
	CommandLineParser.cpp

DllPlugInTester_LDADD= \
  $(top_builddir)/src/cppunit/libcppunit.la ld.so

DllPlugInTester_LDFLAGS = -ldl
