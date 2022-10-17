#include "World.hpp"
#include "../Wrapper/Logger.hpp"

World::World(jobject obj)
{
	WorldObj = obj;
}

jclass World::GetClass()
{
	if (WorldObj == NULL) return NULL;

	jclass WorldClass = JNIHelper::env->GetObjectClass(WorldObj);
	if (WorldClass == NULL) return NULL;
}

std::vector<jobject*> World::getPlayerList()
{
	std::vector<jobject*> result;

	if (WorldObj == NULL) return result;

	jclass WorldClass = JNIHelper::env->GetObjectClass(WorldObj);
	if (WorldClass == NULL) return result;

	jfieldID PlayerEntitieList = JNIHelper::env->GetFieldID(WorldClass, "field_73010_i", "Ljava/util/List;");
	if (PlayerEntitieList == NULL) return result;

	jobject playerEntities = JNIHelper::env->GetObjectField(WorldClass, PlayerEntitieList);
	if (playerEntities == NULL) return result;


	jclass arrayList = JNIHelper::env->FindClass("java/util/ArrayList");
	jfieldID elementid = JNIHelper::env->GetFieldID(arrayList, "elementData", "()[Ljava/lang/Object;");
	jfieldID sizeid = JNIHelper::env->GetFieldID(arrayList, "size", "I");

	int size = JNIHelper::env->GetIntField(playerEntities, sizeid);
	
	jobject array = JNIHelper::env->GetObjectField(playerEntities, elementid);

	jobjectArray all = reinterpret_cast<jobjectArray>(array);

	for (int idx = 0; idx < size; idx++)
	{
		jobject entity = JNIHelper::env->GetObjectArrayElement(all, idx);
		if (entity != NULL) result.push_back(&entity);
	}

	JNIHelper::env->DeleteLocalRef(WorldClass);
	JNIHelper::env->DeleteLocalRef(arrayList);
	JNIHelper::env->DeleteLocalRef(playerEntities);
	JNIHelper::env->DeleteLocalRef(array);

	return result;
}

std::vector<jobject*> World::getEntityList()
{
	std::vector<jobject*> result;

	if (WorldObj == NULL) return result;

	jclass WorldClass = JNIHelper::env->GetObjectClass(WorldObj);
	if (WorldClass == NULL) return result;

	jfieldID EntitieList = JNIHelper::env->GetFieldID(WorldClass, "field_73032_d", "Ljava/lang/List;");
	if (EntitieList == NULL) return result;

	jclass java__lang__List = JNIHelper::env->FindClass("java/lang/List");
	jmethodID toArray = JNIHelper::env->GetMethodID(java__lang__List, "toArray", "()[Ljava/lang/Object;");

	jobject Entities = JNIHelper::env->GetObjectField(WorldClass, EntitieList);
	if (Entities == NULL) return result;

	jobjectArray array = reinterpret_cast<jobjectArray>(JNIHelper::env->CallObjectMethod(Entities, toArray));

	if (array == NULL) return result;

	jsize length = JNIHelper::env->GetArrayLength(array);

	for (int idx = 0; idx < length; idx++)
	{
		jobject entity = JNIHelper::env->GetObjectArrayElement(array, idx);
		if (entity != NULL) result.push_back(&entity);
	}

	JNIHelper::env->DeleteLocalRef(WorldClass);
	JNIHelper::env->DeleteLocalRef(java__lang__List);
	JNIHelper::env->DeleteLocalRef(Entities);
	JNIHelper::env->DeleteLocalRef(array);

	return result;
}