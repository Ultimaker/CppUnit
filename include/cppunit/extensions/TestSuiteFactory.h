#ifndef CPPUNIT_EXTENSIONS_TESTSUITEFACTORY_H
#define CPPUNIT_EXTENSIONS_TESTSUITEFACTORY_H

#include <cppunit/extensions/TestFactory.h>

namespace CppUnit {

  class Test;

  template<typename TestCaseType>
    class TestSuiteFactory : public TestFactory
  {
  public:
    virtual Test *makeTest()
    {
      return TestCaseType::suite();
    }
  };

}  // namespace CppUnit

#endif  // CPPUNIT_EXTENSIONS_TESTSUITEFACTORY_H
