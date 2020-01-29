#include "Decimal7.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Decimal7::SaveKeyDecimal7 = "decimal-7";

Decimal7* Decimal7::create()
{
	Decimal7* instance = new Decimal7();

	instance->autorelease();

	return instance;
}

Decimal7::Decimal7() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(3, 3))
{
}

Decimal7::~Decimal7()
{
}

Item* Decimal7::clone()
{
	return Decimal7::create();
}

std::string Decimal7::getItemName()
{
	return Decimal7::SaveKeyDecimal7;
}

LocalizedString* Decimal7::getString()
{
	return Strings::Hexus_Cards_Decimal7::create();
}

std::string Decimal7::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardDecimal;
}

std::string Decimal7::getSerializationKey()
{
	return Decimal7::SaveKeyDecimal7;
}

std::string Decimal7::getCardKey()
{
	return CardKeys::Decimal7;
}
