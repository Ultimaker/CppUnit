SUBDIRS = extensions ui

DISTCLEANFILES = config-auto.h

libcppunitincludedir = $(includedir)/cppunit
libcppunitinclude_HEADERS =  \
	config-auto.h \
	config-msvc6.h \
	config-bcb5.h \
	Asserter.h \
	CompilerOutputter.h \
	Exception.h \
	NotEqualException.h \
	Outputter.h \
	Portability.h \
	SourceLine.h \
	SynchronizedObject.h \
	Test.h \
	TestAssert.h \
	TestCase.h \
	TestCaller.h \
	TestComposite.h \
	TestFailure.h \
	TestFixture.h \
	TestLeaf.h \
	TestPath.h \
	TestResult.h \
	TestResultCollector.h \
	TestRunner.h \
	TestSucessListener.h \
	TestSuite.h \
	TestTest.h \
	TextOutputter.h \
	TextTestProgressListener.h \
	TextTestResult.h \
	TextTestRunner.h \
	TestListener.h \
	XmlOutputter.h

dist-hook:
	rm -f $(distdir)/config-auto.h
