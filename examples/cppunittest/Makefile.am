EXTRA_DIST = CppUnitTestMain.dsw CppUnitTestMain.dsp

TESTS = cppunittestmain
check_PROGRAMS = $(TESTS)

INCLUDES = -I$(top_builddir)/include -I$(top_srcdir)/include

cppunittestmain_SOURCES = \
	BaseTestCase.cpp \
	BaseTestCase.h \
	CoreSuite.h \
	CppUnitTestMain.cpp \
	CppUnitTestSuite.cpp \
	CppUnitTestSuite.h \
	ExceptionTest.cpp \
	ExceptionTest.h \
	ExtensionSuite.h \
	FailingTestCase.cpp \
	FailingTestCase.h \
	FailureException.h \
	HelperMacrosTest.cpp \
	HelperMacrosTest.h \
	HelperSuite.h \
	MockTestListener.cpp \
	MockTestListener.h \
	NotEqualExceptionTest.cpp \
	NotEqualExceptionTest.h \
	OrthodoxTest.cpp \
	OrthodoxTest.h \
	OutputSuite.h \
	RepeatedTestTest.cpp \
	RepeatedTestTest.h \
	SubclassedTestCase.cpp \
	SubclassedTestCase.h \
	SynchronizedTestResult.h \
	TestAssertTest.cpp \
	TestAssertTest.h \
	TestCallerTest.cpp \
	TestCallerTest.h \
	TestCaseTest.cpp \
	TestCaseTest.h \
	TestDecoratorTest.cpp \
	TestDecoratorTest.h \
	TestListenerTest.cpp \
	TestListenerTest.h \
	TestFailureTest.cpp \
	TestFailureTest.h \
	TestResultTest.cpp \
	TestResultTest.h \
	TestSetUpTest.cpp \
	TestSetUpTest.h \
	TestSuiteTest.cpp \
	TestSuiteTest.h \
	TrackedTestCase.cpp \
	TrackedTestCase.h \
	UnitTestToolSuite.h \
	XmlOutputterTest.h \
	XmlOutputterTest.cpp \
	XmlUniformiser.h \
	XmlUniformiser.cpp

cppunittestmain_LDADD= \
  $(top_builddir)/src/cppunit/libcppunit.la 
