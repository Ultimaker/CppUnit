#ifndef CPPUNIT_EXTENSIONS_TESTDECORATOR_H
#define CPPUNIT_EXTENSIONS_TESTDECORATOR_H

#include <cppunit/Portability.h>
#include <cppunit/TestLeaf.h>

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
class CPPUNIT_API TestDecorator : public TestLeaf
{
public:
  TestDecorator( Test *test );
  ~TestDecorator();

  int countTestCases() const;
  std::string getName() const;
  void run( TestResult *result );

protected:
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

} // namespace CppUnit

#endif

