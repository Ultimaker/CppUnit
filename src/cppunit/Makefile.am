#
# $Id: Makefile.am,v 1.11 2001-10-05 08:06:28 blep Exp $
#

EXTRA_DIST = cppunit.dsw cppunit.dsp
INCLUDES = -I$(top_builddir)/include -I$(top_srcdir)/include

lib_LTLIBRARIES = libcppunit.la

libcppunit_la_SOURCES = \
  NotEqualException.cpp \
  RepeatedTest.cpp \
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
  XmlTestResultOutputter.cpp

libcppunit_la_LDFLAGS= \
 -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE) \
 -release $(LT_RELEASE)




