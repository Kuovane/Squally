#include "IronAxe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string IronAxe::SaveKeyIronAxe = "iron-axe";

IronAxe* IronAxe::create()
{
	IronAxe* instance = new IronAxe();

	instance->autorelease();

	return instance;
}

IronAxe::IronAxe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 5 }}), 4, 6, ItemStats(
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

IronAxe::~IronAxe()
{
}

Item* IronAxe::clone()
{
	return IronAxe::create();
}

std::string IronAxe::getItemName()
{
	return IronAxe::SaveKeyIronAxe;
}

LocalizedString* IronAxe::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_IronAxe::create();
}

std::string IronAxe::getIconResource()
{
	return ItemResources::Equipment_Weapons_Axes_IronAxe;
}

std::string IronAxe::getSerializationKey()
{
	return IronAxe::SaveKeyIronAxe;
}

Size IronAxe::getWeaponCollisionSize()
{
	// As expected: Weapon width, height
	return Size(112.0f, 96.0f);
}

Vec2 IronAxe::getWeaponOffset()
{
	// Unintuitive: x influences y position, y influences x, likely due to initial weapon rotation
	return Vec2(0.0f, 212.0f);
}
