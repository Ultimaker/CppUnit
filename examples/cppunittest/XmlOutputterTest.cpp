#include <cppunit/XmlOutputter.h>
#include <cppunit/TestFailure.h>
#include <cppunit/XmlOutputter.h>
#include "OutputSuite.h"
#include "XmlOutputterTest.h"
#include "XmlUniformiser.h"


CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( XmlOutputterTest, 
                                       CppUnitTest::outputSuiteName() );


XmlOutputterTest::XmlOutputterTest()
{
}


XmlOutputterTest::~XmlOutputterTest()
{
}


void 
XmlOutputterTest::setUp()
{
  m_dummyTests.clear();
  m_result = new CppUnit::TestResultCollector();
}


void 
XmlOutputterTest::tearDown()
{
  delete m_result;
  for ( int index =0; index < m_dummyTests.size(); ++index )
    delete m_dummyTests[index];
  m_dummyTests.clear();
}


void 
XmlOutputterTest::testWriteXmlResultWithNoTest()
{
  CppUnit::OStringStream stream;
  CppUnit::XmlOutputter outputter( m_result, stream );
  outputter.write();

  std::string actualXml = stream.str();
  std::string expectedXml = 
    "<TestRun>"
      "<FailedTests></FailedTests>"
      "<SuccessfulTests></SuccessfulTests>"
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
XmlOutputterTest::testWriteXmlResultWithOneFailure()
{
  addTestFailure( "test1", "message failure1", CppUnit::SourceLine( "test.cpp", 3 ) );

  CppUnit::OStringStream stream;
  CppUnit::XmlOutputter outputter( m_result, stream );
  outputter.write();

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
          "<Message>message failure1</Message>"
        "</FailedTest>"
      "</FailedTests>"
      "<SuccessfulTests></SuccessfulTests>"
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
XmlOutputterTest::testWriteXmlResultWithOneError()
{
  addTestError( "test1", "message error1" );

  CppUnit::OStringStream stream;
  CppUnit::XmlOutputter outputter( m_result, stream );
  outputter.write();

  std::string actualXml = stream.str();
  std::string expectedXml = 
    "<TestRun>"
      "<FailedTests>"
        "<FailedTest id=\"1\">"
          "<Name>test1</Name>"
          "<FailureType>Error</FailureType>"
          "<Message>message error1</Message>"
        "</FailedTest>"
      "</FailedTests>"
      "<SuccessfulTests></SuccessfulTests>"
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
XmlOutputterTest::testWriteXmlResultWithOneSuccess()
{
  addTest( "test1" );

  CppUnit::OStringStream stream;
  CppUnit::XmlOutputter outputter( m_result, stream );
  outputter.write();

  std::string actualXml = stream.str();
  std::string expectedXml = 
    "<TestRun>"
      "<FailedTests></FailedTests>"
      "<SuccessfulTests>"
        "<Test id=\"1\">"
          "<Name>test1</Name>"
        "</Test>"
      "</SuccessfulTests>"
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
XmlOutputterTest::testWriteXmlResultWithThreeFailureTwoErrorsAndTwoSuccess()
{
  addTestFailure( "test1", "failure1" );
  addTestError( "test2", "error1" );
  addTestFailure( "test3", "failure2" );
  addTestFailure( "test4", "failure3" );
  addTest( "test5" );
  addTestError( "test6", "error2" );
  addTest( "test7" );

  CppUnit::OStringStream stream;
  CppUnit::XmlOutputter outputter( m_result, stream );
  outputter.write();

  std::string actualXml = stream.str();
  std::string expectedXml = 
    "<TestRun>"
       "<FailedTests>"
        "<FailedTest id=\"1\">"
          "<Name>test1</Name>"
          "<FailureType>Assertion</FailureType>"
          "<Message>failure1</Message>"
        "</FailedTest>"
        "<FailedTest id=\"2\">"
          "<Name>test2</Name>"
          "<FailureType>Error</FailureType>"
          "<Message>error1</Message>"
        "</FailedTest>"
        "<FailedTest id=\"3\">"
          "<Name>test3</Name>"
          "<FailureType>Assertion</FailureType>"
          "<Message>failure2</Message>"
        "</FailedTest>"
        "<FailedTest id=\"4\">"
          "<Name>test4</Name>"
          "<FailureType>Assertion</FailureType>"
          "<Message>failure3</Message>"
        "</FailedTest>"
        "<FailedTest id=\"6\">"
          "<Name>test6</Name>"
          "<FailureType>Error</FailureType>"
          "<Message>error2</Message>"
        "</FailedTest>"
      "</FailedTests>"
     "<SuccessfulTests>"
        "<Test id=\"5\">"
          "<Name>test5</Name>"
        "</Test>"
        "<Test id=\"7\">"
          "<Name>test7</Name>"
        "</Test>"
      "</SuccessfulTests>"
      "<Statistics>"
        "<Tests>7</Tests>"
        "<FailuresTotal>5</FailuresTotal>"
        "<Errors>2</Errors>"
        "<Failures>3</Failures>"
      "</Statistics>"
    "</TestRun>";
  CPPUNITTEST_ASSERT_XML_EQUAL( expectedXml, actualXml );
}


void 
XmlOutputterTest::addTest( std::string testName )
{
  CppUnit::Test *test = makeDummyTest( testName );
  m_result->startTest( test );
  m_result->endTest( test );
}


void 
XmlOutputterTest::addTestFailure( std::string testName,
                                  std::string message,
                                  CppUnit::SourceLine sourceLine )
{
  addGenericTestFailure( testName, CppUnit::Message(message), sourceLine, false );
}


void 
XmlOutputterTest::addTestError( std::string testName,
                                std::string message,
                                CppUnit::SourceLine sourceLine )
{
  addGenericTestFailure( testName, CppUnit::Message(message), sourceLine, true );
}


void 
XmlOutputterTest::addGenericTestFailure(  std::string testName,
                                          CppUnit::Message message,
                                          CppUnit::SourceLine sourceLine,
                                          bool isError )
{
  CppUnit::Test *test = makeDummyTest( testName );
  m_result->startTest( test );
  CppUnit::TestFailure failure( test, 
                                new CppUnit::Exception( message, sourceLine ),
                                isError );
  m_result->addFailure( failure );
  m_result->endTest( test );
}


CppUnit::Test *
XmlOutputterTest::makeDummyTest( std::string testName )
{
  CppUnit::Test *test = new CppUnit::TestCase( testName );
  m_dummyTests.push_back( test );
  return test;
}
