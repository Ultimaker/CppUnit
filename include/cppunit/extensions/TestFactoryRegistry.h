#ifndef CPPUNIT_EXTENSIONS_TESTFACTORYREGISTRY_H
#define CPPUNIT_EXTENSIONS_TESTFACTORYREGISTRY_H

#include <cppunit/Portability.h>

#if CPPUNIT_NEED_DLL_DECL
#pragma warning( push )
#pragma warning( disable: 4251 )  // X needs to have dll-interface to be used by clients of class Z
#endif

#include <cppunit/extensions/TestFactory.h>
#include <map>
#include <string>

namespace CppUnit {

class TestSuite;

#if CPPUNIT_NEED_DLL_DECL
  template class CPPUNIT_API std::map<std::string, TestFactory *>;
#endif


/*! \brief Registry for test factory.
 *
 * Notes that the registry assumes lifetime control for any registered test.
 */
class CPPUNIT_API TestFactoryRegistry : public TestFactory
{
public:
  /** Constructs the registry with the specified name.
   * \param name Name of the registry.
   */
  TestFactoryRegistry( std::string name = "All Tests" );

  /// Destructor.
  virtual ~TestFactoryRegistry();

  /** Makes a suite containing all the registered test.
   * \return A new suite containing all the registered test.
   */
  virtual Test *makeTest();

  /** Returns the registry.
   * \return Registry.
   */
  static TestFactoryRegistry &getRegistry();

  /** Returns a named registry.
   * \param name Name of the registry to return.
   * \return Registry. If the registry does not exist, it is created.
   */
  static TestFactoryRegistry &getRegistry( const std::string &name );

  /** Adds the registered test to the specified suite.
   * \param suite Suite the test are added to.
   */
  void addTestToSuite( TestSuite *suite );

  /** Registers a test factory with the specified name.
   * \param name Name associated to the factory.
   * \param factory Factory to register. 
   */
  void registerFactory( const std::string &name,
                        TestFactory *factory );

  /** Registers a test factory using its class name.
   * \param factory Factory to register. 
   */
  void registerFactory( TestFactory *factory );

private:
  TestFactoryRegistry( const TestFactoryRegistry &copy );
  void operator =( const TestFactoryRegistry &copy );

private:
  typedef std::map<std::string, TestFactory *> Factories;
  Factories m_factories;

  std::string m_name;
};


}  // namespace CppUnit


#if CPPUNIT_NEED_DLL_DECL
#pragma warning( pop )
#endif


#endif  // CPPUNIT_EXTENSIONS_TESTFACTORYREGISTRY_H
