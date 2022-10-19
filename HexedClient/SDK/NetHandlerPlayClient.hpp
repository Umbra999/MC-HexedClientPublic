#pragma once
#include "JNIHelper.hpp"

class NetHandlerPlayClient
{
private:
	jobject NetHandlerPlayClientObj = NULL;
	jclass CurrentClass = NULL;

public:
	NetHandlerPlayClient(jobject obj);
	jobject GetCurrentObject();
	jclass GetCurrentClass();
};