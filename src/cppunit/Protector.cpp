#include <cppunit/Exception.h>
#include <cppunit/Message.h>
#include <cppunit/Protector.h>
#include <cppunit/TestResult.h>
#include "ProtectorContext.h"

CPPUNIT_NS_BEGIN

Functor::~Functor()
{
}


Protector::~Protector()
{
}


void 
Protector::reportTestFailure( const Message &message,
                              const ProtectorContext &context,
                              bool isError )
{
  Message actualMessage;
  if ( context.m_shortDescription.empty() )
    actualMessage = message;
  else
  {
    actualMessage = Message( context.m_shortDescription, 
                             message.shortDescription() );
    actualMessage.addDetail( message );
  }

  if ( isError )
    context.m_result->addError( context.m_test, new Exception( message ) );
  else
    context.m_result->addFailure( context.m_test, new Exception( message ) );
}


CPPUNIT_NS_END
