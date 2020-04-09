#include "KingRedsongSlime.h"

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

const std::string KingRedsongSlime::MapKey = "king-redsong-slime";
HexusOpponentData* KingRedsongSlime::HexusOpponentDataInstance = nullptr;
const std::string KingRedsongSlime::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_KING_REDSONG_SLIME";

KingRedsongSlime* KingRedsongSlime::deserialize(ValueMap& properties)
{
	KingRedsongSlime* instance = new KingRedsongSlime(properties);

	instance->autorelease();

	return instance;
}

KingRedsongSlime::KingRedsongSlime(ValueMap& properties) : super(properties,
	KingRedsongSlime::MapKey,
	EntityResources::Npcs_CastleValgrind_KingRedsongSlime_Animations,
	EntityResources::Npcs_CastleValgrind_KingRedsongSlime_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = KingRedsongSlime::getHexusOpponentData();
}

KingRedsongSlime::~KingRedsongSlime()
{
}

Vec2 KingRedsongSlime::getDialogueOffset()
{
	return Vec2(-32.0f, -96.0f);
}

LocalizedString* KingRedsongSlime::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_CastleValgrind_KingRedsong::create();
}

HexusOpponentData* KingRedsongSlime::getHexusOpponentData()
{
	if (KingRedsongSlime::HexusOpponentDataInstance == nullptr)
	{
		KingRedsongSlime::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameCastleValgrind,
			Vec2(-32.0f, -96.0f),
			KingRedsongSlime::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Air,
			HexusOpponentData::generateDeck(32, 0.402f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
			}),
			nullptr,
			nullptr
		);
	}

	return KingRedsongSlime::HexusOpponentDataInstance;
}