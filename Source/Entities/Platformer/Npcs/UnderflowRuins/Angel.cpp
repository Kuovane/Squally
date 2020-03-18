#include "Angel.h"

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

const std::string Angel::MapKeyAngel = "angel";
HexusOpponentData* Angel::HexusOpponentDataInstance = nullptr;
const std::string Angel::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ANGEL";

Angel* Angel::deserialize(ValueMap& properties)
{
	Angel* instance = new Angel(properties);

	instance->autorelease();

	return instance;
}

Angel::Angel(ValueMap& properties) : super(properties,
	Angel::MapKeyAngel,
	EntityResources::Npcs_UnderflowRuins_Angel_Animations,
	EntityResources::Npcs_UnderflowRuins_Angel_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Angel::getHexusOpponentData();
}

Angel::~Angel()
{
}

Vec2 Angel::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Angel::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_UnderflowRuins_Angel::create();
}

HexusOpponentData* Angel::getHexusOpponentData()
{
	if (Angel::HexusOpponentDataInstance == nullptr)
	{
		Angel::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameUnderflowRuins,
			Vec2(-32.0f, -112.0f),
			Angel::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Light,
			HexusOpponentData::generateDeck(32, 0.143f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip2),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
			}),
			nullptr,
			nullptr
		);
	}

	return Angel::HexusOpponentDataInstance;
}