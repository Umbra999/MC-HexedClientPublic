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
	if (getMinecraftClass() == NULL) return NULL;
	if (minecraftInstance.GetCurrentClass() == NULL)
	{
		jfieldID findMinecraft = JNIHelper::env->GetStaticFieldID(getMinecraftClass(), "field_71432_P", "Lnet/minecraft/client/Minecraft;");
		if (findMinecraft == NULL) return NULL;
		jobject Instance = JNIHelper::env->GetStaticObjectField(getMinecraftClass(), findMinecraft);
		minecraftInstance = Minecraft(Instance);
	}
	return minecraftInstance;
}

bool LaunchWrapper::IsForge()
{
	if (forgeClass == NULL) forgeClass = JNIHelper::env->FindClass("net/minecraftforge/common/ForgeVersion");
	return forgeClass != NULL;
}