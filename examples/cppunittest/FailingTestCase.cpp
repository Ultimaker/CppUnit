#include "FailingTestCase.h"


FailingTestCase::FailingTestCase( bool failSetUp,
                                  bool failRunTest,
                                  bool failTearDown ) :
  CppUnit::TestCase( "FailingTestCase" ),
  m_failSetUp( failSetUp ),
  m_failRunTest( failRunTest ),
  m_failTearDown( failTearDown ),
  m_setUpCalled( false ),
  m_runTestCalled( false ),
  m_tearDownCalled( false )
{
}


FailingTestCase::~FailingTestCase()
{
}


void 
FailingTestCase::setUp()
{
  m_setUpCalled = true;
  doFailure( m_failSetUp );
}


void 
FailingTestCase::tearDown()
{
  m_tearDownCalled = true;
  doFailure( m_failTearDown );
}


void 
FailingTestCase::runTest()
{
  m_runTestCalled = true;
  doFailure( m_failRunTest );
}


void
FailingTestCase::doFailure( bool shouldFail )
{
  if ( shouldFail )
    throw FailureException();
}


void 
FailingTestCase::verify( bool runTestCalled, 
                         bool tearDownCalled )
{
  CPPUNIT_ASSERT( m_setUpCalled );
  CPPUNIT_ASSERT_EQUAL( runTestCalled, m_runTestCalled );
  CPPUNIT_ASSERT_EQUAL( tearDownCalled, m_tearDownCalled );
}
