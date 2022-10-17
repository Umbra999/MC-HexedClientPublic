#pragma once
#include "LocalPlayer.hpp"

class Minecraft
{
public:
	jobject MinecraftObj;

	Minecraft(jobject obj);
	jclass GetClass();

	LocalPlayer getLocalPlayer();
	jobject getWorld();
	void SetLeftClickDelay(int count);
	void SetRightClickDelay(int count);
	void LeftClick();
};