#include "cppunit/TestFailure.h"
#include "cppunit/Exception.h"
#include "cppunit/Test.h"

namespace CppUnit {

/// Returns a short description of the failure.
std::string 
TestFailure::toString () const 
{ 
  return m_failedTest->toString () + ": " + m_thrownException->what ();
}

/// Constructs a TestFailure with the given test and exception.
TestFailure::TestFailure (Test *failedTest, Exception *thrownException)
  : m_failedTest (failedTest), m_thrownException (thrownException) 
{
}

/// Deletes the owned exception.
TestFailure::~TestFailure ()
{ 
  delete m_thrownException; 
}

} // namespace CppUnit
