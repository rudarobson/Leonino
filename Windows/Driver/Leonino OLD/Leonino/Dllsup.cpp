/*++

Module Name:

    Dllsup.cpp

Abstract:

    This module contains the implementation of the Driver DLL entry point.

Environment:

   Windows User-Mode Driver Framework (WUDF)

--*/

#include "internal.h"
#include "dllsup.tmh"

//
// This GUID must match the DriverCLSID value for the service binary in the INF.
// For more information see http://msdn.microsoft.com/en-us/library/ff560526(VS.85).aspx
// f8e0a016-fbdf-4245-a1a5-85f721821ea3
//
const CLSID CLSID_Driver =
{0xf8e0a016,0xfbdf,0x4245,{0xa1,0xa5,0x85,0xf7,0x21,0x82,0x1e,0xa3}};

HINSTANCE g_hInstance = NULL;

class CMyDriverModule :
    public CAtlDllModuleT< CMyDriverModule >
{
};

CMyDriverModule _AtlModule;

//
// DLL Entry Point
// 

extern "C"
BOOL
WINAPI
DllMain(
    HINSTANCE hInstance,
    DWORD dwReason,
    LPVOID lpReserved
    )
{
    if (dwReason == DLL_PROCESS_ATTACH) {
        WPP_INIT_TRACING(MYDRIVER_TRACING_ID);
        
        g_hInstance = hInstance;
        DisableThreadLibraryCalls(hInstance);

    } else if (dwReason == DLL_PROCESS_DETACH) {
        WPP_CLEANUP();
    }

    return _AtlModule.DllMain(dwReason, lpReserved);
}


//
// Returns a class factory to create an object of the requested type
// 

STDAPI
DllGetClassObject(
    __in REFCLSID rclsid,
    __in REFIID riid,
    __deref_out LPVOID FAR* ppv
    )
{
    return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}


