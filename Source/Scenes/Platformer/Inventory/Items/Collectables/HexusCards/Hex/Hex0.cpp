#include "Hex0.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Hex0::SaveKeyHex0 = "hex-0";

Hex0* Hex0::create()
{
	Hex0* instance = new Hex0();

	instance->autorelease();

	return instance;
}

Hex0::Hex0() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}), ItemMeta(3, 3))
{
}

Hex0::~Hex0()
{
}

Item* Hex0::clone()
{
	return Hex0::create();
}

std::string Hex0::getItemName()
{
	return Hex0::SaveKeyHex0;
}

LocalizedString* Hex0::getString()
{
	return Strings::Hexus_Cards_Hex0::create();
}

std::string Hex0::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardHex;
}

std::string Hex0::getSerializationKey()
{
	return Hex0::SaveKeyHex0;
}

std::string Hex0::getCardKey()
{
	return CardKeys::Hex0;
}
