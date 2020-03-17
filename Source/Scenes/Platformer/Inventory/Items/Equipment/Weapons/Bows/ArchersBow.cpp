#include "ArchersBow.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ArchersBow::SaveKeyArchersBow = "archers-bow";

ArchersBow* ArchersBow::create()
{
	ArchersBow* instance = new ArchersBow();

	instance->autorelease();

	return instance;
}

ArchersBow::ArchersBow() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 24, 32, ItemStats(
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

ArchersBow::~ArchersBow()
{
}

Item* ArchersBow::clone()
{
	return ArchersBow::create();
}

std::string ArchersBow::getItemName()
{
	return ArchersBow::SaveKeyArchersBow;
}

LocalizedString* ArchersBow::getString()
{
	return Strings::Items_Equipment_Weapons_Bows_ArchersBow::create();
}

std::string ArchersBow::getIconResource()
{
	return ItemResources::Equipment_Weapons_Bows_ArchersBow;
}

std::string ArchersBow::getSerializationKey()
{
	return ArchersBow::SaveKeyArchersBow;
}

Vec2 ArchersBow::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
