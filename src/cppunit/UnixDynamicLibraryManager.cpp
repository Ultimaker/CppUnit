#include <cppunit/Portability.h>

#if defined(CPPUNIT_HAVE_UNIX_DLL_LOADER)
#include <cppunit/plugin/DynamicLibraryManager.h>

#include <dlfcn.h>
#include <unistd.h>


namespace CppUnit
{


DynamicLibraryManager::LibraryHandle 
DynamicLibraryManager::doLoadLibrary( const std::string &libraryName )
{
  return ::dlopen( libraryName.c_str(), DLOPEN_MODE );
}


void 
DynamicLibraryManager::doReleaseLibrary()
{
  ::dlclose( m_libraryHandle);
}


DynamicLibraryManager::Symbol 
DynamicLibraryManager::doFindSymbol( const std::string &symbol )
{
  return ::dlsym ( m_libraryHandle, symbol.c_str() );
}


} //  namespace CppUnit


#endif // defined(CPPUNIT_HAVE_UNIX_DLL_LOADER)
