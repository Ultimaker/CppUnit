#include "CoreSuite.h"
#include "MockTestListener.h"
#include "TestListenerTest.h"
#include <cppunit/extensions/TestSuiteBuilder.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestResult.h>

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( TestListenerTest,
                                       CppUnitTest::coreSuiteName() );


TestListenerTest::TestListenerTest() : 
    CppUnit::TestCase()
{
}


TestListenerTest::~TestListenerTest()
{
}


CppUnit::TestSuite *
TestListenerTest::suite()
{
  CppUnit::TestSuiteBuilder<TestListenerTest> suite("TestListenerTest");

  suite.addTestCaller( "testNoListener", &TestListenerTest::testNoListener );
  suite.addTestCaller( "testAddErrorListener", 
                       &TestListenerTest::testAddErrorListener );
  suite.addTestCaller( "testAddFailureListener", 
                       &TestListenerTest::testAddFailureListener );
  suite.addTestCaller( "testStartTestListener", 
                       &TestListenerTest::testStartTestListener );
  suite.addTestCaller( "testEndTestListener", 
                       &TestListenerTest::testEndTestListener );
  suite.addTestCaller( "testRemoveFrontListener", 
                       &TestListenerTest::testRemoveFrontListener );
  suite.addTestCaller( "testRemoveLastListener", 
                       &TestListenerTest::testRemoveLastListener );

  return suite.takeSuite();
}


void 
TestListenerTest::setUp()
{
  m_listenerTest = NULL;
  m_listenerError = NULL;
  m_dummyTest = new CppUnit::TestCase( "DummyTest" );
  m_dummyError = NULL;
  m_listenerCallbackType = undefined;
  m_result = new CppUnit::TestResult();
  m_result->addListener( this );
}


void 
TestListenerTest::tearDown()
{
  m_result->removeListener( this );
  delete m_result;
  delete m_dummyTest;
}


void 
TestListenerTest::addFailure( CppUnit::TestFailure *failure )
{
  m_listenerTest = failure->failedTest();
  m_listenerError = failure->thrownException();
  m_listenerCallbackType = failure->isError() ? onAddError : 
                                                onAddFailure;
}


void 
TestListenerTest::startTest( CppUnit::Test *test )
{
  m_listenerTest = test;
  m_listenerCallbackType = onStartTest;
}


void 
TestListenerTest::endTest( CppUnit::Test *test )
{
  m_listenerTest = test;
  m_listenerCallbackType = onEndTest;
}


void 
TestListenerTest::testAddErrorListener()
{
  m_result->addError( m_dummyTest, makeDummyError() );
  CPPUNIT_ASSERT( m_listenerCallbackType == onAddError );
  CPPUNIT_ASSERT( m_listenerTest == m_dummyTest );
  CPPUNIT_ASSERT( m_listenerError == m_dummyError );
}


void 
TestListenerTest::testAddFailureListener()
{
  m_result->addFailure( m_dummyTest, makeDummyError() );
  CPPUNIT_ASSERT( m_listenerCallbackType == onAddFailure );
  CPPUNIT_ASSERT( m_listenerTest == m_dummyTest );
  CPPUNIT_ASSERT( m_listenerError == m_dummyError );
}


void 
TestListenerTest::testStartTestListener()
{
  m_result->startTest( m_dummyTest );
  CPPUNIT_ASSERT( m_listenerCallbackType == onStartTest );
  CPPUNIT_ASSERT( m_listenerTest == m_dummyTest );
}


void 
TestListenerTest::testEndTestListener()
{
  m_result->endTest( m_dummyTest );
  CPPUNIT_ASSERT( m_listenerCallbackType == onEndTest );
  CPPUNIT_ASSERT( m_listenerTest == m_dummyTest );
}


CppUnit::Exception *
TestListenerTest::makeDummyError()
{
  m_dummyError = new CppUnit::Exception( "dummy exception" );
  return m_dummyError;
}


void 
TestListenerTest::testNoListener()
{
  CppUnit::TestResult result;
  result.addError( m_dummyTest, makeDummyError() );
  result.addFailure( m_dummyTest, makeDummyError() );
  result.startTest( m_dummyTest );
  result.endTest( m_dummyTest );
}


void 
TestListenerTest::testTwoListener()
{
  MockTestListener listener;
  m_result->addListener( &listener );
  m_result->startTest( m_dummyTest );
  CPPUNIT_ASSERT( m_listenerCallbackType == onStartTest );
  CPPUNIT_ASSERT( listener.wasCalled() );
}


void 
TestListenerTest::testRemoveFrontListener()
{
  MockTestListener listener;
  m_result->addListener( &listener );
  m_result->removeListener( &listener );
  m_result->startTest( m_dummyTest );
  CPPUNIT_ASSERT( m_listenerCallbackType == onStartTest );
  CPPUNIT_ASSERT( !listener.wasCalled() );
}


void 
TestListenerTest::testRemoveLastListener()
{
  MockTestListener listener;
  m_result->addListener( &listener );

  m_result->removeListener( this );
  m_result->startTest( m_dummyTest );
  CPPUNIT_ASSERT( m_listenerCallbackType == undefined );
  CPPUNIT_ASSERT( listener.wasCalled() );
}
