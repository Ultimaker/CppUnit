#if _MSC_VER > 1000     // VC++
#pragma once
#pragma warning( disable : 4786 )   // disable warning debug symbol > 255...
#endif // _MSC_VER > 1000

#include <utility>
#include "cppunit/TestSuite.h"
#include "cppunit/extensions/TestFactoryRegistry.h"

#ifdef USE_TYPEINFO
#include "TypeInfoHelper.h"
#endif // USE_TYPEINFO

namespace CppUnit {

TestFactoryRegistry::TestFactoryRegistry( std::string name ) :
    m_name( name )
{
}

TestFactoryRegistry::~TestFactoryRegistry()
{
  for ( Factories::iterator it = m_factories.begin(); it != m_factories.end(); ++it )
  {
    AbstractTestFactory *factory = it->second;
    delete factory;
  }
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
// No clean-up at the current time => memory leaks.
// Need to find a way to solve the folowing issue:
// getRegistry().registryFactory( "Functionnal", 
//                                getRegistry( "Functionnal" ) );
// => the test factory registry "Functionnal" would be
// destroyed twice: once by the map below, once by the getRegistry() factory.
  static NamedRegistries registries;

  NamedRegistries::const_iterator foundIt = registries.find( name );
  if ( foundIt == registries.end() )
  {
    TestFactoryRegistry *factory = new TestFactoryRegistry( name );
    registries.insert( std::make_pair( name, factory ) );
    return *factory;
  }
  return *foundIt->second;
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
