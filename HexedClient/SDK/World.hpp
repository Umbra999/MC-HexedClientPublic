#pragma once
#include <Windows.h>
#include <iostream>
#include "JNIHelper.hpp"

class World
{
private:
	jobject WorldObj;

public:
	World(jobject obj);
};