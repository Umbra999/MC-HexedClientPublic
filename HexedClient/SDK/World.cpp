#include "World.hpp"

World::World(jobject obj)
{
	WorldObj = obj;
	JNIHelper::env->DeleteLocalRef(obj);
}