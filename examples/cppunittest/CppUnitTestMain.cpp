#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/CompilerTestResultOutputter.h>
#include <cppunit/TextTestResult.h>
#include <cppunit/TextTestRunner.h>
#include "CppUnitTestSuite.h"


int 
main( int argc, char* argv[] )
{
  bool selfTest = (argc > 1)  &&  
                  (std::string("-selftest") == argv[1]);

  CppUnit::TextTestRunner runner;
  runner.addTest( CppUnitTest::suite() );

  bool wasSucessful = runner.run( "", false, !selfTest );
  if ( selfTest )
  {  
    CppUnit::CompilerTestResultOutputter outputter( runner.result(),
                                                    std::cerr );
    outputter.write();
  }

  return wasSucessful ? 0 : 1;
}

