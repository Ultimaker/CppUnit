#ifndef CPPUNIT_ASSERTER_H
#define CPPUNIT_ASSERTER_H

#include <cppunit/Portability.h>
#include <cppunit/SourceLine.h>
#include <string>

namespace CppUnit
{

namespace Asserter
{

  void fail( std::string message, 
             SourceLine sourceLine = SourceLine() );

  void failIf( bool shouldFail, 
               std::string message, 
               SourceLine sourceLine = SourceLine() );

  void failNotEqual( std::string expected, 
                     std::string actual, 
                     SourceLine sourceLine = SourceLine(),
                     std::string additionalMessage ="" );

  void failNotEqualIf( bool shouldFail,
                       std::string expected, 
                       std::string actual, 
                       SourceLine sourceLine = SourceLine(),
                       std::string additionalMessage ="" );

} // namespace Asserter
} // namespace CppUnit


#endif  // CPPUNIT_ASSERTER_H
