#include "Magnus.h"

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

const std::string Magnus::MapKey = "magnus";
HexusOpponentData* Magnus::HexusOpponentDataInstance = nullptr;
const std::string Magnus::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_MAGNUS";

Magnus* Magnus::deserialize(ValueMap& properties)
{
	Magnus* instance = new Magnus(properties);

	instance->autorelease();

	return instance;
}

Magnus::Magnus(ValueMap& properties) : super(properties,
	Magnus::MapKey,
	EntityResources::Npcs_DaemonsHallow_Magnus_Animations,
	EntityResources::Npcs_DaemonsHallow_Magnus_Emblem,
	Size(112.0f, 160.0f),
	0.85f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Magnus::getHexusOpponentData();
}

Magnus::~Magnus()
{
}

Vec2 Magnus::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Magnus::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_DaemonsHallow_Magnus::create();
}

HexusOpponentData* Magnus::getHexusOpponentData()
{
	if (Magnus::HexusOpponentDataInstance == nullptr)
	{
		Magnus::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameDaemonsHallow,
			Vec2(-32.0f, -112.0f),
			Magnus::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Fire,
			HexusOpponentData::generateDeck(32, 0.714f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip2),
				CardList::getInstance()->cardListByName.at(CardKeys::Kill),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::ReturnToHand),
				CardList::getInstance()->cardListByName.at(CardKeys::Kill),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip3),
			}),
			nullptr,
			nullptr
		);
	}

	return Magnus::HexusOpponentDataInstance;
}