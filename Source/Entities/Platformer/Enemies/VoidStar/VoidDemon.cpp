#include "VoidDemon.h"

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

const std::string VoidDemon::MapKeyVoidDemon = "void-demon";
HexusOpponentData* VoidDemon::HexusOpponentDataInstance = nullptr;
const std::string VoidDemon::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_VOID_DEMON";

VoidDemon* VoidDemon::deserialize(ValueMap& properties)
{
	VoidDemon* instance = new VoidDemon(properties);

	instance->autorelease();

	return instance;
}

VoidDemon::VoidDemon(ValueMap& properties) : super(properties,
	VoidDemon::MapKeyVoidDemon,
	EntityResources::Enemies_VoidStar_VoidDemon_Animations,
	EntityResources::Enemies_VoidStar_VoidDemon_Emblem,
	Size(338.0f, 342.0f),
	0.7f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = VoidDemon::getHexusOpponentData();
}

VoidDemon::~VoidDemon()
{
}

Vec2 VoidDemon::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* VoidDemon::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_VoidStar_VoidDemon::create();
}

HexusOpponentData* VoidDemon::getHexusOpponentData()
{
	if (VoidDemon::HexusOpponentDataInstance == nullptr)
	{
		VoidDemon::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameVoidStar,
			Vec2(-32.0f, -112.0f),
			VoidDemon::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			HexusOpponentData::generateDeck(32, 0.083f,
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

	return VoidDemon::HexusOpponentDataInstance;
}