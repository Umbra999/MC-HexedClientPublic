#pragma once
#include "JNIHelper.hpp"
#include "Item.hpp"

class ItemStack
{
private:
	jobject CurrentObject = NULL;
	jclass CurrentClass = NULL;

	jfieldID getItemFieldID = NULL;
	jobject getItemObject = NULL;
	Item ItemInstance = NULL;

	jmethodID getUnlocalizedNameMethodID = NULL;
	jobject getUnlocalizedNameObject = NULL;
	jstring getUnlocalizedNameString = NULL;

public:
	ItemStack(jobject obj);
	jobject GetCurrentObject();
	jclass GetCurrentClass();

	Item GetItem();
	jstring getUnlocalizedName();
};