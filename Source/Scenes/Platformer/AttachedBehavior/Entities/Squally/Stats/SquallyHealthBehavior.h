#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Squally;

class SquallyHealthBehavior : public AttachedBehavior
{
public:
	static SquallyHealthBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyHealthBehavior(GameObject* owner);
	virtual ~SquallyHealthBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;
	
	void saveState();
	void respawn(float delay);
	void recalculateMaxHealth(std::function<void()> onCalculated);

	cocos2d::Vec2 spawnCoords;

	Squally* squally;
};
