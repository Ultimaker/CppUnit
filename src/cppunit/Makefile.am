#
# $Id: Makefile.am,v 1.23 2002-04-15 15:30:34 blep Exp $
#

EXTRA_DIST = cppunit.dsp cppunit_dll.dsp DllMain.cpp
INCLUDES = -I$(top_builddir)/include -I$(top_srcdir)/include

lib_LTLIBRARIES = libcppunit.la

libcppunit_la_SOURCES = \
  Asserter.cpp \
  BeosDynamicLibraryManager.cpp \
  CompilerOutputter.cpp \
  DynamicLibraryManager.cpp \
  DynamicLibraryManagerException.cpp \
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
  TestPlugInDefaultImpl.cpp \
  TestPlugInSuite.cpp \
  TestResult.cpp \
  TestResultCollector.cpp \
  TestRunner.cpp \
  TestSetUp.cpp \
  TestSucessListener.cpp \
  TestSuite.cpp \
  TextOutputter.cpp \
  TextTestProgressListener.cpp \
  TextTestResult.cpp \
  TextTestRunner.cpp \
  TypeInfoHelper.cpp \
  UnixDynamicLibraryManager.cpp \
  XmlOutputter.cpp \
  Win32DynamicLibraryManager.cpp

libcppunit_la_LDFLAGS= \
 -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE) \
 -release $(LT_RELEASE)




