#include "TestFailureTest.h"
#include <cppunit/TestFailure.h>
#include <cppunit/Exception.h>


CPPUNIT_TEST_SUITE_REGISTRATION( TestFailureTest );


TestFailureTest::TestFailureTest()
{
}


TestFailureTest::~TestFailureTest()
{
}


void 
TestFailureTest::setUp()
{
  m_exceptionDestroyed = false;
}


void 
TestFailureTest::tearDown()
{
}


void 
TestFailureTest::testConstructorAndGetters()
{
  CppUnit::TestCase test;
  CppUnit::Exception *error = new ObservedException( this );
  checkTestFailure( &test, error );
  CPPUNIT_ASSERT( m_exceptionDestroyed );
}


void 
TestFailureTest::exceptionDestroyed()
{
  m_exceptionDestroyed = true;
}


void 
TestFailureTest::checkTestFailure( CppUnit::Test *test, 
                                   CppUnit::Exception *error )
{
  CppUnit::TestFailure failure( test, error );
  CPPUNIT_ASSERT_EQUAL( test, failure.failedTest() );
  CPPUNIT_ASSERT_EQUAL( error, failure.thrownException() );
}
