#include <cppunit/Asserter.h>
#include <cppunit/Exception.h>
#include <cppunit/Message.h>


namespace CppUnit
{


namespace Asserter
{

void 
fail( std::string message, 
      const SourceLine &sourceLine )
{
  fail( Message( "assertion failed", message ), sourceLine );
}


void 
fail( const Message &message, 
      const SourceLine &sourceLine )
{
  throw Exception( message, sourceLine );
}


void 
failIf( bool shouldFail, 
        const Message &message, 
        const SourceLine &sourceLine )
{
  if ( shouldFail )
    fail( message, sourceLine );
}


void 
failIf( bool shouldFail, 
        std::string message, 
        const SourceLine &sourceLine )
{
  failIf( shouldFail, Message( "assertion failed", message ), sourceLine );
}


std::string 
makeExpected( const std::string &expectedValue )
{
  return "Expected: " + expectedValue;
}


std::string 
makeActual( const std::string &actualValue )
{
  return "Actual  : " + actualValue;
}


Message 
makeNotEqualMessage( const std::string &expectedValue,
                     const std::string &actualValue,
                     const AdditionalMessage &additionalMessage,
                     const std::string &shortDescription )
{
  Message message( shortDescription,
                   makeExpected( expectedValue ),
                   makeActual( actualValue ) );
  message.addDetail( additionalMessage );

  return message;
}


void 
failNotEqual( std::string expected, 
              std::string actual, 
              const SourceLine &sourceLine,
              const AdditionalMessage &additionalMessage,
              std::string shortDescription )
{
  fail( makeNotEqualMessage( expected,
                             actual,
                             additionalMessage,
                             shortDescription ), 
        sourceLine );
}


void 
failNotEqualIf( bool shouldFail,
                std::string expected, 
                std::string actual, 
                const SourceLine &sourceLine,
                const AdditionalMessage &additionalMessage,
                std::string shortDescription )
{
  if ( shouldFail )
    failNotEqual( expected, actual, sourceLine, additionalMessage, shortDescription );
}


} // namespace Asserter
} // namespace CppUnit
