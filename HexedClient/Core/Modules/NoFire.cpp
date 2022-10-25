#include "NoFire.hpp"
#include "../Settings.hpp"
#include "../SDK/LaunchWrapper.hpp"

bool NoFire::NeedReset = false;

void NoFire::OnTick()
{
	if (Settings::NoFire) LaunchWrapper::getMinecraft().getLocalPlayer().SetImmuneToFire(true);
	else if (NeedReset) LaunchWrapper::getMinecraft().getLocalPlayer().SetImmuneToFire(false);
}