#pragma once
#include "LocalPlayer.hpp"
#include "WorldClient.hpp"
#include "NetworkManager.hpp"
#include "ServerData.hpp"

class Minecraft
{
private:
	jobject CurrentObject = NULL;
	jclass CurrentClass = NULL;

	jfieldID getLocalPlayerFieldID = NULL;
	jobject getLocalPlayerObject = NULL;
	LocalPlayer LocalPlayerInstance = NULL;

	jfieldID getWorldFieldID = NULL;
	jobject getWorldObject = NULL;
	WorldClient WorldInstance = NULL;

	jfieldID getNetworkManagerFieldID = NULL;
	jobject getNetworkManagerObject = NULL;
	NetworkManager NetworkManagerInstance = NULL;

	jfieldID getServerDataFieldID = NULL;
	jobject getServerDataObject = NULL;
	ServerData ServerDataInstance = NULL;

	jfieldID leftClickFieldID = NULL;

	jfieldID rightClickFieldID = NULL;

	jmethodID leftClickMethodID = NULL;

	jmethodID rightClickMethodID = NULL;
	
	jfieldID fpsCounterFieldID = NULL;
	jint getfpsCounterInt = NULL;

	jfieldID gameHasFocusFieldID = NULL;
	jboolean hasIngameFocusBool = NULL;

public:
	Minecraft(jobject);
	jobject GetCurrentObject();
	jclass GetCurrentClass();

	LocalPlayer getLocalPlayer();
	WorldClient getWorld();
	NetworkManager getNetworkManager();
	ServerData getServerData();
	void SetLeftClickDelay(int);
	void SetRightClickDelay(int);
	void LeftClick();
	void RightClick();
	bool InGameHasFocus();
	int GetFPS();
	void SetFPS(jint);
};