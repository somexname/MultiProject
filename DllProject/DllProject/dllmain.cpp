// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "dllmain.h"
#include <OleAuto.h>

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// GetCycleCount - private function of DLL2.cpp.  
// The static keyword ensures that this function name is not visible outside DLL2.cpp.
static inline unsigned __int64 GetCycleCount()
{
    unsigned int timehi, timelo;

    // Use the assembly instruction rdtsc, which gets the current -
    // cycle count (since the process started) and puts it in edx:eax.
    __asm
    {
        rdtsc
        mov timehi, edx;
        mov timelo, eax;
    }

    return ((unsigned __int64)timehi << 32) + (unsigned __int64)timelo;
}

///////////////////////////////////////////////////////////////////////////////
// Exported functions
///////////////////////////////////////////////////////////////////////////////

// GetCpuSpeed - returns CPU speed in MHz;  for example, ~2193 will be 
//               returned for a 2.2 GHz CPU.
int __stdcall GetCpuSpeed()
{
    const unsigned __int64 ui64StartCycle = GetCycleCount();
    Sleep(1000);
    return static_cast<int>((GetCycleCount() - ui64StartCycle) / 1000000);
}

BSTR __stdcall GetMyString()
{
    char s[] = "This is my string";

    return SysAllocStringByteLen(s, lstrlen(s));
}

__declspec(dllexport) void __cdecl DisplayHelloFromDLL()
{
    printf("Hello from DLL !\n");
}

__declspec(dllexport) void __cdecl DisplayHello(HumanName* name)
{
    printf("%s,%s\r\n", name->FirstName, name->LastName);
    strcpy_s(name->FirstName, 8, "¹·Êº");
    strcpy_s(name->LastName, 8, "¼¸°Ñ");
    name->Tall = 1000;
}

