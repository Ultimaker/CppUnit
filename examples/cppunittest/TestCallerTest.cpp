#include "FailureException.h"
#include "HelperSuite.h"
#include "TestCallerTest.h"
#include <cppunit/extensions/TestSuiteBuilder.h>
#include <cppunit/extensions/HelperMacros.h>


CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( TestCallerTest, 
                                       CppUnitTest::helperSuiteName() );


void 
TestCallerTest::ExceptionThrower::testThrowFailureException()
{
  throw FailureException();
}


void 
TestCallerTest::ExceptionThrower::testThrowException()
{
  throw CppUnit::Exception( "expected Exception" );
}


void 
TestCallerTest::ExceptionThrower::testThrowNothing()
{
}



TestCallerTest::TestCallerTest() : 
    m_testName( "TrackedTestCaseCaller" )
{
}


TestCallerTest::~TestCallerTest()
{
}


CppUnit::TestSuite *
TestCallerTest::suite()
{
  CppUnit::TestSuiteBuilder<TestCallerTest> suite("TestCallerTest");

  suite.addTestCaller( "testBasicConstructor", &TestCallerTest::testBasicConstructor );
  suite.addTestCaller( "testReferenceConstructor", &TestCallerTest::testReferenceConstructor );
  suite.addTestCaller( "testPointerConstructor", &TestCallerTest::testPointerConstructor );
  suite.addTestCaller( "testExpectFailureException", &TestCallerTest::testExpectFailureException );
  suite.addTestCaller( "testExpectException", &TestCallerTest::testExpectException );
  suite.addTestCaller( "testExpectedExceptionNotCaught", &TestCallerTest::testExpectedExceptionNotCaught );

  return suite.takeSuite();
}


void 
TestCallerTest::setUp()
{
  m_constructorCount = 0;
  m_destructorCount = 0;
  m_setUpCount = 0;
  m_tearDownCount = 0;
  m_testCount = 0;
  TrackedTestCase::setTracker( this );
  m_result = new CppUnit::TestResult();
}


void 
TestCallerTest::tearDown()
{
  TrackedTestCase::removeTracker();
  delete m_result;
}


void 
TestCallerTest::onConstructor()
{
  m_constructorCount++;
}


void 
TestCallerTest::onDestructor()
{
  m_destructorCount++;
}


void 
TestCallerTest::onSetUp()
{
  m_setUpCount++;
}


void 
TestCallerTest::onTearDown()
{
  m_tearDownCount++;
}


void 
TestCallerTest::onTest()
{
  m_testCount++;
}


void 
TestCallerTest::testBasicConstructor()
{
  {
    CppUnit::TestCaller<TrackedTestCase> caller( m_testName, 
                                                 &TrackedTestCase::test );
    checkTestName( caller.getName() );
    checkNothingButConstructorCalled();

    caller.run( m_result );

    checkRunningSequenceCalled();
  } // Force destruction of the test caller.
  CPPUNIT_ASSERT_EQUAL( 1, m_destructorCount );
}


void 
TestCallerTest::testReferenceConstructor()
{
  TrackedTestCase testCase;
  {
    CppUnit::TestCaller<TrackedTestCase> caller( "TrackedTestCaseCaller", 
                                                 &TrackedTestCase::test, 
                                                 testCase );
    checkTestName( caller.getName() );
    checkNothingButConstructorCalled();

    caller.run( m_result );

    checkRunningSequenceCalled();
  } // Force destruction of the test caller.
  CPPUNIT_ASSERT_EQUAL( 0, m_destructorCount );
}


void 
TestCallerTest::testPointerConstructor()
{
  TrackedTestCase *testCase = new TrackedTestCase();
  {
    CppUnit::TestCaller<TrackedTestCase> caller( m_testName, 
                                                 &TrackedTestCase::test, 
                                                 testCase );
    checkTestName( caller.getName() );
    checkNothingButConstructorCalled();

    caller.run( m_result );

    checkRunningSequenceCalled();
  } // Force destruction of the test caller.
  CPPUNIT_ASSERT_EQUAL( 1, m_destructorCount );
}


void 
TestCallerTest::testExpectFailureException()
{
  CppUnit::TestCaller<ExceptionThrower,FailureException> caller( 
      m_testName,
      &ExceptionThrower::testThrowFailureException );
  caller.run( m_result );
  CPPUNIT_ASSERT( m_result->wasSuccessful() );
}


void 
TestCallerTest::testExpectException()
{
  CppUnit::TestCaller<ExceptionThrower,CppUnit::Exception> caller( 
      m_testName,
      &ExceptionThrower::testThrowException );
  caller.run( m_result );
  CPPUNIT_ASSERT( m_result->wasSuccessful() );
}


void 
TestCallerTest::testExpectedExceptionNotCaught()
{
  CppUnit::TestCaller<ExceptionThrower,FailureException> caller( 
      m_testName,
      &ExceptionThrower::testThrowNothing );
  caller.run( m_result );
  CPPUNIT_ASSERT( !m_result->wasSuccessful() );
  CPPUNIT_ASSERT_EQUAL( 1, int(m_result->failures().size()) );
// Can differentiate throw 'new Exception' from throw 'Exception'
// only by text message which is unsafe.
// Possible solution: subclass Exception:
//  CppUnit::Exception *e = m_result->failues()[0]->thrownException();
//  CPPUNIT_ASSERT( e->isInstanceOf( FailureException::type() ) );
}


void 
TestCallerTest::checkNothingButConstructorCalled()
{
  CPPUNIT_ASSERT_EQUAL( 1, m_constructorCount );
  CPPUNIT_ASSERT_EQUAL( 0, m_destructorCount );
  CPPUNIT_ASSERT_EQUAL( 0, m_setUpCount );
  CPPUNIT_ASSERT_EQUAL( 0, m_tearDownCount );
  CPPUNIT_ASSERT_EQUAL( 0, m_testCount );
}


void 
TestCallerTest::checkRunningSequenceCalled()
{
  CPPUNIT_ASSERT_EQUAL( 1, m_setUpCount );
  CPPUNIT_ASSERT_EQUAL( 1, m_testCount );
  CPPUNIT_ASSERT_EQUAL( 1, m_tearDownCount );
}


void 
TestCallerTest::checkTestName( std::string testName )
{
  CPPUNIT_ASSERT( testName == m_testName );
}
