#ifndef CPPUNIT_TEST_H
#define CPPUNIT_TEST_H

#include <string>

namespace CppUnit {

  class TestResult;

  /**
   * A Test can be run and collect its results.
   * \see TestResult.
   * 
   */
  class Test
  {
    public:
      virtual                       ~Test () {};

      virtual void                  run (TestResult *result)    = 0;
      virtual int                   countTestCases () const     = 0;
      virtual std::string           toString () const           = 0;
      virtual std::string           getName () const            = 0;


  };


} // namespace CppUnit

#endif // CPPUNIT_TEST_H

