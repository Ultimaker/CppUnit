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
    throw Exception (conditionExpression, 
                     lineNumber,
                     fileName); 
}


/// Check for a failed equality assertion
void TestAssert::assertEquals (double        expected, 
  double        actual, 
  double        delta,
  long          lineNumber,
  std::string   fileName)
{ 
  if (fabs (expected - actual) > delta) 
    assertImplementation (false, 
                          notEqualsMessage(expected, actual), 
                          lineNumber, 
                          fileName); 
}


} // namespace TestAssert
