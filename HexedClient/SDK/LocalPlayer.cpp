#include "LocalPlayer.hpp"

LocalPlayer::LocalPlayer(jobject obj) : EntityPlayer(obj)
{
	CurrentObject = obj;
}

jobject LocalPlayer::GetCurrentObject()
{
	return CurrentObject;
}

jclass LocalPlayer::GetCurrentClass()
{
	if (CurrentObject == NULL) return NULL;
	if (CurrentClass == NULL) CurrentClass = JNIHelper::env->GetObjectClass(CurrentObject);

	return CurrentClass;
}

NetHandlerPlayClient LocalPlayer::getNetHandlerPlayClient()
{
	if (GetCurrentClass() == NULL) return NULL;

	if (NetHandlerPlayClientInstance.GetCurrentClass() == NULL)
	{
		if (getNetHandlerPlayClientFieldID == NULL)
		{
			getNetHandlerPlayClientFieldID = JNIHelper::env->GetFieldID(GetCurrentClass(), "field_71174_a", "Lnet/minecraft/client/network/NetHandlerPlayClient;");
			if (getNetHandlerPlayClientFieldID == NULL) return NULL;
		}

		if (getNetHandlerPlayClientObject == NULL)
		{
			getNetHandlerPlayClientObject = JNIHelper::env->GetObjectField(GetCurrentObject(), getNetHandlerPlayClientFieldID);
			if (getNetHandlerPlayClientObject == NULL) return NULL;
		}

		NetHandlerPlayClientInstance = NetHandlerPlayClient(getNetHandlerPlayClientObject);
	}

	return NetHandlerPlayClientInstance;
}

void LocalPlayer::setSprinting(jboolean sprinting)
{
	if (GetCurrentClass() == NULL) return;

	if (setSprintingMethodID == NULL)
	{
		setSprintingMethodID = JNIHelper::env->GetMethodID(GetCurrentClass(), "func_70031_b", "(Z)V");
		if (setSprintingMethodID == NULL) return;
	}

	JNIHelper::env->CallVoidMethod(GetCurrentObject(), setSprintingMethodID, sprinting);
}

void LocalPlayer::swingItem()
{
	if (GetCurrentClass() == NULL) return;

	if (swingItemMethodID == NULL)
	{
		swingItemMethodID = JNIHelper::env->GetMethodID(GetCurrentClass(), "func_71038_i", "()V");
		if (swingItemMethodID == NULL) return;
	}

	JNIHelper::env->CallVoidMethod(GetCurrentObject(), swingItemMethodID);
}