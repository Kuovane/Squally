#include "PlatformerAttachedBehaviorDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Engine/Maps/GameObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/StrUtils.h"
#include "Scenes/Platformer/AttachedBehavior/PlatformerAttachedBehavior.h"

using namespace cocos2d;

PlatformerAttachedBehaviorDeserializer* PlatformerAttachedBehaviorDeserializer::create()
{
	PlatformerAttachedBehaviorDeserializer* instance = new PlatformerAttachedBehaviorDeserializer();

	instance->autorelease();

	return instance;
}

PlatformerAttachedBehaviorDeserializer::PlatformerAttachedBehaviorDeserializer() : super()
{
	this->attachedBehaviorDeserializers = std::map<std::string, std::function<AttachedBehavior*(GameObject*)>>();

	this->attachedBehaviorDeserializers[AgroBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)AgroBehavior::create(owner); };
	this->attachedBehaviorDeserializers[EnableAllClippyBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)EnableAllClippyBehavior::create(owner); };
	this->attachedBehaviorDeserializers[EnemyBattleAllyBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)EnemyBattleAllyBehavior::create(owner); };
	this->attachedBehaviorDeserializers[EnemyBehaviorGroup::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)EnemyBehaviorGroup::create(owner); };
	this->attachedBehaviorDeserializers[EntityBehaviorGroup::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)EntityNoCollisionBehaviorGroup::create(owner); };
	this->attachedBehaviorDeserializers[EntityDisarmedBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)EntityDisarmedBehavior::create(owner); };
	this->attachedBehaviorDeserializers[EntityNoCollisionBehaviorGroup::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)EntityNoCollisionBehaviorGroup::create(owner); };
	this->attachedBehaviorDeserializers[EntityPacingBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)EntityPacingBehavior::create(owner); };
	this->attachedBehaviorDeserializers[EntityPickPocketBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)EntityPickPocketBehavior::create(owner); };
	this->attachedBehaviorDeserializers[DisabledPortal::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)DisabledPortal::create(owner); };
	this->attachedBehaviorDeserializers[FirstIOUFound::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)FirstIOUFound::create(owner); };
	this->attachedBehaviorDeserializers[LookAtSquallyBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)LookAtSquallyBehavior::create(owner); };
	this->attachedBehaviorDeserializers[LookAtSquallyBehavior::MapKeyAttachedBehaviorAlias] = [=](GameObject* owner) { return (AttachedBehavior*)LookAtSquallyBehavior::create(owner); };
	this->attachedBehaviorDeserializers[LockedPortal::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)LockedPortal::create(owner); };
	this->attachedBehaviorDeserializers[NoDefendBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)NoDefendBehavior::create(owner); };
	this->attachedBehaviorDeserializers[NoItemsBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)NoItemsBehavior::create(owner); };
	this->attachedBehaviorDeserializers[FriendlyBehaviorGroup::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)FriendlyBehaviorGroup::create(owner); };
	this->attachedBehaviorDeserializers[FriendlyNoCollisionBehaviorGroup::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)FriendlyNoCollisionBehaviorGroup::create(owner); };
	this->attachedBehaviorDeserializers[RestorePotionTutorialBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)RestorePotionTutorialBehavior::create(owner); };
	this->attachedBehaviorDeserializers[ShopkeeperBehaviorGroup::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)ShopkeeperBehaviorGroup::create(owner); };
	this->attachedBehaviorDeserializers[SquallyBehaviorGroup::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)SquallyBehaviorGroup::create(owner); };
	this->attachedBehaviorDeserializers[SquallyCombatBehaviorGroup::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)SquallyCombatBehaviorGroup::create(owner); };
	this->attachedBehaviorDeserializers[SquallyNoSavePositionBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)SquallyNoSavePositionBehavior::create(owner); };
	
	// Helpers
	this->attachedBehaviorDeserializers[GuanoBehaviorGroup::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)GuanoBehaviorGroup::create(owner); };
	this->attachedBehaviorDeserializers[ScrappyBehaviorGroup::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)ScrappyBehaviorGroup::create(owner); };
	this->attachedBehaviorDeserializers[ScrappyCombatBehaviorGroup::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)ScrappyCombatBehaviorGroup::create(owner); };
	
	/*********************
		Hexus
	*********************/

	this->attachedBehaviorDeserializers[PuzzleABehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)PuzzleABehavior::create(owner); };
	this->attachedBehaviorDeserializers[PuzzleBBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)PuzzleBBehavior::create(owner); };
	this->attachedBehaviorDeserializers[PuzzleCBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)PuzzleCBehavior::create(owner); };
	this->attachedBehaviorDeserializers[PuzzleDBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)PuzzleDBehavior::create(owner); };
	this->attachedBehaviorDeserializers[PuzzleEBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)PuzzleEBehavior::create(owner); };

	// EF
	this->attachedBehaviorDeserializers[AraHexusBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)AraHexusBehavior::create(owner); };
	this->attachedBehaviorDeserializers[BardHexusBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)BardHexusBehavior::create(owner); };
	this->attachedBehaviorDeserializers[BlackbeardHexusBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)BlackbeardHexusBehavior::create(owner); };
	this->attachedBehaviorDeserializers[ChironHexusBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)ChironHexusBehavior::create(owner); };
	this->attachedBehaviorDeserializers[ElrielHexusBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)ElrielHexusBehavior::create(owner); };
	this->attachedBehaviorDeserializers[GrampsHexusBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)GrampsHexusBehavior::create(owner); };
	this->attachedBehaviorDeserializers[LianaHexusBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)LianaHexusBehavior::create(owner); };
	this->attachedBehaviorDeserializers[LycanHexusBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)LycanHexusBehavior::create(owner); };
	this->attachedBehaviorDeserializers[MarcelHexusBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)MarcelHexusBehavior::create(owner); };
	this->attachedBehaviorDeserializers[MatuHexusBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)MatuHexusBehavior::create(owner); };
	this->attachedBehaviorDeserializers[MinosHexusBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)MinosHexusBehavior::create(owner); };
	this->attachedBehaviorDeserializers[PolyphemusHexusBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)PolyphemusHexusBehavior::create(owner); };
	this->attachedBehaviorDeserializers[RobinHexusBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)RobinHexusBehavior::create(owner); };
	this->attachedBehaviorDeserializers[TobenHexusBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)TobenHexusBehavior::create(owner); };
		
	/*********************
		COMBAT
	*********************/

	// Helpers
	this->attachedBehaviorDeserializers[GuanoCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)GuanoCombatBehavior::create(owner); };
	
	// Endian forest
	this->attachedBehaviorDeserializers[LycanBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)LycanBehavior::create(owner); };
	
	this->attachedBehaviorDeserializers[CentaurCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)CentaurCombatBehavior::create(owner); };
	this->attachedBehaviorDeserializers[GoblinGruntBoarCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)GoblinGruntBoarCombatBehavior::create(owner); };
	this->attachedBehaviorDeserializers[GoblinShamanCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)GoblinShamanCombatBehavior::create(owner); };
	this->attachedBehaviorDeserializers[GoblinWarriorPigCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)GoblinWarriorPigCombatBehavior::create(owner); };
	this->attachedBehaviorDeserializers[GorgonCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)GorgonCombatBehavior::create(owner); };
	this->attachedBehaviorDeserializers[KingGroggCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)KingGroggCombatBehavior::create(owner); };
	this->attachedBehaviorDeserializers[OgreCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)OgreCombatBehavior::create(owner); };
	this->attachedBehaviorDeserializers[OrcBomberCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)OrcBomberCombatBehavior::create(owner); };
	this->attachedBehaviorDeserializers[OrcGruntCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)OrcGruntCombatBehavior::create(owner); };
	this->attachedBehaviorDeserializers[OrcSwordsmanCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)OrcSwordsmanCombatBehavior::create(owner); };
	this->attachedBehaviorDeserializers[OrcWarriorCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)OrcWarriorCombatBehavior::create(owner); };
	this->attachedBehaviorDeserializers[OrthrusCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)OrthrusCombatBehavior::create(owner); };
	this->attachedBehaviorDeserializers[TrollCombatBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)TrollCombatBehavior::create(owner); };

	/*********************
		Squalr
	*********************/

	this->attachedBehaviorDeserializers[UnknownValueBarBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner) { return (AttachedBehavior*)UnknownValueBarBehavior::create(owner); };
}

PlatformerAttachedBehaviorDeserializer::~PlatformerAttachedBehaviorDeserializer()
{
}

void PlatformerAttachedBehaviorDeserializer::deserializeProperties(GameObject* owner, ValueMap properties)
{
	std::string attachedBehaviorName = GameUtils::getKeyOrDefault(properties, GameObject::MapKeyAttachedBehavior, Value("")).asString();
	
	if (!attachedBehaviorName.empty())
	{
		std::vector<std::string> attachedBehaviors = StrUtils::splitOn(attachedBehaviorName, ", ", false);
		
		for (auto it = attachedBehaviors.begin(); it != attachedBehaviors.end(); it++)
		{
			AttachedBehavior* attachedBehavior = this->deserialize(AttachedBehaviorDeserializer::AttachedBehaviorDeserializationRequestArgs(owner, *it));

			if (attachedBehavior != nullptr)
			{
				owner->attachBehavior(attachedBehavior);
			}
		}
	}
}

std::string PlatformerAttachedBehaviorDeserializer::getPropertyDeserializerKey()
{
	return GameObject::MapKeyAttachedBehavior;
}
