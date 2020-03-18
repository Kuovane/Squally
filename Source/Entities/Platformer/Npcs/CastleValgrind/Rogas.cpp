#include "Rogas.h"

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

const std::string Rogas::MapKeyRogas = "rogas";
HexusOpponentData* Rogas::HexusOpponentDataInstance = nullptr;
const std::string Rogas::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ROGAS";

Rogas* Rogas::deserialize(ValueMap& properties)
{
	Rogas* instance = new Rogas(properties);

	instance->autorelease();

	return instance;
}

Rogas::Rogas(ValueMap& properties) : super(properties,
	Rogas::MapKeyRogas,
	EntityResources::Npcs_CastleValgrind_Rogas_Animations,
	EntityResources::Npcs_CastleValgrind_Rogas_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Rogas::getHexusOpponentData();
}

Rogas::~Rogas()
{
}

Vec2 Rogas::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Rogas::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_CastleValgrind_Rogas::create();
}

HexusOpponentData* Rogas::getHexusOpponentData()
{
	if (Rogas::HexusOpponentDataInstance == nullptr)
	{
		Rogas::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameCastleValgrind,
			Vec2(-32.0f, -112.0f),
			Rogas::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Air,
			HexusOpponentData::generateDeck(32, 0.464f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::Addition),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
			}),
			nullptr,
			nullptr
		);
	}

	return Rogas::HexusOpponentDataInstance;
}