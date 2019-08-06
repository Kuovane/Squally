#include "PlatformerEntity.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/physics/CCPhysicsWorld.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"
#include "Engine/Hackables/HackablePreview.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/CurrencyInventory.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Physics/EngineCollisionTypes.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Events/PlatformerEvents.h"
#include "Entities/Platformer/EntityPreview.h"
#include "Entities/Platformer/StatsTables/StatsTables.h"
#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const float PlatformerEntity::MoveAcceleration = 5800.0f;
const Vec2 PlatformerEntity::SwimAcceleration = Vec2(8000.0f, 420.0f);
const float PlatformerEntity::WallDetectorSize = 64.0f;
const Size PlatformerEntity::DefaultWeaponSize = Size(64.0f, 128.0f);
const float PlatformerEntity::SwimVerticalDrag = 0.93f;
const float PlatformerEntity::JumpVelocity = 7680.0f;
const float PlatformerEntity::GroundCollisionPadding = 28.0f;
const float PlatformerEntity::GroundCollisionOffset = -12.0f;
const float PlatformerEntity::CapsuleRadius = 8.0f;

const int PlatformerEntity::FallBackMaxHealth = 10;
const int PlatformerEntity::FallBackMaxMana = 10;
const int PlatformerEntity::MaxRunes = 3;
const float PlatformerEntity::RuneCooldown = 24.0f;
const int PlatformerEntity::DefaultEq = 1;

const std::string PlatformerEntity::MapKeyPropertyState = "state";

