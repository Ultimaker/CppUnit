#ifndef CPPUNIT_PLUGIN_TESTPLUGINDEFAULTIMPL
#define CPPUNIT_PLUGIN_TESTPLUGINDEFAULTIMPL

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
class CPPUNIT_API TestPlugInDefaultImpl : public CppUnitTestPlugIn
{
public:
  TestPlugInDefaultImpl();

  virtual ~TestPlugInDefaultImpl();

  void initialize();

  CppUnit::Test *getTestSuite();

  void uninitialize();

protected:
   virtual std::string getSuiteName();

  TestSuite *m_suite;
};


}  // namespace CppUnit

#endif // !defined(CPPUNIT_NO_TESTPLUGIN)

#endif // CPPUNIT_PLUGIN_TESTPLUGINDEFAULTIMPL
