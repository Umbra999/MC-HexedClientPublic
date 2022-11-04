#include "Wrapper/Utils.hpp"
#include "Core/Patching.hpp"
#include "Core/Settings.hpp"
#include "Core/GUI.hpp"
#include "SDK/JNIHelper.hpp"
#include "Wrapper/Logger.hpp"
#include "SDK/LaunchWrapper.hpp"
#include "Core/Handler.hpp"

HMODULE HModule;

void Initialize()
{
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
        if (res == JNI_EDETACHED)
        {
            res = vm->AttachCurrentThread((void**)&JNIHelper::env, nullptr);
            Logger::LogDebug("Attached JVM to current Thread");
        }

        if (res == JNI_OK)
        {
            std::string Mappings = LaunchWrapper::IsForge() ? "FORGE" : "VANILLA";
            Logger::Log("Minecraft running on: " + Mappings);

            Logger::Log("Waiting for World to Initialize...");
            while (LaunchWrapper::getMinecraft().GetCurrentClass() == NULL || LaunchWrapper::getMinecraft().getWorld().GetCurrentClass() == NULL)
            {
                Sleep(1);
            }

            Patching::ApplyPatches();
            while (!Settings::ShouldUninject)
            {
                Handler::OnTick(); // for now 
                Sleep(50);
            }
        }
    }

    ShowWindow(GetConsoleWindow(), SW_HIDE);
    FreeConsole();
    Patching::UnapplyPatches();
    GUI::Delete();
    vm->DetachCurrentThread();
    FreeLibraryAndExitThread(HModule, 0);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
            HModule = hModule;
            DisableThreadLibraryCalls(HModule);
            const auto thread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Initialize, NULL, NULL, NULL);
            if (thread) CloseHandle(thread);
            break;
    }
    return TRUE;
}

