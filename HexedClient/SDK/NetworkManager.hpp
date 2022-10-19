#pragma once
#include "JNIHelper.hpp"

class NetworkManager
{
private:
	jobject NetworkManagerObj = NULL;
	jclass CurrentClass = NULL;

public:
	NetworkManager(jobject obj);
	jobject GetCurrentObject();
	jclass GetCurrentClass();
};