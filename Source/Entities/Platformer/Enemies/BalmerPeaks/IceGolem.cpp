#include "IceGolem.h"

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

const std::string IceGolem::MapKeyIceGolem = "ice-golem";
HexusOpponentData* IceGolem::HexusOpponentDataInstance = nullptr;
const std::string IceGolem::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ICE_GOLEM";

IceGolem* IceGolem::deserialize(ValueMap& properties)
{
	IceGolem* instance = new IceGolem(properties);

	instance->autorelease();

	return instance;
}

IceGolem::IceGolem(ValueMap& properties) : super(properties,
	IceGolem::MapKeyIceGolem,
	EntityResources::Enemies_BalmerPeaks_IceGolem_Animations,
	EntityResources::Enemies_BalmerPeaks_IceGolem_Emblem,
	Size(256.0f, 224.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = IceGolem::getHexusOpponentData();
}

IceGolem::~IceGolem()
{
}

Vec2 IceGolem::getDialogueOffset()
{
	return Vec2(-32.0f, -160.0f);
}

LocalizedString* IceGolem::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_BalmerPeaks_IceGolem::create();
}

HexusOpponentData* IceGolem::getHexusOpponentData()
{
	if (IceGolem::HexusOpponentDataInstance == nullptr)
	{
		IceGolem::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameBalmerPeaks,
			Vec2(-32.0f, -160.0f),
			IceGolem::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Water,
			HexusOpponentData::generateDeck(32, 0.333f,
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
					CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
					CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
					CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
					CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
					CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				},
				// Enemy hand
				std::vector<CardData*>
				{
					
				},
				// Player binary cards
				std::vector<CardData*>
				{
					
				},
				// Player decimal cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary5),
				},
				// Player hex cards
				std::vector<CardData*>
				{
					
				},
				// Enemy binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary5),
					CardList::getInstance()->cardListByName.at(CardKeys::Binary10),
					CardList::getInstance()->cardListByName.at(CardKeys::Binary4),
				},
				// Enemy decimal cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary10),
					CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					
				}
			)
		);
	}

	return IceGolem::HexusOpponentDataInstance;
}