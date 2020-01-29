#include "FireAxe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string FireAxe::SaveKeyFireAxe = "fire-axe";

FireAxe* FireAxe::create()
{
	FireAxe* instance = new FireAxe();

	instance->autorelease();

	return instance;
}

FireAxe::FireAxe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 4, 7, ItemStats(
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

FireAxe::~FireAxe()
{
}

Item* FireAxe::clone()
{
	return FireAxe::create();
}

std::string FireAxe::getItemName()
{
	return FireAxe::SaveKeyFireAxe;
}

LocalizedString* FireAxe::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_FireAxe::create();
}

std::string FireAxe::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Axes_FireAxe;
}

std::string FireAxe::getSerializationKey()
{
	return FireAxe::SaveKeyFireAxe;
}

Size FireAxe::getWeaponCollisionSize()
{
	// As expected: Weapon width, height
	return Size(112.0f, 96.0f);
}

Vec2 FireAxe::getWeaponOffset()
{
	// Unintuitive: x influences y position, y influences x, likely due to initial weapon rotation
	return Vec2(0.0f, 212.0f);
}
