EXTRA_DIST = simple.dsp

INCLUDES = -I$(top_builddir)/include -I$(top_srcdir)/include

bin_PROGRAMS=simple

simple_SOURCES= ExampleTestCase.cpp Main.cpp  ExampleTestCase.h

simple_LDADD= \
  $(top_builddir)/src/cppunit/libcppunit.la 

