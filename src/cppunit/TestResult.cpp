#include "cppunit/TestResult.h"
#include "cppunit/TestListener.h"
#include <algorithm>

namespace CppUnit {

/// Destroys a test result
TestResult::~TestResult ()
{
  std::vector<TestFailure *>::iterator it;

  for (it = m_errors.begin (); it != m_errors.end (); ++it)
    delete *it;

  for (it = m_failures.begin (); it != m_failures.end (); ++it)
    delete *it;

  delete m_syncObject;
}

/// Construct a TestResult

  TestResult::TestResult ()
    : m_syncObject (new SynchronizationObject ())
{ 
    m_runTests = 0; 
    m_stop = false; 
}


/** Adds an error to the list of errors. 
 *  The passed in exception
 *  caused the error
 */
void 
  TestResult::addError (Test *test, Exception *e)
{ 
  ExclusiveZone zone (m_syncObject); 
  m_errors.push_back (new TestFailure (test, e)); 

  for ( std::vector<TestListener *>::iterator it = m_listeners.begin();
        it != m_listeners.end(); 
        ++it )
    (*it)->addError( test, e );
}


/** Adds a failure to the list of failures. The passed in exception
 * caused the failure.
 */
void 
  TestResult::addFailure (Test *test, Exception *e)
{ 
  ExclusiveZone zone (m_syncObject); 
  m_failures.push_back (new TestFailure (test, e)); 

  for ( std::vector<TestListener *>::iterator it = m_listeners.begin();
        it != m_listeners.end(); 
        ++it )
    (*it)->addFailure( test, e );
}


/// Informs the result that a test will be started.
void 
  TestResult::startTest (Test *test)
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
  TestResult::endTest (Test *test)
{ 
  ExclusiveZone zone (m_syncObject); 

  for ( std::vector<TestListener *>::iterator it = m_listeners.begin();
        it != m_listeners.end(); 
        ++it )
    (*it)->endTest( test );
}


/// Gets the number of run tests.
int 
  TestResult::runTests ()
{ 
  ExclusiveZone zone (m_syncObject); 
  return m_runTests; 
}


/// Gets the number of detected errors.
int 
  TestResult::testErrors ()
{ 
  ExclusiveZone zone (m_syncObject); 
  return m_errors.size (); 
}


/// Gets the number of detected failures.
int 
  TestResult::testFailures ()
{ 
  ExclusiveZone zone (m_syncObject); 
  return m_failures.size (); 
}


/// Returns whether the entire test was successful or not.
bool 
  TestResult::wasSuccessful ()
{ 
  ExclusiveZone zone (m_syncObject); 
  return m_failures.size () == 0 && m_errors.size () == 0; 
}


/// Returns a vector of the errors.
std::vector<TestFailure *>& 
  TestResult::errors ()
{ 
  ExclusiveZone zone (m_syncObject); 
  return m_errors; 
}


/// Returns a vector of the failures.
std::vector<TestFailure *>& 
  TestResult::failures ()
{ 
  ExclusiveZone zone (m_syncObject); 
  return m_failures; 
}


/// Returns whether testing should be stopped
bool 
  TestResult::shouldStop ()
{ 
  ExclusiveZone zone (m_syncObject); 
  return m_stop; 
}


/// Stop testing
void 
  TestResult::stop ()
{ 
  ExclusiveZone zone (m_syncObject); 
  m_stop = true; 
}


/** Accept a new synchronization object for protection of this instance
 * TestResult assumes ownership of the object
 */
void 
  TestResult::setSynchronizationObject (SynchronizationObject *syncObject)
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
  m_listeners.erase( std::remove( m_listeners.begin(), m_listeners.end(), listener ),
                     m_listeners.end());
}

} // namespace CppUnit
