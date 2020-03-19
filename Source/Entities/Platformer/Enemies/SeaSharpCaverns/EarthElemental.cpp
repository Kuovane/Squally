#include "EarthElemental.h"

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

const std::string EarthElemental::MapKey = "earth-elemental";
HexusOpponentData* EarthElemental::HexusOpponentDataInstance = nullptr;
const std::string EarthElemental::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_EARTH_ELEMENTAL";

EarthElemental* EarthElemental::deserialize(ValueMap& properties)
{
	EarthElemental* instance = new EarthElemental(properties);

	instance->autorelease();

	return instance;
}

EarthElemental::EarthElemental(ValueMap& properties) : super(properties,
	EarthElemental::MapKey,
	EntityResources::Enemies_SeaSharpCaverns_EarthElemental_Animations,
	EntityResources::Enemies_SeaSharpCaverns_EarthElemental_Emblem,
	Size(820.0f, 1480.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = EarthElemental::getHexusOpponentData();
}

EarthElemental::~EarthElemental()
{
}

Vec2 EarthElemental::getDialogueOffset()
{
	return Vec2(-32.0f, -224.0f);
}

LocalizedString* EarthElemental::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_SeaSharpCaverns_EarthElemental::create();
}

HexusOpponentData* EarthElemental::getHexusOpponentData()
{
	if (EarthElemental::HexusOpponentDataInstance == nullptr)
	{
		EarthElemental::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameSeaSharpCaverns,
			Vec2(-32.0f, -224.0f),
			EarthElemental::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
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
					CardList::getInstance()->cardListByName.at(CardKeys::Addition),
					CardList::getInstance()->cardListByName.at(CardKeys::Subtraction),
					CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal1),
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal2),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal15),
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal12),
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal12),
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					
				}
			)
		);
	}

	return EarthElemental::HexusOpponentDataInstance;
}