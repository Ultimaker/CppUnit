#ifndef TESTSETUPTEST_H
#define TESTSETUPTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestSetUp.h>
#include "FailingTestCase.h"


class TestSetUpTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE( TestSetUpTest );
  CPPUNIT_TEST( testRun );
  CPPUNIT_TEST_SUITE_END();

public:
  TestSetUpTest();
  virtual ~TestSetUpTest();

  virtual void setUp();
  virtual void tearDown();

  void testRun();

private:
  class SetUp : public CppUnit::TestSetUp
  {
  public:
    SetUp( CppUnit::Test *test ) : 
        CppUnit::TestSetUp( test ),
        m_setUpCalled( false ),
        m_tearDownCalled( false )
    {
    }

    void setUp() 
    {
      m_setUpCalled = true;
    }

    void tearDown()
    {
      m_tearDownCalled = true;
    }

    bool m_setUpCalled;
    bool m_tearDownCalled;
  };

  TestSetUpTest( const TestSetUpTest &copy );
  void operator =( const TestSetUpTest &copy );

private:
  SetUp *m_setUp;
  FailingTestCase *m_test;
};



#endif  // TESTSETUPTEST_H
