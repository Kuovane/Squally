#include "Hex15.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Hexus/Cards/Hex15.h"

using namespace cocos2d;

const std::string Hex15::SaveKeyHex15 = "hex-15";

Hex15* Hex15::create()
{
	Hex15* instance = new Hex15();

	instance->autorelease();

	return instance;
}

Hex15::Hex15() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}))
{
}

Hex15::~Hex15()
{
}

Item* Hex15::clone()
{
	return Hex15::create();
}

std::string Hex15::getItemName()
{
	return Hex15::SaveKeyHex15;
}

LocalizedString* Hex15::getString()
{
	return Strings::Hexus_Cards_Hex15::create();
}

std::string Hex15::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardHex;
}

std::string Hex15::getSerializationKey()
{
	return Hex15::SaveKeyHex15;
}
