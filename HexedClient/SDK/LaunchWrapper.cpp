#include "LaunchWrapper.hpp"
#include "JNIHelper.hpp"
#include "../Wrapper/Logger.hpp"

Minecraft LaunchWrapper::getMinecraft()
{
	if (MinecraftInstance.GetCurrentClass() == NULL)
	{
		if (minecraftClass == NULL)
		{
			minecraftClass = JNIHelper::ForgeFindClass("net.minecraft.client.Minecraft");
			if (minecraftClass == NULL) return NULL;
		}

		if (getMinecraftFieldID == NULL)
		{
			getMinecraftFieldID = JNIHelper::env->GetStaticFieldID(minecraftClass, "field_71432_P", "Lnet/minecraft/client/Minecraft;");
			if (getMinecraftFieldID == NULL) return NULL;
		}

		if (getMinecraftObject == NULL)
		{
			getMinecraftObject = JNIHelper::env->GetStaticObjectField(minecraftClass, getMinecraftFieldID);
			if (getMinecraftObject == NULL) return NULL;
		}

		MinecraftInstance = Minecraft(getMinecraftObject);
	}

	return MinecraftInstance;
}

bool LaunchWrapper::IsForge()
{
	if (forgeClass == NULL) forgeClass = JNIHelper::env->FindClass("net/minecraftforge/common/ForgeVersion");
	return forgeClass != NULL;
}