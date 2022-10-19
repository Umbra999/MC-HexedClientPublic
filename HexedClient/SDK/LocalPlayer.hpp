#pragma once
#include "JNIHelper.hpp"
#include "NetHandlerPlayClient.hpp"

class LocalPlayer
{
private:
	jobject LocalPlayerObj = NULL;
	jclass CurrentClass = NULL;
	NetHandlerPlayClient NetHandlerPlayClientInstance = NULL;

	jmethodID setSprintingMethodID = NULL;
	jmethodID swingItemMethodID = NULL;

public:
	LocalPlayer(jobject);
	jobject GetCurrentObject();
	jclass GetCurrentClass();

	NetHandlerPlayClient getNetHandlerPlayClient();
	void setSprinting(jboolean);
	void swingItem();
};