#pragma once

#include "Entities/Platformer/PlatformerFriendly.h"

namespace cocos2d
{
	typedef std::map<std::string, Value> ValueMap;
}

class CollisionObject;
class PlatformerEnemy;
class SmartAnimationSequenceNode;

class Squally : public PlatformerFriendly
{
public:
	static Squally* deserialize(cocos2d::ValueMap& properties);

	float getFloatHeight() override;
	cocos2d::Vec2 getAvatarFrameOffset() override;

	static const std::string MapKeySqually;
	static const int SquallyBaseHealth;
	static const int SquallyBaseSpecial;

protected:
	void performSwimAnimation() override;

	cocos2d::Vec2 getButtonOffset() override;

private:
	typedef PlatformerFriendly super;
	friend class SquallyBehaviors;
	friend class SquallyCollisionBehaviors;
	friend class SquallyEquipmentVisuals;
	friend class SquallyMovementBehaviors;
	friend class SquallyOutOfCombatAttackBehaviors;
	
	Squally(cocos2d::ValueMap& properties);
	virtual ~Squally();
	
	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onHackerModeEnable(int eq) override;
	void registerHackables() override;
	bool isAliveSqually();
	void saveState();
	void loadState();
	void runEyeBlinkLoop();
	void spawnHelper();

	bool canJump;

	cocos2d::Node* cameraTrackTarget;
	SmartAnimationSequenceNode* leftEyeController;
	SmartAnimationSequenceNode* rightEyeController;

	static const float SquallyScale;
	static const std::string IdentifierIsAlive;
	static const std::string EventSquallyTrapped;
};
