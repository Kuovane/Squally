#include "PrincessMittens.h"

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

const std::string PrincessMittens::MapKeyPrincessMittens = "princess-mittens";
HexusOpponentData* PrincessMittens::HexusOpponentDataInstance = nullptr;
const std::string PrincessMittens::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_PRINCESS_MITTENS";

PrincessMittens* PrincessMittens::deserialize(ValueMap& properties)
{
	PrincessMittens* instance = new PrincessMittens(properties);

	instance->autorelease();

	return instance;
}

PrincessMittens::PrincessMittens(ValueMap& properties) : super(properties,
	PrincessMittens::MapKeyPrincessMittens,
	EntityResources::Npcs_DaemonsHallow_PrincessMittens_Animations,
	EntityResources::Npcs_DaemonsHallow_PrincessMittens_Emblem,
	Size(112.0f, 160.0f),
	1.05f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = PrincessMittens::getHexusOpponentData();
}

PrincessMittens::~PrincessMittens()
{
}

Vec2 PrincessMittens::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* PrincessMittens::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_DaemonsHallow_PrincessMittens::create();
}

HexusOpponentData* PrincessMittens::getHexusOpponentData()
{
	if (PrincessMittens::HexusOpponentDataInstance == nullptr)
	{
		PrincessMittens::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameDaemonsHallow,
			Vec2(-32.0f, -112.0f),
			PrincessMittens::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Fire,
			HexusOpponentData::generateDeck(32, 0.732f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::ReturnToHand),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::Kill),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
			}),
			nullptr,
			nullptr
		);
	}

	return PrincessMittens::HexusOpponentDataInstance;
}