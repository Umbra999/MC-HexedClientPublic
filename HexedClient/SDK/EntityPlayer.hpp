#pragma once
#include "EntityLivingBase.hpp"

class EntityPlayer
{
private:
	jobject EntityPlayerObj = NULL;
	jclass CurrentClass = NULL;
	EntityLivingBase EntityLivingBaseInstance = NULL;

public:
	EntityPlayer(jobject obj);
	jobject GetCurrentObject();
	jclass GetCurrentClass();

	EntityLivingBase GetEntityLivingBase();
};