#include <cppunit/TestResult.h>
#include <cppunit/XmlTestResultOutputter.h>
#include "OutputSuite.h"
#include "XmlTestResultOutputterTest.h"
#include "XmlUniformiser.h"


CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( XmlTestResultOutputterTest, 
                                       CppUnitTest::outputSuiteName() );


XmlTestResultOutputterTest::XmlTestResultOutputterTest() : 
    CppUnit::TestCase()
{
}


XmlTestResultOutputterTest::~XmlTestResultOutputterTest()
{
}


void 
XmlTestResultOutputterTest::setUp()
{
}


void 
XmlTestResultOutputterTest::tearDown()
{
}


void 
XmlTestResultOutputterTest::testEmptyNodeToString()
{
  CppUnit::XmlTestResultOutputter::Node node( "element" );
  std::string expectedXml = "<element></element>";
  CPPUNITTEST_ASSERT_XML_EQUAL( expectedXml, node.toString() );
}


void 
XmlTestResultOutputterTest::testNodeWithAttributesToString()
{
  CppUnit::XmlTestResultOutputter::Node node( "element" );
  node.addAttribute( "id", 17 );
  node.addAttribute( "date-format", "iso-8901" );
  std::string expectedXml = "<element id=\"17\" "
                            "date-format=\"iso-8901\">"
                            "</element>";
  CPPUNITTEST_ASSERT_XML_EQUAL( expectedXml, node.toString() );
}


void 
XmlTestResultOutputterTest::testEscapedAttributeValueToString()
{
  CppUnit::XmlTestResultOutputter::Node node( "element" );
  node.addAttribute( "escaped", "&<>\"'" );
  std::string expectedXml = "<element escaped=\""
                            "&amp;&lt;&gt;&quot;&apos;"
                            "\"></element>";
  CPPUNITTEST_ASSERT_XML_EQUAL( expectedXml, node.toString() );
}


void 
XmlTestResultOutputterTest::testNodeWithChildrenToString()
{
  CppUnit::XmlTestResultOutputter::Node node( "element" );
  node.addNode( new CppUnit::XmlTestResultOutputter::Node( "child1" ) );
  node.addNode( new CppUnit::XmlTestResultOutputter::Node( "child2" ) );
  std::string expectedXml = "<element><child1></child1>"
                            "<child2></child2></element>";
  CPPUNITTEST_ASSERT_XML_EQUAL( expectedXml, node.toString() );
}


void 
XmlTestResultOutputterTest::testNodeWithContentToString()
{
  CppUnit::XmlTestResultOutputter::Node node( "element", "content\nline2" );
  std::string expectedXml = "<element>content\nline2</element>";
  CPPUNITTEST_ASSERT_XML_EQUAL( expectedXml, node.toString() );
}


void 
XmlTestResultOutputterTest::testNodeWithNumericContentToString()
{
  CppUnit::XmlTestResultOutputter::Node node( "element", 123456789 );
  std::string expectedXml = "<element>123456789</element>";
  CPPUNITTEST_ASSERT_XML_EQUAL( expectedXml, node.toString() );
}


void 
XmlTestResultOutputterTest::testNodeWithContentAndChildToString()
{
  CppUnit::XmlTestResultOutputter::Node node( "element", "content" );
  node.addNode( new CppUnit::XmlTestResultOutputter::Node( "child1" ) );
  std::string expectedXml = "<element><child1></child1>content</element>";
  CPPUNITTEST_ASSERT_XML_EQUAL( expectedXml, node.toString() );
}


void 
XmlTestResultOutputterTest::testWriteXmlResultWithNoTest()
{
  CppUnit::TestResult result;

  CppUnit::OStringStream stream;
  CppUnit::XmlTestResultOutputter outputter;
  outputter.write( &result, stream );

  std::string actualXml = stream.str();
  std::string expectedXml = 
    "<TestRun>"
      "<FailedTests></FailedTests>"
      "<SucessfulTests></SucessfulTests>"
      "<Statistics>"
        "<Tests>0</Tests>"
        "<FailuresTotal>0</FailuresTotal>"
        "<Errors>0</Errors>"
        "<Failures>0</Failures>"
      "</Statistics>"
    "</TestRun>";
  CPPUNITTEST_ASSERT_XML_EQUAL( expectedXml, actualXml );
}


void 
XmlTestResultOutputterTest::testWriteXmlResultWithOneFailure()
{
  CppUnit::TestResult result;
  CppUnit::TestCase test1( "test1" );
  result.startTest( &test1 );
  CppUnit::SourceLine sourceLine( "test.cpp", 3 );
  result.addFailure( &test1, new CppUnit::Exception( "message failure1", 
                                                     sourceLine ) );
  result.endTest( &test1 );

  CppUnit::OStringStream stream;
  CppUnit::XmlTestResultOutputter outputter;
  outputter.write( &result, stream );

  std::string actualXml = stream.str();
  std::string expectedXml = 
    "<TestRun>"
      "<FailedTests>"
        "<FailedTest id=\"1\">"
          "<Name>test1</Name>"
          "<FailureType>Assertion</FailureType>"
          "<Location>"
            "<File>test.cpp</File>"
            "<Line>3</Line>"
          "</Location>"
          "message failure1"
        "</FailedTest>"
      "</FailedTests>"
      "<SucessfulTests></SucessfulTests>"
      "<Statistics>"
        "<Tests>1</Tests>"
        "<FailuresTotal>1</FailuresTotal>"
        "<Errors>0</Errors>"
        "<Failures>1</Failures>"
      "</Statistics>"
    "</TestRun>";
  CPPUNITTEST_ASSERT_XML_EQUAL( expectedXml, actualXml );
}


