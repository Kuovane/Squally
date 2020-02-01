#include "TargetSelectionMenu.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCEventListenerKeyboard.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/PlatformerFriendly.h"
#include "Events/CombatEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/EntitySelectionBehavior.h"
#include "Scenes/Platformer/Level/Combat/Timeline.h"
#include "Scenes/Platformer/Level/Combat/TimelineEntry.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

TargetSelectionMenu* TargetSelectionMenu::create(Timeline* timelineRef)
{
	TargetSelectionMenu* instance = new TargetSelectionMenu(timelineRef);

	instance->autorelease();

	return instance;
}

TargetSelectionMenu::TargetSelectionMenu(Timeline* timelineRef)
{
	this->lightRay = Sprite::create(UIResources::Combat_SelectionLight);
	this->timelineRef = timelineRef;

	this->lightRay->setAnchorPoint(Vec2(0.5f, 0.0f));

	this->addChild(this->lightRay);
}

void TargetSelectionMenu::onEnter()
{
	super::onEnter();

	this->setVisible(false);

	this->scheduleUpdate();
}

void TargetSelectionMenu::initializePositions()
{
	super::initializePositions();
}

void TargetSelectionMenu::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventChangeMenuState, [=](EventCustom* args)
	{
		CombatEvents::MenuStateArgs* combatArgs = static_cast<CombatEvents::MenuStateArgs*>(args->getUserData());

		if (combatArgs != nullptr)
		{
			switch (combatArgs->currentMenu)
			{
				case CombatEvents::MenuStateArgs::CurrentMenu::ChooseAttackTarget:
				{
					this->selectEntity(nullptr);

					for (auto next : this->timelineRef->getEntries())
					{
						if (!next->isPlayerEntry())
						{
							this->selectEntity(next->getEntity());
							break;
						}
					}

					this->allowedSelection = AllowedSelection::Enemy;
					this->setEntityClickCallbacks();
					this->isActive = true;
					this->setVisible(true);
					break;
				}
				case CombatEvents::MenuStateArgs::CurrentMenu::ChooseBuffTarget:
				{
					this->selectEntity(nullptr);

					for (auto next : this->timelineRef->getEntries())
					{
						if (next->isPlayerEntry())
						{
							this->selectEntity(next->getEntity());
							break;
						}
					}

					this->allowedSelection = AllowedSelection::Player;
					this->setEntityClickCallbacks();
					this->isActive = true;
					this->setVisible(true);
					break;
				}
				default:
				{
					this->clearEntityClickCallbacks();
					this->setVisible(false);
					break;
				}
			}
		}
	}));

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_A, EventKeyboard::KeyCode::KEY_LEFT_ARROW }, [=](InputEvents::InputArgs* args)
	{
		this->selectNext(true);
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_D, EventKeyboard::KeyCode::KEY_RIGHT_ARROW }, [=](InputEvents::InputArgs* args)
	{
		this->selectNext(false);
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_ENTER, EventKeyboard::KeyCode::KEY_SPACE }, [=](InputEvents::InputArgs* args)
	{
		this->chooseCurrentTarget();
	});
}

void TargetSelectionMenu::chooseCurrentTarget()
{
	if (!this->isActive || this->selectedEntity == nullptr)
	{
		return;
	}

	CombatEvents::TriggerSelectCastTarget(CombatEvents::CastTargetArgs(this->selectedEntity));
	CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(CombatEvents::MenuStateArgs::CurrentMenu::Closed, nullptr));
}

void TargetSelectionMenu::selectEntity(PlatformerEntity* entity)
{
	const Vec2 LightOffset = Vec2(128.0f, -128.0f);

	if (entity != nullptr)
	{
		this->lightRay->setPosition(GameUtils::getScreenBounds(entity).origin + LightOffset);
		this->lightRay->setVisible(true);
	}
	else
	{
		this->lightRay->setVisible(false);
	}

	this->selectedEntity = entity;
}

