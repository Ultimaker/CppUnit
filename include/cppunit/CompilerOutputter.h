#ifndef CPPUNIT_COMPILERTESTRESULTOUTPUTTER_H
#define CPPUNIT_COMPILERTESTRESULTOUTPUTTER_H

#include <cppunit/Portability.h>
#include <iostream>

namespace CppUnit
{

class Exception;
class SourceLine;
class Test;
class TestFailure;
class TestResult;

/*! \class CompilerOutputter
 * \brief This class implements output test result in a compiler compatible format.
 */
class CompilerOutputter
{
public:
  /*! Constructs a CompilerOutputter object.
   */
  CompilerOutputter( TestResult *result,
                               std::ostream &stream );

  /// Destructor.
  virtual ~CompilerOutputter();

  static CompilerOutputter *defaultOutputter( TestResult *result,
                                                        std::ostream &stream );

  virtual void write( );

  virtual void printSucess();
  virtual void printFailureReport();
  virtual void printFailuresList();
  virtual void printStatistics();
  virtual void printFailureDetail( TestFailure *failure );
  virtual void printFailureLocation( SourceLine sourceLine );
  virtual void printFailureType( TestFailure *failure );
  virtual void printFailedTestName( TestFailure *failure );
  virtual void printFailureMessage( TestFailure *failure );
  virtual void printNotEqualMessage( Exception *thrownException );
  virtual void printDefaultMessage( Exception *thrownException );
  virtual std::string wrap( std::string message );

private:
  /// Prevents the use of the copy constructor.
  CompilerOutputter( const CompilerOutputter &copy );

  /// Prevents the use of the copy operator.
  void operator =( const CompilerOutputter &copy );

private:
  TestResult *m_result;
  std::ostream &m_stream;
};


}  // namespace CppUnit



#endif  // CPPUNIT_COMPILERTESTRESULTOUTPUTTER_H
