#include <cppunit/TextTestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include "CppUnitTestSuite.h"

int 
main( int argc, char* argv[] )
{
  CppUnit::TextTestRunner runner;
  runner.addTest( CppUnitTest::suite() );

  bool wasSucessful = runner.run();

  return wasSucessful ? 0 : 1;
}

