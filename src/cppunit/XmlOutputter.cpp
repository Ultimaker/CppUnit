#include <cppunit/Exception.h>
#include <cppunit/Test.h>
#include <cppunit/TestFailure.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/XmlOutputter.h>
#include <cppunit/tools/XmlDocument.h>
#include <cppunit/tools/XmlElement.h>
#include <stdlib.h>


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

  FailedTests failedTests;
  fillFailedTestsMap( failedTests );

  addFailedTests( failedTests, rootNode );
  addSuccessfulTests( failedTests, rootNode );
  addStatistics( rootNode );

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
  rootNode->addNode( testsNode );

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
  rootNode->addNode( testsNode );

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
  rootNode->addNode( statisticsNode );
  statisticsNode->addNode( new XmlElement( "Tests", m_result->runTests() ) );
  statisticsNode->addNode( new XmlElement( "FailuresTotal", 
                                     m_result->testFailuresTotal() ) );
  statisticsNode->addNode( new XmlElement( "Errors", m_result->testErrors() ) );
  statisticsNode->addNode( new XmlElement( "Failures", m_result->testFailures() ) );
}


void
XmlOutputter::addFailedTest( Test *test,
                             TestFailure *failure,
                             int testNumber,
                             XmlElement *testsNode )
{
  Exception *thrownException = failure->thrownException();
  
  XmlElement *testNode = new XmlElement( "FailedTest" );
  testsNode->addNode( testNode );
  testNode->addAttribute( "id", testNumber );
  testNode->addNode( new XmlElement( "Name", test->getName() ) );
  testNode->addNode( new XmlElement( "FailureType", 
                               failure->isError() ? "Error" : "Assertion" ) );

  if ( failure->sourceLine().isValid() )
    addFailureLocation( failure, testNode );

  testNode->addNode( new XmlElement( "Message", thrownException->what() ) );
}


void
XmlOutputter::addFailureLocation( TestFailure *failure,
                                            XmlElement *testNode )
{
  XmlElement *locationNode = new XmlElement( "Location" );
  testNode->addNode( locationNode );
  SourceLine sourceLine = failure->sourceLine();
  locationNode->addNode( new XmlElement( "File", sourceLine.fileName() ) );
  locationNode->addNode( new XmlElement( "Line", sourceLine.lineNumber() ) );
}


void
XmlOutputter::addSuccessfulTest( Test *test, 
                                          int testNumber,
                                          XmlElement *testsNode )
{
  XmlElement *testNode = new XmlElement( "Test" );
  testsNode->addNode( testNode );
  testNode->addAttribute( "id", testNumber );
  testNode->addNode( new XmlElement( "Name", test->getName() ) );
}


}  // namespace CppUnit
