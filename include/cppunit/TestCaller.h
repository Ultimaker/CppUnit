#ifndef CPPUNIT_TESTCALLER_H
#define CPPUNIT_TESTCALLER_H

#include <memory>
#include <cppunit/TestCase.h>

namespace CppUnit {

  /** Provides access to a test case method.
   * A test caller provides access to a test case method 
   * on a test case class.  Test callers are useful when 
   * you want to run an individual test or add it to a 
   * suite.
   * Test Callers invoke only one Test (i.e. test method) on one 
   * Fixture of a TestCase.
   * 
   * Here is an example:
   * \code
   * class MathTest : public CppUnit::TestCase {
   *         ...
   *     public:
   *         void         setUp ();
   *         void         tearDown ();
   *
   *         void         testAdd ();
   *         void         testSubtract ();
   * };
   *
   * CppUnit::Test *MathTest::suite () {
   *     CppUnit::TestSuite *suite = new CppUnit::TestSuite;
   *
   *     suite->addTest (new CppUnit::TestCaller<MathTest> ("testAdd", testAdd));
   *     return suite;
   * }
   * \endcode
   *
   * You can use a TestCaller to bind any test method on a TestCase
   * class, as long as it accepts void and returns void.
   * TestCallers are automatically registered in the TestRegistry.
   * 
   * \see TestCase
   */

  template <typename Fixture> 
    class TestCaller : public TestCase
    { 
        typedef void             (Fixture::*TestMethod)();
    
      public:
        TestCaller (std::string name, TestMethod test) :
          TestCase (name), 
          m_fixture (new Fixture ()), 
          m_test (test)
        {}

      protected:
        void runTest () 
        { 
          (m_fixture.get ()->*m_test)(); 
        }  

        void setUp ()
        { 
          m_fixture.get ()->setUp (); 
        }

        void tearDown ()
        { 
          m_fixture.get ()->tearDown (); 
        }

        std::string toString () const
        { 
          return "TestCaller " + getName(); 
        }

      private: 
        TestCaller (const TestCaller& other); 
        TestCaller& operator= (const TestCaller& other); 

      private:
        std::auto_ptr<Fixture>   m_fixture;
        TestMethod               m_test;

    };

  /** Returns a TestCaller for the specified method.
   * \param name Name for the TestCaller.
   * \param testMethod Method called by the TestCaller.
   * \return TestCaller for the specified method.      
   */
  template<typename Fixture>
    Test *makeTestCaller( std::string name, void (Fixture::*testMethod)() )
    {
      return new TestCaller<Fixture>( name, testMethod );
    }

} // namespace CppUnit

#endif // CPPUNIT_TESTCALLER_H
