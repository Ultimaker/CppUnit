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

/*! \class CompilerTestResultOutputter
 * \brief This class implements output test result in a compiler compatible format.
 */
class CompilerTestResultOutputter
{
public:
  /*! Constructs a CompilerTestResultOutputter object.
   */
  CompilerTestResultOutputter( TestResult *result,
                               std::ostream &stream );

  /// Destructor.
  virtual ~CompilerTestResultOutputter();

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
  CompilerTestResultOutputter( const CompilerTestResultOutputter &copy );

  /// Prevents the use of the copy operator.
  void operator =( const CompilerTestResultOutputter &copy );

private:
  TestResult *m_result;
  std::ostream &m_stream;
};


}  // namespace CppUnit



#endif  // CPPUNIT_COMPILERTESTRESULTOUTPUTTER_H
