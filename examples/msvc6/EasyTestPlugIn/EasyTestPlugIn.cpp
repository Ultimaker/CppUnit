// EasyTestPlugIn.cpp : Defines the entry point for the DLL application.
//

#include <msvc6/testrunner/TestPlugInInterface.h>

CPPUNIT_TESTPLUGIN_IMPL( "Easy Test Plug-in Suite" );

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