PlatformerEntity::PlatformerEntity(
	ValueMap& properties, 
	std::string scmlResource,
	std::string emblemResource,
	PlatformerCollisionType collisionType,
	Size size,
	float scale, 
	Vec2 collisionOffset,
	int baseHealth,
	int baseSpecial,
	Size movementCollisionSize,
	float ghettoGroundCollisionFix,
	PlatformerCollisionType movementCollisionType,
	std::string inventorySaveKey,
	std::string equipmentSaveKey,
	std::string currencySaveKey
	) : super(properties)
{
	this->animationNode = SmartAnimationNode::create(scmlResource);
	this->weaponCollision = nullptr;
	this->scale = scale;
	this->collisionType = collisionType;
	this->animationResource = scmlResource;
	this->emblemResource = emblemResource;
	this->isCinimaticHijacked = false;
	this->isPlatformerDisabled = false;
	this->state = GameUtils::getKeyOrDefault(this->properties, PlatformerEntity::MapKeyPropertyState, Value("")).asString();
	this->eq = 0;
	this->eqExperience = 0;

	Vec2 scaledColOffset = collisionOffset * scale;

	// A bit sketchy, but maintains backwards compatibility with how entities are coded right now
	movementCollisionSize = (movementCollisionSize.width <= 0.0f || movementCollisionSize.height <= 0.0f) ? size : movementCollisionSize;
	
	this->entitySize = size * scale;

	this->movementCollision = CollisionObject::create(
		PlatformerEntity::createCapsulePolygon(movementCollisionSize, scale),
		(CollisionType)movementCollisionType,
		true,
		false
	);
	this->entityCollision = CollisionObject::create(
		PlatformerEntity::createCapsulePolygon(size, scale * 0.9f),
		(CollisionType)(int)this->collisionType,
		false,
		false
	);
	this->groundCollision = CollisionObject::create(
		PlatformerEntity::createCapsulePolygon(
			Size(std::max((size * scale).width - PlatformerEntity::GroundCollisionPadding * 2.0f, 8.0f), 40.0f),
			1.0f
		),
		(int)PlatformerCollisionType::GroundDetector,
		false,
		false
	);
	this->leftCollision = CollisionObject::create(
		PlatformerEntity::createCapsulePolygon(Size(PlatformerEntity::WallDetectorSize, this->entitySize.height), 1.0f),
		(int)PlatformerCollisionType::WallDetector,
		false,
		false
	);
	this->rightCollision = CollisionObject::create(
		PlatformerEntity::createCapsulePolygon(Size(PlatformerEntity::WallDetectorSize, this->entitySize.height), 1.0f),
		(int)PlatformerCollisionType::WallDetector,
		false,
		false
	);

	this->hexusOpponentData = nullptr;
	this->inventory = Inventory::create(inventorySaveKey);
	this->equipmentInventory = EquipmentInventory::create(equipmentSaveKey);
	this->currencyInventory = CurrencyInventory::create(currencySaveKey);
	this->speechBubble = SpeechBubble::create();
	this->attacks = std::vector<PlatformerAttack*>();
	this->spawnCoords = this->getPosition();
	this->clickHitbox = ClickableNode::create(UIResources::EmptyImage, UIResources::EmptyImage);
	this->controlState = ControlState::Normal;

	// TODO: Configurable/randomizable start direction (if any)
	this->movement = Vec2(0.0f, 0.0f);

	float width = this->properties[PlatformerEntity::MapKeyWidth].asFloat();
	float height = this->properties[PlatformerEntity::MapKeyHeight].asFloat();
	Size movementSize = movementCollisionSize * scale;
	this->hoverHeight = std::abs(movementSize.height - this->entitySize.height);

	this->hackButtonOffset = Vec2(scaledColOffset.x, scaledColOffset.y + this->hoverHeight + this->entitySize.height);

	this->animationNode->setScale(scale);
	this->animationNode->playAnimation("Idle");
	this->animationNode->setPositionY(this->hoverHeight / 2.0f);

	this->movementCollision->bindTo(this);
	this->movementCollision->getPhysicsBody()->setPositionOffset(scaledColOffset + Vec2(0.0f, this->entitySize.height / 2.0f));
	this->entityCollision->getPhysicsBody()->setPositionOffset(scaledColOffset + Vec2(0.0f, movementSize.height / 2.0f));
	this->groundCollision->getPhysicsBody()->setPositionOffset(Vec2(0.0f, -this->hoverHeight / 2.0f + PlatformerEntity::GroundCollisionOffset + ghettoGroundCollisionFix));
	this->leftCollision->getPhysicsBody()->setPositionOffset(scaledColOffset + Vec2(-this->entitySize.width / 2.0f + PlatformerEntity::WallDetectorSize / 2.0f, movementSize.height / 2.0f));
	this->rightCollision->getPhysicsBody()->setPositionOffset(scaledColOffset + Vec2(this->entitySize.width / 2.0f - PlatformerEntity::WallDetectorSize / 2.0f, movementSize.height / 2.0f));
	this->animationNode->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->setAnchorPoint(Vec2(0.5f, 0.0f));

	this->clickHitbox->setContentSize(this->entitySize);
	this->clickHitbox->setPosition(Vec2(movementSize.width / 2.0f, movementSize.height / 2.0f));
	this->clickHitbox->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->clickHitbox->disableInteraction();

	if (GameUtils::keyExists(this->properties, PlatformerEntity::MapKeyFlipX))
	{
		this->animationNode->setFlippedX(this->properties[PlatformerEntity::MapKeyFlipX].asBool());
	}

	if (GameUtils::keyExists(this->properties, PlatformerEntity::MapKeyFlipY))
	{
		this->animationNode->setFlippedY(this->properties[PlatformerEntity::MapKeyFlipY].asBool());
	}

	this->maxHealth = baseHealth;
	this->maxMana = baseSpecial;

	this->health = this->maxHealth;
	this->mana = this->maxMana;
	this->runeCooldowns = std::vector<float>();

	for (int index = 0; index < PlatformerEntity::MaxRunes; index++)
	{
		this->runeCooldowns.push_back(0.0f);
	}

	this->addChild(this->movementCollision);
	this->addChild(this->entityCollision);
	this->addChild(this->groundCollision);
	this->addChild(this->leftCollision);
	this->addChild(this->rightCollision);
	this->addChild(this->animationNode);
	this->addChild(this->speechBubble);
	this->addChild(this->clickHitbox);
	this->addChild(this->inventory);
	this->addChild(this->equipmentInventory);
	this->addChild(this->currencyInventory);
}

PlatformerEntity::~PlatformerEntity()
{
}

void PlatformerEntity::onEnter()
{
	super::onEnter();

	this->rebuildWeaponCollision(PlatformerEntity::DefaultWeaponSize);

	if (GameUtils::getKeyOrDefault(this->properties, CollisionObject::MapKeyTypeCollision, Value("")).asString() == CollisionObject::MapKeyCollisionTypeNone)
	{
		this->movementCollision->setPhysicsEnabled(false);
		this->movementCollision->bindTo(nullptr);
	}

	this->scheduleUpdate();
}

void PlatformerEntity::initializePositions()
{
	super::initializePositions();

	this->speechBubble->setPositionY(this->entitySize.height / 2.0f + 16.0f);
}

void PlatformerEntity::initializeListeners()
{
	super::initializeListeners();

	this->addEventListener(EventListenerCustom::create(PlatformerEvents::EventCinematicHijack, [=](EventCustom*)
	{
		this->isCinimaticHijacked = true;
	}));

	this->addEventListener(EventListenerCustom::create(PlatformerEvents::EventCinematicRestore, [=](EventCustom*)
	{
		this->isCinimaticHijacked = false;
	}));
}

