#ifndef CPPUNIT_PORTABILITY_CPPUNITMAP_H
#define CPPUNIT_PORTABILITY_CPPUNITMAP_H

// The technic used is similar to the wrapper of STLPort.
 
#include <cppunit/Portability.h>
#include <functional>
#include <map>


#if CPPUNIT_STD_NEED_ALLOCATOR

CPPUNIT_NS_BEGIN

template<class Key, class T>
class CppUnitMap : public std::map<Key
                                  ,T
                                  ,std::less<Key>
                                  ,CPPUNIT_STD_ALLOCATOR>
{
public:
};

CPPUNIT_NS_END

#else // CPPUNIT_STD_NEED_ALLOCATOR

#define CppUnitMap std::map

#endif

#endif // CPPUNIT_PORTABILITY_CPPUNITMAP_H