#ifndef CPPUNIT_EXTENSIONS_TESTFACTORY_H
#define CPPUNIT_EXTENSIONS_TESTFACTORY_H

namespace CppUnit {

  class Test;

  /** This class represents an abstract Test factory.
   */
  class TestFactory 
  {
  public:
    virtual ~TestFactory() {}

    /** Makes a new test.
     * \return A new Test.
     */
    virtual Test* makeTest() = 0;
  };

}  // namespace CppUnit

#endif  // CPPUNIT_EXTENSIONS_TESTFACTORY_H
