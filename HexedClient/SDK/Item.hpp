#pragma once
#include "JNIHelper.hpp"

class Item
{
private:
	jobject CurrentObject = NULL;
	jclass CurrentClass = NULL;

	jmethodID getItemIDMethodID = NULL;
	jint getItemIDInt = NULL;

public:
	Item(jobject obj);
	jobject GetCurrentObject();
	jclass GetCurrentClass();
	
	jint GetItemID();
};