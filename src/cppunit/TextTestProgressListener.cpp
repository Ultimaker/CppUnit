#include <cppunit/TestFailure.h>
#include <cppunit/TextTestProgressListener.h>
#include <iostream>


namespace CppUnit
{


TextTestProgressListener::TextTestProgressListener()
{
}


TextTestProgressListener::~TextTestProgressListener()
{
}


void 
TextTestProgressListener::startTest( Test *test )
{
  std::cerr << ".";
}


void 
TextTestProgressListener::addFailure( const TestFailure &failure )
{
  std::cerr << ( failure.isError() ? "E" : "F" );
}


void 
TextTestProgressListener::done()
{
  std::cerr  <<  std::endl;
}

} //  namespace CppUnit

