#ifndef CPPUNIT_TESTCALLER_H
#define CPPUNIT_TESTCALLER_H

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
   * 
   * \see TestCase
   */

  template <typename Fixture> 
    class TestCaller : public TestCase
    { 
        typedef void             (Fixture::*TestMethod)();
    
      public:
        /**
         * Constructor for TestCaller. This constructor builds a new Fixture
         * instance owned by the TestCaller.
         * \param name name of this TestCaller
         * \param test the method this TestCaller calls in runTest()
         **/
        TestCaller (std::string name, TestMethod test) :
          TestCase (name), 
          m_ownFixture(true),
          m_fixture (new Fixture ()),
          m_test (test)
        {}

        /**
         * Constructor for TestCaller. 
         * This constructor does not create a new Fixture instance but accepts
         * an existing one as parameter. The TestCaller will not own the
         * Fixture object.
         * \param name name of this TestCaller
         * \param test the method this TestCaller calls in runTest()
         * \param fixture the Fixture to invoke the test method on.
         **/
        TestCaller(std::string name, TestMethod test, Fixture& fixture) :
          TestCase (name), 
          m_ownFixture(false),
          m_fixture (&fixture),
          m_test (test)
        {}

        /**
         * Constructor for TestCaller. 
         * This constructor does not create a new Fixture instance but accepts
         * an existing one as parameter. The TestCaller will own the
         * Fixture object and delete it in its destructor.
         * \param name name of this TestCaller
         * \param test the method this TestCaller calls in runTest()
         * \param fixture the Fixture to invoke the test method on.
         **/
         TestCaller(std::string name, TestMethod test, Fixture* fixture) :
          TestCase (name), 
          m_ownFixture(true),
          m_fixture (fixture),
          m_test (test)
        {}

        ~TestCaller() {
            if (m_ownFixture) {
                if (m_fixture) {
                    delete m_fixture;
                    m_fixture = NULL;
                }
            }
        }

      protected:
        void runTest () 
        { 
          (m_fixture->*m_test)(); 
        }  

        void setUp ()
        { 
          m_fixture->setUp (); 
        }

        void tearDown ()
        { 
          m_fixture->tearDown (); 
        }

        std::string toString () const
        { 
          return "TestCaller " + getName(); 
        }

      private: 
        TestCaller (const TestCaller& other); 
        TestCaller& operator= (const TestCaller& other); 

      private:
        bool       m_ownFixture;
        Fixture*   m_fixture;
        TestMethod m_test;

    };

} // namespace CppUnit

#endif // CPPUNIT_TESTCALLER_H
