#
# $Id: Makefile.am,v 1.20 2002-04-12 19:28:47 blep Exp $
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
  Test.cpp \
  TestAssert.cpp \
  TestCase.cpp \
  TestComposite.cpp \
  TestFactoryRegistry.cpp \
  TestFailure.cpp \
  TestLeaf.cpp \
  TestPath.cpp \
  TestResult.cpp \
  TestResultCollector.cpp \
  TestRunner.cpp \
  TestSetUp.cpp \
  TestSucessListener.cpp \
  TestSuite.cpp \
  TestTest.cpp \
  TextOutputter.cpp \
  TextTestProgressListener.cpp \
  TextTestResult.cpp \
  TextTestRunner.cpp \
  TypeInfoHelper.cpp \
  XmlOutputter.cpp

libcppunit_la_LDFLAGS= \
 -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE) \
 -release $(LT_RELEASE)




