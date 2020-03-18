#include "MummyPriest.h"

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

const std::string MummyPriest::MapKeyMummyPriest = "mummy-priest";
HexusOpponentData* MummyPriest::HexusOpponentDataInstance = nullptr;
const std::string MummyPriest::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_MUMMY_PRIEST";

MummyPriest* MummyPriest::deserialize(ValueMap& properties)
{
	MummyPriest* instance = new MummyPriest(properties);

	instance->autorelease();

	return instance;
}

MummyPriest::MummyPriest(ValueMap& properties) : super(properties,
	MummyPriest::MapKeyMummyPriest,
	EntityResources::Enemies_UnderflowRuins_MummyPriest_Animations,
	EntityResources::Enemies_UnderflowRuins_MummyPriest_Emblem,
	Size(128.0f, 256.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = MummyPriest::getHexusOpponentData();
}

MummyPriest::~MummyPriest()
{
}

Vec2 MummyPriest::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* MummyPriest::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_UnderflowRuins_MummyPriest::create();
}

HexusOpponentData* MummyPriest::getHexusOpponentData()
{
	if (MummyPriest::HexusOpponentDataInstance == nullptr)
	{
		MummyPriest::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameUnderflowRuins,
			Vec2(-32.0f, -112.0f),
			MummyPriest::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Light,
			HexusOpponentData::generateDeck(32, 0.417f,
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
					CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeftCircular),
					CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				},
				// Enemy hand
				std::vector<CardData*>
				{
					
				},
				// Player binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary10),
					CardList::getInstance()->cardListByName.at(CardKeys::Binary7),
					CardList::getInstance()->cardListByName.at(CardKeys::Binary7),
					CardList::getInstance()->cardListByName.at(CardKeys::Binary7),
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
					
				},
				// Enemy decimal cards
				std::vector<CardData*>
				{
					
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Hex15),
					CardList::getInstance()->cardListByName.at(CardKeys::Hex15),
					CardList::getInstance()->cardListByName.at(CardKeys::Hex15),
				}
			)
		);
	}

	return MummyPriest::HexusOpponentDataInstance;
}