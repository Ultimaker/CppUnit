#include <cppunit/Portability.h>
#include <cppunit/extensions/TypeInfoHelper.h>

#if CPPUNIT_HAVE_RTTI

#include <string>


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

#endif // CPPUNIT_HAVE_RTTI
