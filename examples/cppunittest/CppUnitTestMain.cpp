#include <cppunit/TextTestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

int 
main( int argc, char* argv[] )
{
  CppUnit::TextTestRunner runner;
  runner.addTest( CppUnit::TestFactoryRegistry::getRegistry().makeTest() );

  runner.run();

  return 0;
}

