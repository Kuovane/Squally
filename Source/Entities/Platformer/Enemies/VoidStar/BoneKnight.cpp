#include "BoneKnight.h"

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

const std::string BoneKnight::MapKeyBoneKnight = "bone-knight";
HexusOpponentData* BoneKnight::HexusOpponentDataInstance = nullptr;
const std::string BoneKnight::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_BONE_KNIGHT";

BoneKnight* BoneKnight::deserialize(ValueMap& properties)
{
	BoneKnight* instance = new BoneKnight(properties);

	instance->autorelease();

	return instance;
}

BoneKnight::BoneKnight(ValueMap& properties) : super(properties,
	BoneKnight::MapKeyBoneKnight,
	EntityResources::Enemies_VoidStar_BoneKnight_Animations,
	EntityResources::Enemies_VoidStar_BoneKnight_Emblem,
	Size(540.0f, 340.0f),
	1.0f,
	Vec2(-64.0f, 0.0f))
{
	this->hexusOpponentData = BoneKnight::getHexusOpponentData();
}

BoneKnight::~BoneKnight()
{
}

Vec2 BoneKnight::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* BoneKnight::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_VoidStar_BoneKnight::create();
}

HexusOpponentData* BoneKnight::getHexusOpponentData()
{
	if (BoneKnight::HexusOpponentDataInstance == nullptr)
	{
		BoneKnight::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameVoidStar,
			Vec2(-32.0f, -112.0f),
			BoneKnight::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
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

	return BoneKnight::HexusOpponentDataInstance;
}