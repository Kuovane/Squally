#include "Shaman.h"

Shaman* Shaman::create()
{
	Shaman* instance = new Shaman();

	instance->autorelease();

	return instance;
}

Shaman::Shaman() : Enemy::Enemy(
	Resources::Entities_Environment_Caverns_Shaman_Animations,
	false,
	Size(256.0f, 288.0f),
	0.75f,
	Vec2(0.0f, 0.0f))
{
}

Shaman::~Shaman()
{
}