#include "OrthodoxTest.h"
#include <cppunit/extensions/Orthodox.h>
#include <cppunit/TestResult.h>

CPPUNIT_TEST_SUITE_REGISTRATION( OrthodoxTest );

OrthodoxTest::OrthodoxTest()
{
}


OrthodoxTest::~OrthodoxTest()
{
}


void 
OrthodoxTest::setUp()
{
  m_result = new CppUnit::TestResult();
}


void 
OrthodoxTest::tearDown()
{
  delete m_result;
}


void 
OrthodoxTest::testValue()
{
  CppUnit::Orthodox<Value> test;
  test.run( m_result );
  checkSuccess();
}


void 
OrthodoxTest::testValueBadConstructor()
{
  CppUnit::Orthodox<ValueBadConstructor> test;
  test.run( m_result );
  checkFailure();
}


void 
OrthodoxTest::testValueBadInvert()
{
  CppUnit::Orthodox<ValueBadInvert> test;
  test.run( m_result );
  checkFailure();
}


void 
OrthodoxTest::testValueBadEqual()
{
  CppUnit::Orthodox<ValueBadEqual> test;
  test.run( m_result );
  checkFailure();
}


void 
OrthodoxTest::testValueBadNotEqual()
{
  CppUnit::Orthodox<ValueBadNotEqual> test;
  test.run( m_result );
  checkFailure();
}


void 
OrthodoxTest::testValueBadCall()
{
  CppUnit::Orthodox<ValueBadCall> test;
  test.run( m_result );
  checkFailure();
}


void 
OrthodoxTest::testValueBadAssignment()
{
  CppUnit::Orthodox<ValueBadAssignment> test;
  test.run( m_result );
  checkFailure();
}


void 
OrthodoxTest::checkSuccess()
{
  CPPUNIT_ASSERT_EQUAL( 0, m_result->testErrors() );
  CPPUNIT_ASSERT_EQUAL( 0, m_result->testFailures() );
  CPPUNIT_ASSERT( m_result->runTests() > 0 );
}


void 
OrthodoxTest::checkFailure()
{
  CPPUNIT_ASSERT( m_result->testErrors() > 0  ||  
                  m_result->testFailures() > 0 );
}

