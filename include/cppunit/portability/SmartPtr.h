#ifndef CPPUNIT_PORTABILITY_CPPUNITSMARTPTR_H
#define CPPUNIT_PORTABILITY_CPPUNITSMARTPTR_H

#if HAVE_CXX11
#define CppUnitSmartPtr std::unique_ptr
#else
#define CppUnitSmartPtr std::auto_ptr
#endif

#endif // CPPUNIT_PORTABILITY_CPPUNITDEQUE_H
