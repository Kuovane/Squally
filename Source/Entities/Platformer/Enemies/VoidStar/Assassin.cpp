#include "Assassin.h"

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

const std::string Assassin::MapKeyAssassin = "assassin";
HexusOpponentData* Assassin::HexusOpponentDataInstance = nullptr;
const std::string Assassin::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ASSASSIN";

Assassin* Assassin::deserialize(ValueMap& properties)
{
	Assassin* instance = new Assassin(properties);

	instance->autorelease();

	return instance;
}

Assassin::Assassin(ValueMap& properties) : super(properties,
	Assassin::MapKeyAssassin,
	EntityResources::Enemies_VoidStar_Assassin_Animations,
	EntityResources::Enemies_VoidStar_Assassin_Emblem,
	Size(278.0f, 288.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Assassin::getHexusOpponentData();
}

Assassin::~Assassin()
{
}

Vec2 Assassin::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Assassin::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_VoidStar_Assassin::create();
}

HexusOpponentData* Assassin::getHexusOpponentData()
{
	if (Assassin::HexusOpponentDataInstance == nullptr)
	{
		Assassin::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameVoidStar,
			Vec2(-32.0f, -112.0f),
			Assassin::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
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

	return Assassin::HexusOpponentDataInstance;
}