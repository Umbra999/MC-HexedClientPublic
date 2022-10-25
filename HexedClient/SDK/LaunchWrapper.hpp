#pragma once
#include "Minecraft.hpp"

class LaunchWrapper
{
private:
	inline static jclass forgeClass = NULL;

	inline static jclass minecraftClass = NULL;
	inline static jfieldID getMinecraftFieldID = NULL;
	inline static jobject getMinecraftObject = NULL;
	inline static Minecraft MinecraftInstance = NULL;
public:
	static Minecraft getMinecraft();
	static bool IsForge();
};