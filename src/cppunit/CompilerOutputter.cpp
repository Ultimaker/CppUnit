#include <cppunit/NotEqualException.h>
#include <cppunit/SourceLine.h>
#include <cppunit/TestResult.h>
#include <cppunit/CompilerOutputter.h>


namespace CppUnit
{

/** Print TestResult in a compiler compatible format.
 *
 * Heres is an example of usage:
 * \code
 * int main( int argc, char* argv[] ) {
 *   bool selfTest = (argc > 1)  &&  
 *                   (std::string("-selftest") == argv[1]);
 *
 *   CppUnit::TextTestRunner runner;
 *   runner.addTest( CppUnitTest::suite() );
 * 
 *   bool wasSucessful = runner.run( "", false, !selfTest );
 *   if ( selfTest )
 *   {  
 *     CppUnit::CompilerOutputter outputter( runner.result(),
 *                                                     std::cerr );
 *     outputter.write();
 *   }
 * 
 *   return wasSucessful ? 0 : 1;
 * }
 * \endcode
 */
CompilerOutputter::CompilerOutputter( 
                               TestResult *result,
                               std::ostream &stream ) :
    m_result( result ),
    m_stream( stream )
{
}


CompilerOutputter::~CompilerOutputter()
{
}


CompilerOutputter *
CompilerOutputter::defaultOutputter( TestResult *result,
                                               std::ostream &stream )
{
  return new CompilerOutputter( result, stream );
// For automatic adpatation...
//  return new CPPUNIT_DEFAULT_OUTPUTTER( result, stream );
}


void 
CompilerOutputter::write()
{
  if ( m_result->wasSuccessful() )
    printSucess();
  else
    printFailureReport();
}


void 
CompilerOutputter::printSucess()
{
  m_stream  << "OK (" << m_result->runTests()  << ")"  
            <<  std::endl;
}


void 
CompilerOutputter::printFailureReport()
{
  printFailuresList();
  printStatistics();
}


void 
CompilerOutputter::printFailuresList()
{
  for ( int index =0; index < m_result->testFailuresTotal(); ++index)
  {
    printFailureDetail( m_result->failures()[ index ] );
  }
}


void 
CompilerOutputter::printFailureDetail( TestFailure *failure )
{
  printFailureLocation( failure->sourceLine() );
  printFailureType( failure );
  printFailedTestName( failure );
  printFailureMessage( failure );
}

 
void 
CompilerOutputter::printFailureLocation( SourceLine sourceLine )
{
  if ( sourceLine.isValid() )
    m_stream  <<  sourceLine.fileName()  
              <<  "("  << sourceLine.lineNumber()  << ") : ";
  else
    m_stream  <<  "##Failure Location unknown## : ";
}


void 
CompilerOutputter::printFailureType( TestFailure *failure )
{
  m_stream  <<  (failure->isError() ? "Error" : "Assertion");
}


void 
CompilerOutputter::printFailedTestName( TestFailure *failure )
{
  m_stream  <<  std::endl;
  m_stream  <<  "Test name: "  <<  failure->failedTestName();
}


void 
CompilerOutputter::printFailureMessage( TestFailure *failure )
{
  m_stream  <<  std::endl;
  Exception *thrownException = failure->thrownException();
  if ( thrownException->isInstanceOf( NotEqualException::type() ) )
    printNotEqualMessage( thrownException );
  else
    printDefaultMessage( thrownException );
  m_stream  <<  std::endl;
}


void 
CompilerOutputter::printNotEqualMessage( Exception *thrownException )
{
  NotEqualException *e = (NotEqualException *)thrownException;
  m_stream  <<  wrap( "- Expected : " + e->expectedValue() );
  m_stream  <<  std::endl;
  m_stream  <<  wrap( "- Actual   : " + e->actualValue() );
  m_stream  <<  std::endl;
  if ( !e->additionalMessage().empty() )
  {
    m_stream  <<  wrap( "- " + e->additionalMessage() );
    m_stream  <<  std::endl;
  }
}


void 
CompilerOutputter::printDefaultMessage( Exception *thrownException )
{
  std::string wrappedMessage = wrap( thrownException->what() );
  m_stream  <<  wrappedMessage  << std::endl;
}


void 
CompilerOutputter::printStatistics()
{
  m_stream  <<  "Failures !!!"  <<  std::endl;
  m_stream  <<  "Run: "  <<  m_result->runTests()  << "   "
            <<  "Failure total: "  <<  m_result->testFailuresTotal()  << "   "
            <<  "Failures: "  <<  m_result->testFailures()  << "   "
            <<  "Errors: "  <<  m_result->testErrors()
            <<  std::endl;
}


std::string
CompilerOutputter::wrap( std::string message )
{
  const int maxLineLength = 80;
  std::string wrapped;
  int index =0;
  while ( index < message.length() )
  {
    std::string line( message.substr( index, maxLineLength ) );
    wrapped += line;
    index += maxLineLength;
    if ( index < message.length() )
      wrapped += "\n";
  }
  return wrapped;
}



}  // namespace CppUnit
