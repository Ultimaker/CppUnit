#
# $Id: Makefile.am,v 1.16 2002-03-03 11:57:26 blep Exp $
#

EXTRA_DIST = cppunit.dsw cppunit.dsp
INCLUDES = -I$(top_builddir)/include -I$(top_srcdir)/include

lib_LTLIBRARIES = libcppunit.la

libcppunit_la_SOURCES = \
  Asserter.cpp \
  CompilerOutputter.cpp \
  Exception.cpp \
  NotEqualException.cpp \
  RepeatedTest.cpp \
  SourceLine.cpp \
  SynchronizedObject.cpp \
  TestAssert.cpp \
  TestCase.cpp \
  TestFactoryRegistry.cpp \
  TestFailure.cpp \
  TestResult.cpp \
  TestRegistry.cpp \
  TestResultCollector.cpp \
  TestSucessListener.cpp \
  TestSuite.cpp \
  TextOutputter.cpp \
  TextTestProgressListener.cpp \
  TextTestResult.cpp \
  TextTestRunner.cpp \
  TypeInfoHelper.cpp \
  XmlOutputter.cpp

libcppunit_la_LDFLAGS= \
 -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE) \
 -release $(LT_RELEASE)




