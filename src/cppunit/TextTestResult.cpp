#include <iostream>
#include "cppunit/TextTestResult.h"
#include "cppunit/Exception.h"
#include "cppunit/NotEqualException.h"
#include "cppunit/Test.h"

namespace CppUnit {


void 
TextTestResult::addError( Test *test, 
                          Exception *e )
{
  TestResult::addError( test, e );
  std::cerr << "E";
}


void 
TextTestResult::addFailure( Test *test, 
                            Exception *e )
{
  TestResult::addFailure (test, e);
  std::cerr << "F";
}


void 
TextTestResult::startTest( Test *test )
{
  TestResult::startTest (test);
  std::cerr << ".";
}


void 
TextTestResult::printFailures( std::ostream &stream )
{
  TestFailures::const_iterator itFailure = failures().begin();
  int failureNumber = 1;
  while ( itFailure != failures().end() ) 
    printFailure( *itFailure++, failureNumber++, stream );
}


void 
TextTestResult::printFailure( TestFailure *failure,
                              int failureNumber,
                              std::ostream &stream )
{
  printFailureListMark( failureNumber, stream );
  stream << ' ';
  printFailureTestName( failure, stream );
  stream << ' ';
  printFailureType( failure, stream );
  stream << ' ';
  printFailureLocation( failure->thrownException(), stream );
  stream << std::endl;
  printFailureDetail( failure->thrownException(), stream );
  stream << std::endl;
}


void 
TextTestResult::printFailureListMark( int failureNumber,
                                      std::ostream &stream )
{
  stream << failureNumber << ")";
}


void 
TextTestResult::printFailureTestName( TestFailure *failure,
                                      std::ostream &stream )
{
  stream << "test: " << failure->failedTest()->getName();
}


void 
TextTestResult::printFailureType( TestFailure *failure,
                                  std::ostream &stream )
{
  stream << "("
         << (failure->isError() ? "E" : "F")
         << ")";
}


void 
TextTestResult::printFailureLocation( Exception *thrownException,
                                      std::ostream &stream )
{
  stream << "line: " << thrownException->lineNumber()
         << ' ' << thrownException->fileName();
}


void 
TextTestResult::printFailureDetail( Exception *thrownException,
                                    std::ostream &stream )
{
  if ( thrownException->isInstanceOf( NotEqualException::type() ) )
  {
    NotEqualException *e = (NotEqualException*)thrownException;
    stream << "expected: " << e->expectedValue() << std::endl
           << "but was:  " << e->actualValue();
  }
  else
  {
    stream << " \"" << thrownException->what() << "\"";
  }
}


void 
TextTestResult::print( std::ostream& stream ) 
{
  printHeader( stream );
  stream << std::endl;
  printFailures( stream );
}


void 
TextTestResult::printHeader( std::ostream &stream )
{
  if (wasSuccessful ())
    stream << std::endl << "OK (" << runTests () << " tests)" 
           << std::endl;
  else
    stream << std::endl
           << "!!!FAILURES!!!" << std::endl
           << "Test Results:" << std::endl
           << "Run:  "  << runTests()
           << "   Failures: "  << testFailures()
           << "   Errors: "  << testErrors()
           << std::endl;
}


std::ostream &
operator <<( std::ostream &stream, 
             TextTestResult &result )
{ 
  result.print (stream); return stream; 
}


} // namespace CppUnit
