#pragma once
#include "Minecraft.hpp"

class LaunchWrapper
{
private:
	inline static jclass minecraftClass = NULL;
	inline static Minecraft minecraftInstance = NULL;
	inline static jclass forgeClass = NULL;
	static jclass getMinecraftClass();
public:
	static Minecraft getMinecraft();
	static bool IsForge();
};