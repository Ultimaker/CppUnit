#include <cppunit/Portability.h>

#if defined(CPPUNIT_HAVE_UNIX_SHL_LOADER)
#include <cppunit/plugin/DynamicLibraryManager.h>

#include <dl.h>
#include <unistd.h>


CPPUNIT_NS_BEGIN


DynamicLibraryManager::LibraryHandle 
DynamicLibraryManager::doLoadLibrary( const std::string &libraryName )
{
   return ::shl_load(libraryName.c_str(), BIND_IMMEDIATE, 0L);
   //return ::dlopen( libraryName.c_str(), RTLD_NOW );   // RTLD_LAZY ?
}


void 
DynamicLibraryManager::doReleaseLibrary()
{
  ::shl_unload( (shl_t)m_libraryHandle);
  //::dlclose( m_libraryHandle);
}


DynamicLibraryManager::Symbol 
DynamicLibraryManager::doFindSymbol( const std::string &symbol )
{
   DynamicLibraryManager::Symbol L_symaddr = 0;
   if ( ::shl_findsym ( (shl_t*)(&m_libraryHandle), symbol.c_str(), TYPE_UNDEFINED, &L_symaddr ) == 0 ) {
      return L_symaddr;
   } else {
      return 0;
   }
   //return ::dlsym ( m_libraryHandle, symbol.c_str() );
}


std::string 
DynamicLibraryManager::getLastErrorDetail() const
{
  return "";
}


CPPUNIT_NS_END


#endif // defined(CPPUNIT_HAVE_UNIX_SHL_LOADER)
