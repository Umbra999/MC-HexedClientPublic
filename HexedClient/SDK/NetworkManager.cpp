#include "NetworkManager.hpp"

NetworkManager::NetworkManager(jobject obj)
{
	NetworkManagerObj = obj;
}

jobject NetworkManager::GetCurrentObject()
{
	return NetworkManagerObj;
}

jclass NetworkManager::GetCurrentClass()
{
	if (NetworkManagerObj == NULL) return NULL;
	if (CurrentClass == NULL) CurrentClass = JNIHelper::env->GetObjectClass(NetworkManagerObj);

	return CurrentClass;
}