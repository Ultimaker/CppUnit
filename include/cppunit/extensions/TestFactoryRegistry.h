#ifndef CPPUNIT_EXTENSIONS_TESTFACTORYREGISTRY_H
#define CPPUNIT_EXTENSIONS_TESTFACTORYREGISTRY_H

#include <cppunit/Portability.h>
#include <cppunit/extensions/TestFactory.h>
#include <map>
#include <string>

namespace CppUnit {

  class TestSuite;

  /** This class implements a registry for test factory.
   *
   * Note that the registry assume lifetime control for any registered test.
   */
  class TestFactoryRegistry : public TestFactory
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

    typedef std::map<std::string, TestFactoryRegistry *> NamedRegistries;

    std::string m_name;
  };



}  // namespace CppUnit


#endif  // CPPUNIT_EXTENSIONS_TESTFACTORYREGISTRY_H
