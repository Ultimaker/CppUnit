#include <cppunit/plugin/TestPlugInSuite.h>

#if !defined(CPPUNIT_NO_TESTPLUGIN)

#include <cppunit/plugin/DynamicLibraryManager.h>


namespace CppUnit
{


TestPlugInSuite::TestPlugInSuite( const std::string &libraryFileName )
    : m_library( new DynamicLibraryManager( libraryFileName ) )
    , m_librarySuite( NULL )
    , m_interface( NULL )
{
  try
  {
    CppUnitTestPlugInSignature plug = (CppUnitTestPlugInSignature)m_library->findSymbol( 
          CPPUNIT_STRINGIZE( CPPUNIT_PLUGIN_EXPORTED_NAME ) );
    m_interface = (*plug)();
    m_interface->initialize();
    m_librarySuite = m_interface->getTestSuite();
  }
  catch( ... )
  {
    delete m_library;
    m_library = NULL;
    throw;
  }
}


TestPlugInSuite::~TestPlugInSuite()
{
  if ( m_interface )
    m_interface->uninitialize();
  delete m_library;
}


int 
TestPlugInSuite::getChildTestCount() const
{
  return m_librarySuite->getChildTestCount();
}


Test *
TestPlugInSuite::doGetChildTestAt( int index ) const
{
  return m_librarySuite->getChildTestAt( index );
}


} //  namespace CppUnit


#endif // !defined(CPPUNIT_NO_TESTPLUGIN)