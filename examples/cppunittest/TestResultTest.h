#ifndef TESTRESULTTEST_H
#define TESTRESULTTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFailure.h>
#include "SynchronizedTestResult.h"


class TestResultTest : public CppUnit::TestCase,
                       public SynchronizedTestResult::SynchronizationObjectListener
{
  CPPUNIT_TEST_SUITE( TestResultTest );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testStop );
  CPPUNIT_TEST( testAddTwoErrors );
  CPPUNIT_TEST( testAddTwoFailures );
  CPPUNIT_TEST( testStartTest );
  CPPUNIT_TEST( testEndTest );
  CPPUNIT_TEST( testWasSuccessfulWithErrors );
  CPPUNIT_TEST( testWasSuccessfulWithFailures );
  CPPUNIT_TEST( testWasSuccessfulWithErrorsAndFailures );
  CPPUNIT_TEST( testWasSuccessfulWithSucessfulTest );
  CPPUNIT_TEST( testSynchronizationAddError );
  CPPUNIT_TEST( testSynchronizationAddFailure );
  CPPUNIT_TEST( testSynchronizationStartTest );
  CPPUNIT_TEST( testSynchronizationEndTest );
  CPPUNIT_TEST( testSynchronizationRunTests );
  CPPUNIT_TEST( testSynchronizationTestErrors );
  CPPUNIT_TEST( testSynchronizationTestFailures );
  CPPUNIT_TEST( testSynchronizationFailures );
  CPPUNIT_TEST( testSynchronizationWasSuccessful );
  CPPUNIT_TEST( testSynchronizationShouldStop );
  CPPUNIT_TEST( testSynchronizationStop );
  CPPUNIT_TEST_SUITE_END();

public:
  TestResultTest();
  virtual ~TestResultTest();

  virtual void setUp();
  virtual void tearDown();

  void testConstructor();

  void testStop();

  void testAddTwoErrors();
  void testAddTwoFailures();
  void testStartTest();
  void testEndTest();

  void testWasSuccessfulWithNoTest();
  void testWasSuccessfulWithErrors();
  void testWasSuccessfulWithFailures();
  void testWasSuccessfulWithErrorsAndFailures();
  void testWasSuccessfulWithSucessfulTest();

  void testSynchronizationAddError();
  void testSynchronizationAddFailure();
  void testSynchronizationStartTest();
  void testSynchronizationEndTest();
  void testSynchronizationRunTests();
  void testSynchronizationTestErrors();
  void testSynchronizationTestFailures();
  void testSynchronizationErrors();
  void testSynchronizationFailures();
  void testSynchronizationWasSuccessful();
  void testSynchronizationShouldStop();
  void testSynchronizationStop();

  virtual void locked();
  virtual void unlocked();

private:
  TestResultTest( const TestResultTest &copy );
  void operator =( const TestResultTest &copy );

  void checkResult( int failures,
                    int errors,
                    int testsRun );

  void checkFailure( CppUnit::TestFailure *failure,
                     std::string expectedMessage,
                     CppUnit::Test *expectedTest,
                     bool expectedIsError );

  void checkWasSuccessful( bool shouldBeSuccessful );

  void checkSynchronization();

private:
  CppUnit::TestResult *m_result;
  SynchronizedTestResult *m_synchronizedResult;  
  CppUnit::Test *m_test;
  CppUnit::Test *m_test2;
  int m_lockCount;
  int m_unlockCount;
};



#endif  // TESTRESULTTEST_H
