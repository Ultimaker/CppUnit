#
# $Id: Makefile.am,v 1.5 2001-06-02 22:29:52 smr99 Exp $
#

EXTRA_DIST = cppunit.dsw cppunit.dsp
INCLUDES = -I$(top_srcdir)/include

lib_LTLIBRARIES = libcppunit.la

libcppunit_la_SOURCES = \
  TestCase.cpp \
  TestSuite.cpp \
  TestResult.cpp \
  TestFailure.cpp \
  TestRegistry.cpp \
  Exception.cpp \
  TextTestResult.cpp \
  TextTestRunner.cpp \
  TestFactoryRegistry.cpp \
  TypeInfoHelper.cpp \
  estring.h

libcppunit_la_LDFLAGS= \
 -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE) \
 -release $(LT_RELEASE)




