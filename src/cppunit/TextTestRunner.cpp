
#include <iostream>
#include <cppunit/TestSuite.h>
#include <cppunit/TextTestRunner.h>
#include <cppunit/TextTestResult.h>

namespace CppUnit {

TextTestRunner::TextTestRunner()
{
  m_suite = new TestSuite( "All Tests" );
}


TextTestRunner::~TextTestRunner()
{
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
 * \param doWait if \c true then the user must press the RETURN key 
 *               before the run() method exit.
 * \return \c true is the test was successful, \c false if the test
 *         failed or was not found.
 */
bool
TextTestRunner::run( std::string testName,
                     bool doWait )
{
  bool sucessful = runTestByName( testName );
  wait( doWait );
  return sucessful;
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
  TextTestResult result;
  test->run( &result );
  std::cout << result << std::endl;
  return result.wasSuccessful();
}


}  //  namespace CppUnit
