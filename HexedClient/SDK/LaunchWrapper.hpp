#pragma once
#include "Minecraft.hpp"

class LaunchWrapper
{
private:

public:
	inline static jclass minecraftClass;
	inline static jclass getMinecraftClass();
	inline static Minecraft getMinecraft();
};