#include "TestCallerTest.h"
#include <cppunit/extensions/TestSuiteBuilder.h>
#include <cppunit/extensions/HelperMacros.h>

CU_TEST_SUITE_REGISTRATION( TestCallerTest );


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
}


void 
TestCallerTest::tearDown()
{
  TrackedTestCase::removeTracker();
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

    caller.run();

    checkRunningSequenceCalled();
  } // Force destruction of the test caller.
  assertLongsEqual( 1, m_destructorCount );
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

    caller.run();

    checkRunningSequenceCalled();
  } // Force destruction of the test caller.
  assertLongsEqual( 0, m_destructorCount );
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

    caller.run();

    checkRunningSequenceCalled();
  } // Force destruction of the test caller.
  assertLongsEqual( 1, m_destructorCount );
}


void 
TestCallerTest::checkNothingButConstructorCalled()
{
  assertLongsEqual( 1, m_constructorCount );
  assertLongsEqual( 0, m_destructorCount );
  assertLongsEqual( 0, m_setUpCount );
  assertLongsEqual( 0, m_tearDownCount );
  assertLongsEqual( 0, m_testCount );
}


void 
TestCallerTest::checkRunningSequenceCalled()
{
  assertLongsEqual( 1, m_setUpCount );
  assertLongsEqual( 1, m_testCount );
  assertLongsEqual( 1, m_tearDownCount );
}


void 
TestCallerTest::checkTestName( std::string testName )
{
  assert( testName == m_testName );
}
