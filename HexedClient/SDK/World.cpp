#include "World.hpp"
#include "Utils/JavaUtil.hpp"
#include "../Wrapper/Logger.hpp"

World::World(jobject obj)
{
	WorldObj = obj;
}

jobject World::GetCurrentObject()
{
	return WorldObj;
}

jclass World::GetCurrentClass()
{
	if (WorldObj == NULL) return NULL;
	if (CurrentClass == NULL) CurrentClass = JNIHelper::env->GetObjectClass(WorldObj);

	return CurrentClass;
}

std::vector<EntityPlayer> World::getPlayerList()
{
	std::vector<EntityPlayer> cachedPlayers;

	if (GetCurrentClass() == NULL) return cachedPlayers;

	if (playerListFieldID == NULL)
	{
		playerListFieldID = JNIHelper::env->GetFieldID(GetCurrentClass(), "field_73010_i", "Ljava/util/List;");
		if (playerListFieldID == NULL) return cachedPlayers;
	}

	if (playerListObject == NULL)
	{
		playerListObject = JNIHelper::env->GetObjectField(WorldObj, playerListFieldID);
		if (playerListObject == NULL)return cachedPlayers;
	}

	if (playerListSize == NULL)
	{
		playerListSize = JavaUtil::GetArraySize(playerListObject);
		if (playerListSize == NULL) return cachedPlayers;
	}

	if (playerList == NULL)
	{
		playerList = JavaUtil::GetArray(playerListObject);
		if (playerList == NULL) return cachedPlayers;
	}

	for (int idx = 0; idx < playerListSize; idx++)
	{
		jobject entity = JNIHelper::env->GetObjectArrayElement(playerList, idx);
		if (entity != NULL) cachedPlayers.push_back(EntityPlayer(entity));
	}

	return cachedPlayers;
}

std::vector<jobject*> World::getEntityList()
{
	std::vector<jobject*> result;

	if (GetCurrentClass() == NULL) return result;

	if (entityListFieldID == NULL)
	{
		entityListFieldID = JNIHelper::env->GetFieldID(GetCurrentClass(), "field_72996_f", "Ljava/util/List;");
		if (entityListFieldID == NULL) return result;
	}

	if (entityListObject == NULL)
	{
		entityListObject = JNIHelper::env->GetObjectField(WorldObj, entityListFieldID);
		if (entityListObject == NULL)return result;
	}

	if (entityListSize == NULL)
	{
		entityListSize = JavaUtil::GetArraySize(entityListObject);
		if (entityListSize == NULL) return result;
	}

	if (entityList == NULL)
	{
		entityList = JavaUtil::GetArray(entityListObject);
		if (entityList == NULL) return result;
	}

	for (int idx = 0; idx < entityListSize; idx++)
	{
		jobject entity = JNIHelper::env->GetObjectArrayElement(entityList, idx);
		if (entity != NULL) result.push_back(&entity);
	}

	return result;
}