#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/CompilerOutputter.h>
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
    CppUnit::CompilerOutputter *outputter = 
        CppUnit::CompilerOutputter::defaultOutputter( runner.result(),
                                                      std::cerr );
    outputter->write();
    delete outputter;
  }

  return wasSucessful ? 0 : 1;
}

