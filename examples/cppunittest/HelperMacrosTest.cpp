#include "FailureException.h"
#include "HelperMacrosTest.h"
#include "HelperSuite.h"
#include "SubclassedTestCase.h"
#include <cppunit/TestResult.h>
#include <memory>

/* Note:
 - no unit test for CPPUNIT_TEST_SUITE_REGISTRATION...
 */

class FailTestCase : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE( FailTestCase );
  CPPUNIT_TEST_FAIL( testFail );
  CPPUNIT_TEST_SUITE_END();
public:
  void testFail()
  {
    CPPUNIT_ASSERT_MESSAGE( "Failure", false );
  }
};


class FailToFailTestCase : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE( FailToFailTestCase );
  CPPUNIT_TEST_FAIL( testFailToFail );
  CPPUNIT_TEST_SUITE_END();
public:
  void testFailToFail()
  {
  }
};


class ExceptionTestCase : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE( ExceptionTestCase );
  CPPUNIT_TEST_EXCEPTION( testException, FailureException );
  CPPUNIT_TEST_SUITE_END();
public:
  void testException()
  {
    throw FailureException();
  }
};


class ExceptionNotCaughtTestCase : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE( ExceptionNotCaughtTestCase );
  CPPUNIT_TEST_EXCEPTION( testExceptionNotCaught, FailureException );
  CPPUNIT_TEST_SUITE_END();
public:
  void testExceptionNotCaught()
  {
  }
};



CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( HelperMacrosTest, 
                                       CppUnitTest::helperSuiteName() );


HelperMacrosTest::HelperMacrosTest() : 
    CppUnit::TestCase()
{
}


HelperMacrosTest::~HelperMacrosTest()
{
}


void 
HelperMacrosTest::setUp()
{
  m_result = new CppUnit::TestResult();
}


void 
HelperMacrosTest::tearDown()
{
  delete m_result;
}


void 
HelperMacrosTest::testNoSubclassing()
{
  std::auto_ptr<CppUnit::TestSuite> suite( BaseTestCase::suite() );
  CPPUNIT_ASSERT_EQUAL( 1, suite->countTestCases() );

  suite->run( m_result );
  checkTestResult( 0,0,1 );
}


void 
HelperMacrosTest::testSubclassing()
{
  std::auto_ptr<CppUnit::TestSuite> suite( SubclassedTestCase::suite() );
  CPPUNIT_ASSERT_EQUAL( 2, suite->countTestCases() );

  suite->run( m_result );
  checkTestResult( 1,0,2 );
}


void 
HelperMacrosTest::testFail()
{
  std::auto_ptr<CppUnit::TestSuite> suite( FailTestCase::suite() );
  suite->run( m_result );
  checkTestResult( 0,0,1 );
}


void 
HelperMacrosTest::testFailToFail()
{
  std::auto_ptr<CppUnit::TestSuite> suite( FailToFailTestCase::suite() );
  suite->run( m_result );
  checkTestResult( 1,0,1 );
}


void 
HelperMacrosTest::testException()
{
  std::auto_ptr<CppUnit::TestSuite> suite( ExceptionTestCase::suite() );
  suite->run( m_result );
  checkTestResult( 0,0,1 );
}


void 
HelperMacrosTest::testExceptionNotCaught()
{
  std::auto_ptr<CppUnit::TestSuite> suite( ExceptionNotCaughtTestCase::suite() );
  suite->run( m_result );
  checkTestResult( 1,0,1 );
}


void 
HelperMacrosTest::checkTestResult( int expectedFailures, 
                                   int expectedErrors, 
                                   int expectedTestsRun )
{
  CPPUNIT_ASSERT_EQUAL( expectedFailures, m_result->testFailures() );
  CPPUNIT_ASSERT_EQUAL( expectedErrors, m_result->testErrors() );
  CPPUNIT_ASSERT_EQUAL( expectedTestsRun, m_result->runTests() );
}
