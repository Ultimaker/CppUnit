#include <cppunit/Portability.h>

#if !defined(CPPUNIT_NO_TESTPLUGIN)

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestSuite.h>
#include <cppunit/plugin/TestPlugInDefaultImpl.h>


namespace CppUnit
{

TestPlugInDefaultImpl::TestPlugInDefaultImpl() 
    : m_suite( NULL )
{
}


TestPlugInDefaultImpl::~TestPlugInDefaultImpl()
{
  delete m_suite;
  m_suite = NULL;
}


void 
TestPlugInDefaultImpl::initialize() 
{
  m_suite = new TestSuite( getSuiteName() );
  TestFactoryRegistry::getRegistry().addTestToSuite( m_suite );
}


Test *
TestPlugInDefaultImpl::getTestSuite()
{
  return m_suite;
}


void 
TestPlugInDefaultImpl::uninitialize()
{
  delete m_suite;
  m_suite = NULL;
}


std::string 
TestPlugInDefaultImpl::getSuiteName()
{
  return "All Tests";
}


}  // namespace CppUnit


#endif // !defined(CPPUNIT_NO_TESTPLUGIN)
