#include "TestSuiteTest.h"
#include "FailingTestCase.h"
#include <cppunit/TestResult.h>


CPPUNIT_TEST_SUITE_REGISTRATION( TestSuiteTest );


TestSuiteTest::TestSuiteTest()
{
}


TestSuiteTest::~TestSuiteTest()
{
}


void 
TestSuiteTest::setUp()
{
  m_suite = new CppUnit::TestSuite();
  m_result = new CppUnit::TestResult();
}


void 
TestSuiteTest::tearDown()
{
  delete m_result;
  delete m_suite;
}


void 
TestSuiteTest::testConstructor()
{
  std::string name( "MySuite" );
  CppUnit::TestSuite suite( name );
  CPPUNIT_ASSERT_EQUAL( name, suite.getName() );
}


void 
TestSuiteTest::testCountTestCasesWithNoTest()
{
  CPPUNIT_ASSERT_EQUAL( 0, m_suite->countTestCases() );
}


void 
TestSuiteTest::testCountTestCasesWithTwoTests()
{
  m_suite->addTest( new CppUnit::TestCase( "test1" ) );
  m_suite->addTest( new CppUnit::TestCase( "test2" ) );

  CPPUNIT_ASSERT_EQUAL( 2, m_suite->countTestCases() );
}


void 
TestSuiteTest::testCountTestCasesWithSubSuite()
{
  CppUnit::TestSuite *subSuite = new CppUnit::TestSuite( "SubSuite");
  subSuite->addTest( new CppUnit::TestCase( "test1" ) );
  subSuite->addTest( new CppUnit::TestCase( "test2" ) );

  m_suite->addTest( new CppUnit::TestCase( "test3" ) );
  m_suite->addTest( subSuite );

  CPPUNIT_ASSERT_EQUAL( 3, m_suite->countTestCases() );
}


void 
TestSuiteTest::testRunWithOneTest()
{
  FailingTestCase *test = new FailingTestCase();
  m_suite->addTest( test );

  m_suite->run( m_result );
  test->verify();
  checkResult( 0, 0, 1 );
}


void 
TestSuiteTest::testRunWithOneTestAndSubSuite()
{
  CppUnit::TestSuite *subSuite = new CppUnit::TestSuite( "SubSuite");
  
  FailingTestCase *test2 = new FailingTestCase();
  subSuite->addTest( test2 );

  FailingTestCase *test3 = new FailingTestCase();
  subSuite->addTest( test3 );

  FailingTestCase *test = new FailingTestCase();
  m_suite->addTest( test );
  m_suite->addTest( subSuite );

  m_suite->run( m_result );
  checkResult( 0, 0, 3 );
  test->verify();
  test2->verify();
  test3->verify();
}


void 
TestSuiteTest::testGetTests()
{
  m_suite->addTest( new CppUnit::TestCase( "test1" ) );
  m_suite->addTest( new CppUnit::TestCase( "test2" ) );
  CPPUNIT_ASSERT_EQUAL( 2, int(m_suite->getTests().size()) );
}


void 
TestSuiteTest::testDeleteContents()
{
  m_suite->addTest( new CppUnit::TestCase( "test2" ) );
  m_suite->deleteContents();
  CPPUNIT_ASSERT_EQUAL( 0, int(m_suite->getTests().size()) );
}


void 
TestSuiteTest::checkResult( int failures,
                            int errors,
                            int testsRun )
{
  CPPUNIT_ASSERT_EQUAL( testsRun, m_result->runTests() );
  CPPUNIT_ASSERT_EQUAL( errors, m_result->testErrors() );
  CPPUNIT_ASSERT_EQUAL( failures, m_result->testFailures() );
}
