#include "KingGroggCombatBehavior.h"

#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Items/EntityInventoryBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityAttackBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Entities/KingGrogg/DragonBreath.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Entities/Enemies/BasicSlash.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/RestorePotion/RestorePotion.h"

#include "Resources/UIResources.h"

using namespace cocos2d;
	
const std::string KingGroggCombatBehavior::MapKeyAttachedBehavior = "king-grogg-combat";

KingGroggCombatBehavior* KingGroggCombatBehavior::create(GameObject* owner)
{
	KingGroggCombatBehavior* instance = new KingGroggCombatBehavior(owner);

	instance->autorelease();

	return instance;
}

KingGroggCombatBehavior::KingGroggCombatBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

KingGroggCombatBehavior::~KingGroggCombatBehavior()
{
}

void KingGroggCombatBehavior::initializePositions()
{
}

void KingGroggCombatBehavior::onLoad()
{
	this->entity->watchForAttachedBehavior<EntityAttackBehavior>([=](EntityAttackBehavior* attackBehavior)
	{
		attackBehavior->registerAttack(DragonBreath::create(0.5f, EntityAttackBehavior::DefaultRecoverSpeedSlow, PlatformerAttack::PriorityCommon));
		attackBehavior->registerAttack(BasicSlash::create(0.7f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::PriorityUncommon));
	});
	
	this->entity->watchForAttachedBehavior<EntityInventoryBehavior>([=](EntityInventoryBehavior* entityInventoryBehavior)
	{
		Inventory* inventory = entityInventoryBehavior->getInventory();

		if (inventory != nullptr)
		{
			inventory->forceInsert(RestorePotion::create());
		}
	});
}
