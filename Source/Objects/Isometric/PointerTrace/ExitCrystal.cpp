#include "ExitCrystal.h"

#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Utils/GameUtils.h"

#include "Resources/IsometricObjectResources.h"

using namespace cocos2d;

const std::string ExitCrystal::MapKeyExitCrystal = "exit-crystal";

ExitCrystal* ExitCrystal::create(ValueMap& initProperties)
{
	ExitCrystal* instance = new ExitCrystal(initProperties);

	instance->autorelease();

	return instance;
}

ExitCrystal::ExitCrystal(ValueMap& initProperties) : super(initProperties)
{
	this->shadow = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_Shadow);
	this->crystal = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_ExitCrystal);

	this->addChild(this->shadow);
	this->addChild(this->crystal);
}

ExitCrystal::~ExitCrystal()
{
}

void ExitCrystal::onEnter()
{
	super::onEnter();

	this->crystal->runAction(RepeatForever::create(
		Sequence::create(
			EaseSineInOut::create(MoveTo::create(4.0f, Vec2(0.0f, 128.0f))),
			EaseSineInOut::create(MoveTo::create(4.0f, Vec2(0.0f, 96.0f))),
			nullptr
		)
	));
	this->shadow->runAction(RepeatForever::create(
		Sequence::create(
			ScaleTo::create(4.0f, 0.75f),
			ScaleTo::create(4.0f, 1.0f),
			nullptr
		)
	));
}

void ExitCrystal::initializePositions()
{
	super::initializePositions();

	this->crystal->setPosition(Vec2(0.0f, 96.0f));
}