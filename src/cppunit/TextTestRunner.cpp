#include <cppunit/TestSuite.h>
#include <cppunit/TextTestRunner.h>
#include <cppunit/TextTestResult.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/TextTestProgressListener.h>
#include <cppunit/TestResult.h>
#include <iostream>

namespace CppUnit {

/** Constructs a test runner with the specified TestResult.
 *
 * A TextTestRunner owns a TextTestResult. It can be accessed 
 * anytime using result(). If you run the test more than once,
 * remember to call result()->reset() before each run.
 *
 * \param result TextTestResult used by the test runner. If none
 *               is specified then a default TextTestResult is
 *               instanciated.
 */
TextTestRunner::TextTestRunner( Outputter *outputter ) 
    : m_outputter( outputter )
    , m_suite( new TestSuite( "All Tests" ) )
    , m_result( new TestResultCollector() )
    , m_eventManager( new TestResult() )
{
  if ( !m_outputter )
    m_outputter = new TextOutputter( m_result, std::cout );
  m_eventManager->addListener( m_result );
}


TextTestRunner::~TextTestRunner()
{
  delete m_eventManager;
  delete m_outputter;
  delete m_result;
  delete m_suite;
}


/** Adds the specified test.
 *
 * \param test Test to add.
 */
void 
TextTestRunner::addTest( Test *test )
{
  if ( test != NULL )
    m_suite->addTest( test );
}


/** Runs the named test case.
 *
 * \param testName Name of the test case to run. If an empty is given, then
 *                 all added test are run. The name must be the name of
 *                 of an added test.
 * \param wait if \c true then the user must press the RETURN key 
 *               before the run() method exit.
 * \param printResult if \c true (default) then the test result are printed
 *                    on the standard output.
 * \return \c true is the test was successful, \c false if the test
 *         failed or was not found.
 */
bool
TextTestRunner::run( std::string testName,
                     bool doWait,
                     bool doPrintResult )
{
  runTestByName( testName );
  printResult( doPrintResult );
  wait( doWait );
  return m_result->wasSuccessful();
}


bool
TextTestRunner::runTestByName( std::string testName )
{
  if ( testName.empty() )
    return runTest( m_suite );

  Test *test = findTestByName( testName );
  if ( test != NULL )
    return runTest( test );

  std::cout << "Test " << testName << " not found." << std::endl;
  return false;
}


void 
TextTestRunner::wait( bool doWait )
{
  if ( doWait ) 
  {
    std::cout << "<RETURN> to continue" << std::endl;
    std::cin.get ();
  }
}


void 
TextTestRunner::printResult( bool doPrintResult )
{
  std::cout << std::endl;
  if ( doPrintResult )
    m_outputter->write();
}


Test * 
TextTestRunner::findTestByName( std::string name ) const
{
  for ( std::vector<Test *>::const_iterator it = m_suite->getTests().begin(); 
        it != m_suite->getTests().end(); 
        ++it )
  {
    Test *test = *it;
    if ( test->getName() == name )
      return test;
  }
  return NULL;
}


bool
TextTestRunner::runTest( Test *test )
{
  TextTestProgressListener progress;
  m_eventManager->addListener( &progress );
  test->run( m_eventManager );
  m_eventManager->removeListener( &progress );
  return m_result->wasSuccessful();
}


TestResultCollector &
TextTestRunner::result() const
{
  return *m_result;
}


TestResult &
TextTestRunner::eventManager() const
{
  return *m_eventManager;
}


void 
TextTestRunner::setOutputter( Outputter *outputter )
{
  delete m_outputter;
  m_outputter = outputter;
}


}  //  namespace CppUnit
