#ifndef CPPUNIT_EXTENSIONS_TESTDECORATOR_H
#define CPPUNIT_EXTENSIONS_TESTDECORATOR_H

#include <cppunit/Portability.h>
#include <cppunit/Test.h>

namespace CppUnit {

class TestResult;


/*! \brief  Decorator for Tests.
 *
 * TestDecorator provides an alternate means to extend functionality
 * of a test class without subclassing the test.  Instead, one can
 * subclass the decorater and use it to wrap the test class.
 *
 * Does not assume ownership of the test it decorates
 */ 
class CPPUNIT_API TestDecorator : public Test
{
public:
  TestDecorator( Test *test );
  ~TestDecorator();

  int countTestCases() const;

  std::string getName() const;

  void run( TestResult *result );

  int getChildTestCount() const;

protected:
  Test *doGetChildTestAt( int index ) const;

  Test *m_test;

private:
  TestDecorator( const TestDecorator &);
  void operator =( const TestDecorator & );
};


inline 
TestDecorator::TestDecorator( Test *test )
{ 
  m_test = test; 
}


inline 
TestDecorator::~TestDecorator()
{
}


inline int 
TestDecorator::countTestCases() const
{ 
  return m_test->countTestCases(); 
}


inline void 
TestDecorator::run( TestResult *result )
{ 
  m_test->run(result); 
}


inline std::string 
TestDecorator::getName() const
{ 
  return m_test->getName(); 
}


inline int 
TestDecorator::getChildTestCount() const
{
  return m_test->getChildTestCount();
}


inline Test *
TestDecorator::doGetChildTestAt( int index ) const
{
  return m_test->getChildTestAt( index );
}

} // namespace CppUnit

#endif

