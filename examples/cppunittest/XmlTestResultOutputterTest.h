#ifndef CPPUNITEST_XMLTESTRESULTOUTPUTTERTEST_H
#define CPPUNITEST_XMLTESTRESULTOUTPUTTERTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFailure.h>


/*! \class XmlTestResultOutputterTest
 * \brief Unit tests for XmlTestResultOutputter.
 */
class XmlTestResultOutputterTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE( XmlTestResultOutputterTest );
  CPPUNIT_TEST( testEmptyNodeToString );
  CPPUNIT_TEST( testNodeWithAttributesToString );
  CPPUNIT_TEST( testEscapedAttributeValueToString );
  CPPUNIT_TEST( testNodeWithChildrenToString );
  CPPUNIT_TEST( testNodeWithContentToString );
  CPPUNIT_TEST( testNodeWithNumericContentToString );
  CPPUNIT_TEST( testNodeWithContentAndChildToString );
  CPPUNIT_TEST( testWriteXmlResultWithNoTest );
  CPPUNIT_TEST( testWriteXmlResultWithOneFailure );
  CPPUNIT_TEST( testWriteXmlResultWithOneError );
  CPPUNIT_TEST( testWriteXmlResultWithOneSucess );
  CPPUNIT_TEST( testWriteXmlResultWithThreeFailureTwoErrorsAndTwoSucess );
  CPPUNIT_TEST_SUITE_END();

public:
  /*! Constructs a XmlTestResultOutputterTest object.
   */
  XmlTestResultOutputterTest();

  /// Destructor.
  virtual ~XmlTestResultOutputterTest();

  void setUp();
  void tearDown();

  void testEmptyNodeToString();
  void testNodeWithAttributesToString();
  void testEscapedAttributeValueToString();
  void testNodeWithChildrenToString();
  void testNodeWithContentToString();
  void testNodeWithNumericContentToString();
  void testNodeWithContentAndChildToString();

  void testWriteXmlResultWithNoTest();
  void testWriteXmlResultWithOneFailure();
  void testWriteXmlResultWithOneError();
  void testWriteXmlResultWithOneSucess();
  void testWriteXmlResultWithThreeFailureTwoErrorsAndTwoSucess();

private:
  /// Prevents the use of the copy constructor.
  XmlTestResultOutputterTest( const XmlTestResultOutputterTest &copy );

  /// Prevents the use of the copy operator.
  void operator =( const XmlTestResultOutputterTest &copy );

  std::string statistics( int tests, 
                          int total, 
                          int error, 
                          int failure );

private:
};



#endif  // CPPUNITEST_XMLTESTRESULTOUTPUTTERTEST_H
