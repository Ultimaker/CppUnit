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

CPPUNIT_NS_BEGIN


  class TestFixture;

  /*! \brief Abstract TestFixture factory.
   */
  class TestFixtureFactory
  {
  public:
    //! Creates a new TestFixture instance.
    virtual CPPUNIT_NS(TestFixture) *makeFixture() =0;
  };

CPPUNIT_NS_END




/*! \addtogroup WritingTestFixture Writing test fixture
 */
/** @{
 */


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
 * class MyTest : public CppUnit::TestFixture {
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
 * class StringTest : public CppUnit::TestFixture {
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
 * CPPUNIT_TEST_SUITE_REGISTRATION( StringTest<char> );
 * CPPUNIT_TEST_SUITE_REGISTRATION( StringTest<wchar_t> );
 * \endcode
 */


/*! \brief Begin test suite
 *
 * This macro starts the declaration of a new test suite.
 * Use CPPUNIT_TEST_SUB_SUITE() instead, if you wish to include the
 * test suite of the parent class.
 *
 * \param ATestFixtureType Type of the test case class. This type \b MUST
 *                         be derived from TestFixture.
 * \see CPPUNIT_TEST_SUB_SUITE, CPPUNIT_TEST, CPPUNIT_TEST_SUITE_END, 
 * \see CPPUNIT_TEST_SUITE_REGISTRATION, CPPUNIT_TEST_EXCEPTION, CPPUNIT_TEST_FAIL.
 */
#define CPPUNIT_TEST_SUITE( ATestFixtureType )                             \
  private:                                                                 \
    typedef ATestFixtureType ThisTestFixtureType;                          \
    class __ThisTestFixtureFactory : public CPPUNIT_NS(TestFixtureFactory) \
    {                                                                      \
      virtual CPPUNIT_NS(TestFixture) *makeFixture()                       \
      {                                                                    \
        return new ATestFixtureType();                                     \
      }                                                                    \
    };                                                                     \
    static const CPPUNIT_NS(TestNamer) &__getTestNamer()                   \
    {                                                                      \
      static CPPUNIT_TESTNAMER_DECL( testNamer, ATestFixtureType );        \
      return testNamer;                                                    \
    }                                                                      \
  public:                                                                  \
    class ThisTestFixtureFactory                                           \
    {                                                                      \
    public:                                                                \
      ThisTestFixtureFactory( CPPUNIT_NS(TestFixtureFactory) *factory )    \
        : m_factory( factory )                                             \
      {                                                                    \
      }                                                                    \
      ThisTestFixtureType *makeFixture() const                             \
      {                                                                    \
        return (ThisTestFixtureType *)m_factory->makeFixture();            \
      }                                                                    \
    private:                                                               \
      CPPUNIT_NS(TestFixtureFactory) *m_factory;                           \
    };                                                                     \
                                                                           \
    static void                                                            \
    __registerTests( CPPUNIT_NS(TestSuite) *suite,                         \
                     CPPUNIT_NS(TestFixtureFactory) *fixtureFactory,       \
                     const CPPUNIT_NS(TestNamer) &namer )                  \
    {                                                                      \
      const ThisTestFixtureFactory factory( fixtureFactory );              \
      CPPUNIT_NS(TestSuiteBuilder)<ThisTestFixtureType> builder( suite, namer )


/*! \brief Begin test suite (includes parent suite)
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
 * \param ATestFixtureType Type of the test case class. This type \b MUST
 *                         be derived from TestFixture.
 * \param ASuperClass   Type of the parent class.
 * \see CPPUNIT_TEST_SUITE.
 */
#define CPPUNIT_TEST_SUB_SUITE( ATestFixtureType, ASuperClass )  \
  private:                                                       \
    typedef ASuperClass __ThisSuperClassType;                    \
    CPPUNIT_TEST_SUITE( ATestFixtureType );                      \
      __ThisSuperClassType::__registerTests( suite, fixtureFactory, namer )


/*! \brief Add a method to the suite.
 * \param testMethod Name of the method of the test case to add to the
 *                   suite. The signature of the method must be of
 *                   type: void testMethod();
 * \see  CPPUNIT_TEST_SUITE.
 */
#define CPPUNIT_TEST( testMethod )                                           \
      builder.addTestCaller( #testMethod,                                    \
                             &ThisTestFixtureType::testMethod ,            \
                             factory.makeFixture() ) 

/*! \brief Add a test to the suite (for custom test macro).
 *
 * The specified test will be added to the test suite being declared. This macro
 * is intended for \e advanced usage, to extend %CppUnit by creating new macro such
 * as CPPUNIT_TEST_EXCEPTION()...
 *
 * Between macro CPPUNIT_TEST_SUITE() and CPPUNIT_TEST_SUITE_END(), you can assume
 * that the following variables can be used:
 * \code
 * const ThisTestFixtureFactory &factory;
 * const CppUnit::TestNamer &namer;
 * \endcode
 *
 * \c factory can be used to create a new instance of the TestFixture type 
 * specified in CPPUNIT_TEST_SUITE():
 * \code
 *   factory.makeFixture()\endcode
 *
 * Below is an example that show how to use this macro to create new macro to add
 * test to the fixture suite. The macro below show how you would add a new type
 * of test case which fails if the execution last more than a given time limit.
 * It relies on an imaginary TimeOutTestCaller class which has an interface similar
 * to TestCaller.
 * 
 * \code
 * #define CPPUNITEX_TEST_TIMELIMIT( testMethod, timeLimit )            \
 *      CPPUNIT_TEST_ADD( (new TimeOutTestCaller<ThisTestFixtureType>(  \
 *                  namer.getTestNameFor( #testMethod ),                \
 *                  &ThisTestFixtureType::testMethod,                   \
 *                  factory.makeFixture(),                              \
 *                  timeLimit ) ) )
 *   
 * class PerformanceTest : CppUnit::TestFixture
 * {
 * public:
 *   CPPUNIT_TEST_SUITE( PerformanceTest );
 *   CPPUNITEX_TEST_TIMELIMIT( testSortReverseOrder, 5.0 );
 *   CPPUNIT_TEST_SUITE_END();
 *
 *   void testSortReverseOrder();
 * };
 * \endcode
 *
 * \param test Test to add to the suite. Must be a subclass of Test. The test name
 *             should have been obtained using TestNamer::getTestNameFor().
 */
#define CPPUNIT_TEST_ADD( test ) \
      builder.addTest( test )

/*! \brief Add a test which fail if the specified exception is not caught.
 *
 * Example:
 * \code
 * #include <cppunit/extensions/HelperMacros.h>
 * #include <vector>
 * class MyTest : public CppUnit::TestFixture {
 *   CPPUNIT_TEST_SUITE( MyTest );
 *   CPPUNIT_TEST_EXCEPTION( testVectorAtThrow, std::invalid_argument );
 *   CPPUNIT_TEST_SUITE_END();
 * public:
 *   void testVectorAtThrow()
 *   {
 *     std::vector<int> v;
 *     v.at( 1 );     // must throw exception std::invalid_argument
 *   }
 * };
 * \endcode
 *
 * \param testMethod Name of the method of the test case to add to the suite.
 * \param ExceptionType Type of the exception that must be thrown by the test 
 *                      method.
 */
#define CPPUNIT_TEST_EXCEPTION( testMethod, ExceptionType )              \
    CPPUNIT_TEST_ADD( (new CPPUNIT_NS(TestCaller)<ThisTestFixtureType,   \
                                                ExceptionType>(          \
                               namer.getTestNameFor( #testMethod ),      \
                               &ThisTestFixtureType::testMethod,         \
                               factory.makeFixture() ) ) )

/*! \brief Adds a test case which is excepted to fail.
 *
 * The added test case expect an assertion to fail. You usually used that type
 * of test case when testing custom assertion macros.
 *
 * \code
 * CPPUNIT_TEST_FAIL( testAssertFalseFail );
 * 
 * void testAssertFalseFail()
 * {
 *   CPPUNIT_ASSERT( false );
 * }
 * \endcode
 * \see CreatingNewAssertions.
 */
#define CPPUNIT_TEST_FAIL( testMethod ) \
              CPPUNIT_TEST_EXCEPTION( testMethod, CPPUNIT_NS(Exception) )

/*! \brief Adds a custom test case.
 *
 * Use this to add a test case that is returned by a given method to the fixture
 * suite. The specified method must have the following signature:
 * \code
 * static CppUnit::Test *makeCustomTest( const ThisTestFixtureFactory &factory,
 *                                       const CppUnit::TestNamer &namer );
 * \endcode
 *
 * \c ThisTestFixtureFactory is a class declared by CPPUNIT_TEST_SUITE(). It has a method
 * \c makeFixture() which returns a pointer on a new fixture of the type passed to
 * CPPUNIT_TEST_SUITE().
 *
 * Here is an example that add a custom test:
 *
 * \code
 * #include <cppunit/extensions/HelperMacros.h>
 *
 * class MyTest : public CppUnit::TestFixture {
 *   CPPUNIT_TEST_SUITE( MyTest );
 *   CPPUNIT_TEST_CUSTOM( makeTimeOutTest1 );
 *   CPPUNIT_TEST_SUITE_END();
 * public:
 *   static CppUnit::Test *makeTimeOutTest1( const ThisTestFixtureFactory &factory,
 *                                           const CppUnit::TestNamer &namer )
 *   {
 *     return new TimeOutTestCaller( namer.getTestNameFor( "test1" ),
 *                                   &MyTest::test1,
 *                                   factory.makeFixture(),
 *                                   5.0 );
 *   }
 *
 *   void test1()
 *   {
 *     // Do some test that may never end...
 *   }
 * };
 * \endcode
 */
#define CPPUNIT_TEST_CUSTOM( testMakerMethod ) \
      builder.addTest( testMakerMethod( factory, namer ) )

/*! \brief Adds some custom test cases.
 *
 * Use this to add many custom test cases to the fixture suite. The specified method 
 * must have the following signature:
 * \code
 * static void addCustomTests( CppUnit::TestSuite *suite,
 *                             const ThisTestFixtureFactory &factory,
 *                             const CppUnit::TestNamer &namer );
 * \endcode
 *
 * Here is an example that add two custom tests:
 *
 * \code
 * #include <cppunit/extensions/HelperMacros.h>
 *
 * class MyTest : public CppUnit::TestFixture {
 *   CPPUNIT_TEST_SUITE( MyTest );
 *   CPPUNIT_TEST_CUSTOMS( addTimeOutTests );
 *   CPPUNIT_TEST_SUITE_END();
 * public:
 *   static void addTimeOutTests( CppUnit::TestSuite *suite,                           \
 *                                const ThisTestFixtureFactory &factory,
 *                                const CppUnit::TestNamer &namer )
 *   {
 *     suite->addTest( new TimeOutTestCaller( namer.getTestNameFor( "test1" ) ),
 *                                   &MyTest::test1,
 *                                   factory.makeFixture(),
 *                                   5.0 );
 *     suite->addTest( new TimeOutTestCaller( namer.getTestNameFor( "test2" ) ),
 *                                   &MyTest::test2,
 *                                   factory.makeFixture(),
 *                                   5.0 );
 *   }
 *
 *   void test1()
 *   {
 *     // Do some test that may never end...
 *   }
 *
 *   void test2()
 *   {
 *     // Do some test that may never end...
 *   }
 * };
 * \endcode
 */
#define CPPUNIT_TEST_CUSTOMS( testAdderMethod ) \
      testAdderMethod( suite, factory, namer )


/*! \brief End declaration of the test suite.
 *
 * After this macro, member access is set to "private".
 *
 * \see  CPPUNIT_TEST_SUITE.
 * \see  CPPUNIT_TEST_SUITE_REGISTRATION.
 */
#define CPPUNIT_TEST_SUITE_END()                                                    \
      builder.takeSuite();                                                          \
    }                                                                               \
    static CPPUNIT_NS(TestSuite) *suite()                                              \
    {                                                                               \
      const CPPUNIT_NS(TestNamer) &namer = __getTestNamer();                           \
      CPPUNIT_NS(TestSuiteBuilder)<ThisTestFixtureType> builder( namer );            \
      __ThisTestFixtureFactory factory;                                             \
      ThisTestFixtureType::__registerTests( builder.suite(), &factory, namer );   \
      return builder.takeSuite();                                                   \
    }                                                                               \
  private: /* dummy typedef so that the macro can still end with ';'*/              \
    typedef __ThisTestFixtureFactory __CppUnitDummyTypedefTestFixture

/** @}
 */


/*! Adds the specified fixture suite to the unnamed registry.
 * \ingroup CreatingTestSuite
 *
 * This macro declares a static variable whose construction
 * causes a test suite factory to be inserted in a global registry
 * of such factories.  The registry is available by calling
 * the static function CppUnit::TestFactoryRegistry::getRegistry().
 * 
 * \param ATestFixtureType Type of the test case class.
 * \warning This macro should be used only once per line of code (the line
 *          number is used to name a hidden static variable).
 * \see CPPUNIT_TEST_SUITE_NAMED_REGISTRATION
 * \see CPPUNIT_REGISTRY_ADD_TO_DEFAULT
 * \see CPPUNIT_REGISTRY_ADD
 * \see CPPUNIT_TEST_SUITE, CppUnit::AutoRegisterSuite, 
 *      CppUnit::TestFactoryRegistry.
 */
#define CPPUNIT_TEST_SUITE_REGISTRATION( ATestFixtureType )      \
  static CPPUNIT_NS(AutoRegisterSuite)< ATestFixtureType >       \
             CPPUNIT_MAKE_UNIQUE_NAME(__autoRegisterSuite )


/** Adds the specified fixture suite to the specified registry suite.
 * \ingroup CreatingTestSuite
 *
 * This macro declares a static variable whose construction
 * causes a test suite factory to be inserted in the global registry
 * suite of the specified name. The registry is available by calling
 * the static function CppUnit::TestFactoryRegistry::getRegistry().
 * 
 * For the suite name, use a string returned by a static function rather
 * than a hardcoded string. That way, you can know what are the name of
 * named registry and you don't risk mistyping the registry name.
 *
 * \code
 * // MySuites.h
 * namespace MySuites {
 *   std::string math() { 
 *     return "Math";
 *   }
 * }
 *
 * // ComplexNumberTest.cpp
 * #include "MySuites.h"
 * 
 * CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( ComplexNumberTest, MySuites::math() );
 * \endcode
 *
 * \param ATestFixtureType Type of the test case class.
 * \param suiteName Name of the global registry suite the test suite is 
 *                  registered into.
 * \warning This macro should be used only once per line of code (the line
 *          number is used to name a hidden static variable).
 * \see CPPUNIT_TEST_SUITE_REGISTRATION
 * \see CPPUNIT_REGISTRY_ADD_TO_DEFAULT
 * \see CPPUNIT_REGISTRY_ADD
 * \see CPPUNIT_TEST_SUITE, CppUnit::AutoRegisterSuite, 
 *      CppUnit::TestFactoryRegistry..
 */
#define CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( ATestFixtureType, suiteName ) \
  static CPPUNIT_NS(AutoRegisterSuite)< ATestFixtureType >                   \
             CPPUNIT_MAKE_UNIQUE_NAME(__autoRegisterSuite )(suiteName)

/*! Adds that the specified registry suite to another registry suite.
 * \ingroup CreatingTestSuite
 *
 * Use this macros to automatically create test registry suite hierarchy. For example,
 * if you want to create the following hierarchy:
 * - Math
 *   - IntegerMath
 *   - FloatMath
 *     - FastFloat
 *     - StandardFloat
 * 
 * You can do this automatically with:
 * \code
 * CPPUNIT_REGISTRY_ADD( "FastFloat", "FloatMath" );
 * CPPUNIT_REGISTRY_ADD( "IntegerMath", "Math" );
 * CPPUNIT_REGISTRY_ADD( "FloatMath", "Math" );
 * CPPUNIT_REGISTRY_ADD( "StandardFloat", "FloatMath" );
 * \endcode
 *
 * There is no specific order of declaration. Think of it as declaring links.
 *
 * You register the test in each suite using CPPUNIT_TEST_SUITE_NAMED_REGISTRATION.
 *
 * \param which Name of the registry suite to add to the registry suite named \a to.
 * \param to Name of the registry suite \a which is added to.
 * \see CPPUNIT_REGISTRY_ADD_TO_DEFAULT, CPPUNIT_TEST_SUITE_NAMED_REGISTRATION.
 */
#define CPPUNIT_REGISTRY_ADD( which, to )                                     \
  static CPPUNIT_NS(AutoRegisterRegistry)                                     \
             CPPUNIT_MAKE_UNIQUE_NAME( __autoRegisterRegistry )( which, to )

/*! Adds that the specified registry suite to the default registry suite.
 * \ingroup CreatingTestSuite
 *
 * This macro is just like CPPUNIT_REGISTRY_ADD except the specified registry
 * suite is added to the default suite (root suite).
 *
 * \param which Name of the registry suite to add to the default registry suite.
 * \see CPPUNIT_REGISTRY_ADD.
 */
#define CPPUNIT_REGISTRY_ADD_TO_DEFAULT( which )                         \
  static CPPUNIT_NS(AutoRegisterRegistry)                                \
             CPPUNIT_MAKE_UNIQUE_NAME( __autoRegisterRegistry )( which )

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
