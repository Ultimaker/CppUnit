#ifndef CPPUNIT_TESTFAILURE_H    // -*- C++ -*-
#define CPPUNIT_TESTFAILURE_H

#include <cppunit/Portability.h>
#include <string>

namespace CppUnit {

class Exception;
class SourceLine;
class Test;


/*! \brief Record of a failed test execution.
 *
 * A TestFailure collects a failed test together with
 * the caught exception.
 *
 * TestFailure assumes lifetime control for any exception
 * passed to it.
 */
class TestFailure 
{
public:
  TestFailure( Test *failedTest,
               Exception *thrownException,
               bool isError );

  virtual ~TestFailure ();

  Test *failedTest() const;

  Exception *thrownException() const;

  SourceLine sourceLine() const;

  bool isError() const;

  std::string failedTestName() const;
  
  std::string toString() const;

protected:
  Test *m_failedTest;
  Exception *m_thrownException;
  bool m_isError;

private: 
  TestFailure( const TestFailure &other ); 
  TestFailure &operator =( const TestFailure& other ); 
};


} // namespace CppUnit

#endif // CPPUNIT_TESTFAILURE_H
