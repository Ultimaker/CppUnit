#
# $Id: Makefile.am,v 1.4 2001-05-19 17:41:03 bastiaan Exp $
#

EXTRA_DIST = cppunit.dsw cppunit.dsp
INCLUDES = -I$(top_srcdir)/include

lib_LTLIBRARIES = libcppunit.la

libcppunit_la_SOURCES = \
  TestAssert.cpp \
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




