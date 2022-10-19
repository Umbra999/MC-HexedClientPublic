#include "Minecraft.hpp"

Minecraft::Minecraft(jobject obj)
{
	MinecraftObj = obj;
}

jobject Minecraft::GetCurrentObject()
{
	return MinecraftObj;
}

jclass Minecraft::GetCurrentClass()
{
	if (MinecraftObj == NULL) return NULL;
	if (CurrentClass == NULL) CurrentClass = JNIHelper::env->GetObjectClass(MinecraftObj);

	return CurrentClass;
}

LocalPlayer Minecraft::getLocalPlayer()
{
	if (GetCurrentClass() == NULL) return NULL;
	if (LocalPlayerInstance.GetCurrentClass() == NULL)
	{
		jfieldID getLocalPlayer = JNIHelper::env->GetFieldID(GetCurrentClass(), "field_71439_g", "Lnet/minecraft/client/entity/EntityPlayerSP;");
		if (getLocalPlayer == NULL) return NULL;
		jobject Instance = JNIHelper::env->GetObjectField(MinecraftObj, getLocalPlayer);
		LocalPlayerInstance = LocalPlayer(Instance);
	}

	return LocalPlayerInstance;
}

World Minecraft::getWorld()
{
	if (GetCurrentClass() == NULL) return NULL;
	if (WorldInstance.GetCurrentClass() == NULL)
	{
		jfieldID getWorld = JNIHelper::env->GetFieldID(GetCurrentClass(), "field_71441_e", "Lnet/minecraft/client/multiplayer/WorldClient;");
		if (getWorld == NULL) return NULL;
		jobject Instance = JNIHelper::env->GetObjectField(MinecraftObj, getWorld);
		WorldInstance = World(Instance);
	}

	return WorldInstance;
}

NetworkManager Minecraft::getNetworkManager()
{
	if (GetCurrentClass() == NULL) return NULL;
	if (NetworkManagerInstance.GetCurrentClass() == NULL)
	{
		jfieldID getNetworkManager = JNIHelper::env->GetFieldID(GetCurrentClass(), "field_71453_ak", "Lnet/minecraft/client/network/NetworkManager;");
		if (getNetworkManager == NULL) return NULL;
		jobject Instance = JNIHelper::env->GetObjectField(MinecraftObj, getNetworkManager);
		NetworkManagerInstance = NetworkManager(Instance);
	}

	return NetworkManagerInstance;
}

void Minecraft::SetLeftClickDelay(int count)
{
	if (GetCurrentClass() == NULL) return;
	if (leftClickFieldID == NULL)
	{
		leftClickFieldID = JNIHelper::env->GetFieldID(GetCurrentClass(), "field_71429_W", "I");
		if (leftClickFieldID == NULL) return;
	}

	JNIHelper::env->SetIntField(MinecraftObj, leftClickFieldID, count);
}

void Minecraft::SetRightClickDelay(int count)
{
	if (GetCurrentClass() == NULL) return;
	if (rightClickFieldID == NULL)
	{	
		rightClickFieldID = JNIHelper::env->GetFieldID(GetCurrentClass(), "field_71467_ac", "I");
		if (rightClickFieldID == NULL) return;
	}

	JNIHelper::env->SetIntField(MinecraftObj, rightClickFieldID, count);
}

void Minecraft::LeftClick()
{
	if (GetCurrentClass() == NULL) return;
	if (leftClickMethodID == NULL)
	{
		leftClickMethodID = JNIHelper::env->GetMethodID(GetCurrentClass(), "func_147116_af", "()V");
		if (leftClickMethodID == NULL) return;
	}

	JNIHelper::env->CallVoidMethod(MinecraftObj, leftClickMethodID);
}

void Minecraft::RightClick()
{
	if (GetCurrentClass() == NULL) return;
	if (rightClickMethodID == NULL)
	{
		rightClickMethodID = JNIHelper::env->GetMethodID(GetCurrentClass(), "func_147121_ag", "()V");
		if (rightClickMethodID == NULL) return;
	}

	JNIHelper::env->CallVoidMethod(MinecraftObj, rightClickMethodID);
}

bool Minecraft::InGameHasFocus()
{
	if (GetCurrentClass() == NULL) return NULL;
	if (gameHasFocusFieldID == NULL)
	{
		gameHasFocusFieldID = JNIHelper::env->GetFieldID(GetCurrentClass(), "field_71415_G", "Z");
		if (gameHasFocusFieldID == NULL) return NULL;
	}

	if (hasIngameFocus == NULL) hasIngameFocus = JNIHelper::env->GetBooleanField(MinecraftObj, gameHasFocusFieldID);

	return hasIngameFocus;
}

int Minecraft::GetFPS()
{
	if (GetCurrentClass() == NULL) return NULL;
	if (fpsCounterFieldID == NULL)
	{
		fpsCounterFieldID = JNIHelper::env->GetStaticFieldID(GetCurrentClass(), "field_71470_ab", "I");
		if (fpsCounterFieldID == NULL) return NULL;
	}

	if (fpsCounter == NULL) fpsCounter = JNIHelper::env->GetStaticIntField(GetCurrentClass(), fpsCounterFieldID);

	return fpsCounter;
}

void Minecraft::SetFPS(jint FPS)
{
	if (GetCurrentClass() == NULL) return;
	if (fpsCounterFieldID == NULL)
	{
		fpsCounterFieldID = JNIHelper::env->GetStaticFieldID(GetCurrentClass(), "field_71470_ab", "I");
		if (fpsCounterFieldID == NULL) return;
	}

	JNIHelper::env->SetStaticIntField(GetCurrentClass(), fpsCounterFieldID, FPS);
}