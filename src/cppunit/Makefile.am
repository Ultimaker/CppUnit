#
# $Id: Makefile.am,v 1.18 2002-03-25 22:35:34 blep Exp $
#

EXTRA_DIST = cppunit.dsw cppunit.dsp cppunit_dll.dsp DllMain.cpp
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
  TestResultCollector.cpp \
  TestSetUp.cpp \
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




