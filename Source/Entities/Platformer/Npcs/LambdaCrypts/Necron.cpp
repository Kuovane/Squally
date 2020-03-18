#include "Necron.h"

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

const std::string Necron::MapKeyNecron = "necron";
HexusOpponentData* Necron::HexusOpponentDataInstance = nullptr;
const std::string Necron::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_NECRON";

Necron* Necron::deserialize(ValueMap& properties)
{
	Necron* instance = new Necron(properties);

	instance->autorelease();

	return instance;
}

Necron::Necron(ValueMap& properties) : super(properties,
	Necron::MapKeyNecron,
	EntityResources::Npcs_LambdaCrypts_Necron_Animations,
	EntityResources::Npcs_LambdaCrypts_Necron_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Necron::getHexusOpponentData();
}

Necron::~Necron()
{
}

Vec2 Necron::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Necron::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_LambdaCrypts_Necron::create();
}

HexusOpponentData* Necron::getHexusOpponentData()
{
	if (Necron::HexusOpponentDataInstance == nullptr)
	{
		Necron::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameLambdaCrypts,
			Vec2(-32.0f, -112.0f),
			Necron::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			HexusOpponentData::generateDeck(32, 0.804f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::Inverse),
				CardList::getInstance()->cardListByName.at(CardKeys::Subtraction),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
			}),
			nullptr,
			nullptr
		);
	}

	return Necron::HexusOpponentDataInstance;
}