#ifndef CPPUNIT_TESTSUITE_H
#define CPPUNIT_TESTSUITE_H

#include <vector>
#include <string>

#ifndef CPPUNIT_TEST_H
#include "Test.h"
#endif

namespace CppUnit {

  class TestResult;

  /**
   * A TestSuite is a Composite of Tests.
   * It runs a collection of test cases. Here is an example.
   * \code
   * CppUnit::TestSuite *suite= new CppUnit::TestSuite();
   * suite->addTest(new CppUnit::TestCaller<MathTest> (
   *                  "testAdd", testAdd));
   * suite->addTest(new CppUnit::TestCaller<MathTest> (
   *                  "testDivideByZero", testDivideByZero));
   * \endcode
   * Note that TestSuites assume lifetime
   * control for any tests added to them.
   *
   * \see Test 
   * \see TestCaller
   */


  class TestSuite : public Test
  {
    public:
                        TestSuite       (std::string name = "");
                        ~TestSuite      ();

    void                run             (TestResult *result);
    int                 countTestCases  ();
    void                addTest         (Test *test);
    std::string         getName         () const;
    std::string         toString        () const;

    virtual void        deleteContents  ();

    private:
      TestSuite (const TestSuite& other);
      TestSuite& operator= (const TestSuite& other); 

    private:
      std::vector<Test *> m_tests;
      const std::string   m_name;
  };
} // namespace CppUnit

#endif // CPPUNIT_TESTSUITE_H
