#include "GlobalHackAttributeContainer.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListener.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Events/HackableEvents.h"
#include "Engine/Events/SceneEvents.h"
#include "Engine/Hackables/HackActivatedAbility.h"
#include "Engine/Hackables/HackableCode.h"

using namespace cocos2d;

GlobalHackAttributeContainer* GlobalHackAttributeContainer::instance = nullptr;

void GlobalHackAttributeContainer::registerGlobalNode()
{
	if (GlobalHackAttributeContainer::instance == nullptr)
	{
		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(GlobalHackAttributeContainer::getInstance());
	}
}

GlobalHackAttributeContainer* GlobalHackAttributeContainer::getInstance()
{
	if (GlobalHackAttributeContainer::instance == nullptr)
	{
		GlobalHackAttributeContainer::instance = new GlobalHackAttributeContainer();

		GlobalHackAttributeContainer::instance->autorelease();
	}

	return GlobalHackAttributeContainer::instance;
}

GlobalHackAttributeContainer* GlobalHackAttributeContainer::create()
{
	GlobalHackAttributeContainer* instance = new GlobalHackAttributeContainer();

	instance->autorelease();

	return instance;
}

GlobalHackAttributeContainer::GlobalHackAttributeContainer() : super()
{
	this->codeMap = std::map<void*, HackableCode*>();
	this->abilityMap = std::map<std::string, HackActivatedAbility*>();
	this->hackablesContainer = Node::create();

	this->addChild(this->hackablesContainer);
}

GlobalHackAttributeContainer::~GlobalHackAttributeContainer()
{
}

void GlobalHackAttributeContainer::initializeListeners()
{
	super::initializeListeners();

	this->addGlobalEventListener(EventListenerCustom::create(SceneEvents::EventBeforeSceneChange, [=](EventCustom* eventCustom)
	{
		HackableBase::HackTimersPaused = false;
	}));

	this->addGlobalEventListener(EventListenerCustom::create(HackableEvents::EventPauseHackTimers, [=](EventCustom* eventCustom)
	{
		HackableBase::HackTimersPaused = true;
	}));

	this->addGlobalEventListener(EventListenerCustom::create(HackableEvents::EventResumeHackTimers, [=](EventCustom* eventCustom)
	{
		HackableBase::HackTimersPaused = false;
	}));
}

HackableCode* GlobalHackAttributeContainer::GetHackableCode(void* startAddress)
{
	if (GlobalHackAttributeContainer::instance->codeMap.find(startAddress) != GlobalHackAttributeContainer::instance->codeMap.end())
	{
		return GlobalHackAttributeContainer::instance->codeMap[startAddress];
	}

	return nullptr;
}

void GlobalHackAttributeContainer::RegisterHackableCode(HackableCode* hackableCode)
{
	if (hackableCode == nullptr)
	{
		return;
	}

	if (GlobalHackAttributeContainer::instance->codeMap.find(hackableCode->codePointer) == GlobalHackAttributeContainer::instance->codeMap.end())
	{
		GlobalHackAttributeContainer::instance->codeMap[hackableCode->codePointer] = hackableCode;
		GlobalHackAttributeContainer::instance->hackablesContainer->addChild(hackableCode);
	}
}

HackActivatedAbility* GlobalHackAttributeContainer::GetHackActivatedAbility(std::string identifier)
{
	if (GlobalHackAttributeContainer::instance->abilityMap.find(identifier) != GlobalHackAttributeContainer::instance->abilityMap.end())
	{
		return GlobalHackAttributeContainer::instance->abilityMap[identifier];
	}

	return nullptr;
}

void GlobalHackAttributeContainer::RegisterHackActivatedAbility(HackActivatedAbility* hackActivatedAbility)
{
	if (hackActivatedAbility == nullptr)
	{
		return;
	}

	const std::string identifier = hackActivatedAbility->getHackableIdentifier();

	if (GlobalHackAttributeContainer::instance->abilityMap.find(identifier) == GlobalHackAttributeContainer::instance->abilityMap.end())
	{
		GlobalHackAttributeContainer::instance->abilityMap[identifier] = hackActivatedAbility;
		GlobalHackAttributeContainer::instance->hackablesContainer->addChild(hackActivatedAbility);
	}
}