void PlatformerEntity::update(float dt)
{
	super::update(dt);

	for (int index = 0; index < this->getMaxRunes(); index++)
	{
		if (this->getRuneCooldown(index) > 0.0f)
		{
			this->setRuneCooldown(index, this->getRuneCooldown(index) - dt);
		}
	}
}

Vec2 PlatformerEntity::getButtonOffset()
{
	return this->hackButtonOffset;
}

HackablePreview* PlatformerEntity::createDefaultPreview()
{
	return EntityPreview::create(this);
}

float PlatformerEntity::getFloatHeight()
{
	return 0.0f;
}

void PlatformerEntity::performSwimAnimation()
{
	this->animationNode->playAnimation("Swim");
}

void PlatformerEntity::performJumpAnimation()
{
	this->animationNode->playAnimation("Jump");
}

void PlatformerEntity::addHealth(int healthDelta)
{
	this->setHealth(this->getHealth() + healthDelta);
}

void PlatformerEntity::setHealth(int health)
{
	if (this->isDead())
	{
		return;
	}

	this->health = MathUtils::clamp(health, 0, this->maxHealth);

	if (this->health <= 0)
	{
		this->animationNode->playAnimation("Death", SmartAnimationNode::AnimationPlayMode::PauseOnAnimationComplete);
	}
}

void PlatformerEntity::kill(bool loadDeadAnim)
{
	this->setHealth(0);

	if (loadDeadAnim)
	{
		this->animationNode->playAnimation("Dead", SmartAnimationNode::AnimationPlayMode::PauseOnAnimationComplete);
	}
}

void PlatformerEntity::revive()
{
	this->health = this->getMaxHealth();
	this->mana = this->getMaxMana();

	for (int index = 0; index < this->getMaxRunes(); index++)
	{
		this->setRuneCooldown(index, 0.0f);
	}

	// Idle
	this->animationNode->playAnimation();
}

int PlatformerEntity::getHealth()
{
	return this->health;
}

int PlatformerEntity::getMaxHealth()
{
	return this->maxHealth;
}

bool PlatformerEntity::isAlive()
{
	return !this->isDead();
}

bool PlatformerEntity::isDead()
{
	return this->health <= 0;
}

int PlatformerEntity::getMana()
{
	return this->mana;
}

void PlatformerEntity::addMana(int manaDelta)
{
	this->setMana(this->getMana() + manaDelta);
}

void PlatformerEntity::setMana(int mana)
{
	this->mana = MathUtils::clamp(mana, 0, this->getMaxMana());
}

int PlatformerEntity::getMaxMana()
{
	return this->maxMana;
}

int PlatformerEntity::getAvailableRunes()
{
	int availableRunes = 0;

	for (int index = 0; index < this->getMaxRunes(); index++)
	{
		if (this->getRuneCooldown(index) <= 0.0f)
		{
			availableRunes++;
		}
	}

	return availableRunes;
}

bool PlatformerEntity::tryUseRune()
{
	for (int index = this->getMaxRunes() - 1; index >= 0; index--)
	{
		if (this->getRuneCooldown(index) <= 0.0f)
		{
			PlatformerEvents::TriggerRuneConsumed(PlatformerEvents::RuneConsumedArgs(this, index));

			this->setRuneCooldown(index, PlatformerEntity::RuneCooldown);

			return true;
		}
	}

	return false;
}

float PlatformerEntity::getRuneCooldown(int runeIndex)
{
	int index = MathUtils::clamp(runeIndex, 0, this->getMaxRunes() - 1);

	return this->runeCooldowns[index];
}

void PlatformerEntity::setRuneCooldown(int runeIndex, float cooldown)
{
	int index = MathUtils::clamp(runeIndex, 0, this->getMaxRunes() - 1);

	this->runeCooldowns[index] = MathUtils::clamp(cooldown, 0.0f, PlatformerEntity::RuneCooldown);
}

int PlatformerEntity::getMaxRunes()
{
	return PlatformerEntity::MaxRunes;
}

void PlatformerEntity::setEq(int eq)
{
	this->eq = eq;
}

int PlatformerEntity::getEq()
{
	return this->eq;
}

bool PlatformerEntity::setEqExperience(int eqExperience)
{
	int expToLevel = StatsTables::getExpRequiredAtLevel(this->getEq());

	this->eqExperience = eqExperience;

	if (this->eqExperience >= expToLevel)
	{
		// Level up!
		this->setEq(this->getEq() + 1);
		
		// Recurse to handle potential over-leveling
		this->setEqExperience(this->eqExperience - expToLevel);

		return true;
	}

	return false;
}

bool PlatformerEntity::addEqExperience(int eqExperience)
{
	return this->setEqExperience(this->getEqExperience() + eqExperience);
}

int PlatformerEntity::getEqExperience()
{
	return this->eqExperience;
}

