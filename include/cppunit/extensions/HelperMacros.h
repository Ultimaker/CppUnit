// //////////////////////////////////////////////////////////////////////////
// Header file HelperMacros.h
// (c)Copyright 2000, Baptiste Lepilleur.
// Created: 2001/04/15
// //////////////////////////////////////////////////////////////////////////
#ifndef CPPUNIT_EXTENSIONS_HELPERMACROS_H
#define CPPUNIT_EXTENSIONS_HELPERMACROS_H

#include <cppunit/Portability.h>
#include <cppunit/extensions/AutoRegisterSuite.h>
#include <cppunit/extensions/TestSuiteBuilder.h>
#include <string>

// The macro __CPPUNIT_SUITE_CTOR_ARGS expand to an expression used to construct
// the TestSuiteBuilder with macro CPPUNIT_TEST_SUITE.
//
// The name of the suite is obtained using RTTI if CPPUNIT_USE_TYPEINFO_NAME 
// is defined, otherwise it is extracted from the macro parameter
//
// This macro is for cppunit internal and should not be use otherwise.
#if CPPUNIT_USE_TYPEINFO_NAME
#  define __CPPUNIT_SUITE_CTOR_ARGS( ATestCaseType )
#else
#  define __CPPUNIT_SUITE_CTOR_ARGS( ATestCaseType ) (std::string(#ATestCaseType))
#endif


/** \file
 * Macros intended to ease the definition of test suites.
 *
 * The macros
 * CPPUNIT_TEST_SUITE(), CPPUNIT_TEST(), and CPPUNIT_TEST_SUITE_END()
 * are designed to facilitate easy creation of a test suite.
 * For example,
 *
 * \code
 * #include <cppunit/extensions/HelperMacros.h>
 * class MyTest : public CppUnit::TestCase {
 *   CPPUNIT_TEST_SUITE( MyTest );
 *   CPPUNIT_TEST( testEquality );
 *   CPPUNIT_TEST( testSetName );
 *   CPPUNIT_TEST_SUITE_END();
 * public:
 *   void testEquality();
 *   void testSetName();
 * };
 * \endcode
 * 
 * The effect of these macros is to define two methods in the
 * class MyTest.  The first method is an auxiliary function
 * named registerTests that you will not need to call directly.
 * The second function
 * \code static CppUnit::TestSuite *suite()\endcode
 * returns a pointer to the suite of tests defined by the CPPUNIT_TEST()
 * macros.  
 *
 * Rather than invoking suite() directly,
 * the macro CPPUNIT_TEST_SUITE_REGISTRATION() is
 * used to create a static variable that automatically
 * registers its test suite in a global registry.
 * The registry yields a Test instance containing all the
 * registered suites.
 * \code
 * CPPUNIT_TEST_SUITE_REGISTRATION( MyTest );
 * CppUnit::Test* tp =
 *   CppUnit::TestFactoryRegistry::getRegistry().makeTest();
 * \endcode
 * 
 * The test suite macros can even be used with templated test classes.
 * For example:
 *
 * \code
 * template<typename CharType>
 * class StringTest : public CppUnit::Testcase {
 *   CPPUNIT_TEST_SUITE( StringTest );
 *   CPPUNIT_TEST( testAppend );
 *   CPPUNIT_TEST_SUITE_END();
 * public:  
 *   ...
 * };
 * \endcode
 *
 * You need to add in an implementation file:
 *
 * \code
 * CPPUNIT_TEST_SUITE_REGISTRATION( String<char> );
 * CPPUNIT_TEST_SUITE_REGISTRATION( String<wchar_t> );
 * \endcode
 */


/** Begin test suite
 *
 * This macro starts the declaration of a new test suite.
 * Use CPPUNIT_TEST_SUB_SUITE() instead, if you wish to include the
 * test suite of the parent class.
 *
 * \param ATestCaseType Type of the test case class.
 * \see CPPUNIT_TEST_SUB_SUITE, CPPUNIT_TEST, CPPUNIT_TEST_SUITE_END, CPPUNIT_TEST_SUITE_REGISTRATION.
 */
