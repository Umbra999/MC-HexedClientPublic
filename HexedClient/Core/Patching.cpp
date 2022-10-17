#include "Patching.hpp"
#include "../Wrapper/Logger.hpp"
#include "../minhook/MinHook.h"
#include "GUI.hpp"

typedef void(*OnUpdate) ();
OnUpdate originalOnUpdate;
OnUpdate patchedOnUpdate;
void OnUpdatePatch()
{
	//handler.OnUpdatePatch();
	originalOnUpdate();
}

typedef void(*SetSprinting) (bool);
SetSprinting originalSetSprinting;
SetSprinting patchedSetSprinting;
void SetSprintingPatch(bool sprinting)
{
	//handler.OnUpdatePatch();
	originalSetSprinting(true); // testing
}

typedef void(*twglSwapBuffers) (HDC);
twglSwapBuffers originalSwapBuffers;
void* patchedSwapBuffers;
void SwapBuffersPatch(HDC hDc)
{
	/*Logger::Log("Swapped Buffers");*/
	GUI::OnSwapBuffers(hDc);
	originalSwapBuffers(hDc);
}

void Patching::PatchOnUpdate()
{
	//Minecraft minecraftInstance = LaunchWrapper::getMinecraft();
	//if (minecraftInstance.MinecraftObj == NULL) return;

	//jmethodID OnUpdateMethod = JNIHelper::env->GetMethodID(minecraftInstance.GetClass(), "func_71411_J", "()V"); // maybe i should use func_99999_d instead?
	//if (OnUpdateMethod == NULL) return;

	//patchedOnUpdate = OnUpdate(*(unsigned __int64*)(*(unsigned __int64*)OnUpdateMethod + 0x40));

	//MH_CreateHook(patchedOnUpdate, &OnUpdatePatch, (void**)(&originalOnUpdate));

	//Logger::LogDebug("OnUpdate Patched");
}

void Patching::PatchSetSprinting()
{
	/*Minecraft minecraftInstance = LaunchWrapper::getMinecraft();
	if (minecraftInstance.MinecraftObj == NULL) return;

	LocalPlayer localPlayerInstance = minecraftInstance.getLocalPlayer();
	if (localPlayerInstance.LocalPlayerObj == NULL) return;

	jclass LocalPlayerClass = localPlayerInstance.GetClass();
	if (LocalPlayerClass == NULL) return;

	jmethodID SetSprintingMethod = JNIHelper::env->GetMethodID(LocalPlayerClass, "func_70031_b", "(Z)V");
	if (SetSprintingMethod == NULL) return;

	patchedSetSprinting = SetSprinting(*(unsigned __int64*)(*(unsigned __int64*)SetSprintingMethod + 0x40));

	MH_CreateHook(patchedSetSprinting, &OnUpdatePatch, (void**)(&originalSetSprinting));

	Logger::LogDebug("SetSprinting Patched");*/
}

void Patching::PatchSwapBuffers()
{
	patchedSwapBuffers = (void*)GetProcAddress(GetModuleHandle("opengl32.dll"), "wglSwapBuffers");
	MH_CreateHook(patchedSwapBuffers, &SwapBuffersPatch, (LPVOID*)&originalSwapBuffers);
	Logger::Log("Swap Buffer Patched");
}

void Patching::ApplyPatches()
{
	MH_Initialize();

	PatchSwapBuffers();
	PatchOnUpdate();
	PatchSetSprinting();

	MH_EnableHook(MH_ALL_HOOKS);
}

void Patching::UnapplyPatches()
{
	MH_Uninitialize();

	MH_DisableHook(MH_ALL_HOOKS);
}