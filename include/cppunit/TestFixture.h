#ifndef CPPUNIT_TESTFIXTURE_H    // -*- C++ -*-
#define CPPUNIT_TESTFIXTURE_H

#include <cppunit/Portability.h>

namespace CppUnit {


/*! \brief Wraps a test case with setUp and tearDown methods.
 *
 * A TestFixture is used to provide a common environment for a set
 * of test cases.
 *
 */
class CPPUNIT_API TestFixture
{
public:
  virtual ~TestFixture() {};

  //! \brief Set up context before running a test.
  virtual void setUp() {};

  //! Clean up after the test run.
  virtual void tearDown() {};
};


}

#endif
