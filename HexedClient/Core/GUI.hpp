#pragma once
#include <Windows.h>

class GUI
{
private:
	static LRESULT __stdcall patchedWNDPROC(HWND, UINT, WPARAM, LPARAM);
	static void Create();

public:
	static bool IsInitialized;
	static bool Enabled;
	static void Delete();
	static void Render();
	static void OnSwapBuffers(HDC);
};
