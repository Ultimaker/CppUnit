
#ifndef CPP_UINT_TESTSETUP_H
#define CPP_UINT_TESTSETUP_H

#ifndef CPPUNIT_TESTDECORATOR_H
#include "TestDecorator.h"
#endif

namespace CppUnit {

class Test;
class TestResult;


class TestSetup : public TestDecorator 
{
public:
                    TestSetup (Test *test) : TestDecorator (test) {}
                    run (TestResult *result);

protected:
    void            setUp () {}
    void            tearDown () {}

private:
  TestSetup( const TestSetup & );
  void operator =( const TestSetup & );
};


inline TestSetup::run (TestResult *result)
{ setUp (); TestDecorator::run (result); tearDown (); }


} //  namespace CppUnit

#endif

