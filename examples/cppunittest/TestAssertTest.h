#ifndef TESTASSERTTEST_H
#define TESTASSERTTEST_H

#include <cppunit/extensions/HelperMacros.h>


class TestAssertTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE( TestAssertTest );
  CPPUNIT_TEST( testAssertTrue );
  CPPUNIT_TEST( testAssertFalse );
  CPPUNIT_TEST( testAssertEqual );
  CPPUNIT_TEST( testAssertMessageTrue );
  CPPUNIT_TEST( testAssertMessageFalse );
  CPPUNIT_TEST( testAssertDoubleEquals );
  CPPUNIT_TEST( testAssertDoubleNotEquals );
  CPPUNIT_TEST( testAssertLongEquals );
  CPPUNIT_TEST( testAssertLongNotEquals );
  CPPUNIT_TEST_SUITE_END();

public:
  TestAssertTest();

  virtual ~TestAssertTest();

  virtual void setUp();
  virtual void tearDown();

  void testAssertTrue();
  void testAssertFalse();
  
  void testAssertEqual();

  void testAssertMessageTrue();
  void testAssertMessageFalse();

  void testAssertDoubleEquals();
  void testAssertDoubleNotEquals();

  void testAssertLongEquals();
  void testAssertLongNotEquals();

private:
  TestAssertTest( const TestAssertTest &copy );
  void operator =( const TestAssertTest &copy );

  void checkDoubleNotEquals( double expected, 
                             double actual, 
                             double delta );

private:
};

#endif  // TESTASSERTTEST_H
