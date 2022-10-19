#include "Utils/JavaUtil.hpp"
#include "Entity.hpp"

Entity::Entity(jobject obj)
{
	EntityObj = obj;
}

jobject Entity::GetCurrentObject()
{
	return EntityObj;
}

jclass Entity::GetCurrentClass()
{
	if (EntityObj == NULL) return NULL;
	if (CurrentClass == NULL) CurrentClass = JNIHelper::env->GetObjectClass(EntityObj);

	return CurrentClass;
}

jstring Entity::GetDisplayName()
{
	if (GetCurrentClass() == NULL) return NULL;
	if (getNameMethodID == NULL)
	{
		getNameMethodID = JNIHelper::env->GetMethodID(GetCurrentClass(), "func_70005_c_", "()Ljava/lang/String;");
		if (getNameMethodID == NULL) return NULL;
	}

	if (getNameObject == NULL)
	{
		getNameObject = JNIHelper::env->CallObjectMethod(EntityObj, getNameMethodID);
		if (getNameObject == NULL) return NULL;
	}

	if (DisplayName == NULL) DisplayName = (jstring)getNameObject;
	return DisplayName;
}

void Entity::SetDisplayName(jstring Name)
{
	if (GetCurrentClass() == NULL) return;
	if (setNameMethodID == NULL)
	{
		setNameMethodID = JNIHelper::env->GetMethodID(GetCurrentClass(), "func_96094_a", "(Ljava/lang/String;)V");
		if (setNameMethodID == NULL) return;
	}

	JNIHelper::env->CallVoidMethod(EntityObj, setNameMethodID, Name);
}