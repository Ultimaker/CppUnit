#include "TestResultTest.h"
#include <cppunit/extensions/TestSuiteBuilder.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestResult.h>
#include "MockTestListener.h"

CU_TEST_SUITE_REGISTRATION( TestResultTest );


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
  CppUnit::TestSuiteBuilder<TestResultTest> suite;

  suite.addTestCaller( "testNoListener", &testNoListener );
  suite.addTestCaller( "testAddErrorListener", &testAddErrorListener );
  suite.addTestCaller( "testAddFailureListener", &testAddFailureListener );
  suite.addTestCaller( "testStartTestListener", &testStartTestListener );
  suite.addTestCaller( "testEndTestListener", &testEndTestListener );
  suite.addTestCaller( "testRemoveFrontListener", &testRemoveFrontListener );
  suite.addTestCaller( "testRemoveLastListener", &testRemoveLastListener );

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
  assert( m_listenerCallbackType == onAddError );
  assert( m_listenerTest == m_dummyTest );
  assert( m_listenerError == m_dummyError );
}


void 
TestResultTest::testAddFailureListener()
{
  m_result->addFailure( m_dummyTest, makeDummyError() );
  assert( m_listenerCallbackType == onAddFailure );
  assert( m_listenerTest == m_dummyTest );
  assert( m_listenerError == m_dummyError );
}


void 
TestResultTest::testStartTestListener()
{
  m_result->startTest( m_dummyTest );
  assert( m_listenerCallbackType == onStartTest );
  assert( m_listenerTest == m_dummyTest );
}


void 
TestResultTest::testEndTestListener()
{
  m_result->endTest( m_dummyTest );
  assert( m_listenerCallbackType == onEndTest );
  assert( m_listenerTest == m_dummyTest );
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
  assert( m_listenerCallbackType == onStartTest );
  assert( listener.wasCalled() );
}


void 
TestResultTest::testRemoveFrontListener()
{
  MockTestListener listener;
  m_result->addListener( &listener );
  m_result->removeListener( &listener );
  m_result->startTest( m_dummyTest );
  assert( m_listenerCallbackType == onStartTest );
  assert( !listener.wasCalled() );
}


void 
TestResultTest::testRemoveLastListener()
{
  MockTestListener listener;
  m_result->addListener( &listener );

  m_result->removeListener( this );
  m_result->startTest( m_dummyTest );
  assert( m_listenerCallbackType == undefined );
  assert( listener.wasCalled() );
}
