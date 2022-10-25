#include "Item.hpp"

Item::Item(jobject obj)
{
	CurrentObject = obj;
}

jobject Item::GetCurrentObject()
{
	return CurrentObject;
}

jclass Item::GetCurrentClass()
{
	if (CurrentObject == NULL) return NULL;
	if (CurrentClass == NULL) CurrentClass = JNIHelper::env->GetObjectClass(CurrentObject);

	return CurrentClass;
}

jint Item::GetItemID()
{
	if (GetCurrentClass() == NULL) return NULL;

	if (getItemIDInt == NULL)
	{
		if (getItemIDMethodID == NULL)
		{
			getItemIDMethodID = JNIHelper::env->GetMethodID(GetCurrentClass(), "func_150891_b", "(Lnet/minecraft/item/Item;)I");
			if (getItemIDMethodID == NULL) return NULL;
		}

		getItemIDInt = JNIHelper::env->CallStaticIntMethod(GetCurrentClass(), getItemIDMethodID, GetCurrentObject());
	}

	return getItemIDInt;
}