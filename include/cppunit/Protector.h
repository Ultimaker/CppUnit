#ifndef CPPUNIT_PROTECTOR_H
#define CPPUNIT_PROTECTOR_H

#include <cppunit/Portability.h>

CPPUNIT_NS_BEGIN


class Message;
class ProtectorContext;


class CPPUNIT_API Functor
{
public:
  virtual ~Functor();

  virtual bool operator()() const =0;
};


class CPPUNIT_API Protector
{
public:
  virtual ~Protector();
  
  virtual bool protect( const Functor &functor,
                        const ProtectorContext &context ) =0;

protected:
  void reportTestFailure( const Message &message,
                          const ProtectorContext &context,
                          bool isError );
};

CPPUNIT_NS_END


#endif // CPPUNIT_PROTECTOR_H