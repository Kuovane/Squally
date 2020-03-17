#include "Hex12.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Hex12::SaveKeyHex12 = "hex-12";

Hex12* Hex12::create()
{
	Hex12* instance = new Hex12();

	instance->autorelease();

	return instance;
}

Hex12::Hex12() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(3, 3))
{
}

Hex12::~Hex12()
{
}

Item* Hex12::clone()
{
	return Hex12::create();
}

std::string Hex12::getItemName()
{
	return Hex12::SaveKeyHex12;
}

LocalizedString* Hex12::getString()
{
	return Strings::Hexus_Cards_Hex12::create();
}

std::string Hex12::getIconResource()
{
	return ItemResources::Collectables_Cards_CardHex;
}

std::string Hex12::getSerializationKey()
{
	return Hex12::SaveKeyHex12;
}

std::string Hex12::getCardKey()
{
	return CardKeys::Hex12;
}
