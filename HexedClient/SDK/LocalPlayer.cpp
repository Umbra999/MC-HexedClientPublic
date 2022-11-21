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
			getNetHandlerPlayClientFieldID = JNIHelper::IsForge() ? JNIHelper::env->GetFieldID(GetCurrentClass(), "field_71174_a", "Lnet/minecraft/client/network/NetHandlerPlayClient;") : JNIHelper::env->GetFieldID(GetCurrentClass(), "a", "Lbcy;");
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
		setSprintingMethodID = JNIHelper::env->GetMethodID(GetCurrentClass(), JNIHelper::IsForge() ? "func_70031_b" : "d", "(Z)V");
		if (setSprintingMethodID == NULL) return;
	}

	JNIHelper::env->CallVoidMethod(GetCurrentObject(), setSprintingMethodID, sprinting);
}

void LocalPlayer::swingItem()
{
	if (GetCurrentClass() == NULL) return;

	if (swingItemMethodID == NULL)
	{
		swingItemMethodID = JNIHelper::env->GetMethodID(GetCurrentClass(), JNIHelper::IsForge() ? "func_71038_i" : "bw", "()V");
		if (swingItemMethodID == NULL) return;
	}

	JNIHelper::env->CallVoidMethod(GetCurrentObject(), swingItemMethodID);
}