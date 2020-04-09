#include "EbxCrystal.h"

#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/PointerTrace/RegisterState.h"

#include "Resources/IsometricObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string EbxCrystal::MapKey = "ebx-crystal";

EbxCrystal* EbxCrystal::create(ValueMap& properties)
{
	EbxCrystal* instance = new EbxCrystal(properties);

	instance->autorelease();

	return instance;
}

EbxCrystal::EbxCrystal(ValueMap& properties) : super(properties)
{
	this->crystal = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EbxCrystal);
	
	LocalizedString* registerString = (sizeof(void*) == 4)
		? (LocalizedString*)Strings::PointerTrace_Assembly_RegisterEbx::create()
		: (LocalizedString*)Strings::PointerTrace_Assembly_RegisterRbx::create();

	this->buildString(registerString);

	this->crystalNode->addChild(this->crystal);
}

EbxCrystal::~EbxCrystal()
{
}

void EbxCrystal::onEnter()
{
	super::onEnter();
}

void EbxCrystal::initializePositions()
{
	super::initializePositions();
}

void EbxCrystal::updateRegister(int value)
{
	RegisterState::setRegisterEbx(value);
}

int EbxCrystal::getRegisterValue()
{
	return RegisterState::getRegisterEbx();
}
