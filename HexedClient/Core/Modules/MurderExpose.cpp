#include "MurderExpose.hpp"
#include "../Settings.hpp"
#include "../SDK/LaunchWrapper.hpp"
#include "../Wrapper/Logger.hpp"
#include "../../Wrapper/ClientConsole.hpp"

void MurderExpose::OnTick()
{
	if (Settings::MurderExpose)
	{
		for (auto& player : LaunchWrapper::getMinecraft().getWorld().getPlayerList())
		{
			if (JNIHelper::env->IsSameObject(player.GetCurrentObject(), LaunchWrapper::getMinecraft().getLocalPlayer().GetCurrentObject())) continue;

			if (player.getCurrentEquipedItem().getUnlocalizedName() == NULL) continue;

			std::string HeldItem = JNIHelper::env->GetStringUTFChars(player.getCurrentEquipedItem().getUnlocalizedName(), 0);

			if (HeldItem == "item.swordGold" || HeldItem == "item.swordDiamond" || HeldItem == "item.swordIron" || HeldItem == "item.swordStone" || HeldItem == "item.swordWood" || 
				HeldItem == "item.shovelGold" || HeldItem == "item.shovelDiamond" || HeldItem == "item.shovelIron" || HeldItem == "item.shovelStone" || HeldItem == "item.shovelWood" || 
				HeldItem == "item.hatchedGold" || HeldItem == "item.hatchedDiamond" || HeldItem == "item.hatchedIron" || HeldItem == "item.hatchedStone" || HeldItem == "item.hatchedWood" ||
				HeldItem == "item.pickaxeGold" || HeldItem == "item.pickaxeDiamond" || HeldItem == "item.pickaxeIron" || HeldItem == "item.pickaxeStone" || HeldItem == "item.pickaxeWood" ||
				HeldItem == "item.hoeGold" || HeldItem == "item.hoeDiamond" || HeldItem == "item.hoeIron" || HeldItem == "item.hoeStone" || HeldItem == "item.hoeWood" ||
				HeldItem == "item.feather" || HeldItem == "item.carrotGolden" || HeldItem == "item.nameTag" || HeldItem == "item.carrotOnAStick" || HeldItem == "item.blazeRod" || HeldItem == "tile.notGate" || HeldItem == "tile.torch" || HeldItem == "item.bone" || HeldItem == "item.cookie" || HeldItem == "item.stick" || HeldItem == "item.prismarineShard" || HeldItem == "item.apple" || HeldItem == "item.speckledMelon" || HeldItem == "item.beefCooked" ||
				HeldItem == "item.pumpkinPie" || HeldItem == "item.carrots" || HeldItem == "item.shears" || HeldItem == "item.fish.salmon.raw" || HeldItem == "tile.doublePlant.rose" || HeldItem == "tile.deadbush" || HeldItem == "item.appleGold" || HeldItem == "tile.sponge.dry" || HeldItem == "item.boath" || HeldItem == "tile.dragonEgg" || HeldItem == "item.netherbrick" || HeldItem == "item.netherquartz" || HeldItem == "item.dyePowder.red" || HeldItem == "item.book")
			{
				std::string DisplayName = JNIHelper::env->GetStringUTFChars(player.GetDisplayName(), 0);
				Logger::Log(DisplayName + " is the Murder: " + HeldItem);
				ClientConsole::Log(DisplayName + " is the Murder: " + HeldItem);
			}
		}
	}
}