#ifndef MOCKTESTLISTENER_H
#define MOCKTESTLISTENER_H

#include <cppunit/TestListener.h>


class MockTestListener : public CppUnit::TestListener
{
public:
  MockTestListener();
  virtual ~MockTestListener() {}

  virtual void addError( CppUnit::Test *test, CppUnit::Exception *e );
  virtual void addFailure( CppUnit::Test *test, CppUnit::Exception *e );
  virtual void startTest( CppUnit::Test *test );
  virtual void endTest( CppUnit::Test *test );

  bool wasCalled() const;
  void reset();

private:
  bool m_called;
};



// Inlines methods for MockTestListener:
// -------------------------------------



#endif  // MOCKTESTLISTENER_H
