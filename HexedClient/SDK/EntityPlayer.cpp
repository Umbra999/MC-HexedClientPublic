#include "EntityPlayer.hpp"
#include "../Wrapper/Logger.hpp"

EntityPlayer::EntityPlayer(jobject obj)
{
	EntityPlayerObj = obj;
}

jobject EntityPlayer::GetCurrentObject()
{
	return EntityPlayerObj;
}

jclass EntityPlayer::GetCurrentClass()
{
	if (EntityPlayerObj == NULL) return NULL;
	if (CurrentClass == NULL) CurrentClass = JNIHelper::env->GetObjectClass(EntityPlayerObj);

	return CurrentClass;
}

EntityLivingBase EntityPlayer::GetEntityLivingBase()
{
	if (GetCurrentClass() == NULL) return NULL;
	if (EntityLivingBaseInstance.GetCurrentClass() == NULL) EntityLivingBaseInstance = EntityLivingBase(EntityPlayerObj);

	return EntityLivingBaseInstance;
}