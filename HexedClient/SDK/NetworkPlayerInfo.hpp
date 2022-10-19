#pragma once
#include "JNIHelper.hpp"

class NetworkPlayerInfo
{
private:
	jobject NetworkPlayerInfoObj = NULL;
	jclass CurrentClass = NULL;

public:
	NetworkPlayerInfo(jobject obj);
	jobject GetCurrentObject();
	jclass GetCurrentClass();
};