#include "Viper.h"

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

const std::string Viper::MapKey = "viper";
HexusOpponentData* Viper::HexusOpponentDataInstance = nullptr;
const std::string Viper::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_VIPER";

Viper* Viper::deserialize(ValueMap& properties)
{
	Viper* instance = new Viper(properties);

	instance->autorelease();

	return instance;
}

Viper::Viper(ValueMap& properties) : super(properties,
	Viper::MapKey,
	EntityResources::Npcs_LambdaCrypts_Viper_Animations,
	EntityResources::Npcs_LambdaCrypts_Viper_Emblem,
	Size(112.0f, 160.0f),
	0.85f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Viper::getHexusOpponentData();
}

Viper::~Viper()
{
}

Vec2 Viper::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Viper::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_LambdaCrypts_Viper::create();
}

HexusOpponentData* Viper::getHexusOpponentData()
{
	if (Viper::HexusOpponentDataInstance == nullptr)
	{
		Viper::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameLambdaCrypts,
			Vec2(-32.0f, -112.0f),
			Viper::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			HexusOpponentData::generateDeck(32, 0.848f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::SuddenDeath),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::ReturnToHand),
				CardList::getInstance()->cardListByName.at(CardKeys::Subtraction),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip3),
				CardList::getInstance()->cardListByName.at(CardKeys::SuddenDeath),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
			}),
			nullptr,
			nullptr
		);
	}

	return Viper::HexusOpponentDataInstance;
}