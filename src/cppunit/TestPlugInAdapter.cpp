#include <cppunit/Portability.h>

#if !defined(CPPUNIT_NO_TESTPLUGIN)

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestSuite.h>
#include <cppunit/plugin/TestPlugInAdapter.h>


namespace CppUnit
{

TestPlugInAdapter::TestPlugInAdapter() 
{
}


TestPlugInAdapter::~TestPlugInAdapter()
{
}


void 
TestPlugInAdapter::initialize( TestFactoryRegistry *registry,
                                   const Parameters &parameters )
{
}


void 
TestPlugInAdapter::addListener( TestResult *eventManager )
{
}


void 
TestPlugInAdapter::removeListener( TestResult *eventManager )
{
}


void 
TestPlugInAdapter::uninitialize( TestFactoryRegistry *registry )
{
}


}  // namespace CppUnit


#endif // !defined(CPPUNIT_NO_TESTPLUGIN)
