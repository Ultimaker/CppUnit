#ifndef CPPUNIT_PLUGIN_PARAMETERS
#define CPPUNIT_PLUGIN_PARAMETERS

#include <cppunit/Portability.h>

#if !defined(CPPUNIT_NO_TESTPLUGIN)

#include <cppunit/portability/CppUnitDeque.h>
#include <string>

CPPUNIT_NS_BEGIN


typedef CppUnitDeque<std::string> Parameters;


CPPUNIT_NS_END

#endif // !defined(CPPUNIT_NO_TESTPLUGIN)


#endif // CPPUNIT_PLUGIN_PARAMETERS
