#include "Medusa.h"

#include "cocos/math/CCGeometry.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"
#include "Scenes/Hexus/StateOverride.h"

#include "Resources/EntityResources.h"
#include "Resources/HexusResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Medusa::MapKey = "medusa";
HexusOpponentData* Medusa::HexusOpponentDataInstance = nullptr;
const std::string Medusa::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_MEDUSA";

Medusa* Medusa::deserialize(ValueMap& properties)
{
	Medusa* instance = new Medusa(properties);

	instance->autorelease();

	return instance;
}

Medusa::Medusa(ValueMap& properties) : super(properties,
	Medusa::MapKey,
	EntityResources::Enemies_UnderflowRuins_Medusa_Animations,
	EntityResources::Enemies_UnderflowRuins_Medusa_Emblem,
	Size(224.0f, 304.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Medusa::getHexusOpponentData();
}

Medusa::~Medusa()
{
}

Vec2 Medusa::getDialogueOffset()
{
	return Vec2(-32.0f, -196.0f);
}

LocalizedString* Medusa::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_UnderflowRuins_Medusa::create();
}

HexusOpponentData* Medusa::getHexusOpponentData()
{
	if (Medusa::HexusOpponentDataInstance == nullptr)
	{
		Medusa::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameUnderflowRuins,
			Vec2(-32.0f, -196.0f),
			Medusa::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Light,
			HexusOpponentData::generateDeck(32, 0.833f,
			{

			}),
			nullptr,
			StateOverride::create(
				// Player losses
				1,
				// Enemy losses
				1,
				// Player's turn
				true,
				// Player passed
				true,
				// Enemy passed
				true,
				// Player deck
				std::vector<CardData*>
				{
					
				},
				// Enemy deck
				std::vector<CardData*>
				{
					
				},
				// Player hand
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Steal),
CardList::getInstance()->cardListByName.at(CardKeys::Kill),
CardList::getInstance()->cardListByName.at(CardKeys::ShiftRightCircular),
				},
				// Enemy hand
				std::vector<CardData*>
				{
					
				},
				// Player binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary8),
CardList::getInstance()->cardListByName.at(CardKeys::Binary8),
				},
				// Player decimal cards
				std::vector<CardData*>
				{
					
				},
				// Player hex cards
				std::vector<CardData*>
				{
					
				},
				// Enemy binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary4),
CardList::getInstance()->cardListByName.at(CardKeys::Binary4),
				},
				// Enemy decimal cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal5),
CardList::getInstance()->cardListByName.at(CardKeys::Decimal6),
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Hex8),
CardList::getInstance()->cardListByName.at(CardKeys::Hex4),
CardList::getInstance()->cardListByName.at(CardKeys::Hex4),
CardList::getInstance()->cardListByName.at(CardKeys::Hex4),
				}
			)
		);
	}

	return Medusa::HexusOpponentDataInstance;
}