#include <typeinfo>
#include <stdexcept>
#include <cmath>

#include "cppunit/TestCase.h"
#include "cppunit/Exception.h"
#include "cppunit/TestResult.h"
#include "estring.h"

namespace CppUnit {

/// Create a default TestResult
CppUnit::TestResult* TestCase::defaultResult ()
{ return new TestResult; } 

/// Run the test and catch any exceptions that are triggered by it 
void 
TestCase::run (TestResult *result)
{
  result->startTest (this);
  
  setUp ();
  
  try {

    runTest ();
    
  }
  catch (Exception& e) {
    Exception *copy = new Exception (e);
    result->addFailure (this, copy);
    
  }
  catch (exception& e) {
    result->addError (this, new Exception (e.what ()));
    
  }
  catch (...) {
    Exception *e = new Exception ("unknown exception");
    result->addError (this, e);

  }

  tearDown ();

  result->endTest (this);

}


/// A default run method 
TestResult *TestCase::run ()
{
  TestResult *result = defaultResult ();

  run (result);
  return result;

}

/// All the work for runTest is deferred to subclasses 
void TestCase::runTest ()
{
}

/** Constructs a test case.
 *  \param name the name of the TestCase.
 **/
TestCase::TestCase (std::string name) 
  : m_name (name) 
{
}

/** Constructs a test case for a suite.
 *  This TestCase is intended for use by the TestCaller and should not
 *  be used by a test case for which run() is called.
 **/
TestCase::TestCase () 
  : m_name ("") 
{
}


/// Destructs a test case
TestCase::~TestCase ()
{}


/// Returns a count of all the tests executed
int TestCase::countTestCases () const
{ return 1; }


/// Returns the name of the test case
std::string 
  TestCase::getName () const
{ 
  return m_name; 
}


/// A hook for fixture set up
void TestCase::setUp ()
{}
  

/// A hook for fixture tear down
void TestCase::tearDown ()
{}


/// Returns the name of the test case instance
std::string 
  TestCase::toString () const
{ 
  std::string className;

#ifdef CU_USE_TYPEINFO
  const std::type_info& thisClass = typeid (*this);
  className = thisClass.name();
#else
  className = "TestCase";
#endif // CU_USE_TYPEINFO

  return className + "." + getName (); 
}
  
} // namespace CppUnit
