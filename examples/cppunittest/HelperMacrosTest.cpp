#include "HelperMacrosTest.h"
#include "SubclassedTestCase.h"
#include <cppunit/TestResult.h>
#include <memory>

/* Note:
 - no unit test for CPPUNIT_TEST_SUITE_REGISTRATION...
 */


CPPUNIT_TEST_SUITE_REGISTRATION( HelperMacrosTest );


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
HelperMacrosTest::checkTestResult( int expectedFailures, 
                                   int expectedErrors, 
                                   int expectedTestsRun )
{
  CPPUNIT_ASSERT_EQUAL( expectedFailures, m_result->testFailures() );
  CPPUNIT_ASSERT_EQUAL( expectedErrors, m_result->testErrors() );
  CPPUNIT_ASSERT_EQUAL( expectedTestsRun, m_result->runTests() );
}
