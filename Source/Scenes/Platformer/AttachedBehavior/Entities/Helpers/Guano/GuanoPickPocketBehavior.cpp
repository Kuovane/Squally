#include "GuanoPickPocketBehavior.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Inventory/Item.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/MinMaxPool.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/HelperEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GuanoPickPocketBehavior::MapKeyAttachedBehavior = "pick-pocketer";

GuanoPickPocketBehavior* GuanoPickPocketBehavior::create(GameObject* owner)
{
	GuanoPickPocketBehavior* instance = new GuanoPickPocketBehavior(owner);

	instance->autorelease();

	return instance;
}

GuanoPickPocketBehavior::GuanoPickPocketBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->isPickPocketing = false;

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

GuanoPickPocketBehavior::~GuanoPickPocketBehavior()
{
}

void GuanoPickPocketBehavior::onLoad()
{
	this->addEventListener(EventListenerCustom::create(HelperEvents::EventRequestPickPocket, [=](EventCustom* eventCustom)
	{
		HelperEvents::RequestPickPocketArgs* args = static_cast<HelperEvents::RequestPickPocketArgs*>(eventCustom->getUserData());

		if (args != nullptr && !this->isPickPocketing)
		{
			this->tryPickPocket(args->target, args->pocketPool, args->saveKeyPickPocketed);
		}
	}));
}

void GuanoPickPocketBehavior::tryPickPocket(PlatformerEntity* target, MinMaxPool* pocketPool, std::string pickPocketSaveKey)
{
	if (pocketPool == nullptr)
	{
		return;
	}

	if (this->entity->getStateOrDefault(StateKeys::PatrolHijacked, Value(false)).asBool())
	{
		return;
	}
	
	this->isPickPocketing = true;
	this->entity->setState(StateKeys::PatrolHijacked, Value(true));
	this->entity->setState(StateKeys::PatrolDestinationX, Value(GameUtils::getWorldCoords(target).x));
	this->entity->setOpacity(192);

	this->entity->listenForStateWriteOnce(StateKeys::PatrolDestinationReached, [=](Value value)
	{
		if (this->isPickPocketing)
		{
			this->stopAllActions();
			this->endPickPocket();

			PlatformerEvents::TriggerGiveItemsFromPool(PlatformerEvents::GiveItemsFromPoolArgs(pocketPool));

			target->saveObjectState(pickPocketSaveKey, Value(true));
		}
	});

	this->runAction(Sequence::create(
		DelayTime::create(5.0f),
		CallFunc::create([=]()
		{
			if (this->isPickPocketing)
			{
				this->endPickPocket();
			}
		}),
		nullptr
	));
}

void GuanoPickPocketBehavior::onDisable()
{
	super::onDisable();
}

void GuanoPickPocketBehavior::endPickPocket()
{
	this->isPickPocketing = false;
	this->entity->clearState(StateKeys::PatrolHijacked);
	this->entity->clearState(StateKeys::PatrolDestinationX);
	this->entity->runAction(Sequence::create(
		DelayTime::create(1.0f),
		FadeTo::create(0.25f, 255),
		nullptr
	));
}
