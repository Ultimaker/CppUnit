#ifndef CPPUNIT_TESTLISTENER_H    // -*- C++ -*-
#define CPPUNIT_TESTLISTENER_H

#include <cppunit/Portability.h>


namespace CppUnit {

class Exception;
class Test;
class TestFailure;


/*! \brief Listener for test progress and result.
 * \ingroup TrackingTestExecution
 *
 * Implementing the Observer pattern a TestListener may be registered
 * to a TestResult to obtain information on the testing progress. Use
 * specialized sub classes of TestListener for text output
 * (TextTestProgressListener). Do not use the Listener for the test
 * result output, use a subclass of Outputter instead.
 *
 * The test framework distinguishes between failures and errors.
 * A failure is anticipated and checked for with assertions. Errors are
 * unanticipated problems signified by exceptions that are not generated
 * by the framework.
 *
 * \code
 *
 * #include <cppunit/TestListener.h>
 * #include <cppunit/Test.h>
 * #include <time.h>    // for clock()
 *
 * class TimingListener : public CppUnit::TestListener
 * {
 * public:
 *   void startTest( CppUnit::Test *test )
 *   {
 *     _chronometer.start();
 *   }
 *  
 *   void endTest( CppUnit::Test *test )
 *   {
 *     _chronometer.end();
 *     addTest( test, _chronometer.elapsedTime() );
 *   }
 *
 *   // ... (interface to add/read test timing result)
 *
 * private:
 *
 *   class Clock
 *   {
 *   public:
 *     Clock() : _startTime( 0 ), _endTime(0) {}
 * 
 *     void start()
 *     {
 *       _startTime = clock();
 *     }
 * 
 *     void end()
 *     {
 *       _endTime = clock();
 *     }
 *
 *     double elapsedTime() const
 *     {
 *       return double(_endTime - _startTime) / CLOCKS_PER_SEC;
 *     }
 *  
 *   private:
 *     clock_t _startTime, _endTime;   
 *   };
 *
 *   Clock _chronometer;
 * };
 *   
 *
 *
 * \see TestResult
 */
class CPPUNIT_API TestListener
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


