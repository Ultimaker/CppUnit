#ifndef CPPUNIT_PLUGIN_PARAMETERS
#define CPPUNIT_PLUGIN_PARAMETERS

#include <cppunit/Portability.h>

#if !defined(CPPUNIT_NO_TESTPLUGIN)

#include <cppunit/portability/CppUnitDeque.h>
#include <string>

CPPUNIT_NS_BEGIN


class CPPUNIT_API PlugInParameters
{
public:
  PlugInParameters( const std::string &commandLine = "" );

  virtual ~PlugInParameters();

  std::string getCommandLine() const;

private:
  std::string m_commandLine;
};


CPPUNIT_NS_END

#endif // !defined(CPPUNIT_NO_TESTPLUGIN)


#endif // CPPUNIT_PLUGIN_PARAMETERS
