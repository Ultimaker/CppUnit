#
# $Id: Makefile.am,v 1.1 2001-04-28 18:23:32 bastiaan Exp $
#

EXTRA_DIST = cppunit.dsw cppunit.dsp

cppunitdir=$(includedir)/cppunit

lib_LTLIBRARIES = libcppunit.la

libcppunit_la_SOURCES = \
  TestCase.cpp \
  TestSuite.cpp \
  TestResult.cpp \
  TestFailure.cpp \
  TestRegistry.cpp \
  Exception.cpp \
  TextTestResult.cpp \
  estring.h

libcppunit_la_LDFLAGS= \
 -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE) \
 -release $(LT_RELEASE)




