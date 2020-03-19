#include "FriendlyBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/EntityBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Friendly/Collision/FriendlyCollisionBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Friendly/Collision/FriendlyPlayerCollisionBehavior.h"

using namespace cocos2d;

const std::string FriendlyBehaviorGroup::MapKey = "friendly";

FriendlyBehaviorGroup* FriendlyBehaviorGroup::create(GameObject* owner)
{
	FriendlyBehaviorGroup* instance = new FriendlyBehaviorGroup(owner);

	instance->autorelease();

	return instance;
}

FriendlyBehaviorGroup::FriendlyBehaviorGroup(GameObject* owner) : super(owner, {
	FriendlyCollisionBehavior::create(owner),
	FriendlyPlayerCollisionBehavior::create(owner),
	EntityBehaviorGroup::create(owner),
	})
{
}

FriendlyBehaviorGroup::~FriendlyBehaviorGroup()
{
}

void FriendlyBehaviorGroup::onLoad()
{
}
