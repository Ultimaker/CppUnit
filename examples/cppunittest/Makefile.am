EXTRA_DIST = CppUnitTestMain.dsw CppUnitTestMain.dsp

TESTS = cppunittestmain
check_PROGRAMS = $(TESTS)

INCLUDES = -I$(top_srcdir)/include

cppunittestmain_SOURCES = \
	CppUnitTestMain.cpp \
	MockTestListener.cpp \
	MockTestListener.h \
	TestCallerTest.cpp \
	TestCallerTest.h \
	TestResultTest.cpp \
	TestResultTest.h \
	TrackedTestCase.cpp \
	TrackedTestCase.h

cppunittestmain_LDADD= \
  $(top_builddir)/src/cppunit/libcppunit.la 
