#ifndef CPPUNITEST_XMLELEMENTTEST_H
#define CPPUNITEST_XMLELEMENTTEST_H

#include <cppunit/extensions/HelperMacros.h>


/*! Unit tests for XmlElement.
 */
class XmlElementTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( XmlElementTest );
  CPPUNIT_TEST( testStringContentConstructor );
  CPPUNIT_TEST( testNumericContentConstructor );
  CPPUNIT_TEST( testSetName );
  CPPUNIT_TEST( testSetStringContent );
  CPPUNIT_TEST( testSetNumericContent );
  CPPUNIT_TEST( testNodeCount );
  CPPUNIT_TEST_EXCEPTION( testElementAtNegativeIndexThrow, std::invalid_argument );
  CPPUNIT_TEST_EXCEPTION( testElementAtTooLargeIndexThrow, std::invalid_argument );
  CPPUNIT_TEST( testElementAt );
  CPPUNIT_TEST_EXCEPTION( testElementForThrow, std::invalid_argument );
  CPPUNIT_TEST( testElementFor );

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

  void testStringContentConstructor();
  void testNumericContentConstructor();
  void testSetName();
  void testSetStringContent();
  void testSetNumericContent();
  void testNodeCount();
  void testElementAtNegativeIndexThrow();
  void testElementAtTooLargeIndexThrow();
  void testElementAt();
  void testElementForThrow();
  void testElementFor();

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