void TargetSelectionMenu::selectNext(bool directionIsLeft)
{
	if (!this->isActive)
	{
		return;
	}

	std::vector<PlatformerEntity*> targetEntityGroup = std::vector<PlatformerEntity*>();

	switch (this->allowedSelection)
	{
		case AllowedSelection::Player:
		{
			ObjectEvents::QueryObjects(QueryObjectsArgs<PlatformerFriendly>([&](PlatformerFriendly* entity)
			{
				if (entity->getStateOrDefaultBool(StateKeys::IsAlive, true))
				{
					targetEntityGroup.push_back(entity);
				}
			}), PlatformerFriendly::PlatformerFriendlyTag);

			break;
		}
		case AllowedSelection::Either:
		{
			ObjectEvents::QueryObjects(QueryObjectsArgs<PlatformerEnemy>([&](PlatformerEntity* entity)
			{
				if (entity->getStateOrDefaultBool(StateKeys::IsAlive, true))
				{
					targetEntityGroup.push_back(entity);
				}
			}), PlatformerEnemy::PlatformerEnemyTag);

			break;
		}
		case AllowedSelection::Enemy:
		{
			ObjectEvents::QueryObjects(QueryObjectsArgs<PlatformerEnemy>([&](PlatformerEnemy* entity)
			{
				if (entity->getStateOrDefaultBool(StateKeys::IsAlive, true))
				{
					targetEntityGroup.push_back(entity);
				}
			}), PlatformerEnemy::PlatformerEnemyTag);

			break;
		}
		default:
		{
			break;
		}
	}

	auto entityPosition = std::find(targetEntityGroup.begin(), targetEntityGroup.end(), this->selectedEntity);

	if (entityPosition != std::end(targetEntityGroup))
	{
		if (directionIsLeft)
		{
			PlatformerEntity* nextEntity = (*entityPosition == targetEntityGroup.front()) ? targetEntityGroup.back() : *std::prev(entityPosition);

			this->selectEntity(nextEntity);
		}
		else
		{
			auto next = std::next(entityPosition);

			PlatformerEntity* nextEntity = (next != std::end(targetEntityGroup)) ? *next : targetEntityGroup.front();

			this->selectEntity(nextEntity);
		}
	}
	else
	{
		this->selectEntity(nullptr);
	}
}

void TargetSelectionMenu::setEntityClickCallbacks()
{
	ObjectEvents::QueryObjects(QueryObjectsArgs<PlatformerEntity>([=](PlatformerEntity* entity)
	{
		this->setEntityClickCallbacks(entity);
	}), PlatformerEntity::PlatformerEntityTag);
}

void TargetSelectionMenu::setEntityClickCallbacks(PlatformerEntity* entity)
{
	entity->getAttachedBehavior<EntitySelectionBehavior>([=](EntitySelectionBehavior* selection)
	{
		if (!entity->getStateOrDefaultBool(StateKeys::IsAlive, true)
			|| (this->allowedSelection == AllowedSelection::Player && dynamic_cast<PlatformerFriendly*>(entity) == nullptr)
			|| (this->allowedSelection == AllowedSelection::Enemy && dynamic_cast<PlatformerEnemy*>(entity) == nullptr))
		{
			return;
		}

		PlatformerEntity* entityRef = entity;

		selection->setEntityClickCallbacks([=]()
		{
			CombatEvents::TriggerSelectCastTarget(CombatEvents::CastTargetArgs(entityRef));
			CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(CombatEvents::MenuStateArgs::CurrentMenu::Closed, nullptr));
		},
		[=]()
		{
			this->selectEntity(entityRef);
		});
	});
}

void TargetSelectionMenu::clearEntityClickCallbacks()
{
	ObjectEvents::QueryObjects(QueryObjectsArgs<PlatformerEntity>([=](PlatformerEntity* entity)
	{
		EntitySelectionBehavior* selection = entity->getAttachedBehavior<EntitySelectionBehavior>();
		
		if (selection != nullptr)
		{
			selection->clearEntityClickCallbacks();
		}
	}), PlatformerEntity::PlatformerEntityTag);
}
