#include "Horus.h"

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

const std::string Horus::MapKey = "horus";
HexusOpponentData* Horus::HexusOpponentDataInstance = nullptr;
const std::string Horus::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_HORUS";

Horus* Horus::deserialize(ValueMap& properties)
{
	Horus* instance = new Horus(properties);

	instance->autorelease();

	return instance;
}

Horus::Horus(ValueMap& properties) : super(properties,
	Horus::MapKey,
	EntityResources::Npcs_UnderflowRuins_Horus_Animations,
	EntityResources::Npcs_UnderflowRuins_Horus_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Horus::getHexusOpponentData();
}

Horus::~Horus()
{
}

Vec2 Horus::getDialogueOffset()
{
	return Vec2(-32.0f, -128.0f);
}

LocalizedString* Horus::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_UnderflowRuins_Horus::create();
}

HexusOpponentData* Horus::getHexusOpponentData()
{
	if (Horus::HexusOpponentDataInstance == nullptr)
	{
		Horus::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameUnderflowRuins,
			Vec2(-32.0f, -128.0f),
			Horus::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Light,
			HexusOpponentData::generateDeck(32, 0.214f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
			}),
			nullptr,
			nullptr
		);
	}

	return Horus::HexusOpponentDataInstance;
}