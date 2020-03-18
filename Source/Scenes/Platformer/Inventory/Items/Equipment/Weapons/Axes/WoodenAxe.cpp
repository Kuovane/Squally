#include "WoodenAxe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WoodenAxe::SaveKeyWoodenAxe = "wooden-axe";

WoodenAxe* WoodenAxe::create()
{
	WoodenAxe* instance = new WoodenAxe();

	instance->autorelease();

	return instance;
}

WoodenAxe::WoodenAxe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 4, 7, ItemStats(
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

WoodenAxe::~WoodenAxe()
{
}

Item* WoodenAxe::clone()
{
	return WoodenAxe::create();
}

std::string WoodenAxe::getItemName()
{
	return WoodenAxe::SaveKeyWoodenAxe;
}

LocalizedString* WoodenAxe::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_WoodenAxe::create();
}

std::string WoodenAxe::getIconResource()
{
	return ItemResources::Equipment_Weapons_Axes_WoodenAxe;
}

std::string WoodenAxe::getSerializationKey()
{
	return WoodenAxe::SaveKeyWoodenAxe;
}

Size WoodenAxe::getWeaponCollisionSize()
{
	// As expected: Weapon width, height
	return Size(112.0f, 96.0f);
}

Vec2 WoodenAxe::getWeaponOffset()
{
	// Unintuitive: x influences y position, y influences x, likely due to initial weapon rotation
	return Vec2(0.0f, 212.0f);
}
