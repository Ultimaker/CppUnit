
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
 */

void 
TextTestRunner::run( std::string testName,
                     bool doWait )
{
  runTestByName( testName );
  wait( doWait );
}


void 
TextTestRunner::runTestByName( std::string testName )
{
  if ( testName.empty() )
  {
    runTest( m_suite );
  }
  else
  { 
    Test *test = findTestByName( testName );
    if ( test != NULL )
      runTest( test );
    else
    {
      std::cout << "Test " << testName << " not found." << std::endl;
    }
  }
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


void 
TextTestRunner::runTest( Test *test )
{
  TextTestResult result;
  test->run( &result );
  std::cout << result << std::endl;
}


}  //  namespace CppUnit
