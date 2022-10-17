#include "LaunchWrapper.hpp"
#include "JNIHelper.hpp"

jclass LaunchWrapper::getMinecraftClass()
{
	if (minecraftClass == NULL)
	{
		jclass Instance = JNIHelper::ForgeFindClass("net.minecraft.client.Minecraft");
		minecraftClass = Instance;
		JNIHelper::env->DeleteLocalRef(Instance);
	}
	return minecraftClass;
}

Minecraft LaunchWrapper::getMinecraft()
{
	jfieldID findMinecraft = JNIHelper::env->GetStaticFieldID(getMinecraftClass(), "field_71432_P", "Lnet/minecraft/client/Minecraft;");
	if (findMinecraft == NULL) return NULL;
	jobject Instance = JNIHelper::env->GetStaticObjectField(getMinecraftClass(), findMinecraft);
	return Minecraft(Instance);
}