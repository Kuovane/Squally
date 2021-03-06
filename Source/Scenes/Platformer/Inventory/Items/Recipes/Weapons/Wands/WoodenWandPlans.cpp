#include "WoodenWandPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WoodenWandPlans::SaveKey = "wooden-wand-plans";

WoodenWandPlans* WoodenWandPlans::create()
{
	WoodenWandPlans* instance = new WoodenWandPlans();

	instance->autorelease();

	return instance;
}

WoodenWandPlans::WoodenWandPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

WoodenWandPlans::~WoodenWandPlans()
{
}

Item* WoodenWandPlans::craft()
{
	return WoodenWand::create();
}

std::vector<std::tuple<Item*, int>> WoodenWandPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 6 },
	};
}

Item* WoodenWandPlans::clone()
{
	return WoodenWandPlans::create();
}

std::string WoodenWandPlans::getItemName()
{
	return WoodenWandPlans::SaveKey;
}

LocalizedString* WoodenWandPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_WoodenWand::create();
}

std::string WoodenWandPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string WoodenWandPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Wands_WoodenWand;
}

std::string WoodenWandPlans::getSerializationKey()
{
	return WoodenWandPlans::SaveKey;
}
