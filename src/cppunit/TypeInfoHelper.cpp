#include <cppunit/Portability.h>

#if CPPUNIT_USE_TYPEINFO_NAME

#include <string>
#include <cppunit/extensions/TypeInfoHelper.h>


namespace CppUnit {

std::string 
TypeInfoHelper::getClassName( const std::type_info &info )
{
  static std::string classPrefix( "class " );
  std::string name( info.name() );

  if ( name.substr( 0, classPrefix.length() ) == classPrefix )
    return name.substr( classPrefix.length() );
  return name;
}


} //  namespace CppUnit

#endif 
