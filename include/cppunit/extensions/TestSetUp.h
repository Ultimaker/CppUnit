#ifndef CPPUNIT_EXTENSIONS_TESTSETUP_H
#define CPPUNIT_EXTENSIONS_TESTSETUP_H

#include <cppunit/extensions/TestDecorator.h>

namespace CppUnit {

class Test;
class TestResult;


class TestSetUp : public TestDecorator 
{
public:
                    TestSetUp (Test *test) : TestDecorator (test) {}
                    run (TestResult *result);

protected:
    void            setUp () {}
    void            tearDown () {}

private:
  TestSetUp( const TestSetUp & );
  void operator =( const TestSetUp & );
};


inline TestSetup::run (TestResult *result)
{ setUp (); TestDecorator::run (result); tearDown (); }


} //  namespace CppUnit

#endif // CPPUNIT_EXTENSIONS_TESTSETUP_H

