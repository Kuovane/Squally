#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class HackableData;

class CinematicMarker : public HackableObject
{
public:
	static CinematicMarker* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	CinematicMarker(cocos2d::ValueMap& properties);
	~CinematicMarker();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef HackableObject super;
};
