#ifndef CPPUNIT_TESTPLUGINRUNNER_TESTPLUGININTERFACE_H
#define CPPUNIT_TESTPLUGINRUNNER_TESTPLUGININTERFACE_H

#include <cppunit/Test.h>
#include <cppunit/TestSuite.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

#if !defined(WINAPI)
#define WIN32_LEAN_AND_MEAN 
#define NOGDI
#define NOUSER
#define NOKERNEL
#define NOSOUND
#define NOMINMAX
#include <windows.h>
#endif

/*! \brief Abstract TestPlugIn for DLL.
 * \ingroup WritingTestPlugIn
 *
 * A Test plug-in DLL must subclass this class and "publish" an instance
 * using the following exported function:
 * \code
 * extern "C" {
 *   __declspec(dllimport) TestPlugInInterface *GetTestPlugInInterface();
 * }
 * \endcode
 *
 * When loading the DLL, the TestPlugIn runner look-up this function and
 * retreives the 
 *
 * See the TestPlugIn example for VC++ for details.
 */
class TestPlugInInterface
{
public:
  virtual ~TestPlugInInterface() {}

  /*! Returns an instance of the "All Tests" suite.
   *
   * \return Instance of the top-level suite that contains all test. Ownership
   *         is granted to the method caller.
   */
  virtual CppUnit::Test *makeTest() =0;
};

typedef TestPlugInInterface* (WINAPI *GetTestPlugInInterfaceFunction)(void);


extern "C" {
  __declspec(dllexport) TestPlugInInterface *GetTestPlugInInterface();
}


/*! Implements the TestPlugInInterface and export the interface.
 * \ingroup WritingTestPlugIn
 *
 * Creates a subclass of TestPlugInInterface and implements 
 * TestPlugInInterface::makeTest() by returning a suite that contains
 * all the test registered to the default test factory registry 
 * ( TestFactoryRegistry::getRegistry() ).
 *
 * The name of the returned suite is specified by \a rootSuiteName.
 *
 * This macro also implements the GetTestPlugInInterface() function that
 * is exported by the DLL.
 *
 * \param rootSuiteName Name of the suite exported by the DLL.
 */
#define CPPUNIT_TESTPLUGIN_IMPL( rootSuiteName )                           \
  class TestPlugInInterfaceImpl : public TestPlugInInterface               \
  {                                                                        \
  public:                                                                  \
    CppUnit::Test *makeTest()                                              \
    {                                                                      \
      CppUnit::TestSuite *suite = new CppUnit::TestSuite( rootSuiteName ); \
      CppUnit::TestFactoryRegistry::getRegistry().addTestToSuite( suite ); \
      return suite;                                                        \
    }                                                                      \
  };                                                                       \
                                                                           \
                                                                           \
  TestPlugInInterface *GetTestPlugInInterface()                            \
  {                                                                        \
    static TestPlugInInterfaceImpl plugInInterface;                        \
    return &plugInInterface;                                               \
  }                                                                        \
                                                                           \
  /* A dummy typedef to allow ending of macro with ';' */                  \
  typedef TestPlugInInterfaceImpl __TheTestPlugInInterfaceDummyDecl



#endif // CPPUNIT_TESTPLUGINRUNNER_TESTPLUGININTERFACE_H
