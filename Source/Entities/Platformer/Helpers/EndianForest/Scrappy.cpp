#include "Scrappy.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/math/CCGeometry.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Dialogue/SpeechBubble.h"
#include "Engine/Save/SaveManager.h"
#include "Events/PlatformerEvents.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Events/CombatEvents.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"
#include "Scenes/Hexus/StateOverride.h"

#include "Resources/EntityResources.h"
#include "Resources/FXResources.h"
#include "Resources/HexusResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Scrappy::MapKey = "scrappy";
HexusOpponentData* Scrappy::HexusOpponentDataInstance = nullptr;

const std::string Scrappy::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_SCRAPPY";

Scrappy* Scrappy::deserialize(ValueMap& properties)
{
	Scrappy* instance = new Scrappy(properties);

	instance->autorelease();

	return instance;
}

Scrappy::Scrappy(ValueMap& properties) : super(properties,
	Scrappy::MapKey,
	EntityResources::Helpers_EndianForest_Scrappy_Animations,
	EntityResources::Helpers_EndianForest_Scrappy_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Scrappy::getHexusOpponentData();

	this->fireAnimation = SmartAnimationSequenceNode::create();

	this->fireAnimation->setFlippedY(true);
	this->fireAnimation->setScale(0.25f);

	this->belowAnimationNode->addChild(this->fireAnimation);
}

Scrappy::~Scrappy()
{
}

void Scrappy::onEnter()
{
	super::onEnter();

	this->fireAnimation->playAnimationRepeat(FXResources::FlameSmall_FlameSmall_0000, 0.045f);
}

void Scrappy::initializePositions()
{
	super::initializePositions();
	
	this->fireAnimation->setPosition(Vec2(0.0f, -16.0f));
}

void Scrappy::initializeListeners()
{
	super::initializeListeners();
}

Vec2 Scrappy::getDialogueOffset()
{
	return Vec2(0.0f, 48.0f);
}

LocalizedString* Scrappy::getEntityName()
{
	return Strings::Platformer_Entities_Names_Helpers_EndianForest_Scrappy::create();
}

HexusOpponentData* Scrappy::getHexusOpponentData()
{
	if (Scrappy::HexusOpponentDataInstance == nullptr)
	{
		Scrappy::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameDaemonsHallow,
			Vec2(-32.0f, -112.0f),
			Scrappy::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Fire,
			HexusOpponentData::generateDeck(32, 1.000f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
			}),
			{ },
			nullptr
		);
	}

	return Scrappy::HexusOpponentDataInstance;
}
