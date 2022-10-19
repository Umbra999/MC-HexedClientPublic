#pragma once
#include "LocalPlayer.hpp"
#include "World.hpp"
#include "NetworkManager.hpp"

class Minecraft
{
private:
	jobject MinecraftObj = NULL;
	jclass CurrentClass = NULL;
	LocalPlayer LocalPlayerInstance = NULL;
	World WorldInstance = NULL;
	NetworkManager NetworkManagerInstance = NULL;

	jfieldID leftClickFieldID = NULL;
	jfieldID rightClickFieldID = NULL;
	jmethodID leftClickMethodID = NULL;
	jmethodID rightClickMethodID = NULL;
	jfieldID gameHasFocusFieldID = NULL;
	jfieldID fpsCounterFieldID = NULL;

	jboolean hasIngameFocus = NULL;
	jint fpsCounter = NULL;

public:
	Minecraft(jobject);
	jobject GetCurrentObject();
	jclass GetCurrentClass();

	LocalPlayer getLocalPlayer();
	World getWorld();
	NetworkManager getNetworkManager();
	void SetLeftClickDelay(int);
	void SetRightClickDelay(int);
	void LeftClick();
	void RightClick();
	bool InGameHasFocus();
	int GetFPS();
	void SetFPS(jint);
};