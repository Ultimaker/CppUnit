// //////////////////////////////////////////////////////////////////////////
// Header file HelperMacros.h
// (c)Copyright 2000, Baptiste Lepilleur.
// Created: 2001/04/15
// //////////////////////////////////////////////////////////////////////////
#ifndef CPPUNIT_EXTENSIONS_HELPERMACROS_H
#define CPPUNIT_EXTENSIONS_HELPERMACROS_H

#include <string>
#include <cppunit/extensions/AutoRegisterSuite.h>
#include <cppunit/extensions/TestSuiteBuilder.h>

// The macro __CU_SUITE_CTOR_ARGS expand to an expression used to construct
// the TestSuiteBuilder with macro CU_TEST_SUITE.
//
// The name of the suite is obtained using RTTI if CU_USE_TYPEINFO is
// defined, otherwise it is extracted from the macro parameter
//
// This macro is for cppunit internal and should not be use otherwise.
#ifdef CU_USE_TYPEINFO
#define __CU_SUITE_CTOR_ARGS( ATestCaseType )

#else  // CU_USE_TYPEINFO
#define __CU_SUITE_CTOR_ARGS( ATestCaseType ) (std::string(#ATestCaseType))

#endif // CU_USE_TYPEINFO


/** \file
 * Macros intended to ease the definition of test suites.
 *
 * The macros
 * CU_TEST_SUITE(), CU_TEST(), and CU_TEST_SUITE_END()
 * are designed to facilitate easy creation of a test suite.
 * For example,
 *
 * \code
 * #include <cppunit/extensions/HelperMacros.h>
 * class MyTest : public CppUnit::TestCase {
 *   CU_TEST_SUITE( MyTest );
 *   CU_TEST( testEquality );
 *   CU_TEST( testSetName );
 *   CU_TEST_SUITE_END();
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
 * returns a pointer to the suite of tests defined by the CU_TEST()
 * macros.  
 *
 * Rather than invoking suite() directly,
 * the macro CU_TEST_SUITE_REGISTRATION() is
 * used to create a static variable that automatically
 * registers its test suite in a global registry.
 * The registry yields a Test instance containing all the
 * registered suites.
 * \code
 * CU_TEST_SUITE_REGISTRATION( MyTest );
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
 *   CU_TEST_SUITE( StringTest );
 *   CU_TEST( testAppend );
 *   CU_TEST_SUITE_END();
 * public:  
 *   ...
 * };
 * \endcode
 *
 * You need to add in an implementation file:
 *
 * \code
 * CU_TEST_SUITE_REGISTRATION( String<char> );
 * CU_TEST_SUITE_REGISTRATION( String<wchar_t> );
 * \endcode
 */


/** Begin test suite
 *
 * This macro starts the declaration of a new test suite.
 * Use CU_TEST_SUB_SUITE() instead, if you wish to include the
 * test suite of the parent class.
 *
 * \param ATestCaseType Type of the test case class.
 * \see CU_TEST_SUB_SUITE, CU_TEST, CU_TEST_SUITE_END, CU_TEST_SUITE_REGISTRATION.
 */
#define CU_TEST_SUITE( ATestCaseType )                                  \
  private:                                                              \
    typedef ATestCaseType __ThisTestCaseType;                           \
  public:                                                               \
    template<typename TestCaseType>                                     \
    static void                                                         \
    registerTests( CppUnit::TestSuiteBuilder<TestCaseType> &suite,      \
                   TestCaseType *test )                                 \
    {


/** Begin test suite (includes parent suite)
 * 
 * This macro may only be used in a class whose parent class
 * defines a test suite using CU_TEST_SUITE() or CU_TEST_SUB_SUITE().
 *
 * This macro begins the declaration of a test suite, in the same
 * manner as CU_TEST_SUITE().  In addition, the test suite of the
 * parent is automatically inserted in the test suite being
 * defined.
 * 
 * Here is an example:
 *
 * \code
 * #include <cppunit/extensions/HelperMacros.h>
 * class MySubTest : public MyTest {
 *   CU_TEST_SUB_SUITE( MySubTest, MyTest );
 *   CU_TEST( testAdd );
 *   CU_TEST( testSub );
 *   CU_TEST_SUITE_END();
 * public:
 *   void testAdd();
 *   void testSub();
 * };
 * \endcode
 *
 * \param ATestCaseType Type of the test case class.
 * \param ASuperClass   Type of the parent class.
 * \see CU_TEST_SUITE.
 */
#define CU_TEST_SUB_SUITE( ATestCaseType, ASuperClass )                       \
  private:                                                                    \
    typedef ASuperClass __ThisSuperClassType;                                 \
  CU_TEST_SUITE( ATestCaseType );                                             \
      __ThisSuperClassType::registerTests( suite, test )


/** Add a method to the suite.
 * \param testMethod Name of the method of the test case to add to the
 *                   suite. The signature of the method must be of
 *                   type: void testMethod();
 * \see  CU_TEST_SUITE.
 */
#define CU_TEST( testMethod )                                           \
      suite.addTestCaller( #testMethod, &__ThisTestCaseType::testMethod ) 


/** End declaration of the test suite.
 *
 * After this macro, member access is set to "private".
 *
 * \see  CU_TEST_SUITE.
 * \see  CU_TEST_SUITE_REGISTRATION.
 */
#define CU_TEST_SUITE_END()                                             \
}                                                                       \
    static CppUnit::Test *suite()                                       \
    {                                                                   \
      __ThisTestCaseType *test =NULL;                                   \
      CppUnit::TestSuiteBuilder<__ThisTestCaseType>                     \
          suite __CU_SUITE_CTOR_ARGS( ATestCaseType );                  \
      __ThisTestCaseType::registerTests( suite, test );                 \
      return suite.takeSuite();                                         \
    }                                                                   \
  private:

#define __CU_CONCATENATE_DIRECT( s1, s2 ) s1##s2
#define __CU_CONCATENATE( s1, s2 ) __CU_CONCATENATE_DIRECT( s1, s2 )

/** Decorates the specified string with the line number to obtain a unique name;
 * @param str String to decorate.
 */
#define __CU_MAKE_UNIQUE_NAME( str ) __CU_CONCATENATE( str, __LINE__ )


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
 * \see  CU_TEST_SUITE, CppUnit::AutoRegisterSuite.
 */
#define CU_TEST_SUITE_REGISTRATION( ATestCaseType )                     \
  static CppUnit::AutoRegisterSuite< ATestCaseType >                    \
             __CU_MAKE_UNIQUE_NAME(__autoRegisterSuite )


#endif  // CPPUNIT_EXTENSIONS_HELPERMACROS_H
