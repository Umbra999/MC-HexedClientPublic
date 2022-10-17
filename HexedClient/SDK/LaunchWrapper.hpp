#pragma once
#include "Minecraft.hpp"

class LaunchWrapper
{
private:
	inline static jclass minecraftClass;
public:
	static jclass getMinecraftClass();
	static Minecraft getMinecraft();
	static bool IsForge();
};