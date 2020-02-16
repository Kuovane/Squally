#pragma once
#include <set>

#include "Engine/Maps/GameObject.h"

namespace cocos2d
{
	class ParticleSystem;
}

class CollisionObject;
class HackableData;
class LiquidNode;

class Water : public GameObject
{
public:
	static Water* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyWater;

protected:
	Water(cocos2d::ValueMap& properties);
	virtual ~Water();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void applyWaterForce(CollisionObject* target, float dt);

private:
	typedef GameObject super;

	CollisionObject* waterCollision;
	LiquidNode* water;

	void runSplashes();
	void runSplash(int index);

	cocos2d::Size waterSize;
	int splashes;

	static const float SplashSpacing;
	static const float WaterGravity;
	static const float WaterCollisionOffset;
	static const cocos2d::Color4B SurfaceColor;
	static const cocos2d::Color4B BodyColor;

	static const std::string MapKeyPropertyDisablePhysics;
};
