#include "TestDecoratorTest.h"
#include "FailingTestCase.h"
#include <cppunit/TestResult.h>


CPPUNIT_TEST_SUITE_REGISTRATION( TestDecoratorTest );


TestDecoratorTest::TestDecoratorTest()
{
}


TestDecoratorTest::~TestDecoratorTest()
{
}


void 
TestDecoratorTest::setUp()
{
  m_test = new FailingTestCase();
  m_decorator = new CppUnit::TestDecorator( m_test );
}


void 
TestDecoratorTest::tearDown()
{
  delete m_decorator;
  delete m_test;
}


void 
TestDecoratorTest::testCountTestCases()
{
  CPPUNIT_ASSERT_EQUAL( 1, m_decorator->countTestCases() );
}


void 
TestDecoratorTest::testRun()
{
  CppUnit::TestResult result;
  m_decorator->run( &result );
  m_test->verify();
}


void 
TestDecoratorTest::testGetName()
{
  CPPUNIT_ASSERT_EQUAL( m_test->getName(), m_decorator->getName() );
}
