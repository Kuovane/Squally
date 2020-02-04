#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class PlatformerEntity;

class EntityEqBehavior : public AttachedBehavior
{
public:
	static EntityEqBehavior* create(GameObject* owner);

	void load(std::string saveKeyEq, std::string saveKeyExp);
	void setEq(int eq);
	int getEq();
	bool setEqExperience(int eqExperience);
	bool addEqExperience(int eqExperience);
	int getEqExperience();
	
	static const int DefaultEq;

protected:
	EntityEqBehavior(GameObject* owner);
	virtual ~EntityEqBehavior();

	void onLoad() override;

	PlatformerEntity* entity;

private:
	typedef AttachedBehavior super;

	void save();

	std::string saveKeyEq;
	std::string saveKeyExp;
};
