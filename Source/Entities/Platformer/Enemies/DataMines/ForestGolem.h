#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class ForestGolem : public PlatformerEnemy
{
public:
	static ForestGolem* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	ForestGolem(cocos2d::ValueMap& properties);
	virtual ~ForestGolem();

private:
	typedef PlatformerEnemy super;
};
