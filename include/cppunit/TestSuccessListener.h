#ifndef CPPUNIT_TESTSUCCESSLISTENER_H
#define CPPUNIT_TESTSUCCESSLISTENER_H

#include <cppunit/SynchronizedObject.h>
#include <cppunit/TestListener.h>


namespace CppUnit
{

/*! \brief TestListener that checks if any test case failed.
 * \ingroup TrackingTestExecution
 */
class CPPUNIT_API TestSuccessListener : public TestListener,
                                        public SynchronizedObject
{
public:
  /*! Constructs a TestSuccessListener object.
   */
  TestSuccessListener( SynchronizationObject *syncObject = 0 );

  /// Destructor.
  virtual ~TestSuccessListener();

  virtual void reset();

  void addFailure( const TestFailure &failure );

  /// Returns whether the entire test was successful or not.
  virtual bool wasSuccessful() const;

private:
  bool m_success;
};


} //  namespace CppUnit


#endif  // CPPUNIT_TESTSUCCESSLISTENER_H
