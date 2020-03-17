#include "Hex8.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Hex8::SaveKeyHex8 = "hex-8";

Hex8* Hex8::create()
{
	Hex8* instance = new Hex8();

	instance->autorelease();

	return instance;
}

Hex8::Hex8() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(3, 3))
{
}

Hex8::~Hex8()
{
}

Item* Hex8::clone()
{
	return Hex8::create();
}

std::string Hex8::getItemName()
{
	return Hex8::SaveKeyHex8;
}

LocalizedString* Hex8::getString()
{
	return Strings::Hexus_Cards_Hex8::create();
}

std::string Hex8::getIconResource()
{
	return ItemResources::Collectables_Cards_CardHex;
}

std::string Hex8::getSerializationKey()
{
	return Hex8::SaveKeyHex8;
}

std::string Hex8::getCardKey()
{
	return CardKeys::Hex8;
}
