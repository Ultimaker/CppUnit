#include <cppunit/TextTestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include "CppUnitTestSuite.h"

int 
main( int argc, char* argv[] )
{
  CppUnit::TextTestRunner runner;
  runner.addTest( CppUnitTest::suite() );

  runner.run();

  return 0;
}