void 
XmlTestResultOutputterTest::testWriteXmlResultWithOneError()
{
  CppUnit::TestResult result;
  CppUnit::TestCase test1( "test1" );
  result.startTest( &test1 );
  result.addError( &test1, new CppUnit::Exception( "message error1" ) );
  result.endTest( &test1 );

  CppUnit::OStringStream stream;
  CppUnit::XmlTestResultOutputter outputter;
  outputter.write( &result, stream );

  std::string actualXml = stream.str();
  std::string expectedXml = 
    "<TestRun>"
      "<FailedTests>"
        "<FailedTest id=\"1\">"
          "<Name>test1</Name>"
          "<FailureType>Error</FailureType>"
          "message error1"
        "</FailedTest>"
      "</FailedTests>"
      "<SucessfulTests></SucessfulTests>"
      "<Statistics>"
        "<Tests>1</Tests>"
        "<FailuresTotal>1</FailuresTotal>"
        "<Errors>1</Errors>"
        "<Failures>0</Failures>"
      "</Statistics>"
    "</TestRun>";
  CPPUNITTEST_ASSERT_XML_EQUAL( expectedXml, actualXml );
}


void 
XmlTestResultOutputterTest::testWriteXmlResultWithOneSucess()
{
  CppUnit::TestResult result;
  CppUnit::TestCase test1( "test1" );
  result.startTest( &test1 );
  result.endTest( &test1 );

  CppUnit::OStringStream stream;
  CppUnit::XmlTestResultOutputter outputter;
  outputter.write( &result, stream );

  std::string actualXml = stream.str();
  std::string expectedXml = 
    "<TestRun>"
      "<FailedTests></FailedTests>"
      "<SucessfulTests>"
        "<Test id=\"1\">"
          "<Name>test1</Name>"
        "</Test>"
      "</SucessfulTests>"
      "<Statistics>"
        "<Tests>1</Tests>"
        "<FailuresTotal>0</FailuresTotal>"
        "<Errors>0</Errors>"
        "<Failures>0</Failures>"
      "</Statistics>"
    "</TestRun>";
  CPPUNITTEST_ASSERT_XML_EQUAL( expectedXml, actualXml );
}


void 
XmlTestResultOutputterTest::testWriteXmlResultWithThreeFailureTwoErrorsAndTwoSucess()
{
  CppUnit::TestCase test1( "test1" );
  CppUnit::TestCase test2( "test2" );
  CppUnit::TestCase test3( "test3" );
  CppUnit::TestCase test4( "test4" );
  CppUnit::TestCase test5( "test5" );
  CppUnit::TestCase test6( "test6" );
  CppUnit::TestCase test7( "test7" );
  CppUnit::TestResult result;
  result.startTest( &test1 );
  result.addFailure( &test1, new CppUnit::Exception( "failure1" ) );
  result.endTest( &test1 );
  result.startTest( &test2 );
  result.addError( &test2, new CppUnit::Exception( "error1" ) );
  result.endTest( &test2 );
  result.startTest( &test3 );
  result.addFailure( &test3, new CppUnit::Exception( "failure2" ) );
  result.endTest( &test3 );
  result.startTest( &test4 );
  result.addFailure( &test4, new CppUnit::Exception( "failure3" ) );
  result.endTest( &test4 );
  result.startTest( &test5 );
  result.endTest( &test5 );
  result.startTest( &test6 );
  result.addError( &test6, new CppUnit::Exception( "error2" ) );
  result.endTest( &test6 );
  result.startTest( &test7 );
  result.endTest( &test7 );

  CppUnit::OStringStream stream;
  CppUnit::XmlTestResultOutputter outputter;
  outputter.write( &result, stream );

  std::string actualXml = stream.str();
  std::string expectedXml = 
    "<TestRun>"
       "<FailedTests>"
        "<FailedTest id=\"1\">"
          "<Name>test1</Name>"
          "<FailureType>Assertion</FailureType>"
          "failure1"
        "</FailedTest>"
        "<FailedTest id=\"2\">"
          "<Name>test2</Name>"
          "<FailureType>Error</FailureType>"
          "error1"
        "</FailedTest>"
        "<FailedTest id=\"3\">"
          "<Name>test3</Name>"
          "<FailureType>Assertion</FailureType>"
          "failure2"
        "</FailedTest>"
        "<FailedTest id=\"4\">"
          "<Name>test4</Name>"
          "<FailureType>Assertion</FailureType>"
          "failure3"
        "</FailedTest>"
        "<FailedTest id=\"6\">"
          "<Name>test6</Name>"
          "<FailureType>Error</FailureType>"
          "error2"
        "</FailedTest>"
      "</FailedTests>"
     "<SucessfulTests>"
        "<Test id=\"5\">"
          "<Name>test5</Name>"
        "</Test>"
        "<Test id=\"7\">"
          "<Name>test7</Name>"
        "</Test>"
      "</SucessfulTests>"
      "<Statistics>"
        "<Tests>7</Tests>"
        "<FailuresTotal>5</FailuresTotal>"
        "<Errors>2</Errors>"
        "<Failures>3</Failures>"
      "</Statistics>"
    "</TestRun>";
  CPPUNITTEST_ASSERT_XML_EQUAL( expectedXml, actualXml );
}