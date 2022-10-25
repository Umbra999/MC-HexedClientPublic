#include <imgui.h>
#include "PlayerESP.hpp"
#include "../Settings.hpp"
#include "../SDK/LaunchWrapper.hpp"

void PlayerESP::OnTick()
{
	if (Settings::PlayerESP)
	{
		auto draw = ImGui::GetBackgroundDrawList();

		for (auto& val : LaunchWrapper::getMinecraft().getWorld().getPlayerList())
		{
			if (!JNIHelper::env->IsSameObject(val.GetCurrentObject(), LaunchWrapper::getMinecraft().getLocalPlayer().GetCurrentObject()))
			{
				
			}
		}
	}
}