#include "TestResultTest.h"
#include <cppunit/TestResult.h>

/* Note:
 - the TestListener part of TestResult is tested in TestListenerTest.
 - bug identified: errors() and failures() are synchronized but returns
   reference! No unit test for that one (need multihread...).
 */


CPPUNIT_TEST_SUITE_REGISTRATION( TestResultTest );


TestResultTest::TestResultTest()
{
}


TestResultTest::~TestResultTest()
{
}


void 
TestResultTest::setUp()
{
  m_lockCount = 0;
  m_unlockCount = 0;
  m_result = new CppUnit::TestResult();
  m_synchronizedResult = new SynchronizedTestResult( this );  
  m_test = new CppUnit::TestCase();
  m_test2 = new CppUnit::TestCase();
}


void 
TestResultTest::tearDown()
{
  delete m_test2;
  delete m_test;
  delete m_synchronizedResult;
  delete m_result;
}


void 
TestResultTest::testConstructor()
{
  checkResult( 0, 0, 0 );
  CPPUNIT_ASSERT( !m_result->shouldStop() );
}


void 
TestResultTest::testStop()
{
  m_result->stop();
  CPPUNIT_ASSERT( m_result->shouldStop() );
}


void 
TestResultTest::testAddTwoErrors()
{
  std::string errorMessage1( "First Error" );
  m_result->addError( m_test, new CppUnit::Exception( errorMessage1 ) );

  std::string errorMessage2( "Second Error" );
  m_result->addError( m_test2, new CppUnit::Exception( errorMessage2 ) );
  checkResult( 0, 2, 0 );
  checkFailure( m_result->errors().at(0),
                errorMessage1,
                m_test );
  checkFailure( m_result->errors().at(1),
                errorMessage2,
                m_test2 );
}


void 
TestResultTest::testAddTwoFailures()
{
  std::string errorMessage1( "First Failure" );
  m_result->addFailure( m_test, new CppUnit::Exception( errorMessage1 ) );

  std::string errorMessage2( "Second Failure" );
  m_result->addFailure( m_test2, new CppUnit::Exception( errorMessage2 ) );
  checkResult( 2, 0, 0 );
  checkFailure( m_result->failures().at(0),
                errorMessage1,
                m_test );
  checkFailure( m_result->failures().at(1),
                errorMessage2,
                m_test2 );
}


void 
TestResultTest::testStartTest()
{
  m_result->startTest( m_test );
  m_result->startTest( m_test );
  checkResult( 0, 0, 2 );
}


void 
TestResultTest::testEndTest()
{
  // It doesn't actually do anything beyond TestListener stuffs...
}


void 
TestResultTest::testWasSuccessfulWithNoTest()
{
  checkWasSuccessful( true );
}


void 
TestResultTest::testWasSuccessfulWithErrors()
{
  m_result->addError( m_test, new CppUnit::Exception( "Error1" ) );
  m_result->addError( m_test, new CppUnit::Exception( "Error2" ) );
  checkWasSuccessful( false );
}


void 
TestResultTest::testWasSuccessfulWithFailures()
{
  m_result->addFailure( m_test, new CppUnit::Exception( "Failure1" ) );
  m_result->addFailure( m_test, new CppUnit::Exception( "Failure2" ) );
  checkWasSuccessful( false );
}


void 
TestResultTest::testWasSuccessfulWithErrorsAndFailures()
{
  m_result->addError( m_test, new CppUnit::Exception( "Error1" ) );
  m_result->addFailure( m_test, new CppUnit::Exception( "Failure2" ) );
  checkWasSuccessful( false );
}


void 
TestResultTest::testWasSuccessfulWithSucessfulTest()
{
  m_result->startTest( m_test );
  m_result->endTest( m_test );
  m_result->startTest( m_test2 );
  m_result->endTest( m_test2 );
  checkWasSuccessful( true );
}


void 
TestResultTest::testSynchronizationAddError()
{
  m_synchronizedResult->addError( m_test, new CppUnit::Exception( "Error1" ) );
  checkSynchronization();
}


void 
TestResultTest::testSynchronizationAddFailure()
{
  m_synchronizedResult->addFailure( m_test, new CppUnit::Exception( "Failure1" ) );
  checkSynchronization();
}


void 
TestResultTest::testSynchronizationStartTest()
{
  m_synchronizedResult->startTest( m_test );
  checkSynchronization();
}


void 
TestResultTest::testSynchronizationEndTest()
{
  m_synchronizedResult->endTest( m_test );
  checkSynchronization();
}


void 
TestResultTest::testSynchronizationRunTests()
{
  m_synchronizedResult->runTests();
  checkSynchronization();
}


void 
TestResultTest::testSynchronizationTestErrors()
{
  m_synchronizedResult->testErrors();
  checkSynchronization();
}


void 
TestResultTest::testSynchronizationTestFailures()
{
  m_synchronizedResult->testFailures();
  checkSynchronization();
}


void 
TestResultTest::testSynchronizationErrors()
{
  m_synchronizedResult->errors();
  checkSynchronization();
}


void 
TestResultTest::testSynchronizationFailures()
{
  m_synchronizedResult->failures();
  checkSynchronization();
}


void 
TestResultTest::testSynchronizationWasSuccessful()
{
  m_synchronizedResult->wasSuccessful();
  checkSynchronization();
}


void 
TestResultTest::testSynchronizationShouldStop()
{
  m_synchronizedResult->shouldStop();
  checkSynchronization();
}


void 
TestResultTest::testSynchronizationStop()
{
  m_synchronizedResult->stop();
  checkSynchronization();
}


void 
TestResultTest::checkResult( int failures,
                             int errors,
                             int testsRun )
{
  CPPUNIT_ASSERT_EQUAL( testsRun, m_result->runTests() );
  CPPUNIT_ASSERT_EQUAL( errors, m_result->testErrors() );
  CPPUNIT_ASSERT_EQUAL( failures, m_result->testFailures() );
}


void
TestResultTest::checkFailure( CppUnit::TestFailure *failure,
                              std::string expectedMessage,
                              CppUnit::Test *expectedTest )
{
  std::string actualMessage( failure->thrownException()->what() );
  CPPUNIT_ASSERT_EQUAL( expectedMessage, actualMessage );
  CPPUNIT_ASSERT_EQUAL( expectedTest, failure->failedTest() );
}


void 
TestResultTest::checkWasSuccessful( bool shouldBeSuccessful )
{
  CPPUNIT_ASSERT_EQUAL( shouldBeSuccessful, m_result->wasSuccessful() );
}


void 
TestResultTest::locked()
{
  CPPUNIT_ASSERT_EQUAL( m_lockCount, m_unlockCount );
  ++m_lockCount;
}


void 
TestResultTest::unlocked()
{
  ++m_unlockCount;
  CPPUNIT_ASSERT_EQUAL( m_lockCount, m_unlockCount );
}


void 
TestResultTest::checkSynchronization()
{
  CPPUNIT_ASSERT_EQUAL( m_lockCount, m_unlockCount );
  CPPUNIT_ASSERT( m_lockCount > 0 );
}
