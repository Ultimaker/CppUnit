#include <cmath>

#include "cppunit/TestAssert.h"
#include "estring.h"

namespace CppUnit {

/// Check for a failed general assertion 
void TestAssert::assertImplementation (bool          condition,
  std::string   conditionExpression,
  long          lineNumber,
  std::string   fileName)
{ 
  if (!condition) 
    throw Exception (conditionExpression, lineNumber, fileName); 
}


/// Check for a failed equality assertion 
void TestAssert::assertEquals (long        expected, 
  long        actual,
  long        lineNumber,
  std::string fileName)
{ 
  if (expected != actual) 
    assertImplementation (false, notEqualsMessage(expected, actual), lineNumber, fileName); 
}


/// Check for a failed equality assertion
void TestAssert::assertEquals (double        expected, 
  double        actual, 
  double        delta,
  long          lineNumber,
  std::string   fileName)
{ 
  if (fabs (expected - actual) > delta) 
    assertImplementation (false, notEqualsMessage(expected, actual), lineNumber, fileName); 

}


/// Build a message about a failed equality check 
std::string TestAssert::notEqualsMessage (long expected, long actual)
{ 
  return "expected: " + estring (expected) + " but was: " + estring (actual); 
}


/// Build a message about a failed equality check 
std::string TestAssert::notEqualsMessage (double expected, double actual)
{ 
  return "expected: " + estring (expected) + " but was: " + estring (actual); 
}

} // namespace TestAssert