#define CPPUNIT_TEST_SUITE( ATestCaseType )                               \
  private:                                                                \
    typedef ATestCaseType __ThisTestCaseType;                             \
    class ThisTestCaseFactory : public CppUnit::TestFactory               \
    {                                                                     \
      virtual CppUnit::Test *makeTest()                                   \
      {                                                                   \
        return new ATestCaseType();                                       \
      }                                                                   \
    };                                                                    \
  public:                                                                 \
    static void                                                           \
    registerTests( CppUnit::TestSuite *suite,                             \
                   CppUnit::TestFactory *factory )                        \
    {                                                                     \
      CppUnit::TestSuiteBuilder<__ThisTestCaseType> builder( suite );


/** Begin test suite (includes parent suite)
 * 
 * This macro may only be used in a class whose parent class
 * defines a test suite using CPPUNIT_TEST_SUITE() or CPPUNIT_TEST_SUB_SUITE().
 *
 * This macro begins the declaration of a test suite, in the same
 * manner as CPPUNIT_TEST_SUITE().  In addition, the test suite of the
 * parent is automatically inserted in the test suite being
 * defined.
 * 
 * Here is an example:
 *
 * \code
 * #include <cppunit/extensions/HelperMacros.h>
 * class MySubTest : public MyTest {
 *   CPPUNIT_TEST_SUB_SUITE( MySubTest, MyTest );
 *   CPPUNIT_TEST( testAdd );
 *   CPPUNIT_TEST( testSub );
 *   CPPUNIT_TEST_SUITE_END();
 * public:
 *   void testAdd();
 *   void testSub();
 * };
 * \endcode
 *
 * \param ATestCaseType Type of the test case class.
 * \param ASuperClass   Type of the parent class.
 * \see CPPUNIT_TEST_SUITE.
 */
#define CPPUNIT_TEST_SUB_SUITE( ATestCaseType, ASuperClass )  \
  private:                                                    \
    typedef ASuperClass __ThisSuperClassType;                 \
    CPPUNIT_TEST_SUITE( ATestCaseType );                      \
      __ThisSuperClassType::registerTests( suite, factory )


/** Add a method to the suite.
 * \param testMethod Name of the method of the test case to add to the
 *                   suite. The signature of the method must be of
 *                   type: void testMethod();
 * \see  CPPUNIT_TEST_SUITE.
 */
#define CPPUNIT_TEST( testMethod )                                      \
      builder.addTestCaller( #testMethod,                               \
                             &__ThisTestCaseType::testMethod ,          \
                             (__ThisTestCaseType*)factory->makeTest() ) 


/** End declaration of the test suite.
 *
 * After this macro, member access is set to "private".
 *
 * \see  CPPUNIT_TEST_SUITE.
 * \see  CPPUNIT_TEST_SUITE_REGISTRATION.
 */
#define CPPUNIT_TEST_SUITE_END()                                        \
      builder.takeSuite();                                              \
    }                                                                   \
    static CppUnit::TestSuite *suite()                                  \
    {                                                                   \
      CppUnit::TestSuiteBuilder<__ThisTestCaseType>                     \
          builder __CPPUNIT_SUITE_CTOR_ARGS( ATestCaseType );           \
      ThisTestCaseFactory factory;                                      \
      __ThisTestCaseType::registerTests( builder.suite(), &factory );   \
      return builder.takeSuite();                                       \
    }                                                                   \
  private: /* dummy typedef so that the macro can still end with ';'*/  \
    typedef ThisTestCaseFactory __ThisTestCaseFactory                   

#define __CPPUNIT_CONCATENATE_DIRECT( s1, s2 ) s1##s2
#define __CPPUNIT_CONCATENATE( s1, s2 ) __CPPUNIT_CONCATENATE_DIRECT( s1, s2 )

/** Decorates the specified string with the line number to obtain a unique name;
 * @param str String to decorate.
 */
#define __CPPUNIT_MAKE_UNIQUE_NAME( str ) __CPPUNIT_CONCATENATE( str, __LINE__ )


/** Register test suite into global registry.
 *
 * This macro declares a static variable whose construction
 * causes a test suite factory to be inserted in a global registry
 * of such factories.  The registry is available by calling
 * the static function CppUnit::TestFactoryRegistry::getRegistry().
 * 
 * \param ATestCaseType Type of the test case class.
 * \warning This macro should be used only once per line of code (the line
 *          number is used to name a hidden static variable).
 * \see  CPPUNIT_TEST_SUITE, CppUnit::AutoRegisterSuite.
 */
#define CPPUNIT_TEST_SUITE_REGISTRATION( ATestCaseType )                     \
  static CppUnit::AutoRegisterSuite< ATestCaseType >                    \
             __CPPUNIT_MAKE_UNIQUE_NAME(__autoRegisterSuite )


// Backwards compatibility
// (Not tested!)

#if CPPUNIT_ENABLE_CU_TEST_MACROS

#define CU_TEST_SUITE(tc) CPPUNIT_TEST_SUITE(tc)
#define CU_TEST_SUB_SUITE(tc,sc) CPPUNIT_TEST_SUB_SUITE(tc,sc)
#define CU_TEST(tm) CPPUNIT_TEST(tm)
#define CU_TEST_SUITE_END() CPPUNIT_TEST_SUITE_END()
#define CU_TEST_SUITE_REGISTRATION(tc) CPPUNIT_TEST_SUITE_REGISTRATION(tc)

#endif


#endif  // CPPUNIT_EXTENSIONS_HELPERMACROS_H
