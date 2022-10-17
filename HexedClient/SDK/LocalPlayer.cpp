#include "LocalPlayer.hpp"

LocalPlayer::LocalPlayer(jobject obj)
{
	LocalPlayerObj = obj;
}

jclass LocalPlayer::GetClass()
{
	if (LocalPlayerObj == NULL) return NULL;

	jclass LocalPlayerClass = JNIHelper::env->GetObjectClass(LocalPlayerObj);
	if (LocalPlayerClass == NULL) return NULL;

	return LocalPlayerClass;
}

void LocalPlayer::setSprinting(jboolean sprinting)
{
	if (LocalPlayerObj == NULL) return;

	jclass LocalPlayerClass = GetClass();
	if (LocalPlayerClass == NULL) return;

	jmethodID setSprinting = JNIHelper::env->GetMethodID(LocalPlayerClass, "func_70031_b", "(Z)V");
	if (setSprinting == NULL) return;

	JNIHelper::env->CallVoidMethod(LocalPlayerObj, setSprinting, sprinting);

	JNIHelper::env->DeleteLocalRef(LocalPlayerClass);
}