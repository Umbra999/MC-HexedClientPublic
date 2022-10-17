#include "Minecraft.hpp"

Minecraft::Minecraft(jobject obj)
{
	MinecraftObj = obj;
	JNIHelper::env->DeleteLocalRef(obj);
}

jclass Minecraft::GetClass()
{
	if (MinecraftObj == NULL) return NULL;

	jclass MinecraftClass = JNIHelper::env->GetObjectClass(MinecraftObj);
	if (MinecraftClass == NULL) return NULL;

	return MinecraftClass;
}

LocalPlayer Minecraft::getLocalPlayer()
{
	if (MinecraftObj == NULL) return NULL;

	jclass MinecraftClass = GetClass();
	if (MinecraftClass == NULL) return NULL;

	jfieldID getLocalPlayer = JNIHelper::env->GetFieldID(MinecraftClass, "field_71439_g", "Lnet/minecraft/client/entity/EntityPlayerSP;");
	if (getLocalPlayer == NULL) return NULL;

	jobject Instance = JNIHelper::env->GetObjectField(MinecraftObj, getLocalPlayer);

	return LocalPlayer(Instance);
}

jobject Minecraft::getWorld()
{
	if (MinecraftObj == NULL) return NULL;

	jclass MinecraftClass = GetClass();
	if (MinecraftClass == NULL) return NULL;

	jfieldID getWorld = JNIHelper::env->GetFieldID(MinecraftClass, "field_71441_e", "Lnet/minecraft/client/multiplayer/WorldClient;");
	if (getWorld == NULL) return NULL;

	return JNIHelper::env->GetObjectField(MinecraftObj, getWorld);
}

void Minecraft::SetLeftClickDelay(int count)
{
	if (MinecraftObj == NULL) return;

	jclass MinecraftClass = GetClass();
	if (MinecraftClass == NULL) return;

	jfieldID leftclickfield = JNIHelper::env->GetFieldID(MinecraftClass, "field_71429_W", "I");
	if (leftclickfield == NULL) return;
	if (MinecraftObj == NULL) return;

	JNIHelper::env->SetIntField(MinecraftObj, leftclickfield, count);
}

void Minecraft::SetRightClickDelay(int count)
{
	if (MinecraftObj == NULL) return;

	jclass MinecraftClass = GetClass();
	if (MinecraftClass == NULL) return;

	jfieldID rightclickfield = JNIHelper::env->GetFieldID(MinecraftClass, "field_71467_ac", "I");
	if (rightclickfield == NULL) return;

	JNIHelper::env->SetIntField(MinecraftObj, rightclickfield, count);
}

void Minecraft::LeftClick()
{
	if (MinecraftObj == NULL) return;

	jclass MinecraftClass = GetClass();
	if (MinecraftClass == NULL) return;

	jmethodID leftClick = JNIHelper::env->GetMethodID(MinecraftClass, "func_147116_af", "()V");
	if (leftClick == NULL) return;

	JNIHelper::env->CallVoidMethod(MinecraftObj, leftClick);
}