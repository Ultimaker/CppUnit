#include <cppunit/plugin/DynamicLibraryManagerException.h>

#if !defined(CPPUNIT_NO_TESTPLUGIN)

namespace CppUnit
{


DynamicLibraryManagerException::DynamicLibraryManagerException( 
                                         const std::string &libraryName )
    : m_cause( loadingFailed )
    , std::runtime_error( "Failed to load dynamic library: " + libraryName )
{
}


DynamicLibraryManagerException::DynamicLibraryManagerException( 
                                const std::string &libraryName,
                                const std::string &symbol )
    : m_cause( symbolNotFound )
    , std::runtime_error( "Symbol [" + symbol + "] not found in dynamic libary:" +
                          libraryName )
{
}


DynamicLibraryManagerException::Cause 
DynamicLibraryManagerException::getCause() const
{
  return m_cause;
}


} //  namespace CppUnit


#endif // !defined(CPPUNIT_NO_TESTPLUGIN)
