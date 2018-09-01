#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class Troll : public PlatformerEnemy
{
public:
	static Troll * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyTroll;

private:
	Troll(ValueMap* initProperties);
	~Troll();
};