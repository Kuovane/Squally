#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Squally;
class SmartAnimationSequenceNode;

class SquallyMouthBehavior : public AttachedBehavior
{
public:
	static SquallyMouthBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyMouthBehavior(GameObject* owner);
	~SquallyMouthBehavior();

	void onLoad() override;
	void update(float dt) override;

private:
	typedef AttachedBehavior super;

	Squally* squally;
};
