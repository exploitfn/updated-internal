#define _CRT_SECURE_NO_WARNINGS
#include "UnrealSDKClass.h"
#include "Afort.hpp"
#include "Actor.hpp"
#include "hook.h"
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		Main();
	}
	return TRUE;
}