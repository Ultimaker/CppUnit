#
# $Id: Makefile.am,v 1.36 2002-07-03 07:02:49 blep Exp $
#

EXTRA_DIST = cppunit.dsp cppunit_dll.dsp DllMain.cpp
INCLUDES = -I$(top_builddir)/include -I$(top_srcdir)/include

lib_LTLIBRARIES = libcppunit.la

libcppunit_la_SOURCES = \
  AdditionalMessage.cpp \
  Asserter.cpp \
  BeOsDynamicLibraryManager.cpp \
  BriefTestProgressListener.cpp \
  CompilerOutputter.cpp \
  DynamicLibraryManager.cpp \
  DynamicLibraryManagerException.cpp \
  Exception.cpp \
  Message.cpp \
  RepeatedTest.cpp \
  PlugInManager.cpp \
  SourceLine.cpp \
  StringTools.cpp \
  SynchronizedObject.cpp \
  Test.cpp \
  TestAssert.cpp \
  TestCase.cpp \
  TestComposite.cpp \
  TestFactoryRegistry.cpp \
  TestFailure.cpp \
  TestLeaf.cpp \
  TestNamer.cpp \
  TestPath.cpp \
  TestPlugInDefaultImpl.cpp \
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
  XmlOutputterHook.cpp \
  Win32DynamicLibraryManager.cpp

libcppunit_la_LDFLAGS= \
 -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE) \
 -release $(LT_RELEASE)

