//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Dudly.h"

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

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////A////A////A////A////A////A////A////A////A////A/

////B////B////B////B////B////B////B////B////B////B/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

using namespace cocos2d;

const std::string Dudly::MapKeyDudly = "dudly";
HexusOpponentData* Dudly::HexusOpponentDataInstance = nullptr;
const std::string Dudly::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_DUDLY";

Dudly* Dudly::deserialize(ValueMap& initProperties)
{
	Dudly* instance = new Dudly(initProperties);

	instance->autorelease();

	return instance;
}

Dudly::Dudly(ValueMap& initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_LambdaCrypts_Dudly_Animations,
	EntityResources::Npcs_LambdaCrypts_Dudly_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	Size(112.0f, 160.0f),
	0.9f,
	Vec2(0.0f, 0.0f),
	16,
	8)
{
	this->hexusOpponentData = Dudly::getHexusOpponentData();

	///////////////////////////////////////////////////
	// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/
	
	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/
	// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
	///////////////////////////////////////////////////
}

Dudly::~Dudly()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

Vec2 Dudly::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* Dudly::getHexusOpponentData()
{
	if (Dudly::HexusOpponentDataInstance == nullptr)
	{
		Dudly::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_LambdaCrypts_Dudly_Animations,
			HexusResources::Menus_HexusFrameLambdaCrypts,
			0.9f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Dudly::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			0.777f,
			HexusOpponentData::generateDeck(32, 0.777f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::ReturnToHand),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::Subtraction),
				CardList::getInstance()->cardListByName.at(CardKeys::Inverse),
				CardList::getInstance()->cardListByName.at(CardKeys::Addition),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),

			}),
			nullptr
		);
	}

	return Dudly::HexusOpponentDataInstance;
}