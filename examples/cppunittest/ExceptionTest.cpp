#include "ExceptionTest.h"
#include <cppunit/Exception.h>
#include <cppunit/NotEqualException.h>
#include <memory>


CPPUNIT_TEST_SUITE_REGISTRATION( ExceptionTest );


ExceptionTest::ExceptionTest()
{
}


ExceptionTest::~ExceptionTest()
{
}


void 
ExceptionTest::setUp()
{
}


void 
ExceptionTest::tearDown()
{
}


void 
ExceptionTest::testConstructor()
{
  const std::string message( "a message" );
  const int lineNumber = 17;
  const std::string fileName( "dir/afile.cpp" );
  
  CppUnit::Exception e( message, lineNumber, fileName  );

  CPPUNIT_ASSERT_EQUAL( message, std::string( e.what() ) );
  CPPUNIT_ASSERT_EQUAL( lineNumber, int(e.lineNumber()) );
  CPPUNIT_ASSERT_EQUAL( fileName, e.fileName() );
}


void 
ExceptionTest::testDefaultConstructor()
{
  CppUnit::Exception e;

  CPPUNIT_ASSERT_EQUAL( std::string(""), std::string( e.what() ) );
  CPPUNIT_ASSERT_EQUAL( CppUnit::Exception::UNKNOWNLINENUMBER, 
                        e.lineNumber() );
  CPPUNIT_ASSERT_EQUAL( CppUnit::Exception::UNKNOWNFILENAME, 
                        e.fileName() );
}


void 
ExceptionTest::testCopyConstructor()
{
  CppUnit::Exception e( "message", 17, "fileName.cpp"  );
  CppUnit::Exception other( e );
  checkIsSame( e, other );
}


void 
ExceptionTest::testAssignment()
{
  CppUnit::Exception e( "message", 17, "fileName.cpp"  );
  CppUnit::Exception other;
  other = e;
  checkIsSame( e, other );
}


void 
ExceptionTest::testClone()
{
  CppUnit::Exception e( "message", 17, "fileName.cpp"  );
  std::auto_ptr<CppUnit::Exception> other( e.clone() );
  checkIsSame( e, *other.get() );
}


void 
ExceptionTest::testIsInstanceOf()
{
  CppUnit::Exception e( "message", 17, "fileName.cpp"  );
  CPPUNIT_ASSERT( e.isInstanceOf( CppUnit::Exception::type() ) );
  CPPUNIT_ASSERT( !e.isInstanceOf( CppUnit::NotEqualException::type() ) );
}


void 
ExceptionTest::checkIsSame( CppUnit::Exception &e, 
                            CppUnit::Exception &other )
{
  std::string eWhat( e.what() );
  std::string otherWhat( other.what() );
  CPPUNIT_ASSERT_EQUAL( eWhat, otherWhat );
  CPPUNIT_ASSERT_EQUAL( e.lineNumber(), other.lineNumber() );
  CPPUNIT_ASSERT_EQUAL( e.fileName(), other.fileName() );
}
