#
# $Id: Makefile.am,v 1.2 2000-10-11 18:53:13 e-s Exp $
#

cppunitdir=$(includedir)/cppunit

lib_LTLIBRARIES = libcppunit.la

libcppunit_la_SOURCES = \
  TestCase.cpp \
  TestSuite.cpp \
  TestResult.cpp \
  TestFailure.cpp \
  TestRegistry.cpp \
  Exception.cpp \
  TextTestResult.cpp 

cppunit_HEADERS = \
  estring.h \
  Test.h \
  TestCase.h \
  TestSuite.h \
  TestResult.h \
  TestFailure.h \
  TestRegistry.h \
  TestCaller.h \
  Exception.h \
  TextTestResult.h



libcppunit_la_LDFLAGS= \
 -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE) \
 -release $(LT_RELEASE)




