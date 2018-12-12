#include "CollisionObject.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"
#include "cocos/base/CCValue.h"
#include "cocos/physics/CCPhysicsBody.h"
#include "cocos/physics/CCPhysicsContact.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

const std::string CollisionObject::MapKeyTypeCollision = "collision";

CollisionObject* CollisionObject::create(cocos2d::PhysicsBody* physicsBody, CollisionType collisionType, bool isDynamic, bool canRotate)
{
	ValueMap valueMap = ValueMap();

	CollisionObject* instance = new CollisionObject(&valueMap, physicsBody, collisionType, isDynamic, canRotate);

	instance->autorelease();

	return instance;
}

CollisionObject::CollisionObject(ValueMap* initProperties, PhysicsBody* initPhysicsBody, std::string deserializedCollisionName, bool isDynamic, bool canRotate) :
	CollisionObject(initProperties, initPhysicsBody, (CollisionType)0, isDynamic, canRotate)
{
	// Fire event, allowing for the game to map the deserialized collision string type (ie 'solid') to a unique integer identifier for CollisionType
	CollisionMappingEvents::requestCollisionMapKeyMapping(CollisionMappingEvents::CollisionMapRequestArgs(deserializedCollisionName, this));

	// Fire event, allowing for the game to map what this collision object collides with
	if (this->physicsBody != nullptr)
	{
		CollisionMappingEvents::requestAllowedCollisionMapping(CollisionMappingEvents::AllowedCollisionsRequestArgs(this->physicsBody->getCollisionBitmask(), this));
	}
}

CollisionObject::CollisionObject(ValueMap* initProperties, PhysicsBody* initPhysicsBody, CollisionType collisionType, bool isDynamic, bool canRotate) :
	HackableObject(initProperties)
{
	this->physicsBody = initPhysicsBody;
	this->collisionEvents = std::map<CollisionType, std::vector<std::function<CollisionResult(CollisionData)>>>();
	this->collisionEndEvents = std::map<CollisionType, std::vector<std::function<CollisionResult(CollisionData)>>>();

	if (this->physicsBody != nullptr)
	{
		this->physicsBody->setRotationEnable(canRotate);
		this->physicsBody->setDynamic(isDynamic);
		this->setPhysicsBody(initPhysicsBody);
	}

	this->setCollisionType(collisionType);

	// Fire event, allowing for the game to map what this collision object collides with
	CollisionMappingEvents::requestAllowedCollisionMapping(CollisionMappingEvents::AllowedCollisionsRequestArgs(collisionType, this));
}

CollisionObject::~CollisionObject()
{
}

void CollisionObject::onEnter()
{
	HackableObject::onEnter();

	this->scheduleUpdate();
}

