#include <Windows.h>
#include "Core/Core.h"
#include "Utils/CrashLog/CrashLog.h"

DWORD WINAPI MainThread(LPVOID lpParam)
{
	U::Core.Load();
	U::Core.Loop();
	U::Core.Unload();

	FreeLibraryAndExitThread(static_cast<HMODULE>(lpParam), EXIT_SUCCESS);
}


BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		AddVectoredExceptionHandler(1, CrashLog::ExceptionFilter);

		if (const auto hMainThread = CreateThread(nullptr, 0, MainThread, hinstDLL, 0, nullptr))
			CloseHandle(hMainThread);
	}

	return TRUE;
}