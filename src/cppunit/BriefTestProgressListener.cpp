#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/Test.h>
#include <cppunit/TestFailure.h>
#include <iostream>


namespace CppUnit
{


BriefTestProgressListener::BriefTestProgressListener()
    : m_lastTestFailed( false )
{
}


BriefTestProgressListener::~BriefTestProgressListener()
{
}


void 
BriefTestProgressListener::startTest( Test *test )
{
  std::cerr << test->getName();
  std::cerr.flush();

  m_lastTestFailed = false;
}


void 
BriefTestProgressListener::addFailure( const TestFailure &failure )
{
  std::cerr << " : " << (failure.isError() ? "error" : "assertion");
  m_lastTestFailed  = true;
}


void 
BriefTestProgressListener::endTest( Test *test )
{
  if ( !m_lastTestFailed )
    std::cerr  <<  " : OK";
  std::cerr << std::endl;
}


} //  namespace CppUnit

