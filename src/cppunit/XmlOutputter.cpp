#include <cppunit/Exception.h>
#include <cppunit/Test.h>
#include <cppunit/TestFailure.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/XmlOutputter.h>
#include <cppunit/XmlOutputterHook.h>
#include <cppunit/tools/XmlDocument.h>
#include <cppunit/tools/XmlElement.h>
#include <stdlib.h>
#include <algorithm>


namespace CppUnit
{

// XmlElement
// //////////////////////////////////////////////////////////////////






// XmlOutputter
// //////////////////////////////////////////////////////////////////

XmlOutputter::XmlOutputter( TestResultCollector *result,
                            std::ostream &stream,
                            std::string encoding )
  : m_result( result )
  , m_stream( stream )
  , m_xml( new XmlDocument( encoding ) )
{
}


XmlOutputter::~XmlOutputter()
{
  delete m_xml;
}


void 
XmlOutputter::addHook( XmlOutputterHook *hook )
{
  m_hooks.push_back( hook );
}


void 
XmlOutputter::removeHook( XmlOutputterHook *hook )
{
  m_hooks.erase( std::find( m_hooks.begin(), m_hooks.end(), hook ) );
}


void 
XmlOutputter::write()
{
  m_xml->setRootElement( makeRootNode() );
  m_stream  <<  m_xml->toString();
}


void 
XmlOutputter::setStyleSheet( const std::string &styleSheet )
{
  m_xml->setStyleSheet( styleSheet );
}


XmlElement *
XmlOutputter::makeRootNode()
{
  XmlElement *rootNode = new XmlElement( "TestRun" );

  for ( Hooks::const_iterator it = m_hooks.begin(); it != m_hooks.end(); ++it )
    (*it)->beginDocument( m_xml, rootNode );

  FailedTests failedTests;
  fillFailedTestsMap( failedTests );

  addFailedTests( failedTests, rootNode );
  addSuccessfulTests( failedTests, rootNode );
  addStatistics( rootNode );

  for ( Hooks::const_iterator itEnd = m_hooks.begin(); itEnd != m_hooks.end(); ++itEnd )
    (*itEnd)->endDocument( m_xml, rootNode );

  return rootNode;
}


void 
XmlOutputter::fillFailedTestsMap( FailedTests &failedTests )
{
  const TestResultCollector::TestFailures &failures = m_result->failures();
  TestResultCollector::TestFailures::const_iterator itFailure = failures.begin();
  while ( itFailure != failures.end() )
  {
    TestFailure *failure = *itFailure++;
    failedTests.insert( std::make_pair(failure->failedTest(), failure ) );
  }
}


void
XmlOutputter::addFailedTests( FailedTests &failedTests,
                                        XmlElement *rootNode )
{
  XmlElement *testsNode = new XmlElement( "FailedTests" );
  rootNode->addElement( testsNode );

  const TestResultCollector::Tests &tests = m_result->tests();
  for ( int testNumber = 0; testNumber < tests.size(); ++testNumber )
  {
    Test *test = tests[testNumber];
    if ( failedTests.find( test ) != failedTests.end() )
      addFailedTest( test, failedTests[test], testNumber+1, testsNode );
  }
}


void
XmlOutputter::addSuccessfulTests( FailedTests &failedTests,
                                           XmlElement *rootNode )
{
  XmlElement *testsNode = new XmlElement( "SuccessfulTests" );
  rootNode->addElement( testsNode );

  const TestResultCollector::Tests &tests = m_result->tests();
  for ( int testNumber = 0; testNumber < tests.size(); ++testNumber )
  {
    Test *test = tests[testNumber];
    if ( failedTests.find( test ) == failedTests.end() )
      addSuccessfulTest( test, testNumber+1, testsNode );
  }
}


void
XmlOutputter::addStatistics( XmlElement *rootNode )
{
  XmlElement *statisticsNode = new XmlElement( "Statistics" );
  rootNode->addElement( statisticsNode );
  statisticsNode->addElement( new XmlElement( "Tests", m_result->runTests() ) );
  statisticsNode->addElement( new XmlElement( "FailuresTotal", 
                                              m_result->testFailuresTotal() ) );
  statisticsNode->addElement( new XmlElement( "Errors", m_result->testErrors() ) );
  statisticsNode->addElement( new XmlElement( "Failures", m_result->testFailures() ) );

  for ( Hooks::const_iterator it = m_hooks.begin(); it != m_hooks.end(); ++it )
    (*it)->statisticsAdded( m_xml, statisticsNode );
}


void
XmlOutputter::addFailedTest( Test *test,
                             TestFailure *failure,
                             int testNumber,
                             XmlElement *testsNode )
{
  Exception *thrownException = failure->thrownException();
  
  XmlElement *testNode = new XmlElement( "FailedTest" );
  testsNode->addElement( testNode );
  testNode->addAttribute( "id", testNumber );
  testNode->addElement( new XmlElement( "Name", test->getName() ) );
  testNode->addElement( new XmlElement( "FailureType", 
                                        failure->isError() ? "Error" : 
                                                             "Assertion" ) );

  if ( failure->sourceLine().isValid() )
    addFailureLocation( failure, testNode );

  testNode->addElement( new XmlElement( "Message", thrownException->what() ) );

  for ( Hooks::const_iterator it = m_hooks.begin(); it != m_hooks.end(); ++it )
    (*it)->failTestAdded( m_xml, testNode, test, failure );
}


void
XmlOutputter::addFailureLocation( TestFailure *failure,
                                  XmlElement *testNode )
{
  XmlElement *locationNode = new XmlElement( "Location" );
  testNode->addElement( locationNode );
  SourceLine sourceLine = failure->sourceLine();
  locationNode->addElement( new XmlElement( "File", sourceLine.fileName() ) );
  locationNode->addElement( new XmlElement( "Line", sourceLine.lineNumber() ) );
}


void
XmlOutputter::addSuccessfulTest( Test *test, 
                                 int testNumber,
                                 XmlElement *testsNode )
{
  XmlElement *testNode = new XmlElement( "Test" );
  testsNode->addElement( testNode );
  testNode->addAttribute( "id", testNumber );
  testNode->addElement( new XmlElement( "Name", test->getName() ) );

  for ( Hooks::const_iterator it = m_hooks.begin(); it != m_hooks.end(); ++it )
    (*it)->successfulTestAdded( m_xml, testNode, test );
}


}  // namespace CppUnit
