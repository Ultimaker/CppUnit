#include "cppunit/Exception.h"
#include "cppunit/Test.h"
#include "cppunit/TestFailure.h"

namespace CppUnit {

/// Constructs a TestFailure with the given test and exception.
TestFailure::TestFailure( Test *failedTest, 
                          Exception *thrownException,
                          bool isError ) :
    m_failedTest( failedTest ), 
    m_thrownException( thrownException ),
    m_isError( isError )
{
}

/// Deletes the owned exception.
TestFailure::~TestFailure()
{ 
  delete m_thrownException; 
}

/// Gets the failed test.
Test *
TestFailure::failedTest() const
{ 
  return m_failedTest; 
}


/// Gets the thrown exception. Never \c NULL.
Exception *
TestFailure::thrownException() const
{ 
  return m_thrownException; 
}


/// Indicates if the failure is a failed assertion or an error.
bool 
TestFailure::isError() const
{
  return m_isError;
}

/// Returns a short description of the failure.
std::string 
TestFailure::toString() const 
{ 
  return m_failedTest->toString() + ": " + m_thrownException->what();
}

} // namespace CppUnit
