#ifndef CPPUNIT_ABSTRACTTESTFACTORY_H
#define CPPUNIT_ABSTRACTTESTFACTORY_H



namespace CppUnit {

  class Test;

  /** This class represents an abstract Test factory.
   */
  class AbstractTestFactory 
  {
  public:
    virtual ~AbstractTestFactory() {}

    /** Makes a new test.
     * \return A new Test.
     */
    virtual Test *makeTest() =0;
  };

}  // namespace CppUnit

#endif  // CPPUNIT_ABSTRACTTESTFACTORY_H
