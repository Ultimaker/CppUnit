#ifndef TESTCALLERTEST_H
#define TESTCALLERTEST_H

#include <cppunit/TestCase.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestSuite.h>
#include "TrackedTestCase.h"


class TestCallerTest : public CppUnit::TestCase, 
                              Tracker
{
public:
  TestCallerTest();
  virtual ~TestCallerTest();

  static CppUnit::TestSuite *suite();

  virtual void setUp();
  virtual void tearDown();

  void testBasicConstructor();
  void testReferenceConstructor();
  void testPointerConstructor();

  void testExpectFailureException();
  void testExpectException();
  void testExpectedExceptionNotCaught();

private:
  class ExceptionThrower : public CppUnit::TestCase
  {
  public:
    void testThrowFailureException();
    void testThrowException();
    void testThrowNothing();
  };

  virtual void onConstructor();
  virtual void onDestructor();
  virtual void onSetUp();
  virtual void onTearDown();
  virtual void onTest();

  void checkNothingButConstructorCalled();
  void checkRunningSequenceCalled();
  void checkTestName( std::string testName );

  TestCallerTest( const TestCallerTest &copy );
  void operator =( const TestCallerTest &copy );

private:
  int m_constructorCount;
  int m_destructorCount;
  int m_setUpCount;
  int m_tearDownCount;
  int m_testCount;
  const std::string m_testName;
  CppUnit::TestResult *m_result;
};



// Inlines methods for TestCallerTest:
// -----------------------------------



#endif  // TESTCALLERTEST_H
