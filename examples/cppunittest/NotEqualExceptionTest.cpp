#include "NotEqualExceptionTest.h"
#include <cppunit/NotEqualException.h>


CPPUNIT_TEST_SUITE_REGISTRATION( NotEqualExceptionTest );


NotEqualExceptionTest::NotEqualExceptionTest()
{
}


NotEqualExceptionTest::~NotEqualExceptionTest()
{
}


void 
NotEqualExceptionTest::setUp()
{
}


void 
NotEqualExceptionTest::tearDown()
{
}



void 
NotEqualExceptionTest::testConstructor()
{
  std::string expectedValue( "expectedValue" );
  std::string actualValue( "actualValue" );
  CppUnit::NotEqualException e( expectedValue, actualValue );

  CPPUNIT_ASSERT_EQUAL( expectedValue, e.expectedValue() );
  CPPUNIT_ASSERT_EQUAL( actualValue, e.actualValue() );

  std::string expectedMessage( "Expected: expectedValue, but was: actualValue" );
  std::string actualMessage( e.what() );
  CPPUNIT_ASSERT_EQUAL( expectedMessage, actualMessage );
}


void 
NotEqualExceptionTest::testClone()
{
  CppUnit::NotEqualException e( "expectedValue", "actualValue" );
  std::auto_ptr<CppUnit::NotEqualException> 
      other( (CppUnit::NotEqualException *)e.clone() );
  CPPUNIT_ASSERT_EQUAL( std::string( e.what() ),
                        std::string( other->what() ) );
}


void 
NotEqualExceptionTest::testIsInstanceOf()
{
  CppUnit::NotEqualException e( "expectedValue", "actualValue" );
  CPPUNIT_ASSERT( e.isInstanceOf( CppUnit::NotEqualException::type() ) );
  CPPUNIT_ASSERT( e.isInstanceOf( CppUnit::Exception::type() ) );
}


void 
NotEqualExceptionTest::testAssignment()
{
  CppUnit::NotEqualException e( "expectedValue", "actualValue" );
  CppUnit::NotEqualException other( "", "" );
  other = e;
  CPPUNIT_ASSERT_EQUAL( std::string( e.what() ),
                        std::string( other.what() ) );
}
