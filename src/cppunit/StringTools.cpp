#include <cppunit/tools/StringTools.h>


namespace CppUnit
{

namespace StringTools
{

  std::string toString( int value )
  {
    OStringStream stream;
    stream << value;
    return stream.str();
  }

  std::string toString( double value )
  {
    OStringStream stream;
    stream << value;
    return stream.str();
  }


} // namespace StringTools


} //  namespace CppUnit

