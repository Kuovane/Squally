#include "Guano.h"

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

const std::string Guano::MapKey = "guano";
HexusOpponentData* Guano::HexusOpponentDataInstance = nullptr;
const std::string Guano::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_GUANO";

Guano* Guano::deserialize(ValueMap& properties)
{
	Guano* instance = new Guano(properties);

	instance->autorelease();

	return instance;
}

Guano::Guano(ValueMap& properties) : super(properties,
	Guano::MapKey,
	EntityResources::Helpers_EndianForest_Guano_Animations,
	EntityResources::Helpers_EndianForest_Guano_Emblem,
	Size(224.0f, 440.0f),
	0.3f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Guano::getHexusOpponentData();
}

Guano::~Guano()
{
}

Vec2 Guano::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Guano::getEntityName()
{
	return Strings::Platformer_Entities_Names_Helpers_EndianForest_Guano::create();
}

HexusOpponentData* Guano::getHexusOpponentData()
{
	if (Guano::HexusOpponentDataInstance == nullptr)
	{
		Guano::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameEndianForest,
			Vec2(-32.0f, -112.0f),
			Guano::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			HexusOpponentData::generateDeck(32, 1.000f,
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
					
				}
			)
		);
	}

	return Guano::HexusOpponentDataInstance;
}