#include "MockTestListener.h"


MockTestListener::MockTestListener()
{
  reset();
}


void 
MockTestListener::addError( CppUnit::Test *test, CppUnit::Exception *e )
{
  m_called = true;
}


void 
MockTestListener::addFailure( CppUnit::Test *test, CppUnit::Exception *e )
{
  m_called = true;
}


void 
MockTestListener::startTest( CppUnit::Test *test )
{
  m_called = true;
}


void 
MockTestListener::endTest( CppUnit::Test *test )
{
  m_called = true;
}


bool 
MockTestListener::wasCalled() const
{
  return m_called;
}


void 
MockTestListener::reset()
{
  m_called = false;
}
