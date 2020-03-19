#include "Leopold.h"

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

const std::string Leopold::MapKey = "leopold";
HexusOpponentData* Leopold::HexusOpponentDataInstance = nullptr;
const std::string Leopold::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_LEOPOLD";

Leopold* Leopold::deserialize(ValueMap& properties)
{
	Leopold* instance = new Leopold(properties);

	instance->autorelease();

	return instance;
}

Leopold::Leopold(ValueMap& properties) : super(properties,
	Leopold::MapKey,
	EntityResources::Npcs_CastleValgrind_Leopold_Animations,
	EntityResources::Npcs_CastleValgrind_Leopold_Emblem,
	Size(112.0f, 160.0f),
	0.95f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Leopold::getHexusOpponentData();
}

Leopold::~Leopold()
{
}

Vec2 Leopold::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Leopold::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_CastleValgrind_Leopold::create();
}

HexusOpponentData* Leopold::getHexusOpponentData()
{
	if (Leopold::HexusOpponentDataInstance == nullptr)
	{
		Leopold::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameCastleValgrind,
			Vec2(-32.0f, -112.0f),
			Leopold::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Air,
			HexusOpponentData::generateDeck(32, 0.491f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::ReturnToHand),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::Addition),
			}),
			nullptr,
			nullptr
		);
	}

	return Leopold::HexusOpponentDataInstance;
}