void CollisionObject::initializeListeners()
{
	HackableObject::initializeListeners();

	EventListenerPhysicsContact* contactListener = EventListenerPhysicsContact::create();

	contactListener->onContactBegin = CC_CALLBACK_1(CollisionObject::onContactBegin, this);
	contactListener->onContactPreSolve = CC_CALLBACK_1(CollisionObject::onContactUpdate, this);
	contactListener->onContactPostSolve = CC_CALLBACK_1(CollisionObject::onContactUpdate, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(CollisionObject::onContactEnd, this);

	this->addEventListener(contactListener);
}

void CollisionObject::setCollisionType(CollisionType collisionType)
{
	if (this->physicsBody != nullptr)
	{
		this->physicsBody->setCategoryBitmask(collisionType);
	}
}

void CollisionObject::update(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 pos = this->getPosition();
	Size STOP_PHYSICS_OFFSET = visibleSize / 2.0f;

	if (this->physicsBody != nullptr && this->physicsBody->isDynamic())
	{
		Vec2 cameraPosition = GameCamera::getInstance()->getCameraPosition();

		if (pos.x > cameraPosition.x + visibleSize.width + STOP_PHYSICS_OFFSET.width ||
			pos.x < cameraPosition.x - STOP_PHYSICS_OFFSET.width ||
			pos.y > cameraPosition.y + visibleSize.height + STOP_PHYSICS_OFFSET.height ||
			pos.y < cameraPosition.y - STOP_PHYSICS_OFFSET.height)
		{
			// Bypass setter to force disable physics for this object
			this->physicsBody->setEnabled(false);
		}
		else
		{
			// Use setter such that if physics was disabled for a reason other than being off-screen, we do not overwrite that
			this->setPhysicsEnabled(this->physicsEnabled);
		}
	}
}

void CollisionObject::setPhysicsEnabled(bool enabled)
{
	this->physicsEnabled = enabled;

	if (this->physicsBody != nullptr)
	{
		this->physicsBody->setEnabled(enabled);
	}
}

Vec2 CollisionObject::getVelocity()
{
	return this->physicsBody == nullptr ? Vec2::ZERO : this->physicsBody->getVelocity();
}

void CollisionObject::setVelocity(Vec2 velocity)
{
	if (this->physicsBody != nullptr)
	{
		this->physicsBody->setVelocity(velocity);
	}
}

CollisionType CollisionObject::getCollisionType()
{
	return this->physicsBody == nullptr ? (CollisionType)0 : (CollisionType)this->physicsBody->getCategoryBitmask();
}

void CollisionObject::addPhysicsShape(cocos2d::PhysicsShape* shape)
{
	if (this->physicsBody != nullptr)
	{
		this->physicsBody->addShape(shape);
	}
}

void CollisionObject::allowCollisionWith(std::vector<CollisionType> collisionTypes)
{
	CollisionType bitmask = 0;

	for (auto it = collisionTypes.begin(); it != collisionTypes.end(); it++)
	{
		bitmask |= *it;
	}

	this->physicsBody->setContactTestBitmask(this->physicsBody->getContactTestBitmask() | (int)bitmask);
	this->physicsBody->setCollisionBitmask(this->physicsBody->getCollisionBitmask() | (int)bitmask);
}

void CollisionObject::whenCollidesWith(std::vector<CollisionType> collisionTypes, std::function<CollisionResult(CollisionData)> onCollision)
{
	for (auto it = collisionTypes.begin(); it != collisionTypes.end(); it++)
	{
		CollisionType collisionType = *it;

		if (this->collisionEvents.find(collisionType) != this->collisionEvents.end())
		{
			this->collisionEvents[collisionType] = std::vector<std::function<CollisionResult(CollisionData)>>();
		}

		this->collisionEvents[collisionType].push_back(onCollision);
	}
}

void CollisionObject::whenStopsCollidingWith(std::vector<CollisionType> collisionTypes, std::function<CollisionResult(CollisionData)> onCollisionEnd)
{
	for (auto it = collisionTypes.begin(); it != collisionTypes.end(); it++)
	{
		CollisionType collisionType = *it;

		if (this->collisionEndEvents.find(collisionType) != this->collisionEndEvents.end())
		{
			this->collisionEndEvents[collisionType] = std::vector<std::function<CollisionResult(CollisionData)>>();
		}

		this->collisionEndEvents[collisionType].push_back(onCollisionEnd);
	}
}

bool CollisionObject::onContactBegin(PhysicsContact &contact)
{
	// Currently we are not distinguishing between these two
	return this->onContactUpdate(contact);
}

bool CollisionObject::onContactUpdate(PhysicsContact &contact)
{
	return this->runContactEvents(contact, this->collisionEvents);
}

bool CollisionObject::onContactEnd(PhysicsContact &contact)
{
	return this->runContactEvents(contact, this->collisionEndEvents);
}

bool CollisionObject::runContactEvents(cocos2d::PhysicsContact& contact, std::map<CollisionType, std::vector<std::function<CollisionResult(CollisionData)>>> eventMap)
{
	CollisionData collisionData = this->constructCollisionData(contact);
	CollisionResult result = CollisionResult::CollideWithPhysics;

	if (collisionData.other != nullptr)
	{
		CollisionType collisionType = collisionData.other->getCollisionType();

		if (eventMap.find(collisionType) != eventMap.end())
		{
			std::vector<std::function<CollisionResult(CollisionData)>> events = eventMap[collisionType];

			for (auto eventIt = events.begin(); eventIt != events.end(); eventIt++)
			{
				CollisionResult eventResult = (*eventIt)(collisionData);

				// Doing nothing takes precidence
				result = (result == CollisionResult::DoNothing) ? CollisionResult::DoNothing : eventResult;
			}
		}
	}

	return (result == CollisionResult::CollideWithPhysics ? true : false);
}

CollisionObject::CollisionData CollisionObject::constructCollisionData(PhysicsContact& contact)
{
	PhysicsShape* other = nullptr;

	if (contact.getShapeA()->getBody() != this->physicsBody && contact.getShapeB()->getBody() != this->physicsBody)
	{
		return nullptr;
	}

	if (contact.getShapeA()->getBody() == this->physicsBody)
	{
		other = contact.getShapeB();
	}
	else
	{
		other = contact.getShapeA();
	}

	return CollisionObject::CollisionData(dynamic_cast<CollisionObject*>(other->getBody()->getNode()));
}
