#pragma once
#include "LocalPlayer.hpp"
#include "World.hpp"

class Minecraft
{
public:
	jobject MinecraftObj;

	Minecraft(jobject obj);
	jclass GetClass();

	LocalPlayer getLocalPlayer();
	World getWorld();
	void SetLeftClickDelay(int count);
	void SetRightClickDelay(int count);
	void LeftClick();
};