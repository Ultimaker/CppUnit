#
# $Id: Makefile.am,v 1.3 2001-04-14 22:37:30 bastiaan Exp $
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
  estring.h

libcppunit_la_LDFLAGS= \
 -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE) \
 -release $(LT_RELEASE)




