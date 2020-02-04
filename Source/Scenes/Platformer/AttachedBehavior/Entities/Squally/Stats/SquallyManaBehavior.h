#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Squally;

class SquallyManaBehavior : public AttachedBehavior
{
public:
	static SquallyManaBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyManaBehavior(GameObject* owner);
	virtual ~SquallyManaBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;
	
	void saveState();
	void recalculateMaxMana(std::function<void()> onCalculated);

	Squally* squally;
};
