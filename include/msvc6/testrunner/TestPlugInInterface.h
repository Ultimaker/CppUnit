#ifndef CPPUNIT_TESTPLUGINRUNNER_TESTPLUGININTERFACE_H
#define CPPUNIT_TESTPLUGINRUNNER_TESTPLUGININTERFACE_H

#ifndef NOMINMAX
# define NOMINMAX
#endif
#include <windef.h>   // for WINAPI


#include <cppunit/Test.h>

class TestPlugInInterface
{
public:
  virtual ~TestPlugInInterface() {}

  virtual CppUnit::Test *makeTest() =0;
};

typedef TestPlugInInterface* (WINAPI *GetTestPlugInInterfaceFunction)(void);



#endif // CPPUNIT_TESTPLUGINRUNNER_TESTPLUGININTERFACE_H
