#ifndef CPPUNIT_TEXTTESTRUNNER_H
#define CPPUNIT_TEXTTESTRUNNER_H

#include <string>
#include <vector>

namespace CppUnit {

class Test;
class TestSuite;
class TextTestResult;

/**
 * A text mode test runner.
 *
 * The test runner manage the life cycle of the added tests.
 *
 * The test runner can run only one of the added tests or all the tests. 
 *
 * TestRunner prints out a trace as the tests are executed followed by a
 * summary at the end.
 *
 * Here is an example of use:
 *
 * \code
 * TextTestRunner runner;
 * runner.addTest( ExampleTestCase::suite() );
 * runner.run( "", true );    // Run all tests and wait
 * \endcode
 */
class TextTestRunner
{
public:
  TextTestRunner( TextTestResult *result =0 );
  virtual ~TextTestRunner();

  bool run( std::string testName ="",
            bool wait = false,
            bool printResult = true );

  void addTest( Test *test );

  TextTestResult *result();

protected:
  bool runTest( Test *test );
  bool runTestByName( std::string testName );
  void wait( bool doWait );
  void printResult( bool doPrintResult );

  Test *findTestByName( std::string name ) const;
  TestSuite *m_suite;
  TextTestResult *m_result;
};

}  // namespace CppUnit

#endif  // CPPUNIT_TEXTTESTRUNNER_H
