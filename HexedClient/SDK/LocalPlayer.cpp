#include "LocalPlayer.hpp"

LocalPlayer::LocalPlayer(jobject obj)
{
	LocalPlayerObj = obj;
}

jobject LocalPlayer::GetCurrentObject()
{
	return LocalPlayerObj;
}

jclass LocalPlayer::GetCurrentClass()
{
	if (LocalPlayerObj == NULL) return NULL;
	if (CurrentClass == NULL) CurrentClass = JNIHelper::env->GetObjectClass(LocalPlayerObj);

	return CurrentClass;
}

NetHandlerPlayClient LocalPlayer::getNetHandlerPlayClient()
{
	if (GetCurrentClass() == NULL) return NULL;
	if (NetHandlerPlayClientInstance.GetCurrentClass() == NULL)
	{
		jfieldID getNNetHandlerPlayClient = JNIHelper::env->GetFieldID(GetCurrentClass(), "field_71174_a", "Lnet/minecraft/client/network/NetHandlerPlayClient;");
		if (getNNetHandlerPlayClient == NULL) return NULL;
		jobject Instance = JNIHelper::env->GetObjectField(LocalPlayerObj, getNNetHandlerPlayClient);
		NetHandlerPlayClientInstance = NetHandlerPlayClient(Instance);
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

	JNIHelper::env->CallVoidMethod(LocalPlayerObj, setSprintingMethodID, sprinting);
}

void LocalPlayer::swingItem()
{
	if (GetCurrentClass() == NULL) return;
	if (swingItemMethodID == NULL)
	{
		swingItemMethodID = JNIHelper::env->GetMethodID(GetCurrentClass(), "func_71038_i", "()V");
		if (swingItemMethodID == NULL) return;
	}

	JNIHelper::env->CallVoidMethod(LocalPlayerObj, swingItemMethodID);
}