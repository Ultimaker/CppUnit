#
# $Id: Makefile.am,v 1.2 2001-04-29 14:09:16 bastiaan Exp $
#

EXTRA_DIST = cppunit.dsw cppunit.dsp

cppunitdir=$(includedir)/cppunit

lib_LTLIBRARIES = libcppunit.la

libcppunit_la_SOURCES = \
  TestAssert.cpp \
  TestCase.cpp \
  TestSuite.cpp \
  TestResult.cpp \
  TestFailure.cpp \
  TestRegistry.cpp \
  Exception.cpp \
  TextTestResult.cpp \
  TestFactoryRegistry.cpp \
  TypeInfoHelper.cpp \
  TypeInfoHelper.h \
  estring.h

libcppunit_la_LDFLAGS= \
 -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE) \
 -release $(LT_RELEASE)




