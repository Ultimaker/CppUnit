#ifndef CPPUNIT_COMPILERTESTRESULTOUTPUTTER_H
#define CPPUNIT_COMPILERTESTRESULTOUTPUTTER_H

#include <cppunit/Portability.h>
#include <cppunit/Outputter.h>
#include <vector>
#include <iostream>

namespace CppUnit
{

class Exception;
class SourceLine;
class Test;
class TestFailure;
class TestResultCollector;

/*! \class CompilerOutputter
 * \brief This class implements output test result in a compiler compatible format.
 */
class CPPUNIT_API CompilerOutputter : public Outputter
{
public:
  /*! Constructs a CompilerOutputter object.
   */
  CompilerOutputter( TestResultCollector *result,
                     std::ostream &stream );

  /// Destructor.
  virtual ~CompilerOutputter();

  static CompilerOutputter *defaultOutputter( TestResultCollector *result,
                                              std::ostream &stream );

  void write();

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

  typedef std::vector<std::string> Lines;
  static Lines splitMessageIntoLines( std::string message );

private:
  TestResultCollector *m_result;
  std::ostream &m_stream;
};


}  // namespace CppUnit



#endif  // CPPUNIT_COMPILERTESTRESULTOUTPUTTER_H
