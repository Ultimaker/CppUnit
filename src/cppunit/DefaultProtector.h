#ifndef CPPUNIT_DEFAULTPROTECTOR_H
#define CPPUNIT_DEFAULTPROTECTOR_H

#include <cppunit/Protector.h>

CPPUNIT_NS_BEGIN

class DefaultProtector : public Protector
{
public:
  bool protect( const Functor &functor,
                const ProtectorContext &context );
};

CPPUNIT_NS_END

#endif // CPPUNIT_DEFAULTPROTECTOR_H