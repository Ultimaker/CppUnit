#ifndef CPPUNIT_EXTENSIONS_TESTSUITEBUILDER_H
#define CPPUNIT_EXTENSIONS_TESTSUITEBUILDER_H

#include <memory>
#include <cppunit/config.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#if CPPUNIT_USE_TYPEINFO
#  include <cppunit/extensions/TypeInfoHelper.h>
#endif

namespace CppUnit {

  template<typename Fixture>
  class TestSuiteBuilder
  {
    public:
      typedef void (Fixture::*TestMethod)();

#if CPPUNIT_USE_TYPEINFO
      TestSuiteBuilder() : 
          m_suite( new TestSuite( 
              TypeInfoHelper::getClassName( typeid(Fixture) )  ) )
      {
      }
#endif  // CPPUNIT_USE_TYPEINFO

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

      void addTestCaller( std::string name, TestMethod testMethod )
      {
          Test *test = 
              new TestCaller<Fixture>( m_suite->getName() + "." + name, 
                                       testMethod );
          addTest( test );
      }

    private:
      std::auto_ptr<TestSuite> m_suite;
  };

}  // namespace CppUnit

#endif  // CPPUNIT_EXTENSIONS_TESTSUITEBUILDER_H
