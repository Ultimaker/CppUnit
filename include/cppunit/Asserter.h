#ifndef CPPUNIT_ASSERTER_H
#define CPPUNIT_ASSERTER_H

#include <cppunit/Portability.h>
#include <cppunit/SourceLine.h>
#include <string>

namespace CppUnit
{

namespace Asserter
{

  void CPPUNIT_API fail( std::string message, 
                         SourceLine sourceLine = SourceLine() );

  void CPPUNIT_API failIf( bool shouldFail, 
                           std::string message, 
                           SourceLine sourceLine = SourceLine() );

  void CPPUNIT_API failNotEqual( std::string expected, 
                                 std::string actual, 
                                 SourceLine sourceLine = SourceLine(),
                                 std::string additionalMessage ="" );

  void CPPUNIT_API failNotEqualIf( bool shouldFail,
                                   std::string expected, 
                                   std::string actual, 
                                   SourceLine sourceLine = SourceLine(),
                                   std::string additionalMessage ="" );

} // namespace Asserter
} // namespace CppUnit


#endif  // CPPUNIT_ASSERTER_H
