#include <cppunit/Portability.h>
#include <cppunit/extensions/TypeInfoHelper.h>

#if CPPUNIT_HAVE_RTTI

#include <string>


CPPUNIT_NS_BEGIN


std::string 
TypeInfoHelper::getClassName( const std::type_info &info )
{
  static std::string classPrefix( "class " );
  std::string name( info.name() );

  // Work around gcc 3.0 bug: strip number before type name.
  int firstNotDigitIndex = 0;
  while ( firstNotDigitIndex < name.length()  &&
          name[firstNotDigitIndex] >= '0'  &&
          name[firstNotDigitIndex] <= '9' )
    ++firstNotDigitIndex;
  name = name.substr( firstNotDigitIndex );

  if ( name.substr( 0, classPrefix.length() ) == classPrefix )
    return name.substr( classPrefix.length() );
  return name;
}


CPPUNIT_NS_END

#endif // CPPUNIT_HAVE_RTTI
