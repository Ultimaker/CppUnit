#ifndef TESTFAILURETEST_H
#define TESTFAILURETEST_H

#include <cppunit/extensions/HelperMacros.h>


class TestFailureTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE( TestFailureTest );
  CPPUNIT_TEST( testConstructorAndGetters );
  CPPUNIT_TEST_SUITE_END();

public:
  TestFailureTest();
  virtual ~TestFailureTest();

  virtual void setUp();
  virtual void tearDown();

  void testConstructorAndGetters();

  void exceptionDestroyed();

private:
  class ObservedException : public CppUnit::Exception
  {
  public:
    ObservedException( TestFailureTest *listener ) : 
        CppUnit::Exception( "ObservedException" ),
        m_listener( listener )
    {
    }

    virtual ~ObservedException() 
    {
      m_listener->exceptionDestroyed();
    }
  private:
    TestFailureTest *m_listener;
  };


  TestFailureTest( const TestFailureTest &copy );
  void operator =( const TestFailureTest &copy );
  void checkTestFailure( CppUnit::Test *test, 
                         CppUnit::Exception *error );

private:
  bool m_exceptionDestroyed;
};



#endif  // TESTFAILURETEST_H
