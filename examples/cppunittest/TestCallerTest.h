#ifndef TESTCALLERTEST_H
#define TESTCALLERTEST_H

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include "TrackedTestCase.h"


class TestCallerTest : public CppUnit::TestCase, 
                              Tracker
{
public:
  /*! Constructs a TestCallerTest object.
   */
  TestCallerTest();

  /*! Destructor.
   */
  virtual ~TestCallerTest();

  static CppUnit::TestSuite *suite();

  virtual void setUp();
  virtual void tearDown();

  void testBasicConstructor();
  void testReferenceConstructor();
  void testPointerConstructor();

private:
  virtual void onConstructor();
  virtual void onDestructor();
  virtual void onSetUp();
  virtual void onTearDown();
  virtual void onTest();

  void checkNothingButConstructorCalled();
  void checkRunningSequenceCalled();
  void checkTestName( std::string testName );

  /// Prevents the use of the copy constructor.
  TestCallerTest( const TestCallerTest &copy );

  /// Prevents the use of the copy operator.
  void operator =( const TestCallerTest &copy );

private:
  int m_constructorCount;
  int m_destructorCount;
  int m_setUpCount;
  int m_tearDownCount;
  int m_testCount;
  const std::string m_testName;
};



// Inlines methods for TestCallerTest:
// -----------------------------------



#endif  // TESTCALLERTEST_H
