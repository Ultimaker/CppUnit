#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/TextTestProgressListener.h>
#include <cppunit/XmlOutputter.h>
#include "CppUnitTestSuite.h"
#include <stdexcept>
#include <fstream>


int 
main( int argc, char* argv[] )
{
  // Retreive test path from command line first argument. Default to "" which resolve
  // to the top level suite.
  std::string testPath = (argc > 1) ? std::string(argv[1]) : "";

  // Create the event manager and test controller
  CppUnit::TestResult controller;

  // Add a listener that colllects test result
  CppUnit::TestResultCollector result;
  controller.addListener( &result );        

  // Add a listener that print dots as test run.
  CppUnit::TextTestProgressListener progress;
  controller.addListener( &progress );      

  // Add the top suite to the test runner
  CppUnit::TestRunner runner;
  runner.addTest( CppUnitTest::suite() );   
  try
  {
    std::cout << "Running "  <<  testPath;
    runner.run( controller, testPath );

    std::cerr << std::endl;

    // Print test in a compiler compatible format.
    CppUnit::CompilerOutputter outputter( &result, std::cerr );
    outputter.write(); 

    std::ofstream file( "tests.xml" );
    CppUnit::XmlOutputter xml( &result, file );
    xml.setStyleSheet( "report.xsl" );
    xml.write();
    file.close();
  }
  catch ( std::invalid_argument &e )  // Test path not resolved
  {
    std::cerr  <<  std::endl  
               <<  "ERROR: "  <<  e.what()
               << std::endl;
    return 0;
  }

  return result.wasSuccessful() ? 0 : 1;
}

