#include "TestResultTest.h"
#include <cppunit/extensions/TestSuiteBuilder.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestResult.h>
#include "MockTestListener.h"

CPPUNIT_TEST_SUITE_REGISTRATION( TestResultTest );


TestResultTest::TestResultTest() : 
    CppUnit::TestCase()
{
}


TestResultTest::~TestResultTest()
{
}


CppUnit::TestSuite *
TestResultTest::suite()
{
  CppUnit::TestSuiteBuilder<TestResultTest> suite("TestResultTest");

  suite.addTestCaller( "testNoListener", &TestResultTest::testNoListener );
  suite.addTestCaller( "testAddErrorListener", 
                       &TestResultTest::testAddErrorListener );
  suite.addTestCaller( "testAddFailureListener", 
                       &TestResultTest::testAddFailureListener );
  suite.addTestCaller( "testStartTestListener", 
                       &TestResultTest::testStartTestListener );
  suite.addTestCaller( "testEndTestListener", 
                       &TestResultTest::testEndTestListener );
  suite.addTestCaller( "testRemoveFrontListener", 
                       &TestResultTest::testRemoveFrontListener );
  suite.addTestCaller( "testRemoveLastListener", 
                       &TestResultTest::testRemoveLastListener );

  return suite.takeSuite();
}


void 
TestResultTest::setUp()
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
TestResultTest::tearDown()
{
  m_result->removeListener( this );
  delete m_result;
  delete m_dummyTest;
}


void 
TestResultTest::addError( CppUnit::Test *test, CppUnit::Exception *e )
{
  m_listenerTest = test;
  m_listenerError = e;
  m_listenerCallbackType = onAddError;
}


void 
TestResultTest::addFailure( CppUnit::Test *test, CppUnit::Exception *e )
{
  m_listenerTest = test;
  m_listenerError = e;
  m_listenerCallbackType = onAddFailure;
}

void 
TestResultTest::startTest( CppUnit::Test *test )
{
  m_listenerTest = test;
  m_listenerCallbackType = onStartTest;
}


void 
TestResultTest::endTest( CppUnit::Test *test )
{
  m_listenerTest = test;
  m_listenerCallbackType = onEndTest;
}


void 
TestResultTest::testAddErrorListener()
{
  m_result->addError( m_dummyTest, makeDummyError() );
  CPPUNIT_ASSERT( m_listenerCallbackType == onAddError );
  CPPUNIT_ASSERT( m_listenerTest == m_dummyTest );
  CPPUNIT_ASSERT( m_listenerError == m_dummyError );
}


void 
TestResultTest::testAddFailureListener()
{
  m_result->addFailure( m_dummyTest, makeDummyError() );
  CPPUNIT_ASSERT( m_listenerCallbackType == onAddFailure );
  CPPUNIT_ASSERT( m_listenerTest == m_dummyTest );
  CPPUNIT_ASSERT( m_listenerError == m_dummyError );
}


void 
TestResultTest::testStartTestListener()
{
  m_result->startTest( m_dummyTest );
  CPPUNIT_ASSERT( m_listenerCallbackType == onStartTest );
  CPPUNIT_ASSERT( m_listenerTest == m_dummyTest );
}


void 
TestResultTest::testEndTestListener()
{
  m_result->endTest( m_dummyTest );
  CPPUNIT_ASSERT( m_listenerCallbackType == onEndTest );
  CPPUNIT_ASSERT( m_listenerTest == m_dummyTest );
}


CppUnit::Exception *
TestResultTest::makeDummyError()
{
  m_dummyError = new CppUnit::Exception( "dummy exception" );
  return m_dummyError;
}


void 
TestResultTest::testNoListener()
{
  CppUnit::TestResult result;
  result.addError( m_dummyTest, makeDummyError() );
  result.addFailure( m_dummyTest, makeDummyError() );
  result.startTest( m_dummyTest );
  result.endTest( m_dummyTest );
}


void 
TestResultTest::testTwoListener()
{
  MockTestListener listener;
  m_result->addListener( &listener );
  m_result->startTest( m_dummyTest );
  CPPUNIT_ASSERT( m_listenerCallbackType == onStartTest );
  CPPUNIT_ASSERT( listener.wasCalled() );
}


void 
TestResultTest::testRemoveFrontListener()
{
  MockTestListener listener;
  m_result->addListener( &listener );
  m_result->removeListener( &listener );
  m_result->startTest( m_dummyTest );
  CPPUNIT_ASSERT( m_listenerCallbackType == onStartTest );
  CPPUNIT_ASSERT( !listener.wasCalled() );
}


void 
TestResultTest::testRemoveLastListener()
{
  MockTestListener listener;
  m_result->addListener( &listener );

  m_result->removeListener( this );
  m_result->startTest( m_dummyTest );
  CPPUNIT_ASSERT( m_listenerCallbackType == undefined );
  CPPUNIT_ASSERT( listener.wasCalled() );
}
