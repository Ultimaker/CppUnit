#include <cppunit/tools/XmlElement.h>
#include "ToolsSuite.h"
#include "XmlElementTest.h"
#include "XmlUniformiser.h"


CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( XmlElementTest, 
                                       CppUnitTest::toolsSuiteName() );


XmlElementTest::XmlElementTest()
{
}


XmlElementTest::~XmlElementTest()
{
}


void 
XmlElementTest::setUp()
{
}


void 
XmlElementTest::tearDown()
{
}


void 
XmlElementTest::testEmptyNodeToString()
{
  CppUnit::XmlElement node( "element" );
  std::string expectedXml = "<element></element>";
  CPPUNITTEST_ASSERT_XML_EQUAL( expectedXml, node.toString() );
}


void 
XmlElementTest::testNodeWithAttributesToString()
{
  CppUnit::XmlElement node( "element" );
  node.addAttribute( "id", 17 );
  node.addAttribute( "date-format", "iso-8901" );
  std::string expectedXml = "<element id=\"17\" "
                            "date-format=\"iso-8901\">"
                            "</element>";
  CPPUNITTEST_ASSERT_XML_EQUAL( expectedXml, node.toString() );
}


void 
XmlElementTest::testEscapedAttributeValueToString()
{
  CppUnit::XmlElement node( "element" );
  node.addAttribute( "escaped", "&<>\"'" );
  std::string expectedXml = "<element escaped=\""
                            "&amp;&lt;&gt;&quot;&apos;"
                            "\"></element>";
  CPPUNITTEST_ASSERT_XML_EQUAL( expectedXml, node.toString() );
}


void 
XmlElementTest::testNodeToStringEscapeContent()
{
  CppUnit::XmlElement node( "element", "ChessTest<class Chess>" );
  std::string expectedXml = "<element>"
                            "ChessTest&lt;class Chess&gt;"
                            "</element>";
  CPPUNITTEST_ASSERT_XML_EQUAL( expectedXml, node.toString() );
}


void 
XmlElementTest::testNodeWithChildrenToString()
{
  CppUnit::XmlElement node( "element" );
  node.addNode( new CppUnit::XmlElement( "child1" ) );
  node.addNode( new CppUnit::XmlElement( "child2" ) );
  std::string expectedXml = "<element><child1></child1>"
                            "<child2></child2></element>";
  CPPUNITTEST_ASSERT_XML_EQUAL( expectedXml, node.toString() );
}


void 
XmlElementTest::testNodeWithContentToString()
{
  CppUnit::XmlElement node( "element", "content\nline2" );
  std::string expectedXml = "<element>content\nline2</element>";
  CPPUNITTEST_ASSERT_XML_EQUAL( expectedXml, node.toString() );
}


void 
XmlElementTest::testNodeWithNumericContentToString()
{
  CppUnit::XmlElement node( "element", 123456789 );
  std::string expectedXml = "<element>123456789</element>";
  CPPUNITTEST_ASSERT_XML_EQUAL( expectedXml, node.toString() );
}


void 
XmlElementTest::testNodeWithContentAndChildToString()
{
  CppUnit::XmlElement node( "element", "content" );
  node.addNode( new CppUnit::XmlElement( "child1" ) );
  std::string expectedXml = "<element><child1></child1>content</element>";
  CPPUNITTEST_ASSERT_XML_EQUAL( expectedXml, node.toString() );
}
