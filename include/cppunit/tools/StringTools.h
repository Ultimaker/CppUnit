#ifndef CPPUNIT_TOOLS_STRINGTOOLS_H
#define CPPUNIT_TOOLS_STRINGTOOLS_H

#include <cppunit/Portability.h>
#include <string>
#include <vector>


namespace CppUnit
{

/*! \brief Tool functions to manipulate string.
 */
namespace StringTools
{

  typedef std::vector<std::string> Strings;

  std::string CPPUNIT_API toString( int value );

  std::string CPPUNIT_API toString( double value );

  Strings CPPUNIT_API split( const std::string &text, 
                             char separator );

  std::string CPPUNIT_API wrap( const std::string &text,
                                int wrapColumn = 79 );

} // namespace StringTools


} //  namespace CppUnit


#endif  // CPPUNIT_TOOLS_STRINGTOOLS_H
