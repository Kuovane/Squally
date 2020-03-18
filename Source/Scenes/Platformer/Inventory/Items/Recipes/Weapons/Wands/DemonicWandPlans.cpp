#include "DemonicWandPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DemonicWandPlans::SaveKeyDemonicWandPlans = "demonic-wand-plans";

DemonicWandPlans* DemonicWandPlans::create()
{
	DemonicWandPlans* instance = new DemonicWandPlans();

	instance->autorelease();

	return instance;
}

DemonicWandPlans::DemonicWandPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

DemonicWandPlans::~DemonicWandPlans()
{
}

Item* DemonicWandPlans::craft()
{
	return ArcaneWand::create();
}

std::vector<std::tuple<Item*, int>> DemonicWandPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 6 },
		{ Tin::create(), 2 },
		{ Gold::create(), 4 },
		{ Emerald::create(), 2 },
		{ Jade::create(), 3 },
	};
}

Item* DemonicWandPlans::clone()
{
	return DemonicWandPlans::create();
}

std::string DemonicWandPlans::getItemName()
{
	return DemonicWandPlans::SaveKeyDemonicWandPlans;
}

LocalizedString* DemonicWandPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_ArcaneWand::create();
}

std::string DemonicWandPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string DemonicWandPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Wands_ArcaneWand;
}

std::string DemonicWandPlans::getSerializationKey()
{
	return DemonicWandPlans::SaveKeyDemonicWandPlans;
}
