#include <cppunit/Test.h>
#include <cppunit/TestFailure.h>
#include <cppunit/TestListener.h>
#include <cppunit/TestResult.h>
#include <algorithm>
#include "DefaultProtector.h"
#include "ProtectorChain.h"
#include "ProtectorContext.h"

CPPUNIT_NS_BEGIN


/// Construct a TestResult
TestResult::TestResult( SynchronizationObject *syncObject )
    : SynchronizedObject( syncObject )
    , m_protectorChain( new ProtectorChain() )
{ 
  m_protectorChain->push( new DefaultProtector() );
  reset();
}


/// Destroys a test result
TestResult::~TestResult()
{
  delete m_protectorChain;
}


/** Resets the result for a new run.
 *
 * Clear the previous run result.
 */
void 
TestResult::reset()
{
  ExclusiveZone zone( m_syncObject ); 
  m_stop = false;
}


/** Adds an error to the list of errors. 
 *  The passed in exception
 *  caused the error
 */
void 
TestResult::addError( Test *test, 
                      Exception *e )
{ 
  addFailure( TestFailure( test, e, true ) );
}


/** Adds a failure to the list of failures. The passed in exception
 * caused the failure.
 */
void 
TestResult::addFailure( Test *test, Exception *e )
{ 
  addFailure( TestFailure( test, e, false ) );
}


/** Called to add a failure to the list of failures.
 */
void 
TestResult::addFailure( const TestFailure &failure )
{
  ExclusiveZone zone( m_syncObject ); 
  for ( TestListeners::iterator it = m_listeners.begin();
        it != m_listeners.end(); 
        ++it )
    (*it)->addFailure( failure );
}


/// Informs TestListener that a test will be started.
void 
TestResult::startTest( Test *test )
{ 
  ExclusiveZone zone( m_syncObject ); 
  for ( TestListeners::iterator it = m_listeners.begin();
        it != m_listeners.end(); 
        ++it )
    (*it)->startTest( test );
}

  
/// Informs TestListener that a test was completed.
void 
TestResult::endTest( Test *test )
{ 
  ExclusiveZone zone( m_syncObject ); 
  for ( TestListeners::iterator it = m_listeners.begin();
        it != m_listeners.end(); 
        ++it )
    (*it)->endTest( test );
}


/// Informs TestListener that a test suite will be started.
void 
TestResult::startSuite( Test *test )
{
  ExclusiveZone zone( m_syncObject ); 
  for ( TestListeners::iterator it = m_listeners.begin();
        it != m_listeners.end(); 
        ++it )
    (*it)->startSuite( test );
}


/// Informs TestListener that a test suite was completed.
void 
TestResult::endSuite( Test *test )
{
  ExclusiveZone zone( m_syncObject ); 
  for ( TestListeners::iterator it = m_listeners.begin();
        it != m_listeners.end(); 
        ++it )
    (*it)->endSuite( test );
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


void 
TestResult::addListener( TestListener *listener )
{
  ExclusiveZone zone( m_syncObject ); 
  m_listeners.push_back( listener );
}


void 
TestResult::removeListener ( TestListener *listener )
{
  ExclusiveZone zone( m_syncObject ); 
  m_listeners.erase( std::remove( m_listeners.begin(), 
                                  m_listeners.end(), 
                                  listener ),
                     m_listeners.end());
}


void 
TestResult::runTest( Test *test )
{
  startTestRun( test );
  test->run( this );
  endTestRun( test );
}


void 
TestResult::startTestRun( Test *test )
{
  ExclusiveZone zone( m_syncObject ); 
  for ( TestListeners::iterator it = m_listeners.begin();
        it != m_listeners.end(); 
        ++it )
    (*it)->startTestRun( test, this );
}


void 
TestResult::endTestRun( Test *test )
{
  ExclusiveZone zone( m_syncObject ); 
  for ( TestListeners::iterator it = m_listeners.begin();
        it != m_listeners.end(); 
        ++it )
    (*it)->endTestRun( test, this );
}


bool 
TestResult::protect( const Functor &functor,
                     Test *test,
                     const std::string &shortDescription )
{
  ProtectorContext context( test, this, shortDescription );
  return m_protectorChain->protect( functor, context );
}


void 
TestResult::pushProtector( Protector *protector )
{
  m_protectorChain->push( protector );
}


void 
TestResult::popProtector()
{
  m_protectorChain->pop();
}


CPPUNIT_NS_END
