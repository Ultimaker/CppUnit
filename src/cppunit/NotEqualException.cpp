#include <cppunit/NotEqualException.h>

namespace CppUnit {


NotEqualException::NotEqualException( std::string expected,
                                      std::string actual,
                                      long lineNumber, 
                                      std::string fileName ) : 
    Exception( "Expected: " + expected + ", but was: " + actual,
               lineNumber,
               fileName ),
    m_expected( expected ),
    m_actual( actual )
{
}


NotEqualException::NotEqualException( const NotEqualException &other ) : 
    Exception( other ),
    m_expected( other.m_expected ),
    m_actual( other.m_actual )
{
}


NotEqualException::~NotEqualException() throw()
{
}


NotEqualException &
NotEqualException::operator =( const NotEqualException &other )
{
  Exception::operator =( other );

  if ( &other != this )
  {
    m_expected = other.m_expected;
    m_actual = other.m_actual;
  }
  return *this;
}


Exception *
NotEqualException::clone() const
{
  return new NotEqualException( *this );
}


bool 
NotEqualException::isInstanceOf( const Type &exceptionType ) const
{
  return exceptionType == type()  ||
         Exception::isInstanceOf( exceptionType );
}


Exception::Type
NotEqualException::type()
{
  return Type( "CppUnit::NotEqualException" );
}


std::string 
NotEqualException::expectedValue() const
{
  return m_expected;
}


std::string 
NotEqualException::actualValue() const
{
  return m_actual;
}


}  //  namespace CppUnit
