#include "Exception.h"

using namespace CppUnit;

const std::string 
CppUnit::Exception::UNKNOWNFILENAME = 
  "<unknown>";
const int CppUnit::Exception::UNKNOWNLINENUMBER = -1;

/// Construct the exception
CppUnit::Exception::Exception (const Exception& other)
  : exception (other)
{ 
  m_message       = other.m_message; 
  m_lineNumber    = other.m_lineNumber;
  m_fileName      = other.m_fileName;
} 

CppUnit::Exception::Exception (std::string message, long lineNumber, std::string fileName)
  : m_message (message), m_lineNumber (lineNumber), m_fileName (fileName)
{}


/// Destruct the exception
CppUnit::Exception::~Exception ()
{}


/// Perform an assignment
Exception& 
CppUnit::Exception::operator= (const Exception& other)
{ 
  exception::operator= (other);

  if (&other != this) {
    m_message       = other.m_message; 
    m_lineNumber    = other.m_lineNumber;
    m_fileName      = other.m_fileName;
  }

  return *this; 
}


/// Return descriptive message
const char*
CppUnit::Exception::what() const throw ()
{ return m_message.c_str (); }

/// The line on which the error occurred
long 
CppUnit::Exception::lineNumber ()
{ return m_lineNumber; }


/// The file in which the error occurred
std::string 
CppUnit::Exception::fileName ()
{ return m_fileName; }

