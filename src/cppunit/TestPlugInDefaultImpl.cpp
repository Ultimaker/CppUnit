#include <cppunit/Portability.h>

#if !defined(CPPUNIT_NO_TESTPLUGIN)

#include <cppunit/TestSuite.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/plugin/TestPlugInDefaultImpl.h>


namespace CppUnit
{

TestPlugInDefaultImpl::TestPlugInDefaultImpl() 
{
}


TestPlugInDefaultImpl::~TestPlugInDefaultImpl()
{
}


void 
TestPlugInDefaultImpl::initialize( TestFactoryRegistry *registry,
                                   const Parameters &parameters )
{
}


void 
TestPlugInDefaultImpl::addListener( TestResult *eventManager )
{
}


void 
TestPlugInDefaultImpl::removeListener( TestResult *eventManager )
{
}


void 
TestPlugInDefaultImpl::addXmlOutputterHooks( XmlOutputter *outputter )
{
}


void 
TestPlugInDefaultImpl::removeXmlOutputterHooks()
{
}


void 
TestPlugInDefaultImpl::uninitialize( TestFactoryRegistry *registry )
{
}


}  // namespace CppUnit


#endif // !defined(CPPUNIT_NO_TESTPLUGIN)
