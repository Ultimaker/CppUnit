#if _MSC_VER > 1000     // VC++
#pragma once
#pragma warning( disable : 4786 )   // disable warning debug symbol > 255...
#endif // _MSC_VER > 1000

#include <utility>
#include "cppunit/TestSuite.h"
#include "cppunit/extensions/TestFactoryRegistry.h"
#include "cppunit/extensions/TestSuiteBuilder.h"

#ifdef USE_TYPEINFO
#include "../TypeInfoHelper.h"
#endif // USE_TYPEINFO

namespace CppUnit {

TestFactoryRegistry::TestFactoryRegistry( std::string name ) :
    m_name( name )
{
}


TestFactoryRegistry::~TestFactoryRegistry()
{
}


TestFactoryRegistry &
TestFactoryRegistry::getRegistry()
{
  static TestFactoryRegistry registry;
  return registry;
}


TestFactoryRegistry &
TestFactoryRegistry::getRegistry( const std::string &name )
{
  static NamedRegistries registries;

  TestFactoryRegistry*& registryPointer = registries[ name ];
  if (NULL == registryPointer) {
    registryPointer = new TestFactoryRegistry( name );
  }
  
  return *registryPointer;
}


void 
TestFactoryRegistry::registerFactory( const std::string &name,
                                      AbstractTestFactory *factory )
{
  m_factories[name] = factory;
}


#ifdef USE_TYPEINFO
void 
TestFactoryRegistry::registerFactory( AbstractTestFactory *factory )
{
  std::string name = TypeInfoHelper::getClassName( typeid( *factory ) );
  registerFactory( name, factory );
}
#endif // USE_TYPEINFO

Test *
TestFactoryRegistry::makeTest()
{
  TestSuite *suite = new TestSuite( "All Tests" );
  addTestToSuite( suite );
  return suite;
}


void 
TestFactoryRegistry::addTestToSuite( TestSuite *suite )
{
  for ( Factories::iterator it = m_factories.begin(); 
        it != m_factories.end(); 
        ++it )
  {
    AbstractTestFactory *factory = (*it).second;
    suite->addTest( factory->makeTest() );
  }
}


}  // namespace CppUnit
