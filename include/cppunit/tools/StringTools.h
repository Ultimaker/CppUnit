#ifndef CPPUNIT_TOOLS_STRINGTOOLS_H
#define CPPUNIT_TOOLS_STRINGTOOLS_H

#include <cppunit/Portability.h>
#include <string>


namespace CppUnit
{

/*! \brief Tool functions to manipulate string.
 */
namespace StringTools
{

  std::string CPPUNIT_API toString( int value );

  std::string CPPUNIT_API toString( double value );


} // namespace StringTools


} //  namespace CppUnit


#endif  // CPPUNIT_TOOLS_STRINGTOOLS_H
