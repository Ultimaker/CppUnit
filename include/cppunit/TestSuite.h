#ifndef CPPUNIT_TESTSUITE_H
#define CPPUNIT_TESTSUITE_H

#include <vector>
#include <string>
#include <cppunit/Test.h>

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
   * TestSuites do not register themselves in the TestRegistry.
   * \see Test 
   * \see TestCaller
   */


  class TestSuite : public Test
  {
    public:
                        TestSuite       (std::string name = "");
#ifdef USE_TYPEINFO
                        TestSuite       (const std::type_info &info );
#endif // USE_TYPEINFO
                        ~TestSuite      ();

    void                run             (TestResult *result);
    int                 countTestCases  () const;
    void                addTest         (Test *test);
    std::string         getName         () const;
    std::string         toString        () const;

    const std::vector<Test *> & getTests() const;

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
