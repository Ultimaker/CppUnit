#include "TestAssertTest.h"

/*
 Note:
 - tests need to be added to test asserEquals() template function and
 use of assertion traits. Some check may need to be added to check
 the message content in Exception.
 - code need to be refactored with the use of a test caller that expect
 an exception.
 */


CPPUNIT_TEST_SUITE_REGISTRATION( TestAssertTest );


TestAssertTest::TestAssertTest()
{
}


TestAssertTest::~TestAssertTest()
{
}


void 
TestAssertTest::setUp()
{
}


void 
TestAssertTest::tearDown()
{
}

void 
TestAssertTest::testAssertTrue()
{
  CPPUNIT_ASSERT( true );
}


void 
TestAssertTest::testAssertFalse()
{
  bool exceptionCatched = false;
  try
  {
    CPPUNIT_ASSERT( false );
  }
  catch( CppUnit::Exception & )
  {
    exceptionCatched = true; // ok, we were expecting an exception.
  }

  CPPUNIT_ASSERT( exceptionCatched );
}


static int foo() { return 1; }


void 
TestAssertTest::testAssertEqual()
{
    CPPUNIT_ASSERT_EQUAL(1,1);
    CPPUNIT_ASSERT_EQUAL( 1, foo() );
}


void 
TestAssertTest::testAssertMessageTrue()
{
  CPPUNIT_ASSERT_MESSAGE( "This test should not failed", true );
}


void 
TestAssertTest::testAssertMessageFalse()
{
  bool exceptionCatched = false;
  std::string message( "This test message should not be seen" );
  try
  {
    CPPUNIT_ASSERT_MESSAGE( message, false );
  }
  catch( CppUnit::Exception &e )
  {
    CPPUNIT_ASSERT_EQUAL( message, std::string( e.what() ) );
    exceptionCatched = true; // ok, we were expecting an exception.
  }

  CPPUNIT_ASSERT( exceptionCatched );
}


void 
TestAssertTest::testAssertDoubleEquals()
{
  CPPUNIT_ASSERT_DOUBLES_EQUAL( 1.1, 1.2, 0.101 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( 1.2, 1.1, 0.101 );
}


void 
TestAssertTest::testAssertDoubleNotEquals()
{
  checkDoubleNotEquals( 1.1, 1.2, 0.09 );
  checkDoubleNotEquals( 1.2, 1.1, 0.09 );
}


void 
TestAssertTest::checkDoubleNotEquals( double expected, 
                                      double actual, 
                                      double delta )
{
  bool exceptionCatched = false;
  try
  {
    CPPUNIT_ASSERT_DOUBLES_EQUAL( expected, actual, delta );
  }
  catch( CppUnit::Exception & )
  {
    exceptionCatched = true; // ok, we were expecting an exception.
  }

  CPPUNIT_ASSERT( exceptionCatched );
}


void 
TestAssertTest::testAssertLongEquals()
{
  CPPUNIT_ASSERT_EQUAL( 12345678, 12345678 );
}


void 
TestAssertTest::testAssertLongNotEquals()
{
  bool exceptionCatched = false;
  try
  {
    CPPUNIT_ASSERT_EQUAL( 1, 2 );
  }
  catch( CppUnit::Exception & )
  {
    exceptionCatched = true; // ok, we were expecting an exception.
  }

  CPPUNIT_ASSERT( exceptionCatched );
}
