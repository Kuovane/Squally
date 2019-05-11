#include "GeneralTab.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Sound/SoundManager.h"
#include "Engine/UI/Controls/Checkbox.h"
#include "Engine/UI/Controls/Slider.h"
#include "Engine/Utils/GameUtils.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

GeneralTab* GeneralTab::create()
{
	GeneralTab* instance = new GeneralTab();

	instance->autorelease();

	return instance;
}

GeneralTab::GeneralTab()
{
	this->musicIcon = Sprite::create(UIResources::Menus_OptionsMenu_MusicIcon);
	this->soundIcon = Sprite::create(UIResources::Menus_OptionsMenu_SoundIcon);

	this->musicSlider = Slider::create(UIResources::Menus_OptionsMenu_SliderFrame, UIResources::Menus_OptionsMenu_SliderFill, UIResources::Menus_Buttons_SliderButton, UIResources::Menus_Buttons_SliderButtonSelected, SoundManager::getMusicVolume());
	this->soundSlider = Slider::create(UIResources::Menus_OptionsMenu_SliderFrame, UIResources::Menus_OptionsMenu_SliderFill, UIResources::Menus_Buttons_SliderButton, UIResources::Menus_Buttons_SliderButtonSelected, SoundManager::getSoundVolume());

	this->musicSlider->setProgressUpdateCallback(CC_CALLBACK_1(GeneralTab::onMusicVolumeUpdate, this));
	this->soundSlider->setProgressUpdateCallback(CC_CALLBACK_1(GeneralTab::onSoundVolumeUpdate, this));

	this->addChild(this->musicIcon);
	this->addChild(this->soundIcon);
	this->addChild(this->soundSlider);
	this->addChild(this->musicSlider);
}

GeneralTab::~GeneralTab()
{
}

void GeneralTab::onEnter()
{
	super::onEnter();

	float delay = 0.1f;
	float duration = 0.25f;

	GameUtils::fadeInObject(this->musicIcon, delay, duration);
	GameUtils::fadeInObject(this->soundIcon, delay, duration);
	GameUtils::fadeInObject(this->musicSlider, delay, duration);
	GameUtils::fadeInObject(this->soundSlider, delay, duration);
}

void GeneralTab::initializeListeners()
{
	super::initializeListeners();
}

void GeneralTab::initializePositions()
{
	super::initializePositions();

	this->soundIcon->setPosition(Vec2(-276.0f, 176.0f));
	this->musicIcon->setPosition(Vec2(-276.0f, 96.0f));
	this->soundSlider->setPosition(Vec2(32.0f, 176.0f));
	this->musicSlider->setPosition(Vec2(32.0f, 96.0f));
}

void GeneralTab::onSoundVolumeUpdate(float soundVolume)
{
	SoundManager::setSoundVolume(soundVolume);
}

void GeneralTab::onMusicVolumeUpdate(float musicVolume)
{
	SoundManager::setMusicVolume(musicVolume);
}
