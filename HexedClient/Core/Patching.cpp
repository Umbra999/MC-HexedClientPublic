#include "Patching.hpp"
#include "../Wrapper/Logger.hpp"
#include "../minhook/MinHook.h"
#include "GUI.hpp"
#include "../SDK/LaunchWrapper.hpp"

typedef void(*OnUpdate) ();
OnUpdate originalOnUpdate;
OnUpdate patchedOnUpdate;
void OnUpdatePatch()
{
	originalOnUpdate();
}

typedef void(*OnTick) ();
OnTick originalOnTick;
OnTick patchedOnTick;
void OnTickPatch()
{
	originalOnTick();
}

typedef void(*SetSprinting) (jboolean);
SetSprinting originalSetSprinting;
SetSprinting patchedSetSprinting;
void SetSprintingPatch(jboolean state)
{
	originalSetSprinting(state);
}

typedef void(*twglSwapBuffers) (HDC);
twglSwapBuffers originalSwapBuffers;
twglSwapBuffers patchedSwapBuffers;
void SwapBuffersPatch(HDC hDc)
{
	GUI::OnSwapBuffers(hDc);
	originalSwapBuffers(hDc);
}

void Patching::PatchOnUpdate()
{
	Minecraft minecraftInstance = LaunchWrapper::getMinecraft();
	if (minecraftInstance.GetCurrentClass() == NULL) return;

	jmethodID OnUpdateMethod = JNIHelper::env->GetMethodID(minecraftInstance.GetCurrentClass(), "func_99999_d", "()V"); // maybe i should use func_71411_J instead?
	if (OnUpdateMethod == NULL) return;

	patchedOnUpdate = OnUpdate(*(unsigned __int64*)(*(unsigned __int64*)OnUpdateMethod + 0x40));

	MH_CreateHook(patchedOnUpdate, &OnUpdatePatch, (void**)(&originalOnUpdate));

	Logger::LogDebug("OnUpdate Patched");
}

void Patching::PatchOnTick()
{
	Minecraft minecraftInstance = LaunchWrapper::getMinecraft();
	if (minecraftInstance.GetCurrentClass() == NULL) return;

	jmethodID OnTickMethod = JNIHelper::env->GetMethodID(minecraftInstance.GetCurrentClass(), "func_71407_l", "()V");
	if (OnTickMethod == NULL) return;

	patchedOnTick = OnTick(*(unsigned __int64*)(*(unsigned __int64*)OnTickMethod + 0x40));

	MH_CreateHook(patchedOnTick, &OnTickPatch, (void**)(&originalOnTick));

	Logger::LogDebug("OnTick Patched");
}

void Patching::PatchSetSprinting()
{
	Minecraft minecraftInstance = LaunchWrapper::getMinecraft();
	if (minecraftInstance.GetCurrentClass() == NULL) return;

	LocalPlayer localPlayerInstance = LaunchWrapper::getMinecraft().getLocalPlayer();
	if (localPlayerInstance.GetCurrentClass() == NULL) return;

	jmethodID SetSprintingMethod = JNIHelper::env->GetMethodID(localPlayerInstance.GetCurrentClass(), "func_70031_b", "(Z)V");
	if (SetSprintingMethod == NULL) return;

	patchedSetSprinting = SetSprinting(*(unsigned __int64*)(*(unsigned __int64*)SetSprintingMethod + 0x40));

	MH_CreateHook(patchedSetSprinting, &SetSprintingPatch, (void**)(&originalSetSprinting));

	Logger::LogDebug("SetSprinting Patched");
}

void Patching::PatchSwapBuffers()
{
	patchedSwapBuffers = (twglSwapBuffers)GetProcAddress(GetModuleHandleA("opengl32.dll"), "wglSwapBuffers");
	MH_CreateHook(patchedSwapBuffers, &SwapBuffersPatch, (LPVOID*)&originalSwapBuffers);
	Logger::Log("Swap Buffer Patched");
}

void Patching::ApplyPatches()
{
	MH_Initialize();

	PatchSwapBuffers();
	PatchOnUpdate();
	PatchOnTick();
	PatchSetSprinting();

	MH_EnableHook(MH_ALL_HOOKS);
}

void Patching::UnapplyPatches()
{
	MH_Uninitialize();

	MH_DisableHook(MH_ALL_HOOKS);
}