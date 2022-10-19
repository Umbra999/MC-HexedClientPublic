#include "Handler.hpp"
#include <Windows.h>
#include "Settings.hpp"
#include "../SDK/LaunchWrapper.hpp"
#include "../Wrapper/Logger.hpp"

int Handler::CurrentTick = 0;

void Handler::OnTick()
{
	Settings::DebugFPS = LaunchWrapper::getMinecraft().GetFPS();

	if (Settings::NoHitDelay)
	{
		LaunchWrapper::getMinecraft().SetLeftClickDelay(0);
	}

	if (Settings::NoBuildDelay)
	{
		LaunchWrapper::getMinecraft().SetRightClickDelay(0);
	}

	if (Settings::AutoSprint)
	{
		LaunchWrapper::getMinecraft().getLocalPlayer().setSprinting(true);
	}

	if (Settings::Autoclicker && (GetAsyncKeyState(VK_LBUTTON) & 0x8000))
	{
		if ((Settings::AutoclickerCount - CurrentTick++) >= 0) LaunchWrapper::getMinecraft().LeftClick();
		if (CurrentTick >= 20) CurrentTick = 0;
	}

	if (Settings::FrameSpoof)
	{
		LaunchWrapper::getMinecraft().SetFPS(Settings::FrameSpoofValue);
	}

	if (Settings::AntiBot)
	{
		for (auto& val : LaunchWrapper::getMinecraft().getWorld().getPlayerList())
		{
			std::string s = JNIHelper::env->GetStringUTFChars(val.GetEntityLivingBase().GetEntity().GetDisplayName(), 0);
			Logger::Log(s);
		}
	}
}

void Handler::DoKeyBinds()
{
	if (!LaunchWrapper::getMinecraft().InGameHasFocus()) return;

	if (GetAsyncKeyState(VK_END))
	{
		Settings::ShouldUninject = true;
	}
}