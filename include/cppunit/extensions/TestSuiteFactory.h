#ifndef CPPUNIT_EXTENSIONS_TESTSUITEFACTORY_H
#define CPPUNIT_EXTENSIONS_TESTSUITEFACTORY_H

#include <cppunit/extensions/AbstractTestFactory.h>

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

#endif  // CPPUNIT_EXTENSIONS_TESTSUITEFACTORY_H
