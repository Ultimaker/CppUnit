#ifndef CPPUNIT_PLUGIN_TESTPLUGINADAPTER
#define CPPUNIT_PLUGIN_TESTPLUGINADAPTER

#include <cppunit/Portability.h>

#if !defined(CPPUNIT_NO_TESTPLUGIN)

#include <cppunit/plugin/TestPlugIn.h>

namespace CppUnit
{

class TestSuite;


/*! Default implementation of test plug-in interface.
 * \ingroup WritingTestPlugIn
 *
 * Override getSuiteName() to specify the suite name. Default is "All Tests".
 *
 * CppUnitTestPlugIn::::getTestSuite() returns a suite that contains
 * all the test registered to the default test factory registry 
 * ( TestFactoryRegistry::getRegistry() ).
 *
 */
class CPPUNIT_API TestPlugInAdapter : public CppUnitTestPlugIn
{
public:
  TestPlugInAdapter();

  virtual ~TestPlugInAdapter();

  void initialize( TestFactoryRegistry *registry,
                   const Parameters &parameters );

  void addListener( TestResult *eventManager );

  void removeListener( TestResult *eventManager );

  void uninitialize( TestFactoryRegistry *registry );
};


}  // namespace CppUnit

#endif // !defined(CPPUNIT_NO_TESTPLUGIN)

#endif // CPPUNIT_PLUGIN_TESTPLUGINADAPTER
