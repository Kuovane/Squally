#include "EspCrystal.h"

#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/PointerTrace/RegisterState.h"

#include "Resources/IsometricObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string EspCrystal::MapKey = "esp-crystal";

EspCrystal* EspCrystal::create(ValueMap& properties)
{
	EspCrystal* instance = new EspCrystal(properties);

	instance->autorelease();

	return instance;
}

EspCrystal::EspCrystal(ValueMap& properties) : super(properties)
{
	this->crystal = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EspCrystal);
	
	LocalizedString* registerString = (sizeof(void*) == 4)
		? (LocalizedString*)Strings::PointerTrace_Assembly_RegisterEsp::create()
		: (LocalizedString*)Strings::PointerTrace_Assembly_RegisterRsp::create();

	this->buildString(registerString);

	this->crystalNode->addChild(this->crystal);
}

EspCrystal::~EspCrystal()
{
}

void EspCrystal::onEnter()
{
	super::onEnter();
}

void EspCrystal::initializePositions()
{
	super::initializePositions();
}

void EspCrystal::updateRegister(int value)
{
	RegisterState::setRegisterEsp(value);
}

int EspCrystal::getRegisterValue()
{
	return RegisterState::getRegisterEsp();
}
