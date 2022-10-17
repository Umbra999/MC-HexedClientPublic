#pragma once
#include <Windows.h>
#include <iostream>
#include "JNIHelper.hpp"
#include <vector>

class World
{
private:

public:
	jobject WorldObj;

	World(jobject obj);
	jclass GetClass();

	std::vector<jobject*> getPlayerList();
	std::vector<jobject*> getEntityList();
};