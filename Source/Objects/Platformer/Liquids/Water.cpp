#include "Water.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCValue.h"

#include "Engine/Physics/CollisionObject.h"
#include "Engine/Physics/Liquid/LiquidNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string Water::MapKeyWater = "water";
const float Water::SplashSpacing = 192.0f;
const float Water::WaterGravity = 0.0f;
const float Water::WaterCollisionOffset = 128.0f;
const Color4B Water::SurfaceColor = Color4B(105, 190, 206, 212);
const Color4B Water::BodyColor = Color4B(98, 186, 209, 64);

Water* Water::create(ValueMap& properties)
{
	Water* instance = new Water(properties);

	instance->autorelease();

	return instance;
}

Water::Water(ValueMap& properties) : super(properties)
{
	this->waterSize = Size(this->properties.at(GameObject::MapKeyWidth).asFloat(), this->properties.at(GameObject::MapKeyHeight).asFloat());
	this->water = LiquidNode::create(this->waterSize, 192.0f, Water::SurfaceColor, Water::BodyColor);
	this->splashes = int(std::round(this->waterSize.width / Water::SplashSpacing));

	float waterCollisionHeight = MathUtils::clamp(this->waterSize.height - Water::WaterCollisionOffset, 0.0f, this->waterSize.height);
	float effectiveOffset = this->waterSize.height - waterCollisionHeight;
	Size collisionSize = Size(this->waterSize.width, waterCollisionHeight);

	std::string customCollison = GameUtils::getKeyOrDefault(this->properties, CollisionObject::MapKeyTypeCollision, Value("")).asString();

	if (customCollison == "")
	{
		this->waterCollision = CollisionObject::create(CollisionObject::createBox(collisionSize), (CollisionType)PlatformerCollisionType::Water, false, false);
	}
	else
	{
		this->waterCollision = CollisionObject::create(CollisionObject::createBox(collisionSize), customCollison, false, false);
	}

	this->waterCollision->setPositionY(-effectiveOffset / 2.0f);
	
	this->addChild(this->water);
	this->addChild(this->waterCollision);
}

Water::~Water()
{
}

void Water::onEnter()
{
	super::onEnter();

	this->runSplashes();
}

void Water::initializePositions()
{
	super::initializePositions();
}

void Water::initializeListeners()
{
	super::initializeListeners();

	this->waterCollision->whileCollidesWith({ (int)PlatformerCollisionType::Player, (int)PlatformerCollisionType::Physics }, [=](CollisionObject::CollisionData collisionData)
	{
		this->applyWaterForce(collisionData.other, collisionData.dt);

		return CollisionObject::CollisionResult::DoNothing;
	});
}

void Water::runSplashes()
{
	for (int index = 0; index < this->splashes; index++)
	{
		this->runSplash(index);
	}
}

void Water::runSplash(int index)
{
	this->water->runAction(Sequence::create(
		DelayTime::create(RandomHelper::random_real(1.0f, 2.0f)),
		CallFunc::create([=]()
		{
			float x = RandomHelper::random_real(0.0f, Water::SplashSpacing) * float(index);
			this->water->splash(x, RandomHelper::random_real(0.0f, 1.0f));
			this->runSplash(index);
		}),
		nullptr
	));
}

void Water::applyWaterForce(CollisionObject* target, float dt)
{
	target->setVelocity(target->getVelocity() + Vec2(0.0f, Water::WaterGravity * dt));
}
