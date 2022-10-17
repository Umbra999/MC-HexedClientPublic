#include "Wrapper/Utils.hpp"
#include "Core/Patching.hpp"
#include "Core/Settings.hpp"
#include "Wrapper/main_window_finder.hpp"
#include "Core/GUI.hpp"
#include "SDK/JNIHelper.hpp"
#include "Wrapper/Logger.hpp"

HMODULE HModule;

void Initialize()
{
    while (Settings::MainWindow == NULL)
    {
        Settings::MainWindow = main_window_finder_t().find_main_window(GetCurrentProcessId());
        Sleep(1);
    }

    AllocConsole();
    SetConsoleOutputCP(65001);
    freopen_s(reinterpret_cast<FILE**>(stdin), "CONIN$", "r", stdin);
    freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);
    std::string msg = "HEXED | CONSOLE | " + Utils::RandomString(16);
    SetConsoleTitleA(msg.c_str());

    jsize count;
    JavaVM* vm;

    if (JNI_GetCreatedJavaVMs(&vm, 1, &count) == JNI_OK && count > 0)
    {
        jint res = vm->GetEnv((void**)&JNIHelper::env, JNI_VERSION_1_6);
        if (res == JNI_EDETACHED) res = vm->AttachCurrentThread((void**)&JNIHelper::env, nullptr);

        if (res == JNI_OK && JNIHelper::env != nullptr)
        {
            vm->DetachCurrentThread();

            /*while (LaunchWrapper::getMinecraft().MinecraftObj == NULL || LaunchWrapper::getMinecraft().getLocalPlayer().LocalPlayerObj == NULL)
            {
                Sleep(1);
            }*/

            Patching::ApplyPatches();
            while (!Settings::ShouldUninject)
            {
                //Handler::ExternalWork();
                //Handler::OnUpdatePatch(); // for now 
                Sleep(50);
            }
        }
    }

    ShowWindow(GetConsoleWindow(), SW_HIDE);
    FreeConsole();
    Patching::UnapplyPatches();
    GUI::Delete();
    FreeLibraryAndExitThread(HModule, 0);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
            HModule = hModule;
            DisableThreadLibraryCalls(hModule);
            CreateThread(NULL, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(Initialize), NULL, NULL, NULL);
            break;
    }
    return TRUE;
}

