#ifndef FAILINGTESTCASE_H
#define FAILINGTESTCASE_H

#include <cppunit/TestCase.h>
#include "FailureException.h"


class FailingTestCase : public CppUnit::TestCase
{
public:
  FailingTestCase( bool failSetUp =false,
                   bool failRunTest =false,
                   bool failTearDown =false );

  virtual ~FailingTestCase();

  virtual void setUp();
  virtual void tearDown();

  virtual void runTest();

  void verify( bool runTestCalled =true, 
               bool tearDownCalled =true);

private:
  FailingTestCase( const FailingTestCase &copy );
  void operator =( const FailingTestCase &copy );

  void doFailure( bool shouldFail );

private:
  bool m_failSetUp;
  bool m_failRunTest;
  bool m_failTearDown;

  bool m_setUpCalled;
  bool m_runTestCalled;
  bool m_tearDownCalled;
};


#endif  // FAILINGTESTCASE_H
