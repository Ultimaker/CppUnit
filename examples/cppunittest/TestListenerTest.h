#ifndef TESTLISTENERTEST_H
#define TESTLISTENERTEST_H

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestListener.h>


class TestListenerTest : public CppUnit::TestCase,
                         public CppUnit::TestListener
{
public:
  TestListenerTest();

  virtual ~TestListenerTest();

  static CppUnit::TestSuite *suite();

  virtual void setUp();
  virtual void tearDown();

  void testAddErrorListener();
  void testAddFailureListener();
  void testStartTestListener();
  void testEndTestListener();

  void testNoListener();
  void testTwoListener();

  void testRemoveLastListener();
  void testRemoveFrontListener();

private:
  enum ListenerCallbackType {
    undefined,
    onAddError,
    onAddFailure,
    onStartTest,
    onEndTest
  };

  virtual void addError( CppUnit::Test *test, CppUnit::Exception *e );
  virtual void addFailure( CppUnit::Test *test, CppUnit::Exception *e );
  virtual void startTest( CppUnit::Test *test );
  virtual void endTest( CppUnit::Test *test );

  CppUnit::Exception *makeDummyError();

  TestListenerTest( const TestListenerTest &copy );
  void operator =( const TestListenerTest &copy );

private:
  CppUnit::Test *m_listenerTest;
  CppUnit::Exception *m_listenerError;
  CppUnit::Test *m_dummyTest;
  CppUnit::Exception *m_dummyError;
  CppUnit::TestResult *m_result;
  ListenerCallbackType m_listenerCallbackType;
};


#endif  // TESTLISTENERTEST_H
