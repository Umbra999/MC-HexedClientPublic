#pragma once
#include "JNIHelper.hpp"

class LocalPlayer
{
public:
	jobject LocalPlayerObj;

	LocalPlayer(jobject obj);
	jclass GetClass();
	void setSprinting(jboolean sprinting);
};