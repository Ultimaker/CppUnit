#ifndef CPPUNIT_PLUGIN_TESTPLUGIN
#define CPPUNIT_PLUGIN_TESTPLUGIN

#include <cppunit/Portability.h>

#if !defined(CPPUNIT_NO_TESTPLUGIN)

namespace CppUnit
{
class Test;
}

/*! \file
 */


/*! Test plug-in interface.
 * \ingroup WritingTestPlugIn
 *
 * This class define the interface implemented by test plug-in. A pointer to that
 * interface is returned by the function exported by the test plug-in.
 * \see CPPUNIT_PLUGIN_IMPLEMENT, CPPUNIT_PLUGIN_EXPORTED_FUNCTION_IMPL
 * \see TestPlugInDefaultImpl.
 */
struct CppUnitTestPlugIn
{
  /*! Called just after loading the dynamic library. 
   *
   * Initializes the plug-in.
   */
  virtual void initialize() = 0;

  /*! Returns the root test of the plug-in.
   *
   * Caller does not assume ownership of the test.
   * \return Pointer on a Test. Must never be \c NULL. The caller does not assume
   *         ownership of the returned Test. The Test must remain valid until
   *         uninitialize() is called.
   */
  virtual CppUnit::Test *getTestSuite() =0;

  /*! Called just before unloading the dynamic library.
   * Unitializes the plug-in.
   */
  virtual void uninitialize() = 0;
};



/*! Name of the function exported by a test plug-in.
 * \ingroup WritingTestPlugIn
 *
 * The signature of the exported function is:
 * \code
 * CppUnitTestPlugIn *CPPUNIT_PLUGIN_EXPORTED_NAME(void);
 * \endif
 */
#define CPPUNIT_PLUGIN_EXPORTED_NAME cppunitTestPlugIn

/*! Type of the function exported by a plug-in.
 * \ingroup WritingTestPlugIn
 */
typedef CppUnitTestPlugIn *(*CppUnitTestPlugInSignature)();


/*! Implements the function exported by the test plug-in
 * \ingroup WritingTestPlugIn
 */
#define CPPUNIT_PLUGIN_EXPORTED_FUNCTION_IMPL( TestPlugInInterfaceType )       \
  CPPUNIT_PLUGIN_EXPORT CppUnitTestPlugIn *CPPUNIT_PLUGIN_EXPORTED_NAME(void)  \
  {                                                                            \
    static TestPlugInInterfaceType plugIn;                                     \
    return &plugIn;                                                            \
  }                                                                            \
  typedef char __CppUnitPlugInExportFunctionDummyTypeDef  // dummy typedef so it can end with ';'


// Note: This include should remain after definition of CppUnitTestPlugIn
#include <cppunit/plugin/TestPlugInDefaultImpl.h>


/*! \def CPPUNIT_PLUGIN_IMPLEMENT_MAIN()
 * \brief Implements the 'main' function for the plug-in.
 *
 * This macros implements the main() function for dynamic library.
 * For example, WIN32 requires a DllMain function, while some Unix 
 * requires a main() function. This macros takes care of the implementation.
 */

// Win32
#if defined(CPPUNIT_HAVE_WIN32_DLL_LOADER)
#if !defined(APIENTRY)
#define WIN32_LEAN_AND_MEAN 
#define NOGDI
#define NOUSER
#define NOKERNEL
#define NOSOUND
#define NOMINMAX
#include <windows.h>
#endif
#define CPPUNIT_PLUGIN_IMPLEMENT_MAIN()               \
  BOOL APIENTRY DllMain( HANDLE hModule,              \
                         DWORD  ul_reason_for_call,   \
                         LPVOID lpReserved )          \
  {                                                   \
      return TRUE;                                    \
  }                                                   \
  typedef char __CppUnitPlugInImplementMainDummyTypeDef

// Unix
#elif defined(CPPUNIT_HAVE_UNIX_DLL_LOADER)
#define CPPUNIT_PLUGIN_IMPLEMENT_MAIN()               \
  int main( int argc, char *argv[] )                  \
  {                                                   \
    return 0;                                         \
  }                                                   \
  typedef char __CppUnitPlugInImplementMainDummyTypeDef

//     (void)argc; (void)argv;                           \ 


// Other
#else     // other platforms don't require anything specifics
#endif



/*! Implements and exports the test plug-in interface.
 * \ingroup WritingTestPlugIn
 *
 * This macro creates a subclass of CppUnitTestPlugInDefaultImpl to specify set
 * the name of the suite returned by CppUnitTestPlugIn::getTestSuite(), exports
 * the test plug-in function using the subclass, and implements the 'main' 
 * function for the plug-in using CPPUNIT_PLUGIN_IMPLEMENT_MAIN().
 *
 * \see CppUnitTestPlugIn, CppUnitTestPlugInDefaultImpl
 * \see CPPUNIT_PLUGIN_EXPORTED_FUNCTION_IMPL(), CPPUNIT_PLUGIN_IMPLEMENT_MAIN().
 */
#define CPPUNIT_PLUGIN_IMPLEMENT( suiteName )                                        \
  class __CppUnitTestPlugInNamedDefaultImpl : public CppUnit::TestPlugInDefaultImpl  \
  {                                                                                  \
    virtual std::string getSuiteName()                                               \
    {                                                                                \
      return suiteName;                                                              \
    }                                                                                \
  };                                                                                 \
                                                                                     \
  CPPUNIT_PLUGIN_EXPORTED_FUNCTION_IMPL( __CppUnitTestPlugInNamedDefaultImpl );      \
  CPPUNIT_PLUGIN_IMPLEMENT_MAIN()


#endif // !defined(CPPUNIT_NO_TESTPLUGIN)


#endif // CPPUNIT_PLUGIN_TESTPLUGIN
