#include <cppunit/Asserter.h>
#include <cppunit/Message.h>
#include <cppunit/NotEqualException.h>


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

/* @@fixme Need to take NotEqualException down before including that change.
void 
failNotEqual( std::string expected, 
              std::string actual, 
              const SourceLine &sourceLine,
              const Message &additionalMessage )
{
  Message message( "equality assertion failed",
                   "Expected: " + expected,
                   "Actual  : " + actual );
  message.addDetail( additionalMessage );
  fail( message, sourceLine );
}
*/

void 
failNotEqual( std::string expected, 
              std::string actual, 
              const SourceLine &sourceLine,
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
                const SourceLine &sourceLine,
                std::string additionalMessage )
{
  if ( shouldFail )
    failNotEqual( expected, actual, sourceLine, additionalMessage );
}


} // namespace Asserter
} // namespace CppUnit
