#ifndef CPPUNIT_EXTENSIONS_TESTSUITEBUILDER_H
#define CPPUNIT_EXTENSIONS_TESTSUITEBUILDER_H

#include <cppunit/Portability.h>
#include <memory>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#if CPPUNIT_USE_TYPEINFO_NAME
#  include <cppunit/extensions/TypeInfoHelper.h>
#endif

namespace CppUnit {

  template<typename Fixture>
  class TestSuiteBuilder
  {
    public:
      typedef void (Fixture::*TestMethod)();

#if CPPUNIT_USE_TYPEINFO_NAME
      TestSuiteBuilder() : 
          m_suite( new TestSuite( 
              TypeInfoHelper::getClassName( typeid(Fixture) )  ) )
      {
      }
#endif

      TestSuiteBuilder( TestSuite *suite ) : m_suite( suite ) 
      {
      }

      TestSuiteBuilder(std::string name) : m_suite( new TestSuite(name) ) 
      {
      }

      TestSuite *suite() const
      {
        return m_suite.get();
      }

      TestSuite *takeSuite()
      {
        return m_suite.release();
      }

      void addTest( Test *test )
      {
        m_suite->addTest( test );
      }

      void addTestCaller( std::string methodName, 
                          TestMethod testMethod )
      {
          Test *test = 
              new TestCaller<Fixture>( makeTestName( methodName ), 
                                       testMethod );
          addTest( test );
      }

      void addTestCaller( std::string methodName, 
                          TestMethod testMethod, 
                          Fixture *fixture )
      {
          Test *test = 
              new TestCaller<Fixture>( makeTestName( methodName ), 
                                       testMethod,
                                       fixture);
          addTest( test );
      }

    protected:
      std::string makeTestName( const std::string &methodName )
      {
        return m_suite->getName() + "." + methodName;
      }

    private:
      std::auto_ptr<TestSuite> m_suite;
  };

}  // namespace CppUnit

#endif  // CPPUNIT_EXTENSIONS_TESTSUITEBUILDER_H
