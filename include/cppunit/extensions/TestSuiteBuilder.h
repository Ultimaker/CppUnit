#ifndef CPPUNIT_EXTENSIONS_TESTSUITEBUILDER_H
#define CPPUNIT_EXTENSIONS_TESTSUITEBUILDER_H

#include <cppunit/Portability.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>
#include <cppunit/extensions/TestNamer.h>
#include <memory>


CPPUNIT_NS_BEGIN


/*! \brief Helper to add tests to a TestSuite.
 * \ingroup WritingTestFixture
 *
 * All tests added to the TestSuite are prefixed by TestSuite name. The resulting
 * TestCase name has the following pattern:
 *
 * MyTestSuiteName.myTestName
 * \see TestNamer.
 */
template<class Fixture>
class TestSuiteBuilder
{
public:
  typedef void (Fixture::*TestMethod)();
  TestSuiteBuilder( TestSuite *suite,
                    const TestNamer &namer ) 
    : m_suite( suite )
    , m_testNamer( namer )
  {
  }


  TestSuiteBuilder( const TestNamer &namer ) 
    : m_suite( new TestSuite( namer.getFixtureName() ) )
    , m_testNamer( namer )
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

  std::string makeTestName( const std::string &methodName )
  {
    return m_testNamer.getTestNameFor( methodName );
  }

private:
  std::auto_ptr<TestSuite> m_suite;
  const TestNamer &m_testNamer;
};


CPPUNIT_NS_END

#endif  // CPPUNIT_EXTENSIONS_TESTSUITEBUILDER_H
