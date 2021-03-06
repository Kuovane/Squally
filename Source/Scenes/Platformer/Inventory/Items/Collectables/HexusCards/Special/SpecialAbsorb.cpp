#include "SpecialAbsorb.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SpecialAbsorb::SaveKey = "special-absorb";

SpecialAbsorb* SpecialAbsorb::create()
{
	SpecialAbsorb* instance = new SpecialAbsorb();

	instance->autorelease();

	return instance;
}

SpecialAbsorb::SpecialAbsorb() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 14 }}), ItemMeta(3, 3))
{
}

SpecialAbsorb::~SpecialAbsorb()
{
}

Item* SpecialAbsorb::clone()
{
	return SpecialAbsorb::create();
}

std::string SpecialAbsorb::getItemName()
{
	return SpecialAbsorb::SaveKey;
}

LocalizedString* SpecialAbsorb::getString()
{
	return Strings::Hexus_Cards_Absorb::create();
}

std::string SpecialAbsorb::getIconResource()
{
	return ItemResources::Collectables_Cards_CardSpecial;
}

std::string SpecialAbsorb::getSerializationKey()
{
	return SpecialAbsorb::SaveKey;
}

std::string SpecialAbsorb::getCardKey()
{
	return CardKeys::Addition;
}
