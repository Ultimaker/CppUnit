#ifndef CPPUNIT_TESTFAILURE_H
#define CPPUNIT_TESTFAILURE_H

#include <string>

namespace CppUnit {

  class Test;
  class Exception;


  /**
   * A TestFailure collects a failed test together with
   * the caught exception.
   *
   * TestFailure assumes lifetime control for any exception
   * passed to it.  The lifetime of tests is handled by
   * their TestSuite (if they have been added to one) or
   * whomever creates them.
   * 
   * see TestResult
   * see TestSuite
   *
   */
  class TestFailure 
  {
    public:
      TestFailure (Test *failedTest, Exception *thrownException);
      ~TestFailure ();

      Test*        failedTest ();

      Exception*   thrownException ();

      std::string  toString () const;

    protected:
      Test         *m_failedTest;
      Exception    *m_thrownException;

    private: 
      TestFailure (const TestFailure& other); 
      TestFailure& operator= (const TestFailure& other); 
  };

  /// Gets the failed test.
  inline Test *TestFailure::failedTest ()
  { return m_failedTest; }


  /// Gets the thrown exception.
  inline Exception *TestFailure::thrownException ()
  { return m_thrownException; }

} // namespace CppUnit

#endif // CPPUNIT_TESTFAILURE_H
