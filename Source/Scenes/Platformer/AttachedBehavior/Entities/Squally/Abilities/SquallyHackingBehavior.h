#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Squally;

class SquallyHackingBehavior : public AttachedBehavior
{
public:
	static SquallyHackingBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyHackingBehavior(GameObject* owner);
	virtual ~SquallyHackingBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	void toggleHackerMode();

	Squally* squally;
};
