#include "CopperAxe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CopperAxe::SaveKeyCopperAxe = "copper-axe";

CopperAxe* CopperAxe::create()
{
	CopperAxe* instance = new CopperAxe();

	instance->autorelease();

	return instance;
}

CopperAxe::CopperAxe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 4, 7, ItemStats(
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

CopperAxe::~CopperAxe()
{
}

Item* CopperAxe::clone()
{
	return CopperAxe::create();
}

std::string CopperAxe::getItemName()
{
	return CopperAxe::SaveKeyCopperAxe;
}

LocalizedString* CopperAxe::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_CopperAxe::create();
}

std::string CopperAxe::getIconResource()
{
	return ItemResources::Equipment_Weapons_Axes_CopperAxe;
}

std::string CopperAxe::getSerializationKey()
{
	return CopperAxe::SaveKeyCopperAxe;
}

Size CopperAxe::getWeaponCollisionSize()
{
	// As expected: Weapon width, height
	return Size(112.0f, 96.0f);
}

Vec2 CopperAxe::getWeaponOffset()
{
	// Unintuitive: x influences y position, y influences x, likely due to initial weapon rotation
	return Vec2(0.0f, 212.0f);
}
