#include <cppunit/Asserter.h>
#include <cppunit/NotEqualException.h>


namespace CppUnit
{


/*! Asserter creates and throws failure exception.
 *
 * The following example show how to create an assertion that
 * checks if two XML strings are equivalent (extract from
 * XmlUniformiser.cpp of CppUnit test suite):
 *
 * \code
 * // Asserts that two XML strings are equivalent.
 * #define CPPUNITTEST_ASSERT_XML_EQUAL( expected, actual ) \
 *     ::CppUnitTest::checkXmlEqual( expected, actual,      \
 *                                  CPPUNIT_SOURCELINE() )
 * void 
 * checkXmlEqual( std::string expectedXml,
 *                std::string actualXml,
 *                CppUnit::SourceLine sourceLine )
 * {
 *   std::string expected = XmlUniformiser( expectedXml ).stripped();
 *   std::string actual = XmlUniformiser( actualXml ).stripped();
 * 
 *   if ( expected == actual )
 *     return;
 * 
 *   int index = notEqualIndex( expected, actual );
 *   CppUnit::OStringStream message;
 *   message  <<  "differ at index: "  <<  index  << "\n"
 *           <<  "expected: "  <<  expected.substr(index) << "\n"
 *           <<  "but was : "  <<  actual.substr( index );
 *   ::CppUnit::Asserter::failNotEqual( expected,
 *                                      actual,
 *                                      sourceLine,
 *                                      message.str() );
 * }
 *
 *
 * int 
 * notEqualIndex( std::string expectedXml,
 *                std::string actualXml )
 * {
 *   int index = 0;
 *   while ( index < actualXml.length()  &&  
 *           index < expectedXml.length()  &&
 *           actualXml[index] == expectedXml[index] )
 *     ++index;
 * 
 *   return index;
 * }
 * \endcode
 */
namespace Asserter
{


void 
fail( std::string message, 
      SourceLine sourceLine )
{
  throw Exception( message, sourceLine );
}


void 
failIf( bool shouldFail, 
        std::string message, 
        SourceLine location )
{
  if ( shouldFail )
    fail( message, location );
}


void 
failNotEqual( std::string expected, 
              std::string actual, 
              SourceLine sourceLine,
              std::string additionalMessage )
{
  throw NotEqualException( expected, 
                           actual, 
                           sourceLine, 
                           additionalMessage );
}


void 
failNotEqualIf( bool shouldFail,
                std::string expected, 
                std::string actual, 
                SourceLine sourceLine,
                std::string additionalMessage )
{
  if ( shouldFail )
    failNotEqual( expected, actual, sourceLine, additionalMessage );
}


} // namespace Asserter
} // namespace CppUnit
