#include "Minecraft.hpp"

Minecraft::Minecraft(jobject obj)
{
	CurrentObject = obj;
}

jobject Minecraft::GetCurrentObject()
{
	return CurrentObject;
}

jclass Minecraft::GetCurrentClass()
{
	if (CurrentObject == NULL) return NULL;
	if (CurrentClass == NULL) CurrentClass = JNIHelper::env->GetObjectClass(CurrentObject);

	return CurrentClass;
}

LocalPlayer Minecraft::getLocalPlayer()
{
	if (GetCurrentClass() == NULL) return NULL;

	if (LocalPlayerInstance.GetCurrentClass() == NULL)
	{
		if (getLocalPlayerFieldID == NULL)
		{
			getLocalPlayerFieldID = JNIHelper::env->GetFieldID(GetCurrentClass(), "field_71439_g", "Lnet/minecraft/client/entity/EntityPlayerSP;");
			if (getLocalPlayerFieldID == NULL) return NULL;
		}

		if (getLocalPlayerObject == NULL)
		{
			getLocalPlayerObject = JNIHelper::env->GetObjectField(GetCurrentObject(), getLocalPlayerFieldID);
			if (getLocalPlayerObject == NULL) return NULL;
		}

		LocalPlayerInstance = LocalPlayer(getLocalPlayerObject);
	}

	return LocalPlayerInstance;
}

WorldClient Minecraft::getWorld()
{
	if (GetCurrentClass() == NULL) return NULL;

	if (WorldInstance.GetCurrentClass() == NULL)
	{
		if (getWorldFieldID == NULL)
		{
			getWorldFieldID = JNIHelper::env->GetFieldID(GetCurrentClass(), "field_71441_e", "Lnet/minecraft/client/multiplayer/WorldClient;");
			if (getWorldFieldID == NULL) return NULL;
		}
		
		if (getWorldObject == NULL)
		{
			getWorldObject = JNIHelper::env->GetObjectField(GetCurrentObject(), getWorldFieldID);
			if (getWorldObject == NULL) return NULL;
		}

		WorldInstance = WorldClient(getWorldObject);
	}

	return WorldInstance;
}

NetworkManager Minecraft::getNetworkManager()
{
	if (GetCurrentClass() == NULL) return NULL;

	if (NetworkManagerInstance.GetCurrentClass() == NULL)
	{
		if (getNetworkManagerFieldID == NULL)
		{
			getNetworkManagerFieldID = JNIHelper::env->GetFieldID(GetCurrentClass(), "field_71453_ak", "Lnet/minecraft/client/network/NetworkManager;");
			if (getNetworkManagerFieldID == NULL) return NULL;
		}

		if (getNetworkManagerObject == NULL)
		{
			getNetworkManagerObject = JNIHelper::env->GetObjectField(GetCurrentObject(), getNetworkManagerFieldID);
			if (getNetworkManagerObject == NULL) return NULL;
		}

		NetworkManagerInstance = NetworkManager(getNetworkManagerObject);
	}

	return NetworkManagerInstance;
}

ServerData Minecraft::getServerData()
{
	if (GetCurrentClass() == NULL) return NULL;

	if (ServerDataInstance.GetCurrentClass() == NULL)
	{
		if (getServerDataFieldID == NULL)
		{
			getServerDataFieldID = JNIHelper::env->GetFieldID(GetCurrentClass(), "field_71422_O", "Lnet/minecraft/client/multiplayer/ServerData;");
			if (getServerDataFieldID == NULL) return NULL;
		}

		if (getServerDataObject == NULL)
		{
			getServerDataObject = JNIHelper::env->GetObjectField(GetCurrentObject(), getServerDataFieldID);
			if (getServerDataObject == NULL) return NULL;
		}

		ServerDataInstance = ServerData(getServerDataObject);
	}

	return ServerDataInstance;
}

void Minecraft::SetLeftClickDelay(int count)
{
	if (GetCurrentClass() == NULL) return;

	if (leftClickFieldID == NULL)
	{
		leftClickFieldID = JNIHelper::env->GetFieldID(GetCurrentClass(), "field_71429_W", "I");
		if (leftClickFieldID == NULL) return;
	}

	JNIHelper::env->SetIntField(GetCurrentObject(), leftClickFieldID, count);
}

void Minecraft::SetRightClickDelay(int count)
{
	if (GetCurrentClass() == NULL) return;

	if (rightClickFieldID == NULL)
	{
		rightClickFieldID = JNIHelper::env->GetFieldID(GetCurrentClass(), "field_71467_ac", "I");
		if (rightClickFieldID == NULL) return;
	}

	JNIHelper::env->SetIntField(GetCurrentObject(), rightClickFieldID, count);
}

void Minecraft::LeftClick()
{
	if (GetCurrentClass() == NULL) return;

	if (leftClickMethodID == NULL)
	{
		leftClickMethodID = JNIHelper::env->GetMethodID(GetCurrentClass(), "func_147116_af", "()V");
		if (leftClickMethodID == NULL) return;
	}

	JNIHelper::env->CallVoidMethod(GetCurrentObject(), leftClickMethodID);
}

void Minecraft::RightClick()
{
	if (GetCurrentClass() == NULL) return;

	if (rightClickMethodID == NULL)
	{
		rightClickMethodID = JNIHelper::env->GetMethodID(GetCurrentClass(), "func_147121_ag", "()V");
		if (rightClickMethodID == NULL) return;
	}

	JNIHelper::env->CallVoidMethod(GetCurrentObject(), rightClickMethodID);
}

bool Minecraft::InGameHasFocus()
{
	if (GetCurrentClass() == NULL) return NULL;

	if (hasIngameFocusBool == NULL)
	{
		if (gameHasFocusFieldID == NULL)
		{
			gameHasFocusFieldID = JNIHelper::env->GetFieldID(GetCurrentClass(), "field_71415_G", "Z");
			if (gameHasFocusFieldID == NULL) return NULL;
		}

		hasIngameFocusBool = JNIHelper::env->GetBooleanField(GetCurrentObject(), gameHasFocusFieldID);
	}

	return hasIngameFocusBool;
}

int Minecraft::GetFPS()
{
	if (GetCurrentClass() == NULL) return NULL;

	if (getfpsCounterInt == NULL)
	{
		if (fpsCounterFieldID == NULL)
		{
			fpsCounterFieldID = JNIHelper::env->GetStaticFieldID(GetCurrentClass(), "field_71470_ab", "I");
			if (fpsCounterFieldID == NULL) return NULL;
		}

		getfpsCounterInt = JNIHelper::env->GetStaticIntField(GetCurrentClass(), fpsCounterFieldID);
	}

	return getfpsCounterInt;
}

void Minecraft::SetFPS(jint FPS)
{
	if (GetCurrentClass() == NULL) return;

	if (fpsCounterFieldID == NULL)
	{
		fpsCounterFieldID = JNIHelper::env->GetStaticFieldID(GetCurrentClass(), "field_71470_ab", "I");
		if (fpsCounterFieldID == NULL) return;
	}

	JNIHelper::env->SetStaticIntField(GetCurrentClass(), fpsCounterFieldID, FPS);
}