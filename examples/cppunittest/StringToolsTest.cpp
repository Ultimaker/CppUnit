#include "StringToolsTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION( StringToolsTest );


StringToolsTest::StringToolsTest()
{
}


StringToolsTest::~StringToolsTest()
{
}


void 
StringToolsTest::setUp()
{
}


void 
StringToolsTest::tearDown()
{
}


void 
StringToolsTest::testToStringInt()
{
  std::string expected = "123456789";
  std::string actual = CppUnit::StringTools::toString( 123456789 );
  CPPUNIT_ASSERT_EQUAL( expected, actual );
}


void 
StringToolsTest::testToStringDouble()
{
  std::string expected = "1234.56";
  std::string actual = CppUnit::StringTools::toString( 1234.56 );
  CPPUNIT_ASSERT_EQUAL( expected, actual );
}


void 
StringToolsTest::testSplitEmptyString()
{
  std::string text;
  CppUnit::StringTools::Strings expected;
  CppUnit::StringTools::Strings actual = CppUnit::StringTools::split( text, ';' );

  CPPUNIT_ASSERT_EQUAL( expected.size(), actual.size() );
  CPPUNIT_ASSERT( expected == actual );
}


void 
StringToolsTest::testSplitOneItem()
{
  std::string text = "1";
  CppUnit::StringTools::Strings expected;
  expected.push_back( "1" );
  CppUnit::StringTools::Strings actual = CppUnit::StringTools::split( text, ';' );

  CPPUNIT_ASSERT_EQUAL( expected.size(), actual.size() );
  CPPUNIT_ASSERT( expected == actual );
}


void 
StringToolsTest::testSplitItemEmpty()
{
  std::string text = "1;";
  CppUnit::StringTools::Strings expected;
  expected.push_back( "1" );
  expected.push_back( "" );
  CppUnit::StringTools::Strings actual = CppUnit::StringTools::split( text, ';' );

  CPPUNIT_ASSERT_EQUAL( expected.size(), actual.size() );
  CPPUNIT_ASSERT( expected == actual );
}


void 
StringToolsTest::testSplitTwoItem()
{
  std::string text = "2;1";
  CppUnit::StringTools::Strings expected;
  expected.push_back( "2" );
  expected.push_back( "1" );
  CppUnit::StringTools::Strings actual = CppUnit::StringTools::split( text, ';' );

  CPPUNIT_ASSERT_EQUAL( expected.size(), actual.size() );
  CPPUNIT_ASSERT( expected == actual );
}


void 
StringToolsTest::testSplitEmptyTwoItem()
{
  std::string text = ";1;2";
  CppUnit::StringTools::Strings expected;
  expected.push_back( "" );
  expected.push_back( "1" );
  expected.push_back( "2" );
  CppUnit::StringTools::Strings actual = CppUnit::StringTools::split( text, ';' );

  CPPUNIT_ASSERT_EQUAL( expected.size(), actual.size() );
  CPPUNIT_ASSERT( expected == actual );
}


void 
StringToolsTest::testSplitEmptyItemEmpty()
{
  std::string text = ";1;";
  CppUnit::StringTools::Strings expected;
  expected.push_back( "" );
  expected.push_back( "1" );
  expected.push_back( "" );
  CppUnit::StringTools::Strings actual = CppUnit::StringTools::split( text, ';' );

  CPPUNIT_ASSERT_EQUAL( expected.size(), actual.size() );
  CPPUNIT_ASSERT( expected == actual );
}


void 
StringToolsTest::testSplitEmptyItemEmptyEmptyItem()
{
  std::string text = ";1;;;2";
  CppUnit::StringTools::Strings expected;
  expected.push_back( "" );
  expected.push_back( "1" );
  expected.push_back( "" );
  expected.push_back( "" );
  expected.push_back( "2" );
  CppUnit::StringTools::Strings actual = CppUnit::StringTools::split( text, ';' );

  CPPUNIT_ASSERT_EQUAL( expected.size(), actual.size() );
  CPPUNIT_ASSERT( expected == actual );
}


void 
StringToolsTest::testWrapEmpty()
{
  std::string text = "";
  std::string expected = "";

  std::string actual = CppUnit::StringTools::wrap( text, 6 );
  CPPUNIT_ASSERT_EQUAL( expected, actual );
}


void 
StringToolsTest::testWrapNotNeeded()
{
  std::string text = "abcd";
  std::string expected = text;

  std::string actual = CppUnit::StringTools::wrap( text, 6 );
  CPPUNIT_ASSERT_EQUAL( expected, actual );
}


void 
StringToolsTest::testWrapLimitNotNeeded()
{
  std::string text = "abcdef";
  std::string expected = text;

  std::string actual = CppUnit::StringTools::wrap( text, 6 );
  CPPUNIT_ASSERT_EQUAL( expected, actual );
}


void 
StringToolsTest::testWrapOneNeeded()
{
  std::string text = "abcdefghi";
  std::string expected = "abcdef\nghi";

  std::string actual = CppUnit::StringTools::wrap( text, 6 );
  CPPUNIT_ASSERT_EQUAL( expected, actual );
}


void 
StringToolsTest::testWrapTwoNeeded()
{
  std::string text = "abcdefghijklmnop";
  std::string expected = "abcdef\nghijkl\nmnop";

  std::string actual = CppUnit::StringTools::wrap( text, 6 );
  CPPUNIT_ASSERT_EQUAL( expected, actual );
}


void 
StringToolsTest::testWrapLimitTwoNeeded()
{
  std::string text = "abcdefghijklmnopqr";
  std::string expected = "abcdef\nghijkl\nmnopqr";

  std::string actual = CppUnit::StringTools::wrap( text, 6 );
  CPPUNIT_ASSERT_EQUAL( expected, actual );
}


void 
StringToolsTest::testWrapOneNeededTwoNeeded()
{
  std::string text = "123456789\nabcdefghijklmno";
  std::string expected = "123456\n789\nabcdef\nghijkl\nmno";

  std::string actual = CppUnit::StringTools::wrap( text, 6 );
  CPPUNIT_ASSERT_EQUAL( expected, actual );
}


void 
StringToolsTest::testWrapNotNeededEmptyLinesOneNeeded()
{
  std::string text = "12345\n\n\n\nabcdefghi";
  std::string expected = "12345\n\n\n\nabcdef\nghi";

  std::string actual = CppUnit::StringTools::wrap( text, 6 );
  CPPUNIT_ASSERT_EQUAL( expected, actual );
}

