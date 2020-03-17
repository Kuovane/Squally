#include "BattleSword.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string BattleSword::SaveKeyBattleSword = "battle-sword";

BattleSword* BattleSword::create()
{
	BattleSword* instance = new BattleSword();

	instance->autorelease();

	return instance;
}

BattleSword::BattleSword() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 24, 32, ItemStats(
	// Health
	0,
	// Mana
	0,
	// Attack
	0,
	// Armor
	0,
	// Speed
	0.05f
))
{
}

BattleSword::~BattleSword()
{
}

Item* BattleSword::clone()
{
	return BattleSword::create();
}

std::string BattleSword::getItemName()
{
	return BattleSword::SaveKeyBattleSword;
}

LocalizedString* BattleSword::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_BattleSword::create();
}

std::string BattleSword::getIconResource()
{
	return ItemResources::Equipment_Weapons_Swords_BattleSword;
}

std::string BattleSword::getSerializationKey()
{
	return BattleSword::SaveKeyBattleSword;
}
