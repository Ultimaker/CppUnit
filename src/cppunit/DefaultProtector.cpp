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
    // BUG: => should return what is returned. Need to update
    // UT to prove there is a bug. Consequence: runTest() is called
    // even if setUp() failed in a 'sub-protector'.
    functor();
    return true;
//    return functor();
  }
  catch ( Exception &failure )
  {
    reportFailure( context, failure );
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
    reportError( context, message );
  }
  catch ( ... )
  {
    reportError( context,
                 Message( "uncaught exception of unknown type") );
  }
  
  return false;
}


CPPUNIT_NS_END
