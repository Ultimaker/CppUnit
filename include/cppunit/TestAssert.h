#ifndef CPPUNIT_TESTASSERT_H
#define CPPUNIT_TESTASSERT_H

#include <string>

#ifndef CPPUNIT_EXCEPTION_H
#include "Exception.h"
#endif

namespace CppUnit {

  /*! \brief This class represents
   */
  class TestAssert
  {
  public:
    virtual ~TestAssert() {}

    static void    assertImplementation(
      bool         condition, 
      std::string  conditionExpression = "",
      long         lineNumber = Exception::UNKNOWNLINENUMBER,
      std::string  fileName = Exception::UNKNOWNFILENAME);

    static void    assertEquals     (long         expected, 
      long         actual,
      long         lineNumber = Exception::UNKNOWNLINENUMBER,
      std::string  fileName = Exception::UNKNOWNFILENAME);

    static void    assertEquals     (double       expected, 
      double       actual, 
      double       delta, 
      long         lineNumber = Exception::UNKNOWNLINENUMBER,
      std::string  fileName = Exception::UNKNOWNFILENAME);

    static std::string         notEqualsMessage (long         expected, 
      long         actual);

    static std::string         notEqualsMessage (double       expected, 
      double       actual);
  };


/** A set of macros which allow us to get the line number
 * and file name at the point of an error.
 * Just goes to show that preprocessors do have some
 * redeeming qualities.
 */
#define CPPUNIT_SOURCEANNOTATION
  
#ifdef CPPUNIT_SOURCEANNOTATION

    #undef assert
    #define assert(condition)\
    (CppUnit::TestAssert::assertImplementation ((condition),(#condition),\
        __LINE__, __FILE__))

#else

    #undef assert
    #define assert(condition)\
    (CppUnit::TestAssert::assertImplementation ((condition),"",\
        __LINE__, __FILE__))

#endif


/// Macro for primitive value comparisons
#define assertDoublesEqual(expected,actual,delta)\
(CppUnit::TestAssert::assertEquals ((expected),\
        (actual),(delta),__LINE__,__FILE__))

/// Macro for primitive value comparisons
#define assertLongsEqual(expected,actual)\
(CppUnit::TestAssert::assertEquals ((expected),\
        (actual),__LINE__,__FILE__))


} // namespace CppUnit

#endif  // CPPUNIT_TESTASSERT_H
