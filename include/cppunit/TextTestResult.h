#ifndef CPPUNIT_TEXTTESTRESULT_H
#define CPPUNIT_TEXTTESTRESULT_H

#include <cppunit/TestResult.h>
#include <iostream>

namespace CppUnit {

class SourceLine;
class Exception;
class Test;

class TextTestResult : public TestResult 
{
  public:
    virtual void addError( Test *test, Exception *e );
    virtual void addFailure( Test *test, Exception *e );
    virtual void startTest( Test *test );
    virtual void print( std::ostream &stream );
    virtual void printFailures( std::ostream &stream );
    virtual void printHeader( std::ostream &stream );

    virtual void printFailure( TestFailure *failure,
                               int failureNumber,
                               std::ostream &stream );
    virtual void printFailureListMark( int failureNumber,
                                        std::ostream &stream );
    virtual void printFailureTestName( TestFailure *failure,
                                       std::ostream &stream );
    virtual void printFailureType( TestFailure *failure,
                                   std::ostream &stream );
    virtual void printFailureLocation( SourceLine sourceLine,
                                       std::ostream &stream );
    virtual void printFailureDetail( Exception *thrownException,
                                     std::ostream &stream );
    virtual void printFailureWarning( std::ostream &stream );
    virtual void printStatistics( std::ostream &stream );
};

/** insertion operator for easy output */
std::ostream &operator <<( std::ostream &stream, 
                           TextTestResult &result );

} // namespace CppUnit

#endif // CPPUNIT_TEXTTESTRESULT_H


