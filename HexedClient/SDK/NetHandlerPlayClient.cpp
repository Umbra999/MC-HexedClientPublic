#include "NetHandlerPlayClient.hpp"

NetHandlerPlayClient::NetHandlerPlayClient(jobject obj)
{
	NetHandlerPlayClientObj = obj;
}

jobject NetHandlerPlayClient::GetCurrentObject()
{
	return NetHandlerPlayClientObj;
}

jclass NetHandlerPlayClient::GetCurrentClass()
{
	if (NetHandlerPlayClientObj == NULL) return NULL;
	if (CurrentClass == NULL) CurrentClass = JNIHelper::env->GetObjectClass(NetHandlerPlayClientObj);

	return CurrentClass;
}