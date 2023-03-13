#ifndef DLL_H
#define DLL_H

#pragma once


#include <stdio.h>
//#include <Windows.h>
#include <WTypes.h>

///////////////////////////////////////////////////////////////////////////////
// This function is exported from the dll project
int __stdcall GetCpuSpeed();
BSTR __stdcall GetMyString();


extern "C" {
	struct HumanName {
		CHAR FirstName[100];
		CHAR LastName[100];
		DWORD Tall;
	};
}

#endif //DLL2_H