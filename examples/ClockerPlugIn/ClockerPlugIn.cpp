#include <cppunit/TestResult.h>
#include <cppunit/plugin/TestPlugIn.h>
#include "ClockerListener.h"



class ClockerPlugIn : public CppUnitTestPlugIn
{
public:
  ClockerPlugIn()
    : m_dumper( NULL )
  {
  }

  ~ClockerPlugIn()
  {
    delete m_dumper;
  }


  void initialize( CppUnit::TestFactoryRegistry *registry,
                   const CppUnit::Parameters &parameters )
  {
    bool flatten = false;
    if ( parameters.size() > 0  &&  parameters[0] == "flat" )
      flatten = true;

    m_dumper = new ClockerListener( flatten );
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
  ClockerListener *m_dumper;
};


CPPUNIT_PLUGIN_EXPORTED_FUNCTION_IMPL( ClockerPlugIn );

CPPUNIT_TESTPLUGIN_MAIN();