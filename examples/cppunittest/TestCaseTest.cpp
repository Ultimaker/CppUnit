#include "CoreSuite.h"
#include "TestCaseTest.h"
#include "FailingTestCase.h"
#include <cppunit/TestResult.h>

/*
 - test have been done to check exception management in run(). other 
   tests need to be added to check the other aspect of TestCase.
 */

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( TestCaseTest,
                                       CppUnitTest::coreSuiteName() );


TestCaseTest::TestCaseTest()
{
}


TestCaseTest::~TestCaseTest()
{
}


void 
TestCaseTest::setUp()
{
  m_result = new CppUnit::TestResult();
}


void 
TestCaseTest::tearDown()
{
  delete m_result;
}


void 
TestCaseTest::testSetUpFailure()
{
  checkFailure( true, false, false );
}


void 
TestCaseTest::testRunTestFailure()
{
  checkFailure( false, true, false );
}


void 
TestCaseTest::testTearDownFailure()
{
  checkFailure( false, false, true );
}


void 
TestCaseTest::testFailAll()
{
  checkFailure( true, true, true );
}


void 
TestCaseTest::testNoFailure()
{
  checkFailure( false, false, false );
}


void 
TestCaseTest::checkFailure( bool failSetUp, 
                            bool failRunTest,
                            bool failTearDown )
{
  try
  {
    FailingTestCase test( failSetUp, failRunTest, failTearDown );
    test.run( m_result );
    test.verify( !failSetUp, !failSetUp );
  }
  catch ( FailureException & )
  {
    CPPUNIT_ASSERT_MESSAGE( "exception should have been catched", false );
  }
}


void 
TestCaseTest::testCountTestCases()
{
  CppUnit::TestCase test;
  CPPUNIT_ASSERT_EQUAL( 1, test.countTestCases() );
}


void 
TestCaseTest::testDefaultConstructor()
{
  CppUnit::TestCase test;
  CPPUNIT_ASSERT_EQUAL( std::string(""), test.getName() );
}


void 
TestCaseTest::testConstructorWithName()
{
  std::string testName( "TestName" );
  CppUnit::TestCase test( testName );
  CPPUNIT_ASSERT_EQUAL( testName, test.getName() );
}


void 
TestCaseTest::testDefaultRun()
{
  CppUnit::TestCase test;
  std::auto_ptr<CppUnit::TestResult> result( test.run() );

  checkResult( 0, 0, 1, result.get() );
}


void 
TestCaseTest::testTwoRun()
{
  FailingTestCase test1( false, true, false );
  test1.run( m_result );
  test1.run( m_result );
  
  FailingTestCase test2( false, false, false );
  test2.run( m_result );

  checkResult( 2, 0, 1, m_result );
}


void 
TestCaseTest::checkResult( int failures,
                           int errors,
                           int testsRun,
                           CppUnit::TestResult *result )
{
  CPPUNIT_ASSERT_EQUAL( testsRun, result->runTests() );
  CPPUNIT_ASSERT_EQUAL( errors, result->testErrors() );
  CPPUNIT_ASSERT_EQUAL( failures, result->testFailures() );
}
