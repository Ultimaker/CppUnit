#
# $Id: Makefile.am,v 1.1.1.1 2000-10-05 18:37:28 e-s Exp $
#

cppunitdir=$(includedir)/cppunit

lib_LTLIBRARIES = libcppunit.la

libcppunit_la_SOURCES = \
  TestCase.cpp \
  TestSuite.cpp \
  TestResult.cpp \
  TestFailure.cpp \
  TestRegistry.cpp

cppunit_HEADERS = \
  Test.h \
  TestCase.h \
  TestSuite.h \
  TestResult.h \
  TestFailure.h \
  TestRegistry.h \
  TestCaller.h \
  Exception.h


libcppunit_la_LDFLAGS= \
 -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE) \
 -release $(LT_RELEASE)




