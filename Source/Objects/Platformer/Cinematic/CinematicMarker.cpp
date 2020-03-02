#include "CinematicMarker.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"

#include "Events/SwitchEvents.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string CinematicMarker::MapKeyCinematicMarker = "cinematic-marker";

CinematicMarker* CinematicMarker::create(ValueMap& properties)
{
	CinematicMarker* instance = new CinematicMarker(properties);

	instance->autorelease();

	return instance;
}

CinematicMarker::CinematicMarker(ValueMap& properties) : super(properties)
{
}

CinematicMarker::~CinematicMarker()
{
}

void CinematicMarker::onEnter()
{
	super::onEnter();
}

void CinematicMarker::initializePositions()
{
	super::initializePositions(); 
}

void CinematicMarker::initializeListeners()
{
	super::initializeListeners();
}
