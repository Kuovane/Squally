#include "Amelia.h"

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

const std::string Amelia::MapKey = "amelia";
HexusOpponentData* Amelia::HexusOpponentDataInstance = nullptr;
const std::string Amelia::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_AMELIA";

Amelia* Amelia::deserialize(ValueMap& properties)
{
	Amelia* instance = new Amelia(properties);

	instance->autorelease();

	return instance;
}

Amelia::Amelia(ValueMap& properties) : super(properties,
	Amelia::MapKey,
	EntityResources::Npcs_LambdaCrypts_Amelia_Animations,
	EntityResources::Npcs_LambdaCrypts_Amelia_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Amelia::getHexusOpponentData();
}

Amelia::~Amelia()
{
}

Vec2 Amelia::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Amelia::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_LambdaCrypts_Amelia::create();
}

HexusOpponentData* Amelia::getHexusOpponentData()
{
	if (Amelia::HexusOpponentDataInstance == nullptr)
	{
		Amelia::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameLambdaCrypts,
			Vec2(-32.0f, -112.0f),
			Amelia::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			HexusOpponentData::generateDeck(32, 0.759f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::Addition),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::Kill),
				CardList::getInstance()->cardListByName.at(CardKeys::BonusMoves),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::Subtraction),
			}),
			nullptr,
			nullptr
		);
	}

	return Amelia::HexusOpponentDataInstance;
}