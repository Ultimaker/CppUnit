#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestPath.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/TextTestProgressListener.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/plugin/DynamicLibraryManagerException.h>
#include <cppunit/plugin/Parameters.h>
#include <cppunit/plugin/PlugInManager.h>
#include <cppunit/plugin/TestPlugIn.h>
#include <iostream>


/*! Runs the specified tests located in the root suite.
 * \param parameters List of string representing the command line arguments.
 * \return \c true if the run succeed, \c false if a test failed or if a test
 *         path was not resolved.
 */
bool 
runTests( CppUnit::Parameters parameters )
{
  CppUnit::TestResult controller;
  CppUnit::TestResultCollector result;
  controller.addListener( &result );        
//  CppUnit::TextTestProgressListener progress;
  CppUnit::BriefTestProgressListener progress;
  controller.addListener( &progress );      

  std::string testPath;
  CppUnit::PlugInManager plugInManager;
  // Loads plug-ins & get test path.
  for ( int index =0; index < parameters.size(); ++index )
  {
    std::string parameter = parameters[index];
    if ( parameter[0] == ':' )
      testPath = parameter.substr(1);
    else
      plugInManager.load( parameter );
  }

  // Registers plug-in specific TestListener (global setUp/tearDown, custom TestListener...)
  plugInManager.addListener( &controller );

  // Adds the default registry suite
  CppUnit::TestRunner runner;
  runner.addTest( CppUnit::TestFactoryRegistry::getRegistry().makeTest() );

  // Runs the specified test
  try
  {
    runner.run( controller );
  }
  catch ( std::invalid_argument & )
  {
    std::cerr  <<  "Failed to resolve test path: "  <<  testPath  <<  std::endl;
    return false;
  }

  // Removes plug-in specific TestListener (not really needed but...)
  plugInManager.removeListener( &controller );

  std::cerr << std::endl;

  // Outputs test result
  CppUnit::CompilerOutputter outputter( &result, std::cerr );
  outputter.write();

  return result.wasSuccessful();
}


/*! Main
 * 
 * Usage: 
 *
 * DllPlugInTester.exe dll-filename1 [dll-filename2 [dll-filename3 ...]] [:testpath]
 *
 * <em>dll-filename</em> must be the name of the DLL. If the DLL use some other DLL, they
 * should be in the path or in the same directory as the DLL. The DLL must export
 * a function named "GetTestPlugInInterface" with the signature
 * GetTestPlugInInterfaceFunction. Both are defined in:
 * \code
 * #include <msvc6/testrunner/TestPlugInInterface.h>
 * \endcode.
 *
 * See examples/msvc6/TestPlugIn for an example of post-build testing.
 *
 * If no test path is specified, they all the test of the suite returned by the DLL
 * are run. If a test path is specified, then only the specified test is run. The test
 * path must be prefixed by ':'.
 *
 * Test paths are resolved using Test::resolveTestPath() on the suite returned by
 * TestFactoryRegistry::getRegistry().makeTest();
 *
 * If all test succeed and no error happen then the application exit with code 0.
 * If any error occurs (failed to load dll, failed to resolve test paths) or a 
 * test fail, the application exit with code 1.
 */
int 
main( int argc, 
      char *argv[] )
{
  const int successReturnCode = 0;
  const int failureReturnCode = 1;

  // check command line
  std::string applicationName( argv[0] );
  if ( argc < 2 )
  {
    std::cerr  <<  "Usage: "  <<  std::endl
           <<  applicationName 
           <<  " dll-filename1 [dll-filename2 ...] [:test-path]..."
           <<  std::endl;
    return failureReturnCode;
  }

  bool wasSuccessful = false;
  try
  {
    CppUnit::Parameters parameters;
    for ( int index =1; index < argc; ++index )
      parameters.push_back( argv[index] );
    wasSuccessful = runTests( parameters );
  }
  catch ( CppUnit::DynamicLibraryManagerException &e )
  {
    std::cerr  << "Failed to load test plug-in:"  <<  std::endl
               << e.what() << std::endl;
  }

  return wasSuccessful ? successReturnCode : failureReturnCode;
}


