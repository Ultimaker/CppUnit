#if HAVE_CMATH
#   include <cmath>
#else
#   include <math.h>
#endif

#include <cppunit/TestAssert.h>
#include <cppunit/NotEqualException.h>


namespace CppUnit {


#ifdef CPPUNIT_ENABLE_SOURCELINE_DEPRECATED
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


/// Reports failed equality
void TestAssert::assertNotEqualImplementation( std::string expected,
     std::string actual,
     long lineNumber,
     std::string fileName )
{
  throw NotEqualException( expected, actual, lineNumber, fileName );
}


/// Check for a failed equality assertion
void TestAssert::assertEquals (double        expected, 
  double        actual, 
  double        delta,
  long          lineNumber,
  std::string   fileName)
{ 
  if (fabs (expected - actual) > delta) 
    assertNotEqualImplementation( assertion_traits<double>::toString(expected),
                                  assertion_traits<double>::toString(actual),
                                  lineNumber, 
                                  fileName ); 
}

#else

void 
TestAssert::assertDoubleEquals( double expected,
                                double actual,
                                double delta,
                                SourceLine sourceLine )
{
  Asserter::failNotEqualIf( fabs( expected - actual ) > delta,
                            assertion_traits<double>::toString(expected),
                            assertion_traits<double>::toString(actual),
                            sourceLine );
}


#endif


}
