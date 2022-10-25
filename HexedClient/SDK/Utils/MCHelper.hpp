#pragma once
#include "../JNIHelper.hpp"
#include "../EntityPlayer.hpp"
#include <string>

class MCHelper
{
private:
	
public:
	static EntityPlayer getEntityPlayerByName(std::string);
	static Entity getEntityByName(std::string);
};