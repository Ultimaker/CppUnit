#ifndef CPPUNIT_TESTLISTENER_H
#define CPPUNIT_TESTLISTENER_H

namespace CppUnit {

  class Exception;
  class Test;


  /**
   * A Listener for test progress
   * \see TestResult
   */
  class TestListener
  {
    public:
      virtual ~TestListener() {}

      virtual void addError( Test *test, Exception *e ) {}
      virtual void addFailure( Test *test, Exception *e ) {}
      virtual void startTest( Test *test ) {}
      virtual void endTest( Test *test ) {}
  };

} // namespace CppUnit

#endif // CPPUNIT_TESTLISTENER_H


