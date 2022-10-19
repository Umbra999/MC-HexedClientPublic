#pragma once
#include "Entity.hpp"

class EntityLivingBase
{
private:
	jobject EntityLivingBaseObj = NULL;
	jclass CurrentClass = NULL;

	Entity EntityInstance = NULL;
	jmethodID getHealthMethodID = NULL;
	jfloat getHealthMethod = NULL;

public:
	EntityLivingBase(jobject obj);
	jobject GetCurrentObject();
	jclass GetCurrentClass();

	Entity GetEntity();
	float GetHealth();
};