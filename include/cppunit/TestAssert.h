#ifndef CPPUNIT_TESTASSERT_H
#define CPPUNIT_TESTASSERT_H

#include <string>
#include <sstream>
#include <cppunit/config.h>
#include <cppunit/Exception.h>


namespace CppUnit {

    template <class T>
    struct assertion_traits 
    {  
	static bool equal( const T& x, const T& y )
	{
	    return x == y;
	}

	static std::string toString( const T& x )
	{
	    std::ostringstream ost;
	    ost << x;
	    return ost.str();
	}
    };


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
      std::string  fileName = Exception::UNKNOWNFILENAME)
	{
	    if (!condition) 
		throw Exception (conditionExpression, 
				 lineNumber, 
				 fileName); 
	}


    template <class T>
    static std::string         notEqualsMessage (const T& expected, 
						 const T& actual)
    {
	return "expected: " + assertion_traits<T>::toString(expected)
	     + " but was: " + assertion_traits<T>::toString(actual);
    }


    template <class T>
    static void    assertEquals     (
      const T&     expected,
      const T&     actual,
      long         lineNumber = Exception::UNKNOWNLINENUMBER,
      std::string  fileName = Exception::UNKNOWNFILENAME)
	{
	    assertImplementation( assertion_traits<T>::equal(expected,actual),
				  notEqualsMessage(expected, actual), 
				  lineNumber, 
				  fileName); 
	}

    static void    assertEquals     (double       expected, 
      double       actual, 
      double       delta, 
      long         lineNumber = Exception::UNKNOWNLINENUMBER,
      std::string  fileName = Exception::UNKNOWNFILENAME)
	{
	    assertImplementation( fabs(expected - actual) <= delta,
				  notEqualsMessage(expected, actual), 
				  lineNumber, 
				  fileName); 
	}
  };


/** A set of macros which allow us to get the line number
 * and file name at the point of an error.
 * Just goes to show that preprocessors do have some
 * redeeming qualities.
 */
#if CPPUNIT_HAVE_CPP_SOURCE_ANNOTATION

#  define CPPUNIT_ASSERT(condition)\
    (CppUnit::TestAssert::assertImplementation ((condition),(#condition),\
        __LINE__, __FILE__))

#else

#  define CPPUNIT_ASSERT(condition)\
    (CppUnit::TestAssert::assertImplementation ((condition),"",\
        __LINE__, __FILE__))

#endif


/// Generalized macro for primitive value comparisons
/** Equality and string representation can be defined with
 * an appropriate assertion_traits class.
 * A diagnostic is printed if actual and expected values disagree.
 */
#define CPPUNIT_ASSERT_EQUAL(expected,actual)\
  (CppUnit::TestAssert::assertEquals ((expected),\
    (actual),__LINE__,__FILE__))

/// Macro for primitive value comparisons
#define CPPUNIT_ASSERT_DOUBLES_EQUAL(expected,actual,delta)\
  (CppUnit::TestAssert::assertEquals ((expected),\
    (actual),(delta),__LINE__,__FILE__))


// Backwards compatibility

#if CPPUNIT_ENABLE_NAKED_ASSERT

#undef assert
#define assert(c)                 CPPUNIT_ASSERT(c)
#define assertEqual(e,a)          CPPUNIT_ASSERT_EQUAL(e,a)
#define assertDoublesEqual(e,a,d) CPPUNIT_ASSERT_DOUBLES_EQUAL(e,a,d)
#define assertLongsEqual(e,a)     CPPUNIT_ASSERT_EQUAL(e,a)

#endif


} // namespace CppUnit

#endif  // CPPUNIT_TESTASSERT_H
