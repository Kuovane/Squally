#include "Azmus.h"

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

const std::string Azmus::MapKey = "azmus";
HexusOpponentData* Azmus::HexusOpponentDataInstance = nullptr;
const std::string Azmus::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_AZMUS";

Azmus* Azmus::deserialize(ValueMap& properties)
{
	Azmus* instance = new Azmus(properties);

	instance->autorelease();

	return instance;
}

Azmus::Azmus(ValueMap& properties) : super(properties,
	Azmus::MapKey,
	EntityResources::Npcs_LambdaCrypts_Azmus_Animations,
	EntityResources::Npcs_LambdaCrypts_Azmus_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Azmus::getHexusOpponentData();
}

Azmus::~Azmus()
{
}

Vec2 Azmus::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Azmus::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_LambdaCrypts_Azmus::create();
}

HexusOpponentData* Azmus::getHexusOpponentData()
{
	if (Azmus::HexusOpponentDataInstance == nullptr)
	{
		Azmus::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameLambdaCrypts,
			Vec2(-32.0f, -112.0f),
			Azmus::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			HexusOpponentData::generateDeck(32, 0.768f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::SuddenDeath),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
			}),
			nullptr,
			nullptr
		);
	}

	return Azmus::HexusOpponentDataInstance;
}