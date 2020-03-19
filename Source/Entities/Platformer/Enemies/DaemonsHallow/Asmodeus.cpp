#include "Asmodeus.h"

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

const std::string Asmodeus::MapKey = "asmodeus";
HexusOpponentData* Asmodeus::HexusOpponentDataInstance = nullptr;
const std::string Asmodeus::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ASMODEUS";

Asmodeus* Asmodeus::deserialize(ValueMap& properties)
{
	Asmodeus* instance = new Asmodeus(properties);

	instance->autorelease();

	return instance;
}

Asmodeus::Asmodeus(ValueMap& properties) : super(properties,
	Asmodeus::MapKey,
	EntityResources::Enemies_DaemonsHallow_Asmodeus_Animations,
	EntityResources::Enemies_DaemonsHallow_Asmodeus_Emblem,
	Size(480.0f, 480.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Asmodeus::getHexusOpponentData();
}

Asmodeus::~Asmodeus()
{
}

Vec2 Asmodeus::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Asmodeus::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_DaemonsHallow_Asmodeus::create();
}

HexusOpponentData* Asmodeus::getHexusOpponentData()
{
	if (Asmodeus::HexusOpponentDataInstance == nullptr)
	{
		Asmodeus::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameDaemonsHallow,
			Vec2(-32.0f, -112.0f),
			Asmodeus::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Fire,
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

	return Asmodeus::HexusOpponentDataInstance;
}