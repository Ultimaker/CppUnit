#
# $Id: Makefile.am,v 1.31 2002-05-23 18:38:39 blep Exp $
#

EXTRA_DIST = cppunit.dsp cppunit_dll.dsp DllMain.cpp
INCLUDES = -I$(top_builddir)/include -I$(top_srcdir)/include

lib_LTLIBRARIES = libcppunit.la

libcppunit_la_SOURCES = \
  Asserter.cpp \
  BeOsDynamicLibraryManager.cpp \
  BriefTestProgressListener.cpp \
  CompilerOutputter.cpp \
  DynamicLibraryManager.cpp \
  DynamicLibraryManagerException.cpp \
  Exception.cpp \
  NotEqualException.cpp \
  RepeatedTest.cpp \
  PlugInManager.cpp \
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
  TestPlugInAdapter.cpp \
  TestResult.cpp \
  TestResultCollector.cpp \
  TestRunner.cpp \
  TestSetUp.cpp \
  TestSuccessListener.cpp \
  TestSuite.cpp \
  TextOutputter.cpp \
  TextTestProgressListener.cpp \
  TextTestResult.cpp \
  TextTestRunner.cpp \
  TypeInfoHelper.cpp \
  UnixDynamicLibraryManager.cpp \
  XmlDocument.cpp \
  XmlElement.cpp \
  XmlOutputter.cpp \
  Win32DynamicLibraryManager.cpp

libcppunit_la_LDFLAGS= \
 -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE) \
 -release $(LT_RELEASE)

