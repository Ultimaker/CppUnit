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

/*!
 * \brief A text mode test runner.
 *
 * The test runner manage the life cycle of the added tests.
 *
 * The test runner can run only one of the added tests or all the tests. 
 *
 * TextTestRunner prints out a trace as the tests are executed followed by a
 * summary at the end. The trace and summary print are optional.
 *
 * Here is an example of use:
 *
 * \code
 * CppUnit::TextTestRunner runner;
 * runner.addTest( ExampleTestCase::suite() );
 * runner.run( "", true );    // Run all tests and wait
 * \endcode
 *
 * The trace is printed using a TextTestProgressListener. The summary is printed
 * using a TextOutputter. 
 *
 * You can specify an alternate Outputter at construction
 * or later with setOutputter(). 
 *
 * After construction, you can register additional TestListener to eventManager(),
 * for a custom progress trace, for example.
 *
 * \code
 * CppUnit::TextTestRunner runner;
 * runner.addTest( ExampleTestCase::suite() );
 * runner.setOutputter( CppUnit::CompilerOutputter::defaultOutputter( 
 *                          &runner.result(),
 *                          std::cerr ) );
 * MyCustomProgressTestListener progress;
 * runner.eventManager().addListener( &progress );
 * runner.run( "", true );    // Run all tests and wait
 * \endcode
 *
 * \see CompilerOutputter, XmlOutputter, TextOutputter.
 */
class CPPUNIT_API TextTestRunner
{
public:
  TextTestRunner( Outputter *outputter =NULL );

  virtual ~TextTestRunner();

  bool run( std::string testName ="",
            bool wait = false,
            bool printResult = true,
            bool printProgress = true );

  void addTest( Test *test );

  void setOutputter( Outputter *outputter );

  TestResultCollector &result() const;

  TestResult &eventManager() const;

protected:
  virtual bool runTest( Test *test,
                        bool printTextProgress );
  virtual bool runTestByName( std::string testName,
                              bool printProgress );
  virtual void wait( bool doWait );
  virtual void printResult( bool doPrintResult );

  virtual Test *findTestByName( std::string name ) const;

  TestSuite *m_suite;
  TestResultCollector *m_result;
  TestResult *m_eventManager;
  Outputter *m_outputter;
};

}  // namespace CppUnit

#endif  // CPPUNIT_TEXTTESTRUNNER_H
