#include <cppunit/Exception.h>
#include <cppunit/extensions/TypeInfoHelper.h>
#include "DefaultProtector.h"


CPPUNIT_NS_BEGIN


bool 
DefaultProtector::protect( const Functor &functor,
                           const ProtectorContext &context )
{
  try
  {
    functor();
    return true;
  }
  catch ( Exception &failure )
  {
    reportTestFailure( failure.message(), context, false );
  }
  catch ( std::exception &e )
  {
    std::string shortDescription( "uncaught exception of type " );
#if CPPUNIT_USE_TYPEINFO_NAME
    shortDescription += TypeInfoHelper::getClassName( typeid(e) );
#else
    shortDescription += "std::exception (or derived)."
#endif
    Message message( shortDescription, e.what() );
    reportTestFailure( message, context, true );
  }
  catch ( ... )
  {
    reportTestFailure( Message( "uncaught exception of unknown type"), 
                       context, 
                       true );
  }
  
  return false;
}


CPPUNIT_NS_END
