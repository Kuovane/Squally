#include "Minotaur.h"

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

const std::string Minotaur::MapKeyMinotaur = "minotaur";
HexusOpponentData* Minotaur::HexusOpponentDataInstance = nullptr;
const std::string Minotaur::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_MINOTAUR";

Minotaur* Minotaur::deserialize(ValueMap& properties)
{
	Minotaur* instance = new Minotaur(properties);

	instance->autorelease();

	return instance;
}

Minotaur::Minotaur(ValueMap& properties) : super(properties,
	Minotaur::MapKeyMinotaur,
	EntityResources::Enemies_UnderflowRuins_Minotaur_Animations,
	EntityResources::Enemies_UnderflowRuins_Minotaur_Emblem,
	Size(278.0f, 288.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Minotaur::getHexusOpponentData();
}

Minotaur::~Minotaur()
{
}

Vec2 Minotaur::getDialogueOffset()
{
	return Vec2(-48.0f, -196.0f);
}

LocalizedString* Minotaur::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_UnderflowRuins_Minotaur::create();
}

HexusOpponentData* Minotaur::getHexusOpponentData()
{
	if (Minotaur::HexusOpponentDataInstance == nullptr)
	{
		Minotaur::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameUnderflowRuins,
			Vec2(-48.0f, -196.0f),
			Minotaur::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Light,
			HexusOpponentData::generateDeck(32, 0.667f,
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
					CardList::getInstance()->cardListByName.at(CardKeys::Flip4),
					CardList::getInstance()->cardListByName.at(CardKeys::Flip3),
					CardList::getInstance()->cardListByName.at(CardKeys::Flip2),
				},
				// Enemy hand
				std::vector<CardData*>
				{
					
				},
				// Player binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary13),
					CardList::getInstance()->cardListByName.at(CardKeys::Binary13),
				},
				// Player decimal cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal8),
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal8),
				},
				// Player hex cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Hex6),
					CardList::getInstance()->cardListByName.at(CardKeys::Hex4),
					CardList::getInstance()->cardListByName.at(CardKeys::Hex6),
				},
				// Enemy binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary2),
					CardList::getInstance()->cardListByName.at(CardKeys::Binary10),
					CardList::getInstance()->cardListByName.at(CardKeys::Binary2),
				},
				// Enemy decimal cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal7),
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal13),
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal13),
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal7),
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Hex3),
					CardList::getInstance()->cardListByName.at(CardKeys::Hex3),
					CardList::getInstance()->cardListByName.at(CardKeys::Hex13),
					CardList::getInstance()->cardListByName.at(CardKeys::Hex13),
					CardList::getInstance()->cardListByName.at(CardKeys::Hex13),
					CardList::getInstance()->cardListByName.at(CardKeys::Hex2),
					CardList::getInstance()->cardListByName.at(CardKeys::Hex2),
				}
			)
		);
	}

	return Minotaur::HexusOpponentDataInstance;
}