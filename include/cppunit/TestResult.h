#ifndef CPPUNIT_TESTRESULT_H
#define CPPUNIT_TESTRESULT_H

#include <cppunit/SynchronizedObject.h>
#include <deque>

namespace CppUnit {

class Exception;
class Test;
class TestFailure;
class TestListener;


/**
 * A TestResult collects the results of executing a test case. It is an 
 * instance of the Collecting Parameter pattern.
 *
 * FIXME: NEED UPDATE (main responsibilty is to act as an event manager)
 *
 * The test framework distinguishes between failures and errors.
 * A failure is anticipated and checked for with assertions. Errors are
 * unanticipated problems signified by exceptions that are not generated
 * by the framework.
 *
 * TestResult supplies a template method 'setSynchronizationObject ()'
 * so that subclasses can provide mutual exclusion in the face of multiple
 * threads.  This can be useful when tests execute in one thread and
 * they fill a subclass of TestResult which effects change in another 
 * thread.  To have mutual exclusion, override setSynchronizationObject ()
 * and make sure that you create an instance of ExclusiveZone at the 
 * beginning of each method.
 *
 * \see Test, TestResultCollector
 */

class TestResult : protected SynchronizedObject
{
public:
  TestResult( SynchronizationObject *syncObject = 0 );
  virtual ~TestResult();

  virtual void addListener( TestListener *listener );
  virtual void removeListener( TestListener *listener );

  virtual void reset();
  virtual void stop();

  virtual bool shouldStop() const;

  virtual void startTest( Test *test );
  virtual void addError( Test *test, Exception *e );
  virtual void addFailure( Test *test, Exception *e );
  virtual void endTest( Test *test );

protected:
  void addFailure( const TestFailure &failure );
  
protected:
  typedef std::deque<TestListener *> TestListeners;
  TestListeners m_listeners;
  bool m_stop;

private: 
  TestResult( const TestResult &other );
  TestResult &operator =( const TestResult &other );
};

} // namespace CppUnit

#endif // CPPUNIT_TESTRESULT_H


