#include "cppunit/Exception.h"


namespace CppUnit {


const std::string Exception::UNKNOWNFILENAME = "<unknown>";

const long Exception::UNKNOWNLINENUMBER = -1;


/// Construct the exception
Exception::Exception (const Exception& other) : std::exception (other)
{ 
  m_message       = other.m_message; 
  m_lineNumber    = other.m_lineNumber;
  m_fileName      = other.m_fileName;
} 


Exception::Exception( std::string message, 
                      long lineNumber, 
                      std::string fileName ) : 
    m_message( message ), 
    m_lineNumber( lineNumber ), 
    m_fileName( fileName )
{
}


/// Destruct the exception
Exception::~Exception () throw()
{
}


/// Perform an assignment
Exception& 
Exception::operator=( const Exception& other )
{ 
  SuperClass::operator= (other);

  if (&other != this) 
  {
    m_message       = other.m_message; 
    m_lineNumber    = other.m_lineNumber;
    m_fileName      = other.m_fileName;
  }

  return *this; 
}


/// Return descriptive message
const char*
Exception::what() const throw ()
{ 
  return m_message.c_str (); 
}


/// The line on which the error occurred
long 
Exception::lineNumber()
{ 
  return m_lineNumber; 
}


/// The file in which the error occurred
std::string 
Exception::fileName()
{ 
  return m_fileName; 
}


Exception *
Exception::clone() const
{
  return new Exception( *this );
}


bool 
Exception::isInstanceOf( const Type &exceptionType ) const
{
  return exceptionType == type();
}


Exception::Type
Exception::type()
{
  return Type( "CppUnit::Exception" );
}


}  // namespace CppUnit
