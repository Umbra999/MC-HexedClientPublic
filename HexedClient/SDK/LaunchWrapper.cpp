#include "LaunchWrapper.hpp"
#include "JNIHelper.hpp"
#include "../Wrapper/Logger.hpp"

jclass LaunchWrapper::getMinecraftClass()
{
	if (minecraftClass == NULL) minecraftClass = JNIHelper::ForgeFindClass("net.minecraft.client.Minecraft");
	return minecraftClass;
}

Minecraft LaunchWrapper::getMinecraft()
{
	jfieldID findMinecraft = JNIHelper::env->GetStaticFieldID(getMinecraftClass(), "field_71432_P", "Lnet/minecraft/client/Minecraft;");
	if (findMinecraft == NULL) return NULL;
	jobject Instance = JNIHelper::env->GetStaticObjectField(getMinecraftClass(), findMinecraft);
	return Minecraft(Instance);
}

bool LaunchWrapper::IsForge()
{
	jclass ForgeClass = JNIHelper::env->FindClass("net/minecraftforge/common/ForgeVersion");
	if (ForgeClass == NULL) return false;
	JNIHelper::env->DeleteLocalRef(ForgeClass);
	return true;
}