#ifndef CPPUNIT_TEXTTESTRUNNER_H
#define CPPUNIT_TEXTTESTRUNNER_H

#include <string>
#include <vector>

namespace CppUnit {

class Outputter;
class Test;
class TestSuite;
class TextOutputter;
class TestResult;
class TestResultCollector;

/**
 * A text mode test runner.
 *
 * FIXME: need update
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
class CPPUNIT_API TextTestRunner
{
public:
  /*! Constructs a new text runner.
   * \param outputter used to print text result. Owned by the runner.
   */
  TextTestRunner( Outputter *outputter =NULL );

  virtual ~TextTestRunner();

  bool run( std::string testName ="",
            bool wait = false,
            bool printResult = true );

  void addTest( Test *test );

  void setOutputter( Outputter *outputter );

  TestResultCollector &result() const;

  TestResult &eventManager() const;

protected:
  bool runTest( Test *test );
  bool runTestByName( std::string testName );
  void wait( bool doWait );
  void printResult( bool doPrintResult );

  Test *findTestByName( std::string name ) const;

  TestSuite *m_suite;
  TestResultCollector *m_result;
  TestResult *m_eventManager;
  Outputter *m_outputter;
};

}  // namespace CppUnit

#endif  // CPPUNIT_TEXTTESTRUNNER_H
