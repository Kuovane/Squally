#include "EbpJmp.h"

#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/PointerTrace/RegisterState.h"

#include "Resources/IsometricObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string EbpJmp::MapKey = "ebp-jmp";

EbpJmp* EbpJmp::create(ValueMap& properties)
{
	EbpJmp* instance = new EbpJmp(properties);

	instance->autorelease();

	return instance;
}

EbpJmp::EbpJmp(ValueMap& properties) : super(properties)
{
	this->marker = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EbpJmp);
	
	LocalizedString* registerString = (sizeof(void*) == 4)
		? (LocalizedString*)Strings::PointerTrace_Assembly_RegisterEbp::create()
		: (LocalizedString*)Strings::PointerTrace_Assembly_RegisterRbp::create();

	this->buildJmpString(registerString);

	this->markerNode->addChild(this->marker);
}

EbpJmp::~EbpJmp()
{
}

void EbpJmp::onEnter()
{
	super::onEnter();
}

void EbpJmp::initializePositions()
{
	super::initializePositions();
}

int EbpJmp::getJumpDestination()
{
	return RegisterState::getRegisterEbp();
}
