#ifndef CPPUNIT_TESTSUCESSLISTENER_H
#define CPPUNIT_TESTSUCESSLISTENER_H

#include <cppunit/SynchronizedObject.h>
#include <cppunit/TestListener.h>


namespace CppUnit
{

/*! A TestSucessListener is a TestListener which check if any test case failed.
 */
class TestSucessListener : public TestListener,
                           public SynchronizedObject
{
public:
  /*! Constructs a TestSucessListener object.
   */
  TestSucessListener( SynchronizationObject *syncObject = 0 );

  /// Destructor.
  virtual ~TestSucessListener();

  virtual void reset();

  void addFailure( const TestFailure &failure );

  /// Returns whether the entire test was successful or not.
  virtual bool wasSuccessful() const;

private:
  bool m_sucess;
};


} //  namespace CppUnit


#endif  // CPPUNIT_TESTSUCESSLISTENER_H
