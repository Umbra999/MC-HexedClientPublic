#include "MCHelper.hpp"
#include "../LaunchWrapper.hpp"

EntityPlayer MCHelper::getEntityPlayerByName(std::string name)
{
	for (auto& player : LaunchWrapper::getMinecraft().getWorld().getPlayerList())
	{
		std::string DisplayName = JNIHelper::env->GetStringUTFChars(player.GetDisplayName(), 0);
		if (DisplayName == name) return player;
	}
	
	return NULL;
}

Entity MCHelper::getEntityByName(std::string name)
{
	for (auto& entity : LaunchWrapper::getMinecraft().getWorld().getEntityList())
	{
		std::string DisplayName = JNIHelper::env->GetStringUTFChars(entity.GetDisplayName(), 0);
		if (DisplayName == name) return entity;
	}

	return NULL;
}