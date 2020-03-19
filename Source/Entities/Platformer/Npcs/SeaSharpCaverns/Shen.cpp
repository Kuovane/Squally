#include "Shen.h"

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

const std::string Shen::MapKey = "shen";
HexusOpponentData* Shen::HexusOpponentDataInstance = nullptr;
const std::string Shen::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_SHEN";

Shen* Shen::deserialize(ValueMap& properties)
{
	Shen* instance = new Shen(properties);

	instance->autorelease();

	return instance;
}

Shen::Shen(ValueMap& properties) : super(properties,
	Shen::MapKey,
	EntityResources::Npcs_SeaSharpCaverns_Shen_Animations,
	EntityResources::Npcs_SeaSharpCaverns_Shen_Emblem,
	Size(112.0f, 160.0f),
	1.05f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Shen::getHexusOpponentData();
}

Shen::~Shen()
{
}

Vec2 Shen::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Shen::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_SeaSharpCaverns_Shen::create();
}

HexusOpponentData* Shen::getHexusOpponentData()
{
	if (Shen::HexusOpponentDataInstance == nullptr)
	{
		Shen::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameSeaSharpCaverns,
			Vec2(-32.0f, -112.0f),
			Shen::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			HexusOpponentData::generateDeck(32, 0.375f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::ReturnToHand),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::ReturnToHand),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
			}),
			nullptr,
			nullptr
		);
	}

	return Shen::HexusOpponentDataInstance;
}