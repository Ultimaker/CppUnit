#include <cppunit/Exception.h>
#include <cppunit/Test.h>
#include <cppunit/TestResult.h>
#include <cppunit/XmlTestResultOutputter.h>
#include <map>
#include <stdlib.h>


namespace CppUnit
{

// XmlTestResultOutputter::Node
// //////////////////////////////////////////////////////////////////


XmlTestResultOutputter::Node::Node( std::string elementName,
                                std::string content ) :
    m_name( elementName ),
    m_content( content )
{
}

    
XmlTestResultOutputter::Node::Node( std::string elementName,
                                    int numericContent ) :
    m_name( elementName )
{
  m_content = asString( numericContent );
}


XmlTestResultOutputter::Node::~Node()
{
  Nodes::iterator itNode = m_nodes.begin();
  while ( itNode != m_nodes.end() )
    delete *itNode++;
}


void 
XmlTestResultOutputter::Node::addAttribute( std::string attributeName,
                                            std::string value  )
{
  m_attributes.push_back( Attribute( attributeName, value ) );
}


void 
XmlTestResultOutputter::Node::addAttribute( std::string attributeName,
                                            int numericValue )
{
  addAttribute( attributeName, asString( numericValue ) );
}


void 
XmlTestResultOutputter::Node::addNode( Node *node )
{
  m_nodes.push_back( node );
}


std::string 
XmlTestResultOutputter::Node::toString() const
{
  std::string element = "<";
  element += m_name;
  element += " ";
  element += attributesAsString();
  element += " >\n";

  Nodes::const_iterator itNode = m_nodes.begin();
  while ( itNode != m_nodes.end() )
  {
    const Node *node = *itNode++;
    element += node->toString();
  }

  element += m_content;

  element += "</";
  element += m_name;
  element += ">\n";

  return element;
}


std::string 
XmlTestResultOutputter::Node::attributesAsString() const
{
  std::string attributes;
  Attributes::const_iterator itAttribute = m_attributes.begin();
  while ( itAttribute != m_attributes.end() )
  {
    const Attribute &attribute = *itAttribute++;
    attributes += attribute.first;
    attributes += "=\"";
    attributes += escape( attribute.second );
    attributes += "\"";
  }
  return attributes;
}


std::string 
XmlTestResultOutputter::Node::escape( std::string value ) const
{
  std::string escaped;
  for ( int index =0; index < value.length(); ++index )
  {
    char c = value[index ];
    switch ( c )    // escape all predefined XML entity (safe?)
    {
    case '<': 
      escaped += "&lt;";
      break;
    case '>': 
      escaped += "&gt;";
      break;
    case '&': 
      escaped += "&amp;";
      break;
    case '\'': 
      escaped += "&apos;";
      break;
    case '"': 
      escaped += "&quot;";
      break;
    default:
      escaped += c;
    }
  }
  
  return escaped;
}

// should be somewhere else... Future CppUnit::String ?    
std::string 
XmlTestResultOutputter::Node::asString( int value )
{
  OStringStream stream;
  stream << value;
  return stream.str();
}




// XmlTestResultOutputter
// //////////////////////////////////////////////////////////////////

XmlTestResultOutputter::XmlTestResultOutputter()
{
}


XmlTestResultOutputter::~XmlTestResultOutputter()
{
}


void 
XmlTestResultOutputter::write( TestResult *result,
                               std::ostream &stream )
{
  writeProlog( stream );
  writeTestsResult( result, stream );
}


void 
XmlTestResultOutputter::writeProlog( std::ostream &stream )
{
  stream  <<  "<?xml version=\"1.0\" encoding='ISO-8859-1' standalone='yes' ?>"
          <<  std::endl;
}


void 
XmlTestResultOutputter::writeTestsResult( TestResult *result, 
                                          std::ostream &stream )
{
  Node *rootNode = makeRootNode( result );
  stream  <<  rootNode->toString();
  delete rootNode;
}


XmlTestResultOutputter::Node *
XmlTestResultOutputter::makeRootNode( TestResult *result )
{
  Node *rootNode = new Node( "TestRun" );

  FailedTests failedTests;
  fillFailedTestsMap( result, failedTests );

  rootNode->addNode( makeFailedTestsNode( failedTests, result ) );
  rootNode->addNode( makeSucessfulTestsNode( failedTests, result ) );
  rootNode->addNode( makeStatisticsNode( result ) );

  return rootNode;
}


void 
XmlTestResultOutputter::fillFailedTestsMap( TestResult *result, 
                                            FailedTests &failedTests )
{
  const TestResult::TestFailures &failures = result->failures();
  TestResult::TestFailures::const_iterator itFailure = failures.begin();
  while ( itFailure != failures.end() )
  {
    TestFailure *failure = *itFailure++;
    failedTests.insert( std::make_pair(failure->failedTest(), failure ) );
  }
}


XmlTestResultOutputter::Node *
XmlTestResultOutputter::makeFailedTestsNode( FailedTests &failedTests, 
                                             TestResult *result )
{
  Node *rootNode = new Node( "FailedTests" );

  const TestResult::Tests &tests = result->tests();
  for ( int testNumber = 0; testNumber < tests.size(); ++testNumber )
  {
    Test *test = tests[testNumber];
    if ( failedTests.find( test ) != failedTests.end() )
    {
      rootNode->addNode( makeFailedTestNode( test, 
                                             failedTests[test], 
                                             testNumber+1 ) );
    }
  }

  return rootNode;
}


XmlTestResultOutputter::Node *
XmlTestResultOutputter::makeSucessfulTestsNode( FailedTests &failedTests, 
                                                TestResult *result )
{
  Node *rootNode = new Node( "SucessfulTests" );

  const TestResult::Tests &tests = result->tests();
  for ( int testNumber = 0; testNumber < tests.size(); ++testNumber )
  {
    Test *test = tests[testNumber];
    if ( failedTests.find( test ) == failedTests.end() )
    {
      rootNode->addNode( makeSucessfulTestNode( test, 
                                                testNumber+1 ) );
    }
  }

  return rootNode;
}


XmlTestResultOutputter::Node *
XmlTestResultOutputter::makeStatisticsNode( TestResult *result )
{
  Node *statisticsNode = new Node( "Statistics" );
  statisticsNode->addNode( new Node( "Tests", result->runTests() ) );
  statisticsNode->addNode( new Node( "FailuresTotal", 
                                     result->testFailuresTotal() ) );
  statisticsNode->addNode( new Node( "Errors", result->testErrors() ) );
  statisticsNode->addNode( new Node( "Failures", result->testFailures() ) );

  return statisticsNode;
}


XmlTestResultOutputter::Node *
XmlTestResultOutputter::makeFailedTestNode( Test *test,
                                            TestFailure *failure,
                                            int testNumber )
{
  Exception *thrownException = failure->thrownException();
  
  Node *testNode = new Node( "FailedTest", thrownException->what() );
  testNode->addAttribute( "id", testNumber );
  testNode->addNode( new Node( "Name", test->getName() ) );
  testNode->addNode( new Node( "FailureType", 
                               failure->isError() ? "Error" : "Assertion" ) );

  if ( failure->sourceLine().isValid() )
    testNode->addNode( makeFailureLocationNode( failure ) );
  return testNode;
}


XmlTestResultOutputter::Node *
XmlTestResultOutputter::makeFailureLocationNode( TestFailure *failure )
{
  Node *locationNode = new Node( "Location" );
  SourceLine sourceLine = failure->sourceLine();
  locationNode->addNode( new Node( "File", sourceLine.fileName() ) );
  locationNode->addNode( new Node( "Line", sourceLine.lineNumber() ) );
  return locationNode;
}


XmlTestResultOutputter::Node *
XmlTestResultOutputter::makeSucessfulTestNode( Test *test, 
                                               int testNumber )
{
  Node *testNode = new Node( "Test" );
  testNode->addAttribute( "id", testNumber );
  testNode->addNode( new Node( "Name", test->getName() ) );
  return testNode;
}


}  // namespace CppUnit
