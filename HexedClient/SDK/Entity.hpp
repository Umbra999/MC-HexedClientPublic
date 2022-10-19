#pragma once
#include "JNIHelper.hpp"
#include <string>

class Entity
{
private:
	jobject EntityObj = NULL;
	jclass CurrentClass = NULL;

	jmethodID getNameMethodID = NULL;
	jobject getNameObject = NULL;
	jstring DisplayName = NULL;
	jmethodID setNameMethodID = NULL;

public:
	Entity(jobject obj);
	jobject GetCurrentObject();
	jclass GetCurrentClass();

	jstring GetDisplayName();
	void SetDisplayName(jstring);
};