#include "CandySwordPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CandySwordPlans::SaveKeyCandySwordPlans = "candy-sword-plans";

CandySwordPlans* CandySwordPlans::create()
{
	CandySwordPlans* instance = new CandySwordPlans();

	instance->autorelease();

	return instance;
}

CandySwordPlans::CandySwordPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

CandySwordPlans::~CandySwordPlans()
{
}

Item* CandySwordPlans::craft()
{
	return CandySword::create();
}

std::map<Item*, int> CandySwordPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* CandySwordPlans::clone()
{
	return CandySwordPlans::create();
}

std::string CandySwordPlans::getItemName()
{
	return CandySwordPlans::SaveKeyCandySwordPlans;
}

LocalizedString* CandySwordPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_CandySword::create();
}

std::string CandySwordPlans::getIconResource()
{
	return ObjectResources::Items_Crafting_SCROLL_1;
}

std::string CandySwordPlans::getCraftedItemIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Swords_CandySword;
}

std::string CandySwordPlans::getSerializationKey()
{
	return CandySwordPlans::SaveKeyCandySwordPlans;
}
