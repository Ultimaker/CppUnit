#ifndef CPPUNITEST_XMLTESTRESULTOUTPUTTERTEST_H
#define CPPUNITEST_XMLTESTRESULTOUTPUTTERTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/Test.h>
#include <cppunit/TestFailure.h>
#include <cppunit/TestResultCollector.h>
#include <deque>


/*! \class XmlOutputterTest
 * \brief Unit tests for XmlOutputter.
 */
class XmlOutputterTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( XmlOutputterTest );
  CPPUNIT_TEST( testWriteXmlResultWithNoTest );
  CPPUNIT_TEST( testWriteXmlResultWithOneFailure );
  CPPUNIT_TEST( testWriteXmlResultWithOneError );
  CPPUNIT_TEST( testWriteXmlResultWithOneSuccess );
  CPPUNIT_TEST( testWriteXmlResultWithThreeFailureTwoErrorsAndTwoSuccess );
  CPPUNIT_TEST( testHook );
  CPPUNIT_TEST_SUITE_END();

public:
  /*! Constructs a XmlOutputterTest object.
   */
  XmlOutputterTest();

  /// Destructor.
  virtual ~XmlOutputterTest();

  void setUp();
  void tearDown();
  void testWriteXmlResultWithNoTest();
  void testWriteXmlResultWithOneFailure();
  void testWriteXmlResultWithOneError();
  void testWriteXmlResultWithOneSuccess();
  void testWriteXmlResultWithThreeFailureTwoErrorsAndTwoSuccess();

  void testHook();

private:
  class MockHook;

  /// Prevents the use of the copy constructor.
  XmlOutputterTest( const XmlOutputterTest &copy );

  /// Prevents the use of the copy operator.
  void operator =( const XmlOutputterTest &copy );

  std::string statistics( int tests, 
                          int total, 
                          int error, 
                          int failure );

  void addTest( std::string testName );
  void addTestFailure( std::string testName,
                       std::string message,
                       CppUnit::SourceLine sourceLine = CppUnit::SourceLine() );
  void addTestError( std::string testName,
                     std::string message,
                     CppUnit::SourceLine sourceLine = CppUnit::SourceLine() );
  void addGenericTestFailure( std::string testName,
                              CppUnit::Message message,
                              CppUnit::SourceLine sourceLine,
                              bool isError );

  CppUnit::Test *makeDummyTest( std::string testName );

private:
  CppUnit::TestResultCollector *m_result;
  std::deque<CppUnit::Test *> m_dummyTests;
};



#endif  // CPPUNITEST_XMLTESTRESULTOUTPUTTERTEST_H
