#ifndef CPPUNIT_TESTSUITEFACTORY_H
#define CPPUNIT_TESTSUITEFACTORY_H

#ifndef CPPUNIT_ABSTRACTTESTFACTORY_H
#include "AbstractTestFactory.h"
#endif


namespace CppUnit {

  class Test;

  template<class TestCaseType>
    class TestSuiteFactory : public AbstractTestFactory
  {
  public:
    virtual Test *makeTest()
    {
      return TestCaseType::suite();
    }
  };

}  // namespace CppUnit

#endif  // CPPUNIT_TESTSUITEFACTORY_H
