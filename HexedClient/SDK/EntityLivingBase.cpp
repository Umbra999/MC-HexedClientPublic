#include "EntityLivingBase.hpp"
#include "../Wrapper/Logger.hpp"

EntityLivingBase::EntityLivingBase(jobject obj)
{
	EntityLivingBaseObj = obj;
}

jobject EntityLivingBase::GetCurrentObject()
{
	return EntityLivingBaseObj;
}

jclass EntityLivingBase::GetCurrentClass()
{
	if (EntityLivingBaseObj == NULL) return NULL;
	if (CurrentClass == NULL) CurrentClass = JNIHelper::env->GetObjectClass(EntityLivingBaseObj);

	return CurrentClass;
}

jfloat EntityLivingBase::GetHealth()
{
	if (GetCurrentClass() == NULL) return NULL;
	if (getHealthMethodID == NULL)
	{
		getHealthMethodID = JNIHelper::env->GetMethodID(GetCurrentClass(), "func_110143_aJ", "()F");
		if (getHealthMethodID == NULL) return NULL;
	}

	if (getHealthMethod == NULL) getHealthMethod = JNIHelper::env->CallFloatMethod(EntityLivingBaseObj, getHealthMethodID);

	return getHealthMethod;
}

Entity EntityLivingBase::GetEntity()
{
	if (GetCurrentClass() == NULL) return NULL;
	if (EntityInstance.GetCurrentClass() == NULL) EntityInstance = Entity(EntityLivingBaseObj);

	return EntityInstance;
}