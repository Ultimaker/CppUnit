#ifndef CPPUNIT_TESTLISTENER_H    // -*- C++ -*-
#define CPPUNIT_TESTLISTENER_H

#include <cppunit/Portability.h>


namespace CppUnit {

class Exception;
class Test;
class TestFailure;


/*! TestListener is the interface implemented by classes which want to be notified
 * of the progress and result of a test run.
 *
 * \see TestResult
 */
class TestListener
{
public:
  virtual ~TestListener() {}
  
  /// Called when just before a TestCase is run.
  virtual void startTest( Test *test ) {}

  /*! Called when a failure occurs while running a test.
   * \see TestFailure.
   * \warning \a failure is a temporary object that is destroyed after the 
   *          method call. Use TestFailure::clone() to create a duplicate.
   */
  virtual void addFailure( const TestFailure &failure ) {}

  /// Called just after a TestCase was run (even if a failure occured).
  virtual void endTest( Test *test ) {}
};


} // namespace CppUnit

#endif // CPPUNIT_TESTLISTENER_H


