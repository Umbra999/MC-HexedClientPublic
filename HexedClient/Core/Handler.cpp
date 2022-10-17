#include "Handler.hpp"
#include <Windows.h>
#include "Settings.hpp"
#include "../SDK/LaunchWrapper.hpp"

void Handler::ExternalWork()
{
	if (GetAsyncKeyState(VK_END))
	{
		Settings::ShouldUninject = true;
	}
}

void Handler::OnUpdatePatch()
{
	if (Settings::RemoveLClickDelay)
	{
		LaunchWrapper::getMinecraft().SetLeftClickDelay(0);
	}

	if (Settings::RemoveRClickDelay)
	{
		LaunchWrapper::getMinecraft().SetRightClickDelay(0);
	}

	if (Settings::AutoSprint)
	{
		LaunchWrapper::getMinecraft().getLocalPlayer().setSprinting(true);
	}

	if (Settings::LeftClickMultiplier && (GetAsyncKeyState(VK_LBUTTON) & 0x8000))
	{
		LaunchWrapper::getMinecraft().LeftClick();
	}
}