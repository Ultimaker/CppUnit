#include <cppunit/extensions/TestFactoryRegistry.h>
#include "CppUnitTestSuite.h"
#include "CoreSuite.h"
#include "HelperSuite.h"
#include "ExtensionSuite.h"


namespace CppUnitTest
{

CppUnit::Test *
suite()
{
  CppUnit::TestFactoryRegistry &registry = 
                      CppUnit::TestFactoryRegistry::getRegistry();

  registry.registerFactory( 
      &CppUnit::TestFactoryRegistry::getRegistry( coreSuiteName() ) );
  registry.registerFactory( 
      &CppUnit::TestFactoryRegistry::getRegistry( helperSuiteName() ) );
  registry.registerFactory( 
      &CppUnit::TestFactoryRegistry::getRegistry( extensionSuiteName() ) );

  return registry.makeTest();
}


}  // namespace CppUnitTest
