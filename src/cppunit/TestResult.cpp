#include "cppunit/TestResult.h"
#include "cppunit/TestListener.h"
#include <algorithm>

namespace CppUnit {

/// Construct a TestResult
TestResult::TestResult( SynchronizationObject *syncObject ) : 
    m_syncObject( syncObject == 0 ?  new SynchronizationObject() :
                                     syncObject  )
{ 
  m_runTests = 0;
  m_testErrors = 0;
  m_stop = false; 
}


/// Destroys a test result
TestResult::~TestResult()
{
  TestFailures::iterator itFailure = m_failures.begin();
  while ( itFailure != m_failures.end() )
    delete *itFailure++;

  delete m_syncObject;
}


/** Adds an error to the list of errors. 
 *  The passed in exception
 *  caused the error
 */
void 
TestResult::addError( Test *test, 
                      Exception *e )
{ 
  ExclusiveZone zone( m_syncObject ); 
  ++m_testErrors;
  addFailure( new TestFailure( test, e, true ) );
}


/** Adds a failure to the list of failures. The passed in exception
 * caused the failure.
 */
void 
TestResult::addFailure( Test *test, Exception *e )
{ 
  ExclusiveZone zone( m_syncObject ); 
  addFailure( new TestFailure( test, e, false ) );
}


/** Called to add a failure to the list of failures.
 */
void 
TestResult::addFailure( TestFailure *failure )
{
  m_failures.push_back( failure ); 

  for ( std::vector<TestListener *>::iterator it = m_listeners.begin();
        it != m_listeners.end(); 
        ++it )
    (*it)->addFailure( failure );
}


/// Informs the result that a test will be started.
void 
TestResult::startTest( Test *test )
{ 
  ExclusiveZone zone (m_syncObject); 
  m_runTests++; 

  for ( std::vector<TestListener *>::iterator it = m_listeners.begin();
        it != m_listeners.end(); 
        ++it )
    (*it)->startTest( test );
}

  
/// Informs the result that a test was completed.
void 
TestResult::endTest( Test *test )
{ 
  ExclusiveZone zone (m_syncObject); 

  for ( std::vector<TestListener *>::iterator it = m_listeners.begin();
        it != m_listeners.end(); 
        ++it )
    (*it)->endTest( test );
}


/// Gets the number of run tests.
int 
TestResult::runTests() const
{ 
  ExclusiveZone zone( m_syncObject ); 
  return m_runTests; 
}


/// Gets the number of detected errors (uncaught exception).
int 
TestResult::testErrors() const
{ 
  ExclusiveZone zone( m_syncObject );
  return m_testErrors;
}


/// Gets the number of detected failures (failed assertion).
int 
TestResult::testFailures() const
{ 
  ExclusiveZone zone( m_syncObject ); 
  return m_failures.size() - m_testErrors;
}


/// Gets the total number of detected failures.
int 
TestResult::testFailuresTotal() const
{
  ExclusiveZone zone( m_syncObject ); 
  return m_failures.size();
}


/// Returns whether the entire test was successful or not.
bool 
TestResult::wasSuccessful() const
{ 
  ExclusiveZone zone( m_syncObject );
  return m_failures.size() == 0;
}


/// Returns a vector of the failures.
const std::vector<TestFailure *>& 
TestResult::failures() const
{ 
  ExclusiveZone zone( m_syncObject );
  return m_failures; 
}


/// Returns whether testing should be stopped
bool 
TestResult::shouldStop() const
{ 
  ExclusiveZone zone( m_syncObject );
  return m_stop; 
}


/// Stop testing
void 
TestResult::stop()
{ 
  ExclusiveZone zone( m_syncObject );
  m_stop = true; 
}


/** Accept a new synchronization object for protection of this instance
 * TestResult assumes ownership of the object
 */
void 
TestResult::setSynchronizationObject( SynchronizationObject *syncObject )
{ 
  delete m_syncObject; 
  m_syncObject = syncObject; 
}


void 
TestResult::addListener( TestListener *listener )
{
  ExclusiveZone zone (m_syncObject); 
  m_listeners.push_back( listener );
}


void 
TestResult::removeListener ( TestListener *listener )
{
  ExclusiveZone zone (m_syncObject); 
  m_listeners.erase( std::remove( m_listeners.begin(), 
                                  m_listeners.end(), 
                                  listener ),
                     m_listeners.end());
}

} // namespace CppUnit
