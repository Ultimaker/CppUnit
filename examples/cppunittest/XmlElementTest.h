#ifndef CPPUNITEST_XMLELEMENTTEST_H
#define CPPUNITEST_XMLELEMENTTEST_H

#include <cppunit/extensions/HelperMacros.h>


/*! Unit tests for XmlElement.
 */
class XmlElementTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( XmlElementTest );
  CPPUNIT_TEST( testEmptyNodeToString );
  CPPUNIT_TEST( testNodeWithAttributesToString );
  CPPUNIT_TEST( testEscapedAttributeValueToString );
  CPPUNIT_TEST( testNodeToStringEscapeContent );
  CPPUNIT_TEST( testNodeWithChildrenToString );
  CPPUNIT_TEST( testNodeWithContentToString );
  CPPUNIT_TEST( testNodeWithNumericContentToString );
  CPPUNIT_TEST( testNodeWithContentAndChildToString );
  CPPUNIT_TEST_SUITE_END();

public:
  /*! Constructs a XmlElementTest object.
   */
  XmlElementTest();

  /// Destructor.
  virtual ~XmlElementTest();

  void setUp();
  void tearDown();

  void testEmptyNodeToString();
  void testNodeWithAttributesToString();
  void testEscapedAttributeValueToString();
  void testNodeToStringEscapeContent();
  void testNodeWithChildrenToString();
  void testNodeWithContentToString();
  void testNodeWithNumericContentToString();
  void testNodeWithContentAndChildToString();

private:
  /// Prevents the use of the copy constructor.
  XmlElementTest( const XmlElementTest &copy );

  /// Prevents the use of the copy operator.
  void operator =( const XmlElementTest &copy );
};



#endif  // CPPUNITEST_XMLELEMENTTEST_H
