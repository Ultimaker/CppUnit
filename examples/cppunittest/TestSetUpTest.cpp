#include "TestSetUpTest.h"
#include <cppunit/TestResult.h>

CPPUNIT_TEST_SUITE_REGISTRATION( TestSetUpTest );


TestSetUpTest::TestSetUpTest()
{
}


TestSetUpTest::~TestSetUpTest()
{
}


void 
TestSetUpTest::setUp()
{
  m_test = new FailingTestCase();
  m_setUp = new SetUp( m_test );
}


void 
TestSetUpTest::tearDown()
{
  delete m_setUp;
  delete m_test;
}


void 
TestSetUpTest::testRun()
{
  CppUnit::TestResult result;
  m_setUp->run( &result );
  CPPUNIT_ASSERT( m_setUp->m_setUpCalled );
  CPPUNIT_ASSERT( m_setUp->m_tearDownCalled );
}
