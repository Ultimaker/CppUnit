#include <cppunit/Portability.h>
#include <typeinfo>
#include <stdexcept>

#include <cppunit/TestCase.h>
#include <cppunit/Exception.h>
#include <cppunit/TestResult.h>


namespace CppUnit {


/** Constructs a test case.
 *  \param name the name of the TestCase.
 **/
TestCase::TestCase( const std::string &name )
    : m_name(name)
{
}


/// Run the test and catch any exceptions that are triggered by it 
void 
TestCase::run( TestResult *result )
{
  result->startTest(this);

  try {
    setUp();

    try {
      runTest();
    }
    catch ( Exception &e ) {
      Exception *copy = e.clone();
      result->addFailure( this, copy );
    }
    catch ( std::exception &e ) {
      result->addError( this, new Exception( e.what() ) );
    }
    catch (...) {
      Exception *e = new Exception( "caught unknown exception" );
      result->addError( this, e );
    }

    try {
      tearDown();
    }
    catch (...) {
      result->addError( this, new Exception( "tearDown() failed" ) );
    }
  }
  catch (...) {
          result->addError( this, new Exception( "setUp() failed" ) );
  }
  
  result->endTest( this );
}


/// All the work for runTest is deferred to subclasses 
void 
TestCase::runTest()
{
}


/** Constructs a test case for a suite.
 * \deprecated This constructor was used by fixture when TestFixture did not exist.
 *             Have your fixture inherits TestFixture instead of TestCase.
 * \internal
 *  This TestCase was intended for use by the TestCaller and should not
 *  be used by a test case for which run() is called.
 **/
TestCase::TestCase()
    : m_name( "" )
{
}


/// Destructs a test case
TestCase::~TestCase()
{
}


/// Returns the name of the test case
std::string 
TestCase::getName() const
{ 
  return m_name; 
}
  

} // namespace CppUnit
