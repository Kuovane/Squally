#include "GoldenAxe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GoldenAxe::SaveKeyGoldenAxe = "golden-axe";

GoldenAxe* GoldenAxe::create()
{
	GoldenAxe* instance = new GoldenAxe();

	instance->autorelease();

	return instance;
}

GoldenAxe::GoldenAxe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 4, 7, ItemStats(
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

GoldenAxe::~GoldenAxe()
{
}

Item* GoldenAxe::clone()
{
	return GoldenAxe::create();
}

std::string GoldenAxe::getItemName()
{
	return GoldenAxe::SaveKeyGoldenAxe;
}

LocalizedString* GoldenAxe::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_GoldenAxe::create();
}

std::string GoldenAxe::getIconResource()
{
	return ItemResources::Equipment_Weapons_Axes_GoldenAxe;
}

std::string GoldenAxe::getSerializationKey()
{
	return GoldenAxe::SaveKeyGoldenAxe;
}

Size GoldenAxe::getWeaponCollisionSize()
{
	// As expected: Weapon width, height
	return Size(112.0f, 96.0f);
}

Vec2 GoldenAxe::getWeaponOffset()
{
	// Unintuitive: x influences y position, y influences x, likely due to initial weapon rotation
	return Vec2(0.0f, 212.0f);
}
