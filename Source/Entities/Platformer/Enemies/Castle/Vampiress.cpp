#include "Vampiress.h"

const std::string Vampiress::KeyEnemyVampiress = "vampiress";

Vampiress* Vampiress::deserialize(ValueMap* initProperties)
{
	Vampiress* instance = new Vampiress(initProperties);

	instance->autorelease();

	return instance;
}

Vampiress::Vampiress(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Castle_Vampiress_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(96.0f, 236.0f),
	0.9f,
	Vec2(0.0f, 0.0f))
{
}

Vampiress::~Vampiress()
{
}