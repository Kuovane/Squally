#include "WoodenMallet.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Items/Equipment/Weapons/Maces/WoodenMallet.h"

using namespace cocos2d;

const std::string WoodenMallet::SaveKeyWoodenMallet = "wooden-mallet";

WoodenMallet* WoodenMallet::create()
{
	WoodenMallet* instance = new WoodenMallet();

	instance->autorelease();

	return instance;
}

WoodenMallet::WoodenMallet() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 2 }}), 3, 6)
{
}

WoodenMallet::~WoodenMallet()
{
}

Item* WoodenMallet::clone()
{
	return WoodenMallet::create();
}

std::string WoodenMallet::getItemName()
{
	return WoodenMallet::SaveKeyWoodenMallet;
}

LocalizedString* WoodenMallet::getString()
{
	return Strings::Items_Equipment_Weapons_Maces_WoodenMallet::create();
}

std::string WoodenMallet::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Maces_WoodenMallet;
}

std::string WoodenMallet::getSerializationKey()
{
	return WoodenMallet::SaveKeyWoodenMallet;
}

Vec2 WoodenMallet::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}