#include "Matu.h"

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

const std::string Matu::MapKeyMatu = "matu";
HexusOpponentData* Matu::HexusOpponentDataInstance = nullptr;
const std::string Matu::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_PRINCESS_MATU";

Matu* Matu::deserialize(ValueMap& properties)
{
	Matu* instance = new Matu(properties);

	instance->autorelease();

	return instance;
}

Matu::Matu(ValueMap& properties) : super(properties,
	Matu::MapKeyMatu,
	EntityResources::Npcs_EndianForest_Matu_Animations,
	EntityResources::Npcs_EndianForest_Matu_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Matu::getHexusOpponentData();
}

Matu::~Matu()
{
}

Vec2 Matu::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Matu::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_EndianForest_Matu::create();
}

HexusOpponentData* Matu::getHexusOpponentData()
{
	if (Matu::HexusOpponentDataInstance == nullptr)
	{
		Matu::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameEndianForest,
			Vec2(-32.0f, -112.0f),
			Matu::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			HexusOpponentData::generateDeck(32, 0.045f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
			}),
			nullptr,
			nullptr
		);
	}

	return Matu::HexusOpponentDataInstance;
}