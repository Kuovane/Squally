#include "RoseEarrings.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string RoseEarrings::SaveKey = "rose-earrings";

RoseEarrings* RoseEarrings::create()
{
	RoseEarrings* instance = new RoseEarrings();

	instance->autorelease();

	return instance;
}

RoseEarrings::RoseEarrings() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 23 }}), ItemStats(
	// Health
	0,
	// Mana
	2,
	// Attack
	0,
	// Magic Attack
	0,
	// Armor
	0,
	// Speed
	0.05f
))
{
}

RoseEarrings::~RoseEarrings()
{
}

Item* RoseEarrings::clone()
{
	return RoseEarrings::create();
}

std::string RoseEarrings::getItemName()
{
	return RoseEarrings::SaveKey;
}

LocalizedString* RoseEarrings::getString()
{
	return Strings::Items_Equipment_Gear_Earrings_RoseEarrings::create();
}

std::string RoseEarrings::getIconResource()
{
	return ItemResources::Equipment_Gear_Earrings_RoseEarrings;
}

std::string RoseEarrings::getSerializationKey()
{
	return RoseEarrings::SaveKey;
}
