#ifndef CPPUNIT_TESTCASE_H
#define CPPUNIT_TESTCASE_H

#include <string>

#ifndef CPPUNIT_TEST_H
#include "Test.h"
#endif

#ifndef CPPUNIT_EXCEPTION_H
#include "Exception.h"
#endif

namespace CppUnit {

  class TestResult;

  /**
   * A test case defines the fixture to run multiple tests. 
   * To define a test case
   * do the following:
   * - implement a subclass of TestCase 
   * - the fixture is defined by instance variables 
   * - initialize the fixture state by overriding setUp
   *   (i.e. construct the instance variables of the fixture)
   * - clean-up after a test by overriding tearDown.
   *
   * Each test runs in its own fixture so there
   * can be no side effects among test runs.
   * Here is an example:
   * 
   * \code
   * class MathTest : public TestCase {
   *     protected: int m_value1;
   *     protected: int m_value2;
   *
   *     public: MathTest (string name)
   *                 : TestCase (name) {
   *     }
   *
   *     protected: void setUp () {
   *         m_value1 = 2;
   *         m_value2 = 3;
   *     }
   * }
   * \endcode
   *
   * For each test implement a method which interacts
   * with the fixture. Verify the expected results with assertions specified
   * by calling assert on the expression you want to test:
   * 
   * \code
   *    protected: void testAdd () {
   *        int result = value1 + value2;
   *        assert (result == 5);
   *    }
   * \endcode
   * 
   * Once the methods are defined you can run them. To do this, use
   * a TestCaller.
   *
   * \code
   * Test *test = new TestCaller<MathTest>("testAdd", MathTest::testAdd);
   * test->run ();
   * \endcode
   *
   *
   * The tests to be run can be collected into a TestSuite. CppUnit provides
   * different test runners which can run a test suite and collect the results.
   * The test runners expect a static method suite as the entry
   * point to get a test to run.
   * 
   * \code
   * public: static MathTest::suite () {
   *      TestSuite *suiteOfTests = new TestSuite;
   *      suiteOfTests->addTest(new TestCaller<MathTest>(
   *                              "testAdd", testAdd));
   *      suiteOfTests->addTest(new TestCaller<MathTest>(
   *                              "testDivideByZero", testDivideByZero));
   *      return suiteOfTests;
   *  }
   * \endcode
   * 
   * Note that the caller of suite assumes lifetime control
   * for the returned suite.
   *
   * \see TestResult
   * \see TestSuite 
   * \see TestCaller
   *
   */

  class TestCase : public Test 
  {
    public:
      TestCase         ();
      TestCase         (std::string Name);
      ~TestCase        ();

      virtual void        run              (TestResult *result);
      virtual TestResult  *run             ();
      virtual int         countTestCases   ();
      std::string         getName          () const;
      std::string         toString         () const;

      virtual void        setUp            ();
      virtual void        tearDown         ();

    protected:
      virtual void        runTest          ();
    
      TestResult          *defaultResult   ();
      void                assertImplementation(
        bool         condition, 
        std::string  conditionExpression = "",
        long         lineNumber = Exception::UNKNOWNLINENUMBER,
        std::string  fileName = Exception::UNKNOWNFILENAME);

      void                assertEquals     (long         expected, 
        long         actual,
        long         lineNumber = Exception::UNKNOWNLINENUMBER,
        std::string  fileName = Exception::UNKNOWNFILENAME);

      void                assertEquals     (double       expected, 
        double       actual, 
        double       delta, 
        long         lineNumber = Exception::UNKNOWNLINENUMBER,
        std::string  fileName = Exception::UNKNOWNFILENAME);

      std::string         notEqualsMessage (long         expected, 
        long         actual);

      std::string         notEqualsMessage (double       expected, 
        double       actual);
    
    private:
      TestCase (const TestCase& other); 
      TestCase& operator= (const TestCase& other); 

    private:
      const std::string   m_name;
  };


/** A set of macros which allow us to get the line number
 * and file name at the point of an error.
 * Just goes to show that preprocessors do have some
 * redeeming qualities.
 */
#define CPPUNIT_SOURCEANNOTATION
  
#ifdef CPPUNIT_SOURCEANNOTATION

    #undef assert
    #define assert(condition)\
    (this->assertImplementation ((condition),(#condition),\
        __LINE__, __FILE__))

#else

    #undef assert
    #define assert(condition)\
    (this->assertImplementation ((condition),"",\
        __LINE__, __FILE__))

#endif


/// Macro for primitive value comparisons
#define assertDoublesEqual(expected,actual,delta)\
(this->assertEquals ((expected),\
        (actual),(delta),__LINE__,__FILE__))

/// Macro for primitive value comparisons
#define assertLongsEqual(expected,actual)\
(this->assertEquals ((expected),\
        (actual),__LINE__,__FILE__))
} // namespace CppUnit

#endif // CPPUNIT_TESTCASE_H 
