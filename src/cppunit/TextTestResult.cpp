#include <iostream>
#include "cppunit/TextTestResult.h"
#include "cppunit/Exception.h"
#include "cppunit/Test.h"
#include "estring.h"

namespace CppUnit {

std::ostream& 
CppUnit::operator<< (std::ostream& stream, TextTestResult& result)
{ 
  result.print (stream); return stream; 
}

void 
TextTestResult::addError (Test *test, Exception *e)
{
    TestResult::addError (test, e);
    std::cerr << "E";
}

void 
TextTestResult::addFailure (Test *test, Exception *e)
{
    TestResult::addFailure (test, e);
    std::cerr << "F";
}

void 
TextTestResult::startTest (Test *test)
{
  TestResult::startTest (test);
  std::cerr << ".";
}


void 
TextTestResult::printErrors (std::ostream& stream)
{
    if (testErrors () != 0) {

        if (testErrors () == 1)
            stream << "There was " << testErrors () << " error: " << std::endl;
        else
            stream << "There were " << testErrors () << " errors: " << std::endl;

        int i = 1;

        for (std::vector<TestFailure *>::iterator it = errors ().begin (); it != errors ().end (); ++it) {
            TestFailure             *failure    = *it;
            Exception        *e          = failure->thrownException ();

            stream << i 
                   << ") "
                   << "test: " << failure->failedTest()->getName()  << " "
                   << "line: " << (e ? estring (e->lineNumber ()) : "") << " "
                   << (e ? e->fileName () : "") << " "
                   << "\"" << failure->thrownException ()->what () << "\""
                   << std::endl;
            i++;
        }
    }

}

void 
TextTestResult::printFailures (std::ostream& stream) 
{
    if (testFailures () != 0) {
        if (testFailures () == 1)
            stream << "There was " << testFailures () << " failure: " << std::endl;
        else
            stream << "There were " << testFailures () << " failures: " << std::endl;

        int i = 1;

        for (std::vector<TestFailure *>::iterator it = failures ().begin (); it != failures ().end (); ++it) {
            TestFailure             *failure    = *it;
            Exception        *e          = failure->thrownException ();

            stream << i 
                   << ") "
                   << "test: " << failure->failedTest()->getName()  << " "
                   << "line: " << (e ? estring (e->lineNumber ()) : "") << " "
                   << (e ? e->fileName () : "") << " "
                   << "\"" << failure->thrownException ()->what () << "\""
                   << std::endl;
            i++;
        }
    }

}


void 
TextTestResult::print (std::ostream& stream) 
{
    printHeader (stream);
    printErrors (stream);
    printFailures (stream);

}


void 
TextTestResult::printHeader (std::ostream& stream)
{
    if (wasSuccessful ())
        stream << std::endl << "OK (" << runTests () << " tests)" << std::endl;
    else
        stream << std::endl
             << "!!!FAILURES!!!" << std::endl
             << "Test Results:" << std::endl
             << "Run:  "
             << runTests ()
             << "   Failures: "
             << testFailures ()
             << "   Errors: "
             << testErrors ()
             << std::endl;

}

} // namespace CppUnit
