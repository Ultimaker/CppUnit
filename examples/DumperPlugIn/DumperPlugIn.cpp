#include <cppunit/TestResult.h>
#include <cppunit/plugin/TestPlugIn.h>
#include "DumperListener.h"



class DumperPlugIn : public CppUnitTestPlugIn
{
public:
  DumperPlugIn()
    : m_dumper( NULL )
  {
  }

  ~DumperPlugIn()
  {
    delete m_dumper;
  }


  void initialize( CppUnit::TestFactoryRegistry *registry,
                   const CppUnit::Parameters &parameters )
  {
    bool flatten = false;
    if ( parameters.size() > 0  &&  parameters[0] == "flat" )
      flatten = true;

    m_dumper = new DumperListener( flatten );
  }


  void addListener( CppUnit::TestResult *eventManager )
  {
    eventManager->addListener( m_dumper );
  }


  void removeListener( CppUnit::TestResult *eventManager )
  {
    eventManager->removeListener( m_dumper );
  }


  void uninitialize( CppUnit::TestFactoryRegistry *registry )
  {
  }

private:
  DumperListener *m_dumper;
};


CPPUNIT_PLUGIN_EXPORTED_FUNCTION_IMPL( DumperPlugIn );

CPPUNIT_TESTPLUGIN_MAIN();