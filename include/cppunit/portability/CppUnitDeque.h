#ifndef CPPUNIT_PORTABILITY_CPPUNITDEQUE_H
#define CPPUNIT_PORTABILITY_CPPUNITDEQUE_H

// The technic used is similar to the wrapper of STLPort.
 
#include <cppunit/Portability.h>
#include <deque>


#if CPPUNIT_STD_NEED_ALLOCATOR

CPPUNIT_NS_BEGIN

template<class T>
class CppUnitDeque : public std::deque<T,CPPUNIT_STD_ALLOCATOR>
{
public:
};

CPPUNIT_NS_END

#else // CPPUNIT_STD_NEED_ALLOCATOR

#define CppUnitDeque std::deque

#endif

#endif // CPPUNIT_PORTABILITY_CPPUNITDEQUE_H