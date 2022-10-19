#include "NetworkPlayerInfo.hpp"

NetworkPlayerInfo::NetworkPlayerInfo(jobject obj)
{
	NetworkPlayerInfoObj = obj;
}

jobject NetworkPlayerInfo::GetCurrentObject()
{
	return NetworkPlayerInfoObj;
}

jclass NetworkPlayerInfo::GetCurrentClass()
{
	if (NetworkPlayerInfoObj == NULL) return NULL;
	if (CurrentClass == NULL) CurrentClass = JNIHelper::env->GetObjectClass(NetworkPlayerInfoObj);

	return CurrentClass;
}