bool PlatformerEntity::getIsPlatformerDisabled()
{
	return this->isPlatformerDisabled;
}

void PlatformerEntity::disablePlatformerControls()
{
	this->isPlatformerDisabled = true;
}

SmartAnimationNode* PlatformerEntity::getAnimations()
{
	return this->animationNode;
}

Size PlatformerEntity::getEntitySize()
{
	return this->entitySize;
}

HexusOpponentData* PlatformerEntity::getHexusOpponentData()
{
	return this->hexusOpponentData;
}

CollisionObject* PlatformerEntity::getCollision()
{
	return this->movementCollision;
}

void PlatformerEntity::killAndRespawn()
{
	this->setHealth(0);

	this->runAction(Sequence::create(
		DelayTime::create(1.5f),
		CallFunc::create([=]()
		{
			this->setPosition(this->spawnCoords);
			this->entityCollision->setPosition(Vec2::ZERO);
			this->movementCollision->setPosition(Vec2::ZERO);

			this->revive();
		}),
		nullptr
	));
}

std::vector<PlatformerAttack*> PlatformerEntity::getAttacks()
{
	return this->attacks;
}

std::vector<PlatformerAttack*> PlatformerEntity::getAvailableAttacks()
{
	std::vector<PlatformerAttack*> availableAttacks = std::vector<PlatformerAttack*>();

	for (auto it = this->attacks.begin(); it != this->attacks.end(); it++)
	{
		if ((*it)->getSpecialCost() <= this->getMana())
		{
			availableAttacks.push_back(*it);
		}
	}

	return availableAttacks;
}

std::vector<PlatformerAttack*> PlatformerEntity::cloneAttacks()
{
	std::vector<PlatformerAttack*> attacksClone = std::vector<PlatformerAttack*>();

	for (auto it = this->attacks.begin(); it != this->attacks.end(); it++)
	{
		attacksClone.push_back((*it)->clone());
	}

	return attacksClone;
}

Inventory* PlatformerEntity::getInventory()
{
	return this->inventory;
}

CurrencyInventory* PlatformerEntity::getCurrencyInventory()
{
	return this->currencyInventory;
}

bool PlatformerEntity::isOnGround()
{
	return (!this->groundCollision->getCurrentCollisions().empty());
}

void PlatformerEntity::rebuildWeaponCollision(Size size)
{
	AnimationPart* mainhand = this->animationNode->getAnimationPart("mainhand");

	if (mainhand == nullptr)
	{
		return;
	}

	PlatformerCollisionType weaponType = this->collisionType == PlatformerCollisionType::Player ? PlatformerCollisionType::PlayerWeapon : 
		(this->collisionType == PlatformerCollisionType::Enemy ? PlatformerCollisionType::EnemyWeapon : PlatformerCollisionType::None);

	mainhand->removeTrackingObject(this->weaponCollision);

	this->weaponCollision = CollisionObject::create(
		PlatformerEntity::createCapsulePolygon(size, 1.0f),
		(int)weaponType,
		false,
		false
	);

	this->weaponCollision->setPhysicsEnabled(false);
	mainhand->addTrackingObject(this->weaponCollision);
}

PhysicsBody* PlatformerEntity::createCapsulePolygon(Size size, float scale)
{
	Size newSize = size * scale;

	newSize.height = std::max(0.0f, newSize.height - PlatformerEntity::CapsuleRadius * 2.0f);

	std::vector<Vec2> points = std::vector<Vec2>();

	// Right side
	points.push_back(Vec2(newSize.width / 2.0f, newSize.height / 2.0f));
	points.push_back(Vec2(newSize.width / 2.0f, -newSize.height / 2.0f));

	// Bottom capsule
	points.push_back(Vec2(0.0f, -newSize.height / 2.0f - PlatformerEntity::CapsuleRadius));

	// Left side
	points.push_back(Vec2(-newSize.width / 2.0f, -newSize.height / 2.0f));
	points.push_back(Vec2(-newSize.width / 2.0f, newSize.height / 2.0f));

	// Top capsule
	points.push_back(Vec2(0.0f, newSize.height / 2.0f + PlatformerEntity::CapsuleRadius));

	return PhysicsBody::createPolygon(points.data(), points.size(), PhysicsMaterial(0.5f, 0.0f, 0.5f));
}

void PlatformerEntity::registerAttack(PlatformerAttack* attack)
{
	this->addChild(attack);
	this->attacks.push_back(attack);
}

float PlatformerEntity::getScale()
{
	return this->scale;
}

std::string PlatformerEntity::getAnimationResource()
{
	return this->animationResource;
}

std::string PlatformerEntity::getEmblemResource()
{
	return this->emblemResource;
}
