#pragma once
#include <Windows.h>
#include <iostream>
#include "JNIHelper.hpp"
#include <vector>
#include "EntityPlayer.hpp"

class World
{
private:
	jobject WorldObj = NULL;
	jclass CurrentClass = NULL;

	jfieldID playerListFieldID = NULL;
	jobject playerListObject = NULL;
	jint playerListSize = NULL;
	jobjectArray playerList = NULL;

	jfieldID entityListFieldID = NULL;
	jobject entityListObject = NULL;
	jint entityListSize = NULL;
	jobjectArray entityList = NULL;

public:
	World(jobject obj);
	jobject GetCurrentObject();
	jclass GetCurrentClass();

	std::vector<EntityPlayer> getPlayerList();
	std::vector<jobject*> getEntityList();
};