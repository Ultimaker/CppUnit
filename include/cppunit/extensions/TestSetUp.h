#ifndef CPPUNIT_EXTENSIONS_TESTSETUP_H
#define CPPUNIT_EXTENSIONS_TESTSETUP_H

#include <cppunit/extensions/TestDecorator.h>

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

#endif // CPPUNIT_EXTENSIONS_TESTSETUP_H

